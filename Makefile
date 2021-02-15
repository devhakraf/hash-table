#
# @author 		Abdelhakim RAFIK
# @version 		v1.0.1
# @license 		MIT License
# @Copyright 	Copyright (c) 2021 Abdelhakim RAFIK
# @date 		Feb 2021
#

output: bin/main.o bin/hashTable.o
	gcc bin/main.o bin/hashTable.o -o output

bin/main.o: main.c
	gcc -c main.c -o bin/main.o

bin/hashTable.o: lib/hashTable.c lib/hashTable.h
	gcc -c lib/hashTable.c -o bin/hashTable.o
