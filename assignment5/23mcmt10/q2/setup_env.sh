#!/bin/bash

# Install necessary packages for kernel module development
sudo apt-get update
sudo apt-get install -y build-essential linux-headers-$(uname -r)
