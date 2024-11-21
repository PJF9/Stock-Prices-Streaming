#include "latency_utils.h"
#include <time.h>
#include <stdio.h>


// Declare the latency variables
clock_t startTime;
clock_t endTime;
int mean_latency[120];
int last_idx = 0;


/**
 * @brief Starts the latency measurement by recording the current time.
 *
 * This function sets the global `startTime` variable to the current clock time.
 */
void start_latency_measurement() {
    startTime = clock();
}


/**
 * @brief Ends the latency measurement by recording the current time.
 *
 * This function sets the global `endTime` variable to the current clock time.
 */
void end_latency_measurement() {
    endTime = clock();
}


/**
 * @brief Calculates the mean of recorded latency values.
 *
 * This function computes the average of the latency values stored in the
 * `mean_latency` array up to the current `last_idx`.
 *
 * @return The mean latency as a floating-point number.
 */
float calculate_mean() {
    float mean = 0;
    for (int i = 0; i < last_idx; ++i) {
        mean += mean_latency[i];
    }
    return mean / last_idx;
}


/**
 * @brief Reports the current latency and the mean latency.
 *
 * This function calculates the latency of the current operation based on the
 * difference between `endTime` and `startTime`. The latency is stored in the
 * `mean_latency` array and added to the mean calculation. It then prints the
 * current latency and mean latency to the console.
 */
void latency_report() {
    // Calculate the latency of the experiment
    double latency = ((double)(endTime - startTime)) / CLOCKS_PER_SEC * 1000; // Convert to milliseconds

    mean_latency[last_idx] = latency;
    last_idx += 1;

    // Print current latency and mean latency    
    printf("Latency for API: %.2f ms (mean: %.2f ms)\n", latency, calculate_mean());
}
