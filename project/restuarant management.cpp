#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ORDERS 100

// Define the structure for each order
typedef struct {
    int customerId;
    int burstTime; // total burst time for the order
    int totalBill;
    char *items[10]; // Array of item names
    int quantities[10]; // Quantities of each item
    int itemCount; // Number of items in the order
} Order;

void displayMenu();
void handleOrder(Order *order, int *orderIndex);
void displayOrderSummary(Order *order);
void processOrders(Order orders[], int orderCount);

int main() {
    int choice;
    Order orders[MAX_ORDERS];
    int orderIndex = 0;
    
    printf("Welcome to the restaurant! Please choose an option:\n");
    printf("1. Place an order\n");
    printf("2. Exit\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Take customer orders
        while (1) {
            Order currentOrder;
            printf("\nCustomer %d, please place your order.\n", orderIndex + 1);
            handleOrder(&currentOrder, &orderIndex);
            orders[orderIndex] = currentOrder; // Store the order in the orders array
            orderIndex++;

            printf("\nOrder summary for Customer %d:\n", orderIndex);
            displayOrderSummary(&currentOrder);
        

            printf("\nDo you want to add another customer? (1 for Yes, 0 for No): ");
            int addMore;
            scanf("%d", &addMore);
            if (!addMore) break;
        }

        // After all customers have placed orders, process the orders based on SJF
        processOrders(orders, orderIndex);
    } else if (choice == 2) {
        printf("Thank you for visiting. Have a great day!\n");
    } else {
        printf("Invalid choice. Please restart the system.\n");
    }

    return 0;
}

void displayMenu() {
    printf("\nHere is our menu featuring famous Pakistani dishes:\n");
    printf("+-----------------------------------+----------------+------------------+\n");
    printf("| Item                              | Burst Time (BT) | Price (Rs.)     |\n");
    printf("+-----------------------------------+----------------+------------------+\n");
    printf("| 1. Chicken Biryani                | 3              | 300              |\n");
    printf("| 2. Nihari                         | 3              | 400              |\n");
    printf("| 3. Seekh Kebabs                   | 2              | 250              |\n");
    printf("| 4. Karahi                         | 4              | 600              |\n");
    printf("| 5. Peshawari Chapli Kebabs        | 3              | 500              |\n");
    printf("| 6. Paratha Roll                   | 2              | 150              |\n");
    printf("| 7. Naan                           | 1              | 50               |\n");
    printf("| 8. Sada Roti                      | 1              | 20               |\n");
    printf("| 9. Lassi                          | 2              | 100              |\n");
    printf("| 0. Finish ordering                | -              | -                |\n");
    printf("+-----------------------------------+----------------+------------------+\n");
}


void handleOrder(Order *order, int *orderIndex) {
    int foodChoice, quantity;
    int totalBurstTime = 0;  // Total burst time for the order

    order->customerId = *orderIndex + 1;  // Customer ID starts from 1
    order->itemCount = 0;
    order->totalBill = 0;

    do {
        displayMenu();
        printf("\nSelect an option (0 to finish): ");
        scanf("%d", &foodChoice);

        if (foodChoice == 0) {
            break;
        }

        printf("Enter quantity: ");
        scanf("%d", &quantity);

        // Add items to the order and calculate the total burst time
        switch (foodChoice) {
            case 1: 
                order->items[order->itemCount] = "Chicken Biryani"; 
                order->quantities[order->itemCount] = quantity; 
                order->totalBill += 300 * quantity; 
                totalBurstTime += 3 * quantity; 
                break;
            case 2: 
                order->items[order->itemCount] = "Nihari"; 
                order->quantities[order->itemCount] = quantity; 
                order->totalBill += 400 * quantity; 
                totalBurstTime += 3 * quantity; 
                break;
            case 3: 
                order->items[order->itemCount] = "Seekh Kebabs"; 
                order->quantities[order->itemCount] = quantity; 
                order->totalBill += 250 * quantity; 
                totalBurstTime += 2 * quantity; 
                break;
            case 4: 
                order->items[order->itemCount] = "Karahi"; 
                order->quantities[order->itemCount] = quantity; 
                order->totalBill += 600 * quantity; 
                totalBurstTime += 4 * quantity; 
                break;
            case 5: 
                order->items[order->itemCount] = "Peshawari Chapli Kebabs"; 
                order->quantities[order->itemCount] = quantity; 
                order->totalBill += 500 * quantity; 
                totalBurstTime += 3 * quantity; 
                break;
            case 6: 
                order->items[order->itemCount] = "Paratha Roll"; 
                order->quantities[order->itemCount] = quantity; 
                order->totalBill += 150 * quantity; 
                totalBurstTime += 2 * quantity; 
                break;
            case 7: 
                order->items[order->itemCount] = "Naan"; 
                order->quantities[order->itemCount] = quantity; 
                order->totalBill += 50 * quantity; 
                totalBurstTime += 1 * quantity; 
                break;
            case 8: 
                order->items[order->itemCount] = "Sada Roti"; 
                order->quantities[order->itemCount] = quantity; 
                order->totalBill += 20 * quantity; 
                totalBurstTime += 1 * quantity; 
                break;
            case 9: 
                order->items[order->itemCount] = "Lassi"; 
                order->quantities[order->itemCount] = quantity; 
                order->totalBill += 100 * quantity; 
                totalBurstTime += 2 * quantity; 
                break;
            default: 
                printf("Invalid choice! Please select a valid item.\n"); 
                continue;
        }

        order->itemCount++;
    } while (1);

    order->burstTime = totalBurstTime;  // Set the burst time for this order
}

