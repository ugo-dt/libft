#include "libft/libft.h"

int	_ft_vsnprintf_internal(char *s, size_t maxlen, const char *f, va_list ap);

int	ft_vsnprintf(char* str, size_t size, const char* restrict format, va_list ap)
{
	int		done;
	va_list	ap_copy;

	va_copy(ap_copy, ap);
	done = _ft_vsnprintf_internal(str, size, format, ap_copy);
	va_end(ap_copy);
	return (done);
}
