#include "libft/libft.h"

bool	_ftap_str_isdigit(const char *str, const char **invalid)
{
	*invalid = str;
	if (!str || *str == '\0')
		return false;

	// Optional leading +/-
	if (*str == '+' || *str == '-')
		str++;

	*invalid = str;
	if (!*str) // string was just "+" or "-"
		return false;

	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			return false;
		str++;
		*invalid = str;
	}
	return true;
}

bool	_ftap_str_isfloat(const char *str, const char **invalid)
{
	*invalid = str;
	if (!str || *str == '\0')
		return false;

	// Optional leading +/-
	if (*str == '+' || *str == '-')
		str++;

	*invalid = str;
	if (!*str) // string was just "+" or "-"
		return false;

	bool seen_digit = false;
	bool seen_dot = false;
	bool seen_exp = false;

	while (*str)
	{
		if (ft_isdigit((unsigned char)*str))
		{
			seen_digit = true;
		}
		else if (*str == '.')
		{
			if (seen_dot || seen_exp) // no multiple dots, no dot after exponent
				return false;
			seen_dot = true;
		}
		else if (*str == 'e' || *str == 'E')
		{
			if (seen_exp || !seen_digit) // only one exponent, must follow digits
				return false;
			seen_exp = true;
			seen_digit = false; // require digits after 'e'
			if (*(str + 1) == '+' || *(str + 1) == '-') // allow sign after exponent
			{
				str++;
				*invalid = str;
			}
		}
		else
		{
			return false;
		}
		str++;
		*invalid = str;
	}
	return seen_digit; // must end with digit
}

void	_ftap_unrecognized_option(ftap_state* state, const ftap_desc* desc, const char *long_name)
{
	state->_status = FTAP_STATUS_UNRECOGNIZED_OPTION;
	ft_dprintf(STDERR_FILENO, "%s: unrecognized option '%s'\n", desc->program_name, long_name);
}

void	_ftap_invalid_option(ftap_state* state, const ftap_desc* desc, const char short_name)
{
	state->_status = FTAP_STATUS_INVALID_OPTION;
	ft_dprintf(STDERR_FILENO, "%s: invalid option -- '%c'\n", desc->program_name, short_name);
}

void	_ftap_invalid_option_value(ftap_state* state, const ftap_desc* desc, const char *value, const char *invalid)
{
	state->_status = FTAP_STATUS_INVALID_OPTION_VALUE;
	ft_dprintf(STDERR_FILENO, "%s: invalid value (`%s' near '%s')\n", desc->program_name, value, invalid);
}

void	_ftap_option_requires_argument(ftap_state* state, const ftap_desc* desc, size_t j, bool short_option)
{
	state->_status = FTAP_STATUS_OPTION_REQUIRES_ARGUMENT;
	if (short_option)
		ft_dprintf(STDERR_FILENO, "%s: option requires an argument -- '%c'\n", desc->program_name, desc->options[j].short_name);
	else
		ft_dprintf(STDERR_FILENO, "%s: option '--%s' requires an argument\n", desc->program_name, desc->options[j].long_name);
}

void	_ftap_too_many_arguments(ftap_state* state, const ftap_desc* desc)
{
	state->_status = FTAP_STATUS_TOO_MANY_ARGUMENTS;
	ft_dprintf(STDERR_FILENO, "%s: too many arguments\n", desc->program_name);
}

void	_ftap_get_value(ftap_state* state, const ftap_desc* desc, char **argv, int *i, size_t j, bool short_option)
{
	char* option_argument = NULL;
	const char* invalid = NULL;

	if (desc->options[j].type > FTAP_OPTION_TYPE_BOOL)
	{
		if (short_option && !desc->opt_allow_merge_short)
		{
			option_argument = &argv[*i][2];
			if (!option_argument || *option_argument == '\0')
				option_argument = argv[++(*i)];
		}
		else 
			option_argument = argv[++(*i)];
		if (!option_argument || *option_argument == '\0')
		{
			_ftap_option_requires_argument(state, desc, j, short_option);
			return ;
		}
		switch (desc->options[j].type)
		{
			case FTAP_OPTION_TYPE_STRING:
				*((char **)(desc->options[j].value)) = option_argument;
				break;
			case FTAP_OPTION_TYPE_INT:
				if (!_ftap_str_isdigit(option_argument, &invalid))
				{
					_ftap_invalid_option_value(state, desc, option_argument, invalid);
					return ;
				}
				int* value = (int *)(desc->options[j].value);
				int min = desc->options[j].min ? *((int *)(desc->options[j].min)) : FTAP_INT_MIN;
				int max = desc->options[j].max ? *((int *)(desc->options[j].max)) : FTAP_INT_MAX;

				//FIXME: we rely on libc for strtol
				long _val = strtol(option_argument, NULL, 10);

				if (_val < min)
				{
					state->_status = FTAP_STATUS_INVALID_OPTION_VALUE;
					ft_dprintf(STDERR_FILENO, "%s: option value too small: %ld\n", desc->program_name, _val);
					return ;
				}
				if (_val > max)
				{
					state->_status = FTAP_STATUS_INVALID_OPTION_VALUE;
					ft_dprintf(STDERR_FILENO, "%s: option value too big: %ld\n", desc->program_name, _val);
					return ;
				}
				*value = _val;
				break;
			case FTAP_OPTION_TYPE_FLOAT:
				if (!_ftap_str_isfloat(option_argument, &invalid))
				{
					_ftap_invalid_option_value(state, desc, option_argument, invalid);
					return ;
				}
				//FIXME: we rely on libc for atof
				*((float *)(desc->options[j].value)) = atof(option_argument);
				break;
			default:
				break;
		}
	}
}

