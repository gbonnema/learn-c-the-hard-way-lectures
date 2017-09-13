CFLAGS=-Wall -Werror -g 

ex26: ex26_args.o ex26_utils.o ex26_config.o
	gcc $(CFLAGS) ex26.c ex26_args.o ex26_utils.o ex26_config.o -o ex26

ex26_args.o:
	gcc $(CFLAGS) ex26_args.c -c -o ex26_args.o

ex26_utils.o:
	gcc $(CFLAGS) ex26_utils.c -c -o ex26_utils.o

ex26_config.o:
	gcc $(CFLAGS) ex26_config.c -c -o ex26_config.o

clean:
	rm -f *.o ex26
