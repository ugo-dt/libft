#ifndef _LIBFT_PRINTF_H
# define _LIBFT_PRINTF_H

# include "libft.h"

# ifdef __cplusplus
extern "C" {
# endif

# if !defined(LIBFT_NO_STATEMENT_EXPRESSIONS)
#  ifdef __GNUC__
#   if __has_warning("-Wgnu-statement-expression")
#    pragma GCC diagnostic ignored	"-Wgnu-statement-expression"
#   endif
#  endif // __GNUC
# endif

# ifndef __extern_always_inline
#  define __extern_always_inline static inline
# endif

# ifndef LIBFT_PRINTF_NULL_STRING
#   define LIBFT_PRINTF_NULL_STRING	"(null)"
# endif // LIBFT_PRINTF_NULL_STRING

# ifndef LIBFT_PRINTF_NULL_PTR
#  if defined(__linux__)
#   define LIBFT_PRINTF_NULL_PTR	"(nil)"
#  elif defined(__APPLE__)
#   define LIBFT_PRINTF_NULL_PTR	"0x0"
#  else
#   define LIBFT_PRINTF_NULL_PTR	"0x0"
#  endif
# endif // LIBFT_PRINTF_NULL_PTR

struct _libft_printf_specs
{
	struct
	{
		LIBFT_BOOL	alt:1;
		LIBFT_BOOL	zero:1;
		LIBFT_BOOL	left:1;
		LIBFT_BOOL	space:1;
		LIBFT_BOOL	showsign:1;
	}flags;

	struct
	{
		int	width;
		int	precision;
	}info;
};

char *_ft_printf_create_c(char c, struct _libft_printf_specs *specs);
char *_ft_printf_create_s(const char *s, struct _libft_printf_specs *specs);
char *_ft_printf_create_p(size_t addr, struct _libft_printf_specs *specs);
char *_ft_printf_create_di(int nb, struct _libft_printf_specs *specs);
char *_ft_printf_create_u(unsigned int nb, struct _libft_printf_specs *specs);
char *_ft_printf_create_xX(char x, unsigned int nb, struct _libft_printf_specs *specs);
char *_ft_printf_create_l(long nb, struct _libft_printf_specs *specs);
char *_ft_printf_create_ll(long long nb, struct _libft_printf_specs *specs);
char *_ft_printf_create_ul(unsigned long nb, struct _libft_printf_specs *specs);
char *_ft_printf_create_ull(unsigned long long nb, struct _libft_printf_specs *specs);

__extern_always_inline const unsigned char *_ft_find_spec(const unsigned char *format)
{
	const unsigned char *c = (const unsigned char *)ft_strchr((const char *)format, '%');
	if (!c)
		return format + ft_strlen((const char *)format);
	return (c);
}

# define FIND_WIDTH(f_, specs_, ap_)						\
	do														\
	{														\
		specs_.info.width = 0;								\
		if (ft_isdigit(*f_))								\
		{													\
			specs_.info.width = ft_atoi((const char *)f_);	\
			while (ft_isdigit(*f_) && *f_)					\
				f_++;										\
		}													\
		else if (*f_ == '*')								\
		{													\
			int _w = va_arg(ap_, int);						\
			if (_w < 0)										\
			{												\
				specs_.flags.left = LIBFT_TRUE;				\
				specs_.info.width = -_w;					\
			}												\
			else											\
				specs_.info.width = _w;						\
			f_++;											\
		}													\
		if (*f_ == '\0')									\
			return (-1);									\
	} while (0)

# define FIND_PRECISION(f_, specs_, ap_)							\
	do																\
	{																\
		specs_.info.precision = -1;									\
		while (*f_ == '*' || *f_ == '-' || ft_isdigit(*f_))			\
			f_++;													\
		if (*f_ == '.')												\
		{															\
			specs_.info.precision = 1;								\
			f_++;													\
			if (ft_isdigit(*f_))									\
				specs_.info.precision = ft_atoi((const char *)f);	\
			else if (*f_ == '*')									\
			{														\
				int _p = va_arg(ap_, int);							\
				specs_.info.precision = _p < 0 ? 0 : _p;			\
				f_++;												\
			}														\
		}															\
		while (*f_ == '*' || *f_ == '.' || ft_isdigit(*f_))			\
			f_++;													\
		if (specs_.info.precision > -1)								\
			specs_.flags.zero = LIBFT_FALSE;						\
		if (*f_ == '\0')											\
			return (-1);											\
	} while (0)

# define FIND_FLAGS(f_, specs_)						\
	do												\
	{												\
		f_++;										\
		while (ft_strchr("#0- +", *f_) && *f_)		\
	{												\
			if (*f_ == '#')							\
			{										\
				specs_.flags.alt = LIBFT_TRUE;		\
			}										\
			if (*f_ == '0')							\
			{										\
				specs_.flags.zero = LIBFT_TRUE;		\
			}										\
			if (*f_ == '-')							\
			{										\
				specs_.flags.left = LIBFT_TRUE;		\
				specs_.flags.zero = LIBFT_FALSE;	\
			}										\
			if (*f_ == ' ')							\
			{										\
				specs_.flags.space = LIBFT_TRUE;	\
			}										\
			if (*f_ == '+')							\
			{										\
				specs_.flags.showsign = LIBFT_TRUE;	\
				specs_.flags.space = LIBFT_FALSE;	\
			}										\
			f_++;									\
		}											\
	} while (0)

# define GET_NUMBER_LENGTH(len_ptr_, nb_, base_, precision_, type_)	\
	do																\
	{																\
		(*(len_ptr_)) = 1;											\
		type_ tmp_ = nb_;											\
		if (tmp_ < 0)												\
		{															\
			(*(len_ptr_))++;										\
			tmp_ = -tmp_;											\
		}															\
		while (tmp_ >= base_)										\
		{															\
			tmp_ /= base_;											\
			(*(len_ptr_))++;										\
		}															\
		if (nb_ < 0)												\
		{															\
			if (precision_ > -1 && (*(len_ptr_)) <= precision_)		\
				(*(len_ptr_)) = precision_ + 1;						\
		}															\
		else														\
		{															\
			if (precision_ > -1 && (*(len_ptr_)) < precision_)		\
				(*(len_ptr_)) = precision_;							\
		}															\
	} while (0)

# define MAKE_UNSIGNED_NUMBER_STRING(s, n_, length_, type_)	\
	do														\
	{														\
		char *s_ = (s);										\
		int i_ = length_ - 1;								\
		type_ nb_ = n_;										\
		while (nb_ >= 10)									\
		{													\
			s_[i_] = nb_ % 10 + 48;							\
			nb_ /= 10;										\
			i_--;											\
		}													\
		s_[i_] = nb_ % 10 + 48;								\
		i_--;												\
		while (i_ >= 0)										\
			s_[i_--] = '0';									\
	} while (0)

# define MAKE_NUMBER_STRING(s, type_, abs_f_, n_, length_)	\
	do														\
	{														\
		char *s_ = (s);										\
		int i_;												\
		unsigned type_ nb_;									\
		if ((n_ < 0))										\
			s_[0] = '-';									\
		i_ = length_ - 1;									\
		nb_ = abs_f_(n_);									\
		while (nb_ >= 10)									\
		{													\
			s_[i_] = nb_ % 10 + 48;							\
			nb_ /= 10;										\
			i_--;											\
		}													\
		s_[i_] = nb_ % 10 + 48;								\
		i_--;												\
		while (i_ >= (n_ < 0))								\
			s_[i_--] = '0';									\
	} while (0)

static inline char *_ft_printf_create_string_helper(struct _libft_printf_specs *specs, int arg_length, int *arg_start)
{
	char *s;

	if (specs->info.width < arg_length)
		specs->info.width = arg_length;
	s = LIBFT_MALLOC(sizeof(char) * specs->info.width);
	if (!s)
		return (NULL);
	int padding_length = specs->info.width - arg_length;
	int padding_start;
	if (!specs->flags.left)
	{
		padding_start = 0;
		*arg_start = padding_length;
	}
	else
	{
		padding_start = arg_length;
		*arg_start = 0;
	}
	ft_memset(s + padding_start, specs->flags.zero ? '0' : ' ', padding_length);
	return (s);
}

# define DO_POSITIONAL(_f, _s, _specs, ap_)																\
	do																									\
	{																									\
		if (*_f == 'l')																					\
		{																								\
			int is_long_ = 0;																			\
			_f++;																						\
			if (*_f == 'l')																				\
			{																							\
				_f++;																					\
				is_long_ = 1;																			\
			}																							\
			if (*_f == 'u')																				\
			{																							\
				if (is_long_)																			\
					_s = _ft_printf_create_ull(va_arg(ap_, unsigned long long), &_specs);				\
				else																					\
					_s = _ft_printf_create_ul(va_arg(ap_, unsigned long), &_specs);						\
			}																							\
			else if (*_f == 'd' || *_f == 'i')															\
			{																							\
				if (is_long_)																			\
					_s = _ft_printf_create_ll(va_arg(ap_, long long), &_specs);							\
				else																					\
					_s = _ft_printf_create_l(va_arg(ap_, long), &_specs);								\
			}																							\
		}																								\
		else if (*_f == '%')																			\
			_s = _ft_printf_create_c('%', &_specs);														\
		else if (*_f == 'c')																			\
			_s = _ft_printf_create_c(va_arg(ap_, int), &_specs);										\
		else if (*_f == 's')																			\
			_s = _ft_printf_create_s(va_arg(ap_, char *), &_specs);										\
		else if (*_f == 'p')																			\
			_s = _ft_printf_create_p(va_arg(ap_, size_t), &_specs);										\
		else if (*_f == 'd' || *_f == 'i')																\
			_s = _ft_printf_create_di(va_arg(ap_, int), &_specs);										\
		else if (*_f == 'u')																			\
			_s = _ft_printf_create_u(va_arg(ap_, unsigned int), &_specs);								\
		else if (*_f == 'x' || *_f == 'X')																\
			_s = _ft_printf_create_xX(*_f, va_arg(ap_, int), &_specs);									\
		if (!_s)																						\
			return (-1);																				\
	} while (0)

# ifdef __cplusplus
}
# endif

#endif // _LIBFT_PRINTF_H
