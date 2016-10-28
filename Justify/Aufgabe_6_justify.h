/* 
 * File:   Aufgabe_6_justify.h
 * Author: Florian
 *
 * Created on 11. November 2014, 18:00
 */

#ifndef AUFGABE_6_JUSTIFY_H
#define	AUFGABE_6_JUSTIFY_H

#define MAX_LINE_LENGTH 100

#define END_OF_LINE '\0'
#define FREESPACE ' '

typedef enum{
    FALSE,
    TRUE
}BOOL;

/**
 * 
 * @param p_line enthält den Zeiger einer einzelnen Zeile eines Textes.
 * @param target_line_length enthält die Zielzeilenlänge.
 * @param p_justified_line enthält einen Zeiger einer im Blocksatz formatierte Zeile
                      ,deren Länge der Zielzeilenläange entspricht.
 */
extern void justify_line(char *p_line, int target_line_length, char *p_justified_line);

#endif	/* AUFGABE_6_JUSTIFY_H */

