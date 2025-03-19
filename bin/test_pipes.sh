#!/bin/bash

echo -e "\n\n${BLUE}=== TEST pipes =================================${NC}"

test_pipes_commands() {
    run_test "ls | grep minishell"
    run_test "echo multiple pipes | grep pipe | cat -e"
    run_test "cat /etc/passwd | grep root"
    run_test "ls -l | grep src"
    run_test "cd src/ && ls -l | grep *.c"
    run_test "ls -l | grep n && echo ok || echo ko"
    run_test "ls -l | grep zz && echo ok || echo ko"
}

# Call the pipes test suite
test_pipes_commands
