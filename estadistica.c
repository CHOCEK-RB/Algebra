#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define _TIPO "%d"
typedef int TIPO;

int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

void imput_arr(TIPO *arr, int *n) {
  while (scanf(_TIPO, &arr[*n]) != EOF) {
    if (*n > MAX) {
      break;
    }
    ++*n;
  }
}

void print_arr(TIPO *arr, int n) {
  printf("Lista : ");
  for (int i = 0; i < n; ++i) {
    printf(_TIPO, arr[i]);
    if (i < n - 1) {
      printf(", ");
    }
  }
  printf("\n");
}

TIPO *eliminar_datos_repetidos(TIPO *arr, int n, int *new_n) {

  TIPO dato = arr[0];
  int cont = 1, j = 0;
  for (int i = 1; i < n; ++i) {
    if (dato != arr[i]) {
      dato = arr[i];
      ++cont;
    }
  }

  TIPO *new_arr = (TIPO *)malloc(cont * sizeof(TIPO));
  new_arr[0] = arr[0];
  for (int i = 1; i < n && j < cont; ++i) {
    if (new_arr[j] != arr[i]) {
      ++j;
      new_arr[j] = arr[i];
    }
  }

  *new_n = cont;
  return new_arr;
}

void frecuencia_no_acumulada_no_agrupados(TIPO *arr, TIPO *new_arr, int *fi,
                                          double *hi, double *pi, int n,
                                          int new_n) {
  fi[0] = 0;
  hi[0] = 0;
  pi[0] = 0;
  for (int i = 0, j = 0; i < n && j < new_n; ++i) {
    if (new_arr[j] == arr[i]) {
      ++fi[j];
    } else {
      hi[j] = fi[j] / (n * 1.0);
      pi[j] = hi[j] * 100;
      ++j;
      fi[j] = 1;
      hi[j] = 0;
      pi[j] = 0;
    }
  }
  hi[new_n - 1] = fi[new_n - 1] / (n * 1.0);
  pi[new_n - 1] = hi[new_n - 1] * 100;
}

void frecuencia_acumulada(int *fi, double *hi, double *pi, int *Fi, double *Hi,
                          double *Pi, int new_n) {
  Fi[0] = fi[0];
  Hi[0] = hi[0];
  Pi[0] = pi[0];
  for (int i = 1; i < new_n; ++i) {
    Fi[i] = Fi[i - 1] + fi[i];
    Hi[i] = Hi[i - 1] + hi[i];
    Pi[i] = Pi[i - 1] + pi[i];
  }
}

void print_tabla_no_agrupados(TIPO *new_arr, int *fi, double *hi, double *pi,
                              int *Fi, double *Hi, double *Pi, int new_n) {
  printf("|\txi\t|\tfi\t|\thi\t|\tpi\t|\tFi\t|\tHi\t|\tPi\t|\n");
  for (int i = 0; i < new_n; ++i) {
    printf(
        "%c\t%d\t%c\t%d\t%c\t%.2f\t%c\t%.2f\t%c\t%d\t%c\t%.2f\t%c\t%.2f\t%c\n",
        '|', new_arr[i], '|', fi[i], '|', hi[i], '|', pi[i], '|', Fi[i], '|',
        Hi[i], '|', Pi[i], '|');
  }
}

void datos_no_agrupados(TIPO *arr, TIPO *new_arr, int *fi, double *hi,
                        double *pi, int *Fi, double *Hi, double *Pi, int n,
                        int new_n) {
  frecuencia_no_acumulada_no_agrupados(arr, new_arr, fi, hi, pi, n, new_n);
  frecuencia_acumulada(fi, hi, pi, Fi, Hi, Pi, new_n);
  print_tabla_no_agrupados(new_arr, fi, hi, pi, Fi, Hi, Pi, new_n);
}

int main() {
  TIPO *arr = (TIPO *)malloc(MAX * sizeof(TIPO));
  int n = 0, new_n = 0;
  imput_arr(arr, &n);
  print_arr(arr, n);
  qsort(arr, n, sizeof(TIPO), compare);
  print_arr(arr, n);

  TIPO *new_arr = eliminar_datos_repetidos(arr, n, &new_n);
  int *fi = (int *)malloc(n * sizeof(int));
  double *hi = (double *)malloc(n * sizeof(double));
  double *pi = (double *)malloc(n * sizeof(double));
  int *Fi = (int *)malloc(n * sizeof(int));
  double *Hi = (double *)malloc(n * sizeof(double));
  double *Pi = (double *)malloc(n * sizeof(double));

  print_arr(new_arr, new_n);

  datos_no_agrupados(arr, new_arr, fi, hi, pi, Fi, Hi, Pi, n, new_n);

  free(arr);
  free(new_arr);
  free(fi);
  free(hi);
  free(pi);
  free(Fi);
  free(Hi);
  free(Pi);
}
