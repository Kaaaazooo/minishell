/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:09:13 by sabrugie          #+#    #+#             */
/*   Updated: 2021/09/30 19:08:57 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_size(t_line_char *marked, uint16_t flag)
{
	int			i;
	int			j;
	uint16_t	init_flag;

	i = 0;
	j = 0;
	init_flag = marked[i].flag;
	while (marked[i].c && init_flag & marked[i].flag)
	{
		if (marked[i].flag & flag || (flag == 0 && marked[i].flag == flag))
			++j;
		++i;
	}
	while (marked[i].c && init_flag ^ marked[i].flag)
	{
		if (marked[i].flag & flag || (flag == 0 && marked[i].flag == 0))
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

void	fill_if_flag(t_line_char *dst, t_line_char *marked, uint16_t flag)
{
	int			i;
	int			j;
	uint16_t	init_flag;

	i = 0;
	j = 0;
	init_flag = marked[i].flag;
	while (marked[i].c && init_flag & marked[i].flag)
	{
		if (marked[i].flag & flag || (flag == 0 && marked[i].flag == flag))
		{
			dst[j].c = marked[i].c;
			dst[j++].flag = marked[i].flag;
		}
		++i;
	}
	while (marked[i].c && init_flag ^ marked[i].flag)
	{
		if (marked[i].flag & flag || (flag == 0 && marked[i].flag == flag))
		{
			dst[j].c = marked[i].c;
			dst[j++].flag = marked[i].flag;
		}
		++i;
	}
}

int	new_lstr(t_lstr *dst, t_line_char **marked)
{
	dst->lstr = ft_calloc(token_size(*marked, 0) + 1,
			sizeof(t_line_char));
	if (dst->lstr == NULL)
		return (-1);
	fill_if_flag(dst->lstr, *marked, 0);
	dst->control = ft_calloc(token_size(*marked, M_CONTROL) + 1,
			sizeof(t_line_char));
	if (dst->control == NULL)
	{
		free(dst->lstr);
		return (-1);
	}
	fill_if_flag(dst->control, *marked, M_CONTROL);

	printf("marked : [");
	for (int i = 0; (*marked)[i].c; i++)
		printf("%c", (*marked)[i].c);
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
		if (new_lstr(&cmd[i++], &marked))
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
