/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 05:33:34 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/16 19:05:00 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"
#include "parsing/parsing.h"

char		*type_to_str(int type);
void		print_command(t_token *command);
char		*operator_type_to_str(int type);
void		printTree(t_token *command, int depth, int isRight, int *branch);
t_token	*last_command(t_token *current);

t_token	*ast_top(t_token *current);

// void	print_AST(t_token *command)
// {
// 	int array[1024] = {0};

// 	command = ast_top(command);
// 	printTree(command, 0, 0, array);
// }

void	print_AST_test(t_token *command)
{
	int array[1024] = {0};

	printTree(command, 0, 0, array);
}

void print_command(t_token *command)
{
	int 	i;
	// char	*infile = "STDIN";
	// char	*outfile = "STDOUT";

	i = -1;
    if (command->type == CMD || command->type == SUBSHELL)
    {
		if (command->type == SUBSHELL)
			printf("(\"%s\")", command->content);
		else
			printf("%s", command->args[++i]);
		while (command->args && command->args[++i] != NULL)
		{
			printf(" (\"%s\")", command->args[i]);
		}
	}
	printf ("%s", operator_type_to_str(command->type));
}

void printTree(t_token *command, int depth, int isRight, int *branch) {
    if (depth > 0) {
        for (int i = 0; i < depth - 1; i++) {
            if (branch[i]) printf("│   ");
            else printf("    ");
        }
        printf("%s", isRight ? "└──" : "├──");
    }

    if (command == NULL) {
        printf("NULL\n");
        return;
    }

    print_command(command);
    printf("\n");

    if (command->left != NULL || command->right != NULL) {
        branch[depth] = (command->right != NULL);
        printTree(command->left, depth + 1, command->right == NULL, branch);
        printTree(command->right, depth + 1, 1, branch);
    }
}

char *operator_type_to_str(int type)
{
	if (type == AND)
		return (ft_strdup("AND"));
	if (type == OR)
		return (ft_strdup("OR"));
	if (type == PIPE)
		return (ft_strdup("PIPE"));
	if (type == LIST)
		return (ft_strdup("LIST"));
	return (NULL);
}

char *type_to_str(int type)
{
	if (type == CMD)
		return (ft_strdup("CMD"));
	if (is_operator_type(type))
		return (ft_strdup("OPERATOR"));
	if (is_redirection_type(type))
		return (ft_strdup("REDIRECTION"));
	if (type == SUBSHELL)
		return (ft_strdup("PARENTHESIS"));
	return (NULL);
}
