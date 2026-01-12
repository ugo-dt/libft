#ifndef LIBFT_H
#define LIBFT_H

#include <assert.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#define LIBFT_RESTRICT
#else

#ifndef LIBFT_ASSERT
	#define LIBFT_ASSERT(...)	assert(__VA_ARGS__)
#endif

#define LIBFT_RESTRICT	restrict
#define LIBFT_UNUSED __attribute__((unused))
#define LIBFT_NODISCARD __attribute__((warn_unused_result))
#define LIBFT_NOTUSED(x) ((void)(x))
#define LIBFT_FORCE_INLINE static inline __attribute__((always_inline))

#ifndef INT32_MAX
	#define INT32_MAX INT_MAX
	#define INT32_MIN INT_MIN
#endif // INT32_MAX

#if defined(LIBFT_NO_FUNCTION_POINTERS)
	#define LIBFT_STRING_NO_FUNCTION_POINTERS
	#define LIBftv_NO_FUNCTION_POINTERS
#endif // defined(LIBFT_NO_FUNCTION_POINTERS)

#ifndef LIBFT_BUFFERSIZE
	#define LIBFT_BUFFERSIZE	42
#endif

#if defined(__GNUC__) && !defined(LIBFT_NO_STATEMENT_EXPRESSIONS)
	#ifndef max
		#define max(a, b) ({\
			__typeof__(a) _a = (a); \
			__typeof__(b) _b = (b); \
			_a > _b ? _a : _b; })
	#endif // max
	#ifndef min
		#define min(a, b) ({\
			__typeof__(a) _a = (a); \
			__typeof__(b) _b = (b); \
			_a < _b ? _a : _b; })
	#endif // min
	#ifndef clamp
		#define clamp(x, mn, mx) ({\
			__typeof__(x) _x = (x); \
			__typeof__(mn) _mn = (mn); \
			__typeof__(mx) _mx = (mx); \
			max(_mn, min(_mx, _x)); })
	#endif // clamp
#else // !defined(__GNUC__) || defined(LIBFT_NO_STATEMENT_EXPRESSIONS)
	#define LIBFT_DECL_MIN_MAX_TYPE(T, ...) \
	static inline T _libft__min_##__VA_ARGS__(const T a, const T b) { return ((a) < (b)) ? (a) : (b); } \
	static inline T _libft__max_##__VA_ARGS__(const T a, const T b) { return ((a) > (b)) ? (a) : (b); }
	LIBFT_DECL_MIN_MAX_TYPE(signed char, c) LIBFT_DECL_MIN_MAX_TYPE(unsigned char, uc)
	LIBFT_DECL_MIN_MAX_TYPE(signed short, s) LIBFT_DECL_MIN_MAX_TYPE(unsigned short, us)
	LIBFT_DECL_MIN_MAX_TYPE(signed int, i) LIBFT_DECL_MIN_MAX_TYPE(unsigned int, ui)
	LIBFT_DECL_MIN_MAX_TYPE(signed long, l) LIBFT_DECL_MIN_MAX_TYPE(unsigned long, ul)
	LIBFT_DECL_MIN_MAX_TYPE(signed long long, ll) LIBFT_DECL_MIN_MAX_TYPE(unsigned long long, ull)
	LIBFT_DECL_MIN_MAX_TYPE(float, f) LIBFT_DECL_MIN_MAX_TYPE(double, d) LIBFT_DECL_MIN_MAX_TYPE(long double, ld)
	#define LIBFT_MIN_MAX_TYPE_GENERIC(a, b, _f) _Generic((b),	\
	signed char: _f##c,			unsigned char: _f##uc,			\
	signed short: _f##s,		unsigned short: _f##us,			\
	signed int: _f##i,			unsigned int: _f##ui,			\
	signed long: _f##l,			unsigned long: _f##ul,			\
	signed long long: _f##ll,	unsigned long long: _f##ull,	\
	float: _f##f,												\
	double: _f##d,												\
	long double: _f##ld											\
)((a), (b))

#ifndef min
	#define min(a, b) LIBFT_MIN_MAX_TYPE_GENERIC(a, b, _libft__min_)
#endif // min

#ifndef max
	#define max(a, b) LIBFT_MIN_MAX_TYPE_GENERIC(a, b, _libft__max_)
#endif // max

