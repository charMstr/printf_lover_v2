#!/bin/sh

. ./config.sh
TESTER_DIR=`pwd`
IMPORTED_FILES_PATH=$TESTER_DIR/utils/copy_in_here_ft_printf_files
OUTPUTS_PATH=./outputs
GENERATION_TESTS_PATH=$TESTER_DIR/utils/auto_generation_tests
GENERATED_TESTS_PATH=$TESTER_DIR/utils/generated_tests
GENERATED_USER_TESTS_PATH=$GENERATED_TESTS_PATH/generated_tests_usr_version
ASSERT_TESTS_PATH=$GENERATED_TESTS_PATH/assert_tests

###############################################################################
########################## COLOR CODES ########################################
REMOVE_FG="\033[38;5;196m"
CREAT_FG="\033[38;5;46m"
BLACK_FG="\033[38;5;0m"
BLACK_BG="\033[48;5;0m"
CLEAR_COLOR="\033[m"
NAME_BG="\033[48;5;39m"
OBJECTS_BG="\033[48;5;11m"
RANLIB_BG="\033[48;5;172m"
###############################################################################

RECOMP_IF_NO_PERCENT=0

function exit_error_compile_time()
{
	FUNC_RETURN=`echo "$?"`
	if [ "$FUNC_RETURN" != "0" ]
	then
		printf "\033[3;38;5;1m 🤪  ABORT:\nDue to error at this compiling stage\033[m\n"
		exit
	fi
}

function update_programs()
{
	compiling_usr_printf_and_import_files
	if [ "$1" == "4" ]
	then
		rebuild_c_files_according_to_options
	fi
	cd $GENERATED_TESTS_PATH
	printf "\n\n$CREAT_FG compiling printf_breaker with the original ${BLACK_FG}${NAME_BG}printf() $CLEAR_COLOR\n\n"
	DEBUG_FLAF="DEBUG_FLAG=-g -f_sanitize=address"
	if [ "$1" == "2" ]
	then
		DEBUG_FLAF=  
	fi
	make re $DEBUG_FLAG &> /dev/null
	exit_error_compile_time
	cp ./sources/*.c $GENERATED_USER_TESTS_PATH/sources/
	cp specifiers_and_srcs.mk $GENERATED_USER_TESTS_PATH
	printf "\n$CREAT_FG compiling printf_breaker with ${BLACK_FG}${NAME_BG}ft_printf() $CLEAR_COLOR\n\n"
	cd $GENERATED_USER_TESTS_PATH
	for j in sources/test*.c
	do
		sed -i '' '8,$s/printf/ft_printf/g' $j 
		for HEY in `ls includes/*.h`
		do
			printf "%s\n" 5 i "#include \"../$HEY\"" . w | ed $j &> /dev/null
		done
	done
	make re $DEBUG_FLAG #&> /dev/null
	exit_error_compile_time
	cd $ASSERT_TESTS_PATH
	printf "\n${CREAT_FG} compiling ${BLACK_FG}${NAME_BG}printf_breaker_returns ${CLEAR_COLOR} ${CREAT_FG}with printf() and ft_printf()...${CLEAR_COLOR}\n\n"
	for j in sources/test*.c
	do
		for HEY in `ls includes/*.h`
		do
			printf "%s\n" 5 i "#include \"../$HEY\"" . w | ed $j &> /dev/null
		done
	done
	make re $DEBUG_FLAG # &> /dev/null
	exit_error_compile_time
	cd $TESTER_DIR
}

function rebuild_c_files_according_to_options()
{
	printf "(re)generating .c files according to your options:\n"
	cd $GENERATION_TESTS_PATH
	make &> /dev/null
	exit_error_compile_time
	./build_custom_functions
	cd $TESTER_DIR
}

function compiling_usr_printf_and_import_files()
{
	cd $PATH_TO_USER_PROJECT
	printf "\n$CREAT_FG compiling your ${BLACK_FG}${NAME_BG}libftprintf.a $CLEAR_COLOR\n\n"
	make &> /dev/null
	exit_error_compile_time
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
			sed -i '' '7,$s/.*libft.*/#include \"..\/includes\/libft.h\"/' $K
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
		printf "\n$CREAT_FG for this special case ${BLACK_FG}${NAME_BG}'%%' ${CLEAR_COLOR}${CREAT_COLOR} we will recompile WITHOUT '-g -fsanitize=address'$CLEAR_COLOR\n\n"
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
		printf "\n$CREAT_FG recompiling WITH '-g -fsanitize=address' after previously trying the %% specifier$CLEAR_COLOR\n\n"
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
