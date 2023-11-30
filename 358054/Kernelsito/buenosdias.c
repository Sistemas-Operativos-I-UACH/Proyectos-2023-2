#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "buenos_dias"

static int __init buenos_dias_init(void) {
    printk(KERN_INFO "Kernel buenos dias :) has been loaded\n");
    return 0;
}

static void __exit buenos_dias_exit(void) {
    printk(KERN_INFO "Kernel buenos dias :( has been unloaded\n");
}

module_init(buenos_dias_init);
module_exit(buenos_dias_exit);

MODULE_LICENSE("GPL");