#endif // __GNUC__
#endif // __cplusplus

// >>array

/** The ft_array_size() function returns the size of a NULL terminated
 * two-dimensional array. */
size_t ft_array_size(void** arr);

/** The ft_free_array() function frees a each element from a two-dimensional
 * array, starting from index 0 up to the first NULL element encountered. */
void ft_free_array(void** arr);

/** The ft_free_array_n() function frees up to n elements from a
 * two-dimensional array, then frees the void* to the array. */
void ft_free_array_n(void** tab, size_t n);

/*
 * The ft_copy_array() function returns a copy of the NULL-terminated
 * two-dimensional array arr. The function only copies up to the first
 * NULL encountered.
 * 
 * The memory for the copy is obtained using malloc(3),
 * and can be freed with free(3);
 */
char** ft_copy_array(char **arr);

/** 
 * The ft_split() function splits a string it into words, and returns them as
 * a NULL-terminated array of strings.
 * 
 * A "word" is defined as a part of a string delimited by the character c,
 * or by the start/end of the string.
 * 
 * The memory for the array is obtained using malloc(3),
 * and can be freed with free(3);
 */
char** ft_split(const char *s, char c);

/*
 * Print every string in the array arr, followed by a newline,
 * on the file descriptor fd.
 * 
 * The function stops at the first NULL string encountered.
 */
void ft_print_array_fd(const char **arr, int fd);

/** Sort an array of strings using ft_strcmp(). */
void ft_sort_array(char **array);

// >>char

/** The ft_islower() function tests for any lower-case letters */
int ft_islower(int c);

/** The ft_isupper() function tests for any upper-case letter. */
int ft_isupper(int c);

/** The ft_tolower() function converts an upper-case letter to the corresponding
 * lower-case letter. The argument must be representable as an unsigned char.*/
int ft_tolower(int c);

/** The ft_toupper() function converts an lower-case letter to the corresponding
 * upper-case letter. The argument must be representable as an unsigned char.*/
int ft_toupper(int c);

/** The ft_isalpha() function tests for any character
 * for which isupper(3) or islower(3) is true.
 *
 * @return Zero if the character tests false and non-zero if the
 * character tests true.
 */
int ft_isalpha(int c);

/** The ft_isdigit() function tests for a decimal digit character. 
 *
 * This includes the following characters only:
 * '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
 * 
 * @returns Zero if the character tests false and return non-zero if the
 * character tests true.
 */
int ft_isdigit(int c);

/** The ft_isalnum() function tests for any character for which
 * ft_isalpha() or ft_isdigit() is true. */
int ft_isalnum(int c);

/** The isascii() function tests for an ASCII character, which is any character
 * between 0 and decimal 127 inclusive. */
int ft_isascii(int c);

/** The ft_isprint() function tests for any printing character,
 * including space (' '). */
int ft_isprint(int c);

/** The ft_isspace() function tests for the white-space characters.
 * This includes the following standard characters:
 * '\\t'   '\\n'    '\\v'    '\\f'    '\\r'    ' ' */
int ft_isspace(int c);

// >>list

/**
 * struct s_list
 * 
 * @param content Pointer to any type of data;
 * @param next The address of the next link of the list (NULL if last).
 */
typedef struct s_list
{
	void* content;
	struct s_list* next;
}t_list;

/** Adds a new element at the end of the list.
 * 
 * @param lst The first element of the list.
 * @param new_elem The new element to be added at the back of the list. Can be NULL.
 */
void ft_lstadd_back(t_list **lst, t_list *new_elem);

/** Adds a new element at the start of the list.
 * 
 * @param lst The first element of the list. Can be NULL. 
 * @param new_elem The new element to be added at the front of the list. Can be NULL.
 */
void ft_lstadd_front(t_list **lst, t_list *new_elem);

/** Clears a linked list.
 * 
 * @param lst The first element of the list. Can be NULL.
 * @param del The function to delete the contents of the element. Can be NULL.
 */
void ft_lstclear(t_list **lst, void (*del)(void* ));

/** Deletes an element, without relinking the list.
 *
 * @param lst The element to be deleted. Can be NULL.
 * @param del The function to delete the contents of the element. Can be NULL.
 */
void ft_lstdelone(t_list *lst, void (*del)(void* ));

