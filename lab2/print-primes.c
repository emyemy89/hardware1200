/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

void print_number(int n);

int is_prime(int n);

void print_primes(int n);

int currentColumn = 0; // currentColumn needs to be a global variable


void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS
    
        
    

  /*printf("%10d ", 2);
  printf("%10d ", 3);
  printf("%10d ", 5);
  printf("%10d ", 7);
  printf("%10d ", 11);
  printf("%10d ", 13);
  printf("\n");
  printf("%10d ", 17);
  printf("%10d ", 19);

  printf("\n");*/
    
    for (int i = 2; i <= n; i++) {
            if (is_prime(i)) {
                print_number(i);
            }
        }
        printf("\n");

}

void print_number(int n){
    printf("%10d ", n);
    currentColumn++;
      if(currentColumn>=COLUMNS){
        printf("\n");
        currentColumn = 0;
      }
}

int is_prime(int n){
    int e=0;
    for(int i=1;i<=n;i++){
        if(n%i==0)
            e++;
    }
        if(e>=3)
            return 0;
        else
            return 1;
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

 
