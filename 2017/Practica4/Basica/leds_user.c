#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>


void contadorAscendente(int leds, int velocidad);

//opciones de encendido de los leds
static const char* cnt_str[8]={
" ",
"3",
"2",
"23",
"1",
"13",
"12",
"123"
};

int main(){
	int leds = open("/dev/chardev_leds", O_WRONLY | O_CREAT | O_TRUNC);

	contadorAscendente(leds, 2);
	
	close(leds);
	return 0;

}

void contadorAscendente(int leds, int velocidad){
	int i = 0;

	for(i = 0; i < 8; i++){
		write(leds, cnt_str[i],strlen(cnt_str[i]));
		sleep(velocidad);
	}

}
