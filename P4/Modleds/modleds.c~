#include <linux/module.h>
#include <asm-generic/errno.h>
#include <linux/init.h>
#include <linux/tty.h>      /* For fg_console */
#include <linux/kd.h>       /* For KDSETLED */
#include <linux/vt_kern.h>
#include <linux/version.h> /* For LINUX_VERSION_CODE */

//Las macros definidas podrian ampliarse para seleccionar marcaras de bits que encienda solo luces especificas...eso seria way!
#define ALL_LEDS_ON 0x7
#define ALL_LEDS_OFF 0

//mascaras de led idependientes
#define ONLY_CAPS_LED 0x4
#define ONLY_NUM_LED 0x2
#define ONLY_SCROLL_LED 0x1
#define SCROLL_NUM_LED 0x3
#define SCROLL_CAPS_LED 0x5
#define NUM_CAPS_LED 0x6



//almacena el puntero del manejador del controlador
struct tty_driver* kbd_driver= NULL;


/* Get driver handler */
struct tty_driver* get_kbd_driver_handler(void)
{
    printk(KERN_INFO "modleds: Cargado modulo de lucecitas\n");
    printk(KERN_INFO "modleds: LA version fgconsole es %x\n", fg_console);
    
    //Se retorna 
#if ( LINUX_VERSION_CODE > KERNEL_VERSION(2,6,32) )
    return vc_cons[fg_console].d->port.tty->driver;
#else
    return vc_cons[fg_console].d->vc_tty->driver;
#endif
}

/* Set led state to that specified by mask */
static inline int set_leds(struct tty_driver* handler, unsigned int mask)
{
#if ( LINUX_VERSION_CODE > KERNEL_VERSION(2,6,32) )
    return (handler->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED,mask);
#else
    return (handler->ops->ioctl) (vc_cons[fg_console].d->vc_tty, NULL, KDSETLED, mask);
#endif
}

static int __init modleds_init(void)
{
    //kbb_driver almacena el manejador del controlador del dispositvo del teclado
    kbd_driver= get_kbd_driver_handler();
    
    //se iluminan todo los leds (consultar macros disponibles, aqui podria hacerse algun filigrama con bucles....)
    set_leds(kbd_driver,ALL_LEDS_ON);
    return 0;
}

static void __exit modleds_exit(void)
{
    //apagar todos los leds quizas podria hacerse de alguna manera vistosa
    //La mascara son 31 bits a 0, ¿eso significa una AND con los bits de la variable, o simplemente sobreescribe?, 
    //creo que es lo segundo, en ese caso si quieres apagar un bit especifico, tiene que dejar encendido los demas
    //hay que crearse mascaras para hacerlo mas comodo
  
    set_leds(kbd_driver,ALL_LEDS_OFF);
}

module_init(modleds_init);
module_exit(modleds_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modleds");
