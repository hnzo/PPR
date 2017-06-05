/** 
 * @file   determinante.c
 * @author: Dmitry Rybinkin
 *
 * Created on 23. Oktober 2014
 */

#include <stdio.h>
#include <math.h>

#define MAX_SIZE 10
/**
 * Diese Methode ist dazu gedacht die Determinante einer n-Matrix zu berechnen.
 * Man gibt ihr eine vorhandene Matrix und eine Matrix-groesse und diese liefert
 * dann einen gueltigen (oder auch ungueltigen) Wert.
 * @param matrix Vorhandene Matrix.
 * @param size Groesse der Matrix.
 * @return Berechneter Determinantenwert.
 */
double get_determinant(double matrix[MAX_SIZE][MAX_SIZE], int size);

/**
 * Die print_matrix Funktion gibt eine Matrix aus. Sie nimmt eine vorhandene
 * matrix und deren groesse und gibt sie formatiert wieder aus.
 * @param matrix Vorhandene Matrix.
 * @param size Groesse der Matrix.
 */
void print_matrix(double matrix[MAX_SIZE][MAX_SIZE], int size);

int main(void)
{

    double matrix[MAX_SIZE][MAX_SIZE] = {
        {25, 50, 13, -7, 6},
        {98, 66, 18, -24, 1},
        {20, 21, 22, 23, 24},
        {25, 26, 27, 28, 29},
        {30, 31, 32, 33, 43}
    };


    print_matrix(matrix, 1);
    printf("\n");
    print_matrix(matrix, 2);
    printf("\n");
    print_matrix(matrix, 4);
    printf("\n");
    print_matrix(matrix, 5);
    printf("\n");
    print_matrix(matrix, 3);
    printf("\n");
    print_matrix(matrix, 11);
    printf("\n");
    print_matrix(matrix, -1);
    printf("\n");

    printf("Ergebnis = %.1f \n", get_determinant(matrix, 5));

    return 0;
}

double get_determinant(double matrix[MAX_SIZE][MAX_SIZE], int size)
{

    double ergebnis = 0;
    int sigma_zaehler;
    int anzahl_spalten;
    int anzahl_zeilen;
    int unter_matrix_spalten;
    double unter_matrix[MAX_SIZE][MAX_SIZE];


   if (size < 1 || size > MAX_SIZE)
    {
        printf("%s\n", "Parameter \"size\" ist ungültig!");
        return 0.0;
    }
    if (size == 1)
    {
        ergebnis = matrix[0][0];
    }
    else if (size == 2)
    {
        ergebnis = (matrix[0][0] * matrix[1][1])
                - (matrix[1][0] * matrix [0][1]);
    }
    else
    {
        for (sigma_zaehler = 1; sigma_zaehler <= size; sigma_zaehler++)
        {
            unter_matrix_spalten = 0;

            for (anzahl_zeilen = 0; anzahl_zeilen < size; anzahl_zeilen++)
            {
                for (anzahl_spalten = 0; anzahl_spalten < size; anzahl_spalten++)
                {
                    if (anzahl_spalten != sigma_zaehler - 1)
                    {
                        unter_matrix[anzahl_zeilen][unter_matrix_spalten]
                                = matrix[anzahl_zeilen + 1][anzahl_spalten];
                        unter_matrix_spalten++;
                    }
                }
                unter_matrix_spalten = 0;
            }

            ergebnis += (sigma_zaehler % 2 == 0 ? -1 : 1)
                    * matrix[0][sigma_zaehler - 1]
                    * get_determinant(unter_matrix, size - 1);
        }

    }
    return ergebnis;
}

void print_matrix(double matrix[MAX_SIZE][MAX_SIZE], int size)
{
    int anzahl_zeilen;
    int anzahl_spalten;
    if ((size <= 10) && (size > 0))
    {
        for (anzahl_zeilen = 0; anzahl_zeilen < size; anzahl_zeilen++)
        {
            for (anzahl_spalten = 0; anzahl_spalten < size; anzahl_spalten++)
            {
                printf("%3.1f ", matrix[anzahl_zeilen][anzahl_spalten]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("%s", "Die groesse der Matrix war ausserhalb des gueltigen "
               "Bereichs!");
    }
}