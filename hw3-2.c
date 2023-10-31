#include <stdio.h>
#include <stdlib.h>

// Function to calculate the minimum number of vehicles needed
int minVehiclesNeeded(int s[], int d[], int n) {
    int vehiclesNeeded = 0;
    int currentEndTime = 0;

    for (int i = 0; i < n; i++) {
        if (d[i] > 24) {
            // Reject orders that have a return time greater than 24
            return -1;
        }

        if (s[i] > currentEndTime) {
            // If the order can start after the current driver's end time, assign it to the current driver.
            currentEndTime = d[i];
            vehiclesNeeded++;
        } else if (d[i] <= currentEndTime) {
            // If the order can be finished before or at the same time as the current driver's end time, do nothing.
            continue;
        } else {
            // If the order starts before the current driver's end time but ends after, assign it to a new driver.
            vehiclesNeeded++;
            currentEndTime = d[i];
        }
    }

    return vehiclesNeeded + 1; // Add 1 for the first driver
}

// Function to sort values and store in the array
void sortAndStore(int *d_array, int *r_array, int *n, int d, int r, int max_pairs) {
    if (d > r) {
        // Swap d and r if d is greater than r
        int temp = d;
        d = r;
        r = temp;
    }

    if (*n < max_pairs) {
        d_array[*n] = d;
        r_array[*n] = r;
        (*n)++;
    }
}

int main() {
    int s_array[100]; // Start times
    int d_array[100]; // Departure times
    int n = 0; // Initialize the order counter
    int p; // Number of drivers

    printf("Enter the number of drivers (p): ");
    scanf("%d", &p);

    while (1) {
        int s, d;
        int result = scanf("%d %d", &s, &d);

        if (result == EOF) {
            // End-of-file reached
            break;
        } else if (result != 2) {
            // Invalid input, skip and continue
            printf("Invalid input. Skipping...\n");
            while (fgetc(stdin) != '\n');
            continue;
        }

        s_array[n] = s;
        d_array[n] = d;
        n++;

        if (n == 100) {
            printf("Reached the maximum number of orders (100).\n");
            break;
        }
    }

    if (n == 0) {
        printf("No orders to schedule.\n");
        return 0;
    }

    // Sort the orders based on departure times
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (d_array[j] > d_array[j + 1]) {
                int temp = d_array[j];
                d_array[j] = d_array[j + 1];
                d_array[j + 1] = temp;
                temp = s_array[j];
                s_array[j] = s_array[j + 1];
                s_array[j + 1] = temp;
            }
        }
    }

    // Initialize an array of arrays to store driver schedules
    int **driverSchedules = (int **)malloc(p * sizeof(int *));
    for (int i = 0; i < p; i++) {
        driverSchedules[i] = (int *)malloc(100 * sizeof(int));
    }

    // Initialize array to track driver schedule sizes
    int *scheduleSizes = (int *)malloc(p * sizeof(int));
    for (int i = 0; i < p; i++) {
        scheduleSizes[i] = 0;
    }

    // Assign orders to drivers
    for (int i = 0; i < n; i++) {
        int assignedDriver = -1;
        for (int j = 0; j < p; j++) {
            if (s_array[i] >= d_array[i] || (scheduleSizes[j] > 0 && s_array[i] < driverSchedules[j][scheduleSizes[j] - 1])) {
                // If the order has no duration (s >= d) or it overlaps with a previous order of the driver, skip it.
                continue;
            }

            assignedDriver = j;
            driverSchedules[j][scheduleSizes[j]++] = d_array[i];
            break;
        }

        if (assignedDriver == -1) {
            printf("Cannot accommodate all orders. Additional drivers needed.\n");
            for (int i = 0; i < p; i++) {
                free(driverSchedules[i]);
            }
            free(driverSchedules);
            free(scheduleSizes);
            return 0;
        }
    }

    // Print driver schedules
    for (int i = 0; i < p; i++) {
        printf("Driver %d Schedule: ", i + 1);
        for (int j = 0; j < scheduleSizes[i]; j++) {
            printf("(%d, %d) ", s_array[j],
