/**
 * Description: Program that reads in three contact names and contact phone numbers, putting the information
 * into a linked list. Then outputting the linked list as a Contact List
 * Authors: Vincent Nguyen
 * Author emails: vincent.n.nguyen@sjsu.edu
 * Last modified date: 04-16-2023
 * Creation date: 04-16-2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define ContactNode struct
typedef struct ContactNode {
    char contactName[50];
    char contactPhoneNumber[50];
    struct ContactNode* nextNodePtr;
} ContactNode;

// Initialize a contact node with the given name, phone number, and next node pointer
void InitializeContactNode(ContactNode* thisNode, char name[], char phone[], ContactNode* nextNode) {

    // copy the lines of thisNode to the contactName and contactPhoneNumber
    strcpy(thisNode->contactName, name);
    strcpy(thisNode->contactPhoneNumber, phone);

    // set the nextNodePtr of thisNode to the nextNode
    thisNode->nextNodePtr = nextNode;
}

// Get the name of a node
char* GetName(ContactNode* thisNode) {
    return thisNode->contactName;
}

// Get the phone number of a node
char* GetPhoneNumber(ContactNode* thisNode) {
    return thisNode->contactPhoneNumber;
}

// Insert a new node after an existing node
void InsertAfter(ContactNode* thisNode, ContactNode* newNode) {

    // set the nextNodePtr of thisNode to the newNode
    newNode->nextNodePtr = thisNode->nextNodePtr;

    // set the nextNodePtr of the thisNode which is before the newNode to the newNode
    thisNode->nextNodePtr = newNode;
}

// Get the next node after the current one
ContactNode* GetNext(ContactNode* thisNode) {
    return thisNode->nextNodePtr;
}

// Print the contact name and phone number of a given node
void PrintContactNode(ContactNode* thisNode) {
    printf("Name: %s\n", GetName(thisNode));
    printf("Phone number: %s\n", GetPhoneNumber(thisNode));
}


int main(void) {
    // Initialize head node with empty fields and a null nextNodePtr
    ContactNode* headNode = (ContactNode*) malloc(sizeof(ContactNode));
    strcpy(headNode->contactName, "");
    strcpy(headNode->contactPhoneNumber, "");
    headNode->nextNodePtr = NULL;

    // Read in three contacts and create nodes
    char name[50], phone[50];
    ContactNode* currNode = headNode;
    for (int i = 1; i <= 3; i++) {

        // Prompt the client for a contact name, read in from stdin, remove newline
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = '\0';

        // Prompt the client for a contact phone number, read in from stdin, remove newline
        fgets(phone, 50, stdin);
        phone[strcspn(phone, "\n")] = '\0';

        // Allocate memory for the new node
        ContactNode* newNode = (ContactNode*) malloc(sizeof(ContactNode));

        // Initialize the new contact node
        InitializeContactNode(newNode, name, phone, NULL);

        // Insert after the last node which is the current node
        InsertAfter(currNode, newNode);

        // Set currNode to the newNode which is the next node of the current node
        currNode = GetNext(currNode);
    }

    // Print each node
    // Set current node to the headNodes nextNodePtr
    currNode = headNode->nextNodePtr;
    int count = 1;

    // While current node isn't null print the person #, name, and phone number
    while (currNode != NULL) {
        printf("Person %d: %s, %s\n", count, GetName(currNode), GetPhoneNumber(currNode));

        // Set current node to the next node and increment the count
        currNode = GetNext(currNode);
        count++;
    }

    // Print each contact
    printf("\nCONTACT LIST\n");

    // Set current node to the headNodes nextNodePtr
    currNode = headNode->nextNodePtr;

    // while linked list isn't empty
    while (currNode != NULL) {
        // User PrintContactNode to print the current node information
        PrintContactNode(currNode);
        printf("\n");

        // Move to next node
        currNode = GetNext(currNode);
    }

    // Free memory used by nodes
    currNode = headNode;
    while (currNode != NULL) {
        ContactNode* temp = currNode;
        currNode = GetNext(currNode);
        free(temp);
    }

    return 0;
}

