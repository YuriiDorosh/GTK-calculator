#!/bin/bash

# Install the requirements
sudo apt update
sudo apt install -y gcc
sudo apt install -y pkg-config
sudo apt-get install -y libgtk-3-dev

# Compile the project
gcc calculator.c -o calc `pkg-config --cflags --libs gtk+-3.0` -lm

# Run the project
./calc
