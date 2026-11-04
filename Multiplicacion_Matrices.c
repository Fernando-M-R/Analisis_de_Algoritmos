#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void SumaMat(int n,
             int *A, int lda, int fa, int ca,
             int *B, int ldb, int fb, int cb,
             int *R, int ldr, int fr, int cr) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            R[(fr+i)*ldr + (cr+j)] = A[(fa+i)*lda + (ca+j)] + B[(fb+i)*ldb + (cb+j)];
}

void RestaMat(int n,
              int *A, int lda, int fa, int ca,
              int *B, int ldb, int fb, int cb,
              int *R, int ldr, int fr, int cr) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            R[(fr+i)*ldr + (cr+j)] = A[(fa+i)*lda + (ca+j)] - B[(fb+i)*ldb + (cb+j)];
}

void Multi_Mat(int n,
            //Arreglo,Tam.Filas,Fila 1, Columna 1 
               int *A, int lda, int fa, int ca,
               int *B, int ldb, int fb, int cb,
               int *R, int ldr, int fr, int cr) {
  
    if (n==1) {
        R[(fr)*ldr + (cr)] = A[(fa)*lda + (ca)] * B[(fb)*ldb + (cb)];
        return;
    }
    int m = n / 2;

    // Indices de cuadrantes
    // El elemento (i, j) del arrglo está en (f+i)*ld + (c+j)
    int a11f=fa,   a11c=ca,    a12f=fa,   a12c=ca+m;
    int a21f=fa+m, a21c=ca,    a22f=fa+m, a22c=ca+m;
    int b11f=fb,   b11c=cb,    b12f=fb,   b12c=cb+m;
    int b21f=fb+m, b21c=cb,    b22f=fb+m, b22c=cb+m;

    //Creamos los arreglos S's y P's 
    int *S[10], *P[7];
    for (int i = 0; i < 10; i++) S[i] = malloc(m*m*sizeof(int));
    for (int i = 0; i < 7;  i++) P[i] = malloc(m*m*sizeof(int));

    RestaMat(m, B,ldb,b12f,b12c, B,ldb,b22f,b22c, S[0],m,0,0); // S1 = B12 - B22
    SumaMat (m, A,lda,a11f,a11c, A,lda,a12f,a12c, S[1],m,0,0); // S2 = A11 + A12
    SumaMat (m, A,lda,a21f,a21c, A,lda,a22f,a22c, S[2],m,0,0); // S3 = A21 + A22
    RestaMat(m, B,ldb,b21f,b21c, B,ldb,b11f,b11c, S[3],m,0,0); // S4 = B21 - B11
    SumaMat (m, A,lda,a11f,a11c, A,lda,a22f,a22c, S[4],m,0,0); // S5 = A11 + A22
    SumaMat (m, B,ldb,b11f,b11c, B,ldb,b22f,b22c, S[5],m,0,0); // S6 = B11 + B22
    RestaMat(m, A,lda,a12f,a12c, A,lda,a22f,a22c, S[6],m,0,0); // S7 = A12 - A22
    SumaMat (m, B,ldb,b21f,b21c, B,ldb,b22f,b22c, S[7],m,0,0); // S8 = B21 + B22
    RestaMat(m, A,lda,a11f,a11c, A,lda,a21f,a21c, S[8],m,0,0); // S9 = A11 - A21
    SumaMat (m, B,ldb,b11f,b11c, B,ldb,b12f,b12c, S[9],m,0,0); // S10 = B11 + B12

    Multi_Mat(m, A,lda,a11f,a11c, S[0],m,0,0,      P[0],m,0,0); // P1 = A11*S1
    Multi_Mat(m, S[1],m,0,0,      B,ldb,b22f,b22c, P[1],m,0,0); // P2 = S2*B22
    Multi_Mat(m, S[2],m,0,0,      B,ldb,b11f,b11c, P[2],m,0,0); // P3 = S3*B11
    Multi_Mat(m, A,lda,a22f,a22c, S[3],m,0,0,      P[3],m,0,0); // P4 = A22*S4
    Multi_Mat(m, S[4],m,0,0,      S[5],m,0,0,      P[4],m,0,0); // P5 = S5*S6
    Multi_Mat(m, S[6],m,0,0,      S[7],m,0,0,      P[5],m,0,0); // P6 = S7*S8
    Multi_Mat(m, S[8],m,0,0,      S[9],m,0,0,      P[6],m,0,0); // P7 = S9*S10

    // Iteramos m*m veces asignando el valor correspondiene a cada valor de su cuadrante 
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++) {
            
            int p1=P[0][i*m+j], p2=P[1][i*m+j], p3=P[2][i*m+j], p4=P[3][i*m+j],
                p5=P[4][i*m+j], p6=P[5][i*m+j], p7=P[6][i*m+j];
            
            R[(fr+i)*ldr   + (cr+j)]   = p5 + p4 - p2 + p6; // C11
            R[(fr+i)*ldr   + (cr+m+j)] = p1 + p2;           // C12
            R[(fr+m+i)*ldr + (cr+j)]   = p3 + p4;           // C21
            R[(fr+m+i)*ldr + (cr+m+j)] = p5 + p1 - p3 - p7; // C22
        }

    //Liberamos memoria
    for (int i = 0; i < 10; i++) free(S[i]);
    for (int i = 0; i < 7;  i++) free(P[i]);
}

