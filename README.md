# gyro-pc98

This is my personal collection of PC98 related code I have written.

## Samples

**Rect**: This is my interpretation of the sample code from PC9800 Series Technical Data Book BIOS for using the Graphics BIOS to draw a rectangle.

## Building

**Requirements**: This project assumes you have a modern version of clang and GNU ld installed.
**Building**: The repository can be built using `make`.
**Development**: To make iterating faster you can create a config.mk file that sets the MOUNT variable to where a floppy drive is mounted on your machine and then use `make install` to build and copy `rect.com` to the floppy drive.
