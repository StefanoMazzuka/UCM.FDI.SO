#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

#define LOCKFILE "/dev/leds"


void leds(char * str, int len);

int main(int argc, char *argv[]){
	char x[4]="123";
	FILE *fichero1 = NULL;
	//Obtenemos el numero de escrituras en el disco sda, esto nos permitira comparar posteriormente
	//si ha habido alguna escritura en el disco y entonces iluminar los leds momentaneamente
	fichero1 = popen("cat /sys/block/sda/stat | awk '{ print $5 }'", "r");
	//fichero1 = popen("vmstat -d | egrep sda | awk '{ print $6 }'", "r");
	if (fichero1 == NULL){
		printf("Failed to run command\n");
		return 1;
	}
	
	char nEscrituras1[1000];
	fgets(nEscrituras1, 1000, fichero1);
	while(!feof(fichero1)) {
		fgets(nEscrituras1, 1000, fichero1);
	}
	pclose(fichero1);
	char nEscrituras2[1000];

	x[0]='\0';
	leds(x, 1);
	sleep( 1 );

	while (1){
		FILE *fichero2 = NULL;
		//fichero2 = popen("vmstat -d | egrep sda | awk '{ print $6 }'", "r");
		fichero2 = popen("cat /sys/block/sda/stat | awk '{ print $5 }'", "r");
		if (fichero2 == NULL){
			printf("Failed to run command\n");
			return 1;
		}
		fgets(nEscrituras2, 1000, fichero2);
		while(!feof(fichero2)) {
			fgets(nEscrituras2, 1000, fichero2);
		}
		if (strcmp(nEscrituras1, nEscrituras2) != 0) {
			strcpy(nEscrituras1, nEscrituras2);
			x[0]='1';
			x[1]='2';
			x[2]='3';
			x[3]='\0';
			leds(x, 3);
			usleep( 100000 );
		}
	
		else {
			x[0]='\0';
			leds(x, 1);
			usleep( 100000 );
		}
		pclose(fichero2);
	}

	printf("Good bye!!\n");
	
	return 0;
}


void leds(char * str, int len){
	int pfd;
	if ((pfd = open(LOCKFILE, O_WRONLY | O_CREAT | O_TRUNC)) == -1){
	    perror("Cannot open output file\n"); exit(1);
	}
	printf("Str:%s long:%i fileDescri:%i\n", str, len, pfd);

	write(pfd, str, len);

	close(pfd);
}
