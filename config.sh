#!/bin/sh

# replace here the path by the path of your project:
# example:
# PATH_TO_MY_PROJECT="/Users/charmstr/Projects/ft_printf_42cursus"

#PATH_FT_PRINTF="../"

PATH_TO_MY_PROJECT="/Users/charmstr/Projects/ft_printf_42cursus"





cd $PATH_TO_MY_PROJECT
PARSED_PATH=`pwd`
export `echo "PATH_TO_USER_PROJECT=$PARSED_PATH"`
cd - &> /dev/null
