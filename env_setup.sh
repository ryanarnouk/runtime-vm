#!/bin/bash

EXECUTABLE_DIR="$(pwd)/bin"
EXECUTABLE_NAME="runtime"
LANG_NAME="rvm"

if [ ! -f "$EXECUTABLE_DIR/$EXECUTABLE_NAME" ]; then
    echo "Error: Executable $EXECUTABLE_NAME not found in $EXECUTABLE_DIR"
    exit 1
fi

# Create symbolic link in /usr/local/bin to set to LANG_NAME command
sudo ln -sf "$EXECUTABLE_DIR/$EXECUTABLE_NAME" /usr/local/bin/$LANG_NAME

echo "The 'rvm' command is setup and points to $EXECUTABLE_DIR/$EXECUTABLE_NAME."
