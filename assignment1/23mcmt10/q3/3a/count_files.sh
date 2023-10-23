#! /bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 path_directory"
    exit 1
fi

path_directory="$1"

if [ ! -d "$path_directory" ]; then
    echo "Directory $path_directory not found."
    exit 1
fi


count=$(ls "$path_directory" | grep 'A*.txt' | wc -l)

echo "Number of txt files starting with A in $path_directory : $count"
