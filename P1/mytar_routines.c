#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mytar.h"

extern char *use;

/** Copy nBytes bytes from the origin file to the destination file.
 *
 * origin: pointer to the FILE descriptor associated with the origin file
 * destination:  pointer to the FILE descriptor associated with the destination file
 * nBytes: number of bytes to copy
 *
 * Returns the number of bytes actually copied or -1 if an error occured.
 */
int 
copynFile(FILE * origin, FILE * destination, int nBytes)
{
	/**
	* cont: number of "getc" function calls, should match with nBytes
	* c: int value to cats as a unsigned char on the "putc" function
	*/
	int c, cont = 0;

	while ((c = getc(origin)) != EOF && cont < nBytes){
		putc((unsigned char)c, destination);
		cont++;
	}
	return cont;
}

/** Loads a string from a file.
 *
 * file: pointer to the FILE descriptor 
 * 
 * The loadstr() function must allocate memory from the heap to store 
 * the contents of the string read from the FILE. 
 * Once the string has been properly built in memory, the function returns
 * the starting address of the string (pointer returned by malloc()) 
 * 
 * Returns: !=NULL if success, NULL if error
 */
char* 
loadstr(FILE * file)
{
	int n, size = 0;
	char* str = NULL;

	//calculate the number of characters on the file name
	do{
		n = getc(file);
		size++;
	}while(n != (int) '\0' && n != EOF);

	//try to allocate
	if(n != EOF )
		str = (char *)malloc(size);

	//Reset pointer reader to the begining of the name
	fseek(file, -size, SEEK_CUR);
	//read and store the file name
	fread(str, 1, size, file)
	return str;
}

/** Read tarball header and store it in memory.
 *
 * tarFile: pointer to the tarball's FILE descriptor 
 * nFiles: output parameter. Used to return the number 
 * of files stored in the tarball archive (first 4 bytes of the header).
 *
 * On success it returns the starting memory address of an array that stores 
 * the (name,size) pairs read from the tar file. Upon failure, the function returns NULL.
 */
