#include <stdio.h>
#include <stdlib.h>

// Structure to store item details
struct Item {
    double value, weight;
};

// Comparator function to sort items by decreasing value/weight ratio
int compare(const void* a, const void* b) {
    double r1 = ((struct Item*)a)->value / ((struct Item*)a)->weight;
    double r2 = ((struct Item*)b)->value / ((struct Item*)b)->weight;
    return (r2 > r1) ? 1 : -1;
}

// Function to compute maximum value for fractional knapsack
double fractionalKnapsack(double capacity, struct Item items[], int n) {
    // Sort items by value/weight ratio
    qsort(items, n, sizeof(struct Item), compare);

    double totalValue = 0.0; // Resultant value
	int i;
    for (i = 0; i < n; i++) {
        // If full item can be added
        if (items[i].weight <= capacity) {
            capacity -= items[i].weight;
            totalValue += items[i].value;
        } 
        // If only a fraction of item can be added
        else {
            totalValue += items[i].value * (capacity / items[i].weight);
            break; // Knapsack is full
        }
    }

    return totalValue;
}

int main() {
    int n;
    double capacity;

    // Input: Number of items
    printf("Enter number of items: ");
    scanf("%d", &n);

    // Dynamic memory allocation for items
    struct Item* items = (struct Item*)malloc(n * sizeof(struct Item));

    // Input: Values and Weights
    printf("Enter value and weight for each item:\n");
    int i;
    for (i = 0; i < n; i++) {
        printf("Item %d - Value: ", i + 1);
        scanf("%lf", &items[i].value);
        printf("Item %d - Weight: ", i + 1);
        scanf("%lf", &items[i].weight);
    }

    // Input: Maximum capacity of knapsack
    printf("Enter capacity of knapsack: ");
    scanf("%lf", &capacity);

    // Call function and display result
    double maxValue = fractionalKnapsack(capacity, items, n);
    printf("\nMaximum value that can be obtained = %.2lf\n", maxValue);

    // Free allocated memory
    free(items);

    return 0;
}

