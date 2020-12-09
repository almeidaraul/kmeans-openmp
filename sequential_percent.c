#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#define DIM 3
int main(void) {
	double start_time = omp_get_wtime();
	double pstart_time, ptime = 0.0;
	int scanfArgs = 0;

	int i, j, k, n, c;
	double dmin, dx;
	double *x, *mean, *sum;
	int *cluster, *count, color;
	int flips;
	scanfArgs += scanf("%d", &k);
	scanfArgs += scanf("%d", &n);
	x = (double *)malloc(sizeof(double)*DIM*n);
	mean = (double *)malloc(sizeof(double)*DIM*k);
	sum= (double *)malloc(sizeof(double)*DIM*k);
	cluster = (int *)malloc(sizeof(int)*n);
	count = (int *)malloc(sizeof(int)*k);

	for (i = 0; i<n; i++)
		cluster[i] = 0;

	for (i = 0; i<k; i++)
		scanfArgs += scanf("%lf %lf %lf", mean+i*DIM, mean+i*DIM+1, mean+i*DIM+2);

	for (i = 0; i<n; i++)
		scanfArgs += scanf("%lf %lf %lf", x+i*DIM, x+i*DIM+1, x+i*DIM+2);
	
	if (scanfArgs < 3*(k+n)+2)
		exit(EXIT_FAILURE);

	flips = n;
	while (flips>0) {
		flips = 0;
		for (j = 0; j < k; j++) {
			count[j] = 0;
			for (i = 0; i < DIM; i++)
				sum[j*DIM+i] = 0.0;
		}
		pstart_time = omp_get_wtime();
		for (i = 0; i < n; i++) {
			dmin = -1; color = cluster[i];
			for (c = 0; c < k; c++) {
				dx = 0.0;
				for (j = 0; j < DIM; j++)
					dx +=  (x[i*DIM+j] - mean[c*DIM+j])*(x[i*DIM+j] - mean[c*DIM+j]);
				if (dx < dmin || dmin == -1) {
					color = c;
					dmin = dx;
				}
			}
			if (cluster[i] != color) {
				flips++;
				cluster[i] = color;
			}
		}
		ptime += omp_get_wtime()-pstart_time;

		for (i = 0; i < n; i++) {
			count[cluster[i]]++;
			for (j = 0; j < DIM; j++)
				sum[cluster[i]*DIM+j] += x[i*DIM+j];
		}
		pstart_time = omp_get_wtime();
		for (i = 0; i < k; i++) {
			for (j = 0; j < DIM; j++) {
				mean[i*DIM+j] = sum[i*DIM+j]/count[i];
			}
		}
		ptime += omp_get_wtime()-pstart_time;
	}
	for (i = 0; i < k; i++) {
		for (j = 0; j < DIM; j++)
			printf("%5.2f ", mean[i*DIM+j]);
		printf("\n");
	}
	#ifdef DEBUG
	for (i = 0; i < n; i++) {
		for (j = 0; j < DIM; j++)
			printf("%5.2f ", x[i*DIM+j]);
		printf("%d\n", cluster[i]);
	}
	#endif

	double total_time = omp_get_wtime() - start_time;
	printf("\n%lf\n%lf\n", total_time, total_time-ptime);
	return(0);
}
