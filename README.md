# PRINTF_LOVER_V2

## CROSS TABLE 
![alt text](https://github.com/charMstr/printf_lover_v2/blob/master/grep_harder.png)
*note: this information was yielded with some thorough greps on gcc's error/warnings
at compile time.*

## CHECKER's DESCRIPTION

this is a checker for ft_printf (42cursus november 2019)

This checker generates .c files automatically according to the bonuses you
select or not.
Each .c file will contain a single function testing a single conversion
specifier (example: 's' in "%s") in hundreds if not thousands of different
combinations of flags, field width and precision.

for a given letter ex: 's' in "%s" format string, two versions of
"test_func_s.c" are created in different folders with different makefiles:
- one tests your ft_printf() and then compares its output with the original
printf() using diff
- the second will use assert and compare the return of your ft_printf() and the
real one.

when auto-generating .c code, with the full set of flags from the subject
("*0.- '#+lhllhh") a function testing 'f' or 'g' can have up to 120 000 lines
in which half are ft_printf calls with different flags combinations. Therefore
the compile time can go up to a minute. do not try to compile all the "nfge"
bonuses all together. unless you want a ☕️

keep in mind that this tester excludes in the generation process of *.c files
any case resulting in a warning at compile time. Also it dont check for leaks.
The code ccould be addapted to testing extra extra flags and extr extra
conversion specifiers... see defines in .h files

## CHECKER's USAGE

🖖🏿 how to use the checker 🖖🏿

1/  clone the repository wherever you want, if you clone the repository in the
root of your project folder its all good. if not you will have to edit the
config.sh file and modifiy the PATH_TO_MY_PROJECT variable.
ex: PATH_TO_MY_PROJECT="../" ==> PATH_TO_MY_PROJECT="/Users/charmstr/Projects/ft_printf" 

2/  run the "printf_lover" script, this script is designed to run in a loop.
    refer to step 6/ for more informations but keep in mind that if its not the
	first time that you run the script, you should add a "re" argument to make
	sure potential changes to your project are taken into account.
    ex : $> ./printf_lover re 

3/  you will be asked what bonuses you wanna try on top of the basic 42cursus
	subject in order to generate .c code

4/  enter any option from the offered menu.
    note: - if you enter '%' a recompile is done so that the 
			-g -fsanitize=address flags are not used.
            then if you use another conversion specifier ex: 's' another
			recompile is done to revert changes.

5/  how to read the output?
	- if failure in IMITATION: you get a head and a tail of the file containing
	the last diff.
     you can always have a look in the output folder at the root of the
	 repository. Or you can just copy past the line into a main and just 
	 uncapitalise the 'P' in Printf(...).
    - if failure in RETURNS: the first line of code that aborted is dislayed.

6/ - if you modified your code enter "re" oherwise modifications are not
	recompiled. then stay in the infinite loop choosing again a test to be run.
   - if you want to try more bonuses we need to regenerate *.c files with the
   "rere" choice. This can also be done if you start over the script form the
   command line with the re option.
   
7/  if you exit with the "exit" option from the menu, a sub script is called to
	clean any useless files to make space on your disk.

8/  a folder named quick_tester_folder in the root directory: fully optional
	there you can find a main and a script to play quickly with the output of
	the tester. You just need to copy there all files of your project and then
	open the main, add some lines and run the script "quick_test.sh". It will
	give you a diff between your ft_print() and the real one.
    
Enjoy and give us a "poce bleu" if you loved it.
