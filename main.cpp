/*
 * Check sudoku matrix
 */

#include <iostream>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;

const size_t SIZE = 9;

// returns true if all numbers from 1 to 9 are contained in v, false otherwise
bool basic_search (const unsigned * v[], unsigned n_elements);


// they return 1 if all the rows, columns and subregions (respectively) of the Sudoku matrix comply with the rules, 0 otherwise
// TODO: implement
bool check_rows (const unsigned sudoku[][SIZE]);
bool check_cols (const unsigned sudoku[][SIZE]);
bool check_regions (const unsigned sudoku[][SIZE]);


// Return:
//         1 if sudoku matrix complies to all Sudoku rules
//        -1 if a row violates the game rules
//        -2 if a column violates the game rules
//        -3 if a region violates the game rules
int check_sudoku(const unsigned sudoku[][SIZE]);

// Create a Sudoku matrix by Lewis' Algorithm
// (https://en.wikipedia.org/wiki/Sudoku_solving_algorithms)
void generate_sudoku(unsigned sudoku[][SIZE]);

int main()
{
    // initialize a sudoku matrix
    unsigned sudoku[SIZE][SIZE] = {
            {1,2,3,4,5,6,7,8,9},
            {2,3,4,5,6,7,8,9,1},
            {3,4,5,6,7,8,9,1,2},
            {4,5,6,7,8,9,1,2,3},
            {5,6,7,8,9,1,2,3,4},
            {6,7,8,9,1,2,3,4,5},
            {7,8,9,1,2,3,4,5,6},
            {8,9,1,2,3,4,5,6,7},
            {9,1,2,3,4,5,6,7,8}
    };

    // check
    int res = check_sudoku(sudoku);
    cout << "check_sudoku returns: " <<  res << endl;

    // initialize another sudoku matrix
    unsigned sudoku2[SIZE][SIZE];
    generate_sudoku(sudoku2);

    // check
    res = check_sudoku(sudoku2);
    cout << "check_sudoku returns: " <<  res << endl;


    return 0;
}

// Modified with bool instead int, since the output can be only 0 or 1.
bool search_key (const unsigned v[], unsigned n_elements, unsigned key)
{
    bool key_found = false;

    for (size_t i=0; i<n_elements; ++i)
        if (v[i] == key)
            key_found = true;

    return key_found;
}


bool basic_search (const unsigned * v[], unsigned n_elements){

    // Print for debug purposes
//    cout << "search in array:" << endl;
//    for(size_t i = 0; i < n_elements; ++i){
//        cout << *v[i]<< "\t";
//    }
//    cout << endl;

    for(unsigned n = 1; n <= n_elements; ++n){ // search for the number n in the array v
        bool nIsFound = false;

        for(size_t i = 0 ; i < n_elements && !nIsFound; ++i){
            if (*v[i] == n) nIsFound = true;
        }
        if (!nIsFound) {
            return false; // If the number n has not been found in the array
        }
    }
    return true;
}

bool check_rows (const unsigned sudoku[][SIZE]){
    for(size_t rowIndex = 0; rowIndex < SIZE ; ++rowIndex){
        const unsigned * row[SIZE] = {};
        for(size_t colIndex = 0; colIndex < SIZE; ++colIndex){
            row[colIndex] = &sudoku[rowIndex][colIndex];
        };
        if (!basic_search(row,SIZE)) return false;
    }
    return true;
}

bool check_cols (const unsigned sudoku[][SIZE]){
    for(size_t colIndex = 0; colIndex < SIZE; ++colIndex){      // for every columns
        const unsigned * col[SIZE] = {};                             // Arrey pointers.
        for(size_t rowIndex = 0; rowIndex < SIZE; ++rowIndex){
            col[rowIndex] = &sudoku[rowIndex][colIndex];
        }

        // Print for debug purposes
//        cout << "search in column: " << endl;
//        for(auto pToElem : col){
//            cout << *pToElem << "\t";
//        }
//        cout << endl;

        if (!basic_search(col,SIZE)) return false;
    }
    return true;
}

bool check_regions (const unsigned sudoku[][SIZE]){

    // check if sqrt of SIZE is integer
    size_t nRowColRegions = 0; //Number of rows and colums of regions
    {
        double squareSIZE = std::sqrt((SIZE));
        if (squareSIZE == floor(squareSIZE)) nRowColRegions = squareSIZE;
    }

    for(size_t regRowIndex = 0; regRowIndex < nRowColRegions; ++regRowIndex) {
        for (size_t regColIndex = 0; regColIndex < nRowColRegions; ++regColIndex) {
            size_t i = 0;
            const unsigned *reg[SIZE] = {};

            size_t startRow = nRowColRegions * regRowIndex;
            size_t startCol =nRowColRegions * regColIndex;

            for (size_t rowIndex = startRow; rowIndex < startRow+nRowColRegions; ++rowIndex) {
                for (size_t colIndex = startCol; colIndex <  startCol+nRowColRegions; ++colIndex) {
                    reg[i] = &sudoku[rowIndex][colIndex];
                    ++i;
                };
            };

            if (!basic_search(reg,SIZE)) return false;
        }
    }

    return true;
}


int check_sudoku(const unsigned sudoku[][SIZE])
{
    cout << "To be implemented" << endl;
    /*
    * YOUR CODE GOES HERE
    */
    return 0;
}

void generate_sudoku(unsigned sudoku[][SIZE])
{
    int x = 0;
    for (size_t i=1; i<=3; ++i)
    {
        for (size_t j=1; j<=3; ++j)
        {
            for (size_t k=1; k<=SIZE; ++k)
            {
                sudoku[3*(i-1)+j-1][k-1] = (x % SIZE) + 1;
                x++;
            }
            x += 3;
        }
        x++;
    }
}