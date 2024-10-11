#!/bin/bash

# Initialisation des compteurs
count_total=0
count_leaks=0
leak_tests=()
ko_cmd_line=()
# Couleurs pour les sorties
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
GREEN='\033[1;32m'
RED='\033[1;31m'
NC='\033[0m'  # No Color

# Chemin vers ton minishell
MINISHELL="./minishell"

# Liste des commandes à tester
 export nizar=test1
  export VARTESTER=VARTESTER is working
# Test cases
commands=(
  "echo Hello World"
  "echo -n Hello World"
  "echo Hello \$VARTESTER"
  "echo Hello \$USER"
  "echo 'Hello \$USER'"
  "echo \"Testing quotes\""
  "ls -l"
  "pwd"
  "export VAR=test && echo \$VAR"
  "export nizar=\"test2 test3 test4\""
  "export nizar=\"test2 test3 test4\" && echo \$nizar"
  "export nizar=\"test2 test3 test4\" && echo \$nizar && export nizar=\"ok\" && echo \$nizar"
  "export nizar=\"test2\" \"test3\" \"test4\""
  "export nizar=\"test2\" \"test3\" \"test4\" &&  echo \$nizar"
  "unset VAR && echo \$VAR"
  "cat /etc/passwd | grep root"
  "echo \"testing subshell\" && (echo \"subshell running\")"
  "echo \"multiple commands\" && ls && pwd"
  "ls -l | grep src"
  "echo \$nizar"
  "unset nizar"
  "echo \$nizar"
  "echo \$nizar && nizar=hello && echo \$nizar && set | grep nizar"
  "cd src/ && pwd"
  "cd src/ && pwd && ls -l | grep m && cd .. && pwd && ls -l | grep b"
  "cd src/ && pwd && ls -l | grep m && cd /home && pwd && ls -l | grep b"
  "cd src/ && ls -l | grep *.c"
  "ls *"
  "exit"
  "0"
  ""
  " "
  "  ' '   "
  "exit 0"
  "exit 1"
  "echo ''\$USER''"
  "echo \"une phrase très longue avec l'arrivée d'une apostrophe\" ''\$?''"
  "pwd .."
  "pwd ."
  "./minishell -c \"echo un terminal dans un autre\""
  "cd src/ && ./minishell -c \"echo un terminal dans un autre\""
  "unset PATH && ls -l"
  "ls -l"
  "echo qq \$HOME \$HO'ME' . "er"9 "
  "echo qq\$HOME \$HO'ME' . "er"9 "
  "echo qq\$HOME\$HO'ME' . "er"9 "
  "echo qq\$HOME\$HO'ME' ."er"9 "
  "echo qq\$HOME\$HO'ME'."er"9 "
  ">>> "
  ">> >>"
  "< >>"
  "     \"\"echo \$HO\"ME\""
  "''    \"\"echo \$HO\"ME\""
  "''''\"\"echo \$HO\"ME\""
  "echo \"'HO''ME'\""
  "echo \"'\$HO''ME'\""
  " /bin/echo"
 	" /bin/echo Hola Que Tal"
 	" /bin/env | wc -l"
 	" /bin/cd Desktop"
 	" (ls && ( ( pwd ) ) )"
 	" (ls && ( ( pwd ) ) )"
	"  ( ( ( ( ( pwd) ) ) ) )"
 	" exit "
 	" exit exit "
 	" exit hola "
 	" exit hola que tal "
 	" exit 42 "
 	" exit 000042 "
 	" exit 666 "
 	" exit 666 666 "
 	" exit -666 666 "
 	" exit hola 666 "
 	" exit 666 666 666 666 "
 	" exit 666 hola 666 "
 	" exit hola 666 666 "
 	" exit 259 "
 	" exit -4 "
 	" exit -42 "
 	" exit -0000042 "
 	" exit -259 "
 	" exit -666 "
 	" exit +666 "
 	" exit 0 "
 	" exit +0 "
 	" exit -0 "
 	" exit +42 "
 	" exit -69 -96 "
 	" exit --666 "
 	" exit ++++666 "
 	" exit ++++++0 "
 	" exit ------0 "
 	" exit \"666\" "
 	" exit '666' "
 	" exit '-666' "
 	" exit '+666' "
 	" exit '----666' "
 	" exit '++++666' "
 	" exit '6'66 "
 	" exit '2'66'32' "
 	" exit \"'666'\" "
 	" exit '\"666\"' "
 	" exit '666'\"666\"666 "
 	" exit +'666'\"666\"666 "
 	" exit -'666'\"666\"666 "
 	" exit 9223372036854775807 "
 	" exit 9223372036854775808 "
 	" exit -9223372036854775808 "
 	" exit -9223372036854775809 "
)

# Boucle sur chaque commande à tester
for cmd in "${commands[@]}"; do
  count_total=$((count_total + 1))
  echo -e "${YELLOW}=== TEST $count_total ==============================${NC}"
  echo -e "${BLUE}Testing: $cmd${NC}"

  # Exécuter la commande avec Valgrind sur Minishell pour détecter les fuites
  valgrind_output=$(valgrind --leak-check=full --quiet --log-file=valgrind_output.txt $MINISHELL -c "$cmd")

  # Lire la sortie Valgrind depuis le fichier de log
  if grep -q "definitely lost" valgrind_output.txt; then
    leaks=$(grep "definitely lost" valgrind_output.txt | awk '{print $4}')
    if [ "$leaks" != "0" ]; then
      echo -e "${RED}Memory leaks detected:${NC}"
      cat valgrind_output.txt | grep "definitely lost"
      count_leaks=$((count_leaks + 1))
      leak_tests+=("$count_total")
    ko_cmd_line+=("[$cmd]")
    else
      echo -e "${GREEN}No memory leaks detected.${NC}"
    fi
  else
    echo -e "${GREEN}No memory leaks detected.${NC}"
  fi

  # Nettoyer le fichier temporaire
  rm -f valgrind_output.txt
done

# Afficher le résumé à la fin
echo -e "${YELLOW}=======================================${NC}"
echo -e "${BLUE}Résumé des tests:${NC}"
echo "Total tests: $count_total"
echo "Tests avec fuites de mémoire: $count_leaks"

if [ ${#leak_tests[@]} -ne 0 ]; then
  echo -e "${RED}Index des tests avec fuites: ${leak_tests[*]}${NC}"
   echo -e "cmd: ${RED} ${ko_cmd_line[*]} ${NC} "
else
  echo -e "${GREEN}Aucune fuite détectée.${NC}"
fi
echo -e "${YELLOW}=======================================${NC}"
