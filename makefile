CC=gcc
%.o:%.c $(CC) -c $< -o $@
project:new.o work.o calculate.o
	gcc new.o work.o calculate.o -o project -lreadline -lm

PHONY : clean
clean:
	-rm project new.o work.o calculate.o