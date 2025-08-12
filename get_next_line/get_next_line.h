/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:26:36 by dimatayi          #+#    #+#             */
/*   Updated: 2025/08/12 15:52:58 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# define MAX_FD 1024

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*first_line(int fd, char *buffer);
char	*next_line(char *buffer);
char	*last_line(char *buffer);
char	*fill_line(char *buffer, int i);
int		ft_find_char(char *s, int c);
void	*ft_calloc(size_t elem, size_t size);
int		ft_strlen(const char *s);
char	*gnl_strjoin(const char *s1, const char *s2);
char	*free_me(char *str);

#endif
