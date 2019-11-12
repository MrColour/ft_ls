/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 02:22:59 by kmira             #+#    #+#             */
/*   Updated: 2019/11/11 23:00:06 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

void	short_print(t_h_output *h_output, t_inode *root)
{
	if (*h_output->flags & c_FLAG)
		buffer_output_str(root->color, 0);
	buffer_output_str(&root->file_name[root->file_loc], 0);
	if (*h_output->flags & c_FLAG)
		buffer_output_str(COLOR_RESET, 0);
	buffer_output_str("\n", 0);
}

void	print_permissions(mode_t permission)
{
	char	buff[10];

	ft_memset(buff, '-', sizeof(buff));
	buff[9] = '\0';
	if (permission & S_IRUSR)
		buff[0] = 'r';
	if (permission & S_IWUSR)
		buff[1] = 'w';
	if (permission & S_IXUSR)
		buff[2] = 'x';
	if (permission & S_IRGRP)
		buff[3] = 'r';
	if (permission & S_IWGRP)
		buff[4] = 'w';
	if (permission & S_IXGRP)
		buff[5] = 'x';
	if (permission & S_IROTH)
		buff[6] = 'r';
	if (permission & S_IWOTH)
		buff[7] = 'w';
	if (permission & S_IXOTH)
		buff[8] = 'x';
	buffer_output_str(buff, 0);
}

void	long_print(t_h_output *h_output, t_inode *root)
{
	char			*real_path;

	if (*h_output->flags & c_FLAG)
		buffer_output_str(root->color, 0);
	buffer_output_str(root->type_letter, 0);
	print_permissions(root->stat_info.st_mode);
	print_links(root->nlinks, h_output->longest_nlinks + 2);
	print_pw_and_gr_names(root->pw_name, root->gr_name, h_output);
	print_size(root->size, h_output->longest_size + 2);
	print_time(&root->stat_info.st_mtimespec);
	buffer_output_str(" ", 0);
	buffer_output_str(&root->file_name[root->file_loc], 0);
	if (root->type & SYM_LINK)
	{
		buffer_output_str(" -> ", 0);
		real_path = ft_strnew(30);
		readlink(root->file_name, real_path, 30);
		buffer_output_str(real_path, 0);
	}
	if (*h_output->flags & c_FLAG)
		buffer_output_str(COLOR_RESET, 0);
	buffer_output_str("\n", 0);
}

void	print_tree(t_inode *root)
{
	if (root == NULL)
		return ;
	if (root->left != NULL)
		print_tree(root->left);
	if (root->right != NULL)
		print_tree(root->right);
}

void	print_tree_type(t_inode *root, t_h_output *h_output,
						t_inode_type mask)
{
	if (root == NULL)
		return ;
	if (root->left != NULL)
		print_tree_type(root->left, h_output, mask);
	if (root->type & mask)
	{
		if (*h_output->flags & l_FLAG && !(root->type & BAD_FILE))
			long_print(h_output, root);
		else
			short_print(h_output, root);
		h_output->only_dir = 0;
		h_output->newline = 1;
	}
	if (root->right != NULL)
		print_tree_type(root->right, h_output, mask);
}