/** Applies the function f to each element in the list. 
 *
 * @param lst The first element of the list. Can be NULL.
 * @param f The function to apply to each element. Can be NULL.
 */
void ft_lstiter(t_list *lst, void (*f)(void* ));

/** 
 * @param lst The first element of the list. Can be NULL.
 *
 * @returns The address of the last element in a given list. */
t_list* ft_lstlast(t_list *lst);

/** Creates a copy of the list with the function f applied to each element.
 * 
 * @param lst The first element of the list. Can be NULL.
 *
 * @returns A void* to the first element of the copy. 
 */
t_list* ft_lstmap(t_list *lst, void* (*f)(void* ), void (*del)(void* ));

/** Creates a new t_list element.
 * 
 * @param content A void* to any type of data. Can be NULL.
 *
 * @returns A void* to the new element, or NULL if the allocation failed.
 */
t_list* ft_lstnew(void* content);

/**
 * @param lst The first element of the list. Can be NULL.
 * 
 * @returns The numbers of elements in the list.
 */
int ft_lstsize(t_list *lst);

// >>math

/** The ft_abs() function computes the absolute value of the integer i.
 *
 * @return The absolute value.
 */
int ft_abs(int i);

/** The ft_labs() function computes the absolute value of a long number x.
 *
 * @return The absolute value.
 */
long ft_labs(long i);
long long ft_llabs(long long x);

/** The fabs() functions compute the absolute value of a floating-point
 * number x.
 * @return The absolute value.
 */
double ft_fabs(double x);
float ft_fabsf(float x);
long double ft_fabsl(long double x);

// >>memory

/** The ft_bzero() function writes n zeroed bytes to the string s.
 * If n is zero, ft_bzero() does nothing. */
void ft_bzero(void* s, size_t n);

/** The ft_calloc() function allocates enough space for count objects
 * that are size bytes of memory each and returns a void* to the allocated
 * memory.  The allocated memory is filled with bytes of value zero. */
void* ft_calloc(size_t count, size_t size);

/** The ft_memccpy() function copies bytes from string src to string dst. 
 * If the character c (converted to an unsigned char) occurs in the string
 * src, the copy stops and a void* to the byte after the copy of c in the
 * string dst is returned. Otherwise, n bytes are copied, and a NULL void* is
 * returned.
 *
 * The source and destination strings should not overlap,
 * as the behavior is undefined. */
void* ft_memccpy(void* dest, const void* src, int c, size_t n);

/** The ft_memchr() function locates the first occurrence of c
 * (as converted to an unsigned char) in the string s. */
void* ft_memchr(const void* s, int c, size_t n);

/** The ft_memcmp() function compares byte string s1 against byte string s2.
 * Both strings are assumed to be n bytes long. */
int ft_memcmp(const void* s1, const void* s2, size_t n);

/** The memmove() function copies len bytes from string src to string dst.
 * The two strings may overlap; the copy is always done in a non-destructive
 * manner. */
void* ft_memmove(void* dest, const void* src, size_t n);

/** The ft_memcpy() function copies n bytes from memory area src to memory
 * area dst. If dst and src overlap, behavior is undefined. Applications in
 * which dst and src might overlap should use ft_memmove instead. */
void* ft_memcpy(void* LIBFT_RESTRICT dst, const void* LIBFT_RESTRICT src, size_t n);

/** The ft_memset() function writes len bytes of value c (converted to an
 * unsigned char) to the string s. */
void* ft_memset(void* s, int c, size_t n);

// >>printf

/** Maximum chars of output to write in MAXLEN.  */
int	ft_snprintf(char* str, size_t maxlen, const char *LIBFT_RESTRICT format, ...)
	__attribute__ ((__format__ (__printf__, 3, 4)));

/** Maximum chars of output to write in MAXLEN.  */
int	ft_vsnprintf(char* str, size_t maxlen, const char *LIBFT_RESTRICT format, va_list ap)
	__attribute__ ((__format__ (__printf__, 3, 0)));

/** Write formatted output to the file descriptor fd
 * from the format string FORMAT.
 * @returns The number of written characters. */
int	ft_dprintf(int fd, const char *LIBFT_RESTRICT format, ...) \
	__attribute__((__format__ (__printf__, 2, 3)));

/** Write formatted output to stdout from the format string FORMAT.
 * @returns The number of written characters. */
