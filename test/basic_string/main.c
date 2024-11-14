#include <stdlib.h>
#include <stdio.h>

static int allocations;

static void *our_alloc(size_t size)
{
	allocations++;
	return malloc(size);
}

#define LIBFT_IMPL
#define LIBFT_MALLOC our_alloc
#define LIBFT_FREE free
#include "libft.h"

int	main(void)
{
	struct ft_string	*s;

	allocations = 0;
	s = ft_string_create_from_string("Hello");
	printf("|%s|\n", ft_string_data(s));
	printf("size: %zu\ncap: %zu\n", ft_string_size(s), ft_string_capacity(s));

	ft_string_assign(s, "Hello");
	printf("|%s|\n", ft_string_data(s));
	printf("size: %zu\ncap: %zu\n", ft_string_size(s), ft_string_capacity(s));

	ft_string_add_string(s, ", world!");
	printf("|%s|\n", ft_string_data(s));
	printf("size: %zu\ncap: %zu\n", ft_string_size(s), ft_string_capacity(s));
	
	ft_string_add_char(s, ' ', 1);
	printf("|%s|\n", ft_string_data(s));
	printf("size: %zu\ncap: %zu\n", ft_string_size(s), ft_string_capacity(s));
	
	ft_string_add_char(s, 'e', 5);
	printf("|%s|\n", ft_string_data(s));
	printf("size: %zu\ncap: %zu\n", ft_string_size(s), ft_string_capacity(s));
	
	ft_string_assign(s, "The text");
	printf("|%s|\n", ft_string_data(s));
	printf("size: %zu\ncap: %zu\n", ft_string_size(s), ft_string_capacity(s));

	ft_string_add_char(s, 'a', 2);
	printf("|%s|\n", ft_string_data(s));
	printf("size: %zu\ncap: %zu\n", ft_string_size(s), ft_string_capacity(s));

	// ft_string_shrink_to_fit(s);
	printf("|%s|\n", ft_string_data(s));
	printf("size: %zu\ncap: %zu\n", ft_string_size(s), ft_string_capacity(s));
	
	ft_string_reserve(s, 100);
	printf("|%s|\n", ft_string_data(s));
	printf("size: %zu\ncap: %zu\n", ft_string_size(s), ft_string_capacity(s));
	
	ft_string_add_string(s, " --- an other string");
	printf("|%s|\n", ft_string_data(s));
	printf("size: %zu\ncap: %zu\n", ft_string_size(s), ft_string_capacity(s));

	ft_string_assign(s, "Helooooooooooooooooooooooo");
	printf("|%s|\n", ft_string_data(s));
	printf("size: %zu\ncap: %zu\n", ft_string_size(s), ft_string_capacity(s));

	printf("Allocations: %d\n", allocations);
	return (0);
}
