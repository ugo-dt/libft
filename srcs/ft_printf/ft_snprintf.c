#include "libft.h"

int	_ft_vsnprintf_internal(char *s, size_t maxlen, const char *f, va_list ap);

int	ft_snprintf(char* str, size_t maxlen, const char *restrict format, ...)
{
	int		done;
	va_list	ap;

	va_start(ap, format);
	done = _ft_vsnprintf_internal(str, maxlen, format, ap);
	va_end(ap);
	return (done);
}
