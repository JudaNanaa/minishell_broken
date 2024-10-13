#!/bin/bash

# Path to the minishell executable
MINISHELL=./minishell
# Initialisation des compteurs
count_total=0
count_ok=0
count_ko=0
ko_tests=()
ko_cmd_line=()
# Color codes for output formatting
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to run a test command in bash and minishell, then compare outputs
run_test() {
	count_total=$((count_total + 1))
    local cmd="$1"
	echo -e "${YELLOW}=== TEST $count_total ==============================${NC}"
    echo -e "${GREEN}Testing command: ${cmd}${NC}"

    # Run the command in Bash
    bash_output=$(bash -c "$cmd">/dev/null 2>&1) # silent mode
    bash_exit_status=$?
    bash_output=$(bash -c "$cmd" | grep -v "BASH_EXECUTION_STRING")
    
    # Run the command in Minishell
    #minishell_output=$($MINISHELL -c "$cmd" 2>&1)
    minishell_output=$($MINISHELL -c "$cmd")
    minishell_exit_status=$?

    # Compare outputs
    if [ "$bash_output" == "$minishell_output" ] && [ "$bash_exit_status" == "$minishell_exit_status" ]; then
        echo -e "${GREEN}Test passed${NC}"
 		count_ok=$((count_ok + 1)) 
    else
		count_ko=$((count_ko + 1))
        echo -e "${RED}Test failed${NC}"
        echo "Bash output: $bash_output"
        echo "Bash exit status: $bash_exit_status"
        echo "Minishell output: $minishell_output"
        echo "Minishell exit status: $minishell_exit_status"
		ko_tests+=("[$((count_total))]")
		ko_cmd_line+=("[$cmd]")
    fi
}

# Load all test files
source ./bin/test_echo.sh
source ./bin/test_export.sh
source ./bin/test_unset.sh
source ./bin/test_cd.sh
#source test_env.sh
#source test_redirect.sh
source ./bin/test_pipes.sh
source ./bin/test_too_much.sh
# Afficher le nombre de tests réussis et échoués
  echo -e "\n\n${YELLOW}=== Resume =================================${NC}"
  echo -e "${BLUE}Résumé des $count_total tests:${NC}"
  echo -e "${GREEN}Tests OK: $count_ok / $count_total ${NC}"
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

