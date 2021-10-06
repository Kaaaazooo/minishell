/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:09:13 by sabrugie          #+#    #+#             */
/*   Updated: 2021/10/06 16:06:54 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_size(t_line_char *l, uint16_t flag)
{
	int			i;
	int			j;
	uint16_t	s_flag;

	i = 0;
	j = 0;
	s_flag = l[i].flag;
	while (l[i].c && (s_flag & l[i].flag || (s_flag == 0 && l[i].flag == 0)))
	{
		if (l[i].flag & flag || (flag == 0 && l[i].flag == flag))
			++j;
		++i;
	}
	while (l[i].c && (s_flag ^ l[i].flag || (s_flag == 0 && l[i].flag == 0)))
	{
		if (l[i].flag & flag || (flag == 0 && l[i].flag == 0))
			++j;
		++i;
	}
	return (j);
}

int	count_tokens(t_line_char *marked)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (marked[i].c)
	{
		if (marked[i].c == '|' && marked[i].flag)
			++j;
		++i;
	}
	return (j);
}

void	fill_if_flag(t_line_char **dst, t_line_char *l, uint16_t flag)
{
	int			i;
	int			j;
	uint16_t	s_flag;

	i = 0;
	j = 0;
	s_flag = l[i].flag;
	printf("s_flag = %d\n", s_flag);
	printf("l.flag = %d\n", l[i].flag);
	while (l[i].c && (s_flag & l[i].flag || (s_flag == 0 && l[i].flag == 0)))
	{
		printf("1: fill[%d] = [%c] | %d\n", i, l[i].c, l[i].flag);
		if (l[i].flag & flag || (flag == 0 && l[i].flag == 0))
		{
			(*dst)[j].c = l[i].c;
			(*dst)[j++].flag = l[i].flag;
		}
		++i;
	}
	while (l[i].c && (s_flag ^ l[i].flag || (s_flag == 0 && l[i].flag == 0)))
	{
		printf("2: fill[%d] = [%c] | %d\n", i, l[i].c, l[i].flag);
		if (l[i].flag & flag || (flag == 0 && l[i].flag == 0))
		{
			(*dst)[j].c = l[i].c;
			(*dst)[j++].flag = l[i].flag;
		}
		++i;
	}
}

int	new_lstr(t_lstr *dst, t_line_char **marked)
{
	dst->lstr = ft_calloc(token_size(*marked, !M_CONTROL) + 1,
			sizeof(t_line_char));
	if (dst->lstr == NULL)
		return (-1);
	dst->control = ft_calloc(token_size(*marked, M_CONTROL) + 1,
			sizeof(t_line_char));
	if (dst->control == NULL)
	{
		free(dst->lstr);
		return (-1);
	}
	fill_if_flag(&(dst->lstr), *marked, 0);
	fill_if_flag(&(dst->control), *marked, M_CONTROL);

	printf("marked lstr : [");
	for (int i = 0; dst->lstr[i].c; i++)
		printf("dst[%d] = [%c] | %d\n",
				i, dst->lstr[i].c, (*dst).lstr[i].flag);
	printf("]\nmarked control : [");
	for (int i = 0; dst->control[i].c; i++)
		printf("dst[%d] = [%c] | %d\n",
				i, dst->control[i].c, (*dst).control[i].flag);
	printf("]\n\nsize 512\t= %d\n", token_size(*marked, M_CONTROL));
	printf("size %u\t\t= %d\n", 0, token_size(*marked, 0));

	*marked += token_size(*marked, 0) + token_size(*marked, M_CONTROL);
	return (0);
}

t_lstr	*trim_redir(t_line_char *marked)
{
	int		i;
	int		token_nb;
	t_lstr	*cmd;

	i = 0;
	token_nb = count_tokens(marked);
	cmd = ft_calloc(token_nb + 1, sizeof(t_lstr));
	while (i < token_nb)
		if (new_lstr(&(cmd[i++]), &marked))
			exit(0);

	for (int i = 0; cmd[i].lstr; i++)
	{
		for (int j = 0; cmd[i].lstr[j].c; j++)
			printf("cmd[%d][%d] = [%c] | %d\n",
				i, j, cmd[i].lstr[j].c, cmd[i].lstr[j].flag);
		printf("\n");
		for (int k = 0; cmd[i].lstr[k].c; k++)
			printf("cmd[%d][%d] = [%c] | %d\n",
				i, k, cmd[i].control[k].c, cmd[i].control[k].flag);
		printf("\n");
		printf("\n");
	}
	printf("token\t\t= %d\n", count_tokens(marked));

	return (cmd);
}
