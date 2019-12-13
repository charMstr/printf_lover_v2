#!/bin/sh

cd ./auto_generation_tests/
make fclean
cd ../
cd ./sandbox/
rm [^d]*
cd ../
cd ./generated_tests/
make fclean
rm *.mk
rm sources/test*.c
cd ./assert_tests/
make fclean
rm sources/test*.c
rm sources/*.a
cd ../generated_tests_usr_version/
make fclean
rm sources/test*
rm sources/*.a
rm *.mk

