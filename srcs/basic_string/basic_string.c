#include "libft.h"

#define LIBFT_STRING_DEFAULT_CAPACITY	15

struct ft_string
{
	char	*_data;
	size_t	_size;
	size_t	_capacity;
};

static size_t	_ft_string_recommend(size_t capacity, size_t new_size)
{
	// https://stackoverflow.com/a/51239423
	const size_t max_size = 2305843009213693951;
	LIBFT_ASSERT(new_size < max_size);

    const size_t cap = capacity;
    if (cap >= max_size / 2)
        return max_size;
    return max(2 * cap, new_size);
}

LIBFT_BOOL	ft_string_equals(const struct ft_string *s, const char *_x)
{
	return (ft_strcmp(s->_data, _x) == 0);
}

struct ft_string	*ft_string_create(void)
{
	struct ft_string	*s;

	s = ft_calloc(1, sizeof(struct ft_string));
	if (!s)
		return (NULL);

	s->_size = 0;
	s->_capacity = LIBFT_STRING_DEFAULT_CAPACITY;
	s->_data = ft_calloc(s->_size, sizeof(char));
	if (!s->_data)
	{
		LIBFT_FREE(s);
		return (NULL);
	}
	return s;
}

struct ft_string	*ft_string_create_from_string(const char *_x)
{
	struct ft_string	*s;

	s = ft_calloc(1, sizeof(struct ft_string));
	if (!s)
		return (NULL);
	
	s->_capacity = 0;
	ft_string_assign(s, _x);
	return s;
}

struct ft_string	*ft_string_create_from_char(const char _x, size_t count)
{
	struct ft_string	*s;

	s = ft_calloc(1, sizeof(struct ft_string));
	if (!s)
		return (NULL);

	s->_capacity = 0;
	ft_string_assign_char(s, _x, count);
	return s;
}

void	ft_string_destroy(struct ft_string *s)
{
	if (!s)
		return ;
	if (s->_data)
		LIBFT_FREE(s->_data);
	LIBFT_FREE(s);
}

const char	*ft_string_data(const struct ft_string *s)
{
	return s->_data;
}

size_t	ft_string_size(const struct ft_string *s)
{
	return s->_size;
}

size_t	ft_string_length(const struct ft_string *s)
{
	return s->_size;
}

char	ft_string_at(const struct ft_string *s, size_t pos)
{
	LIBFT_ASSERT(pos < s->_size);
	return s->_data[pos];
}

LIBFT_BOOL	ft_string_empty(const struct ft_string *s)
{
	return s->_size == 0;
}

bool	ft_string_reserve(struct ft_string *s, size_t new_cap)
{
	if (s->_capacity < new_cap)
	{
		char *new_data = ft_calloc(new_cap, sizeof(char));
		if (!new_data)
			return (LIBFT_FALSE);
		s->_capacity = new_cap;

		ft_strcpy(new_data, s->_data);

		if (s->_data)
			LIBFT_FREE(s->_data);
		s->_data = new_data;
	}
	return (LIBFT_TRUE);
}

size_t	ft_string_capacity(const struct ft_string *s)
{
	return s->_capacity;
}

LIBFT_BOOL ft_string_shrink_to_fit(struct ft_string *s)
{
	if (s->_capacity > s->_size)
	{
		char *new_data = ft_strdup(s->_data);
		if (!new_data)
			return (LIBFT_FALSE);
		if (s->_data)
			LIBFT_FREE(s->_data);
		s->_data = new_data;
		s->_capacity = s->_size;
	}
	return (LIBFT_TRUE);
}

