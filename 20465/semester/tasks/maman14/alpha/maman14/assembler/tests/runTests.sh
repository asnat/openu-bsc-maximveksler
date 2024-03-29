#!/bin/bash
echo "                 ...Tests... "
echo 
if [[ ! -e runTests.sh ]]; then
	echo This script should run from his home folder
	exit 1
fi

VALID=expected.StdOut  # Update this file if you expect the program to output something that is not an error
INVALID=expected.StdErr # Update this file if you expect the program to output something that is an error 
ASM=../dist/Debug/GNU-Linux-x86/assembler
ERROR_FOUND=false

rm -f $VALID.real
rm -f $INVALID.real

for FILE in $(find asms -type f); do
	if [[ "${FILE%.as}.as" = $FILE ]]; then
		#echo "Not deleting $FILE"
		:
	else
		rm -f ${FILE}
	fi
done

exec 3>&1
exec 4>&2

exec 1>$VALID.real
exec 2>$INVALID.real

	
################################################################
################################################################
##### TESTS - add your assembly calls here... ##################
################################################################
$ASM NOSUCHFILE
$ASM


###################################
# Post analysis
###################################
exec 1>&3
exec 2>&4

if ! diff -Naur $VALID $VALID.real; then
	echo FUCK Build failed because expected output was unexpected
	ERROR_FOUND=true
fi

echo

if ! diff -Naur $INVALID $INVALID.real; then
	echo FUCK it, Build failed because unexpected output wasn\'t fun
	ERROR_FOUND=true
fi


echo 
echo
if [[ $ERROR_FOUND = "false" ]]; then
	echo "IT WORKED, it fucking worked. No one will ever believe you..."
else 
	echo "BUILD FAILED. Yup, you broke it... AGAIN!"
fi

echo

