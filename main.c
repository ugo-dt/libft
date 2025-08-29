#include <libft/libft.h>
#include <libft/internal/iterator.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	ft_vector v = ft_vector_create(&(ft_vector_desc){
		.alloc.sizeof_type = sizeof(int),
	});

	ft_vector_reserve(&v, 10);
	ft_printf("capacity: %ld\n", ft_vector_capacity(&v));

	ft_vector_push_back(&v, &(int){42});
	ft_vector_push_back(&v, &(int){22});
	ft_vector_push_back(&v, &(int){535});
	ft_vector_push_back(&v, &(int){635});

	for (ft_iterator it = ft_vector_begin(&v); !FT_ITER_EQ(it, ft_vector_end(&v)); FT_ITER_INC(it))
	{
		ft_printf("%d\n", *(int*)FT_ITER_VALUE(it));
	}

	for (ft_iterator rit = ft_vector_rbegin(&v); !FT_ITER_EQ(rit, ft_vector_rend(&v)); FT_ITER_INC(rit))
	{
		ft_printf("%d\n", *(int*)FT_ITER_VALUE(rit));
	}

	ft_vector_clear(&v);
	ft_printf("after clear, size: %ld\n", ft_vector_size(&v));
	ft_printf("after clear, capacity: %ld\n", ft_vector_capacity(&v));

	for (ft_iterator it = ft_vector_begin(&v); !FT_ITER_EQ(it, ft_vector_end(&v)); FT_ITER_INC(it))
	{
		ft_printf("%d\n", *(int*)FT_ITER_VALUE(it));
	}

	ft_vector_destroy(&v);
	return (0);
}
