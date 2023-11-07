
# XV6-RISC-V Project

This project involves cross-compiling XV6 for RISC-V on an x86 system. Follow the instructions below to set up and run XV6 on QEMU.

## Prerequisites

- Git
- RISC-V Cross-Compiler
- QEMU

## Clone Repositories

1. Clone the XV6-Riscv repository:
   `git clone https://github.com/mit-pdos/xv6-riscv`

2. Clone the RISC-V GNU toolchain repository:
   `git clone https://github.com/riscv/riscv-gnu-toolchain`

## Cross-Compiler Installation
   
1. Navigate to the riscv-gnu-toolchain directory:
	`cd riscv-gnu-toolchain`

2. Create the installation directory:
	`sudo mkdir -p /opt/riscv`
	`export PATH=$PATH:/opt/riscv/bin`

3. Configure and make the toolchain:
	`./configure --prefix=/opt/riscv`
	`make`
	
## Build XV6 for RISC-V

1. Navigate to the XV6-Riscv directory:
	`cd ../xv6-riscv`

2. Edit the Makefile to set the cross-compiler:

	`nano Makefile`
	Set TOOLPREFIX to the correct RISC-V cross-compiler prefix.
	 ` TOOLPREFIX = /opt/riscv/bin/[risv-unknown-elf-]`

## Build XV6:

	`make`

## Run XV6 on QEMU

1. Install QEMU for RISC-V:

	`sudo apt-get install qemu-system-misc`
	
2. Run XV6 on QEMU:

	`make qemu`

## Exiting XV6
	To exit XV6 and return to the shell:
	Press Ctrl + a (release) + x to pause QEMU.
	In the terminal where QEMU was started, press Ctrl + c to stop QEMU.

Notes
This project is based on XV6-RISC-V and the RISC-V GNU toolchain.
arifthehappy@gmail.com




