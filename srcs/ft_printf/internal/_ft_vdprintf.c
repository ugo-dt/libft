#include "internal/_libft_printf.h"

int _ft_vdprintf_internal(int fd, const char *format, va_list ap)
{
	int				done;
	unsigned char	*f;
	unsigned char	*lead_str_end;

	done = 0;
	f = lead_str_end = (unsigned char *)_ft_find_spec((const unsigned char *)format);
	if ((done = write(fd, format, (const unsigned char *)lead_str_end - (const unsigned char *)format)) < 0)
		return -1;
	while (*f != '\0')
	{
		if (*f != '%')
			done += write(fd, f++, 1);
		else
		{
			struct _libft_printf_specs specs = { 0 };

			FIND_FLAGS(f, specs);
			FIND_WIDTH(f, specs, ap);
			FIND_PRECISION(f, specs, ap);

			char	*s = NULL;
			DO_POSITIONAL(f, s, specs, ap);
			write(fd, s, specs.info.width);
			LIBFT_FREE(s);
			done += specs.info.width;
			f++;
		}
	}
	return (done);
}
