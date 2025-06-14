/*  Author: Ireoluwa 
 * Created on October 29, 2024, 12:19 PM 
 * modified for csc_17_c 
 * Date:    May 2, 2024 
 * Purpose: blackjack 
 */

#ifndef USERMGR_H
#define USERMGR_H

#include <string>
#include "Save.h"
#include "Hash.h"

// User management function prototypes
bool load(Save&, std::string);
void save(Save, std::string);
bool valName(std::string);
void clrBuf();
int getBet(const Save&);
int calcRte(int, int);
void lodExst();
bool valData(const Save&);
Save selPlyr();
void updPlyr(const Save& user);

// Helper functions for player selection
Save lodExst(std::vector<PlyrEnt>& players);
Save creatNw();
void shwLead(std::vector<PlyrEnt>& players);
Save restBal(std::vector<PlyrEnt>& players);
bool chckBal(Save& user);

#endif