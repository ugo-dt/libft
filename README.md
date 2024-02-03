# Libft
## Introduction
This library is an extended version of the Libft project at 42 School.
This is a basic recreation of some of the most used functions in the C library, aimed to be re-used in later projects.
It also includes it's own version of printf, along with other useful functions.

## Building Libft
Libft is a C static library and only requires the standard C library headers.
Build it with the ```make``` command
```
git clone https://github.com/ugo-dt/libft.git
cd libft
make
```

## Using Libft
Include the libft header in your project,
then link the library.
```C
/* main.c - example file */
#include <libft.h>

int main(void)
{
	ft_putendl("Hello, world!");
	return (0);
}
```
```
clang -I libft/include main.c libft/libft.a
```
