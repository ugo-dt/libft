#define LIBFT_IMPL
#include "single_header/libft.h"

int	main(void)
{
	ft_printf("Hello World!\n");

	ft_vector	v = ft_vector_create(&(ft_vector_desc){
		.alloc = (ft_allocator){
			.sizeof_type = sizeof(int),
		},
	});
	ft_vector_reserve(&v, 10);
	for (int i = 0; i < 10; i++)
		ft_vector_push_back(&v, &i);
	
	for (ft_iterator it = ft_vector_begin(&v); FT_ITER_NEQ(it, ft_vector_end(&v)); FT_ITER_INC(it))
		ft_printf("%d\n", FT_ITER_VALUE(it, int));
	return (0);
}
