all: glob.c
	gcc -c -Wall -Werror -fPIC glob.c -lyaslapi
	gcc -shared -o libglob.so glob.o -lyaslapi
