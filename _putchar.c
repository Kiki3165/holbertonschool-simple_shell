#include "main.h"

/**
 * _putchar - function to print character
 * @c: character
 * Return: &c
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}
