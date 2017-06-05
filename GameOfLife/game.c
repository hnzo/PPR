/**
 * Das Programm erstellt ein Spielfeld mit "Lebewesen" 
 * File:   game.c
 * Author: Dimitrij Rybinkin
 *
 * Created on 6. November 2014, 14:43
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALL_ROWS 10
#define ALL_COLUMNS 10
#define BYTE_SIZE 8
#define MAX_CELLS ALL_ROWS*ALL_COLUMNS
#define FREE_CELLS (8-(MAX_CELLS % 8))
#define ALL_BYTES (FREE_CELLS == 0) ? (MAX_CELLS / BYTE_SIZE):((MAX_CELLS / BYTE_SIZE) + 1)


typedef enum
{
    DEAD,
    ALIVE
} BOOL;


/**
 * Print_generation wandelt eine gegebene Game of Life - Generation in ein
 * Spielfeld mit den dazugehoerigen Lebewesen um.
 */
void print_generation(void);
/**
 * Wie auch der Name schon sagt, werden in dieser Funktion Horizontale Linien
 * ausgegeben. Diese Funktion gehoert zu der Print Funktion.
 */
void print_horizontal_line(void);
/**
 * Diese Funktion uebergibt mit Ihrem parameter einen String an das aktuelle 
 * Generationen Array. Dadurch wird die Generation die im String stand nun im
 * Generationen Array stehen.
 * @param string Beinhaltet eine komplette Generation
 */
void set_generation_from_string(char string[]);
/**
 * Mit dieser Funktion ist es moeglich aus einem Generationen Array die 
 * Generation rauszunehmen und diese in einen String zu verstauen.
 * @param String Speicher fuer die gewollte Generation
 */
void get_generation_as_string(char String[]);
/**
 * Die set_next_generation ueberprueft wie eine Generation sich entwickelt.
 * Also im einzelnen heisst das ob ein Lebewesen genug Nachbarn hat zum 
 * ueberleben bzw. es so viele Nachbarn gibt, dass dort ein Lebewesen entstehen
 * kann oder eben Sterben bei ungenuegend Nachbarn.
 * @return 
 */
BOOL set_next_generation(void);
/**
 * Diese Funktion ist das rote Band, dass durch dieses Programm laeuft.
 * Hier werden die print Funktionen aufgerufen und die laufzeit fuer die 
 * Berechnung der Generationen festgelegt.
 * @param max_generations Maximale Generationen Anzahl
 */
void game_of_life(int max_generations);
/**
 * Set_bit setzt in dem Array, welches in den Parametern steht , an der Position
 * welche auch in den Parametern stehen, eine '1'.
 * @param gen Speicherort der Generation
 * @param col Spalte in der das Bit steht
 * @param row Zeile in der das Bit steht
 */
void set_bit(unsigned char gen[], int col, int row);
/**
 * Get_bit holt an der Position, welches aus den Parametern Berechnet wird, das
 * Bit 'raus'.
 * @param col Spalte des Bits
 * @param row Zeile des Bits
 * @return liefert einen Boolean Wert
 */
BOOL get_bit(int col, int row);
/**
 * Get_neighbours zaehlt die Nachbarn fuer das Bit welches mit den Koordinaten
 * im Parameter berechnet wird.
 * @param col Spalte des Bits
 * @param row Zeile des Bits
 * @return Liefert einen Boolean wert
 */
int get_neighbours(int col, int row);
/**
 * Diese Funktion repraesentiert die Rechteck Formel, mit der die Positionen
 * Berechnet werden.
 * @param col
 * @param row
 * @return 
 */
int get_bit_pos(int col, int row);
/**
 * Get_Number_of_byte liefert mir das Byte in welchem eine bestimmte Bitposition
 * steht.
 * @param col Spalte des Bits
 * @param row Zeile des Bits
 * @return Liefert das Byte von einer bestimmten Position
 */
int get_number_of_byte(int col, int row);
/**
 * Gibt die Maske fuer ein bestimmtes Bit wieder.
 * @param col
 * @param row
 * @return 
 */
unsigned char get_mask(int col, int row);

/* Der String in dem die Generation steht. */
unsigned char String [ALL_BYTES];
/* Das ist das Array in dem die Generation steht. */
unsigned char generation[ALL_BYTES];
/* Das ist das Array in dem die naechste Generation gespeichert wird. */
unsigned char next_gen[ALL_BYTES];

