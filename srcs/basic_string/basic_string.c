#include "libft.h"

#define LIBFT_STRING_DEFAULT_CAPACITY	15

static size_t	_ft_string_recommend(size_t capacity, size_t new_size)
{
	LIBFT_ASSERT(new_size < SIZE_MAX);
    if (capacity >= SIZE_MAX / 2)
        return SIZE_MAX;
    return (max(2 * capacity, new_size));
}

LIBFT_BOOL	ft_string_equals(const struct ft_string *s, const char *_x)
{
	return (ft_strcmp(s->_data, _x) == 0);
}

struct ft_string	ft_string_create(void)
{
	struct ft_string	s;

	s._data = ft_calloc(LIBFT_STRING_DEFAULT_CAPACITY, sizeof(char));
	LIBFT_ASSERT(s._data);
	s._capacity = LIBFT_STRING_DEFAULT_CAPACITY;
	return s;
}

struct ft_string	ft_string_create_from_string(const char *_x)
{
	struct ft_string	s = ft_string_create();

	ft_string_assign(&s, _x);
	return s;
}

struct ft_string	ft_string_create_from_string_count(const char *_x, size_t count)
{
	struct ft_string	s = ft_string_create();

	ft_string_assign_count(&s, _x, count);
	return s;
}

struct ft_string	ft_string_create_from_char(const char _x, size_t count)
{
	struct ft_string	s = ft_string_create();

	ft_string_assign_char(&s, _x, count);
	return s;
}

struct ft_string	ft_string_create_from_ft_string(const ft_string *s)
{
	struct ft_string	t = ft_string_create();

	if (s->_data)
		ft_string_assign(&t, s->_data);
	return t;
}

void	ft_string_destroy(struct ft_string *s)
{
	if (!s)
		return ;
	if (s->_data)
	{
		LIBFT_FREE(s->_data);
		s->_capacity = 0;
	}
}

const char	*ft_string_data(const struct ft_string *s)
{
	return s->_data;
}

size_t	ft_string_size(const struct ft_string *s)
{
	if (!s->_data)
		return 0;
	return ft_strlen(s->_data);
}

size_t	ft_string_length(const struct ft_string *s)
{
	return ft_strlen(s->_data);
}

char	ft_string_at(const struct ft_string *s, size_t pos)
{
	LIBFT_ASSERT(pos < s->_capacity);
	return s->_data[pos];
}

LIBFT_BOOL	ft_string_empty(const struct ft_string *s)
{
	return s->_capacity == 0 || s->_data[0] == '\0';
}

size_t	ft_string_max_size(void)
{
	return (SIZE_MAX);
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
	size_t	len = ft_strlen(s->_data) + 1;

	if (s->_capacity > len)
	{
		char *new_data = malloc(sizeof(char) * len);
		if (!new_data)
			return (LIBFT_FALSE);
		ft_memcpy(new_data, s->_data, len);
		if (s->_data)
			LIBFT_FREE(s->_data);
		s->_data = new_data;
		s->_capacity = len;
	}
	return (LIBFT_TRUE);
}

void	_ft_string_print_debug(const struct ft_string *s, const char *_info, const char *param, size_t param_size)
{
	int	_cap;

	if (!s)
		return ;
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
	size_t _size, _newsize;
	size_t len = ft_strlen(_x);

	_size = ft_strlen(s->_data);
	_newsize = _size + len + 1;
	if (s->_capacity < _newsize)
	{
		size_t _newcap = _ft_string_recommend(s->_capacity, _newsize);
		char *new_data = ft_calloc(_newcap, sizeof(char));
		if (!new_data)
			return (LIBFT_FALSE);
		s->_capacity = _newcap;

		if (s->_data)
		{
			ft_strcat(new_data, s->_data);
			LIBFT_FREE(s->_data);
		}
		ft_strcat(new_data, _x);
		s->_data = new_data;
	}
	else
	{
		ft_strcat(s->_data, _x);
	}
	// _ft_string_print_debug(s, "append_string()", _x, ft_strlen(_x));
	return (LIBFT_TRUE);
}

LIBFT_BOOL	ft_string_append_char(struct ft_string *s, const char _x, size_t n)
{
	size_t _size, _newsize;

	_size = ft_strlen(s->_data);
	_newsize = _size + n + 1;
	if (s->_capacity < _newsize)
	{
		size_t _newcap = _ft_string_recommend(s->_capacity, _newsize);
		char *new_data = ft_calloc(_newcap, sizeof(char));
		if (!new_data)
			return (LIBFT_FALSE);
		s->_capacity = _newcap;

		if (s->_data)
		{
			ft_strcpy(new_data, s->_data);
			LIBFT_FREE(s->_data);
		}
		ft_memset(new_data + _size, _x, n);
		s->_data = new_data;
	}
	else
	{
		ft_memset(s->_data + _size, _x, n);
	}
	// _ft_string_print_debug(s, "append_char()", &_x, 1);
	return (LIBFT_TRUE);
}

LIBFT_BOOL	ft_string_assign(struct ft_string *s, const char *_x)
{
	size_t _xsize;

	_xsize = ft_strlen(_x) + 1;
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
	return (LIBFT_TRUE);
}

LIBFT_BOOL	ft_string_assign_count(struct ft_string *s, const char *_x, size_t count)
{
	size_t _xsize;

	_xsize = ft_strnlen(_x, count) + 1;
	if (s->_capacity < _xsize)
	{
		char *new_data = ft_strndup(_x, count);
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
	return (LIBFT_TRUE);
}

LIBFT_BOOL	ft_string_assign_char(struct ft_string *s, const char _x, size_t count)
{
	size_t	_newcap;

	_newcap = count + 1;
	if (s->_capacity < count)
	{
		char *new_data = ft_calloc(_newcap, sizeof(char));
		if (!new_data)
			return (LIBFT_FALSE);
		s->_capacity = _newcap;

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
	return (LIBFT_TRUE);
}

void	ft_string_clear(struct ft_string *s)
{
	if (s->_data)
		ft_bzero(s->_data, s->_capacity);
}
