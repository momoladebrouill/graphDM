all:
	gcc main.c -o main.out -fsanitize=address
	./main.out
clean:
	rm -rf *.out
