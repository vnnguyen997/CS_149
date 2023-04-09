#include<stdio.h>
#include<string.h>

#include "ItemToPurchase.h"

// Sets item's name to "none", items's price = 0, and Item's quantity = 0;
void MakeItemBlank(ItemToPurchase *item) {
    sprintf((*item).itemName, "none");
    (*item).itemPrice = 0;
    (*item).itemQuantity = 0;
}

// prints the parameters
void PrintItemCost(ItemToPurchase item) {
    printf("%s %d @ $%d = $%d\n", item.itemName, item.itemQuantity, item.itemPrice,
           item.itemPrice * item.itemQuantity);
}