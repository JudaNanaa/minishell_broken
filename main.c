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

// Fonction pour filtrer l'historique basé sur l'entrée
char *find_in_history(const char *text, int *index, int direction) {
    HIST_ENTRY **history_list = history_get_history_state()->entries;
    if (!history_list) return NULL;

    int len = strlen(text);

    // Recherche dans l'historique en fonction de la direction et de l'index actuel
    while (*index >= 0 && *index < history_length) {
        const char *cmd = history_list[*index]->line;

        // Vérifie si la commande commence par le texte déjà tapé
        if (strncmp(cmd, text, len) == 0) {
            // Avancer ou reculer dans l'historique selon la direction
            *index += direction;
            return strdup(cmd);
        }

        // Si pas de match, continue à chercher dans la direction donnée
        *index += direction;
    }

    return NULL;
}

// Gestionnaire de touches pour capturer les flèches haut et bas
int my_key_handler(int count, int key) {
    static int current_index = -1; // Index actuel dans l'historique
    if (key == 65) { // Flèche du haut
        if (current_index == -1) {
            current_index = history_length - 1; // Commence à la fin de l'historique
        }
        const char *current = rl_line_buffer; // Ce que l'utilisateur a déjà tapé
        char *match = find_in_history(current, &current_index, -1); // Cherche dans l'historique
        if (match) {
            rl_replace_line(match, 1); // Remplace la ligne avec la suggestion trouvée
            rl_point = rl_end; // Positionne le curseur à la fin
            free(match);
        }
        return 0;
    }
    else if (key == 66) { // Flèche du bas
        if (current_index == -1) {
            current_index = history_length - 1;
        }
        const char *current = rl_line_buffer;
        char *match = find_in_history(current, &current_index, 1); // Cherche dans l'autre sens
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
