#ifndef DOS_H
#define DOS_H

#include <stdint.h>

/**
 * dos_read_keyboard_without_echo() - Reads a key press without showing it.
 *
 * Pauses the program and waits for a key to be pressed. While paused the
 * program can be quit by doing control c.
 *
 * Return: The ASCII value of the key pressed.
 */
uint8_t dos_read_keyboard_without_echo();

/**
 * dos_display_string() - Prints a string to the screen.
 * @param string A string that is terminated by '$'
 *
 * If there is no '$' in the string DOS will continuing reading past the
 * string. It is not possible to print a '$' using this function.
 */
void dos_display_string(char* string);

#endif