void displayOrderSummary(Order *order) {
    printf("\n-------- Order Summary for Customer %d --------\n", order->customerId);
    printf("| %-30s | %-10s | %-10s | %-10s |\n", "Item", "Quantity", "Price (Rs.)", "Burst Time");
    printf("+--------------------------------+------------+------------+------------+\n");
    
    // Print item-wise details with burst time
    for (int i = 0; i < order->itemCount; i++) {
        int pricePerItem = 0;
        int itemBurstTime = 0;
        
        // Assign price per item and burst time based on item
        if (strcmp(order->items[i], "Chicken Biryani") == 0) {
            pricePerItem = 300;
            itemBurstTime = 3;
        } else if (strcmp(order->items[i], "Nihari") == 0) {
            pricePerItem = 400;
            itemBurstTime = 3;
        } else if (strcmp(order->items[i], "Seekh Kebabs") == 0) {
            pricePerItem = 250;
            itemBurstTime = 2;
        } else if (strcmp(order->items[i], "Karahi") == 0) {
            pricePerItem = 600;
            itemBurstTime = 4;
        } else if (strcmp(order->items[i], "Peshawari Chapli Kebabs") == 0) {
            pricePerItem = 500;
            itemBurstTime = 3;
        } else if (strcmp(order->items[i], "Paratha Roll") == 0) {
            pricePerItem = 150;
            itemBurstTime = 2;
        } else if (strcmp(order->items[i], "Naan") == 0) {
            pricePerItem = 50;
            itemBurstTime = 1;
        } else if (strcmp(order->items[i], "Sada Roti") == 0) {
            pricePerItem = 20;
            itemBurstTime = 1;
        } else if (strcmp(order->items[i], "Lassi") == 0) {
            pricePerItem = 100;
            itemBurstTime = 2;
        }

        int totalPricePerItem = pricePerItem * order->quantities[i];
        int totalBurstTimePerItem = itemBurstTime * order->quantities[i];

        // Print the item details
        printf("| %-30s | %-10d | %-10d | %-10d |\n", 
               order->items[i], order->quantities[i], totalPricePerItem, totalBurstTimePerItem);
    }
    
    printf("+--------------------------------+------------+------------+------------+\n");
    printf("| %-30s | %-10s | %-10d | %-10d |\n", "Total Bill", "", order->totalBill, order->burstTime);
    printf("+--------------------------------+------------+------------+------------+\n");
    printf("Total Burst Time: %d\n", order->burstTime);
    printf("Thank you for your order!\n");
}





void processOrders(Order orders[], int orderCount) {
    // Sort orders by burst time (Shortest Job First scheduling)
    for (int i = 0; i < orderCount - 1; i++) {
        for (int j = i + 1; j < orderCount; j++) {
            if (orders[i].burstTime > orders[j].burstTime) {
                // Swap orders based on burst time
                Order temp = orders[i];
                orders[i] = orders[j];
                orders[j] = temp;
            }
        }
    }

    // Print the processing order based on SJF
    printf("\nProcessing orders based on Shortest Job First (SJF):\n");
    printf("+----------------------------------------------------------+\n");
    printf("| %-15s | %-15s | %-15s |\n", "Customer ID", "Burst Time", "Total Bill");
    printf("+----------------------------------------------------------+\n");
    
    for (int i = 0; i < orderCount; i++) {
        printf("| %-15d | %-15d | %-15d |\n",
               orders[i].customerId, orders[i].burstTime, orders[i].totalBill);
    }
    printf("+----------------------------------------------------------+\n");

    
}