int	ft_printf(const char *LIBFT_RESTRICT format, ...) \
	__attribute__((__format__ (__printf__, 1, 2)));

// >>string

/** The ft_atoi() function converts the initial portion
 * of the string pointed by str to an int representation. */
int ft_atoi(const char *str);

/** The ft_itoa() function converts an integer value to
 * a null-terminated string. */
char* ft_itoa(int n);

/** Returns the length from s to the next character c
 * or the next '\\0' character. */
size_t ft_len_to_char(const char *s, char c);

/** Returns the length from s to the next space character (using ft_isspace())
 * or the next '\\0' character. */
size_t ft_len_to_space(const char *s);

/** The ft_str_tolower() function converts each uppercase letter to the 
 * corresponding lowercase letter in the null-terminated string s. */
void ft_str_tolower(char *s);

/** The ft_str_toupper() function converts each lowercase letter to the 
 * corresponding uppercase letter in the null-terminated string s. */
void ft_str_toupper(char *s);

/** 
 * The ft_strcmp() and ft_strncmp() functions lexicographically compare the
 * null-terminated strings s1 and s2.
 * 
 * @returns 0 if the strings are identical.
 */
int ft_strcmp(const char *s1, const char *s2);

/** 
 * The ft_strcmp() and ft_strncmp() functions lexicographically compare the
 * null-terminated strings s1 and s2.
 * 
 * The ft_strncmp() function compares not more than n characters.
 * Because ft_strncmp() is designed for comparing strings rather than binary
 * data, characters that appear after a '\\0' character are not compared.
 * 
 * @returns 0 if the strings are identical.
 */
int ft_strncmp(const char *s1, const char *s2, size_t n);

/** 
 * The ft_strdup() function allocates sufficient memory for a copy of the string
 * s1, does the copy, and returns a void* to it. The void* may subsequently
 * be used as an argument tothe function free(3).
 * 
 * If insufficient memory is available, NULL is returned.
 */
char* ft_strdup(const char *s);

/** 
 * The ft_strndup() function allocates sufficient memory for a copy of the string
 * s1, does the copy, and returns a void* to it. The void* may subsequently
 * be used as an argument tothe function free(3).
 * 
 * The function copies at most n characters from the string s1 and always
 * NULL-terminates the copied string.
 * 
 * If insufficient memory is available, NULL is returned.
 */
char* ft_strndup(const char *s, size_t n);

/** 
 * The ft_strjoin() function appends the string s2 to the end of s1,
 * overwriting the terminating null character ('\\0') at the end of s1,
 * then adds a terminating null character.
 * 
 * If either of the strings is NULL, the function returns NULL.
 * 
 * Memory for the new string is obtained with malloc(3),
 * and can be freed with free(3);
 */
char* ft_strjoin(const char *s1, const char *s2);

/** 
 * The ft_strjoin_3() function appends a copy of the null-terminated strings
 * s2 and s3 to the end of the null-terminated string s1, overwriting the
 * terminating null character ('\\0') at the end of s1, then adds a
 * terminating null character.
 * 
 * If one of the strings is NULL, the function returns NULL.
 * 
 * Memory for the new string is obtained with malloc(3),
 * and can be freed with free(3);
 */
char* ft_strjoin_3(const char *s1, const char *s2, const char *s3);

/** 
 * The ft_strcat() and function append a copy of the null-terminated
 * string s2 to the end of the null-terminated string s1, then add a terminating
 * '\\0'. The string s1 must have sufficient space to hold the result.
 */
char* ft_strcat(char *s1, const char *s2);

/** 
 * The ft_strcat() and function append a copy of the null-terminated
 * string s2 to the end of the null-terminated string s1, then add a terminating
 * '\\0'. The string s1 must have sufficient space to hold the result. 
 * 
 * The ft_strncat function appends not more than n characters from s2,
 * and then adds a terminating '\\0'.
 */
char* ft_strncat(char *s1, const char *s2, size_t n);

/** 
 * The ft_strlcat() function appends the NUL-terminated
 * string src to the end of dst.
 * It will append at most size - ft_strlen(dst) - 1 bytes,
 * null-terminating the result.
 * 
 * The function returns the total length of the string it tried to create.
 */
size_t ft_strlcat(char *dst, const char *src, size_t size);

