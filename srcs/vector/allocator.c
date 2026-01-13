#include "libft/libft.h"

void*	ft_allocator_allocate(const ft_allocator* alloc, size_t n)
{
	void* ptr = malloc(n * alloc->sizeof_type);
	LIBFT_ASSERT(ptr != NULL && "Allocation failed");
	return ptr;
}

void	ft_allocator_deallocate(const ft_allocator* alloc, void *p, size_t n)
{
	(void)alloc;
	(void)n;
	free(p);
}

void	ft_allocator_construct(const ft_allocator* alloc, void *p, const void* value)
{
	ft_memcpy(p, value, alloc->sizeof_type);
}

void	ft_allocator_destroy(const ft_allocator* alloc, void *p)
{
	(void)alloc;
	(void)p;
}

size_t	ft_allocator_max_size(const struct ft_allocator* alloc)
{
	return SIZE_MAX / alloc->sizeof_type;
}
