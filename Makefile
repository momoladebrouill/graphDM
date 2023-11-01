all:
	gcc main.c -o main.out
	./main.out
graph:
	gcc graph.c -o graph.out
	./graph.out
pile:
	gcc pile.c -o pile.out
	./pile.out
file:
	gcc file.c -o file.out
	./file.out
tasMin:
	gcc tasMin.c -o tasMin.out -fsanitize=address
	./tasMin.out
clean:
	rm -rf *.out