int main()
{
    char spielfeld01[] = "1000100001"
            "0000000000"
            "0000000000"
            "0000000000"
            "1000100001"
            "0000000000"
            "0000000000"
            "0000000000"
            "0000000000"
            "1000010001";
    char spielfeld02[] = "1100110001"
            "0000000001"
            "0000000000"
            "1000000000"
            "1000100001"
            "0000010001"
            "0000000000"
            "0000000000"
            "0000100000"
            "1100100011";
    char spielfeld03[] = "1100110011"
            "0100100001"
            "0000000000"
            "1000010000"
            "1000100011"
            "1001000001"
            "0000000000"
            "0000000000"
            "1100110011"
            "1000100001";
    char spielfeld04[] = "1101110011"
            "1101110011"
            "0000000000"
            "1001100011"
            "1100100011"
            "1000010011"
            "0000000000"
            "0000000000"
            "1101110011"
            "1100110011";
    char spielfeld05[] = "1101110011"
            "1101110011"
            "1110010000"
            "1101100011"
            "1101110111"
            "1101110011"
            "0000000000"
            "0000100000"
            "1111110011"
            "1111110011";
    char spielfeld06[] = "1101010011"
            "1000001011"
            "0000010000"
            "0000001101"
            "0000001111"
            "1101011101"
            "0001010000"
            "0110110000"
            "1000000011"
            "1000010011";
    char spielfeld07[] = "1100010111"
            "1100111111"
            "0000010001"
            "0000110011"
            "0100000001"
            "1010010011"
            "1001000000"
            "0111110000"
            "1101110011"
            "0100000011";
    char spielfeld08[] = "1101110011"
            "1100100011"
            "0000000000"
            "1000110011"
            "0100110010"
            "1010010011"
            "1000010000"
            "0000010000"
            "1101110011"
            "1110100011";
    char blinker[] = "0000000000"
            "0000000000"
            "0000000000"
            "0010000000"
            "0010000000"
            "0010000000"
            "0000000000"
            "0000000000"
            "0000000000"
            "0000000000";
    char spielfeld10[] =
            "11010"
            "11001"
            "00001"
            "10000"
            "11100";

    set_generation_from_string(blinker);
    game_of_life(10);

    return (EXIT_SUCCESS);
}

void game_of_life(int max_generation)
{
    /* Diese Funktion gibt uns die Moeglichkeit generationen auf dem 
     * Bildschirm auszugeben, bis entweder die maximale generation erreicht ist
     * oder wenn es keine weiteren Generationen mehr gibt.
     */
    int generation_count = 1;
    printf("Generation: %d\n", generation_count);
    print_generation();

    while ((generation_count < max_generation) && set_next_generation() == ALIVE)
    {
        generation_count++;
        printf("Generation: %d\n", generation_count);
        print_generation();

        /* Clear Screen anweisung */
        printf("\033c");
    }
    print_generation();


}

void set_generation_from_string(char string[])
{
    int local_rows;
    int local_columns;
    /* Vorbelegung des Generationen Arrays mit '0' */
    memset(generation, 0, ALL_BYTES);

    for (local_columns = 0; local_columns < ALL_COLUMNS; local_columns++)
    {
        for (local_rows = 0; local_rows < ALL_ROWS; local_rows++)
        {
            BOOL creature;

            creature = (string[get_bit_pos(local_columns, local_rows)] == '1'
                    ? ALIVE
                    : DEAD);
            if (creature == ALIVE)
            {
                set_bit(generation, local_columns, local_rows);
            }
        }
    }
}

/*Funktionen zum bestimmen der nächsten Generation*/

BOOL set_next_generation()
{
    /* Hier werden vor jedem Aufbau einer Generation die unnoetigen 
     * Stellen rausgelöscht */
    unsigned char next_gen[ALL_BYTES] = {0};
    BOOL creature_status = DEAD;
    int local_cols;
    int local_rows;
    for (local_cols = 0; local_cols < ALL_COLUMNS; local_cols++)
    {
        for (local_rows = 0; local_rows < ALL_ROWS; local_rows++)
        {
            BOOL creature = get_bit(local_cols, local_rows);
            int neighbours;

            neighbours = get_neighbours(local_cols, local_rows);

            if (creature == DEAD)
            {
                if (neighbours == 3)
                {
                    /* Hier entsteht ein Lebewesen, da es 3 Nachbarn gibt */
                    creature_status = ALIVE;
                    set_bit(next_gen, local_cols, local_rows);
                }
            }
                /* Fuer den Fall, dass ein Lebewesen existiert wird geprueft ob es 
                 * denn auch in seinem Umfeld ueberleben kann.
                 */
            else if (neighbours == 2 || neighbours == 3)
            {
                /* Lebewesen setzen, denn es wird ueberleben */
                set_bit(next_gen, local_cols, local_rows);
            }
            else
            {
                creature_status = ALIVE;
            }
        }
    }
    if (creature_status)
    {
        memcpy(generation, next_gen, ALL_BYTES + 1);
    }
    return creature_status;
}

