#!/bin/sh

#modify If you want to warn if argument needed...
if [ $# -eq 0 ]
then
	printf "\033[38;5;1mfailed to provide 1 arg\n\033[0m";	
	exit
fi

cp -rf  ./main_test.c ./sandbox/main_test_ft.c
sed -i '' '16,$s/printf/ft_printf/g' ./sandbox/main_test_ft.c
make
if [ "$?" != 0 ]
then
	printf "\033[31mfailure to compile, you need to have ALL your project files here\n"
	printf "as a example, you can do: \033[32mcp -rf path_to_ft_printf/* ./\033[m\n"
	exit
fi
mkdir -p ./includes
mkdir -p ./sandbox/includes/
for G in `ls *.h */*.h 2> /dev/null`
do
	cp -rf $G ./sandbox/includes/
	cp -rf $G ./includes/
done
gcc -Wall -Wextra -Werror -g -fsanitize=address ./main_test.c libftprintf.a -o ./sandbox/real_printf
gcc -Wall -Werror -Wextra -g -fsanitize=address ./sandbox/main_test_ft.c libftprintf.a -o ./sandbox/my_ft_printf

#no use of the fsanitize flags when checking onto the % special case.
#gcc -Wall -Wextra -Werror ./sandbox/main_test.c libftprintf.a -o ./sandbox/real_printf
#gcc -Wall -Werror -Wextra ./sandbox/main_test_ft.c libftprintf.a -o ./sandbox/my_ft_printf

./sandbox/real_printf $1 > ./sandbox/printf_output
./sandbox/my_ft_printf $1 > ./sandbox/usr_output
diff ./sandbox/printf_output ./sandbox/usr_output
RET=`echo $?`
if [ $RET != 0 ]
then
	printf "\nDIFF TEST: \033[38;5;1m[FAIL]\n\033[0m";	
else
	printf "\nDIFF TEST: \033[38;5;2m[SUCCESS]\n\033[0m";	
fi

printf "\n\033[38;5;156myour ft_printf() returned:\033[0m\n"
./sandbox/my_ft_printf $1 $2 $3
printf "\n\033[38;5;156mreal printf() returned:\033[0m\n"
./sandbox/real_printf $1 $2 $3 
