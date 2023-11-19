#include <linux/init.h>
#include <linux/module.h>
#include "ring_buffer.c"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MD ARIF KHAN");
MODULE_DESCRIPTION("Ring Buffer Kernel Module");
MODULE_VERSION("0.1");

struct ring_buffer* rb;

static int __init ring_buffer_init(void){
    printk(KERN_INFO "Ring Buffer Module: Initializing\n");
    
    // initialize the ring buffer
    rb = init_ring_buffer();
    if(!rb){
        printk(KERN_INFO "Ring Buffer Module: Failed to initialize\n");
        return -ENOMEM;
    }

    return 0;
}

static void __exit ring_buffer_exit(void){
    printk(KERN_INFO "Ring Buffer Module: Exiting\n");

    // clean the ring buffer
    cleanup_ring_buffer(rb);
}

module_init(ring_buffer_init);
module_exit(ring_buffer_exit);


