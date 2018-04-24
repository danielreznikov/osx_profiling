
/*
 * Authors: Daniel Reznikov, Aaaron Trefler, Rebecca McKinley
 *
 * Utility functions for project
*/
#ifndef UTILS_C
#define UTILS_C

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

/* OSX includes only */
#include <mach/mach_time.h>
#include <mach/mach.h>
#include <mach/thread_policy.h>


/* Prints the header for the output table */
void printHeader(char *title) {
    printf("\n==========%s==========\n", title);
    printf("|==============|============|\n");
    printf("|  Experiment  |  Overhead  |\n");
    printf("|==============|============|\n");
}

/* Prints a single entry of the output table */
void printEntry(int experimentNumber, uint64_t entry) {
    printf("|%*s%-8d| %*s%-9" PRIu64 "|\n", 6, " ", experimentNumber, 2, " ", entry);
}

/* Prints the average and stdev in the format of the output table */
void printStats(float average, float std) {
    printf("|--------------|------------|\n");
    printf("|   Average    | %*s%-10.3f|\n", 1, " ", average);
    printf("|--------------|------------|\n");
    printf("|   Std Dev    | %*s%-10.3f|\n", 1, " ", std);
    printf("|--------------|------------|\n");
}

/* Compute standard of deviation of a list of numbers */
void stats(float data[], size_t numElems, float *avg, float *std) {

    float sum = 0.0;
    float mean = 0.0;
    float squared_err = 0.0;
    int i = 0;

    for(; i<numElems; ++i) {
        sum += data[i];
    }

    for(i = 0; i < numElems; ++i)
        squared_err += pow(data[i] - mean, 2);

    *std = sqrt(squared_err/numElems);
    *avg = sum/numElems;
}

/* Write experiment results to file. Assumes 10 trials per condition */
void write_results_matrix_procedure_call_overhead_exp(char filename[100], float experiment_results[8][10]) {

    FILE *fp;
    int i, j;
    char heading[100] = "Experiment, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10";

    fp=fopen(filename, "w+");

    fprintf(fp, "%s", heading);
    for(i=0; i<8; i++){
        fprintf(fp,"\n%d",i+1);
        for(j=0; j<10; j++)
            fprintf(fp, ",%f ", experiment_results[i][j]);
    }
    fprintf(fp, "\n");
    fclose(fp);

    return;
}

/* Write experiment results to file. Assumes 10 trials were run. */
void write_results_array(char filename[100], float experiment_results[10]) {
    int TRIALS = 10;

    FILE *fp;
    int i, j;
    char heading[100] = "Experiment, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10";

    fp=fopen(filename, "w+");

    fprintf(fp, "%s", heading);
    fprintf(fp,"%d", 0);
    for(i=0; i<TRIALS; i++){
        fprintf(fp, ",%f ", experiment_results[i]);
    }
    fprintf(fp, "\n");
    fclose(fp);

    return;
}

#endif
