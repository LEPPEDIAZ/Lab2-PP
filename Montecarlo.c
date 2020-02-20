/* File:      pi_monte_carlo.c
 * Purpose:   Estimate pi using OpenMP and a monte carlo method
 *
 * Compile:   gcc -fopenmp -o pi_monte_carlo
 *                  pi_monte_carlo.c my_rand.c
 *            *needs my_rand.c, my_rand.h
 *
 * Run:       ./pi_monte_carlo <number of threads>
 *                  <number of tosses>
 *
 * Input:     None
 * Output:    Estimate of pi
 *
 * Note:      The estimated value of pi depends on both the number of
 *            threads and the number of "tosses".
 */
using namespace std; 
  #include<stdlib.h>
  #include <iomanip>

    #include<stdio.h>
    #include<time.h>
    #include <pthread.h>
    #include <iostream> 
    #include <time.h> 
    using namespace std; 
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

/* Serial function */
void Get_args(char* argv[], int* thread_count_p,
      long long int* number_of_tosses_p);
void Usage(char* prog_name);

/* Parallel function */
long long int Count_hits(long long int number_of_tosses, int thread_count);

/*---------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   double pi_estimate;
   int thread_count;
   long long int number_in_circle;
   long long int number_of_tosses;

   if (argc != 3) Usage(argv[0]);
   Get_args(argv, &thread_count, &number_of_tosses);

     clock_t t; 
        t = clock
        ();
  
   number_in_circle = Count_hits(number_of_tosses, thread_count);

    // Recording the end clock tick. 
 t = clock() - t; 
       double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
       printf("\n took %f seconds to execute \n", time_taken);    
       
     

   pi_estimate = 4*number_in_circle/((double) number_of_tosses);
cout << scientific << setprecision(15) << pi_estimate << endl;

   return 0;
}

/*---------------------------------------------------------------------
 * Function:      Count_hits
 * Purpose:       Calculate number of hits in the unit circle
 * In arg:        number_of_tosses, thread_count
 * Return val:    number_in_circle
 */

long long int Count_hits(long long int number_of_tosses, int thread_count) {

    int aciertos_en_circulo = 0;
    double x,y,toss,distancia_cuadrada;

    #pragma omp parallel firstprivate(x, y,distancia_cuadrada , toss) shared(aciertos_en_circulo) num_threads(thread_count)
    for (toss = 0; toss < number_of_tosses; toss++) {
        x = (double)random()/RAND_MAX;
        y = (double)random()/RAND_MAX;
        distancia_cuadrada = x*x + y*y;
        if (distancia_cuadrada <= 1) aciertos_en_circulo ++;
    }
    return aciertos_en_circulo ;

}  /* Count_hits */

/*---------------------------------------------------------------------
 * Function:  Usage
 * Purpose:   Print a message showing how to run program and quit
 * In arg:    prog_name:  the name of the program from the command line
 */

void Usage(char prog_name[] /* in */) {
   fprintf(stderr, "usage: %s ", prog_name);
   fprintf(stderr, "<number of threads> <total number of tosses>\n");
   exit(0);
}  /* Usage */

/*------------------------------------------------------------------
 * Function:    Get_args
 * Purpose:     Get the command line args
 * In args:     argv
 * Out args:    thread_count_p, number_of_tosses_p
 */

void Get_args(
           char*           argv[]              /* in  */,
           int*            thread_count_p      /* out */,
           long long int*  number_of_tosses_p  /* out */) {

   *thread_count_p = strtol(argv[1], NULL, 10);
   *number_of_tosses_p = strtoll(argv[2], NULL, 10);
}  /* Get_args */


