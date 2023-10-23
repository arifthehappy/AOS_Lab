#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 input_file"
    exit 1
fi

input_file="$1"
output_file="output.txt"

# Clear the output file
> "$output_file"

# Check if the input file exists
if [ ! -e "$input_file" ]; then
    echo "Input file $input_file not found."
    exit 1
fi

# Process each line in the input file
while read -r input_number base_input base_conversion; do
    # Check if the line has exactly 3 columns
    if [ -z "$input_number" ] || [ -z "$base_input" ] || [ -z "$base_conversion" ]; then
        echo "Invalid input line: $input_number $base_input $base_conversion"
        continue
    fi

    echo "Processing line: $input_number $base_input $base_conversion"
    
    # Convert the input number from base_input to base_conversion
    converted_number=$(echo "obase=$base_conversion; ibase=$base_input; $input_number" | bc)

    # Write the converted number to the output file
    echo "$converted_number" >> "$output_file"
    
    # Print the converted number
    echo "$converted_number"
done < "$input_file"

echo "Conversion completed. Results are stored in $output_file."
