#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int A[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    
    int *L = (int *)malloc((n1 + 1) * sizeof(int));
    int *R = (int *)malloc((n2 + 1) * sizeof(int));
    
    for (int i = 0; i < n1; i++)
        L[i] = A[p + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[q + 1 + j];
        
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    
    int i = 0;
    int j = 0;
    
    for (int k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
    
    free(L);
    free(R);
}

void merge_sort(int A[], int p, int r) {
    if (p < r) {
        int q = p + (r - p) / 2; 
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

int main() {
    int n;
    printf("Ingrese el numero de elementos: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));

    srand(time(NULL)); 
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000 + 1;
    }

    if(n < 50) {
        printf("Arreglo original: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    
    clock_t inicio = clock();
    merge_sort(arr, 0, n - 1);
    clock_t fin = clock();
    double tiempo = ((double)(fin - inicio) / CLOCKS_PER_SEC) * 1000.0;

    if(n < 50) {
        printf("Arreglo ordenado: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    printf("Milisegundos \n");
    printf("Tiempo de ejecucion: %.40f ms\n", tiempo);
    printf("Segundos \n");
    printf("Tiempo de ejecucion: %.40f s\n", tiempo / 1000.0);


    return 0;
}
