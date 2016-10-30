#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>



int main() {
	int op, leds;
	op = menuPrincipal();
	leds = open("/dev/leds", O_WRONLY | O_CREAT | O_TRUNC );
	while(op != 0){
		if(op == 1){
			printf("\n\nGenerando un numero al azar(del 0 al 3)...");
			adivinaNumero(leds);
		}else if(op == 2){
			int rapidez = elijeVelocidad();
			contadorAs(leds, rapidez);
		}else if(op == 3){
			int rapidez = elijeVelocidad();
			contadorDes(leds, rapidez);
		}else if(op == 4){
			juegoDeLuces(leds);
		}else{
			printf("---> Opcion incorrecta!!! <--- \n");
		}
		op = menuPrincipal();
	}
	close(leds);
	return 0;
}

void juegoDeLuces(leds){
	char buff[4];
	int i, velocidad = 125000;
	for(i = 0; i < 10; i++){
		if(i == 5){
			velocidad = 62500;
		}
		buff[0] = ' ';
		buff[1] = ' ';
		buff[2] = ' ';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = '1';
		buff[1] = ' ';
		buff[2] = ' ';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = '1';
		buff[1] = '2';
		buff[2] = ' ';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = ' ';
		buff[1] = '2';
		buff[2] = '3';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = ' ';
		buff[1] = ' ';
		buff[2] = '3';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = ' ';
		buff[1] = ' ';
		buff[2] = ' ';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = ' ';
		buff[1] = ' ';
		buff[2] = '3';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = ' ';
		buff[1] = '2';
		buff[2] = '3';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = '1';
		buff[1] = '2';
		buff[2] = '3';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = '1';
		buff[1] = '2';
		buff[2] = ' ';
		write(leds, buff, 4);
		usleep(velocidad);
	}
	
	velocidad = 125000;
	buff[0] = '1';
	buff[1] = ' ';
	buff[2] = ' ';
	write(leds, buff, 4);
	usleep(velocidad);
	for(i = 0; i < 10; i++){
		buff[1] = '2';
		buff[2] = ' ';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[1] = ' ';
		buff[2] = '3';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[1] = ' ';
		buff[2] = ' ';
		write(leds, buff, 4);
		usleep(velocidad);
	}

	buff[0] = '1';
	buff[1] = '2';
	buff[2] = ' ';
	write(leds, buff, 4);
	usleep(250000);
	buff[0] = ' ';
	buff[1] = '2';
	buff[2] = '3';
	write(leds, buff, 4);
	usleep(250000);
	buff[0] = ' ';
	buff[1] = ' ';
	buff[2] = '3';
	write(leds, buff, 4);
	usleep(250000);
	buff[0] = ' ';
	buff[1] = ' ';
	buff[2] = ' ';
	write(leds, buff, 4);
	usleep(250000);
	buff[0] = ' ';
	buff[1] = ' ';
	buff[2] = '3';
	write(leds, buff, 4);
	usleep(250000);
	for(i = 0; i < 10; i++){
		buff[0] = ' ';
		buff[1] = '2';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = '1';
		buff[1] = ' ';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = ' ';
		buff[1] = ' ';
		write(leds, buff, 4);
		usleep(velocidad);
	}

	velocidad = 62500;
	for(i = 0; i < 10; i++){
		buff[0] = '1';
		buff[1] = ' ';
		buff[2] = ' ';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = ' ';
		buff[1] = ' ';
		buff[2] = ' ';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = '1';
		buff[1] = ' ';
		buff[2] = ' ';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = ' ';
		buff[1] = ' ';
		buff[2] = ' ';
		write(leds, buff, 4);
		usleep(250000);
		buff[0] = ' ';
		buff[1] = ' ';
		buff[2] = '3';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = ' ';
		buff[1] = ' ';
		buff[2] = ' ';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = ' ';
		buff[1] = ' ';
		buff[2] = '3';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = ' ';
		buff[1] = ' ';
		buff[2] = ' ';
		write(leds, buff, 4);
		usleep(velocidad);
	}
	
	
	for(i = 0; i < 15; i++){
		buff[0] = '1';
		buff[1] = ' ';
		buff[2] = '3';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = ' ';
		buff[1] = ' ';
		buff[2] = ' ';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = '1';
		buff[1] = ' ';
		buff[2] = '3';
		write(leds, buff, 4);
		usleep(500000);
		buff[0] = ' ';
		buff[1] = '2';
		buff[2] = ' ';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = ' ';
		buff[1] = ' ';
		buff[2] = ' ';
		write(leds, buff, 4);
		usleep(velocidad);
		buff[0] = ' ';
		buff[1] = '2';
		buff[2] = ' ';
		write(leds, buff, 4);
		usleep(500000);
		if(i > 9 && i < 14){
			buff[0] = '1';
			buff[1] = '2';
			buff[2] = '3';
			write(leds, buff, 4);
			usleep(velocidad);
			buff[0] = ' ';
			buff[1] = ' ';
			buff[2] = ' ';
			write(leds, buff, 4);
			usleep(velocidad);
			buff[0] = '1';
			buff[1] = '2';
			buff[2] = '3';
			write(leds, buff, 4);
			usleep(500000);
		}
		if (i == 14){
			buff[0] = '1';
			buff[1] = '2';
			buff[2] = '3';
			write(leds, buff, 4);
			sleep(4);
			buff[0] = ' ';
			buff[1] = ' ';
			buff[2] = ' ';
			write(leds, buff, 4);
		}
	}

}

