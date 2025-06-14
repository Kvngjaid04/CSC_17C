/* 
 * File:   Gameplay.cpp
 * Author: Ireoluwa
 * Created on June 13, 2025, 9:01 PM
 */

#include "Gameplay.h"
#include "Deck.h"
#include "UserMgr.h"
#include "Graph.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Recursive double down function with depth parameter
bool dblDown(Save& user, int& bet, int depth = 0) {
    // check if user has enough funds
    if (user.cash < bet) {
        return false;
    }
    
    // only do the operation at depth 0
    if (depth == 0) {
        return dblDown(user, bet, depth + 1);
    }
    
    // Actual operation at depth 1
    user.cash -= bet;   // Take out additional bet from cash
    bet *= 2;           // Double the bet
    cout << "Bet doubled to $" << bet << "!\n";
    cout << "Remaining cash: $" << user.cash << "\n";
    return true;
}

// Function to calculate the sum of a hand
int sumHand(const list<int>& hand) { 
    int total = 0; 
    int aces = 0;
    
    // Using STL for_each algorithm with lambda
    for_each(hand.begin(), hand.end(), [&](int card) {
        if (card == 1) {
            aces++;
            total += 11;
        } else {
            total += card;
        }
    });
    
    // Adjust for aces if needed
    while (total > 21 && aces > 0) {
        total -= 10;
        aces--;
    }
    
    return total;
}

// Function to deal initial cards
void deal(vector<Card>& deck, list<int>& pHand, list<int>& dHand) { 
    cout << "\nYour cards:\n"; 
    
    // Deal two cards to player
    for (int i = 0; i < 2; i++) {
        int card = draw(deck);
        pHand.push_back(card);
        pCard(card, deck.back().suit);
    }
    
    // Deal two cards to dealer
    for (int i = 0; i < 2; i++) {
        int card = draw(deck);
        dHand.push_back(card);
        if (i == 0) {
            cout << "\nDealer's up card:\n";
            pCard(card, deck.back().suit);
        }
    }
}

// Function to display the initial deal
void show(const list<int>& pHand, const list<int>& dHand, 
        const vector<Card>& deck) {
    // Use find algorithm to get the first card
    auto it = dHand.begin();
    if (it != dHand.end()) {
        cout << "Dealer's visible total: " << *it << endl;
    }
}

// Show strategy hint and win probability
void showHint(AVLTree& tree, Graph& graph, list<int>& hand, int pSum, int dCard)
    {    cout << "\n  BLACKJACK ADVISOR  \n";
    
    // Get strategy from AVL tree
    char hint = tree.getHint(pSum, dCard);
    cout << "Strategy: ";
    switch(hint) {
        case 'h': cout << "Hit"; break;
        case 's': cout << "Stand"; break;
        case 'd': cout << "Double"; break;
        default: cout << "Stand"; break;
    }
    cout << "\n";
    
    // Get win probability from Dijkstra
    int prob = winProb(graph, hand, dCard);
    cout << "Win chance: " << prob << "%\n";
}

// Recursive function to play the player's turn with hint option
void pTurn(vector<Card>& deck, list<int>& hand, int& pSum, Save& user, 
            int& bet, AVLTree& tree, Graph& graph) { 
    pSum = sumHand(hand);
    cout << "\nYour total: " << pSum << endl; 
    // if 21 or over, end turn
    if (pSum >= 21) {
        return;
    }
    string input;
    char choice;
    do {
        cout << "\nHit, Stand, Double, or Hint? (h/s/d/hint): ";
        cin >> input;
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        if (input == "hint") {
            // Get dealer's up card
            int dCard = deck.empty() ? 10 : (deck.back().val > 10 ? 10 : 
                    deck.back().val);
            showHint(tree, graph, hand, pSum, dCard);continue;
        } else if (input.length() == 1) {choice = input[0];
        } else {choice = 'x';  }
        if (choice != 'h' && choice != 's' && choice != 'd')
            cout << "Please enter 'h', 's', 'd', or 'hint'\n";
    } while (choice != 'h' && choice != 's' && choice != 'd');
    clrBuf();
    //  player chooses to stand
    if (choice == 's') { return;    }
    // Handle double down
    else if (choice == 'd') {
        if (dblDown(user, bet)) {
            // Take exactly one card and end turn
            int card = draw(deck);
            hand.push_back(card);cout << "\nYou drew:\n"; 
            pCard(card, deck.back().suit); 
            pSum = sumHand(hand); cout << "\nYour final total: "<< pSum << endl;
            return; // End turn after doubling
        } else {
            cout << "Not enough funds to double down!\n";
            // Recursive call to continue turn
            pTurn(deck, hand, pSum, user, bet, tree, graph);
        } }
    // Handle hit
    else if (choice == 'h') {
        int card = draw(deck);
        hand.push_back(card);
        cout << "\nYou drew:\n"; 
        pCard(card, deck.back().suit); 
        // Recursive call to continue turn
        pTurn(deck, hand, pSum, user, bet, tree, graph);
    }
}

// Function to play the dealer's turn
void dTurn(vector<Card>& deck, list<int>& hand, int& dSum) { 
    dSum = sumHand(hand);
    
    cout << "\nDealer shows hidden card:\n"; 
    
    // Using STL iterator to traverse the list
    for (auto it = hand.begin(); it != hand.end(); ++it) {
        pCard(*it, deck.back().suit);
    }
    
    cout << "Dealer total: " << dSum << endl; 
    
    while (dSum < 17) { 
        int card = draw(deck);
        hand.push_back(card);
        
        cout << "\nDealer drew:\n"; 
        pCard(card, deck.back().suit); 
        
        dSum = sumHand(hand);
        cout << "Dealer total: " << dSum << endl; 
    } 
    
    cout << "\nFinal dealer total: " << dSum << endl; 
}

// Function to handle the game outcome
void result(Save& user, int bet, int pSum, int dSum) { 
    cout << "\nFinal totals:\n"; 
    cout << "Your total: " << pSum << endl; 
    
    if (pSum <= 21) cout << "Dealer total: " << dSum << endl; 
    
    user.games++; 
    
    if (pSum > 21) { 
        cout << "\nBust! You lose $" << bet << endl; 
        user.cash -= bet; 
    } 
    else if (dSum > 21) { 
        cout << "\nDealer bust! You win $" << bet << endl; 
        user.cash += bet; 
        user.wins++; 
    } 
    else if (pSum > dSum) { 
        cout << "\nYou win $" << bet << endl; 
        user.cash += bet; 
        user.wins++; 
    } 
    else if (pSum < dSum) { 
        cout << "\nYou lose $" << bet << endl; 
        user.cash -= bet; 
    } 
    else cout << "\nPush!\n"; 
    
    cout << "Current cash: $" << user.cash << endl; 
}

// Function to check if the player can continue
bool canPlay(const Save& user) { 
    if (user.cash <= 0) { 
        cout << "\nYou're broke! Game over!\n"; 
        return false; 
    } 
    return true; 
}