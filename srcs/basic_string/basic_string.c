#include "libft.h"

typedef struct _ft_string
{
	size_t	capacity;
	char*	data;
}_ft_string;

static size_t	_ft_string_recommend(size_t capacity, size_t new_size)
{
	LIBFT_ASSERT(new_size < SIZE_MAX);
    if (capacity >= SIZE_MAX / 2)
        return SIZE_MAX;
    return max(2 * capacity, new_size);
}

LIBFT_BOOL	ft_string_equals(const ft_string a, const ft_string b)
{
	return ft_strcmp(a->data, b->data) == 0;
}

LIBFT_BOOL	ft_string_equals_str(const ft_string s, const char *_x)
{
	return ft_strcmp(s->data, _x) == 0;
}

ft_string	_ft_string_alloc_impl(void)
{
	return LIBFT_MALLOC(sizeof(struct _ft_string));
}

_ft_string	*ft_string_create(void)
{
	ft_string	string;
	
	string = _ft_string_alloc_impl();
	LIBFT_ASSERT(string);
	string->capacity = LIBFT_STRING_DEFAULT_CAPACITY;
	string->data = LIBFT_MALLOC(string->capacity * sizeof(*string->data));
	LIBFT_ASSERT(string->data);
	string->data[0] = '\0';
	return string;
}

_ft_string	*ft_string_create_from_str(const char *_x)
{
	ft_string string;
	
	string = _ft_string_alloc_impl();
	LIBFT_ASSERT(string);
	string->capacity = 0;
	string->data = NULL;
	ft_string_assign(string, _x);
	return string;
}

_ft_string	*ft_string_create_from_str_count(const char *_x, size_t count)
{
	ft_string string;
	
	string = _ft_string_alloc_impl();
	string->capacity = 0;
	string->data = NULL;
	ft_string_assign_count(string, _x, count);
	return string;
}

_ft_string	*ft_string_create_from_char(const char _x, size_t count)
{
	ft_string string;
	
	string = _ft_string_alloc_impl();
	string->capacity = 0;
	string->data = NULL;
	ft_string_assign_char(string, _x, count);
	return string;
}

_ft_string	*ft_string_create_from_ft_string(const ft_string x)
{
	ft_string	string, _x;
	
	string = _ft_string_alloc_impl();
	string->capacity = 0;
	string->data = NULL;
	_x = (ft_string )x;
	if (_x->data)
		ft_string_assign(string, _x->data);
	return string;
}

void	ft_string_destroy(ft_string s)
{
	if (!s)
		return ;
	if (s->data)
	{
		LIBFT_FREE(s->data);
		s->capacity = 0;
	}
	LIBFT_FREE(s);
}

const char	*ft_string_data(const ft_string s)
{
	return s->data;
}

size_t	ft_string_size(const ft_string s)
{
	if (!s->data)
		return 0;
	return ft_strlen(s->data);
}

size_t	ft_string_length(const ft_string s)
{
	return ft_strlen(s->data);
}

char	ft_string_at(const ft_string s, size_t pos)
{
	LIBFT_ASSERT(pos < s->capacity);
	return s->data[pos];
}

LIBFT_BOOL	ft_string_empty(const ft_string s)
{
	return s->capacity == 0 || s->data[0] == '\0';
}

size_t	ft_string_max_size(void)
{
	return (SIZE_MAX);
}

void	ft_string_reserve(_ft_string *s, size_t new_cap)
{
	if (s->capacity < new_cap)
	{
		char *new_data = ft_calloc(new_cap, sizeof(char));
		LIBFT_ASSERT(new_data);
		s->capacity = new_cap;

		ft_strcpy(new_data, s->data);

		if (s->data)
			LIBFT_FREE(s->data);
		s->data = new_data;
	}
}

size_t	ft_string_capacity(const ft_string s)
{
	return s->capacity;
}

void	ft_string_shrink_to_fit(_ft_string *s)
{
	size_t	len = ft_strlen(s->data) + 1;

	if (s->capacity > len)
	{
		char *new_data = malloc(sizeof(char) * len);
		LIBFT_ASSERT(new_data);
		ft_memcpy(new_data, s->data, len);
		if (s->data)
			LIBFT_FREE(s->data);
		s->data = new_data;
		s->capacity = len;
	}
}

