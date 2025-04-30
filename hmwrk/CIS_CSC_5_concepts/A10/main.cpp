/* 
 * Note:  This time you create the strcmp() function that takes into
 * account the new sort order.
 */

// System Libraries Here
#include <iostream> // cin, cout
#include <cstring>  // strlen(), strcpy()
using namespace std;

// Global Constants Only, No Global Variables
const int COLMAX = 80; // Maximum columns allowed (including null terminator)

// Function Prototypes Here
int read(char [][COLMAX], int &); // Outputs row and columns detected from input
void sort(char [][COLMAX], int, int, const char[], const char[]); // Sort by row using custom strcmp()
void print(const char [][COLMAX], int, int); // Print the sorted 2-D array
int cstrcmp(const char [], const char [], const char [], const char []); // Custom strcmp with replacement sort order

// Program Execution Begins Here
int main(int argc, char** argv) {
    // Declare all Variables Here
    const int ROW = 30; // Only 20 required
    char array[ROW][COLMAX]; // Bigger than necessary 
    int colIn, colDet, rowIn, rowDet; // Row, Col input and detected
    char replace[COLMAX], with[COLMAX]; // New sort order
    
    // Input the new sort order then sort
    cout << "Modify the sort order by swapping these characters." << endl;
    cin >> replace;
    cout << "With the following characters" << endl;
    cin >> with;
    cout << "Read in a 2 dimensional array of characters and sort by Row" << endl;
    cout << "Input the number of rows <= 20" << endl;
    cin >> rowIn;
    cout << "Input the maximum number of columns <=20" << endl;
    cin >> colIn;
    
    // Now read in the array of characters and determine its size
    rowDet = rowIn;
    cout << "Now input the array." << endl;
    colDet = read(array, rowDet);
    
    // Compare the size input vs. size detected and sort if same
    if (rowDet == rowIn && colDet == colIn) {
        sort(array, rowIn, colIn, replace, with);
        cout << "The Sorted Array" << endl;
        print(array, rowIn, colIn);
    } else {
        if (rowDet != rowIn)
            cout << (rowDet < rowIn ? "Row Input size less than specified." : "Row Input size greater than specified.") << endl;
        if (colDet != colIn)
            cout << (colDet < colIn ? "Column Input size less than specified." : "Column Input size greater than specified.") << endl;
    }
    
    // Exit
    return 0;
}

// Read the 2D array and determine the number of columns used
int read(char a[][COLMAX], int & rows) {
    int maxCol = 0;
    int RRows = 0; // Number of rows actually read
    cin.ignore(); // Ignore newline from previous input

    char line[COLMAX];
    while (cin.getline(line, COLMAX) && RRows < 30) { // 30 is the max rows allowed
        if (RRows < rows) {
            strcpy(a[RRows], line);
            int crntCol = strlen(line);
            if (crntCol > maxCol) {
                maxCol = crntCol;
            }
        }
        RRows++;
    }

    rows = RRows; // Update rows
    return maxCol;
}

// bubble Sort the 2D array by rows using the custom strcmp function
void sort(char a[][COLMAX], int row, int col, const char replace[], const char with[]) {
    for (int i = 0; i < row - 1; ++i) {
        for (int j = 0; j < row - i - 1; ++j) {
            if (cstrcmp(a[j], a[j + 1], replace, with) > 0) {
                // Swap rows
                char temp[COLMAX];
                strcpy(temp, a[j]);
                strcpy(a[j], a[j + 1]);
                strcpy(a[j + 1], temp);
            }
        }
    }
}

// Custom strcmp function with character replacement based on new order
int cstrcmp(const char a[], const char b[], const char replace[], const char with[]) {
  const int cascii = 256;
    char l[cascii];

// Initialize the custom array
for (int i = 0; i < cascii; ++i) {
    l[i] = i;
}

// Find the minimum length between 'replace' and 'with'
int minLnth = strlen(replace) < strlen(with) ? strlen(replace) : strlen(with);

// Swap characters in the custom array
for (int i = 0; i < minLnth; ++i) {
    for (int j = 0; j < cascii; ++j) {
        if (l[j] == replace[i]) {
            l[j] = with[i];
        } else if (l[j] == with[i]) {
            l[j] = replace[i];
        }
    }
}

// Compare characters using the modified array
int i = 0;
while (a[i] != '\0' || b[i] != '\0') {
    char charA, charB;
    for (int j = 0; j < cascii; ++j) {
        if (l[j] == a[i]) {
            charA = j;
        }
        if (l[j] == b[i]) {
            charB = j;
        }
    }

    if (charA != charB) {
        return charA - charB;
    }
    ++i;
}
return a[i] - b[i];
}

// Print the 2D array row by row
void print(const char a[][COLMAX], int row, int col) {
    for (int i = 0; i < row; ++i) {
        cout << a[i] << endl; // Print each row as a string
    }
}
