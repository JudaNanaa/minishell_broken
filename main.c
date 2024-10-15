// #include <stdio.h>
// #include <stdlib.h>
// #include <readline/readline.h>
// #include <readline/history.h>
// #include <string.h>

// // Fonction pour filtrer l'historique basé sur l'entrée
// char *find_in_history(const char *text, int direction) {
//     HIST_ENTRY **history_list = history_get_history_state()->entries;
//     if (!history_list) return NULL;

//     int i = history_length - 1; // Commence par la dernière commande
//     int len = strlen(text);

//     // Recherche dans l'historique en fonction de la direction
//     while (i >= 0 && i < history_length) {
//         const char *cmd = history_list[i]->line;

//         // Vérifie si la commande commence par le texte déjà tapé
//         if (strncmp(cmd, text, len) == 0) {
//             return strdup(cmd);
//         }
//         // Direction : 1 pour flèche du haut, -1 pour flèche du bas
//         i += direction;
//     }

//     return NULL;
// }

// // Gestionnaire de touches pour capturer les flèches haut et bas
// int my_key_handler(int count, int key) {
//     // Séquences d'échappement pour les flèches du haut et du bas
//     if (key == 65) { // Flèche du haut
//         const char *current = rl_line_buffer; // Ce que l'utilisateur a déjà tapé
//         char *match = find_in_history(current, -1); // Cherche dans l'historique
//         if (match) {
//             rl_replace_line(match, 1); // Remplace la ligne avec la suggestion trouvée
//             rl_point = rl_end; // Positionne le curseur à la fin
//             free(match);
//         }
//         return 0;
//     }
//     // printf("count == %d\n", count);
//     // printf("key == %d\n", key);
//     else if (key == 66) { // Flèche du bas
//         const char *current = rl_line_buffer;
//         char *match = find_in_history(current, 1); // Cherche dans l'autre sens
//         if (match) {
//             rl_replace_line(match, 1);
//             rl_point = rl_end;
//             free(match);
//         }
//         return 0;
//     }
//     return 1; // Autres touches sont traitées normalement
// }

// int main() {
//     char *input;

//     // Ajoute notre gestionnaire de touches personnalisé
//     rl_bind_keyseq("\\e[A", my_key_handler); // Bind pour la flèche du haut
//     rl_bind_keyseq("\\e[B", my_key_handler); // Bind pour la flèche du haut

//     while ((input = readline("> ")) != NULL) {
//         if (*input) {
//             add_history(input); // Ajoute la commande à l'historique
//         }

//         // Simule "exit" pour quitter
//         if (strcmp(input, "exit") == 0) {
//             free(input);
//             break;
//         }

//         printf("Command: %s\n", input);
//         free(input);
//     }

//     return 0;
// }



#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

