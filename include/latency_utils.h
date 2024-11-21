#ifndef LATENCY_H
#define LATENCY_H


/**
 * @brief Starts the latency measurement by recording the current time.
 *
 * This function sets the global `startTime` variable to the current clock time.
 */
void start_latency_measurement();


/**
 * @brief Ends the latency measurement by recording the current time.
 *
 * This function sets the global `endTime` variable to the current clock time.
 */
void end_latency_measurement();


/**
 * @brief Reports the current latency and the mean latency.
 *
 * This function calculates the latency of the current operation based on the
 * difference between `endTime` and `startTime`. The latency is stored in the
 * `mean_latency` array and added to the mean calculation. It then prints the
 * current latency and mean latency to the console.
 */
void latency_report();


#endif // LATENCY_H
