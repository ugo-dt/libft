# Libft
## This library is an extended version of the Libft project at 42 School.
#### Create libft.a with the `make` command.

##### Usage example
```C
/* main.c - example file */
#include "libft.h"

int main(void)
{
  ft_putstr("Hello World!\n", 1);
  return (0);
}
```
`make -C libft && clang -I libft/srcs/ main.c libft/libft.a`
