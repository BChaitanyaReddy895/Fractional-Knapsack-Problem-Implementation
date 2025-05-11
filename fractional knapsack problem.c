#include <stdio.h>
#include <stdlib.h>

// Structure to store item details
struct Item {
    double value, weight;
    int index; // original index of item for display
};

// Comparator function to sort items by decreasing value/weight ratio
int compare(const void* a, const void* b) {
    double r1 = ((struct Item*)a)->value / ((struct Item*)a)->weight;
    double r2 = ((struct Item*)b)->value / ((struct Item*)b)->weight;
    return (r2 > r1) ? 1 : -1;
}

// Function to compute maximum value for fractional knapsack
double fractionalKnapsack(double capacity, struct Item items[], int n) {
    qsort(items, n, sizeof(struct Item), compare);

    double totalValue = 0.0;
    printf("\nItems selected into knapsack:\n");
    printf("---------------------------------------------------\n");
    printf("| %-8s | %-10s | %-10s | %-9s |\n", "Item No", "Weight Taken", "Value Gained", "Fraction");
    printf("---------------------------------------------------\n");
	int i;
    for (i = 0; i < n; i++) {
        if (capacity <= 0) break;

        if (items[i].weight <= capacity) {
            capacity -= items[i].weight;
            totalValue += items[i].value;
            printf("| %-8d | %-10.2lf | %-10.2lf | %-9.2lf |\n", 
                   items[i].index + 1, items[i].weight, items[i].value, 1.0);
        } else {
            double fraction = capacity / items[i].weight;
            double takenValue = items[i].value * fraction;
            totalValue += takenValue;
            printf("| %-8d | %-10.2lf | %-10.2lf | %-9.2lf |\n", 
                   items[i].index + 1, capacity, takenValue, fraction);
            capacity = 0; // Knapsack is full
        }
    }

    printf("---------------------------------------------------\n");
    return totalValue;
}

int main() {
    int n;
    double capacity;

    printf("=== Fractional Knapsack Problem ===\n");

    // Input number of items
    printf("Enter the number of items: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input! Number of items must be a positive integer.\n");
        return 1;
    }

    // Allocate memory
    struct Item* items = (struct Item*)malloc(n * sizeof(struct Item));
    if (items == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Input item values and weights
    int i;
    for (i = 0; i < n; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("  Enter value: ");
        if (scanf("%lf", &items[i].value) != 1 || items[i].value < 0) {
            printf("  Invalid input for value.\n");
            free(items);
            return 1;
        }

        printf("  Enter weight: ");
        if (scanf("%lf", &items[i].weight) != 1 || items[i].weight <= 0) {
            printf("  Invalid input for weight.\n");
            free(items);
            return 1;
        }

        items[i].index = i; // Store original index
    }

    // Input knapsack capacity
    printf("\nEnter the capacity of the knapsack: ");
    if (scanf("%lf", &capacity) != 1 || capacity <= 0) {
        printf("Invalid input! Capacity must be a positive number.\n");
        free(items);
        return 1;
    }

    // Compute and print the maximum value
    double maxValue = fractionalKnapsack(capacity, items, n);
    printf("\n>> Maximum value that can be obtained = %.2lf\n", maxValue);

    // Free memory
    free(items);
    return 0;
}
