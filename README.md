# Libft
## This library is an extended version of the Libft project at 42 School.
#### Create libft.a with the `make` command.

##### Usage example
```C
/* main.c - example file */
#include "libft.h"

int main(void)
{
	ft_putstr("Hello World!\n");
	return (0);
}
```
```bash
foo$> ls -o
total 8
drwxr-xr-x  9 bar  288 Feb  6 01:23 libft
-rw-r--r--  1 bar  112 Feb  6 12:34 main.c
foo$> make -C libft && clang -I libft/include main.c libft/libft.a
Compiling libft.a...
libft.a ready!
foo$> ./a.out
Hello World!
foo$>
```
