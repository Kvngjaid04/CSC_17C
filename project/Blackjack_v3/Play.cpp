/*  Author: Ireoluwa 
 * Created on October 29, 2024, 12:19 PM 
 * modified for csc_17_c 
 * Date:    May 2, 2024 
 * Purpose: blackjack 
 */

#include "Play.h"
#include "Deck.h"
#include "UserMgr.h"
#include <iostream>
#include <algorithm>
using namespace std;

// Recursive double down with depth
bool dblDown(Save& user, int& bet, int depth) {
    if (user.cash < bet) {
        return false;
    }
    
    if (depth == 0) {
        return dblDown(user, bet, depth + 1);
    }
    
    user.cash -= bet;
    bet *= 2;
    cout << "Bet doubled to $" << bet << "!\n";
    cout << "Remaining cash: $" << user.cash << "\n";
    return true;
}

// Calculate sum of hand using Card objects
int sumHand(const list<Card>& hand) { 
    int total = 0; 
    int aces = 0;
    
    for_each(hand.begin(), hand.end(), [&](const Card& card) {
        int val = card.val > 10 ? 10 : card.val;
        if (card.val == 1) {
            aces++;
            total += 11;
        } else {
            total += val;
        }
    });
    
    while (total > 21 && aces > 0) {
        total -= 10;
        aces--;
    }
    
    return total;
}

// Deal initial cards using Card objects
void deal(vector<Card>& deck, list<Card>& pHand, list<Card>& dHand) { 
    cout << "\nYour cards:\n"; 
    
    for (int i = 0; i < 2; i++) {
        if (!deck.empty()) {
            Card drawn = deck.back();
            deck.pop_back();
            pHand.push_back(drawn);
            pCard(drawn.val, drawn.suit);
        }
    }
    
    for (int i = 0; i < 2; i++) {
        if (!deck.empty()) {
            Card drawn = deck.back();
            deck.pop_back();
            dHand.push_back(drawn);
            if (i == 0) {
                cout << "\nDealer's up card:\n";
                pCard(drawn.val, drawn.suit);
            }
        }
    }
}

// Show initial deal
void show(const list<Card>& pHand, const list<Card>& dHand, 
          const vector<Card>& deck) {
    auto it = dHand.begin();
    if (it != dHand.end()) {
        int val = it->val > 10 ? 10 : it->val;
        cout << "Dealer's visible total: " << val << endl;
    }
}

// Show strategy hint with simple win probability
void hint(AVL& tree, list<Card>& hand, int pSum, int dCard) {
    cout << "\n  BLACKJACK ADVISOR  \n";
    
    char hnt = tree.getHint(pSum, dCard);
    cout << "Strategy: ";
    switch(hnt) {
        case 'h': cout << "Hit"; break;
        case 's': cout << "Stand"; break;
        case 'd': cout << "Double"; break;
        default: cout << "Stand"; break;
    }
    cout << "\n";
    
    // Simple win probability based on basic blackjack math
    int prob = 50; // Default
    
    if (pSum > 21) prob = 0;        // Busted
    else if (pSum == 21) prob = 90; // Blackjack
    else if (dCard <= 6) {          // Dealer weak
        if (pSum >= 17) prob = 75;
        else if (pSum >= 13) prob = 65;
        else prob = 60;
    } else {                        // Dealer strong
        if (pSum >= 17) prob = 55;
        else if (pSum >= 13) prob = 35;
        else prob = 45;
    }
    
    cout << "Win chance: " << prob << "%\n";
}

// Player's turn with recursion using Card objects
void pTurn(vector<Card>& deck, list<Card>& hand, int& pSum, 
           Save& user, int& bet, AVL& tree) { 
    pSum = sumHand(hand);
    cout << "\nYour total: " << pSum << endl; 
    if (pSum >= 21) {  return; }
    string input;
    char choice;
    do {
        cout << "\nHit, Stand, Double, or Hint? (h/s/d/hint): ";
        cin >> input;
        transform(input.begin(), input.end(), input.begin(),   ::tolower);
        if (input == "hint") {
            int dCard = 10; // Default
            if (!deck.empty()) {
                dCard = deck.back().val > 10 ? 10 : deck.back().val; }
            hint(tree, hand, pSum, dCard);
            continue;
        } else if (input == "h" || input == "hit") { choice = 'h';
        } else if (input == "s" || input == "stand") {  choice = 's';
        } else if (input == "d" || input == "double") { choice = 'd';
        } else {  choice = 'x'; }      
        if (choice != 'h' && choice != 's' && choice != 'd')
            cout << "Please enter 'h'/'hit', 's'/'stand', "
                    "'d'/'double', or 'hint'\n";
    } while (choice != 'h' && choice != 's' && choice != 'd');  clrBuf();
    if (choice == 's') {  return; }
    else if (choice == 'd') {
        if (dblDown(user, bet)) {
            if (!deck.empty()) { Card drawn = deck.back();
                deck.pop_back(); hand.push_back(drawn);
                cout << "\nYou drew:\n";  pCard(drawn.val, drawn.suit); 
                pSum = sumHand(hand); 
                cout << "\nYour final total: " << pSum << endl;
            }
            return;
        } else {
            cout << "Not enough funds to double down!\n";
            pTurn(deck, hand, pSum, user, bet, tree);
        } 
    }
    else if (choice == 'h') {
        if (!deck.empty()) {  Card drawn = deck.back();
            deck.pop_back(); hand.push_back(drawn);
            cout << "\nYou drew:\n"; pCard(drawn.val, drawn.suit); 
        }
        pTurn(deck, hand, pSum, user, bet, tree);
    }
}

// Dealer's turn using Card objects
void dTurn(vector<Card>& deck, list<Card>& hand, int& dSum) { 
    dSum = sumHand(hand);
    
    cout << "\nDealer shows hidden card:\n"; 
    
    for (auto it = hand.begin(); it != hand.end(); ++it) {
        pCard(it->val, it->suit);
    }
    
    cout << "Dealer total: " << dSum << endl; 
    
    while (dSum < 17) { 
        if (!deck.empty()) {
            Card drawn = deck.back();
            deck.pop_back();
            hand.push_back(drawn);
            
            cout << "\nDealer drew:\n"; 
            pCard(drawn.val, drawn.suit); 
            
            dSum = sumHand(hand);
            cout << "Dealer total: " << dSum << endl; 
        } else {
            break;
        }
    } 
    
    cout << "\nFinal dealer total: " << dSum << endl; 
}

// Handle game outcome
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

// Check if player can continue
bool canPlay(const Save& user) { 
    if (user.cash <= 0) { 
        cout << "\nYou're broke! Game over!\n"; 
        return false; 
    } 
    return true; 
}