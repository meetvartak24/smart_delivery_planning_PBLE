#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Function Prototypes
void enterDetails(int *n, int *capacity, int id[], int w[], int p[]);
void displayDetails(int n, int id[], int w[], int p[], float p_w[]);
void calculateRatio(int n, int w[], int p[], float p_w[]);
void sortPackages(int n, int id[], int w[], int p[], float p_w[]);
void findMaxValue(int n, int capacity, int w[], int p[], float fraction[], float *max_profit, float *total_weight);
void displaySelected(int n, int id[], int w[], int p[], float fraction[], float max_profit, float total_weight);

int main() {
    int id[MAX], w[MAX], p[MAX];
    float p_w[MAX] = {0};       // Profit to weight ratios
    float fraction[MAX] = {0};  // Fraction of each package selected (0.0 to 1.0)
    
    int vehicle_capacity = 0;
    int number_of_packages = 0;
    float max_profit = 0;
    float total_weight_used = 0;
    
    int choice;

    // Menu-driven program loop
    while (1) {
        printf("\n=========================================\n");
        printf("       SMART DELIVERY PLANNING MENU      \n");
        printf("=========================================\n");
        printf("1. Enter Package Details\n");
        printf("2. Display Package Details\n");
        printf("3. Calculate Value/Weight Ratio\n");
        printf("4. Sort Packages by Ratio\n");
        printf("5. Find Maximum Value\n");
        printf("6. Display Selected Packages\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enterDetails(&number_of_packages, &vehicle_capacity, id, w, p);
                break;
            case 2:
                if (number_of_packages == 0) printf("Please enter package details first (Option 1).\n");
                else displayDetails(number_of_packages, id, w, p, p_w);
                break;
            case 3:
                if (number_of_packages == 0) printf("Please enter package details first (Option 1).\n");
                else {
                    calculateRatio(number_of_packages, w, p, p_w);
                    printf("Value/Weight ratios calculated successfully.\n");
                }
                break;
            case 4:
                if (p_w[0] == 0 && p[0] != 0) printf("Please calculate ratios first (Option 3).\n");
                else {
                    sortPackages(number_of_packages, id, w, p, p_w);
                    printf("Packages sorted in decreasing order of ratio.\n");
                }
                break;
            case 5:
                if (p_w[0] == 0 && p[0] != 0) printf("Please calculate and sort ratios first.\n");
                else {
                    findMaxValue(number_of_packages, vehicle_capacity, w, p, fraction, &max_profit, &total_weight_used);
                    printf("Maximum value calculation complete. Use Option 6 to view results.\n");
                }
                break;
            case 6:
                if (max_profit == 0) printf("Please calculate the maximum value first (Option 5).\n");
                else displaySelected(number_of_packages, id, w, p, fraction, max_profit, total_weight_used);
                break;
            case 7:
                printf("Exiting program...\n");
                exit(0);
            default:
                // Handling invalid menu choices
                printf("Invalid choice! Please enter a number between 1 and 7.\n");
        }
    }
    return 0;
}

void enterDetails(int *n, int *capacity, int id[], int w[], int p[]) {
    printf("\nEnter the vehicle capacity: ");
    scanf("%d", capacity);

    printf("Enter the number of packages: ");
    scanf("%d", n);

    for (int i = 0; i < *n; i++) {
        printf("\n--- Enter details for Package %d ---\n", i + 1);
        printf("Package ID: ");
        scanf("%d", &id[i]);
        printf("Weight: ");
        scanf("%d", &w[i]);
        printf("Profit/Value: ");
        scanf("%d", &p[i]);
    }
}

void displayDetails(int n, int id[], int w[], int p[], float p_w[]) {
    printf("\n--- Package Details ---\n");
    printf("ID\tWeight\tProfit\tRatio\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%.2f\n", id[i], w[i], p[i], p_w[i]);
    }
}

void calculateRatio(int n, int w[], int p[], float p_w[]) {
    for (int i = 0; i < n; i++) {
        p_w[i] = (float)p[i] / w[i];
    }
}

void sortPackages(int n, int id[], int w[], int p[], float p_w[]) {
    // Bubble sort to arrange packages in decreasing order of Value/Weight ratio
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p_w[j] < p_w[j + 1]) {
                // Swap Ratio
                float temp_pw = p_w[j];
                p_w[j] = p_w[j + 1];
                p_w[j + 1] = temp_pw;

                // Swap ID
                int temp_id = id[j];
                id[j] = id[j + 1];
                id[j + 1] = temp_id;

                // Swap Weight
                int temp_w = w[j];
                w[j] = w[j + 1];
                w[j + 1] = temp_w;

                // Swap Profit
                int temp_p = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp_p;
            }
        }
    }
}

void findMaxValue(int n, int capacity, int w[], int p[], float fraction[], float *max_profit, float *total_weight) {
    *max_profit = 0;
    *total_weight = 0;
    int current_capacity = capacity;

    // Reset fractions to 0 before calculating
    for(int i = 0; i < n; i++) {
        fraction[i] = 0.0;
    }

    for (int i = 0; i < n; i++) {
        if (current_capacity == 0) {
            break; 
        }

        if (w[i] <= current_capacity) {
            // Select complete package
            fraction[i] = 1.0;
            *max_profit += p[i];
            *total_weight += w[i];
            current_capacity -= w[i];
        } else {
            // Select fractional package
            fraction[i] = (float)current_capacity / w[i];
            *max_profit += p[i] * fraction[i];
            *total_weight += w[i] * fraction[i];
            current_capacity = 0; 
        }
    }
}

void displaySelected(int n, int id[], int w[], int p[], float fraction[], float max_profit, float total_weight) {
    printf("\n--- Selected Packages ---\n");
    printf("ID\tWeight\tProfit\tFraction Selected\n");
    
    for (int i = 0; i < n; i++) {
        if (fraction[i] > 0.0) {
            printf("%d\t%d\t%d\t%.2f\n", id[i], w[i], p[i], fraction[i]);
        }
    }
    
    printf("\nTotal Weight Used: %.2f\n", total_weight);
    printf("Maximum Value/Profit Obtained: %.2f\n", max_profit);
}