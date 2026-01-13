#include "libft/libft.h"
#include "libft/iterator.h"

bool _ftfp_isspace(const ftfp_desc* desc, int c)
{
	if (desc->isspace)
		return desc->isspace(c);
	return ft_isspace(c);
}

bool _ftfp_isseparator(const ftfp_desc* desc, int c)
{
	if (desc->isseparator)
		return desc->isseparator(c);
	return false;
}

void	_ftftp_token_construct(const ft_allocator* alloc, void *p, const void* value)
{
	(void)alloc;
	ftfp_token* token = (ftfp_token*)p;
	const ftfp_token* value_token = (const ftfp_token*)value;

	token->type = value_token->type;
	token->row = value_token->row;
	token->col = value_token->col;
	token->value = ft_strdup(value_token->value);
}

void	_ftftp_token_destroy(const ft_allocator* alloc, void *p)
{
	(void)alloc;
	free(((ftfp_token*)p)->value);
}

bool ftfp_valid(const ftfp_state* state)
{
	return state->_status == FTFP_STATUS_SUCCESS;
}

ftfp_state	ftfp_parse(const char *file, const ftfp_desc* desc)
{
	assert(file != NULL);
	assert(desc != NULL);
	
	ftfp_state state = { 0 };
	char *line = NULL;
	int fd;
	size_t i, length, row;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ftfp_state){ ._status = FTFP_STATUS_CANNOT_OPEN_FILE };
	state.tokens = ftv_create(&(ftv_desc){
		.alloc = (ft_allocator){
			.sizeof_type = sizeof(ftfp_token),
			.construct = _ftftp_token_construct,
			.destroy = _ftftp_token_destroy,
		},
	});
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
					char v[token_length + 1];
					ft_memcpy(v, &line[i], token_length);
					v[token_length] = '\0';
					ftv_push_back(&state.tokens, (ftfp_token){
						.type = desc->tokens[j].type,
						.value = v,
						.row = row,
						.col = i + 1,
					});
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
					char v[i - j + 1];
					ft_memcpy(v, &line[j], i - j);
					v[i - j] = '\0';
					ftv_push_back(&state.tokens, (ftfp_token){
						.type = -1,
						.value = v,
						.row = row,
						.col = j + 1,
					});
				}
				// break;
			}
		}
		if (!desc->skip_newlines)
		{
			ftv_push_back(&state.tokens, (ftfp_token){
				.type = -1,
				.value = "\n",
				.row = row,
				.col = length + 1,
			});
		}
		free(line);
		line = NULL;
	}
	free(line);
	close(fd);

	state._status = FTFP_STATUS_SUCCESS;
	return state;
}

void	ftfp_clear(ftfp_state* state)
{
	ftv_destroy(&state->tokens);
}
