#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("MD ARIF KHAN");
MODULE_DESCRIPTION("A simple LKM that prints Hello World");
MODULE_VERSION("0.1");

static int __init hello_world_init(void) {
    printk(KERN_INFO "Hello World! This is my first kernel module.\n");
    return 0; // Non-zero return means that the module couldn't be loaded.
}

static void __exit hello_world_exit(void) {
    printk(KERN_INFO "Goodbye World! Unloading my first kernel module.\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);