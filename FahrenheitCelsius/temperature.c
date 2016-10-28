/* 
 * File:   temperature.c
 * Author: Dmitry Rybinkin
 *
 * Created on 10. Oktober 2014, 02:46
 */

/* Programm zur Umwandlung von Fahrenheit
 * in Celsius für 0, 20, ..., 300 Grad.
 */
#include <stdio.h>

#define LOWER 0 /* untere Grenze der Temperaturtabelle in Fahrenheit */
#define UPPER 300 /* obere Grenze der Temperaturtabelle in Fahrenheit */
#define STEP 20 /* Schrittweite */

double transform_fahrenheit_to_celsius(int fahr);
double transform_celsius_to_fahrenheit(double celsius);

int main(void)
{
    int fahr;
    char Eingabe;
    double celsius;


    printf("Druecken Sie 'c' fuer die Umrechnung von Fahrenheit nach Celsius.\n"
           "und 'f' fuer die Umrechnung von Celsius nach Fahrenheit.\n");
    
    Eingabe = getchar();
    if (Eingabe == 'c' || 'C')
    {
        fahr = LOWER;
        while (fahr <= UPPER)
        {
            celsius = transform_fahrenheit_to_celsius(fahr);
            printf("%d\t%6.1f\n", fahr, celsius);
            fahr = fahr + STEP;
        }
    }
    else if (Eingabe == 'f' || 'F')
    {

        celsius = LOWER;
        while (celsius <= UPPER)
        {
            fahr = transform_celsius_to_fahrenheit(celsius);
            printf("%3.1f\t%d\n", celsius, fahr);
            celsius = celsius + STEP;
        }
   } else {
        printf("Falsche Eingabe! Bitte waehlen sie noch einmal.\n");
   }


    return 0;
}

double transform_fahrenheit_to_celsius(int fahr)
{
    return (5.0 / 9.0) * (fahr - 32);
}

double transform_celsius_to_fahrenheit(double celsius)
{
    return (celsius * 1.8) + 32;
}

