CFLAGS=-Wall -Werror -g 

OBJ = ex26_args.o ex26_utils.o ex26_config.o ex26_logfile.o

ex26: $(OBJ)	
	gcc $(CFLAGS) ex26.c $(OBJ) -o ex26

ex26_args.o:
	gcc $(CFLAGS) ex26_args.c -c -o ex26_args.o

ex26_utils.o:
	gcc $(CFLAGS) ex26_utils.c -c -o ex26_utils.o

ex26_config.o:
	gcc $(CFLAGS) ex26_config.c -c -o ex26_config.o

ex26_logfile.o:
	gcc $(CFLAGS) ex26_logfile.c -c -o ex26_logfile.o

clean:
	rm -f *.o ex26
