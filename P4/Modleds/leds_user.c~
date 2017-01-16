#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>


/*
*	Cabecera
*/
int menu();
int selectSpeed();
void contadorAscendente(int leds, int velocidad);

int main() {
	int op;
	int leds = open("/dev/leds", O_WRONLY | O_CREAT | O_TRUNC );
	while(op = menu()){
		switch(op) {
			case 1:
			    contadorAscendente(leds, selectSpeed());
			    break;
			case 2:
			    printf("Imaginate que va al reves que la opcion 1 ;) \n");
			    break;
			case '\n':
			    break;
			default:
				printf("Algo ha ido mal... \n");
			    return 0;
			}
	}
	close(leds);
	return 0;
}

int menu(){
	int op;
	printf("\n============== TEST ==============\n");
	printf("1.- Contador binario ascendete\n");
	printf("2.- Contador binario descendente\n");
	printf("0. SALIR\n");
	printf("Elije una opcion: ");
	scanf("%i", &op);
	printf("\n==================================\n");
	return op;
}

int selectSpeed(){
	int op, vel;
	printf("============== FRECUENCIA ==============\n");
	printf("1.- Rapido(0.25 segundos)\n");
	printf("2.- Normal(1 segundo)\n");
	printf("3.- Lento(3 segundos)\n");
	printf("Elije la frecuencia: ");
	scanf("%i", &op);
	if(op == 1){
		vel = 250000;
	}else if(op == 2){
		vel = 1000000;
	}else if(op == 3){
		vel = 3000000;
	}else{
		vel = 1000000;
		printf("---> Opcion incorrecta, por defecto 1 segundo <--- \n");
	}
	return vel;
}

static const char* cnt_str[8]={
"",
"3",
"2",
"23",
"1",
"13",
"12",
"123"};


void contadorAscendente(int leds, int velocidad){

	int i=0;

	for (i=0;i<8;i++){
		write(leds,cnt_str[i],strlen(cnt_str[i]));
		usleep(velocidad);
	}

#ifdef DIEGO
	char buff[4];
	int i;
	
printf("0\n");
	usleep(velocidad);


	buff[0] = '3';
	write(leds, buff, strlen(4));
	printf("1\n");
	usleep(velocidad);


	buff[0] = '2';
	write(leds, buff, 4);
	printf("2\n");
	usleep(velocidad);


	buff[0] = '2';
	buff[1] = '3';
	write(leds, buff, 4);
	printf("3\n");
	usleep(velocidad);


	buff[0] = '1';
	buff[1] = ' ';
	write(leds, buff, 4);
	printf("4\n");
	usleep(velocidad);
	

	buff[0] = '3';
	buff[1] = '1';
	write(leds, buff, 4);
	printf("5\n");
	usleep(velocidad);


	buff[0] = '1';
	buff[1] = '2';
	write(leds, buff, 4);
	printf("6\n");
	usleep(velocidad);
	

	buff[0] = '1';
	buff[1] = '2';
	buff[2] = '3';
	write(leds, buff, 4);
	printf("7\n");
	usleep(velocidad);

	buff[0] = ' ';
	buff[1] = ' ';
	buff[2] = ' ';
	write(leds, buff, 4);
#endif

}

