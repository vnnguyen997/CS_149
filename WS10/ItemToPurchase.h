/**
 * Description: This file contains the struct definition, including data members and related
 * function declarations
 * Authors: Vincent Nguyen
 * Author emails: vincent.n.nguyen@sjsu.edu
 * Last modified date: 04-09-2023
 * Creation date: 04-09-2023
 */


#ifndef WS10_ITEMTOPURCHASE_H
#define WS10_ITEMTOPURCHASE_H

// build the struct according to specifications
typedef struct ItemToPurchase_struct {
    char itemName[50];
    int itemPrice;
    int itemQuantity;
} ItemToPurchase;

// Function declarations
// MakeItemBlank has a pointer to an ItemtoPurchase parameter
void MakeItemBlank(ItemToPurchase *item);

// PrintItemCost has an ItemToPurchase parameter
void PrintItemCost(ItemToPurchase item);


#endif //WS10_ITEMTOPURCHASE_H