void	_ftap_parse_long_option(ftap_state* state, char **argv, const ftap_desc* desc, int *i)
{
	bool found = false;
	const char* arg = argv[*i];

	for (size_t j = 0; j < desc->opt_count; j++)
	{
		const char *long_name = &arg[2];

		if (ft_strcmp(long_name, desc->options[j].long_name) == 0)
		{
			state->options[j].is_set = true;
			_ftap_get_value(state, desc, argv, i, j, false);
			found = true;
			break;
		}
		if (found)
			break;
	}
	if (!desc->opt_ignore_unknown && !found)
	{
		_ftap_unrecognized_option(state, desc, arg);
		return ;
	}
}

void	_ftap_parse_short_option(ftap_state* state, char **argv, const ftap_desc* desc, int *i)
{
	bool found = false;
	const char* arg = argv[*i];

	for (int k = 1; arg[k]; k++)
	{
		found = false;
		for (size_t j = 0; j < desc->opt_count; j++)
		{
			if (arg[k] == desc->options[j].short_name)
			{
				state->options[j].is_set = true;
				_ftap_get_value(state, desc, argv, i, j, true);
				found = true;
			}
		}
		if (!desc->opt_ignore_unknown && !found)
		{
			_ftap_invalid_option(state, desc, arg[k]);
			return ;
		}
		if (!desc->opt_allow_merge_short && found) // everything after the option is treated as the value of the option
			break ;
	}
}

void	_ftap_set_options_defaults(const ftap_desc* desc)
{
	for (size_t i = 0; i < desc->opt_count; i++)
	{
		assert(desc->options[i].type == FTAP_OPTION_TYPE_BOOL || desc->options[i].value != NULL);
		if (!desc->options[i].default_value)
			continue;
		switch (desc->options[i].type)
		{
			case FTAP_OPTION_TYPE_STRING:
				assert(desc->options[i].value != NULL);
				*((char **)((desc->options[i].value))) = *(char **)(desc->options[i].default_value);
				break;
			case FTAP_OPTION_TYPE_INT:
				assert(desc->options[i].value != NULL);
				*((int *)(desc->options[i].value)) = *(int *)desc->options[i].default_value;
			break;
			case FTAP_OPTION_TYPE_FLOAT:
				assert(desc->options[i].value != NULL);
				*((float *)(desc->options[i].value)) = *(float *)desc->options[i].default_value;
				break;
			default:
				break;
		}
	}
}

bool	_ftap_option_takes_argument(const ftap_desc* desc, const char *option)
{
	for (size_t i = 0; i < desc->opt_count; i++)
		if (desc->options[i].short_name == option[1] || ft_strcmp(desc->options[i].long_name, &option[2]) == 0)
			return desc->options[i].type > FTAP_OPTION_TYPE_BOOL;
	return false;
}

bool	ftap_valid(const ftap_state* state)
{
	return state->_status == FTAP_STATUS_SUCCESS;
}

ftap_state	ftap_parse(int argc, char** argv, const ftap_desc* desc)
{
	assert(desc != NULL);
	assert(desc->options != NULL || desc->opt_count == 0);

	ftap_state state = {
		.opt_count = desc->opt_count,
		.options = NULL,
		.arguments = NULL,
		._status = FTAP_STATUS_SUCCESS,
	};

	if (state.opt_count > 0)
	{
		state.options = ft_calloc(desc->opt_count, sizeof(ftap_option));
		if (!state.options)
			return (ftap_state){ ._status = FTAP_STATUS_ALLOCATION_FAILURE };
		state._status = FTAP_STATUS_SUCCESS;
		_ftap_set_options_defaults(desc);
	}

	bool parse_options = true;
	size_t arg_count = 0;
	for (int i = 1; i < argc; i++)
	{
		if (parse_options && argv[i][0] == '-')
		{
			if (ft_strcmp(argv[i], "--") == 0)
			{
				parse_options = false;
				continue;
			}
			if (argv[i][1] == '-')
				_ftap_parse_long_option(&state, argv, desc, &i);
			else
				_ftap_parse_short_option(&state, argv, desc, &i);
		}
		else
			arg_count++;
		if (state._status != FTAP_STATUS_SUCCESS)
			return state;
	}

	if (arg_count > 0)
	{
		state.arguments = ft_calloc(arg_count + 1, sizeof(char *));
		if (!state.arguments)
		{
			free(state.options);
			state.options = NULL;
			return (ftap_state){ ._status = FTAP_STATUS_ALLOCATION_FAILURE };
		}
		parse_options = true;
		int j = 0;
		for (int i = 1; i < argc; i++)
		{
			if (parse_options && argv[i][0] == '-')
			{
				if (_ftap_option_takes_argument(desc, argv[i]))
				{
					// if we allow merging short options, we need to skip the next argument
					// otherwise, we skip if the option and its argument are separated.
					// for long options, we always skip the next argument as the '=' sign is not yet supported
					if (desc->opt_allow_merge_short || argv[i][2] == '\0' || argv[i][1] == '-')
						i++;
				}
				if (ft_strcmp(argv[i], "--") == 0)
				{
					parse_options = false;
					continue;
				}
			}
			else
			{
				state.arguments[j++] = argv[i];
			}
		}
		state.arguments[j++] = NULL;
	}
	return state;
}

void	ftap_clear(ftap_state* state)
{
	free(state->options);
	free(state->arguments);
}
