#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#define DIM 3
int main(void) {
	double start_time = omp_get_wtime();

	int i, j, k, n, c;
	double dmin, dx;
	double *x, *mean, *sum;
	int *cluster, *count, color;
	int flips;
	scanf("%d", &k);
	scanf("%d", &n);
	x = (double *)malloc(sizeof(double)*DIM*n); //set de pontos, x[n][dim]
	mean = (double *)malloc(sizeof(double)*DIM*k); //set de medias (centroides), mean[k][dim]
	sum= (double *)malloc(sizeof(double)*DIM*k); //set de somas (p/ calcular medias), sum[k][dim]
	cluster = (int *)malloc(sizeof(int)*n); //set de cluster (p/ cada ponto), cluster[n]
	count = (int *)malloc(sizeof(int)*k); //set de elementos por cluster (?), count[k]
	//NOME: CLUSTER_ZERO
	for (i = 0; i<n; i++)
		cluster[i] = 0; //todos os pontos começam no cluster 0
	//NOME: LE_K
	for (i = 0; i<k; i++) //leitura dos k centroides (cada um é uma linha)
		scanf("%lf %lf %lf", mean+i*DIM, mean+i*DIM+1, mean+i*DIM+2);
	//NOME: LE_N
	for (i = 0; i<n; i++) //leitura dos n pontos (cada um é uma linha)
		scanf("%lf %lf %lf", x+i*DIM, x+i*DIM+1, x+i*DIM+2);
	flips = n; //se n tiver nenhum ponto, não itera
	while (flips>0) {
		flips = 0;
		for (j = 0; j < k; j++) { //para cada um dos k centroides
			count[j] = 0; //começa com 0 elementos
			for (i = 0; i < DIM; i++)
				sum[j*DIM+i] = 0.0; //sum[dim][cluster] = 0, se inverter isso aqui acessa melhor a cache
		}
		for (i = 0; i < n; i++) { //for each n pontos
			dmin = -1; color = cluster[i];
			for (c = 0; c < k; c++) { //for each k clusters
				//calcula distancia(cluster, ponto) e compara com dmin
				dx = 0.0;
				for (j = 0; j < DIM; j++)
					//aqui o acesso tbm ta ruim p/ cache (acessa x[dim][j])
					dx +=  (x[i*DIM+j] - mean[c*DIM+j])*(x[i*DIM+j] - mean[c*DIM+j]); //(dx([1, 2], [3, 4]) = [(1-3)², (2-4)²]
				if (dx < dmin || dmin == -1) { //if closest cluster so far
					color = c;
					dmin = dx;
				}
			}
			if (cluster[i] != color) { //point changed clusters
				flips++;
				cluster[i] = color;
			}
		}

		for (i = 0; i < n; i++) { //for each n points
			//isso podia ser feitono if (cluster[i] != color) pra n ter que ficar loopando mais de uma vez
			count[cluster[i]]++; //conta qtos pontos cada cluster tem
			for (j = 0; j < DIM; j++) //for each dimensao
				//soma todos os pontos de cada cluster (p/ calcular media depois)
				sum[cluster[i]*DIM+j] += x[i*DIM+j]; //acesso ruim de cache ? descobri que talvez n
		}
		for (i = 0; i < k; i++) { //for k clusters
			for (j = 0; j < DIM; j++) { //for dimensions
				mean[i*DIM+j] = sum[i*DIM+j]/count[i]; //calcula media usando sum, acesso ruim de cache?
			}
		}
	}
	for (i = 0; i < k; i++) {
		for (j = 0; j < DIM; j++)
			printf("%5.2f ", mean[i*DIM+j]);
		printf("\n");
	}
	//se quiser debugar, ele tbm printa os elementos de entrada
	#ifdef DEBUG
	for (i = 0; i < n; i++) {
		for (j = 0; j < DIM; j++)
			printf("%5.2f ", x[i*DIM+j]);
		printf("%d\n", cluster[i]);
	}
	#endif

	printf("\nTempo: %lf\n", omp_get_wtime() - start_time);
	return(0);
}