void	_ft_string_print_debug(const ft_string s, const char *_info, const char *param, size_t param_size)
{
	int	_cap;

	if (!s)
		return ;
	_cap = s->capacity;
	ft_printf("--- FT_STRING");
	if (_info)
	{
		ft_printf(" %s", _info);
		if (param)
		{
			ft_putstr(" '");
			for (size_t i = 0; i < param_size; i++)
			{
				if (param[i] == '\0')
					ft_putstr("\\0");
				else if (param[i] == '\n')
					ft_putstr("\\n");
				else if (param[i] == '\t')
					ft_putstr("\\t");
				else if (ft_isascii(param[i]))
					ft_putchar(param[i]);
				else
					ft_putchar('.');
			}
			ft_putchar('\'');
		}
	}
	ft_printf(" ---\n");
	ft_printf("DATA START\n%s\nDATA END\n", s->data);
	ft_printf("-----\n");
	ft_printf("CAP : %d\n", _cap);

	ft_printf("MEM : |");
	for (int i = 0; i <= _cap; i++)
	{
		if (s->data[i] == '\0')
			ft_printf("\\0|");
		else if (s->data[i] == '\n')
			ft_printf("\\n|");
		else if (s->data[i] == '\t')
			ft_printf("\\t|");
		else if (ft_isascii(s->data[i]))
			ft_printf("%2c|", s->data[i]);
		else
			ft_printf("%2c|", '.');
	}
	ft_printf("\n");
	ft_printf("      |");
	for (int i = 0; i <= _cap; i++)
		ft_printf("%2d|", i);
	ft_printf("\n");
	ft_printf("--- END ---\n");
}

void	ft_string_append_str(_ft_string *s, const char *_x)
{
	size_t _size, _newsize;
	size_t len = ft_strlen(_x);

	_size = ft_strlen(s->data);
	_newsize = _size + len + 1;
	if (s->capacity < _newsize)
	{
		size_t _newcap = _ft_string_recommend(s->capacity, _newsize);
		char *new_data = ft_calloc(_newcap, sizeof(char));
		LIBFT_ASSERT(new_data);
		s->capacity = _newcap;

		if (s->data)
		{
			ft_strcat(new_data, s->data);
			LIBFT_FREE(s->data);
		}
		ft_strcat(new_data, _x);
		s->data = new_data;
	}
	else
	{
		ft_strcat(s->data, _x);
	}
	// _ft_string_print_debug(s, "append_string()", _x, ft_strlen(_x));
}

void	ft_string_append_char(ft_string s, const char _x, size_t n)
{
	size_t _size, _newsize;

	_size = ft_strlen(s->data);
	_newsize = _size + n + 1;
	if (s->capacity < _newsize)
	{
		size_t _newcap = _ft_string_recommend(s->capacity, _newsize);
		char *new_data = ft_calloc(_newcap, sizeof(char));
		LIBFT_ASSERT(new_data);
		s->capacity = _newcap;

		if (s->data)
		{
			ft_strcpy(new_data, s->data);
			LIBFT_FREE(s->data);
		}
		ft_memset(new_data + _size, _x, n);
		s->data = new_data;
	}
	else
	{
		ft_memset(s->data + _size, _x, n);
	}
	// _ft_string_print_debug(s, "append_char()", &_x, 1);
}

void		ft_string_append_ft_string(ft_string s, const ft_string x)
{
	if (x->capacity && x->data)
		ft_string_append_str(s, x->data);
}

void	ft_string_assign(ft_string s, const char *_x)
{
	size_t _xsize;

	_xsize = ft_strlen(_x) + 1;
	if (s->capacity < _xsize)
	{
		char *new_data = ft_strdup(_x);
		LIBFT_ASSERT(new_data);
		LIBFT_ASSERT(new_data);
		s->capacity = _xsize;

		if (s->data)
			LIBFT_FREE(s->data);
		s->data = new_data;
	}
	else
	{
		ft_strcpy(s->data, _x);
		ft_memset(s->data + _xsize, '\0', s->capacity - _xsize);
	}
}

void	ft_string_assign_count(ft_string s, const char *_x, size_t count)
{
	size_t _xsize;

	_xsize = ft_strnlen(_x, count) + 1;
	if (s->capacity < _xsize)
	{
		char *new_data = ft_strndup(_x, count);
		LIBFT_ASSERT(new_data);
		s->capacity = _xsize;

		if (s->data)
			LIBFT_FREE(s->data);
		s->data = new_data;
	}
	else
	{
		ft_strcpy(s->data, _x);
		ft_memset(s->data + _xsize, '\0', s->capacity - _xsize);
	}
}

void	ft_string_assign_char(ft_string s, const char _x, size_t count)
{
	size_t	_newcap;

	_newcap = count + 1;
	if (s->capacity < count)
	{
		char *new_data = ft_calloc(_newcap, sizeof(char));
		LIBFT_ASSERT(new_data);
		s->capacity = _newcap;

		ft_memset(new_data, _x, count);
		ft_memset(new_data + count, '\0', s->capacity - count);

		if (s->data)
			LIBFT_FREE(s->data);
		s->data = new_data;
	}
	else
	{
		ft_memset(s->data, _x, count);
		ft_memset(s->data + count, '\0', s->capacity - count);
	}
}

void	ft_string_clear(_ft_string *s)
{
	if (s->data)
		ft_bzero(s->data, s->capacity);
}
