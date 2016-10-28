/* 
 * File:   justify.h
 * Author: Dmitry Rybinkin
 *
 * Created on 23. November 2014, 14:24
 */

#ifndef JUSTIFY_H
#define	JUSTIFY_H

#define MAX_LINE_LENGTH 100

#define EOL '\0'
#define FREESPACE ' '


/**
 * 
 * @param p_line enthält den Zeiger einer einzelnen Zeile eines Textes.
 * @param target_line_length enthält die Zielzeilenlänge.
 * @param p_justified_line enthält einen Zeiger einer im Blocksatz formatierte Zeile
                      ,deren Länge der Zielzeilenläange entspricht.
 */
extern void justify_line(char *p_line, int target_line_length, char *p_justified_line);

#endif	/* JUSTIFY_H */

