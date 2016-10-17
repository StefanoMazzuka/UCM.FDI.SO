#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mytar.h"

extern char *uso;
int loadstr( FILE *file, char** buf );

/** Copia el nBytes del fichero origen al fichero destino.
 *
 * origen: puntero al descriptor FILE del fichero origen
 * destino: puntero al descriptor FILE del fichero destino
 * nBytes: numero de bytes a copiar
 *
 * Devuelve el numero de bytes copiados o -1 en caso de error. 
 */
int copynFile(FILE *origen, FILE *destimo, int nBytes){
 // Completar la función 
	int aux;
	int numeroBytes = 0;
	// Leemos un caracter 
	
	while((numeroBytes < nBytes) && ((aux = fgetc(origen)) != EOF)) {
		// Copiamos el caracter en el fichero destino
		fputc(aux, destimo);
		numeroBytes++;
	}
	return numeroBytes;
}

/** Carga en memoria la cabecera del tarball.
 *
 * tarFile: puntero al descriptor FILE del tarball
 * header: dirección de un puntero que se inicializará con la dirección de un
 * buffer que contenga los descriptores de los ficheros cargados.
 * nFiles: dirección de un entero (puntero a entero) que se inicializará con el
 * número de ficheros contenido en el tarball (primeros bytes de la cabecera).
 *
 * Devuelve EXIT_SUCCESS en caso de exito o EXIT_FAILURE en caso de error
 * (macros definidas en stdlib.h).
 */
int readHeader(FILE *tarFile, stHeaderEntry **header, int *nFiles){
 // Completar la función 
	stHeaderEntry* array = NULL;
	//printf("nFuiles:");
	//(ptr donde leemos, tam dato a leer, numero datos, fichero del que leemos)
	fread(nFiles, sizeof(int), 1, tarFile);
	//printf("nFuiles:");
	// Reservamos memoria para el array
	array = malloc(sizeof(stHeaderEntry) * (*nFiles));
	//fseek(tarFile, 0, SEEK_SET);
	//printf("nFuiles:");
	int i;
	for( i = 0; i < *nFiles; i++){
		//printf("akiiiiiiiiiiiiiiiiiiiii");
		loadstr(tarFile, &array[i].name);
		//fprintf(stderr, "Archivo %d: %s \n", i, array[i].name);
		fread(&array[i].size, sizeof(int), 1, tarFile);
		//fprintf(stderr, "Tam Archivo %d: %u \n", i, array[i].size);
	}
	(*header)=array;

	return (EXIT_SUCCESS);
}

/** Carga una cadena de caracteres de un fichero.
 *
 * file: dirección de la estructura FILE del fichero
 * buf: dirección del puntero en que se inicializará con la dirección donde se
 * copiará la cadena. Será una dirección del heap obtenida con malloc.
 *
 * Devuelve: 0 si tuvo exito, -1 en caso de error.
 */
int loadstr( FILE *file, char** buf ){ 
 // Completar la función 
	char *cadena = (char *)(malloc(PATH_MAX * sizeof(char)));
	int i = 0, aux;
	char car;
	aux = fgetc(file);
	while ((aux != EOF) && ((char)aux != '\0')) {
		car = (char)aux;
		cadena[i] = car;
		aux = fgetc(file);// <---- ESTO FALTABA!!!!!!!!!!
		i++;
	}	
	cadena[i] = '\0';
	(*buf) = cadena;
	return 0;
}

/** crea un tarball a partir de unos ficheros de entrada.
 *
 * nfiles:    numero de ficheros de entrada
 * filenames: array con los nombres de los ficheros de entrada (rutas)
 * tarname:   nombre del tarball
 * 
 * devuelve exit_success en caso de exito y exit_failure en caso de error
 * (macros definidas en stdlib.h).
 *
 * ayuda: calcular primero el espacio necesario para la cabecera del tarball,
 * saltar dicho espacio desde el comienzo del archivo e ir copiando uno a uno
 * los ficheros, rellenando a la vez una representación de la cabecera del
 * tarball en memoria. al final copiar la cabecera al comienzo del tarball.
 * recordar que  que no vale un simple sizeof de stheaderentry para saber el
 * tamaño necesario en disco para el descriptor de un fichero puesto que sizeof
 * no calcula el tamaño de la cadena apuntada por name, sino el tamaño del
 * propio puntero. para calcular el tamaño de una cadena c puede usarse la
 * función strlen.
 */
