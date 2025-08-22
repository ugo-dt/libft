#include "libft.h"
#include <stdlib.h> // strtol, atof - FIXME: don't rely on libc

LIBFT_BOOL	_ArgParse_StringIsDigit(const char *str, const char **invalid)
{
	*invalid = str;
	if (!str || *str == '\0')
		return LIBFT_FALSE;

	// Optional leading +/-
	if (*str == '+' || *str == '-')
		str++;

	*invalid = str;
	if (!*str) // string was just "+" or "-"
		return LIBFT_FALSE;

	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			return LIBFT_FALSE;
		str++;
		*invalid = str;
	}
	return LIBFT_TRUE;
}

LIBFT_BOOL	_ArgParse_StringIsFloat(const char *str, const char **invalid)
{
	*invalid = str;
	if (!str || *str == '\0')
		return LIBFT_FALSE;

	// Optional leading +/-
	if (*str == '+' || *str == '-')
		str++;

	*invalid = str;
	if (!*str) // string was just "+" or "-"
		return LIBFT_FALSE;

	LIBFT_BOOL seen_digit = LIBFT_FALSE;
	LIBFT_BOOL seen_dot = LIBFT_FALSE;
	LIBFT_BOOL seen_exp = LIBFT_FALSE;

	while (*str)
	{
		if (ft_isdigit((unsigned char)*str))
		{
			seen_digit = LIBFT_TRUE;
		}
		else if (*str == '.')
		{
			if (seen_dot || seen_exp) // no multiple dots, no dot after exponent
				return LIBFT_FALSE;
			seen_dot = LIBFT_TRUE;
		}
		else if (*str == 'e' || *str == 'E')
		{
			if (seen_exp || !seen_digit) // only one exponent, must follow digits
				return LIBFT_FALSE;
			seen_exp = LIBFT_TRUE;
			seen_digit = LIBFT_FALSE; // require digits after 'e'
			if (*(str + 1) == '+' || *(str + 1) == '-') // allow sign after exponent
			{
				str++;
				*invalid = str;
			}
		}
		else
		{
			return LIBFT_FALSE;
		}
		str++;
		*invalid = str;
	}
	return seen_digit; // must end with digit
}

void	_ArgParse_UnrecognizedOption(ArgParse_State* state, const ArgParse_Desc* desc, const char *long_name)
{
	state->_status = ArgParse_Status_UnrecognizedOption;
	ft_dprintf(STDERR_FILENO, "%s: unrecognized option '%s'\n", desc->program_name, long_name);
}

void	_ArgParse_InvalidOption(ArgParse_State* state, const ArgParse_Desc* desc, const char short_name)
{
	state->_status = ArgParse_Status_InvalidOption;
	ft_dprintf(STDERR_FILENO, "%s: invalid option -- '%c'\n", desc->program_name, short_name);
}

void	_ArgParse_OptionInvalidValue(ArgParse_State* state, const ArgParse_Desc* desc, const char *value, const char *invalid)
{
	state->_status = ArgParse_Status_OptionInvalidValue;
	ft_dprintf(STDERR_FILENO, "%s: invalid value (`%s' near '%s')\n", desc->program_name, value, invalid);
}

void	_ArgParse_OptionRequiresAnArgument(ArgParse_State* state, const ArgParse_Desc* desc, size_t j, LIBFT_BOOL short_option)
{
	state->_status = ArgParse_Status_OptionRequiresAnArgument;
	if (short_option)
		ft_dprintf(STDERR_FILENO, "%s: option requires an argument -- '%c'\n", desc->program_name, desc->options[j].short_name);
	else
		ft_dprintf(STDERR_FILENO, "%s: option '--%s' requires an argument\n", desc->program_name, desc->options[j].long_name);
}

void	_ArgParse_TooManyArguments(ArgParse_State* state, const ArgParse_Desc* desc)
{
	state->_status = ArgParse_Status_TooManyArguments;
	ft_dprintf(STDERR_FILENO, "%s: too many arguments\n", desc->program_name);
}

