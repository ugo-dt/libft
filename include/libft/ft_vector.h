#include "libft.h"

#ifdef LIBFT_VECTOR_TYPE
# ifndef ft_vector_type_name
#  define ft_vector_type_name LIBFT_VECTOR_TYPE
# endif
#else
# error "Please define LIBFT_VECTOR_TYPE"
#endif

#define ft_vector_value_type		LIBFT_VECTOR_TYPE *
#define ft_vector_const_value_type	const LIBFT_VECTOR_TYPE *
#define ft_vector_pointer			LIBFT_VECTOR_TYPE *
#define ft_vector_const_pointer		const LIBFT_VECTOR_TYPE *

#include "internal/vector_impl.inl"

#undef LIBFT_VECTOR_TYPE
#undef ft_vector_type_name
#undef ft_vector_value_type
#undef ft_vector_const_value_type
#undef ft_vector_pointer
#undef ft_vector_const_pointer

#ifndef FT_VECTOR_H
#define FT_VECTOR_H

typedef struct ft_allocator ft_allocator;

struct ft_allocator
{
	void*	(*allocate)(size_t n);
	void	(*deallocate)(void* p, size_t n);
	void	(*construct)(void* p, const void *value_ptr);
	void	(*destroy)(void* p);
};

typedef struct ft_vector ft_vector;

struct ft_vector
{
	ft_allocator	alloc;
	void*			_begin;
	void*			_end;
	void*			_end_cap;

#ifndef FT_VECTOR_NO_FUNCTION_POINTERS
	// ft_vector* (*create)(void);
	ft_vector*	(*copy)(ft_vector *vector, const ft_vector *_src);
	void*		(*data)(ft_vector *vector);
	void*		(*at)(ft_vector *vector, size_t n);
	LIBFT_BOOL	(*empty)(const ft_vector *vector);
	size_t		(*size)(const ft_vector *vector);
	size_t		(*capacity)(const ft_vector *vector);
	void		(*reserve)(ft_vector *vector, size_t n);
	void		(*resize)(ft_vector *vector, size_t n, const void* value_ptr);
	void		(*assign)(ft_vector *vector, size_t n, const void* value_ptr);
	void		(*assign_range)(ft_vector *vector, void * first, void * last);
	void		(*push_back)(ft_vector *vector, const void* value_ptr);
	void*		(*insert)(ft_vector *vector, size_t position, const void* value_ptr);
	void		(*insert_count)(ft_vector *vector, size_t position, size_t n, const void* value_ptr);
	void		(*insert_range)(ft_vector *vector, size_t position, void * first, void * last);
	void		(*clear)(ft_vector *vector);
	void		(*destroy)(ft_vector *vector);
	void		(*pop_back)(ft_vector *vector);
	void*		(*erase)(ft_vector *vector, size_t position);
	void*		(*erase_range)(ft_vector *vector, void * first, void * last);
	void		(*swap)(void * *a, void * *b);
	void*		(*begin)(const ft_vector *vector);
	void*		(*end)(const ft_vector *vector);
#endif
};

#endif // FT_VECTOR_H