int elijeVelocidad(){
	int op, rap;
	printf("**** ELIGE LA FRECUENCIA ****\n");
	printf("1.- Rapido(0.25 segundos)\n");
	printf("2.- Normal(1 segundo)\n");
	printf("3.- Lento(3 segundos)\n");
	printf("Elije la frecuencia: ");
	scanf("%i", &op);
	if(op == 1){
		rap = 250000;
	}else if(op == 2){
		rap = 1000000;
	}else if(op == 3){
		rap = 3000000;
	}else{
		rap = 1000000;
		printf("---> Opcion incorrecta, por defecto 1 segundo <--- \n");
	}
	return rap;
}

void adivinaNumero(int leds){
	int numero;
	int num;
	num = rand() % 4;
	//sleep(5);
	printf("\nAdivina el numero: ");
	scanf("%i", &numero);
	char buff[4];
	if(num == numero){ // Acierto
		int i;
		printf("--------> CORRECTO <--------\n\n");
		for(i = 0; i < 50; i++){
			buff[0] = '1';
			buff[1] = '2';
			buff[2] = '3';
			write(leds, buff, 4);
			usleep(50000);	
			buff[0] = ' ';
			buff[1] = ' ';
			buff[2] = ' ';
			write(leds, buff, 4);
			usleep(50000);
		}
	}else{ // Fallo
		int i;
		printf("Has fallado, el numero correcto era: %d\n\n", num);
		for(i = 0; i < 3; i++){
			buff[0] = '2';
			write(leds, buff, 4);
			usleep(500000);	
			buff[0] = ' ';
			write(leds, buff, 4);
			usleep(500000);
		}
	}
}

void contadorAs(int leds, int velocidad){
	char buff[4];
	int i;
	printf("---> 0 <--- \n");
	usleep(velocidad);

	//Num1
	buff[0] = '3';
	write(leds, buff, 4);
	printf("---> 1 <--- \n");
	usleep(velocidad);

	// num2
	buff[0] = '2';
	write(leds, buff, 4);
	printf("---> 2 <--- \n");
	usleep(velocidad);

	//Num3
	buff[0] = '2';
	buff[1] = '3';
	write(leds, buff, 4);
	printf("---> 3 <--- \n");
	usleep(velocidad);

	// num4
	buff[0] = '1';
	buff[1] = ' ';
	write(leds, buff, 4);
	printf("---> 4 <--- \n");
	usleep(velocidad);
	
	//Num5
	buff[0] = '3';
	buff[1] = '1';
	write(leds, buff, 4);
	printf("---> 5 <--- \n");
	usleep(velocidad);

	// num6
	buff[0] = '1';
	buff[1] = '2';
	write(leds, buff, 4);
	printf("---> 6 <--- \n");
	usleep(velocidad);
	
	//Num7
	buff[0] = '1';
	buff[1] = '2';
	buff[2] = '3';
	write(leds, buff, 4);
	printf("---> 7 <--- \n");
	usleep(velocidad);

	// Apaga los numeros
	buff[0] = ' ';
	buff[1] = ' ';
	buff[2] = ' ';
	write(leds, buff, 4);

}

void contadorDes(int leds, int velocidad){
	char buff[4];
	//Num7
	buff[0] = '1';
	buff[1] = '2';
	buff[2] = '3';
	write(leds, buff, 4);
	printf("---> 7 <--- \n");
	usleep(velocidad);
	
	// num6
	buff[2] = ' ';
	write(leds, buff, 4);
	printf("---> 6 <--- \n");
	usleep(velocidad);
	
	//Num5
	buff[2] = '3';
	buff[1] = ' ';
	write(leds, buff, 4);
	printf("---> 5 <--- \n");
	usleep(velocidad);
	
	// num4
	buff[0] = '1';
	buff[1] = ' ';
	buff[2] = ' ';
	write(leds, buff, 4);
	printf("---> 4 <--- \n");
	usleep(velocidad);
	
	//Num3
	buff[0] = '2';
	buff[1] = '3';
	write(leds, buff, 4);
	printf("---> 3 <--- \n");
	usleep(velocidad);
	
	// num2
	buff[0] = '2';
	buff[1] = ' ';
	write(leds, buff, 4);
	printf("---> 2 <--- \n");
	usleep(velocidad);

	//Num1
	buff[0] = '3';
	write(leds, buff, 4);
	printf("---> 1 <--- \n");
	usleep(velocidad);
	
	// Apaga los numeros
	buff[0] = ' ';
	buff[1] = ' ';
	buff[2] = ' ';
	write(leds, buff, 4);
	printf("---> 0 <--- \n");

}

int menuPrincipal(){
	int opcion;
	printf("\n******* MENU PRINCIPAL *******\n");
	printf("1.- Adivinar un numero\n");
	printf("2.- Contador binario ascendete\n");
	printf("3.- Contador binario descendente\n");
	printf("4.- Juego de luces\n");
	printf("0. SALIR\n");
	printf("Elije una opcion: ");
	scanf("%i", &opcion);
	return opcion;
}


