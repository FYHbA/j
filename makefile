CC=gcc
%.o:%.c
	$(CC) -c $< -o $@
project:new.o the_two.o work.o calculate.o hex.o
	gcc new.o the_two.o work.o calculate.o hex.o -o project -lreadline -lm

PHONY : clean
clean:
	-rm project new.o work.o calculate.o the_two.o hex.o