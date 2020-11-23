all: ref kmeans

clean:
	@rm a.in otest oskmeans okmeans 2> /dev/null

ref:
	@gcc skmeans.c -fopenmp -o oskmeans
	@export OMP_NUM_THREADS=4

kmeans:
	@gcc kmeans.c -fopenmp -o okmeans
	@export OMP_NUM_THREADS=4

update_test:
	@cp test_kmeans.c .test_kmeans.c	# backup
	@cp kmeans.c test_kmeans.c

test:
	@gcc test_kmeans.c -fopenmp -o otest
	@export OMP_NUM_THREADS=4

output:
	@python2 geninput.py 5 10000 > a.in

compare: ref kmeans test
	@echo "---REFERENCE OUTPUT---"
	@./oskmeans < a.in
	@echo ""
	@echo "---KMEANS OUTPUT---"
	@./okmeans < a.in
	@echo ""
	@echo "---TEST OUTPUT---"
	@./otest < a.in
