#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>



MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dinamita");
MODULE_DESCRIPTION("Modulin");
MODULE_VERSION("0.01");


#define DEVICE_NAME "Modulin"

static int major;
struct cdev char_device;

static int modulin_open(struct inode*, struct file*);
static int modulin_release(struct inode*, struct file*);
static ssize_t modulin_read(struct file*, char*, size_t, loff_t*);
static ssize_t modulin_write(struct file*, const char*, size_t, loff_t*);
int write_to_user(char *, char *);

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = modulin_open,
    .release = modulin_release,
    .read = modulin_read,
    .write = modulin_write,
};

char user_message[1024] = "Compa ¿Qué le parece esa morra?\nLa que anda bailando sola me gusta pa' mí\nBella, ella sabe que está buena\nQue todos andan mirándola cómo baila\nMe acerco y le tiro todo un verbo\nTomamos tragos sin peros, solo tentación";

static int __init modulin_init(void) {
    int result;
    major = register_chrdev(0, DEVICE_NAME, &fops);

    if (major < 0) {
        printk(KERN_ALERT "Modulin Module load failed\n");
        return major;
    }

    printk(KERN_INFO "Modulin Module has been loaded\n");

    printk(KERN_INFO "I was assigned major number %d. To talk to\n", major);
    printk(KERN_INFO "the driver, create a dev file with\n");
    printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, major);
    printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
    printk(KERN_INFO "the device file.\n");
    printk(KERN_INFO "Remove the device file and module when done.\n");

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

static void __exit modulin_exit(void) {
    printk(KERN_INFO "Aún no hay modulin, removiendo módulo!!\n");
}

static int modulin_open(struct inode *inodep, struct file *filep) {
   printk(KERN_INFO "Modulin Module device opened\n");
   return 0;
}


static ssize_t modulin_write(struct file *filep, const char *buffer,
                         size_t len, loff_t *offset) {
    //int errors = 0;
    static char message[256] = {0};
    if (copy_from_user(message, (void *)buffer, len))
        return -EFAULT;
    /*if (len > 1024) {
        printk(KERN_INFO "The message must be 1024 bytes or less");
        return -EFAULT;
    }*/
    strcpy(user_message, message);
    printk(KERN_INFO "From userland: %s\n", (char *)message);
    return len;
}

static int modulin_release(struct inode *inodep, struct file *filep) {
   printk(KERN_INFO "Super Module device closed\n");
   return 0;
}

static ssize_t modulin_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    int errors = 0;
    char *message = "Compa ¿Qué le parece esa morra?\nLa que anda bailando sola me gusta pa' mí\nBella, ella sabe que está buena\nQue todos andan mirándola cómo baila\nMe acerco y le tiro todo un verbo\nTomamos tragos sin peros, solo tentación";
    int message_len = strlen(message);
    errors = copy_to_user(buffer, message, message_len);
    printk(KERN_INFO "user_message: %s\n", message);
    return errors == 0 ? message_len : -EFAULT;
}


module_init(modulin_init);
module_exit(modulin_exit);