#include <stdio.h>
#include <string.h>

int main(void) {
    int k;
    char s[100];
    int minutos = 0;

    printf("Ingresa el numero de estudiantes: ");
    if (scanf("%d", &k) != 1 || k < 1 || k > 100) {
        printf("Entrada invalida. Por favor ingresa un numero entre 1 y 100.\n");
        return 1;
    }

    getchar(); 

    printf("Ingresa la secuencia de estudiantes (solo A y P): ");
    if (fgets(s, sizeof(s), stdin) == NULL) {
        printf("No se pudo leer la secuencia.\n");
        return 1;
    }    

    while (1) {
        int hayA = 0;
        int cambio = 0;
        char siguiente[100];

        strcpy(siguiente, s);

        for (int i = 0; i < k; i++) {
            if (s[i] == 'A') {
                hayA = 1;
                if ((i+1 < k && s[i+1] == 'P')) {
                    siguiente[i+1] = 'A';
                    cambio = 1;
                }
            }
        }
        if (!hayA || !cambio) {
            printf("%d\n", minutos);
            return 0;
        }
        strcpy(s, siguiente);
        minutos++;
    }

    printf("%d\n", minutos);
    return 0;
}