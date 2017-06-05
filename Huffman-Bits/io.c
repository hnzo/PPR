/* 
 * File:   io.c
 * Author: hnzo
 *
 * Created on 24. Oktober 2016, 09:47
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 4096



typedef enum {
    OFF,
    ON
} BIT;

typedef enum {
    FALSE,
    TRUE
} BOOL;

BIT get_bit(unsigned char c, int pos);
char put_bit(unsigned char c, BIT bit, int pos);
unsigned char read_char(void);
BOOL has_next_char(void);
void write_char(unsigned char c);
BOOL has_next_bit(void);
BIT read_bit(void);
void write_bit(BIT c);
void copy_chars(unsigned char in[], unsigned char out[]);
void copy_bits(unsigned char in[], unsigned char out[]);

unsigned char in_buffer[BUF_SIZE];
unsigned char out_buffer[BUF_SIZE];
unsigned char mask = 0x80;

int in_buffer_pos = 0;
int out_buffer_pos = 0;
int bit_pos_in = 0;
int bit_pos_out = 0;


/*
 * 
 */
int main()
{
    unsigned char in_a[] = { "Hallo, das ist eine KI aus dem Jahr 2016. WILLKOMMEN \0" };
    unsigned char out_a[BUF_SIZE] = {0};
       
    copy_bits(in_a, out_a);
   
    printf("out-array-finish: %c \n", out_a[0]);
    printf("out-array-finish: %c \n", out_a[1]);
    printf("out-array-finish: %c \n", out_a[2]);
    printf("out-array-finish: %c \n", out_a[3]);
    printf("out-array-finish: %c \n", out_a[4]);
       
    return (EXIT_SUCCESS);
}

BIT get_bit(unsigned char c, int pos) {
    pos = 7 - pos;
    unsigned char erg;
    erg = c & (mask >> pos);
    erg = erg << pos;
    
    
    return (BIT) erg;
}

char put_bit(unsigned char c, BIT bit, int pos) {
    pos = 7 - pos;
    
    if ( bit == ON ) {
        c = c | (mask >> pos);
    } else {
        c = c & ~(mask >> pos);
    }

    return c;
}

BOOL has_next_char(void) {
    BOOL erg = FALSE;
    if(in_buffer[in_buffer_pos] != '\0') {
        
        erg = TRUE;
    } 
    
    return erg;
}

unsigned char read_char(void) {

    return in_buffer[in_buffer_pos];
}

void write_char(unsigned char c) {
    
    out_buffer[out_buffer_pos] = c;
}

BOOL has_next_bit(void) {
    BOOL erg = FALSE;
              
        if(has_next_char()) {
            erg = TRUE;            
        }    
    return erg;
}

BIT read_bit(void) {
    
    return get_bit(read_char(), bit_pos_in);    
}

void write_bit(BIT c) {
    out_buffer[out_buffer_pos] = put_bit(read_char(), c, bit_pos_out);    
}

void copy_chars(unsigned char in[], unsigned char out[]) {
    in_buffer_pos = 0;
    out_buffer_pos = 0;
    bit_pos_in = 0;
    bit_pos_out = 0;
    
    
    memcpy(in_buffer, in, BUF_SIZE);
    
    while(has_next_char()) {
        unsigned char c = read_char();
        write_char(c);
        out_buffer_pos++;
        in_buffer_pos++;
        
    }
    
    memcpy(out, out_buffer, BUF_SIZE);       
}

/**
 * Hier wird das Bitweise kopieren realisiert. Es werden Zeichen aus dem 
 * Eingabepuffer Bitweise gelesen und danach wieder Bitweise in den
 * Ausgabepuffer geschrieben.
 * @param in Eingangs-Array mit den zu kopierenden Daten
 * @param out Das Ausgangs-Array für die geschriebenen Daten
 */
void copy_bits(unsigned char in[], unsigned char out[]) {
    in_buffer_pos = 0;
    out_buffer_pos = 0;
    bit_pos_in = 0;
    bit_pos_out = 0;
    
    
    memcpy(in_buffer, in, BUF_SIZE);    
    
    while(has_next_bit()) {
        BIT c = read_bit();
        write_bit(c);
   
        if((bit_pos_in <= 7) && (bit_pos_out <= 7)) {
            bit_pos_in++;
            bit_pos_out++; 
        } else {
            bit_pos_in = 0;
            bit_pos_out = 0;
            out_buffer_pos++;
            in_buffer_pos++;
        }
    }
    memcpy(out, out_buffer, BUF_SIZE);
}