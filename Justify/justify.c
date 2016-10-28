/* 
 * File:   justify.c
 * Author: Dmitry Rybinkin
 *
 * Created on 20. November 2014, 17:37
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "justify.h"

/*
 * WORDS repräsentiert die fülle an Wörtern in einem String:
 * EMPTY : 0
 * ONE_WORD : 1 
 */
enum WORDS
{
    EMPTY,
    ONE_WORD
};

/* Speicher für Leerzeichen im String. */
static unsigned int number_of_freespace_in_p_line;
/* Speicher für eingelesene Zeichen. */
static unsigned int number_of_character_in_p_line;
/* Speicher für anzahl aller Wörter im String. */
static unsigned int number_of_words;

/* Startadresse des Strings. */
static char *START_ADRESS_OF_INPUT;
/* Startadresse des */
static char *START_ADRESS_OF_OUTPUT;
static char *START_POSITION_OF_FIRST_CHAR;
static char *END_POSITION_OF_LAST_CHAR;

/**
 * Findet in der übergebenen Zeile, den ersten Buchstaben und überspringt
 * somit vorranstehende Leerzeichen. 
 * @param p_line der Pointer der Zeile die untersucht werden soll.
 */
static void select_first_and_last(char *p_line);

/**
 * Diese Methode zählt die vorkommenden Wörter in der Eingabe.
 * @param p_line
 */
static int count_words(char *p_line);

extern void justify_line(char *p_line, int target_line_length, char *p_justified_line)
{
    /* Initialisierung der Variablen*/
    number_of_freespace_in_p_line = EMPTY;
    number_of_character_in_p_line = EMPTY;
    number_of_words = EMPTY;

    select_first_and_last(p_line);

    START_ADRESS_OF_INPUT = START_POSITION_OF_FIRST_CHAR;
    START_ADRESS_OF_OUTPUT = p_justified_line;

    /* Wörter Zählen */
    count_words(START_POSITION_OF_FIRST_CHAR);

    /* Falls Leerzeile setzte Nullbyte */
    if (number_of_words == EMPTY)
    {
        *p_justified_line = EOL;
    }
    /* Falls nur ein Wort gegeben String "trimmen" */
    else if (number_of_words == ONE_WORD)
    {
        strncpy(p_justified_line, START_POSITION_OF_FIRST_CHAR,
                (size_t) (END_POSITION_OF_LAST_CHAR - START_POSITION_OF_FIRST_CHAR) + 1);
    }
    /* Falls mehrere Wörter vorhanden */
    else
    {
        unsigned int free_spaces = target_line_length - number_of_character_in_p_line;
        unsigned int number_of_gap = (number_of_words - 1);
        unsigned int size_of_normal_space = free_spaces / number_of_gap;
        unsigned int space_overflow = (free_spaces % number_of_gap);

        char *pointer_input = START_ADRESS_OF_INPUT;
        char *pointer_output = START_ADRESS_OF_OUTPUT;
/*
        char *linee = strchr(p_line,'\0');
*/
        
        while (pointer_input <= END_POSITION_OF_LAST_CHAR)
        {
            if ((*pointer_input != FREESPACE)
                    && (*pointer_input != EOL))
            {
                /*Buchstabe*/
                *pointer_output = *pointer_input;
                pointer_output++;
            }
            else if ((*pointer_input == FREESPACE)
                    && (*(pointer_input + 1) != FREESPACE))
            {
                /*Leerzeichen gefunden*/
                unsigned int counter = 0;
                while (counter < size_of_normal_space)
                {
                    *pointer_output = FREESPACE;
                    pointer_output++;
                    counter++;
                }
                if (space_overflow > 0)
                {
                    *pointer_output = FREESPACE;
                    pointer_output++;
                    space_overflow--;
                }
            }
            pointer_input++;
        }
        *(pointer_output + 1) = '\0';
    }
}

/*
 * Diese Funktion markiert mir Anfangs und Endadressen des Anfangs und End-Characters.
 */
static void select_first_and_last(char *p_line)
{
    char *pointer_of_last_char = p_line;

    while (*p_line == FREESPACE)
    {
        p_line++;
    }
    
    START_POSITION_OF_FIRST_CHAR = p_line;

    while (*p_line != EOL)
    {
        if ((*p_line != FREESPACE))
        {
            pointer_of_last_char = p_line;
        }
        p_line++;
    }


    END_POSITION_OF_LAST_CHAR = pointer_of_last_char;
    
    p_line = pointer_of_last_char;
    
//    while(*p_line != EOL) {
//        printf("Leerzeichen");
//        p_line++;
//    }
}
/*
 * Diese Funktion zählt die Wörter in einem vorgegebenen String, auf den der 
 * Pointerparameter zeigt.
 */
static int count_words(char *p_line)
{
    
    char *next_pointer;
    /* Solange Inhalt ungleich dem Zeilenende. */
    while (*p_line != EOL)
    {
        /* Wenn Inhalt einem Leerzeichen gleicht. */
        if (*p_line == FREESPACE)
        {
            number_of_freespace_in_p_line++;
        }
        else if (*p_line != EOL)
        {
            number_of_character_in_p_line++;
        }
        next_pointer = p_line + 1;

        /* Bedingungen für das erstellen eines Wortes. */
        if ((*p_line == FREESPACE)
                && (*next_pointer != FREESPACE)
                && (*next_pointer != EOL))
        {
            number_of_words++;
        }
        p_line++;
    }

    
    if (START_POSITION_OF_FIRST_CHAR != p_line)
    {
        number_of_words++;
    }
    return number_of_words;
}



