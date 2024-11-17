#include "libft.h"
#include <stdio.h>

#define TYPE	int

void	vec_debug(ft_vector *v)
{
	printf("---- VECTOR ---\n");
	printf("SIZE: %zu\n", ft_vector_size(v));
	printf("CAP : %zu\n", ft_vector_capacity(v));
	printf("BEGIN : %p\n", v->_begin);
	printf("END   : %p\n", v->_end);
	printf("ENDCAP: %p\n", v->_end_cap);

	// for (int *i = v->_begin; i != v->_end; _ft_pointer_inc(i, sizeof(int)))
	// 	printf("%c\n", *i);
	for (iterator(it, TYPE) = v->_begin; it != v->_end; iterator_inc(it, v))
		printf("%d\n", *it);
	
	printf("----\n");
}

struct test
{
	int a, b;
};

int	main(void)
{
	TYPE	array[5] = {0, 2, 4, 6, 8};
	TYPE	array2[5] = {10, 12, 14, 16, 18};
	ft_vector(v, TYPE);

	// ft_vector_reserve(&v, 30);

	ft_vector_assign_range(&v, array, array + 5);
	vec_debug(&v);
	
	ft_vector_insert(&v, 1, value_type(TYPE, 1));
	ft_vector_insert(&v, 3, value_type(TYPE, 3));
	ft_vector_insert(&v, 5, value_type(TYPE, 5));
	ft_vector_insert(&v, 7, value_type(TYPE, 7));
	vec_debug(&v);

	ft_vector_assign(&v, 3, value_type(TYPE, 3));
	vec_debug(&v);
	ft_vector_resize(&v, 10, value_type(TYPE, 0));
	vec_debug(&v);
	ft_vector_resize(&v, 1, value_type(TYPE, 0));
	vec_debug(&v);
	ft_vector_resize(&v, 0, value_type(TYPE, 0));
	vec_debug(&v);

	for (TYPE i = 0; i < 5; i++)
		ft_vector_push_back(&v, value_type(TYPE, i));
	vec_debug(&v);

	ft_vector_insert(&v, 3, value_type(TYPE, 3));
	vec_debug(&v);
	ft_vector_insert_count(&v, 3, 3, value_type(TYPE, -3));
	vec_debug(&v);
	ft_vector_insert_range(&v, 0, array2, array2 + 5);
	vec_debug(&v);

	ft_vector_destroy(&v);
	return (0);
}
