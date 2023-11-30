#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Equipo Team4evah");
MODULE_DESCRIPTION("Module Team-Forever!");
MODULE_VERSION("0.01");
Convertia*


//#define DEVICE_NAME "superdupermodule"

/*static int major;
struct cdev char_device;
*/
/*static int vacaciones_open(struct inode*, struct file*);
static int vacaciones_release(struct inode*, struct file*);*/
/*static ssize_t supermodule_read(struct file*, char*, size_t, loff_t*);
static ssize_t supermodule_write(struct file*, const char*, size_t, loff_t*);
int write_to_user(char *, char *);
*/

static int __init Team4evah_init(void) {
    //int result;
    //major = register_chrdev(0, DEVICE_NAME, &fops);

    /*if (major < 0) {
        printk(KERN_ALERT "Super Module load failed\n");
        return major;
    }*/

    printk(KERN_INFO "Team4evah Module has been loaded\n");

    /*printk(KERN_INFO "I was assigned major number %d. To talk to\n", major);
    printk(KERN_INFO "the driver, create a dev file with\n");
    printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, major);
    printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
    printk(KERN_INFO "the device file.\n");
    printk(KERN_INFO "Remove the device file and module when done.\n");
*/
    /*cdev_init(&char_device, &fops);
    char_device.owner = THIS_MODULE;
    // Add the character device to the system
    result = cdev_add(&char_device, major, 1);
    if (result < 0) {
        unregister_chrdev_region(major, 1);
        pr_err("Failed to add the character device\n");
        return result;
    }

    printk(KERN_INFO "The device file for ths module is: /dev/%s\n", DEVICE_NAME);
    */
    return 0;
}

static void __exit Team4evah_exit(void) {
    printk(KERN_INFO "Aún no somos un equipo por siempre, removiendo módulo!!\n");
}


module_init(Team4evah_init);
module_exit(Team4evah_exit);
