/* 
 * File:   io.c
 * Author: hnzo
 *
 * Created on 24. Oktober 2016, 09:47
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096



enum BIT {
    OFF,
    ON
};

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

unsigned char in_buffer = BUFFER_SIZE;
unsigned char out_buffer = BUFFER_SIZE;


/*
 * 
 */
int main(int argc, char** argv)
{
    printf("456");
    printf("123");
    printf("Hello World!");
    return (EXIT_SUCCESS);
}

BIT get_bit(unsigned char c, int pos) {
    
}

char put_bit(unsigned char c, BIT bit, int pos) {
    
}

BOOL has_next_char(void) {
   
}

unsigned char read_char(void) {
    
}

void write_char(unsigned char c) {
    
}

BOOL has_next_bit(void) {
    
}

BIT read_bit(void) {
    
}

void write_bit(BIT c) {
    
}

void copy_chars(unsigned char in[], unsigned char out[]) {
    
}

void copy_bits(unsigned char in[], unsigned char out[]) {
    
}