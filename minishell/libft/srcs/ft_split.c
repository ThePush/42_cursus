/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaccagn <dpaccagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:21:58 by dpaccagn          #+#    #+#             */
/*   Updated: 2021/11/29 18:49:39 by dpaccagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countwords(const char *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

/* **************************************************************************
The countwords function counts each word in the original string.
Incrementing i as long as it's a charset, when i encounters a letter it will
count a word, increment as long as it's a character/charset, rinse/repeat
until i encounters the end of the string taken as a parameter.
°************************************************************************** */

static size_t	ft_wordlen(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

/* **************************************************************************
Wordlen is called in fillwords.and gives the size of each words to fill.
°************************************************************************** */

static char	**ft_freemem(char **new, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free (new[i]);
		i++;
	}
	free (new);
	return (NULL);
}

/* **************************************************************************
Typical function to free all allocated memory
°************************************************************************** */

static char	**ft_fillwords(char **new, const char *str, char c, size_t count)
{
	size_t	words;
	size_t	len;
	size_t	i;

	i = 0;
	words = 0;
	while (words < count)
	{
		while (str[i] == c)
			i++;
		len = ft_wordlen(str + i, c);
		new[words] = ft_substr(str, i, len);
		if (!new[words])
			return (ft_freemem(new, words));
		while (str[i] && str[i] != c)
			i++;
		words++;
	}
	new[words] = NULL;
	return (new);
}

/* **************************************************************************
Fillwords does what it says. The wordcount starts from zero and functions
while the count is not reached. It then creates a string mallocced with
ft_substr, with the right size and fills it with the right words.
°************************************************************************** */

char	**ft_split(const char *str, char c)
{
	size_t	count;
	char	**new;

	if (!str)
		return (NULL);
	count = ft_countwords(str, c);
	new = malloc ((count + 1) * sizeof(*new));
	if (!new)
		return (NULL);
	return (ft_fillwords(new, str, c, count));
}

/* **************************************************************************
The function split takes a string and splits it with charset taken as a para
meter into an array of strings.
The first stage is to malloc the right size for the array of strings.
When done, all the strings are filled with the source words from the original
string
°************************************************************************** */