int	ft_strlen_2d(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	add_string_char_2d(char ***tabb, char *str)
{
	char	**new;
	int		i;
	char	**buff;

	buff = *tabb;
	new = malloc(sizeof(char *) * (ft_strlen_2d(buff) + 1 + 1));
	i = 0;
	while (buff && buff[i])
	{
		new[i] = buff[i];
		i++;
	}
	new[i] = str;
	new[++i] = NULL;
	free(buff);
	*tabb = new;
}

void printf_2d_array(char **to_print)
{
	int i;

	i = 0;
	if (to_print == NULL)
	{
		printf("NULL\n");
		return ;
	}
	while (to_print[i])
	{
		printf("%s\n", to_print[i]);
		i++;
	}
}

// Fonction pour filtrer l'historique basé sur l'entrée
// char *find_in_history(const char *text, int direction) {
//     static int len_history;
//     static int index;
//     int i;
//     char **good_compare;

//     HIST_ENTRY **history_list = history_get_history_state()->entries;
//     if (!history_list) return NULL;

//     good_compare = NULL;
//     i = history_length - 1;
//     int len = strlen(text);
//     printf("text == %s\n", text);
//     i += direction;
//     if (i < 0)
//         i = 0;
//     if (i == history_length)
//         i = history_length - 1;
//     return strdup(history_list[i]->line);
    // while (i >= 0)
    // {
    //     char *cmd = history_list[i]->line;
    //     if (strncmp(cmd, text, len) == 0)
    //         add_string_char_2d(&good_compare, cmd);
    //     i--;
    // }
    // if (good_compare == NULL)
    //     return NULL;
    // printf_2d_array(good_compare);
    // if (len_history < history_length)
    // {
    //     len_history = history_length;
    //     index = 0;
    // }
    // index += direction;
    // printf("len good == %d\n", ft_strlen_2d(good_compare));
    // if (index >= ft_strlen_2d(good_compare))
    // {
    //     index = index - 1;
    //     printf("index == %d\n", index);
    //     return strdup(good_compare[index]);
    // }
    // if (index < 0)
    // {
    //     index = 0;
    //     return NULL;
    // }
    // char *result = good_compare[index];
    // return strdup(result);
    // // Recherche dans l'historique en fonction de la direction et de l'index actuel
    // i = index;
    // // printf("okmerci\n");
    // while (i >= 0 && i < history_length)
    // {
    //     // printf("i == %d || index == %d\n", i, index);
    //     i += direction;
    //     if (i < 0)
    //     {
    //         // printf("i < 0\n");
    //         i = 0;
    //         index = i;

    //         return strdup(cmd);
    //     }
    //     if (i == history_length)
    //     {
    //         // printf("i == history_lenght\n");
    //         i = history_length - 1;
    //     const char *cmd = history_list[i]->line;
    //         index = i;

    //         return strdup(cmd);

    //     }
    //     const char *cmd = history_list[i]->line;

    //     // Vérifie si la commande commence par le texte déjà tapé
    //     if (strncmp(cmd, text, len) == 0 && i != index) 
    //     {
    //         // Avancer ou reculer dans l'historique selon la direction
    //         index = i;
    //         return strdup(cmd);
    //     }
    //     // Si pas de match, continue à chercher dans la direction donnée
    //     // index += direction;
    // }

//     return NULL;
// }

// // Gestionnaire de touches pour capturer les flèches haut et bas
// int my_key_handler(int count, int key) {
//     if (key == 65) { // Flèche du haut
//         const char *current = rl_line_buffer; // Ce que l'utilisateur a déjà tapé
//         char *match = find_in_history(current, 1); // Cherche dans l'historique
//         if (match) {
//             rl_replace_line(match, 1); // Remplace la ligne avec la suggestion trouvée
//             rl_point = rl_end; // Positionne le curseur à la fin
//             free(match);
//         }
//         return 0;
//     }
//     else if (key == 66) { // Flèche du bas
//         const char *current = rl_line_buffer;
//         char *match = find_in_history(current, -1); // Cherche dans l'autre sens
//         if (match) {
//             rl_replace_line(match, 1);
//             rl_point = rl_end;
//             free(match);
//         }
//         return 0;
//     }
//     return 1; // Autres touches sont traitées normalement
// }

// int main() {
//     char *input;

//     // Ajoute notre gestionnaire de touches personnalisé
//     rl_bind_keyseq("\\e[A", my_key_handler); // Bind pour la flèche du haut
//     rl_bind_keyseq("\\e[B", my_key_handler); // Bind pour la flèche du bas

//     while ((input = readline("> ")) != NULL) {
//         if (*input) {
//             add_history(input); // Ajoute la commande à l'historique
//         }

//         // Simule "exit" pour quitter
//         if (strcmp(input, "exit") == 0) {
//             free(input);
//             break;
//         }

//         printf("Command: %s\n", input);
//         free(input);
//     }

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

// Fonction pour filtrer l'historique basé sur l'entrée
char *find_in_history(const char *text, int direction) {
    static const char *initial_text = NULL; // Garde en mémoire le texte initial tapé
    static int index = -1; // Garde en mémoire la position actuelle dans l'historique
    HIST_ENTRY **history_list = history_get_history_state()->entries;
    if (!history_list) return NULL;

    // Si c'est un nouvel appel (nouveau texte), on réinitialise l'index et le texte initial
    if (initial_text == NULL || strcmp(initial_text, text) != 0) {
        initial_text = strdup(text); // Stocke le texte initial
        index = history_length - 1; // Commence à la fin de l'historique
    }

    int len = strlen(initial_text);
    while (index >= 0 && index < history_length) {
        const char *cmd = history_list[index]->line;

        // Vérifie si la commande commence par le texte initial
        if (strncmp(cmd, initial_text, len) == 0) {
            // On avance ou recule dans l'historique en fonction de la direction
            index += direction;
            return strdup(cmd);
        }

        // Si pas de match, continue à chercher dans la direction donnée
        index += direction;
    }

    return NULL;
}

// Gestionnaire de touches pour capturer les flèches haut et bas
int my_key_handler(int count, int key) {
    if (key == 65) { // Flèche du haut
        const char *current = rl_line_buffer; // Ce que l'utilisateur a déjà tapé
        char *match = find_in_history(current, -1); // Cherche dans l'historique
        if (match) {
            rl_replace_line(match, 1); // Remplace la ligne avec la suggestion trouvée
            rl_point = rl_end; // Positionne le curseur à la fin
            free(match);
        }
        return 0;
    } else if (key == 66) { // Flèche du bas
        const char *current = rl_line_buffer;
        char *match = find_in_history(current, 1); // Cherche dans l'autre sens
        if (match) {
            rl_replace_line(match, 1);
            rl_point = rl_end;
            free(match);
        }
        return 0;
    }
    return 1; // Autres touches sont traitées normalement
}

int main() {
    char *input;

    // Ajoute notre gestionnaire de touches personnalisé
    rl_bind_keyseq("\\e[A", my_key_handler); // Bind pour la flèche du haut
    rl_bind_keyseq("\\e[B", my_key_handler); // Bind pour la flèche du bas

    while ((input = readline("> ")) != NULL) {
        if (*input) {
            add_history(input); // Ajoute la commande à l'historique
        }

        // Simule "exit" pour quitter
        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        printf("Command: %s\n", input);
        free(input);
    }

    return 0;
}
