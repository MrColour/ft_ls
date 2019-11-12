/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 22:43:32 by kmira             #+#    #+#             */
/*   Updated: 2019/11/11 22:58:32 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

void	print_total_blocks(int total)
{
	char	*number;

	number = ft_itoa(total);
	buffer_output_str("total ", 0);
	buffer_output_str(number, 0);
	buffer_output_str("\n", 0);
	free(number);
}

#define SIX_MONTHS (15778463)

void	print_time(struct timespec *time_stamp)
{
	char	time_string[26];

	time_string[0] = ' ';
	ft_strncpy(&time_string[1], ctime(&time_stamp->tv_sec) + 4, 7);
	if (time_stamp->tv_sec < time(0) - SIX_MONTHS ||
		time_stamp->tv_sec > time(0) + SIX_MONTHS)
		ft_strncpy(time_string + 8, ctime(&time_stamp->tv_sec) + 19, 5);
	else
		ft_strncpy(time_string + 8, ctime(&time_stamp->tv_sec) + 11, 5);
	time_string[13] = '\0';
	buffer_output_str(time_string, 0);
}

void	print_pw_and_gr_names(char *pw_name, char *gr_name, t_h_output *h_output)
{
	int padd;

	buffer_output_str(" ", 0);
	padd = h_output->longest_pw_name - ft_strlen(pw_name);
	buffer_output_str(pw_name, 0);
	padd_string(padd + 2);
	padd = h_output->longest_gr_name - ft_strlen(gr_name);
	buffer_output_str(gr_name, 0);
	padd_string(padd + 1);
}

void	print_links(char *nlinks, int longest)
{
	int	padd;

	padd = longest - ft_strlen(nlinks);
	padd_string(padd);
	buffer_output_str(nlinks, 0);
}

void	print_size(char *size, int longest)
{
	int	padd;

	padd = longest - ft_strlen(size);
	padd_string(padd);
	buffer_output_str(size, 0);
}

void	print_directory_header(t_inode *directory, t_h_output *h_output)
{
	if (h_output->newline == 1)
		buffer_output_str("\n", 0);
	else
		h_output->newline = 1;
	if (h_output->only_dir == 0)
	{
		if (*h_output->flags & c_FLAG)
			buffer_output_str(directory->color, 0);
		buffer_output_str(directory->file_name, 0);
		if (*h_output->flags & c_FLAG)
			buffer_output_str(COLOR_RESET, 0);
		buffer_output_str(":\n", 0);
	}
}
