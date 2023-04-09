#ifndef WS10_ITEMTOPURCHASE_H
#define WS10_ITEMTOPURCHASE_H

// build the struct according to specifications
typedef struct ItemToPurchase_struct {
    char itemName[50];
    int itemPrice;
    int itemQuantity;
} ItemToPurchase;

// create related functions
// MakeItemBlank has a pointer to an ItemtoPurchase parameter
void MakeItemBlank(ItemToPurchase *item);

// PrintItemCost has an ItemToPurchase parameter
void PrintItemCost(ItemToPurchase item);


#endif //WS10_ITEMTOPURCHASE_H
