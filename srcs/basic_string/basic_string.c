#include "libft/libft.h"

static size_t _ftstr_recommend(size_t capacity, size_t new_size)
{
	LIBFT_ASSERT(new_size < SIZE_MAX);
    if (capacity >= SIZE_MAX / 2)
        return SIZE_MAX;
    return max(2 * capacity, new_size);
}

ft_string ftstr_create(void)
{
	ft_string string;

	string._capacity = LIBFT_STRING_DEFAULT_CAPACITY;
	string._data = ft_calloc(string._capacity, sizeof(*string._data));
	LIBFT_ASSERT(string._data);
	string._data[0] = '\0';
	return string;
}

ft_string _ftstr_create_from_str(const char *x)
{
	ft_string string;

	string._capacity = 0;
	string._data = NULL;
	_ftstr_assign(&string, x);
	return string;
}

ft_string _ftstr_create_from_str_count(const char *_x, size_t count)
{
	ft_string string;
	
	string._capacity = 0;
	string._data = NULL;
	_ftstr_assign_count(&string, _x, count);
	return string;
}

ft_string _ftstr_create_from_char(const char _x, size_t count)
{
	ft_string string;
	
	string._capacity = 0;
	string._data = NULL;
	_ftstr_assign_char(&string, _x, count);
	return string;
}

ft_string _ftstr_create_from_ft_string(const ft_string* x)
{
	ft_string string;
	
	string._capacity = 0;
	string._data = NULL;
	if (x->_data)
		_ftstr_assign(&string, x->_data);
	return string;
}

void _ftstr_destroy(ft_string* s)
{
	LIBFT_ASSERT(s);
	if (s->_data)
	{
		free(s->_data);
		s->_capacity = 0;
	}
}

bool _ftstr_equals(const ft_string* a, const ft_string* b)
{
	return ft_strcmp(a->_data, b->_data) == 0;
}

bool _ftstr_equals_str(const ft_string* s, const char *_x)
{
	return ft_strcmp(s->_data, _x) == 0;
}

const char*	_ftstr_data(const ft_string* s)
{
	return s->_data;
}

size_t _ftstr_size(const ft_string* s)
{
	if (!s->_data)
		return 0;
	return ft_strlen(s->_data);
}

size_t _ftstr_length(const ft_string* s)
{
	return ft_strlen(s->_data);
}

char _ftstr_at(const ft_string* s, size_t pos)
{
	LIBFT_ASSERT(pos < s->_capacity);
	return s->_data[pos];
}

bool _ftstr_empty(const ft_string* s)
{
	return s->_capacity == 0 || s->_data[0] == '\0';
}

size_t _ftstr_max_size(void)
{
	return (SIZE_MAX);
}

void _ftstr_reserve(ft_string *s, size_t new_cap)
{
	if (s->_capacity < new_cap)
	{
		char *new_data = ft_calloc(new_cap, sizeof(char));
		LIBFT_ASSERT(new_data);
		s->_capacity = new_cap;

		ft_strcpy(new_data, s->_data);

		if (s->_data)
			free(s->_data);
		s->_data = new_data;
	}
}

size_t _ftstr_capacity(const ft_string* s)
{
	return s->_capacity;
}

void _ftstr_shrink_to_fit(ft_string *s)
{
	size_t len = ft_strlen(s->_data) + 1;

	if (s->_capacity > len)
	{
		char *new_data = malloc(sizeof(char) * len);
		LIBFT_ASSERT(new_data);
		ft_memcpy(new_data, s->_data, len);
		if (s->_data)
			free(s->_data);
		s->_data = new_data;
		s->_capacity = len;
	}
}

void _ftstr_print_debug(const ft_string* s, const char *_info, const char *param, size_t param_size)
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