/**
 * The strcspn() function calculates the length of the initial segment of s
 * which consists entirely of bytes not in reject.
 */
size_t ft_strcspn(const char *s1, const char *s2);

/** The ft_strcpy() function copy the string src to dst
 * (including the terminating '\\0' character.) */
char* ft_strcpy(char *dest, const char *src);

/** 
 * The ft_strncpy() function copy the string src to dst
 * (including the terminating '\\0' character.)
 *
 * The function copy at most len characters from src into dst.
 * If src is less than n characters long, the remainder of dst is filled with
 * '\\0' characters. Otherwise, dst is not terminated.
 */
char* ft_strncpy(char *s1, const char *s2, size_t n);

/** The ft_strlcpy() function copies up to size - 1 characters from
 * the NUL-terminated string src to dst, NUL-terminating the result. */
size_t ft_strlcpy(char *dst, const char *src, size_t size);

/** The ft_strlen() function computes the length of the string s. */
size_t ft_strlen(const char *s);

/** The ft_strnlen() function attempts to compute the length of s,
 * but never scans beyond the first maxlen bytes of s. */
size_t ft_strnlen(const char *s, size_t maxlen);

/** 
 * The ft_strnstr() function locates the first occurrence of the null-terminated
 * string needle in the string haystack, where not more than len characters are
 * searched. Characters that appear after a '\\0' character are not searched.
 */
char* ft_strnstr(const char *haystack, const char *needle, size_t n);

/** 
 * The ft_strchr() function locates the first occurrence of the char c in the
 * string pointed to by s. The terminating null character is considered to be
 * part of the string; therefore if c is '\\0', the function locates the
 * terminating '\\0'.
 * 
 * The function returns NULL if it cannot find the character c in the string s.
 */
char* ft_strchr(const char *s, int c);

/** 
 * The ft_strchr() function locates the first occurrence of the char c in the
 * string pointed to by s. The terminating null character is considered to be
 * part of the string; therefore if c is '\\0', the function locates the
 * terminating '\\0'.
 * 
 * The function returns NULL if it cannot find the character c in the string s.
 *
 * The ft_strrchr() function is identical to ft_strchr(),
 * except it locates the last occurrence of c.
 */
char* ft_strrchr(const char *s, int c);

/** 
 * The ft_strmapi() applies the given function f to each character of the
 * string s to create a new string (with malloc(3))
 * resulting from successive applications of f.
 */
char* ft_strmapi(const char *s, char (*f)(unsigned int, char));

/** 
 * The ft_substr() function allocates memory with malloc(3) then returns a
 * string of len characters (or up to the first '\\0' encountered), and
 * starting from index start of s.
 */
char* ft_substr(const char *s, unsigned int start, size_t len);

/*
 * The ft_strtrim() function allocates memory with malloc(3) then returns the
 * same string as s1, without the characters specified in set, at the start
 * and at the end of s1.
 */
char* ft_strtrim(char *s1, char *set);

// >>write

/** Write a character on the standard output. */
void ft_putchar(char c);

/** Write a character on the file descriptor fd. */
void ft_putchar_fd(char c, int fd);

/** Print a number on the standard output. */
void ft_putnbr(int n);

/** Print a number on the file descriptor fd. */
void ft_putnbr_fd(int n, int fd);

/** Print the string s on the standard output. */
void ft_putstr(const char *LIBFT_RESTRICT s);

/** Print the string s on the file descriptor fd. */
void ft_putstr_fd(const char *s, int fd);

/** Print the string s followed by a newline, on the standard output. */
void ft_putendl(const char *LIBFT_RESTRICT s);

/** Print a string followed by a newline, on the file descriptor fd. */
void ft_putendl_fd(const char *s, int fd);

// >>get_next_line

int ft_get_next_line(int fd, char **line);

// >>basic_string

typedef struct ft_string
{
	char* _data;
	size_t _capacity;
}ft_string;

#ifndef LIBFT_STRING_DEFAULT_CAPACITY
#define LIBFT_STRING_DEFAULT_CAPACITY	15
#endif // LIBFT_STRING_DEFAULT_CAPACITY

