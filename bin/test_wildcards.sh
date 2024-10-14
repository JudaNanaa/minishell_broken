#!/bin/bash

BLUE='\033[0;34m'
NC='\033[0m'

echo -e "\n\n${BLUE}=== TEST wildcards (*) =================================${NC}"

test_wildcard_commands() {
    run_test "ls *"
    run_test "ls *.sh"
    run_test "ls *.*"
    run_test "ls */"
    run_test "echo *"
    run_test "echo *.sh"
    run_test "echo *.*"
    run_test "echo */"
    run_test "mkdir -p testdir/subdir && touch testdir/file.txt"
    run_test "echo testdir/*"
    run_test "echo testdir/*.txt"
    # run_test "echo */*"
    run_test "rm -r testdir"
    run_test "ls *[0-9]*"
    run_test "ls *test*"
    run_test "echo .*."
}

test_wildcard_commands
