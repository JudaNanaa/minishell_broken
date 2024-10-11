#!/bin/bash

echo -e "\n\n${BLUE}=== TEST export =================================${NC}"

# Test suite for export and environment variables
test_export_commands() {
	run_test "export VAR=test && echo \$VAR"
	run_test "export nizar=\"test2 test3 test4\""
	run_test "export nizar=\"test2 test3 test4\" && echo \$nizar"
	run_test "export nizar=\"test2 test3 test4\" && echo \$nizar && export nizar=\"ok\" && echo \$nizar"
	run_test "export nizar=\"test2\" \"test3\" \"test4\""
	run_test "export nizar=\"test2\" \"test3\" \"test4\" &&  echo \$nizar"
}

# Call the export test suite
test_export_commands
