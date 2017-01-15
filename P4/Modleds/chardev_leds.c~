#include <linux/kernel.h>	//imprescindible
#include <linux/module.h>	//imprescindible
#include <linux/fs.h>
#include <asm/uaccess.h>	/* for copy_to_user */
#include <linux/cdev.h>


#include <asm-generic/errno.h>
#include <linux/init.h>
#include <linux/tty.h>      /* For fg_console */
#include <linux/kd.h>       /* For KDSETLED */
#include <linux/vt_kern.h>
#include <linux/version.h> /* For LINUX_VERSION_CODE */

MODULE_LICENSE("GPL");

//Las macros definidas podrian ampliarse para seleccionar marcaras de bits que encienda solo luces especificas...eso seria way!
#define ALL_LEDS_ON 0x7
#define ALL_LEDS_OFF 0
#define ONLY_CAPS_LED 0x4
#define ONLY_NUM_LED 0x2
#define ONLY_SCROLL_LED 0x1
#define SCROLL_NUM_LED 0x3
#define SCROLL_CAPS_LED 0x5
#define NUM_CAPS_LED 0x6

#define SUCCESS 0
#define DEVICE_NAME "LEDS"
#define BUF_LEN 80




/* Set led state to that specified by mask */
static inline int set_leds(struct tty_driver* handler, unsigned int mask)
{
#if ( LINUX_VERSION_CODE > KERNEL_VERSION(2,6,32) )
    return (handler->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED,mask);
#else
    return (handler->ops->ioctl) (vc_cons[fg_console].d->vc_tty, NULL, KDSETLED, mask);
#endif
}


/*
 *  Prototypes
 */
int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);





dev_t start;				//Mascara de 32 bits (12 bits MAYOR number y 20 MINOR number)
struct cdev* LEDS=NULL;
struct tty_driver* kbd_driver= NULL; 	//almacena el puntero del manejador del controlador
static int Device_Open = 0;		// Is device open? Used to prevent multiple access to device
static char msg[BUF_LEN];		// The msg the device will give when asked
static char *msg_Ptr;			// This will be initialized every time the device is opened successfully


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

				 
//Interzaf de funciiones del dispositivo
static struct file_operations fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release
};

/*
 * This function is called when the module is loaded
 */
int init_module(void)
{
    int major;		/* Major number assigned to our device driver */
    int minor;		/* Minor number assigned to the associated character device */
    int ret;

    /* Get available (major,minor) range, recieve MAYOR number */
    if ((ret=alloc_chrdev_region (&start, 0, 1,DEVICE_NAME))) { //El "0" es el MINOR number de inicio y el "1" cuantos  
								//dispositivos queremos registrar
        printk(KERN_INFO "Can't allocate chrdev_region()");
        return ret;
    }

    /* Create associated cdev */
    if ((LEDS=cdev_alloc())==NULL) {
        printk(KERN_INFO "cdev_alloc() failed ");
        unregister_chrdev_region(start, 1); ////Devolver rango de mayor y minor
        return -ENOMEM;
    }

    cdev_init(LEDS,&fops); //conecta el driver con la interfaz de operaciones

    if ((ret=cdev_add(LEDS,start,1))) {	//añadir "1" dispositivo chardev
        printk(KERN_INFO "cdev_add() failed ");
        kobject_put(&LEDS->kobj);
        unregister_chrdev_region(start, 1);	//ante fallo devolver rango de mayor y minor
        return ret;
    }

    //Recogemos los valores deMAYOR y MINOR number con macros
    major=MAJOR(start);
    minor=MINOR(start);

    printk(KERN_INFO "I was assigned major number %d. To talk to\n", major);
    printk(KERN_INFO "the driver, create a dev file with\n");
    printk(KERN_INFO "'sudo mknod -m 666 /dev/%s c %d %d'.\n", DEVICE_NAME, major,minor);
    printk(KERN_INFO "Try to cat and echo to the device file.\n");
    printk(KERN_INFO "Remove the device file and module when done.\n");

    //kbb_driver almacena el manejador del controlador del dispositvo del teclado
    kbd_driver= get_kbd_driver_handler();
    
    //se iluminan todo los leds (consultar macros disponibles, aqui podria hacerse algun filigrama con bucles....)
    set_leds(kbd_driver,ALL_LEDS_ON);

    return SUCCESS;
}

/*
 * This function is called when the module is unloaded
 */
void cleanup_module(void)
{

    //apagar todos los leds quizas podria hacerse de alguna manera vistosa
    //La mascara son 31 bits a 0, ¿eso significa una AND con los bits de la variable, o simplemente sobreescribe?, 
    //creo que es lo segundo, en ese caso si quieres apagar un bit especifico, tiene que dejar encendido los demas
    //hay que crearse mascaras para hacerlo mas comodo
  
    set_leds(kbd_driver,ALL_LEDS_OFF);
    /* Destroy chardev */
    if (LEDS)
        cdev_del(LEDS); //eliminamos del cdev el dispositivod

    /*
     * Unregister the device
     */
    unregister_chrdev_region(start, 1);//Devolver rango de mayor y minor

}

