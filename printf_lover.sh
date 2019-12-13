#!/bin/sh

. ./config.sh
TESTER_DIR=`pwd`
IMPORTED_FILES_PATH=$TESTER_DIR/utils/copy_in_here_ft_printf_files
OUTPUTS_PATH=./outputs
GENERATION_TESTS_PATH=$TESTER_DIR/utils/auto_generation_tests
GENERATED_TESTS_PATH=$TESTER_DIR/utils/generated_tests
GENERATED_USER_TESTS_PATH=$GENERATED_TESTS_PATH/generated_tests_usr_version
ASSERT_TESTS_PATH=$GENERATED_TESTS_PATH/assert_tests

RECOMP_IF_NO_PERCENT=0

function update_programs()
{
	compiling_usr_printf_and_import_files
	if [ "$1" == "4" ]
	then
		rebuild_c_files_according_to_options
	fi
	cd $GENERATED_TESTS_PATH
	printf "\ncompiling printf_breaker with the original printf()...\n"
	DEBUG_FLAF="DEBUG_FLAG=-g -f_sanitize=address"
	if [ "$1" == "2" ]
	then
		DEBUG_FLAF=  
	fi
	make re $DEBUG_FLAG &> /dev/null
	cp ./sources/*.c $GENERATED_USER_TESTS_PATH/sources/
	cp specifiers_and_srcs.mk $GENERATED_USER_TESTS_PATH
	printf "\ncompiling printf_breaker with ft_printf()...\n"
	cd $GENERATED_USER_TESTS_PATH
	for j in sources/test*.c
	do
		sed -i '' '8,100000s/printf/ft_printf/g' $j 
		for HEY in `ls includes/*.h`
		do
			printf "%s\n" 5 i "#include \"../$HEY\"" . w | ed $j &> /dev/null
		done
	done
	make re $DEBUG_FLAG #&> /dev/null
	cd $ASSERT_TESTS_PATH
	printf "\ncompiling printf_breaker_returns with printf() and ft_printf()...\n\n"
	for j in sources/test*.c
	do
		for HEY in `ls includes/*.h`
		do
			printf "%s\n" 5 i "#include \"../$HEY\"" . w | ed $j &> /dev/null
		done
	done
	make re $DEBUG_FLAG # &> /dev/null
	cd $TESTER_DIR
}

function rebuild_c_files_according_to_options()
{
	printf "(re)generating .c files according to your options:\n"
	cd $GENERATION_TESTS_PATH
	make &> /dev/null
	./build_custom_functions
	cd $TESTER_DIR
}

function compiling_usr_printf_and_import_files()
{
	cd $PATH_TO_USER_PROJECT
	printf "\ncompiling your libftprintf.a...\n"
	make &> /dev/null
	if [ ! -f *.a  ]
	then
		printf "\033[31mfailure to build your 'libftprintf.a' or however '*.a' you called it\n\033[m"
		exit
	fi
	LIB_A=*.a
	cp $LIB_A $GENERATED_USER_TESTS_PATH/sources/
	cp $LIB_A $ASSERT_TESTS_PATH/sources/

	for G in `ls *.h */*.h 2> /dev/null`
	do
		cp $G $IMPORTED_FILES_PATH	
	done
	cd $IMPORTED_FILES_PATH
	for K in `ls *.h */*.h 2> /dev/null`
	do
		if [ "$K" != "libft.h" ]
		then
			sed -i '' 's/.*libft.*/#include \"..\/includes\/libft.h\"/' $K
		fi
		cp $K $GENERATED_USER_TESTS_PATH/includes
		cp $K $ASSERT_TESTS_PATH/includes
	done
	cd $TESTER_DIR
}

