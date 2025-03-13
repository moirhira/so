/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:55:19 by moirhira          #+#    #+#             */
/*   Updated: 2024/11/03 12:17:46 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ctrword(char const *s, char c)
{
	size_t	wordctr;
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	wordctr = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || c == s[i - 1]))
			wordctr++;
		i++;
	}
	return (wordctr);
}

// Allocate Memory for the Array of Substrings
static char	*ft_memalloc(char const *s, size_t len)
{
	size_t		i;
	char		*ptr;

	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[len] = '\0';
	return (ptr);
}

static char	*copy_word(const char **s, char c)
{
	const char	*start;
	size_t		len;

	start = *s;
	len = 0;
	while (**s && **s != c)
	{
		len++;
		(*s)++;
	}
	return (ft_memalloc(start, len));
}

char	**free_split(char **res, size_t indx)
{
	while (indx > 0)
	{
		free(res[--indx]);
	}
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	i;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (ft_ctrword(s, c) + 1));
	if (!res)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			res[i] = copy_word(&s, c);
			if (!res[i])
				return (free_split(res, i));
			i++;
		}
	}
	res[i] = NULL;
	return (res);
}
// int main()
// {
//     char str[] = "Hello, how are you?";
//     char **words = ft_split(str, ' ');
//     for (int i = 0; words[i] != NULL; i++)
//     {
//         printf("%s\n", words[i]);
//         free(words[i]); // Free each allocated substring
//     }
//     free(words); // Free the array of pointers
//     return 0;
// }
// int ft_ctrword(char const *s, char c)
// {
//     size_t wordctr = 0;
//     int in_word = 0;
//     size_t i = 0;
//     if (s == NULL)
//         return 0;
//     while (s[i] != '\0')
//     {
//         if (s[i] != c && in_word == 0) // Start of a new word
//         {
//             wordctr++;
//             in_word = 1; // Now inside a word
//         }
//         else if (s[i] == c) // End of a word
//         {
//             in_word = 0;
//         }
//         i++;
//     }
//     return wordctr;
// }
