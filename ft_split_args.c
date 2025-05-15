#include <stdlib.h>
#include "pipex.h"

int	is_delim(char c, char delim)
{
	return (c == delim);
}

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static void	toggle_quote(int *in_q, char *quote, char c)
{
	if (!(*in_q))
	{
		*in_q = 1;
		*quote = c;
	}
	else if (*quote == c)
		*in_q = 0;
}

static int	count_args(const char *s, char delim)
{
	int	count;
	int	in_q;
	char	quote;

	count = 0;
	in_q = 0;
	while (*s)
	{
		while (*s && is_delim(*s, delim))
			s++;
		if (*s)
			count++;
		while (*s && (!is_delim(*s, delim) || in_q))
		{
			if (is_quote(*s))
				toggle_quote(&in_q, &quote, *s);
			s++;
		}
	}
	return (count);
}

static int	get_arg_len(const char *s, char delim)
{
	int	len;
	int	in_q;
	char	quote;

	len = 0;
	in_q = 0;
	while (*s && (!is_delim(*s, delim) || in_q))
	{
		if (is_quote(*s))
		{
			toggle_quote(&in_q, &quote, *s);
			s++;
		}
		else
		{
			len++;
			s++;
		}
	}
	return (len);
}

static char	*extract_arg(const char **s, char delim)
{
	char	*arg;
	int	len;
	int	in_q;
	int	i;
	char	quote;

	while (**s && is_delim(**s, delim))
		(*s)++;
	len = get_arg_len(*s, delim);
	arg = malloc(len + 1);
	if (!arg)
		return (NULL);
	in_q = 0;
	i = 0;
	while (i < len)
	{
		if (is_quote(**s))
		{
			toggle_quote(&in_q, &quote, **s);
			(*s)++;
		}
		else
		{
			arg[i] = **s;
			(*s)++;
			i++;
		}
	}
	arg[i] = '\0';
	return (arg);
}

char	**ft_split_args(const char *s, char delim)
{
	char	**args;
	int		i;
	int		count;

	if (!s)
		return (NULL);
	count = count_args(s, delim);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (*s && i < count)
	{
		args[i] = extract_arg(&s, delim);
		if (!args[i])
		{
			ft_free_split(args);
			return (NULL);
		}
		i++;
	}
	args[i] = NULL;
	return (args);
}