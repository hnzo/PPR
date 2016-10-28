/* 
 * File:   justify_file_main.c
 * Author: Dmitry Rybinkin
 *
 * Created on 24. November 2014, 20:11
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "justify.h"

#define MODE_READ "r"
#define MODE_WRITE "w"

#define HELP "-h"
#define INPUT "-i"
#define OUTPUT "-o"
#define LENGTH "-l"

#define STANDARD_LENGTH 80

static int line_length = STANDARD_LENGTH;

FILE *input_file;
FILE *output_file;

static int handle_command_parameter(int argc, char** argv);
static void justify_file(FILE *p_input_file, FILE *p_output_stream, int length);
static void print_help_information(void);

/**
 * @param argc Anzahl an übergebenen Argumenten.
 * @param argv Übergebene Argumente.
 * @return EXIT_SUCCESS wenn erfolgreicht, sonst EXIT_FAILURE
 */

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        handle_command_parameter(argc, argv);
    }
    else
    {
        printf("Keine Parameter angegeben.\n"
               "Erforderliche Parameter -i.\n"
               "Mehr Informationen unter -h\n");
        exit(EXIT_FAILURE);
    }

    

    if (input_file != NULL)
    {
        justify_file(input_file, output_file, line_length);
    }

    return (EXIT_SUCCESS);
}


static void justify_file(FILE *p_input_file, FILE *p_output_stream, int length)
{
    /* Aktuelle Eingabezeile */
    char c_line[1000];

    /* Aktuelle Ausgabezeile */
    

    /* Referenz auf aktuelle Eingabezeile */
    char *p_c_line = c_line;

    /* Referenz auf aktuelle Ausgabezeile */


    /* Einlesen der ersten Eingabzeile und überschreiben des Zeilenumbruchs */
    fgets(p_c_line, 999, p_input_file);


    /* Iteration über alle Eingabezeilen */
    int i = 0;
    while (i < 13)
    {
        char o_line[1000];
        memset(o_line, '\0', 1000);
        char *p_o_line = o_line;
        /* Formatierung der aktuellen Eingabezeile */
        justify_line(p_c_line, length, p_o_line);

        /* Schreiben der formatierten Zeile in die Ausgabestream */
        fputs(p_o_line, p_output_stream);
        printf("%s", p_o_line);

        /* Setze Zeilenumbruch am Ende der Zeile 
        fputc('\n', p_output_stream);*/

        /* Einlesen der nächsten Zeile und überschreiben des Zeilenumbruchs */
        fgets(p_c_line, 999, p_input_file);

        i++;
    }

}

static void print_help_information(void)
{
    printf("Befehlsliste:\n");
    printf("-i [file.txt] \t Angabe der Quelldatei. (-i mein_unformatierter_text.txt)\n");
    printf("-o [file.txt] \t Angabe der Zieldatei.* (-o mein_formatierter_text.txt)\n");
    printf("-l [zahl] \t Angabe Zielzeilenlänge.* (-l 80)\n\n");
    printf("-h \t\t Aufruf der Hilfe.* (-h)\n\n");
   
}

static int handle_command_parameter(int argc, char** argv)
{
    /* Überspringe ersten Parameterwert (Programmname) */
    argv++;
    while (argc > 1)
    {
        if (strcmp(*argv, HELP) == 0)
        {
            print_help_information();
            return EXIT_SUCCESS;
        }
        else if (strcmp(*argv, INPUT) == 0)
        {
            argv++;
            argc--;
            input_file = fopen(*argv, MODE_READ);
            printf("Lese Datei");

        }
        else if (strcmp(*argv, OUTPUT) == 0)
        {
            argv++;
            argc--;

            output_file = fopen(*argv, MODE_WRITE);
            printf("Erstelle Datei\n");
        }
        else if (strcmp(*argv, LENGTH) == 0)
        {
            argv++;
            argc--;

            line_length = atoi(*argv);
            printf("Setze Länge");
        }
        else
        {
            /* Unbekannter Parameter.*/
            printf("Unbekannter Befehl. %s\n", *argv);
            return EXIT_FAILURE;
        }
        argv++;
        argc--;
    }

    if (input_file == NULL)
    {
        printf("Es wurde keine Datei zum einlesen angegeben.");
        return EXIT_FAILURE;
    }
    else if (input_file == output_file)
    {
        printf("Eingabe und Ausgabedatei sind identisch, "
               "bitte überprüfen sie ihre Angaben.");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}