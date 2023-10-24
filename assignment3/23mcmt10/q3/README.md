# Instantiating XV6 using WSL

Follow these steps to install windows subsystem for linux (WSL) and XV6

1. *Run PowerShell as administrator*

2.  ```wsl --install -d Ubuntu
   ```

3.  ```sudo apt-get update -y ```

4.  ```sudo apt-get install git mae gcc wget qemu qemu-kvm gdb -y ```

5.  ```git clone https://github.com/mit-pdos/xv6-public.git ```

## Build and run xv6

   ```cd xv6-public && make qemu-nox ```
