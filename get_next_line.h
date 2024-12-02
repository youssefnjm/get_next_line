/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-28 11:10:53 by ynoujoum          #+#    #+#             */
/*   Updated: 2024-11-28 11:10:53 by ynoujoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <unistd.h>
# include <stdlib.h>

int		check_new_line(char	*str);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
void	ft_strcpy(char	*dest, char	*src);
char	*get_next_line(int fd);

#endif