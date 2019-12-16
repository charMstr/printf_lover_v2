#!/bin/sh

cd ./utils
cd ./auto_generation_tests/
make fclean
cd ../tmp_files/
cd ../generated_tests/
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
