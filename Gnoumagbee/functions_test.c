/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcamara <gcamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:30:27 by gcamara           #+#    #+#             */
/*   Updated: 2026/03/02 17:31:56 by gcamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
    char *r;
    //char *pwd;

    //pwd = getcwd(NULL, 0);
    //printf("%s\n", r);
    while (1){
    r = readline("Prompt > ");
    //rl_replace_line("hihi", 0);
    //rl_redisplay();
    add_history(r);
    printf("%s\n", r);
    }
    //add_history(r);
    //printf("History : %s\n", add_history(r));
    free(r);
    return(0);
}