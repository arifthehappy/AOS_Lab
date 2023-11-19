# Hello World Kernel Module

This is a simple Loadable Kernel Module (LKM) that prints "Hello World" in the kernel ring buffer.

## Prerequisites

Before building and loading the module, ensure that you have the necessary kernel headers installed.

`sudo apt-get install linux-headers-$(uname -r)`

## Building the Module

To build the module, use the provided Makefile.

`make`

## Loading the Module

Load the module into the kernel using the following command:

`sudo insmod hello_world.ko`

### Check the kernel ring buffer for the "Hello World" message:

`dmesg`

## Unloading the Module

Unload the module from the kernel with:

`sudo rmmod hello_world`

### Check the kernel ring buffer again for the "Goodbye World" message:

`dmesg`