/*
 * Called when a process tries to open the device file, like
 * "cat /dev/chardev"
 */
static int device_open(struct inode *inode, struct file *file)
{
    if (Device_Open)
        return -EBUSY;

    Device_Open++;

    /* Initialize msg */
    sprintf(msg, "El driver deberia haber encendido todas las luces\n");

    /* Initially, this points to the beginning of the message */
    msg_Ptr = msg;

    /* Increase the module's reference counter */
    try_module_get(THIS_MODULE);

    return SUCCESS;
}

/*
 * Called when a process closes the device file.
 */
static int device_release(struct inode *inode, struct file *file)
{
    Device_Open--;		/* We're now ready for our next caller */

    /*
     * Decrement the usage count, or else once you opened the file, you'll
     * never get get rid of the module.
     */
    module_put(THIS_MODULE);

    return SUCCESS;
}

/*
 * Called when a process, which already opened the dev file, attempts to
 * read from it.
 */
static ssize_t device_read(struct file *filp,	/* see include/linux/fs.h   */
                           char *buffer,	/* buffer to fill with data *///Los bytes leidos se retornan en este buffer
                           size_t length,	/* length of the buffer     */
                           loff_t * offset)//Cuantos elementos hay en el buffer (array de bytes, NO hay que terminarlo por '\0' y su longitud viene definida por el atrivuto "lenght")
{
    /*
     * Number of bytes actually written to the buffer
     * Numeros de bytes escritos en el buffer
     */
    int bytes_to_read = length;

    /*
     * If we're at the end of the message,
     * return 0 -> end of file
     */
    if (*msg_Ptr == 0)
        return 0;

    /* Make sure we don't read more chars than
     * those remaining to read (por si acaso)
     */
    if (bytes_to_read > strlen(msg_Ptr))
        bytes_to_read=strlen(msg_Ptr);// ¿Por que no pasarle la funcion como argumento directamente, sera por localidad del metodo?

    /*
     * Actually transfer the data onto the userspace buffer.
     * For this task we use copy_to_user() due to security issues
     * En terminos generales en escritura/lectura nunca trabajaremos sobre el buffer directamente
     * ya que podriamos corromper el espacio de direcciones de la memoria del SO dado el nivel depermisos
     * en el que opera el Kernel...que es bastante menos restrictivo que la mayoria de niveles de uso.
     */
    if (copy_to_user(buffer,msg_Ptr,bytes_to_read)) //esencialmente sacariamos la info contenida del msg_Ptr
        return -EFAULT;
	/* copy_from_user() se usa en el write, este mecanismo de defensa permite retornar un
	* Error controlado
	*/

    /* Update the pointer for the next read operation 
     * Por seguridad reescribimos el total "real"
     */
    msg_Ptr+=bytes_to_read;

    /*
     * The read operation returns the actual number of bytes
     * we copied  in the user's buffer
     */
    return bytes_to_read;
}

/*
 * Called when a process writes to dev file: echo "hi" > /dev/chardev
 */
static ssize_t device_write(struct file *filp, const char *buffer, size_t length, loff_t * off)
{
    /*
     * Number of bytes actually written to the buffer
     * Numeros de bytes escritos en el buffer
     */
    int bytes_to_write = length;

    /*
     * If we're at the end of the message,
     * return 0 -> end of file
     */
    if (*msg_Ptr == 0)
        return 0;

    /* Make sure we don't read more chars than
     * those remaining to read (por si acaso)
     */
    if (bytes_to_write > strlen(msg_Ptr))
        bytes_to_write=strlen(msg_Ptr);// ¿Por que no pasarle la funcion como argumento directamente, sera por localidad del metodo?

    /*
     * Actually transfer the data onto the userspace buffer.
     * For this task we use copy_to_user() due to security issues
     * En terminos generales en escritura/lectura nunca trabajaremos sobre el buffer directamente
     * ya que podriamos corromper el espacio de direcciones de la memoria del SO dado el nivel depermisos
     * en el que opera el Kernel...que es bastante menos restrictivo que la mayoria de niveles de uso.
     */
    if (copy_from_user(msg_Ptr,buffer,bytes_to_write)) //esencialmente sacariamos la info contenida del msg_Ptr
        return -EFAULT;
	/* copy_from_user() se usa en el write, este mecanismo de defensa permite retornar un
	* Error controlado
	*/

    /* Update the pointer for the next read operation 
     * Por seguridad reescribimos el total "real"
     */
    msg_Ptr+=bytes_to_write;

    /*
     * The read operation returns the actual number of bytes
     * we copied  in the user's buffer
     */
    return bytes_to_write;
}
