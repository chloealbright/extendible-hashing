/**
 * 
 *
 * @file extendible_hash.cpp
 * @author Chloe Albright
 * 
 * @brief Project 3: Extendible hash table implementation file:
    this program is implemented to perform extendible hashing such as
    splitting block (i.e bucket) when a collision occurs, 
    extending directory when global depth and local depth (i.e SigBits) are equal,
    and other helper functions used to perform extendible hashing.
    
 * @version 0.1
 * @date 2022-03-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "extendible_hash.h"

#include <cmath>
#include <iostream>

using namespace std;

/** @brief A helper function to compute the number of sigificant bits needed.
*
* @param size The directory size.
* @return The number of signifcant bits the directory must consider as an int.
*/
int ExtendHash::Directory::computeSigBits(int size){
    return floor(log(size) / log(2) + .5);
}//end computeSigBits

ExtendHash::Directory::Directory(){};

//citing source: Data Structures and Algorithm Analysis, CH5

/** Directory
    @param size The initial directory size
    @post constructs a new Directory given the size 
    and calculates local depth i.e (SigBits) for the blocks
*/
ExtendHash::Directory::Directory(int size){

    resize(size);// COMPLETED: resize this directory
    computeSigBits(size);// COMPLETED: calculate and assign num of significant bits i.e local depth needed for given size.
}//end Directory

/**  size
    @returns number of pointers to blocks in the Directory
*/
int ExtendHash::Directory::size(){
    // COMPLETED: return the number of pointers to blocks.
    return pointers.size();
    
}//end size

/**  resize
    @param size The new size of the directory
    @post resizes the pointers to blocks according 
    to significant bits needed for new size.
*/
void ExtendHash::Directory::resize(int size){
    // resize the pointers.
    pointers.resize(size);

    // for each pointer.
    for (auto &p : pointers)
        // "clear" out the pointer.
        p = nullptr;

    // COMPLETED: compute and assign the number of sigificant bits needed for the new, given size.
    computeSigBits(pointers.size());

}//end resize

/**
* @brief Returns the first size bits of data as base 10 integer.
*
* This is essentially the hash function.
*
* @param data The data for which to obtain a key (hash).
* @param size The number of significant bit to consider.
* @return The first size bits of data as base 10 integer.
*/
int ExtendHash::getKey(int data, int size){
    data = data >> (INT_BITS - size);
    return data;
}//end getKey

/**  doubleDirectory
    helper function for insert
    @post splits (i.e doubles) a directory after a collision, 
    or in our case(while key generated is bigger than directory size).
Doesn't do exactly what slide 68 does. Example: if Directory size is 4 
(i.e 4 keys pointing to 4 individual blocks, 1 to 1)
After doubleDirectory: Directory size is 8, and its keys point to the 
original blocks respectively,
key 1 and key 2 point to block 1
key 3 and key 4 point to block 2
key 5 and key 6 point to block 3
key 6 and key 7 point to block 4
*/
void ExtendHash::doubleDirectory(){
    // create a new, temporary directory double the size of this table's directory.
    Directory temp(2 * directory.size());

    // COMPLETED: for each directory entry (i.e for each directory pointer)
    for(int i = 0; i < directory.pointers.size(); i++){ 
        // COMPLETED: Perform the directory split by copying the old pointers to the new one.
        temp.pointers[2*i] = directory.pointers[i];//set temp node ptr to current block pointer.
        temp.pointers[2*i+1] = directory.pointers[i]; //set temp node ptr's 2nd block ptr to current block pointer.
    }

    // following the split, increment the number of significant bits.
    ++directory.numSigBits;

    // COMPLETED: set this tables directory pointers to the temporary one we created earlier.
    directory.pointers.resize(temp.pointers.size());
    directory.pointers = temp.pointers;  
    
}//end doubleDirectory

/** ExtendHash
* @brief Instantiates a new, default extendible hash table with a directory of size 2 that considers 1 signficant bit.
* @post sets hashtable back to default size 
* The directory is initially size 2 and the number of significant bits is 1.
*/
ExtendHash::ExtendHash(){
    // COMPLETED: "Resize" this table's directory to the default size (e.g., like the one one slide 67).
    directory.resize(2);//default size 

    // COMPLETED: Set the number of significant bits to the default value (e.g., like the one one slide 67).
    directory.numSigBits = 1;
}//end ExtendHash

/**  insert
    @param d The data to insert
    @post inserts new data into extended hash table
*/
void ExtendHash::insert(int d){
    // "hash" the data (get its key) given the current directory size.
    int key = getKey(d, directory.size());

    // if the key is too big for the current directory.
    while (key >= directory.size()){

        // COMPLETED: "split" (i.e double) the directory.
        doubleDirectory(); 
        
        // compute and store a new key using the new number of significant bits to consider.
        key = getKey(d, directory.numSigBits);
    }

    // Now, we know we have enough room.
    // Get the node pointer to the block for the given key.
    Node *p = directory.pointers[key];

    // if there is no block for the key.
    if (directory.pointers[key] == nullptr)
    {
        // make a new "block" for the key.
        directory.pointers[key] = new Node();

        // set the pointer to point to it.
        p = directory.pointers[key];
    }

    // Now, p points to the block for the given key. It's time to do the insertion (if we have room in the block).

    // if there is room in the found block for the new piece of data.
    if (p->data.size() < BLOCKSIZE){ //data is a vector
        // COMPLETED: add the data to the end of the block.
        p->data.push_back(d);//p is the node ptr to the vector data, d is the data to be inserted. 

    }
    else{  // otherwise, we need to "split."
        // for each directory pointer.
        for (int i = 0; i < directory.pointers.size(); i++)
            // if i does not equal the key and the key's block pointer equals the current block pointer.
            if (i != key && directory.pointers[key] == directory.pointers[i]){
                //create a new, temporary block data with the old block's data.
                vector<int> tempBlock = p->data;

                // clear the old block's data.
                p->data.clear();

                // create a new block.
                directory.pointers[i] = new Node;

                // insert the old data into the new block.
                for (auto x : tempBlock)
                    insert(x);

                // COMPLETED: insert the given data.
                insert(d);

                // end the function. We're done.
                return;
            }

        // COMPLETED: at this point, we need a larger directory. Double it.
        doubleDirectory();

        // COMPLETED: then, insert the data.
        insert(d);
    }
}//end insert

// NOTE: Do not change.
ostream &operator<<(ostream &os, const ExtendHash &eh)
{
    // For each block pointer.
    for (int i = 0; i < eh.directory.pointers.size(); i++)
    {
        // Insert the block number.
        os << "Block #" << i << endl;

        // if the block pointer points to an actual block.
        if (eh.directory.pointers[i] != nullptr)
        {
            // Insert the block data.
            for (auto x : eh.directory.pointers[i]->data)
                os << x << endl;
        }
    }

    // return the given output stream reference.
    return os;
}//end operator<<


