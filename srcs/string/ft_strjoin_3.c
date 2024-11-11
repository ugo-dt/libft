#include "libft.h"

char	*ft_strjoin_3(const char *s1, const char *s2, const char *s3)
{
	char			*dst;

	if (!s1 || !s2 || !s3)
		return (NULL);
	dst = LIBFT_MALLOC(sizeof(char)
			* (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3)) + 1);
	if (!dst)
		return (NULL);
	return (ft_strcat(ft_strcat(ft_strcpy(dst, s1), s2), s3));
}
