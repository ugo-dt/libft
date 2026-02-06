#include "libft/libft.h"

uint64_t	fttm_now(void)
{
	struct timespec ts;
#ifdef _WIN32
	clock_gettime(CLOCK_MONOTONIC, &ts);
#else
	timespec_get(&ts, TIME_UTC);
#endif

	return ts.tv_sec * FT_NS_PER_SECOND + ts.tv_nsec;
}

void	fttm_reset(ft_timer* timer)
{
	timer->start = fttm_now();
}

uint64_t	fttm_elapsed_ns(ft_timer* timer)
{
	struct timespec ts;
#ifdef _WIN32
	clock_gettime(CLOCK_MONOTONIC, &ts);
#else
	timespec_get(&ts, TIME_UTC);
#endif

	const uint64_t now = ts.tv_sec * FT_NS_PER_SECOND + ts.tv_nsec;
	return now - timer->start;
}

uint64_t	fttm_elapsed_ms(ft_timer* timer)
{
	return fttm_elapsed_ns(timer) / FT_NS_PER_MS;
}

uint64_t	fttm_elapsed_seconds(ft_timer* timer)
{
	return fttm_elapsed_ns(timer) / FT_NS_PER_SECOND;
}
