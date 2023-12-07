/******************************************************************************

The code must take an n input and store them into array, the array then should be sorted as a pair before it begin the evaluation on how many vehicle needed to satisfied the order
The vehicle must return and depature should be in 24 format with only take hour value. 
The code should be able to calculate the optimal drivers needed in 1-2 days because the order most be delivered at the optimal timing.

*******************************************************************************/
#include <stdio.h>

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

// Function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform a bubble sort on the times array based on return times (d)
void bubbleSort(int s[], int d[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (d[j] > d[j + 1]) {
                // Swap return times (d) and corresponding start times (s)
                swap(&d[j], &d[j + 1]);
                swap(&s[j], &s[j + 1]);
            }
        }
    }
}

int main() {
    int n; // Number of orders
    scanf("%d", &n);
    int s[n], d[n];

    // Input: s1, d1, s2, d2, s3, d3 (departure and return times for three orders)
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &s[i], &d[i]);
    }

    // Sort the orders based on return times (d)
    bubbleSort(s, d, n);

    // Calculate and print the minimum number of vehicles needed
    int vehiclesNeeded = minVehiclesNeeded(s, d, n);

    if (vehiclesNeeded != -1) {
        printf("%d\n", vehiclesNeeded);
    } else {
        printf("Cannot accommodate all orders.\n");
    }

    return 0;
}
