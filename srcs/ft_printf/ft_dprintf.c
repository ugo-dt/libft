#include "libft.h"

int	_ft_vdprintf_internal(int fd, const char *format, va_list ap);

int	ft_dprintf(int fd, const char *restrict format, ...)
{
	int		done;
	va_list	ap;

	va_start(ap, format);
	done = _ft_vdprintf_internal(fd, format, ap);
	va_end(ap);
	return (done);
}
