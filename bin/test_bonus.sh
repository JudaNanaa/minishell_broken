#!/bin/bash

# Path to the minishell executable
MINISHELL=./minishell
count_total=0
count_ok=0
count_ko=0
ko_tests=()
ko_cmd_line=()
# Test cases (more complex)
commands=(
  "echo Hello World"                       # Simple echo
  "echo \"Testing quotes\""                # Quotes
  "ls -l"                                  # List directory
  "pwd"                                    # Print working directory
  "export VAR=test && echo \$VAR"           # Environment variable
  "unset VAR && echo \$VAR"                # Unset variable
  "echo \$HOME"                            # Environment variable expansion
  "cat non_existing_file"                  # Error case
  "ls | grep minishell"                    # Pipe with grep
  "echo exit status test; false"           # Command that fails
  "echo \"Hello\" > test_file && cat test_file"  # Redirection to a file
  "(echo nested command && echo success)"  # Subshell
  "echo multiple pipes | grep pipe | cat -e" # Multiple pipes
  "ls -l > test_output && wc -l < test_output" # Redirection and counting lines
  "exit"                                   # Exit shell
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
  "echo \"une phrase tres longue avec l'arrivee d'une apostrophe\" ''\$?''"
  "pwd .."
  "pwd ."
  "./minishell -c \"echo un terminal dans un autre\""
  "cd src/ && ./minishell -c \"echo un terminal dans un autre\""
  "unset PATH && ls -l"
  "ls -l"
  "echo TEST=\"test1\$HOME '\$HOME' \" && echo \$TEST"
  "VAR1=value1 VAR2=value2 VAR3=value3 && echo \$VAR1 \$VAR2 \$VAR3"
  "export VAR1=value1 VAR2=value2 VAR3=value3  echo \$USER && echo \$VAR1 \$VAR2 \$VAR3"
  "ls -l | grep n && echo ok || echo ko"
  "ls -l | grep zz && echo ok || echo ko"
  ">>> "
  ">> >>"
  "< >>"
  "     \"\"echo \$HO\"ME\""
  "''    \"\"echo \$HO\"ME\""
  "''    echo \$HO\"ME\""
  "''''\"\"echo \$HO\"ME\""
  "echo \"'HO''ME'\""
  "echo \"'\$HO''ME'\""
)

# Define colors for better readability
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Run each command in both bash and minishell
for cmd in "${commands[@]}"; do
  count_total=$((count_total + 1))
  echo -e "${YELLOW}=== TEST $count_total ==============================${NC}"
  echo -e "${BLUE}Testing: $cmd${NC}"

  # Run the command in bash
  echo -e "${GREEN}Bash output:${NC}"
  bash_output=$(bash -c "$cmd")
  bash_exit_status=$?  # Capture the exit status here, before using grep
  bash_output=$(echo "$bash_output" | grep -v "BASH_EXECUTION_STRING")
  echo "$bash_output"
  echo -e "Bash exit status: $bash_exit_status"


  # Run the command in minishell
  echo -e "${GREEN}Minishell output:${NC}"
  minishell_output=$($MINISHELL -c "$cmd")
  minishell_exit_status=$?
  echo "$minishell_output"
  echo -e "Minishell exit status: $minishell_exit_status"

  # Compare the outputs
  if [ "$bash_output" == "$minishell_output" ] && [ "$bash_exit_status" == "$minishell_exit_status" ]; then
    echo -e "${GREEN}PASS: Outputs and exit status match${NC}"
    count_ok=$((count_ok + 1)) 
  else
    count_ko=$((count_ko + 1))
    echo -e "${RED}FAIL: Outputs or exit status differ${NC}"
    echo -e "${YELLOW}Bash output:${NC}"
    echo "$bash_output"
    echo -e "Bash exit status: $bash_exit_status"
    echo -e "${YELLOW}Minishell output:${NC}"
    echo "$minishell_output"
    echo "----------------$cmd---------" >> test.txt #log file
    echo "$minishell_output" >> test.txt #log file
    echo -e "Minishell exit status: $minishell_exit_status"
    echo "Minishell exit status: $minishell_exit_status" >> test.txt #log file
    echo "bash exit status: $bash_exit_status" >> test.txt #log file
    ko_tests+=("[$((count_total))]")
    ko_cmd_line+=("[$cmd]")
  fi
done
# Afficher le nombre de tests réussis et échoués
  echo -e "${YELLOW}=== Resume =================================${NC}"
  echo -e "${BLUE}Résumé des $count_total tests:${NC}"
  echo -e "${GREEN}Tests OK: $count_ok ${NC}"
  if [ "$count_ko" != "0" ]; then
  echo -e "${RED}Tests KO: $count_ko ${NC}"
  else 
  echo -e "${GREEN}*** bravo **********************************${NC}"
  fi
  if [ ${#ko_tests[@]} -ne 0 ]; then
    echo -e "Index des tests KO: ${RED} ${ko_tests[*]} ${NC} "
    echo -e "cmd: ${RED} ${ko_cmd_line[*]} ${NC} "
else
    echo "      Aucun test KO."
fi
  echo -e "${YELLOW}=== END ====================================${NC}"