void _ftstr_append_str(ft_string *s, const char *_x)
{
	size_t _size, _newsize;
	size_t len = ft_strlen(_x);

	_size = ft_strlen(s->_data);
	_newsize = _size + len + 1;
	if (s->_capacity < _newsize)
	{
		size_t _newcap = _ftstr_recommend(s->_capacity, _newsize);
		char *new_data = ft_calloc(_newcap, sizeof(char));
		LIBFT_ASSERT(new_data);
		s->_capacity = _newcap;

		if (s->_data)
		{
			ft_strcat(new_data, s->_data);
			free(s->_data);
		}
		ft_strcat(new_data, _x);
		s->_data = new_data;
	}
	else
	{
		ft_strcat(s->_data, _x);
	}
	// _ftstr_print_debug(s, "append_string()", _x, ft_strlen(_x));
}

void _ftstr_append_char(ft_string* s, const char _x, size_t n)
{
	size_t _size, _newsize;

	_size = ft_strlen(s->_data);
	_newsize = _size + n + 1;
	if (s->_capacity < _newsize)
	{
		size_t _newcap = _ftstr_recommend(s->_capacity, _newsize);
		char *new_data = ft_calloc(_newcap, sizeof(char));
		LIBFT_ASSERT(new_data);
		s->_capacity = _newcap;

		if (s->_data)
		{
			ft_strcpy(new_data, s->_data);
			free(s->_data);
		}
		ft_memset(new_data + _size, _x, n);
		s->_data = new_data;
	}
	else
	{
		ft_memset(s->_data + _size, _x, n);
	}
	// _ftstr_print_debug(s, "append_char()", &_x, 1);
}

void _ftstr_append_ft_string(ft_string* s, const ft_string* x)
{
	assert(x && x->_data);

	if (s->_data == x->_data)
	{
		// Appending to itself, make a copy first
		ft_string temp = _ftstr_create_from_ft_string(x);
		_ftstr_append_ft_string(s, &temp);
		_ftstr_destroy(&temp);
		return ;
	}
	else if (x->_capacity && x->_data)
		_ftstr_append_str(s, x->_data);
}

void _ftstr_assign(ft_string* s, const char *_x)
{
	size_t _xsize;

	_xsize = ft_strlen(_x) + 1;
	if (s->_capacity < _xsize)
	{
		char *new_data = ft_strdup(_x);
		LIBFT_ASSERT(new_data);
		LIBFT_ASSERT(new_data);
		s->_capacity = _xsize;

		if (s->_data)
			free(s->_data);
		s->_data = new_data;
	}
	else
	{
		ft_strcpy(s->_data, _x);
		ft_memset(s->_data + _xsize, '\0', s->_capacity - _xsize);
	}
}

void _ftstr_assign_count(ft_string* s, const char *_x, size_t count)
{
	size_t _xsize;

	_xsize = ft_strnlen(_x, count) + 1;
	if (s->_capacity < _xsize)
	{
		char *new_data = ft_strndup(_x, count);
		LIBFT_ASSERT(new_data);
		s->_capacity = _xsize;

		if (s->_data)
			free(s->_data);
		s->_data = new_data;
	}
	else
	{
		ft_strcpy(s->_data, _x);
		ft_memset(s->_data + _xsize, '\0', s->_capacity - _xsize);
	}
}

void _ftstr_assign_char(ft_string* s, const char _x, size_t count)
{
	size_t _newcap;

	_newcap = count + 1;
	if (s->_capacity < count)
	{
		char *new_data = ft_calloc(_newcap, sizeof(char));
		LIBFT_ASSERT(new_data);
		s->_capacity = _newcap;

		ft_memset(new_data, _x, count);
		ft_memset(new_data + count, '\0', s->_capacity - count);

		if (s->_data)
			free(s->_data);
		s->_data = new_data;
	}
	else
	{
		ft_memset(s->_data, _x, count);
		ft_memset(s->_data + count, '\0', s->_capacity - count);
	}
}

void _ftstr_clear(ft_string *s)
{
	if (s->_data)
		ft_bzero(s->_data, s->_capacity);
}
