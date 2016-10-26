/* @file
 * Hier befinden sich Funktionen, die für die Berechnung des Maximalwertes
 * einer Ulam-Folge noetig sind.
 * Ausserdem gibt es Funktionen zum heraussuchen von Zwillingen sowie Mehrlingen
 * innerhalb mehrerer Ulam-folgen.
 *  
 * @author      Dmitry Rybinkin
 * @date        15.10.2016
 */
#include <stdio.h>
/**
 * Die Funktion berechnet den Maximalwert einer Ulam-Folge.
 * @param a0 Der Uebergabeparameter a0 ist eine ganz Zahl die die Anfangszahl 
 * der Ulam-Folge angibt.
 * @return Ausgegeben wird der Maximalwert der Ulam-Folge. 
 */
int ulam_max(int a0);
/**
 * Ulam-Twins sucht in einem Intervall von Ulam-Folgen nach Zwillingen bzw.
 * gleiche, nebeneinanderliegende Maximalwerte.
 * 
 * @param limit Setzt das Intervall fest in dem nach Ulam-Zwillingen gesucht
 * wird.
 * @return Gibt den Wert des kleinsten Zwillings aus. 
 */
int ulam_twins(int limit);

/**
 * Ulam-Multiples sucht in einem Intervall von Ulam-Folgen nach Mehrlingen, also
 * mehreren aufeinanderfolgenden Maxima.
 * @param limit Setzt das Intervall, in dem gesucht wird, fest.
 * @param number Definiert nach wie vielen Mehrlingen gesucht werden soll.
 * @return Den kleinsten Wert einer Ulam-Folge in den ein Mehrling zu finden
 * ist.
 */
int ulam_multiples(int limit, int number);

/**
 * Enthaelt Beispielausgaben fuer die Funktionen die hier vorhanden sind.
 * @return Konsolenausgaben mit den Ausgabewerten der Funktionen.
 */
int main()
{    
    printf("Ulam_max: %d\n", ulam_max(7));

    printf("Ulam_twins: %d\n", ulam_twins(5));

    return 0;
}

int ulam_max(int a0)
{
    int i = 0;

    if (a0 <= 0)
        i = -1;

    else
    {
        while (a0 > 1)
        {
            if ((a0 > 1) && (a0 % 2 == 0))
                a0 = a0 / 2;

            else if ((a0 > 0) && (a0 % 2 == 1))
                a0 = 3 * a0 + 1;

            if (i < a0)
                i = a0;

        }
    }

    return i;
}

int ulam_twins(int limit)
{
    int result;
    int counter;

    for (counter = 1; counter < limit; counter++)
    {
        if (ulam_max(counter) == ulam_max(counter + 1))
            result = counter;
        else
            result = -1;
    }
    return result;
}

int ulam_multiples(int limit, int number)
{
    int outerCircleIndex = 1;
    int innerCircleIndex = 1;
    int multiples = -1;
    int steps = number;
    int firstNumber;

    if ((limit > 1 && number > 1) && number < limit)
    {
        if (number == 2)
            multiples = ulam_twins(limit);
        else
        {
            for (outerCircleIndex = 1; outerCircleIndex < limit;
                    outerCircleIndex++)
            {
                if ((firstNumber = ulam_twins(outerCircleIndex)) != -1)
                {
                    steps--;
                    for (innerCircleIndex = outerCircleIndex + 1;
                            innerCircleIndex < outerCircleIndex + number;
                            innerCircleIndex++)
                    {
                        if ((ulam_twins(innerCircleIndex) -
                                (innerCircleIndex - outerCircleIndex)) ==
                                firstNumber)
                            steps--;
                        else if (steps == 1)
                            multiples = firstNumber;
                        else
                            steps = number;
                    }
                }
            }
        }
        return multiples;
    }
}
