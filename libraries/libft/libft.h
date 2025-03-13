/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:44:44 by moirhira          #+#    #+#             */
/*   Updated: 2025/03/13 11:44:46 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

char	**ft_split(char const *s, char c);
char	**free_split(char **res, size_t indx);
int		ft_strlen_2d(char **str);
int		ft_strcmp(const char *s1, const char *s2);

#endif
