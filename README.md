# kmeans-openmp
Parallelizing a (given) implementation of the K-Means algorithm with OpenMP

## auxiliary files
### `kmeans.c` (reference sequential code)
**Input:**
```
k
n
centroids' coordinates (x, y, z) (k times)
points' coordinates (x, y, z) (n times)
```

### `getinput.py` (generate input)
**Execution:** `python getinput.py [K][N]`
