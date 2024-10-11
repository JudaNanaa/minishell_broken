#!/bin/bash

echo -e "\n\n${BLUE}=== TEST cd =================================${NC}"

test_cd_commands() {
	run_test "cd src/ && pwd"
	run_test "cd src/ && pwd && ls -l | grep m && cd .. && pwd && ls -l | grep b"
	run_test "cd src/ && pwd && ls -l | grep m && cd /home && pwd && ls -l | grep b"
	run_test "cd src/ && ls -l | grep *.c"
	run_test "cd src/ && ./minishell -c \"echo un terminal dans un autre\""
}

# Call the cd test suite
test_cd_commands