int createTar(int nFiles, char *fileNames[], char tarName[]) {
 // Completar la función
	FILE *tarFile, *inFile;
	//Abrimos el fichero mtar para escritura (fichero destino)
	tarFile = fopen(tarName, "wb");
	
	stHeaderEntry *header;
	//Reservamos memoria para un array stHearderEntry, que tendrá tantas posiciones como ficheros haya que introducir en el mtar
	header = malloc(sizeof(stHeaderEntry) * nFiles ); //+ sizeof(int)SSOO repository
	
	int tamCabecera = 0;
	int i;
	for(i = 0; i < nFiles; i++){
		tamCabecera = tamCabecera + strlen(fileNames[i]) + 1; 
	}
	tamCabecera = sizeof(char) * tamCabecera + sizeof(int) + nFiles * sizeof(unsigned int);
	fseek(tarFile, tamCabecera, SEEK_SET);
	
	// Para cada fichero (inFile) que haya que copiar en el mtar
	for(i = 0; i < nFiles; i++){
		// Reservamos espacio para los nombres de los archivos, +1 por el '\0'
		int tamNombre = strlen(fileNames[i]) + 1;
		header[i].name = (char*)malloc(tamNombre);

		//Abrimos inputFile
		inFile = fopen(fileNames[i], "r");
		if(inFile == NULL){ // Se termina la ejecucion si falla la apertura de un archivo
			free(header);
			fclose(tarFile);
			return EXIT_FAILURE;
		}
		// Copiamos el nombre del archivo en el campo "name" de la cabecera
		strcpy(header[i].name, fileNames[i]);
		//printf("%s", header[i].name);
		// Copiamos el tamaño del archivo en el campo "size" de la cabecera
		header[i].size = copynFile(inFile, tarFile, INT_MAX);
		//printf("%d", header[i].size);
		//Cerramos inputFile
		fclose(inFile);
	}
	
	//Nos posicionamos para escribir en el byte 0 del fichero tar
	//fseek(tarFile, 0, SEEK_SET);
	rewind(tarFile);

	//Escribir número de ficheros principio header
	fwrite(&nFiles, sizeof(int), 1, tarFile);
	//Escribimos las cabeceras en el header
	//fwrite(header, sizeof(stHeaderEntry), nFiles, tarFile);

	//Escribimos las cabeceras
	for(i = 0; i < nFiles; ++i){
		fwrite(header[i].name, sizeof(char), strlen(fileNames[i]), tarFile);
		fputc('\0', tarFile);
		fwrite(&header[i].size, sizeof(unsigned int), 1, tarFile);
	}

	//Liberamos memoria y cerramos el fichero mtar
	free(header);
	fclose(tarFile);

	return EXIT_SUCCESS;
}

/** Extrae todos los ficheros de un tarball.
 *
 * tarName: cadena C con el nombre del tarball
 *
 * Devuelve EXIT_SUCCES en caso de exito y EXIT_FAILURE en caso de error (macros
 * definidas en stdlib.h).
 *
 * AYUDA: debemos cargar primero la cabecera, con lo que nos situaremos al
 * comienzo del primer fichero almacenado. Entonces recorriendo la cabecera
 * sabremos el nombre que debemos ir dando a los ficheros y la cantidad de bytes
 * que debemos leer del fichero para cargar su contenido.
 */
int extractTar(char tarName[]) {
 // Completar la función 
	stHeaderEntry *header;
	FILE *tarFile, *outPutFile;
	int numeroArchivos;
	
	// Abrimos el tarball
	tarFile = fopen(tarName, "rb");	
	//printf("nFuiles:");
	// Leemos la cabecera del tarball
	//printf("estamos aqui \n\n");
	//printf("nFuiles:");
	readHeader(tarFile, &header, &numeroArchivos);
	//printf("asasasas asasas \n\n");
	// Creamos lo ficheros del mtar. Recorremos la cabecera para crear los ficheros
	int i;
	//printf("%d", numeroArchivos);
	for(i = 0; i < numeroArchivos; i++){
		outPutFile = fopen(header[i].name, "wb");
		copynFile(tarFile, outPutFile, header[i].size);
		fclose(outPutFile);
	}
	// Liberamos memoria y cerramos el tarball
	free(header);
	fclose(tarFile);
	
	return (EXIT_SUCCESS);
}
/**
* tarname:   nombre del tarball
* filenames: array con los nombres de los ficheros de entrada (rutas)
* nfiles:    numero de ficheros de entrada
* 
* Añade los ficheros al final de archivo .mtar. La funcion devuelve 0
* si se ha ejecutado correctamente.
*
*/
int listTar(char tarName[]){
	//printf("ESTAMOS AQUI");
	stHeaderEntry *header; 
	int nFiles, i; 
	FILE *tarFile;
	// Abrimos el archivo mtar
	tarFile = fopen(tarName, "r");
	//Leemos toda la cabecera del tar
	readHeader(tarFile, &header , &nFiles);
	//Mostramos nombre y tamaño
	for(i = 0; i < nFiles;i++){
		printf("Name: %s --- ", header[i].name);
		printf("Size: %i Bytes.\n", header[i].size);
	}
	fclose(tarFile);
	return (EXIT_SUCCESS);
}
/**
* tarname:   nombre del tarball
* filenames: array con los nombres de los ficheros de entrada (rutas)
* nfiles:    numero de ficheros de entrada
* 
* Añade los ficheros al final de archivo .mtar. La funcion devuelve 0
* si se ha ejecutado correctamente.
*
*/
int extractTarDirectory(char* tarName, char* directory){

	char* name_directory;

	stHeaderEntry *header;
	FILE *tarFile, *outPutFile;
	int numeroArchivos;
	
	// Abrimos el tarball
	tarFile = fopen(tarName, "rb");	
	// Leemos la cabecera del tarball
	readHeader(tarFile, &header, &numeroArchivos);
	// Creamos lo ficheros del mtar. Recorremos la cabecera para crear los ficheros
	int i;
	//printf("%d", numeroArchivos);
	for(i = 0; i < numeroArchivos; i++){
	//+1 para la '/' test/a.txt 
		name_directory = malloc(strlen(header[i].name) + strlen(directory) + 1);
		sprintf(name_directory, "%s/%s", directory, header[i].name);
		//outPutFile = fopen(name_directory, "wb");
		if((outPutFile = fopen(name_directory, "wb")) == NULL){ // Se termina la ejecucion si falla la apertura de un archivo
			printf("El directorio de destino no existe. /n");
			return EXIT_FAILURE;
		}
		copynFile(tarFile, outPutFile, header[i].size);
		fclose(outPutFile);
	}
	// Liberamos memoria y cerramos el tarball
	free(header);
	fclose(tarFile);
	
	return (EXIT_SUCCESS);
}
   
