/* 
 * File:   main.cpp
 * Author: Ireoluwa
 * Created on June 9, 2025, 1:10 AM
 */

#include <cstdlib>
#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

// clerk struct
struct Clrk {
    int rem; // time remaining to finish current customer
    int svc; // base service time (seconds)
};

//Function Prototypes
int adjVal(int);
pair<float, int> simDay(int, bool);

//Execution Begins here
int main(int argc, char** argv) {
    //Setting the random number seed
    srand(static_cast<unsigned int>(time(0)));  // seed random once

    //Declaring Variables
    const int DAYSEC = 8 * 3600; // 8 hours in seconds

    //Initialize Variables

    //Processing/Mapping Inputs to Outputs
    auto steady = simDay(DAYSEC, false); // no randomness
    auto random = simDay(DAYSEC, true);  // with randomness

    //Displaying Input/Output Information
    cout << fixed << setprecision(2);
    cout << "average wait time: " << steady.first << " sec "
            "  max line " << steady.second << "\n";
    cout << "random average wait time " << random.first << " sec   "
            "max line " << random.second << "\n";

    //Exiting stage left/right
    return 0;
}


int adjVal(int base) {
    int range = base / 2;  // ±50% range
    int offset = (rand() % (2 * range + 1)) - range; // -range to +range
    int result = base + offset;
    if (result < 1) result = 1;
    return result;
}

pair<float, int> simDay(int dur, bool rnd) {
    queue<int> line;             // arrival times of customers (in seconds)
    vector<Clrk> clks = { {0,60}, {0,120}, {0,80} }; // 3 clerks
    int nxtIn = 15;              // next customer arrival time (seconds)
    int cust = 0;                // total customers arrived
    int wSum = 0;                // total wait time sum
    int qMax = 0;                // max queue length

    for (int sec = 0; sec < dur; ++sec) {
        // New arrival?
        if (sec == nxtIn) {
            line.push(sec);
            cust++;
            nxtIn += rnd ? adjVal(15) : 15;  // arrival interval
        }

        // Clerks process customers
        for (size_t i = 0; i < clks.size(); ++i) {
            if (clks[i].rem == 0 && !line.empty()) {
                int arrTime = line.front();
                line.pop();
                wSum += sec - arrTime;
                clks[i].rem = rnd ? adjVal(clks[i].svc) : clks[i].svc;
            }
            if (clks[i].rem > 0) clks[i].rem--;
        }

        // Track max queue length
        if ((int)line.size() > qMax) qMax = (int)line.size();

        // Add clerks if line too long
        int need = (int)clks.size() - 3;  // how many extra clerks?
        if ((int)line.size() > 5 * need) {
            clks.push_back({0, 60});  // add a new clerk with 60s base service
        }

        // Remove extra clerks if line empty
        if (line.empty() && clks.size() > 3) {
            // remove clerks that are idle (rem == 0)
            while (clks.size() > 3 && clks.back().rem == 0) {
                clks.pop_back();
            }
        }
    }

    float avgWait = cust ? static_cast<float>(wSum) / cust : 0.0f;
    return {avgWait, qMax};
}