ft_string ftstr_create(void);
ft_string _ftstr_create_from_str(const char *_x);
ft_string _ftstr_create_from_str_count(const char *_x, size_t count);
ft_string _ftstr_create_from_char(const char _x, size_t count);
ft_string _ftstr_create_from_ft_string(const ft_string* s);
void _ftstr_destroy(ft_string* s);
bool _ftstr_equals(const ft_string* a, const ft_string* b);
bool _ftstr_equals_str(const ft_string* s, const char *_x);
const char*	_ftstr_data(const ft_string* s);
size_t _ftstr_size(const ft_string* s);
size_t _ftstr_length(const ft_string* s);
char _ftstr_at(const ft_string* s, size_t pos);
bool _ftstr_empty(const ft_string* s);
size_t _ftstr_max_size(void);
void _ftstr_reserve(ft_string* s, size_t new_cap);
size_t _ftstr_capacity(const ft_string* s);
void _ftstr_shrink_to_fit(ft_string* s);
void _ftstr_append_str(ft_string* s, const char *_x);
void _ftstr_append_char(ft_string* s, const char _x, size_t n);
void _ftstr_append_ft_string(ft_string* s, const ft_string* x);
void _ftstr_assign(ft_string* s, const char *_x);
void _ftstr_assign_count(ft_string* s, const char *_x, size_t count);
void _ftstr_assign_char(ft_string* s, const char _x, size_t count);
void _ftstr_clear(ft_string* s);

#define ft_string(...) _Generic((__VA_ARGS__),            \
	char *: _ftstr_create_from_str,                       \
	char: _ftstr_create_from_char,                        \
	int: _ftstr_create_from_char,                         \
	struct ft_string*: _ftstr_create_from_ft_string,      \
	const struct ft_string*: _ftstr_create_from_ft_string,\
	default: ftstr_create \
)(__VA_ARGS__)

#define ftstr_destroy(__s) _ftstr_destroy(&(__s))
#define ftstr_equals(__s, __x) _Generic((__x), \
	const char*: _ftstr_equals_str,            \
	char*: _ftstr_equals_str,                  \
	struct ft_string*: _ftstr_equals           \
)(&(__s), __x)
#define ftstr_data(__s) _ftstr_data(&(__s))
#define ftstr_size(__s) _ftstr_size(&(__s))
#define ftstr_length(__s) _ftstr_length(&(__s))
#define ftstr_at(__s, __pos) _ftstr_at(&(__s), __pos)
#define ftstr_empty(__s) _ftstr_empty(&(__s))
#define ftstr_max_size() _ftstr_max_size()
#define ftstr_reserve(__s, __new_cap) _ftstr_reserve(&(__s), __new_cap)
#define ftstr_capacity(__s) _ftstr_capacity(&(__s))
#define ftstr_shrink_to_fit(__s) _ftstr_shrink_to_fit(&(__s))
#define _ftstr_append_generic(__s, ...)        \
	_Generic((__VA_ARGS__),                    \
	const char*: _ftstr_append_str,            \
	char*: _ftstr_append_str,                  \
	struct ft_string*: _ftstr_append_ft_string \
)(__s, __VA_ARGS__)
#define _ftstr_get_append_macro(__sptr, __char, __count, __macro_name, ...)	__macro_name
#define _ftstr_get_append(__sptr, __x) _ftstr_append_generic(__sptr, __x)
#define _ftstr_get_append_count(__sptr, __char, __count) _ftstr_append_char(__sptr, __char, __count)
#define ftstr_append(__s, ...) _ftstr_get_append_macro(&(__s), __VA_ARGS__, _ftstr_get_append_count, _ftstr_get_append)(&(__s), __VA_ARGS__)

#define _ftstr_assign_generic(__s, ...)    \
	_Generic((__VA_ARGS__),                \
	const char*: _ftstr_assign,            \
	char*: _ftstr_assign,                  \
	struct ft_string*: _ftstr_assign_ft_string \
)(__s, __VA_ARGS__)
#define _ftstr_get_assign_macro(__sptr, __char, __count, __macro_name, ...)	__macro_name
#define _ftstr_get_assign(__sptr, __x) _ftstr_assign(__sptr, __x)
#define _ftstr_get_assign_count(__sptr, __char, __count) _ftstr_assign_generic(__sptr, __char, __count)
#define ftstr_assign(__s, ...) _ftstr_get_assign_macro(&(__s), __VA_ARGS__, _ftstr_get_assign_count, _ftstr_get_assign)(&(__s), __VA_ARGS__)

