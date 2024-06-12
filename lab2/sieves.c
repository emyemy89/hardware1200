//
//  sieves.c
//  
//
//  Created by Emi Paraschiv on 31.01.2024.
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
    int primes[n+1]; //  Create an array of size n+1 to include n

        // Initialize the array
        for(int i = 2; i <= n; i++) { //change to <n
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
        for(int i = 2; i <= n; i++) { //change to <n
            if(primes[i]) {
                print_number(i); // Print the prime number
            }
        }
        if(currentColumn != 0) {  //prints a neew line even though the last line
            printf("\n");         // may not have 6 elements in order to avoid
        }                         // printing '%' in the end
}
