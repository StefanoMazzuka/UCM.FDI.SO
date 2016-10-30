/*
*E/S en Linux
/*
* hello.c - El módulo más simple y menos original posible.
*/
#include <linux/module.h> /* Requerido por todos los módulos */
#include <linux/kernel.h> /* Requerido por KERN_INFO */
MODULE_LICENSE("GPL");
int init_module(void) {
	printk(KERN_INFO "Hello world.\n");
	/*
	* Retorno != 0 implica fallo de init_module; el módulo no
	* puede cargarse.
	*/
	return 0;
}
void cleanup_module(void) {
	printk(KERN_INFO "Goodbye world.\n");                            
}

