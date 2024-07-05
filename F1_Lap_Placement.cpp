#include <iostream>
#include <string>
using namespace std;

struct Node {
    string driver;
    int position;
    struct Node* next;
};

void insertAtBeginning(struct Node** head_ref, string new_driver) {
    struct Node* new_node = new Node();
    
    if (!new_node) {
        cout << "Memory allocation failed. Operation aborted." << endl;
        return;
    }
    
    new_node->driver = new_driver;
    new_node->position = 1;
    new_node->next = (*head_ref);

    Node* temp = *head_ref;
    while (temp != NULL) {
        temp->position++;
        temp = temp->next;
    }

    (*head_ref) = new_node;
}

void insertAtEnd(struct Node** head_ref, string new_driver) {
    struct Node* new_node = new Node();
    
    if (!new_node) {
        cout << "Memory allocation failed. Operation aborted." << endl;
        return;
    }
    
    new_node->driver = new_driver;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        new_node->position = 1;
        *head_ref = new_node;
        return;
    }

    Node* last = *head_ref;
    while (last->next != NULL) {
        last = last->next;
    }

    new_node->position = last->position + 1;
    last->next = new_node;
}

void insertAfter(struct Node* prev_node, int new_position, string new_driver) {
    if (prev_node == NULL) {
        cout << "The given previous node cannot be NULL." << endl;
        return;
    }

    struct Node* new_node = new Node();
    
    if (!new_node) {
        cout << "Memory allocation failed. Operation aborted." << endl;
        return;
    }
    
    new_node->driver = new_driver;
    new_node->position = new_position;
    new_node->next = prev_node->next;
    prev_node->next = new_node;

    Node* temp = new_node->next;
    while (temp != NULL) {
        temp->position++;
        temp = temp->next;
    }
}

void deleteNode(struct Node** head_ref, int position) {
    if (*head_ref == NULL) {
        cout << "The list is empty. Nothing to delete." << endl;
        return;
    }

    Node* temp = *head_ref;
    if (temp != NULL && temp->position == position) {
        *head_ref = temp->next;
        delete temp;

        temp = *head_ref;
        while (temp != NULL) {
            temp->position--;
            temp = temp->next;
        }
        return;
    }

    Node* prev = NULL;
    while (temp != NULL && temp->position != position) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Position not found. Deletion failed." << endl;
        return;
    }

    prev->next = temp->next;
    delete temp;

    temp = prev->next;
    while (temp != NULL) {
        temp->position--;
        temp = temp->next;
    }
}

void printPlacements(struct Node* node) {
    int position = 1;
    if (node == NULL) {
        cout << "The list is empty." << endl;
        return;
    }
    
    while (node != NULL) {
        cout << "[" << position << "] : " << node->driver << endl;
        node = node->next;
        position++;
    }
}

int main() {
    struct Node* head = NULL;
    int choice;
    string driver;
    int driverposition;

    do {
        cout << "Formula 1 Grand Prix Lap Placement Tracker" << endl;
        cout << "Menu:" << endl;
        cout << "1. Insert driver at the beginning" << endl;
        cout << "2. Insert driver at the end" << endl;
        cout << "3. Insert driver after a position" << endl;
        cout << "4. Delete a driver at a position" << endl;
        cout << "5. Print the placements" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        
        while(!(cin >> choice)){
            cout << "Invalid input. please enter an integer: ";
            cin.clear();
            cin.ignore(1000000, '\n');
        };

        Node* temp = head;


        switch (choice) {
            case 1:
                cout << "Driver Name: ";
                cin.ignore();
                getline(cin, driver);
                insertAtBeginning(&head, driver);
                break;
            case 2:
                cout << "Driver Name: ";
                cin.ignore();
                getline(cin, driver);
                insertAtEnd(&head, driver);
                break;
            case 3:
                cout << "Enter the position: ";
                cin >> driverposition;
                cout << "Driver name in [" << driverposition << "] position: ";
                cin.ignore();
                getline(cin, driver);

                while (temp != NULL && temp->position != driverposition) {
                    temp = temp->next;
                }

                if (temp != NULL) {
                    insertAfter(temp, driverposition + 1, driver);
                } else {
                    cout << "Position not found." << endl;
                }
                break;
            case 4:
                cout << "Enter the position to delete: ";
                cin >> driverposition;

                deleteNode(&head, driverposition);
                break;
            case 5:
                cout << "Current Lap Placements:" << endl;
                printPlacements(head);
                break;
            case 6:
                cout << "Exiting.. " << endl;
                break;
            default:
                cout << "Invalid choice, please enter a number between 1 and 6." << endl;
                break;
        }
        cout << endl;
    } while (choice != 6);

    return 0;
}
