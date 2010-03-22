#!/bin/bash
echo "                 ...Tests... "
echo 
if [[ ! -e runTests.sh ]]; then
	echo This script should run from his home folder
	exit 1
fi

VALID=expected.StdOut  # Update this file if you expect the program to output something that is not an error
INVALID=expected.StdErr # Update this file if you expect the program to output something that is an error 

rm -f $VALID.real
rm -f $INVALID.real

if ! diff $VALID $VALID.real; then
	echo FUCK Build failed because expected output was unexpected
fi

echo
echo
echo

if ! diff $INVALID $INVALID.real; then
	echo FUCK it, Build failed because unexpected output wasn\'t fun
fi




