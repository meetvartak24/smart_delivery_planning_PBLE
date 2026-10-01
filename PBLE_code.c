# include <stdio.h>
# include <conio.h>
# include <stdlib.h>

int main(){
    int package_id,weight,profit;
    float profit_per_weight;
    int vehicle_capacity;
    int number_of_packages;
    int id[100], w[100], p[100],p_w[100];

    printf("Enter the vehicle capacity: ");
    scanf("%d", &vehicle_capacity);

    printf("Enter the number of packages: ");
    scanf("%d", &number_of_packages);

    for(int i = 0; i < number_of_packages; i++) {

        printf("---------------Enter the package details (id, weight, profit):----------------\n");

        printf("package_id :");
        scanf("%d", &package_id);

        printf("weight :");
        scanf("%d", &weight);

        printf("profit :");
        scanf("%d", &profit);

        profit_per_weight = (float)profit / weight;
        
        id[i] = package_id;
        w[i] = weight;
        p[i] = profit;
        p_w[i] = profit_per_weight;

        printf("profit_per_weight : %.2f\n", profit_per_weight);

        printf("------------------------------------------------------------\n");
    } 

    for(int i = 0; i < number_of_packages; i++) {
        for(int j = i + 1; j < number_of_packages; j++) {
            if(p_w[i] < p_w[j]) {
                float temp = p_w[i];
                p_w[i] = p_w[j];
                p_w[j] = temp;

                int temp_id = id[i];
                id[i] = id[j];
                id[j] = temp_id;

                int temp_weight = w[i];
                w[i] = w[j];
                w[j] = temp_weight;

                int temp_profit = p[i];
                p[i] = p[j];
                p[j] = temp_profit;
            }
        }
    }

    for(int i = 0; i < number_of_packages; i++) {
        if(vehicle_capacity == 0) {
            break;
        }

        if(w[i] <= vehicle_capacity) {
            printf("Package ID: %d, Weight: %d, Profit: %d\n", id[i], w[i], p[i]);
            vehicle_capacity -= w[i];
        } else {
            float fraction = (float)vehicle_capacity / w[i];
            printf("Package ID: %d, Weight: %.2f, Profit: %.2f\n", id[i], vehicle_capacity, p[i] * fraction);
            vehicle_capacity = 0;
        }
    }

    return 0;   
}