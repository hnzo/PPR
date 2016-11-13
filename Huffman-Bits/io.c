/* 
 * File:   io.c
 * Author: hnzo
 *
 * Created on 24. Oktober 2016, 09:47
 */

#include <stdio.h>
#include <stdlib.h>

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

unsigned char in_buffer[BUF_SIZE] = { "Hallo, das ist eine KI aus dem Jahr 2016. WILLKOMMEN" };
unsigned char out_buffer[BUF_SIZE];
unsigned char mask = 0x80;
int in_buffer_pos = 0;
int out_buffer_pos = 0;
int bit_pos = 0;


/*
 * 
 */
int main(int argc, char** argv)
{
    put_bit(in_buffer[0], ON, 2);
    put_bit(in_buffer[0], ON, 0);
  
    /*
    printf("H: %d", get_bit(in_buffer[1], 0));
    printf("%d", get_bit(in_buffer[1], 1)); //1
    printf("%d", get_bit(in_buffer[1], 2));
    printf("%d", get_bit(in_buffer[1], 3));
    printf("%d", get_bit(in_buffer[1], 4)); //1
    printf("%d", get_bit(in_buffer[1], 5));
    printf("%d", get_bit(in_buffer[1], 6));
    printf("%d \n", get_bit(in_buffer[1], 7));
    */
    
    
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
    //in_buffer[0] = c;
    //printf("char: %c \n", c);
    return c;
}

BOOL has_next_char(void) {
    BOOL erg;
    if(in_buffer[in_buffer_pos] != 0) {
        erg = TRUE;
    } else {
        erg = FALSE;
    }
    
    return erg;
}

unsigned char read_char(void) {
    unsigned char uc;
    uc = in_buffer[in_buffer_pos];
    in_buffer_pos++;
    
    return uc;
}

void write_char(unsigned char c) {
    while(out_buffer[out_buffer_pos] > 0) {
        out_buffer_pos++;
    }
    out_buffer[out_buffer_pos] = c;
}

BOOL has_next_bit(void) {
    BOOL erg = FALSE;
    unsigned char uc;
    uc = read_char();
    
    for(int i = 0;i<=7;i++) {
        if(get_bit(uc, i) == ON) {
            erg = TRUE;
        }
    }
    
    return erg;
}

BIT read_bit(void) {
    
}

void write_bit(BIT c) {
    
}

void copy_chars(unsigned char in[], unsigned char out[]) {
    
}

void copy_bits(unsigned char in[], unsigned char out[]) {
    
}