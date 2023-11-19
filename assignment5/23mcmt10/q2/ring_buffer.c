#include <linux/slab.h>
#include <linux/uaccess.h>

#define RING_BUF_SIZE 10

struct ring_buffer {
    int* buffer;
    size_t size;
    size_t head;
    size_t tail;
};

struct ring_buffer* init_ring_buffer(void) {
    struct ring_buffer* rb = kmalloc(sizeof(struct ring_buffer), GFP_KERNEL);
    if(!rb)
        return NULL;

    rb->buffer = kmalloc(sizeof(int) * RING_BUF_SIZE, GFP_KERNEL);
    if(!rb->buffer) {
        kfree(rb);
        return NULL;
    }

    rb->size = RING_BUF_SIZE;
    rb->head = 0;
    rb->tail = 0;

    return rb;
}

void cleanup_ring_buffer(struct ring_buffer* rb) {
    kfree(rb->buffer);
    kfree(rb);
}

int insert_to_ring_buffer(struct ring_buffer* rb, int data) {
    if((rb->head + 1) % rb->size == rb->tail){
        return -1; // buffer full
    }

    rb->buffer[rb->head] = data;
    rb->head = (rb->head + 1) % rb->size;
    return 0; // successfully inserted
}

int retrieve_from_ring_buffer(struct ring_buffer* rb, int* data) {
    if(rb->tail == rb->head)
        return -1; // buffer empty

    *data = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % rb->size;
    return 0; // successfully retrieved
}

