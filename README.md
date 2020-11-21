# kmeans-openmp
Parallelizing a (given) implementation of the K-Means algorithm with OpenMP

## files
### `kmeans.c` and `skmeans.c`
`kmeans.c` is the parallel implementation and `skmeans.c` is the reference sequential implementation. Both will be compiled with `omp.h`to measure time.
**Input:**
```
k
n
centroids' coordinates (x, y, z) (k times)
points' coordinates (x, y, z) (n times)
```

### `getinput.py` (generate input)
**Execution:** `python getinput.py [K][N]`

### `test_kmeans.c`
For comparing changes between two parallel versions

`Makefile` includes two rules related to `test_kmeans.c`:
* **`update_test`**: copies `test_kmeans.c` to a backup file `.test_kmeans.c` and then copies `kmeans.c` to `test_kmeans.c`
* **`test`**: compiles `test_kmeans.c`
