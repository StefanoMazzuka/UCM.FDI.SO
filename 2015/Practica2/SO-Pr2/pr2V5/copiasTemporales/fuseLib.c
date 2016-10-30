#include "fuseLib.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <inttypes.h>
#include <linux/kdev_t.h>


//Modifica el tamaño de los datos reservados a un inodo, reservando o liberando espacio si es necesario
int resizeInodo(uint64_t idxNodoI, size_t newSize){
	EstructuraNodoI *nodoI=miSistemaDeFicheros.nodosI[idxNodoI];
	char bloque[TAM_BLOQUE_BYTES];
	int i, diff=newSize-nodoI->tamArchivo;
	
	if(!diff)
		return 0;
	
	memset(bloque, 0, sizeof(char)*TAM_BLOQUE_BYTES);

	/// El fichero crece
	if(diff>0){
		
		///Borramos el contenido extra del último bloque si hay bloque y no está lleno
		if( nodoI->numBloques && nodoI->tamArchivo%TAM_BLOQUE_BYTES ){
			int bloqueActual=nodoI->idxBloques[nodoI->numBloques-1];
			if ( (lseek(miSistemaDeFicheros.fdDiscoVirtual, bloqueActual * TAM_BLOQUE_BYTES, SEEK_SET) == (off_t) - 1) ||
				 (read(miSistemaDeFicheros.fdDiscoVirtual, &bloque, TAM_BLOQUE_BYTES) == -1) ){
				perror("Falló lseek/read en resizeInodo"); 
				return -EIO;
			}
			int offBloque = nodoI->tamArchivo % TAM_BLOQUE_BYTES;
			int bytes2Write=(diff > (TAM_BLOQUE_BYTES-offBloque))?TAM_BLOQUE_BYTES-offBloque:diff;
			for(i=0;i<bytes2Write;i++){
				bloque[offBloque++]=0;
			}

	        if( (lseek(miSistemaDeFicheros.fdDiscoVirtual, bloqueActual * TAM_BLOQUE_BYTES, SEEK_SET) == (off_t) - 1) || 
				(write(miSistemaDeFicheros.fdDiscoVirtual, &bloque, TAM_BLOQUE_BYTES) == -1) ){
				perror("Falló lseek/write en resizeInodo"); 
				return -EIO;
			}
		}
		
		/// Tamaño del fichero en bloques tras el aumento
		int newBloques = (newSize + TAM_BLOQUE_BYTES -1)/TAM_BLOQUE_BYTES-nodoI->numBloques; 
		if(newBloques){
			memset(bloque, 0, sizeof(char)*TAM_BLOQUE_BYTES);
			
			// Comprobamos que hay suficiente espacio
			if ( newBloques > miSistemaDeFicheros.superBloque.numBloquesLibres )
				return -ENOSPC;

			miSistemaDeFicheros.superBloque.numBloquesLibres-=newBloques;
			int bloqueActual=nodoI->numBloques;
			nodoI->numBloques+=newBloques;
			
			for( i=0; bloqueActual!=nodoI->numBloques; i++ ) {
				if (miSistemaDeFicheros.mapaDeBits[i] == 0) {
					miSistemaDeFicheros.mapaDeBits[i] = 1;
					nodoI->idxBloques[bloqueActual] = i;
					bloqueActual++;
					//Borramos disco (necesario para truncate)
			        if( (lseek(miSistemaDeFicheros.fdDiscoVirtual, i * TAM_BLOQUE_BYTES, SEEK_SET) == (off_t) - 1) || 
						(write(miSistemaDeFicheros.fdDiscoVirtual, &bloque, TAM_BLOQUE_BYTES) == -1) ){
						perror("Falló lseek/write en resizeInodo"); 
						return -EIO;
					}
				}
			}
		}
		nodoI->tamArchivo+=diff;

	}
	/// El fichero decrece
	else{
		//Tamaño del fichero en bloques tras el truncado
		int numBloques = (newSize + TAM_BLOQUE_BYTES -1)/TAM_BLOQUE_BYTES; 
		miSistemaDeFicheros.superBloque.numBloquesLibres+=(nodoI->numBloques-numBloques);

		for( i=nodoI->numBloques; i>numBloques; i-- ) {
			int nBloque = nodoI->idxBloques[i-1];
			miSistemaDeFicheros.mapaDeBits[nBloque] = 0;
			//Borramos disco (no es necesario)
	        if( (lseek(miSistemaDeFicheros.fdDiscoVirtual, nBloque * TAM_BLOQUE_BYTES, SEEK_SET) == (off_t) - 1) || 
				(write(miSistemaDeFicheros.fdDiscoVirtual, &bloque, TAM_BLOQUE_BYTES) == -1) ){
				perror("Falló lseek/write en resizeInodo"); 
				return -EIO;
			}
		}
		nodoI->numBloques=numBloques;
		nodoI->tamArchivo+=diff;
	}
	nodoI->tiempoModificado = time(NULL);
	sync();

	/// Guardamos en disco el contenido de las estructuras modificadas
	escribeSuperBloque(&miSistemaDeFicheros);
	escribeMapaDeBits(&miSistemaDeFicheros);
	escribeNodoI(&miSistemaDeFicheros, idxNodoI, nodoI);
	sync();
	
	return 1;
}

//Formatea el modo de acceso de un fichero para que sea imprimible en pantalla
void mode_string (mode_t mode, char *str) {
  str[0] = mode & S_IRUSR ? 'r' : '-';
  str[1] = mode & S_IWUSR ? 'w' : '-';
  str[2] = mode & S_IXUSR ? 'x' : '-';
  str[3] = mode & S_IRGRP ? 'r' : '-';
  str[4] = mode & S_IWGRP ? 'w' : '-';
  str[5] = mode & S_IXGRP ? 'x' : '-';
  str[6] = mode & S_IROTH ? 'r' : '-';
  str[7] = mode & S_IWOTH ? 'w' : '-';
  str[8] = mode & S_IXOTH ? 'x' : '-';
  str[9] = '\0';
}

/*
 * Get file attributes.
 * 
 * The 'st_dev' and 'st_blksize' fields are ignored. The 'st_ino' field is ignored except if the 'use_ino' mount option is given.
 * 
 *	struct stat {
 *		dev_t     st_dev;     // ID of device containing file
 *		ino_t     st_ino;     // inode number
 *		mode_t    st_mode;    // prot