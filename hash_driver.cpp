/**
 * @file hash_driver.cpp
 * @author Chloe Albright
 * 
 * @brief Project 3: Tests extendible hashing data structure:
    this program is implemented to test extendible hashing functions.
 * @version 0.1
 * @date 2022-03-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include "extendible_hash.h"

using namespace std;

int main(){
    // COMPLETED: Create an extendable hash table.
    ExtendHash CreateTable = ExtendHash();


    // COMPLETED: for 30 iterations.
    for (int i = 0; i < 30; i++)
    {
        // COMPLETED: Insert the value i * 8 into the table.
        CreateTable.insert(i*8);
    }

    // COMPLETED: Output the table to standard output.
    cout<< CreateTable;

    return 0;
}