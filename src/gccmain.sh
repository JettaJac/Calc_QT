#!/bin/bash

# clear

gcc -g main.c s21_calc.c credit.c && ./a.out
# gcc -g main.c s21_calc.c && ./a.out
# gcc -g main.c s21_calc.c -fsanitize=address && CK_FORK=no leaks --atExit -- ./a.out 
	# make clean
	# make
	make test
	# make test1 # err
#		make test2
#		make test3
#		make test4	
	

#  make check
# sh ../push.sh./
# ./../push.sh 
# F5F5F5