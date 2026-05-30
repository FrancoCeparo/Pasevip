#include <stdio.h>
#include <string.h>



typedef struct {
    char credencial[20];
    char apellidoynombre[50];
    char dni[15];
} Socio;



int calcularverificador(char credencial[]) {
    int pesos[] = {2,3,4,5,6,7,2,3,4};
    int suma = 0;

    for (int i = 0; i < 9; i++) {
        int digito = credencial[i] - '0';
        suma = suma + (digito * pesos[i]);
    }

    int resto = suma % 11;
    int verificador = 11 - resto;

    if (verificador == 10) return 'X';
    if (verificador == 11) return '0';
    return  '0' + verificador;
}




int main(int argc, char *argv[]) {


    FILE *archivobin = fopen(argv[1], "rb");
    FILE *archivotxt = fopen(argv[2],"r");

    int cantidadnoverifi = 0;




    if (argc != 3) {
        printf("estas indicando cantidad equivocada de archivos\n");
        return 1;
    }



     FILE *reporte = fopen("reporte.txt", "w");


    if (!archivobin) {
        printf("error al abrir archivo binario.\n");
        return 1;
    }
    if (!archivotxt) {
        printf("error al abrir archivo de texto.\n");
        return 1;
    }
    if (!reporte) {
        printf("error al crear archivo de reporte.\n");
        return 1;
    }

    Socio sociobin;
    char lineatesto[1000];
    int linea=0;




    while (fread(&sociobin, sizeof(Socio), 1, archivobin) == 1){
           if (!fgets(lineatesto, sizeof(lineatesto), archivotxt)) break;

           //  eliminar salto de línea del texto
              lineatesto[strcspn(lineatesto, "\r\n")] = '\0';

            linea++;

            //  línea del archivo de texto

            char credencialtxt[20];
            if (sscanf(lineatesto, " %*d ; %15s", credencialtxt) != 1)
                continue;


            // calculamos verificadores

            char verbin = calcularverificador(sociobin.credencial);
            char vertxt = calcularverificador(credencialtxt);

            // omparamos solo credencial y verificador



            int credigual = strcmp(sociobin.credencial, credencialtxt) == 0;
            int verigual = (verbin == vertxt);

            fprintf(reporte,
                    " %d BIN: %s | Verificador: %c TXT: %s | Verificador: %c  | RESULTADO: ",


                    linea,  sociobin.credencial, verbin,credencialtxt,vertxt);



                    if (credigual){
                        if (verigual)
                        fprintf(reporte, "verificaaa\n");

                        else {

                                fprintf(reporte,  "NO verifica\n");

                                        cantidadnoverifi++;
                        }

        }else {

                        fprintf(reporte,  "NO verifica\n");

                        cantidadnoverifi ++;
                }

                    }

fprintf(reporte, "\n cantidad de no verificados: %d\n",cantidadnoverifi);

    fclose(archivobin);
    fclose(archivotxt);
    fclose(reporte);

    printf("archivo reporte generado correctamente.\n");

    return 0;
}
