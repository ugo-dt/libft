#include "libft.h"

pointer	_ft_allocator_allocate(size_t n, size_t type_size)
{
	return LIBFT_MALLOC(n * type_size);
}

void	_ft_allocator_deallocate(pointer p, size_t n)
{
	(void)n;
	LIBFT_FREE(p);
}

void	_ft_allocator_construct(pointer p, const_value_type value, size_t type_size)
{
	ft_memcpy(p, value, type_size);
}

void	_ft_allocator_destroy(pointer p)
{
	(void)p;
}
