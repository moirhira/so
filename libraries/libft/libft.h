

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>

char	**ft_split(char const *s, char c);
char	**free_split(char **res, size_t indx);
int ft_strlen_2d(char **str);
int	ft_strcmp(const char *s1, const char *s2);

#endif