/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:08:51 by llai              #+#    #+#             */
/*   Updated: 2024/03/19 21:34:44 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_node(t_list *tk_list)
{
	t_token	*data;

	while (tk_list != NULL)
	{
		data = (t_token *)tk_list->content;
		printf("type: %d\n", data->type);
		printf("data: %s\n", data->data);
		tk_list = tk_list->next;
	}
}

// void	print_tree(t_ast *ast)
// {
// 	printf("TREE\n");
// 	printf("Type: %d\n", ast->type);
// 	printf("Data: %s\n", ast->data);
// 	if (ast->left != NULL)
// 	{
// 		printf("left Type: %d\n", ast->left->type);
// 		printf("left Data: %s\n", ast->left->data);
// 	}
// 	if (ast->right != NULL)
// 	{
// 		printf("right Type: %d\n", ast->right->type);
// 		printf("right Data: %s\n", ast->right->data);
// 	}
// 	if (ast->right->right != NULL)
// 	{
// 		printf("right right Type: %d\n", ast->right->right->type);
// 		printf("right right Data: %s\n", ast->right->right->data);
// 	}
// }
void printTreeUtil(t_ast* root, int depth) {
    if (root == NULL) {
        return;
    }

    // Print the current node
    printf("%*sType: %d, Data: %s\n", depth * 4, "", root->type, root->data);

    // Print the left subtree
    printf("%*s\\--Left:\n", depth * 4, "");
    printTreeUtil(root->left, depth + 1);

    // Print the right subtree
    printf("%*s\\--Right:\n", depth * 4, "");
    printTreeUtil(root->right, depth + 1);
}

void printTree(t_ast* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }

    printf("Root:\n");
    printTreeUtil(root, 1);
}

void	init_data(t_data *data)
{
	data->inputString = NULL;
	data->tk_list = NULL;
	data->ast = NULL;
	data->cur_token = NULL;
}

int main()
{
	t_data	data;
	// char	*inputString;
	// t_list	*tk_list = NULL;
	// t_ASTNode	*exectree;

	init_data(&data);
	ignore_control_key();
	while (1)
	{
		// printDir();
		if (takeInput(&data))
			continue;
		// printf("%s\n", inputString);
		tokenize(&data);
		print_node(data.tk_list);
		// parse(tk_list, &exectree);
		parse(&data);
		printTree(data.ast);
		astNodeDelete(data.ast);
		ft_lstclear(&(data.tk_list), free);
		// printf("%s\n", (char *)tk_list->content);

		// ft_lstiter(tk_list, (void *)print_node);
	}
	return (0);
}
