/*  Author: Ireoluwa 
 * Created on October 29, 2024, 12:19 PM 
 * modified for csc_17_c 
 * Date:    May 2, 2024 
 * Purpose: blackjack 
 */ 


#ifndef SAVE_H
#define SAVE_H

#include <cstring>

// Player save data structure
struct Save { 
    char name[30]; 
    int wins; 
    int games; 
    int cash; 
    
    bool operator<(const Save& other) const {
    return strcmp(name, other.name) < 0;
}
};

#endif