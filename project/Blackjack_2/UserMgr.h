/* 
 * File:   usermgr.h
 * Author: Ireoluwa
 * Created on June 10, 2025, 12:10 PM
 */

#ifndef USERMGR_H
#define USERMGR_H

#include <string>
#include "Save.h"

// Function Prototypes for user management
bool load(Save&, std::string);              // Load game 
void save(Save, std::string);               // Save game 
bool vName(std::string);                    // Validate name 
void clrBuf();                              // Clear buffer 
int getBet(const Save&);                    // Get bet amount
int clcRate(int, int);                      // Calculate win rate
void lodExst();                             // Load existing .dat files
bool valData(const Save&);                  // Validate user data

#endif