# Ring Buffer Kernel Module

This project consist of a Linux Kernel Module (LKM) that utilizes a ring/circular buffer data structure for efficient data storage and retrieval within the kernel

## Environment Setup

Run the following shell script to set up the development environment:

1. Add execute permission to script

   `chmod +x setup_env.sh`

2. Run the script

   `./setup_env.sh`

## Ring Buffer Implementation

### ring_buffer.c

This file contains the implementation of a ring buffer data structure. The functions include:

- `init_ring_buffer`: Initialize a new ring buffer.
- `cleanup_ring_buffer`: Releases resources allocated for the ring buffer.
- `insert_to_ring_buffer`: Insert data into the ring buffer.
- `retrieve_from_ring_buffer`: Retrieves data from the ring buffer.

## LKM Implementation

### ring_buffer_module.c

The LKM uses the ring buffer data structure. It provides an initialization function, `ring_buffer_init`, and an exit function, `ring_buffer_exit`, for setting up and cleaning up the module, respectively.

## Testing the Ring Buffer

### test_ring_buffer.c

This file contains a test program for the ring buffer module. It initialize a ring buffer, inserts data, retrieves data, and prints the results.

## Build Instructions

Use the provided Makefile to build the LKM and the test program:

`make`

cleanup the build artifacts with:

`make clean`

## Usage

1. Load the ring buffer module:

   `sudo insmod ring_buffer_module.ko`

2. Load the test program:

   `sudo insmod test_ring_buffer.ko`

3. Check kernel logs for output:

   `dmesg`

4. Unload the modules when done:

   `sudo rmmod test_ring_buffer`

   `sudo rmmod ring_buffer_module`

### Author

- [MD ARIF KHAN](https://github.com/arifthehappy)(arifthehappy@gmail.com)
