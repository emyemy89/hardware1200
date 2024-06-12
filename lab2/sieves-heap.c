//
//  sieves-heap.c
//  
//
//  Created by Emi Paraschiv on 01.02.2024.
//

#include <stdio.h>
#include <stdlib.h>
#define COLUMNS 6
void print_sieve(int n);
void print_number(int n);
int currentColumn = 0;


int main(int argc, char *argv[]){
  if(argc == 2)
    //print_primes(atoi(argv[1]));
      print_sieve(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}


void print_number(int n){
    printf("%10d ", n);
    currentColumn++;
      if(currentColumn>=COLUMNS){
        printf("\n");
        currentColumn = 0;
      }
}



void print_sieve(int n){
    int* primes=(int*)malloc((n+1)*sizeof(int)); //  Create an array of size n+1 to include n
    //check if the array was created
    if (primes == NULL) {
            printf("Failed to allocate memory\n");
            return;
    }

        // Initialize the array
        for(int i = 2; i <= n; i++) {
            primes[i] = 1; // Assume all numbers are prime initially
        }
        // Implement the Sieve algorithm
        for(int i = 2; i*i <= n; i++) {
            if(primes[i]) {
                for(int j = i*i; j <= n; j += i) {
                    primes[j] = 0; // Mark multiples of i as not prime
                }
            }
        }
        // Print the primes
        for(int i = 2; i <= n; i++) {
            if(primes[i]) {
                print_number(i); // Print the prime number
            }
        }
        if(currentColumn != 0) {
            printf("\n");
        }
    free(primes);
}
    

