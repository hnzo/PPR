/**
 * @File:   Aufgabe_6_justify.c
 * @Author: Florian Pelka
 * MatrikelNr: 201124127
 *
 * Created on 11. November 2014, 17:59
 */

#include <string.h>
#include "Aufgabe_6_justify.h"

#define CONTENT_OF(P) *(P)
#define MEM_ADR_OF(P) P

#define LEERZEILE 0
#define EIN_WORT 1

static unsigned int number_of_freespace_in_p_line;
static unsigned int number_of_charakter_in_p_line;
static unsigned int number_of_words;

static char *START_ADRESS_OF_INPUT;
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
 * Die Funktion iniziert die internen Variablen zum generieren des Blocktextes.
 * 
 * @param p_line der Pointer des eingegebenen Textes.
 * @param p_justified_line der Pointer des auszugebenen Textes.
 */
static void init_workspace(char *p_line, char *p_justified_line);

/**
 * Diese Funktion generiert die Blocktextzeile.
 * @param target_line_length
 */
static void generate_justify_line(int target_line_length);

/**
 * Diese Methode zählt die vorkommenden Wörter in der Eingabe.
 * @param p_line
 */
static int count_words(char *p_line);


/********************************************************
 *
 ********************************************************/

extern void justify_line(char *p_line, int target_line_length, char *p_justified_line)
{
    init_workspace(p_line, p_justified_line);

    switch (number_of_words)
    {
        /*Eingabe ist leer*/
    case LEERZEILE: CONTENT_OF(p_justified_line) = END_OF_LINE;
        break;
        /*Eingabe besteht aus einem Wort*/
    case EIN_WORT: strcpy(p_justified_line, p_line);
        break;
        /*Nicht trivialer Fall, Wortanzahl größer 1*/
    default:generate_justify_line(target_line_length);
    }
}

static void init_workspace(char *p_line, char *p_justified_line)
{
    /*Nötig bei mehrmaligem Aufrufen von justify_line*/
    number_of_freespace_in_p_line = LEERZEILE;
    number_of_charakter_in_p_line = LEERZEILE;
    number_of_words = LEERZEILE;

    select_first_and_last(p_line);

    START_ADRESS_OF_INPUT = START_POSITION_OF_FIRST_CHAR;
    START_ADRESS_OF_OUTPUT = p_justified_line;
    
    count_words(START_POSITION_OF_FIRST_CHAR);
}

static void select_first_and_last(char *p_line)
{
    char *pointer_of_last_char = p_line;

    while (CONTENT_OF(p_line) == FREESPACE)
    {
        p_line++;
    }
    START_POSITION_OF_FIRST_CHAR = p_line;

    while (CONTENT_OF(p_line) != END_OF_LINE)
    {
        if ((CONTENT_OF(p_line) != FREESPACE))
        {
            pointer_of_last_char = p_line;
        }
        p_line++;
    }
    END_POSITION_OF_LAST_CHAR = pointer_of_last_char;
}

static int count_words(char *p_line)
{
    char *next_pointer;
    while (CONTENT_OF(p_line) != END_OF_LINE)
    {
        if (CONTENT_OF(p_line) == FREESPACE)
        {
            number_of_freespace_in_p_line++;
        }
        else if (CONTENT_OF(p_line) != END_OF_LINE)
        {
            number_of_charakter_in_p_line++;
        }
        next_pointer = p_line + 1;
        
        if ((CONTENT_OF(p_line) == FREESPACE)
                && (CONTENT_OF(next_pointer) != FREESPACE)
                && (CONTENT_OF(next_pointer) != END_OF_LINE))
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


static void generate_justify_line(int target_line_length)
{
    unsigned int free_spaces = target_line_length - number_of_charakter_in_p_line;
    unsigned int number_of_gap = (number_of_words - 1);
    unsigned int size_of_normal_space = free_spaces / number_of_gap;
    unsigned int space_overload = (free_spaces % number_of_gap);

    char *pointer_input = START_ADRESS_OF_INPUT;
    char *pointer_output = START_ADRESS_OF_OUTPUT;

    while (pointer_input <= END_POSITION_OF_LAST_CHAR)
    {
        if ((CONTENT_OF(pointer_input) != FREESPACE)
                && (CONTENT_OF(pointer_input) != END_OF_LINE))
        {
            /*Buchstabe*/
            CONTENT_OF(pointer_output) = CONTENT_OF(pointer_input);
            pointer_output++;
        }
        else if ((CONTENT_OF(pointer_input) == FREESPACE)
                && (CONTENT_OF(pointer_input + 1) != FREESPACE))
        {
            /*Leerzeichen gefunden*/
            unsigned int counter = 0;
            while (counter < size_of_normal_space)
            {
                CONTENT_OF(pointer_output) = FREESPACE;
                pointer_output++;
                counter++;
            }
            if (space_overload > 0)
            {
                CONTENT_OF(pointer_output) = FREESPACE;
                pointer_output++;
                space_overload--;
            }
        }
        pointer_input++;
    }
}