#define ftstr_clear(__s) _ftstr_clear(&(__s))

// >>ft_argparse

#define FTAP_INT_MIN (INT32_MIN)
#define FTAP_INT_MAX (INT32_MAX)
#define FTAP_VALUE(T_, value_) (&(T_){value_})

typedef enum ftap_option_type
{
	// options without arguments
	FTAP_OPTION_TYPE_BOOL, // default

	// options with arguments
	// expect the address of the variable that will store the value
	FTAP_OPTION_TYPE_STRING,
	FTAP_OPTION_TYPE_INT,
	FTAP_OPTION_TYPE_FLOAT,
} ftap_option_type;

typedef void* ftap_value;

typedef struct ftap_option_desc
{
	ftap_option_type type;
	char short_name;
	char* long_name;
	void* value; // pointer to the variable that will store the value
	ftap_value min;
	ftap_value max;
	ftap_value default_value;
} ftap_option_desc;

typedef struct ftap_desc
{
	char* program_name;
	char* usage;

	// Options
	ftap_option_desc* options;
	size_t opt_count;
	bool opt_ignore_unknown;
	bool opt_allow_merge_short;
} ftap_desc;

typedef struct ftap_option
{
	bool is_set;
} ftap_option;

typedef enum ftap_status
{
	FTAP_STATUS_SUCCESS,
	FTAP_STATUS_INVALID_OPTION,
	FTAP_STATUS_UNRECOGNIZED_OPTION,
	FTAP_STATUS_INVALID_OPTION_VALUE,
	FTAP_STATUS_OPTION_REQUIRES_ARGUMENT,
	FTAP_STATUS_TOO_MANY_ARGUMENTS,
	FTAP_STATUS_ALLOCATION_FAILURE,
} ftap_status;

typedef struct
{
	size_t opt_count;
	ftap_option* options;
	char** arguments;
	ftap_status _status;
} ftap_state;

ftap_state ftap_parse(int argc, char** argv, const ftap_desc* state);
void ftap_clear(ftap_state* state);
bool ftap_valid(const ftap_state* state);

// >>fileparse

typedef struct
{
	int type;
	const char* value;
}ftfp_token_desc;

// todo: comments
typedef struct
{
	ftfp_token_desc* tokens;
	size_t token_count;
	bool skip_newlines;
	bool (*isspace)(int);
	bool (*isseparator)(int);
}ftfp_desc;

typedef struct
{
	uint64_t type;
	char* value;
	int row, col;
}ftfp_token;

typedef enum
{
	FTFP_STATUS_SUCCESS = 0,
	FTFP_STATUS_CANNOT_OPEN_FILE,
	FTFP_STATUS_ALLOCATION_FAILURE,
}ftfp_status;

typedef struct
{
	ftfp_status _status;
	ftfp_token* tokens;
	size_t count;
}ftfp_state;

ftfp_state ftfp_parse(const char *file, const ftfp_desc* desc);
bool ftfp_valid(const ftfp_state* state);
void ftfp_clear(ftfp_state* state);

// >>vector

typedef struct ft_allocator
{
	size_t sizeof_type;
	void* (*allocate)(const struct ft_allocator*, size_t n);
	void (*deallocate)(const struct ft_allocator*, void* p, size_t n);
	void (*construct)(const struct ft_allocator*, void* p, const void* value_ptr);
	void (*destroy)(const struct ft_allocator*, void* p);
	size_t (*max_size)(const struct ft_allocator*);
}ft_allocator;

void* ft_allocator_allocate(const ft_allocator* alloc, size_t n);
void ft_allocator_deallocate(const ft_allocator* alloc, void* p, size_t n);
void ft_allocator_construct(const ft_allocator* alloc, void* p, const void* value);
void ft_allocator_destroy(const ft_allocator* alloc, void* p);
size_t ft_allocator_max_size(const struct ft_allocator* alloc);

typedef enum
{
	IteratorType_Random = 1,
	IteratorType_Reverse = -1
}IteratorType;

typedef struct ft_iterator
{
	void* _p;
	size_t _sizeof_type;
	IteratorType _type;
}ft_iterator;

typedef struct ft_vector
{
	ft_allocator alloc;
	void* begin;
	void* end;
	void* end_cap;
}ft_vector;

