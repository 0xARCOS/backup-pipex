#include <stdlib.h>
#include <unistd.h>
#include "pipex.h"

static int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

static int count_args(const char *s)
{
    int count = 0;
    int in_quotes = 0;
    char quote_char = 0;

    while (*s)
    {
        while(is_space(*s))
            s++;
        if (!*s)
            break;
        count++;
        while (*s && (!is_space(*s) || in_quotes))
        {
            if ((*s == '\'' || *s == '"'))
            {
                if (!in_quotes)
                {
                    in_quotes = 1;
                    quote_char = *s;
                }
                else if (quote_char == *s)
                    in_quotes = 0;
            }
            s++;
        }
    }
    return (count);
}

static char	*extract_arg(const char **s)
{
	char	*arg;
	int		len = 0;
	int		in_quotes = 0;
	char	quote_char = 0;
	const char *start = *s;

	while (*start && is_space(*start))
		start++;

	const char *p = start;
	while (*p && (!is_space(*p) || in_quotes))
	{
		if ((*p == '\'' || *p == '"'))
		{
			if (!in_quotes)
			{
				in_quotes = 1;
				quote_char = *p;
			}
			else if (quote_char == *p)
				in_quotes = 0;
		}
		p++;
		len++;
	}

	arg = malloc(len + 1);
	if (!arg)
		return (NULL);

	int i = 0;
	in_quotes = 0;
	while (*start && (!is_space(*start) || in_quotes))
	{
		if ((*start == '\'' || *start == '"'))
		{
			if (!in_quotes)
			{
				in_quotes = 1;
				quote_char = *start;
			}
			else if (quote_char == *start)
				in_quotes = 0;
			start++;
			continue;
		}
		arg[i++] = *start++;
	}
	arg[i] = '\0';
	*s = start;
	return (arg);
}

char	**ft_split_args(const char *s)
{
	int		count;
	char	**args;
	int		i = 0;

	count = count_args(s);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);

	while (*s && i < count)
	{
		while (is_space(*s))
			s++;
		args[i] = extract_arg(&s);
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
