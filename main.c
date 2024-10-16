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
#define SET 0
#define GET 1

char *get_or_save_text(char *text, int flag)
{
    static char *initial_text;

    if (flag == SET)
        initial_text = text;
    return (initial_text);
}

// Fonction pour filtrer l'historique basé sur l'entrée
char *find_in_history(const char *text, int direction) {
    static const char *initial_text;
    static  char *save_text;
    static int index;
    HIST_ENTRY **history_list;
    int len;
    static char **good_tab;
    static int len_tab;
    char *cmd;
    int i;

    history_list =  history_get_history_state()->entries;
    if (!history_list)
        return NULL;
    
    if (initial_text == NULL || save_text == NULL || strcmp(save_text, text) != 0) {
        // get_or_save_text(strdup(text), SET);
        i = 0;
        good_tab = NULL;
        while (i < history_length)
        {
            cmd = history_list[i]->line;
            if (strncmp(cmd, text, strlen(text)) == 0)
                add_string_char_2d(&good_tab, cmd);
            i++;
        }
        len_tab = ft_strlen_2d(good_tab);
        initial_text = strdup(text);
        index = len_tab;
    }
    len = strlen(initial_text);
    while (index <= len_tab)
    {
        index += direction;
        if (index < 0)
        {
            index = 0;
            save_text = strdup(text);
            return strdup(text);
        }
        else if (index == len_tab + 1 || index == len_tab)
        {
            index = len_tab;
            save_text = strdup(initial_text);
            return strdup(initial_text);
        }
        cmd = good_tab[index];
        if (strncmp(cmd, initial_text, len) == 0) {
            // index += direction;
            save_text = strdup(cmd);
            return strdup(cmd);
        }
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
