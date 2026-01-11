#include "libft/libft.h"
#include <fcntl.h> // open

typedef struct
{
	ftfp_token t;
	size_t length;
}_ftfp_list_item;

typedef struct
{
	_ftfp_list_item* begin;
	_ftfp_list_item* end;
	_ftfp_list_item* end_cap;
}_ftfp_list;

bool	_ftfp_isspace(const ftfp_desc* desc, int c)
{
	if (desc->isspace)
		return desc->isspace(c);
	return ft_isspace(c);
}

bool	_ftfp_isseparator(const ftfp_desc* desc, int c)
{
	if (desc->isseparator)
		return desc->isseparator(c);
	return false;
}

size_t	_ftfp_list_recommend_new_size(_ftfp_list *list)
{
	size_t size = (size_t)(list->end - list->begin);
	size_t capacity = (size_t)(list->end_cap - list->begin);
	return max(2 * capacity, size + 1);
}

bool	_ftfp_list_push(_ftfp_list *list, const _ftfp_list_item* token)
{
	assert(list != NULL);
	assert(token != NULL);

	if (list->end < list->end_cap)
		ft_memcpy(list->end++, token, sizeof(_ftfp_list_item));
	else
	{
		_ftfp_list new_list = { 0 };

		// alloc
		size_t	new_cap = _ftfp_list_recommend_new_size(list);
		new_list.begin = ft_calloc(new_cap, sizeof(_ftfp_list_item));
		if (!new_list.begin)
			return false;
		new_list.end_cap = new_list.begin + new_cap;

		// copy old data
		size_t old_size = (size_t)(list->end - list->begin);
		if (old_size)
			ft_memcpy(new_list.begin, list->begin, old_size * sizeof(_ftfp_list_item));
		new_list.end = new_list.begin + old_size;

		// copy new token
		ft_memcpy(new_list.end, token, sizeof(_ftfp_list_item));
		new_list.end++;

		// swap
		free(list->begin);
		*list = new_list;
	}
	return true;
}

bool	ftfp_valid(const ftfp_state* state)
{
	return state->_status == FTFP_STATUS_SUCCESS;
}

ftfp_state	ftfp_parse(const char *file, const ftfp_desc* desc)
{
	assert(file != NULL);
	assert(desc != NULL);
	
	ftfp_state  state = { 0 };
	char *line = NULL;
	int fd;
	size_t i, length, row;
	_ftfp_list list = { 0 };

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ftfp_state){ ._status = FTFP_STATUS_CANNOT_OPEN_FILE };
	row = 0;
	while (ft_get_next_line(fd, &line))
	{
		row++;
		i = 0;
		length = ft_strlen(line);
		while (i < length && _ftfp_isspace(desc, line[i]))
			i++;
		// todo: comments
		while (i < length)
		{
			bool found = false;
		
			while (i < length && _ftfp_isspace(desc, line[i]))
				i++;
			for (size_t j = 0; j < desc->token_count; j++)
			{
				size_t token_length = ft_strlen(desc->tokens[j].value);
				if (ft_strncmp(&line[i], desc->tokens[j].value, token_length) == 0)
				{
					if (!_ftfp_list_push(&list, &(_ftfp_list_item){
						.t = {
							.type = desc->tokens[j].type,
							.value = (char*)desc->tokens[j].value,
							.row = row,
							.col = i,
						},
						.length = token_length,
					}))
					{
						free(list.begin);
						state._status = FTFP_STATUS_ALLOCATION_FAILURE;
						close(fd);
						return state;
					}
					found = true;
					i += token_length;
					break ;
				}
			}
			if (!found)
			{
				size_t j = i;
				while (i < length && !_ftfp_isspace(desc, line[i]) && !_ftfp_isseparator(desc, line[i]))
					i++;
				if (j < i)
				{
					if (!_ftfp_list_push(&list, &(_ftfp_list_item){
						.t = {
							.type = -1,
							.value = &line[j],
							.row = row,
							.col = j + 1,
						},
						.length = i - j,
					}))
					{
						free(list.begin);
						state._status = FTFP_STATUS_ALLOCATION_FAILURE;
						close(fd);
						return state;
					}
				}
				// break;
			}
		}
		if (!desc->skip_newlines)
		{
			if (!_ftfp_list_push(&list, &(_ftfp_list_item){
				.t = {
					.type = -1,
					.value = "\n",
					.row = row,
					.col = i + 1,
				},
				.length = 1,
			}))
			{
				free(list.begin);
				state._status = FTFP_STATUS_ALLOCATION_FAILURE;
				close(fd);
				return state;
			}
		}
	}
	close(fd);
	
	state.count = (size_t)(list.end - list.begin);
	state.tokens = ft_calloc(state.count, sizeof(ftfp_token));
	if (!state.tokens)
	{
		free(list.begin);
		state._status = FTFP_STATUS_ALLOCATION_FAILURE;
		return state;
	}
	for (size_t i = 0; i < state.count; i++)
	{
		state.tokens[i].type = list.begin[i].t.type;
		state.tokens[i].row = list.begin[i].t.row;
		state.tokens[i].col = list.begin[i].t.col;
		state.tokens[i].value = ft_strndup(list.begin[i].t.value, list.begin[i].length);
	}
	return state;
}

void	ftfp_clear(ftfp_state* state)
{
	for (size_t i = 0; i < state->count; i++)
		free(state->tokens[i].value);
	free(state->tokens);
}
