#!/bin/bash




  export nizar=test1
  export VARTESTER=VARTESTER is working
echo -e "\n\n${BLUE}=== TEST echo =================================${NC}"
# Test suite for echo command
test_echo_commands() {
    run_test "                                echo         "Hello, world!""
    run_test "echo \$HOME"
    run_test "echo \"\$HOME\""
    run_test "echo \"\$HOME 001\""
    run_test "echo \$HOME 001"
    run_test "echo Hello World"
    run_test "echo -n Hello World"
    run_test "echo Hello \$VARTESTER"
    run_test "echo Hello \$USER"
    run_test "echo "Testing quotes""
    run_test "echo "multiple commands" && ls && pwd"
    run_test "echo \$nizar"
    run_test "echo \"testing subshell\" && (echo \"subshell running\")"
    run_test "echo \"une phrase tres longue avec l'arrivee d'une apostrophe\" ''\$?''"
    run_test "echo ""\$HO"ME""
    run_test "echo qq \$HOME \$HO'ME' . "er"9 "
    run_test "echo qq\$HOME \$HO'ME'.\"er\"9 "
    run_test "echo TEST=\"test1\$HOME '\$HOME' \" && echo \$TEST"
    run_test "echo ''\"\$USER\"''"
    run_test "echo \"'HO''ME'\""
    run_test "echo \"'\$HO''ME'\""
}

# Appelle la fonction de test
test_echo_commands