stHeaderEntry* 
readHeader(FILE * tarFile, int *nFiles)
{
	//header to return;
	stHeaderEntry* header = NULL;

	//read the number of files inside the mytar file
	fread(nFiles,sizeof (int), 1,tarFile);

	//tryto alocate memory for header, NULL if fail
	header = (stHeaderEntry *)(malloc(sizeof(stHeaderEntry)* (*nFiles));
	//control de errores
	if(header == null){
		perror("Uopss! This mtar is too big to be alocated in memory");
		fclose(tarFile);
	}
	//alocate header information
	esle{
		for(int i = 0; i < *nFiles; i++){
			//error control
			if((header[i].name = loadstr(tarFile)) == NULL){
				for(int j = 0; j < i; j++)
					free(header[j].name);
				fclose(tarFile);
				return NULL;
			}
			fread(&header[i].size, sizeof(header[i].size), 1, tarFile);
		}
	}
	return header;
}

/** Creates a tarball archive 
 *
 * nfiles: number of files to be stored in the tarball
 * filenames: array with the path names of the files to be included in the tarball
 * tarname: name of the tarball archive
 * 
 * On success, it returns EXIT_SUCCESS; upon error it returns EXIT_FAILURE. 
 * (macros defined in stdlib.h).
 *
 * HINTS: First reserve room in the file to store the tarball header.
 * Move the file's position indicator to the data section (skip the header)
 * and dump the contents of the source files (one by one) in the tarball archive. 
 * At the same time, build the representation of the tarball header in memory.
 * Finally, rewind the file's position indicator, write the number of files as well as 
 * the (file name,file size) pairs in the tar archive.
 *
 * Important reminder: to calculate the room needed for the header, a simple sizeof 
 * of stHeaderEntry will not work. Bear in mind that, on disk, file names found in (name,size) 
 * pairs occupy strlen(name)+1 bytes.
 *
 */
int
createTar(int nFiles, char *fileNames[], char tarName[])
{
	FILE *tarFile, *in;
	stHeaderEntry *header;
	int headerSize = sizeof (int);

	//files value control
	if(nFiles <=0 || nFiles >= 1000){
		perror("No files to tar!! or too many!!");
		return EXIT_FAILURE;
	}
	//Try to open
	if((tarFile = fopen(tarName, "w")) == NULL){
		perror("Cannot open/create the tar file");
		return EXIT_FAILURE;
	}
	//Try to allocate memory header for the compress method
	if((header = malloc(sizeof(stHeaderEntry) * nFiles)) ==NULL){
		perror("Uoopss! Cannot allocate enought memory for this tar")
		fclose(tarFile);
		remove(tarName);
		return EXIT_FAILURE;
	}
	//Prepare header and total size
	for(int i = 0; i < nFiles; i++){
		//strlen(name)+1 bytes
		int nameSpace = strlen(fileNames) + 1;

		header[i].name = (char *)malloc(nameSpace);
		//check for error
		if(header[i].name == NULL){
			perror("Well, this is bad, we have lost a file name");
			fclose(tarFile);
			remove(tarName);
			for(int j = 0; j < i; j++)
				free(header[j].name);
			free(header);
			return EXIT_FAILURE;
		}
		//copy the string directly from the origin
		strcpy(header[i].name, fileNames[i]);
		//add the extra space
		headerSize += nameSpace + sideof (header -> size);
	}

	//Seek the pointer from the begin of the tar file to the end of the header
	fseek(tarFile, headerSize, SEEK_SET);

	for(i = 0; i < nFiles; i++){
		if((imputFile = fopen(fileNames[i], "r")) == NULL){
			perror("Well, this is bad, we cannot open the origin file");
			fclose(tarFile);
			remove(tarName);
			for(j = 0; j < i; j++)
				free(header[j].name);
			free(header);
			return EXIT_FAILURE;
		}
		//Copy
		header[i].size = copynFile(in, tarFile, INT_MAX);
		fclose(imputFile);
	}

	//Pointer to begin, ready to insert the header
	rewind(tarFile);
	//Add the first number (# of files).
	fwrite(&nFiles, sizeof(int),  1, tarFile);
	for(i = 0; i < nFiles; i++){
		fwrite(header[i].name, 1, strlen(header[i].name)+1, tarFile);
		fwrite(&header[i].size, sizeof(header[i].size), 1, tarFile);
	}
	fprintf(stdout, "Done it\n", );

	//free allocated memory
	for(i = 0; i < nFiles, i++)
		free(header[i].name);
	free(header);
	fclose(tarFile);

	return EXIT_SUCCESS;
}

/** Extract files stored in a tarball archive
 *
 * tarName: tarball's pathname
 *
 * On success, it returns EXIT_SUCCESS; upon error it returns EXIT_FAILURE. 
 * (macros defined in stdlib.h).
 *
 * HINTS: First load the tarball's header into memory.
 * After reading the header, the file position indicator will be located at the 
 * tarball's data section. By using information from the 
 * header --number of files and (file name, file size) pairs--, extract files 
 * stored in the data section of the tarball.
 *
 */
int
extractTar(char tarName[])
{
	// Complete the function
	stHeaderEntry *header;
	FILE *tarFile, *output;
	int nFiles;

	//open tar file
	if((tarFile = fopen(tarName, "r")) == NULL){
		perror("Cannot open the tar file");
		return EXIT_FAILURE;
	}

	//create the header
	readHeader(tarFile, &header, &nFiles);
	//create and write the files withthe contain information
	for(int i = 0; i < nFiles, i++){
		output = fopen(header[i].name, "w");
		copynFile(tarFile,output, header[i].size);
		fclose(output);
	}

	fprintf(stdout, "Extracted\n", );
	//liberar memoria
	free(header);
	fclose(tarFile);

	return EXIT_SUCCESS;
}