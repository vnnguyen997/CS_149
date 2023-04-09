#include<stdio.h>
#include<string.h>

#include "ItemToPurchase.h"

int main(void) {

    // variables
    ItemToPurchase item1, item2;
    char c;

    // Prompt user for item 1
    printf("Item 1\n");

    // scan in the item name and set it to item1
    printf("Enter the item name:\n");
    scanf("%[^\n]", item1.itemName);

    // scan in the item price and set to item1
    printf("Enter the item price:\n");
    scanf("%d", &item1.itemPrice);

    // scan in item quantity and set to item1
    printf("Enter the item quantity:\n");
    scanf("%d", &item1.itemQuantity);

    // Before prompting for the second item, enter the following code to allow the user to input a new string
    c = getchar();
    while(c != '\n' && c != EOF) {
        c = getchar();
    }

    // Prompt user for item 2
    printf("\nItem 2\n");

    // scan in the item name and set it to item2
    printf("Enter the item name:\n");
    scanf("%[^\n]", item2.itemName);

    // scan in the item price and set to item2
    printf("Enter the item price:\n");
    scanf("%d", &item2.itemPrice);

    // scan in item quantity and set to item2
    printf("Enter the item quantity:\n");
    scanf("%d", &item2.itemQuantity);

    // Print total cost of item 1 and item 2
    printf("\nTOTAL COST\n");
    PrintItemCost(item1);
    PrintItemCost(item2);

    // Print total
    printf("\nTotal: $%d\n", (item1.itemPrice * item1.itemQuantity) + (item2.itemPrice * item2.itemQuantity));

    return 0;
}