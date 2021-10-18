
all: compile
	
compile:
	clear 

	gcc  	-o s 	jacobi.c
	gcc  	-o p 	jacobi.c -fopenmp

	@echo "Compilaçao concluida"

clean:
	rm -rf ?



