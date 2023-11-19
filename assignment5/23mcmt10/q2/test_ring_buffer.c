#include <linux/init.h>
#include <linux/module.h>
#include "ring_buffer.c"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MD ARIF KHAN");
MODULE_DESCRIPTION("Test Ring Buffer Kernel Module");
MODULE_VERSION("0.1");

static int __init test_ring_buffer_init(void){
    int data;
    int retrieved_data;

    struct ring_buffer* rb = init_ring_buffer();

    if(!rb){
        printk(KERN_ERR "Ring Buffer Module: Failed to initialize\n");
        return -ENOMEM;
    }
    
    // test insertion and retrieval
    data = 10;
    insert_to_ring_buffer(rb, data);
    data = 20;
    insert_to_ring_buffer(rb, data);
    data = 30;
    insert_to_ring_buffer(rb, data);
    
    retrieve_from_ring_buffer(rb, &retrieved_data);
    printk(KERN_INFO "Ring Buffer Module: First data: %d\n", retrieved_data);
    retrieve_from_ring_buffer(rb, &retrieved_data);
    printk(KERN_INFO "Ring Buffer Module: Second data: %d\n",retrieved_data);
    retrieve_from_ring_buffer(rb, &retrieved_data);
    printk(KERN_INFO "Ring Buffer Module: Third data: %d\n", retrieved_data);

    // test cleanup
    cleanup_ring_buffer(rb);

    return 0;
}

static void __exit test_ring_buffer_exit(void){
    printk(KERN_INFO "Ring Buffer Module: Exiting\n");
}

module_init(test_ring_buffer_init);
module_exit(test_ring_buffer_exit);