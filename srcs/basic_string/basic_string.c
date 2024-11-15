#include "libft.h"

#define LIBFT_STRING_DEFAULT_CAPACITY	15

struct ft_string
{
	char	*_data;
	size_t	_size;
	size_t	_capacity;
};

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

LIBFT_BOOL	ft_string_append_string(struct ft_string *s, const char *_x)
{
	size_t _append_len;

	_append_len = ft_strlen(_x);
	if (s->_capacity < s->_size + _append_len)
	{
		char *new_data = ft_strjoin(s->_data, _x);
		if (!new_data)
			return (LIBFT_FALSE);
		s->_capacity = s->_size + _append_len;
		
		if (s->_data)
			LIBFT_FREE(s->_data);
		s->_data = new_data;
	}
	else
	{
		ft_strcat(s->_data, _x);
	}
	s->_size += _append_len;
	return (LIBFT_TRUE);
}

LIBFT_BOOL	ft_string_append_char(struct ft_string *s, const char _x, size_t n)
{
	size_t	_newsize;

	_newsize = s->_size + n;
	if (s->_capacity < _newsize)
	{
		char *new_data = ft_calloc(_newsize, sizeof(char));
		if (!new_data)
			return (LIBFT_FALSE);
		s->_capacity = _newsize;

		ft_strcpy(new_data, s->_data);
		ft_memset(new_data + s->_size - 1, _x, n);

		if (s->_data)
			LIBFT_FREE(s->_data);
		s->_data = new_data;
	}
	else
	{
		ft_memset(s->_data + s->_size, _x, n);
	}
	s->_size = _newsize;
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