int get_neighbours(int col, int row)
{
    int counter;
    int neighbour_row;
    int neighbour_col;
    BOOL neighbour;
    counter = 0;
    
    for (neighbour_row = row - 1; neighbour_row <= row + 1 
            && counter < 4; neighbour_row++)
    {
        for (neighbour_col = col - 1; neighbour_col <= col + 1 
                && counter < 4; neighbour_col++)
        {
            if (neighbour_col < 0
                    || neighbour_col >= ALL_COLUMNS
                    || neighbour_row < 0
                    || neighbour_row >= ALL_ROWS
                    || ((neighbour_col == col) && (neighbour_row == row)))
            {
                continue;
            }


            neighbour = get_bit(neighbour_col, neighbour_row);

            if (neighbour == ALIVE)
            {
                counter++;
            }
        }
    }
    return counter;
}

void set_bit(unsigned char gen[], int col, int row)
{
    int byte;

    byte = get_number_of_byte(col, row);

    gen[byte] = gen[byte] | get_mask(col, row);
}

BOOL get_bit(int col, int row)
{
    BOOL output = DEAD;

    int byte;
    byte = get_number_of_byte(col, row);
    
    /*;   (0010 0110) & (0010 0000) => 0010 0000 == 0 | >0*/
    if ((generation[byte] & get_mask(col, row)) > 0)
    {
        output = ALIVE;
    }
    return output;
}

/* Rechteckformel zur Berechnung der Positionen im Array,String und Spielfeld */
int get_bit_pos(int col, int row)
{
    return (col * ALL_COLUMNS) + row;
}

int get_number_of_byte(int col, int row)
{
    /* Gibt mir das Byte im welchen eine bestimmte Bit Position steht.*/
    int byte;
    int bit;
    int cell;

    cell = get_bit_pos(col, row);
    bit = cell % 8;

    /* '+1' wegen der Differenz in der Startposition */
    byte = (cell - bit + 1) / 8;
    return byte;
}

unsigned char get_mask(int col, int row)
{
    unsigned char mask;
    int shift;

    int bit;
    bit = (get_bit_pos(col, row)) % 8;

    mask = 1; /*00000001*/
    shift = 7 - bit;
    mask <<= (shift); /*10000000*/

    return mask;
}

void get_generation_as_string(char string[])
{
    int local_rows;
    int local_columns;

    /* Es wird ueber das Spielfeld iteriert. An jeder Position wird erfragt, ob
     * an dieser ein lebendes Lebewesen existiert, falls ja wird an dieser 
     * Position mit der Rechteckformel eine '1' im String gesetzt. Ansonsten 
     * wird eine Null gesetzt.
     */
    for (local_columns = 0; local_columns < ALL_COLUMNS; local_columns++)
    {
        for (local_rows = 0; local_rows < ALL_ROWS; local_rows++)
        {
            BOOL creature = get_bit(local_columns, local_rows);
            string[get_bit_pos(local_columns, local_rows)]
                    = (creature == ALIVE ? '1' : '0');
        }
    }
    /* Stringgroesse + 1, da Nullbyte ein weiteres Stringfeld einnehmen muss.*/
    string[(ALL_ROWS*ALL_COLUMNS)] = '\0';
}

void print_generation(void)
{

    int x_coordinate;
    int y_coordinate;
    int slowdown_value;
    char creature_symbol;

    for (x_coordinate = 0; x_coordinate < ALL_ROWS; x_coordinate++)
    {
        print_horizontal_line();

        for (y_coordinate = 0; y_coordinate < ALL_COLUMNS; y_coordinate++)
        {
            BOOL creature = get_bit(x_coordinate, y_coordinate);
            creature_symbol = (creature == ALIVE) ? 'o' : ' ';

            printf("| %c ", creature_symbol);
        }
        printf("|\n");

    }

    print_horizontal_line();

    for (slowdown_value = 0; slowdown_value < 500000000; slowdown_value++)
    {
    }

}

void print_horizontal_line(void)
{
    int counter;
    for (counter = 0; counter < ALL_COLUMNS; counter++)
    {
        printf("+---");

    }
    printf("+\n");
}

