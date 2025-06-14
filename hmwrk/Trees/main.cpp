/* 
 * File:   main.cpp
 * Author: Ireoluwa Dairo
 * Created on May 27, 2025, 1:04 PM
 */

#include <cstdlib>
#include <iostream>
using namespace std;

//User Libraries
#include "AVLTree.h"

//Global Constants - Mathematical, Scientific, Conversions
//Higher Dimensions go here. No Variables

//Function Prototypes
void menu();

//Execution Begins here
int main(int argc, char** argv) {
    //Declaring Variables
    int choice, item;
    AVLTree avl;
    //Processing/Mapping Inputs to Outputs
    do {
        menu();
        cin >> choice;
         switch(choice) {
            case 1:
                cout << "Enter value: ";
                cin >> item;
                avl.root = avl.insert(avl.root, item);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> item;
                avl.root = avl.remove(avl.root, item);
                break;
            case 3:
                cout << "Tree Structure:" << endl;
                avl.disp(avl.root, 1);
                break;
            case 4:
                cout << "Inorder: ";
                avl.inord(avl.root);
                cout << endl; break;
            case 5:
                cout << "Preorder: ";
                avl.preord(avl.root);
                cout << endl; break;
            case 6:
                cout << "Postorder: ";
                avl.postrd(avl.root);
                cout << endl; break;
            case 7:
                cout << "Level order: ";
                avl.level(avl.root);
                cout << endl; break;
            case 8:
                cout << "Exit Program" << endl;
                break;
            default:
                cout << "Invalid choice! Enter 1-8." << endl;
        }
    } while(choice != 8);
    //Exiting stage left/right
    return 0;
}

//******************************************************************************
//                            Display Menu Options
//******************************************************************************
void menu() {
    cout << "\n---------------------" << endl;
    cout << "AVL Tree Menu" << endl;
    cout << "---------------------" << endl;
    cout << "1. Insert Element" << endl;
    cout << "2. Delete Element" << endl;
    cout << "3. Display Tree" << endl;
    cout << "4. Inorder Traversal" << endl;
    cout << "5. Preorder Traversal" << endl;
    cout << "6. Postorder Traversal" << endl;
    cout << "7. Level Order Traversal" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter Choice: ";
}