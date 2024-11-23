#include "libft.h"

void	*_ft_allocator_allocate(size_t n, size_t type_size)
{
	return LIBFT_MALLOC(n * type_size);
}

void	_ft_allocator_deallocate(void *p, size_t n)
{
	(void)n;
	LIBFT_FREE(p);
}

void	_ft_allocator_construct(void *p, const void *value, size_t type_size)
{
	ft_memcpy(p, value, type_size);
}

void	_ft_allocator_destroy(void *p)
{
	(void)p;
}
