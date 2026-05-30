#include <stdio.h>
#include <string.h>

#define MAX_SOCIOS 500

typedef struct {
    char credencial[20];
    char apellidoynombre[50];
    char dni[15];
} Socio;



int calcularverificador(char credencial[]) {
    int pesos[] = {2,3,4,5,6,7,2,3,4};
    int suma = 0;

    for (int i = 0; i < 9; i++) {
        int digito = credencial[i] - '0'; // ese -0 pasa de caracter a entero y viceversa
        suma =suma + (digito * pesos[i]);
    }

    int resto = suma % 11;
    int verificador = 11 - resto;

    if (verificador == 10) return 'X';
    if (verificador == 11) return '0';
    return '0' + verificador;
}









int calcularedad(const char *credencial) {
    int anioNacimiento;

    // suponemos que los primeros 4 caracteres son el año de nacimiento
    sscanf(credencial, "%4d", &anioNacimiento);
    return 2025 - anioNacimiento;
}

int main(int argc, char *argv[]) {


    FILE *archivoBin;
    FILE *archivoTxt;
    Socio socio;
    int cantidad = 0;


    if (argc != 3) {
        printf("estas indicandole cantidad equivocada de archivos");
        return 1;
    }

    char *nombrearchivoBin = argv[1];
    char *nombrearchivotxt = argv[2];


    // abrir archivo binario para escritura

    archivoBin = fopen(nombrearchivoBin, "wb");
    if (!archivoBin) {
        perror("No se pudo abrir el archivo binario");
        return 1;
    }





    while (cantidad < MAX_SOCIOS) {
        printf("Ingrese credencial del socio (o 0 para terminar): ");
        scanf("%s", socio.credencial);



        if (strcmp(socio.credencial, "0") == 0)
            break;

        // calculamos verificador
               int verificadorcalculado = calcularverificador(socio.credencial);

                printf("Verificador calculado: %c\n", verificadorcalculado);


                int verificadoringresado;
                printf("Ingrese el verificador: ");
                scanf(" %c", &verificadoringresado);

                if (verificadoringresado != verificadorcalculado) {
                    printf("Verificador incorrecto. Intente de nuevo.\n\n");
                    continue; // vuelve a pedir credencial
                }








        printf("Ingrese apellido y nombre: ");
        getchar(); // limpiar el buffer
        fgets(socio.apellidoynombre, sizeof(socio.apellidoynombre), stdin);
        // eliminar salto de línea
        socio.apellidoynombre[strcspn(socio.apellidoynombre, "\n")] = 0;

        printf("ingrese dni: ");
        scanf("%s", socio.dni);

        // guardar en archivo binario

        fwrite(&socio, sizeof(Socio), 1, archivoBin);
        cantidad++;
    }

    fclose(archivoBin);


    // abrirel archivo binario para lectura

    archivoBin = fopen(nombrearchivoBin, "rb");
    if (!archivoBin) {
        perror("No se pudo abrir el archivo binario para lectura");
        return 1;
    }


    // abrir archivo de texto para escritura

    archivoTxt = fopen(nombrearchivotxt, "w");
    if (!archivoTxt) {
        perror("No se pudo crear el archivo de texto");
        fclose(archivoBin);
        return 1;
    }

    int orden = 1;
    while (fread(&socio, sizeof(Socio), 1, archivoBin) == 1) {
        int edad = calcularedad(socio.credencial);
        fprintf(archivoTxt, "%d ; %s ; %s ; %s ; %d\n",
                orden, socio.credencial, socio.apellidoynombre, socio.dni, edad);
        orden++;
    }

    fclose(archivoBin);
    fclose(archivoTxt);

    printf("Archivo de texto generado correctamente.\n");

    return 0;
}