void	_ArgParse_GetValue(ArgParse_State* state, const ArgParse_Desc* desc, char **argv, int *i, size_t j, LIBFT_BOOL short_option)
{
	char* option_argument = NULL;
	const char* invalid = NULL;

	if (desc->options[j].type > ArgParse_OptionType_Bool)
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
			_ArgParse_OptionRequiresAnArgument(state, desc, j, short_option);
			return ;
		}
		switch (desc->options[j].type)
		{
			case ArgParse_OptionType_String:
				*((char **)(desc->options[j].value)) = option_argument;
				break;
			case ArgParse_OptionType_Int:
				if (!_ArgParse_StringIsDigit(option_argument, &invalid))
				{
					_ArgParse_OptionInvalidValue(state, desc, option_argument, invalid);
					return ;
				}
				int* value = (int *)(desc->options[j].value);
				int min = desc->options[j].min ? *((int *)(desc->options[j].min)) : ARGPARSE_INT_MIN;
				int max = desc->options[j].max ? *((int *)(desc->options[j].max)) : ARGPARSE_INT_MAX;

				//FIXME: we rely on libc for strtol
				long _val = strtol(option_argument, NULL, 10);

				if (_val < min)
				{
					state->_status = ArgParse_Status_OptionInvalidValue;
					ft_dprintf(STDERR_FILENO, "%s: option value too small: %ld\n", desc->program_name, _val);
					return ;
				}
				if (_val > max)
				{
					state->_status = ArgParse_Status_OptionInvalidValue;
					ft_dprintf(STDERR_FILENO, "%s: option value too big: %ld\n", desc->program_name, _val);
					return ;
				}
				*value = _val;
				break;
			case ArgParse_OptionType_Float:
				if (!_ArgParse_StringIsFloat(option_argument, &invalid))
				{
					_ArgParse_OptionInvalidValue(state, desc, option_argument, invalid);
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

void	_ArgParse_ParseLongOption(ArgParse_State* state, char **argv, const ArgParse_Desc* desc, int *i)
{
	LIBFT_BOOL	found = LIBFT_FALSE;
	const char *arg = argv[*i];

	for (size_t j = 0; j < desc->opt_count; j++)
	{
		const char *long_name = &arg[2];

		if (ft_strcmp(long_name, desc->options[j].long_name) == 0)
		{
			state->options[j].is_set = LIBFT_TRUE;
			_ArgParse_GetValue(state, desc, argv, i, j, LIBFT_FALSE);
			found = LIBFT_TRUE;
			break;
		}
		if (found)
			break;
	}
	if (!desc->opt_ignore_unknown && !found)
	{
		_ArgParse_UnrecognizedOption(state, desc, arg);
		return ;
	}
}

void	_ArgParse_ParseShortOption(ArgParse_State* state, char **argv, const ArgParse_Desc* desc, int *i)
{
	LIBFT_BOOL	found = LIBFT_FALSE;
	const char *arg = argv[*i];

	for (int k = 1; arg[k]; k++)
	{
		found = LIBFT_FALSE;
		for (size_t j = 0; j < desc->opt_count; j++)
		{
			if (arg[k] == desc->options[j].short_name)
			{
				state->options[j].is_set = LIBFT_TRUE;
				_ArgParse_GetValue(state, desc, argv, i, j, LIBFT_TRUE);
				found = LIBFT_TRUE;
			}
		}
		if (!desc->opt_ignore_unknown && !found)
		{
			_ArgParse_InvalidOption(state, desc, arg[k]);
			return ;
		}
		if (!desc->opt_allow_merge_short && found) // everything after the option is treated as the value of the option
			break ;
	}
}

void	_ArgParse_SetOptionsDefaultValues(const ArgParse_Desc* desc)
{
	for (size_t i = 0; i < desc->opt_count; i++)
	{
		assert(desc->options[i].type == ArgParse_OptionType_Bool || desc->options[i].value != NULL);
		if (!desc->options[i].default_value)
			continue;
		switch (desc->options[i].type)
		{
			case ArgParse_OptionType_String:
				assert(desc->options[i].value != NULL);
				*((char **)((desc->options[i].value))) = *(char **)(desc->options[i].default_value);
				break;
			case ArgParse_OptionType_Int:
				assert(desc->options[i].value != NULL);
				*((int *)(desc->options[i].value)) = *(int *)desc->options[i].default_value;
			break;
			case ArgParse_OptionType_Float:
				assert(desc->options[i].value != NULL);
				*((float *)(desc->options[i].value)) = *(float *)desc->options[i].default_value;
				break;
			default:
				break;
		}
	}
}

LIBFT_BOOL	_ArgParse_OptionTakesArgument(const ArgParse_Desc* desc, const char *option)
{
	for (size_t i = 0; i < desc->opt_count; i++)
		if (desc->options[i].short_name == option[1] || strcmp(desc->options[i].long_name, &option[2]) == 0)
			return desc->options[i].type > ArgParse_OptionType_Bool;
	return LIBFT_FALSE;
}

LIBFT_BOOL	ArgParse_IsStateValid(const ArgParse_State* state)
{
	return state->_status == ArgParse_Status_Success;
}

ArgParse_State	ArgParse_Parse(int argc, char** argv, const ArgParse_Desc* desc)
{
	assert(desc != NULL);
	assert(desc->options != NULL || desc->opt_count == 0);

	ArgParse_State state = {
		.opt_count = desc->opt_count,
		.options = NULL,
		.arguments = NULL,
		._status = ArgParse_Status_Success,
	};

	if (state.opt_count > 0)
	{
		state.options = ft_calloc(desc->opt_count, sizeof(ArgParse_Option));
		if (!state.options)
			return (ArgParse_State){ ._status = ArgParse_Status_AllocationError };
		state._status = ArgParse_Status_Success;
		_ArgParse_SetOptionsDefaultValues(desc);
	}

	LIBFT_BOOL parse_options = LIBFT_TRUE;
	size_t arg_count = 0;
	for (int i = 1; i < argc; i++)
	{
		if (parse_options && argv[i][0] == '-')
		{
			if (ft_strcmp(argv[i], "--") == 0)
			{
				parse_options = LIBFT_FALSE;
				continue;
			}
			if (argv[i][1] == '-')
				_ArgParse_ParseLongOption(&state, argv, desc, &i);
			else
				_ArgParse_ParseShortOption(&state, argv, desc, &i);
		}
		else
			arg_count++;
		if (state._status != ArgParse_Status_Success)
			return state;
	}

	if (arg_count > 0)
	{
		state.arguments = ft_calloc(arg_count + 1, sizeof(char *));
		if (!state.arguments)
		{
			LIBFT_FREE(state.options);
			state.options = NULL;
			return (ArgParse_State){ ._status = ArgParse_Status_AllocationError };
		}
		parse_options = LIBFT_TRUE;
		int j = 0;
		for (int i = 1; i < argc; i++)
		{
			if (parse_options && argv[i][0] == '-')
			{
				if (_ArgParse_OptionTakesArgument(desc, argv[i]))
				{
					// if we allow merging short options, we need to skip the next argument
					// otherwise, we skip if the option and its argument are separated.
					// for long options, we always skip the next argument as the '=' sign is not yet supported
					if (desc->opt_allow_merge_short || argv[i][2] == '\0' || argv[i][1] == '-')
						i++;
				}
				if (ft_strcmp(argv[i], "--") == 0)
				{
					parse_options = LIBFT_FALSE;
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

void	ArgParse_ClearState(ArgParse_State* state)
{
	LIBFT_FREE(state->options);
	LIBFT_FREE(state->arguments);
}