void	_ft_string_print_debug(const struct ft_string *s, const char *_info, const char *param, size_t param_size)
{
	int	_size, _cap;

	if (!s)
		return ;
	_size = s->_size;
	_cap = s->_capacity;
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
	ft_printf("DATA START\n%s\nDATA END\n", s->_data);
	ft_printf("-----\n");
	ft_printf("SIZE: %d\n", _size);
	ft_printf("CAP : %d\n", _cap);

	ft_printf("MEM : |");
	for (int i = 0; i <= _cap; i++)
	{
		if (s->_data[i] == '\0')
			ft_printf("\\0|");
		else if (s->_data[i] == '\n')
			ft_printf("\\n|");
		else if (s->_data[i] == '\t')
			ft_printf("\\t|");
		else if (ft_isascii(s->_data[i]))
			ft_printf("%2c|", s->_data[i]);
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

LIBFT_BOOL	ft_string_append_string(struct ft_string *s, const char *_x)
{
	size_t _newsize;

	_newsize = s->_size + ft_strlen(_x);
	if (s->_capacity < _newsize)
	{
		char *new_data = ft_calloc(_ft_string_recommend(s->_capacity, _newsize), sizeof(char));
		if (!new_data)
			return (LIBFT_FALSE);
		s->_capacity = _newsize;

		ft_strcat(new_data, s->_data);
		ft_strcat(new_data, _x);
		if (s->_data)
			LIBFT_FREE(s->_data);
		s->_data = new_data;
	}
	else
	{
		ft_strcat(s->_data, _x);
	}
	s->_size = _newsize;
	// _ft_string_print_debug(s, "append_string()", _x, ft_strlen(_x));
	return (LIBFT_TRUE);
}

LIBFT_BOOL	ft_string_append_char(struct ft_string *s, const char _x, size_t n)
{
	size_t	_newsize;

	ft_printf("1\n");
	_newsize = s->_size + n;
	if (s->_capacity < _newsize)
	{
		char *new_data = ft_calloc(_ft_string_recommend(s->_capacity, _newsize), sizeof(char));
		if (!new_data)
			return (LIBFT_FALSE);
		s->_capacity = _newsize;

		ft_strcpy(new_data, s->_data);
		ft_memset(new_data + s->_size, _x, n);
		new_data[_newsize] = '\0';

		if (s->_data)
			LIBFT_FREE(s->_data);
		s->_data = new_data;
	}
	else
	{
		ft_memset(s->_data + s->_size, _x, n);
	}
	s->_size = _newsize;
	// _ft_string_print_debug(s, "append_char()", &_x, 1);
	return (LIBFT_TRUE);
}

LIBFT_BOOL	ft_string_assign(struct ft_string *s, const char *_x)
{
	size_t _xsize;

	_xsize = ft_strlen(_x);
	if (s->_capacity < _xsize)
	{
		char *new_data = ft_strdup(_x);
		if (!new_data)
			return (LIBFT_FALSE);
		s->_capacity = _xsize;

		if (s->_data)
			LIBFT_FREE(s->_data);
		s->_data = new_data;
	}
	else
	{
		ft_strcpy(s->_data, _x);
		ft_memset(s->_data + _xsize, '\0', s->_capacity - _xsize);
	}
	s->_size = _xsize;
	return (LIBFT_TRUE);
}

LIBFT_BOOL	ft_string_assign_char(struct ft_string *s, const char _x, size_t count)
{
	size_t	_newsize;

	_newsize = count + 1;
	if (s->_capacity < count)
	{
		char *new_data = ft_calloc(_newsize, sizeof(char));
		if (!new_data)
			return (LIBFT_FALSE);
		s->_capacity = _newsize;

		ft_memset(new_data, _x, count);
		ft_memset(new_data + count, '\0', s->_capacity - count);

		if (s->_data)
			LIBFT_FREE(s->_data);
		s->_data = new_data;
	}
	else
	{
		ft_memset(s->_data, _x, count);
		ft_memset(s->_data + count, '\0', s->_capacity - count);
	}
	s->_size = _newsize;
	return (LIBFT_TRUE);
}

void	ft_string_clear(struct ft_string *s)
{
	ft_bzero(s->_data, s->_size);
	s->_size = 0;
}
