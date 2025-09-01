#include "libft/libft.h"
#include <fcntl.h> // open

typedef struct
{
	FileParse_Token	t;
	size_t			length;
}FileParse_TokenListItem;

typedef struct
{
	FileParse_TokenListItem*	begin;
	FileParse_TokenListItem*	end;
	FileParse_TokenListItem*	end_cap;
}FileParse_TokenList;

bool	FileParse_IsSpace(const FileParse_Desc* desc, int c)
{
	if (desc->isspace)
		return desc->isspace(c);
	return ft_isspace(c);
}

bool	FileParse_IsSeparator(const FileParse_Desc* desc, int c)
{
	if (desc->isseparator)
		return desc->isseparator(c);
	return false;
}

size_t	FileParse_TokenList_RecommendNewSize(FileParse_TokenList *list)
{
	size_t size = (size_t)(list->end - list->begin);
	size_t capacity = (size_t)(list->end_cap - list->begin);
	return max(2 * capacity, size + 1);
}

bool	FileParse_TokenList_Push(FileParse_TokenList *list, const FileParse_TokenListItem* token)
{
	assert(list != NULL);
	assert(token != NULL);

	if (list->end < list->end_cap)
		ft_memcpy(list->end++, token, sizeof(FileParse_TokenListItem));
	else
	{
		FileParse_TokenList new_list = { 0 };

		// alloc
		size_t	new_cap = FileParse_TokenList_RecommendNewSize(list);
		new_list.begin = ft_calloc(new_cap, sizeof(FileParse_TokenListItem));
		if (!new_list.begin)
			return false;
		new_list.end_cap = new_list.begin + new_cap;

		// copy old data
		size_t old_size = (size_t)(list->end - list->begin);
		if (old_size)
			ft_memcpy(new_list.begin, list->begin, old_size * sizeof(FileParse_TokenListItem));
		new_list.end = new_list.begin + old_size;

		// copy new token
		ft_memcpy(new_list.end, token, sizeof(FileParse_TokenListItem));
		new_list.end++;

		// swap
		free(list->begin);
		*list = new_list;
	}
	return true;
}

bool	FileParse_IsStateValid(const FileParse_State* state)
{
	return state->_status == FileParse_Status_Success;
}

FileParse_State	FileParse_Parse(const char *file, const FileParse_Desc* desc)
{
	assert(file != NULL);
	assert(desc != NULL);
	
	FileParse_State 	state = { 0 };
	char				*line = NULL;
	int					fd;
	size_t				i, length, row;
	FileParse_TokenList	list = { 0 };

	fd = open(file, O_RDONLY);
	if (!fd)
		return (FileParse_State){ ._status = FileParse_Status_Error };
	row = 0;
	while (ft_get_next_line(fd, &line))
	{
		row++;
		i = 0;
		length = ft_strlen(line);
		while (i < length && FileParse_IsSpace(desc, line[i]))
			i++;
		// todo: comments
		while (i < length)
		{
			bool found = false;
		
			while (i < length && FileParse_IsSpace(desc, line[i]))
				i++;
			for (size_t j = 0; j < desc->token_count; j++)
			{
				size_t token_length = ft_strlen(desc->tokens[j].value);
				if (ft_strncmp(&line[i], desc->tokens[j].value, token_length) == 0)
				{
					if (!FileParse_TokenList_Push(&list, &(FileParse_TokenListItem){
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
						state._status = FileParse_Status_Error;
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
				while (i < length && !FileParse_IsSpace(desc, line[i]) && !FileParse_IsSeparator(desc, line[i]))
					i++;
				if (j < i)
				{
					if (!FileParse_TokenList_Push(&list, &(FileParse_TokenListItem){
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
						state._status = FileParse_Status_Error;
						close(fd);
						return state;
					}
				}
				break;
			}
		}
	}
	close(fd);
	
	state.count = (size_t)(list.end - list.begin);
	state.tokens = ft_calloc(state.count, sizeof(FileParse_Token));
	if (!state.tokens)
	{
		free(list.begin);
		state._status = FileParse_Status_Error;
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

void	FileParse_ClearState(FileParse_State* state)
{
	for (size_t i = 0; i < state->count; i++)
		free(state->tokens[i].value);
	free(state->tokens);
}
