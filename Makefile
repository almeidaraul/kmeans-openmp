all: ref kmeans

clean:
	@rm oskmeans okmeans 2> /dev/null

ref:
	@gcc skmeans.c -fopenmp -o oskmeans
	@export OMP_NUM_THREADS=4

kmeans:
	@gcc kmeans.c -fopenmp -o okmeans
	@export OMP_NUM_THREADS=4