function check_dumb_input()
{
	local dumb_key=1;
	if [ $# -eq 0 ]
	then
		return $dumb_key
	elif [ $1 == "all" ] || [ $1 == "c" ] || [ $1 == "s" ] || [ $1 == "p" ] || [ $1 == "d" ]
	then
		dumb_key=0;
	elif [ $1 == "i" ] || [ $1 == "x" ] || [ $1 == "X" ] || [ $1 == "u" ] || [ $1 == "n" ]
	then
		dumb_key=0;
	elif [ $1 == "f" ] || [ $1 == "g" ] || [ $1 == "e" ] || [ $1 == "hi" ] || [ $1 == "hu" ]
	then
		dumb_key=0;
	elif [ $1 == "hx" ] || [ $1 == "hhi" ] || [ $1 == "hhu" ] || [ $1 == "hhx" ] || [ $1 == "li" ]
	then
		dumb_key=0;
	elif  [ $1 == "lu" ] || [ $1 == "lx" ] || [ $1 == "lli" ] || [ $1 == "llu" ] || [ $1 == "llx" ]
	then
		dumb_key=0;
	elif [ $1 == "exit" ]
	then
		dumb_key=0;
	elif [ $1 == "%" ] 
	then
		dumb_key=2;
	elif [ $1 == "re" ]
	then
		dumb_key=3;
	elif [ $1 == "rere" ]
	then
		dumb_key=4;
	fi
	return $dumb_key;
}

function display_separator()
{
	echo "\033[38;5;213m-------------------------------------------------------------\033[m"
}

function display_menu()
{
	display_separator
	printf "choose between any of those options:\n\n"
	printf "\t\t\t  \033[38;5;87mall\n"
	printf "\t\t    c s p d i u x X %%\n"
	printf "\t\t\tn f g e\n"
	printf "\t\t  hi hu hx hhi hhu hhx\n\t\t  li lu lx lli llu llx\033[m\n"
	printf "\t\t  \033[48;5;87m\033[38;5;0m re \033[0m\t\033[48;5;87m\033[38;5;0m rere \033[0m\t \033[48;5;87m\033[38;5;0m exit \033[0m\n"
}


if [ ! -f $GENERATED_TESTS_PATH/printf_breaker ] || { [ $# != 0 ] && [ $1 == "re" ]; }
then
	update_programs 4
fi

clear

while [ 1 ]
do
	display_menu
	read -p '--> ' -n 4  text
	clear
	display_menu
	echo "--> $text"
	display_separator
	echo "\033[0m"
	check_dumb_input $text
	FUNC_RETURN=`echo "$?"`
	if [ "$FUNC_RETURN" == "1" ]
	then
		printf "\033[3;38;5;1mWrong input\033[m\n"
		continue;
	elif [ "$FUNC_RETURN" == "2" ] && [ "$RECOMP_IF_NO_PERCENT" == "0" ]
	then
		printf "\nfor this special case '%%' we will recompile without '-g -fsanitize=address'\n"
		RECOMP_IF_NO_PERCENT=1
		update_programs $FUNC_RETURN
	elif [ "$FUNC_RETURN" -ge "3" ]
	then
		update_programs $FUNC_RETURN
		clear
		continue;	
	elif [ "$text" == "exit" ]
	then
			sh ./utils/script_quick_clean.sh
			break;
	elif [ "$FUNC_RETURN" == "0" ] && [ "$RECOMP_IF_NO_PERCENT" == "1" ]
	then
		RECOMP_IF_NO_PERCENT=0
		printf "\nrecompiling with '-g -fsanitize=address' after previously trying the %% specifier\n"
		update_programs 1
	fi
	$GENERATED_TESTS_PATH/printf_breaker $text > $OUTPUTS_PATH/printf_output
	$GENERATED_USER_TESTS_PATH/printf_breaker_usr $text > $OUTPUTS_PATH/ft_printf_output
	[ -s $OUTPUTS_PATH/printf_output ]
	if [ `echo "$?"` == "1" ]
	then
		printf "\033[38;5;2m ☞  $text\n to choose such an option you should \033[48;5;87m\033[38;5;0m 'rere' \033[0m\033[38;5;2m and add this bonus/option\033[0m\n"
		continue;
	fi
	diff -u $OUTPUTS_PATH/printf_output $OUTPUTS_PATH/ft_printf_output > $OUTPUTS_PATH/diff.txt
	RET=`echo "$?"`
	if [ $RET != 0 ]
	then
		printf "\033[3;38;5;196mhere are some diff lines:\033[0m\n"
		printf "\033[3;38;5;196m(head)\033[0m\n"
		head -n 8 $OUTPUTS_PATH/diff.txt
		echo ""
		printf "\033[3;38;5;196m(tail)\033[0m\n"
		tail -5 $OUTPUTS_PATH/diff.txt
		printf "\033[3;38;5;196m⬆ \033[4mIMITATION:\033[0m\033[3;38;5;196m⬆  [FAILED]\033[0m\n\n\n"
	else
		printf "\033[4;38;5;2mIMITATION:\033[0m\033[32m ➡ [SUCCESS]\033[0m\n"
	fi
	$ASSERT_TESTS_PATH/printf_breaker_returns $text > $OUTPUTS_PATH/asserts_output
	RET=`echo "$?"`
	if [ $RET != 0 ]
	then
		printf "\033[3;38;5;196m⬆ \033[4mRETURNS:\033[0m\033[3;38;5;196m⬆  [FAILED]\033[0m\n\n\n"
	else
		printf "\n\033[4;38;5;2mRETURNS:\033[0m\033[32m ➡ [SUCCESS]\033[0m\n"
	fi
	echo "\n\n"
done
