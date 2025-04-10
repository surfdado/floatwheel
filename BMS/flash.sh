#!/bin/sh

# Get the firmware file from the command line
firmware_file=$1

# Check that the firmware file was provided
if [ -z "$firmware_file" ]; then
    echo "Usage: ./flash.sh <firmware hex file>"
    exit 1
fi

# Check that the firmware file exists
if [ ! -f "$firmware_file" ]; then
    echo "File not found: $firmware_file"
    exit 1
fi

# Get the extension of the firmware file
extension=$(basename -- "$firmware_file")
extension="${extension##*.}"

# Verify that the firmware file is a .hex
if [ "$extension" != "hex" ]; then
    echo "File is not a .hex file"
    exit 1
fi

# Check that the pyocd command is installed
if [ ! -x "$(command -v pyocd)" ]; then
    echo "pyocd is not installed or was not found in your PATH"
    echo "Install it with: python -m pip install --upgrade pyocd==0.34.3"
    echo "If you have installed pyocd and it cannot be found, please add it to your PATH"
    exit 1
fi

# Check that NSING.N32L40x_DFP.1.0.1.pack exists
if [ ! -f "./NSING.N32L40x_DFP.1.0.1.pack" ]; then
    echo "NSING.N32L40x_DFP.1.0.1.pack not found"
    echo "Download it from https://github.com/surfdado/floatwheel"
    exit 1
fi

# Delimiter to separate the output
delimiter="========"

# Erase and flash the firmware
echo "Erasing the old firmware..."
echo "$delimiter"
pyocd erase -c -t N32L403K8 --pack NSING.N32L40x_DFP.1.0.1.pack

echo "$delimiter"
echo "Flashing the new firmware..."
echo "$delimiter"
pyocd load "$firmware_file" -t N32L403K8 --pack NSING.N32L40x_DFP.1.0.1.pack

echo "$delimiter"
echo "Please check the flashing messages to make sure the flash was successful."
echo "Float on!"
echo "$delimiter"