void MultiClasica(int n,
                  int *A, int lda, int fa, int ca,
                  int *B, int ldb, int fb, int cb,
                  int *R, int ldr, int fr, int cr) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) R[(fr+i)*ldr + (cr+j)] = 0;
        for (int k = 0; k < n; k++) {
            int a = A[(fa+i)*lda + (ca+k)];
            for (int j = 0; j < n; j++)
                R[(fr+i)*ldr + (cr+j)] += a * B[(fb+k)*ldb + (cb+j)];
        }
    }
}

void RellenarMatriz(int n, int *M) {
    int total = n * n;
    int minimo, rango;

    if (total > 10000) { 
        minimo = 0; rango = 2; 
    }
    else{ 
        minimo = 1; rango = 4; 
    }

    for (int k = 0; k < total; k++)
        M[k] = (rand() % rango) + minimo;
}

void ImprimirMat(int n, int *M) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("[%-3d] ", M[i*n + j]);
        printf("\n");
    }
    printf("\n");
}

int main(){
    printf("Algoritmo de multiplicacion de matrices");
    int pot, n;
    srand(time(NULL));
     
    printf("\nIngresa el tamaño de las matrices en potencias de dos (Max 13): ");
    scanf("%d", &pot);

    /*
    if(pot>=14 || pot<=0){
        printf("Tamaño no valido. ");
        return 0;
    }
    */

    n = 1 << pot; // 2^pot
    int *Mat = malloc( n* n * sizeof(int));
    int *Mat2 = malloc(n * n * sizeof(int));
    int *Resul = malloc(n * n * sizeof(int));
    RellenarMatriz(n, Mat);
    RellenarMatriz(n, Mat2);
    RellenarMatriz(n, Resul);
    
    if(n<50){
        printf("Matriz 1:");
        ImprimirMat(n, Mat);
        printf("Matriz 2:");
        ImprimirMat(n, Mat2);
    }
    
    clock_t inicio = clock();
    Multi_Mat(n, Mat, n, 0, 0, Mat2,n,0,0, Resul,n,0,0);
    clock_t fin = clock();
    double tiempo = ((double)(fin - inicio) / CLOCKS_PER_SEC) * 1000.0;
    if(n<50){
        printf("Resultado Multiplicacion Straseen:");
        ImprimirMat(n, Resul);
    }
    printf("Tiempo de ejecucion Strassen: %.15f ms\n", tiempo);

    RellenarMatriz(n, Resul);
    inicio = clock();
    MultiClasica(n, Mat, n, 0, 0, Mat2,n,0,0, Resul,n,0,0);
    fin = clock();
    tiempo = ((double)(fin - inicio) / CLOCKS_PER_SEC) * 1000.0;
    if(n<50){
        printf("Resultado Multiplicacion Clasica:");
        ImprimirMat(n, Resul);
    }
    printf("Tiempo de ejecucion Clasica: %.15f ms\n", tiempo);
    
    free(Mat); free(Mat2); free(Resul);
    
    return 0;
}