typedef struct
{
	ft_allocator alloc;
	size_t size;
	size_t capacity;
	void* default_value;
}ftv_desc;

ft_vector ftv_create(const ftv_desc* desc);
void _ftv_destroy(ft_vector* vector);
ft_iterator _ftv_begin(const ft_vector* vector);
ft_iterator _ftv_end(const ft_vector* vector);
ft_iterator _ftv_rbegin(const ft_vector* vector);
ft_iterator _ftv_rend(const ft_vector* vector);
size_t _ftv_max_size(const ft_vector* vector);
size_t _ftv_size(const ft_vector* vector);
size_t _ftv_capacity(const ft_vector* vector);
size_t _ftv_empty(const ft_vector* vector);
void _ftv_clear(ft_vector* vector);
void _ftv_reserve(ft_vector* vector, size_t n);
void _ftv_assign(ft_vector* vector, ft_iterator first, ft_iterator last);
void _ftv_push_back(ft_vector* vector, const void* value);
void _ftv_pop_back(ft_vector* vector);
void* _ftv_data(const ft_vector* vector);
void* _ftv_at(const ft_vector* vector, size_t n);
ft_iterator _ftv_erase_at(ft_vector* vector, const ft_iterator pos);
ft_iterator _ftv_erase(ft_vector* vector, ft_iterator first, ft_iterator last);
ft_iterator _ftv_insert_element(ft_vector* vector, ft_iterator pos, const void* value);

#define ftv_destroy(__vector) _ftv_destroy((&__vector))
#define ftv_begin(__vector) _ftv_begin((&__vector))
#define ftv_end(__vector) _ftv_end((&__vector))
#define ftv_rbegin(__vector) _ftv_rbegin((&__vector))
#define ftv_rend(__vector) _ftv_rend((&__vector))
#define ftv_max_size(__vector) _ftv_max_size((&__vector))
#define ftv_size(__vector) _ftv_size((&__vector))
#define ftv_capacity(__vector) _ftv_capacity((&__vector))
#define ftv_empty(__vector) _ftv_empty((&__vector))
#define ftv_clear(__vector) _ftv_clear((&__vector))
#define ftv_reserve(__vector, __n) _ftv_reserve((&__vector), (__n))
#define ftv_assign(__vector, __first, __last) _ftv_assign((&__vector), (__first), (__last))
#define ftv_push_back(__vector, ...) _ftv_push_back((&__vector), &((__VA_ARGS__)))
#define ftv_push_backv(__vector, __value) _ftv_push_back((&__vector), &(__typeof__(__value)){__value})
#define ftv_pop_back(__vector) _ftv_pop_back((&__vector))
#define ftv_data(__vector) _ftv_data((&__vector))
#define ftv_at(__vector, __n, __type) (*( __type* )_ftv_at((&__vector), (__n)))
#define ftv_erase_at(__vector, __it_pos) _ftv_erase_at((&__vector), (__it_pos))
#define ftv_erase_range(__vector, __first, __last) _ftv_erase((&__vector), (__first), (__last))
#define ftv_insert_at(__vector, __it_pos, ...) _ftv_insert_element((&__vector), (__it_pos), &((__VA_ARGS__)))
#define ftv_insert_atv(__vector, __it_pos, __value) _ftv_insert_element((&__vector), (__it_pos), &(__typeof__(__value)){__value})

// >>timer

#define FT_NS_PER_SECOND (1000000000)
#define FT_NS_PER_MS (1000000)

typedef struct ft_timer
{
	uint64_t start; // ns
}ft_timer;

uint64_t fttm_now(void);
void fttm_reset(ft_timer* timer);
uint64_t fttm_elapsed_ns(ft_timer* timer);
uint64_t fttm_elapsed_ms(ft_timer* timer);
uint64_t fttm_elapsed_seconds(ft_timer* timer);

#ifdef __cplusplus
} // extern "C"

// reference-based equivalents for C++
ftfp_state ftfp_parse(const char *file, const ftfp_desc& desc) { return ftfp_parse(file, &desc); }
ftap_state ftap_parse(int argc, char** argv, const ftap_desc& state) { return ftap_parse(argc, argv, &state); }
inline ft_vector ftv_create(const ftv_desc& desc) { return ftv_create(&desc); }
#endif

#endif // LIBFT_H
