/**
 * 
 *
 * @file extendible_hash.h
 * @author Chloe Albright
 * @brief Project 3: A representation of an extendible hash table data structure.
    This interface is designed for extendible hashing implementations such as
    splitting buckets when a collision occurs, 
    extending directory when global depth and local depth are equal,
    and other helper functions used to perform extendible hashing.
 * @version 0.1
 * @date 2022-03-29
 *
 * @copyright Copyright (c) 2022
 */

#include <vector>
#include <iostream>

using namespace std;

#ifndef EXTEND_HASH
#define EXTEND_HASH

/**
 * @brief An extendible hash table.
 */
class ExtendHash
{
    /**
     * @brief A representation of an extendible hash "block."
     *
     * If this block gets too big, it should be moved to disk instead of residing in main memory.
     * Four example blocks of size 4 are shown on the bottom of slide 67.
     */
    struct Node
    {
        /**
         * @brief Each "block" holds integers.
         */
        vector<int> data;
    };

    /**
     * @brief A representation of a block directory.
     *
     * An example directory is shown on the top of slide 67. The directory holds pointers to the blocks.
     */
    struct Directory
    {
        /**
         * @brief Pointers to the blocks (see top of slide 67).
         */
        vector<Node *> pointers;

        /**
         * @brief The number of significant bits to consider.
         *
         * On slide 67, this is the number in the parentheses (2).
         */
        int numSigBits;

        /**
         * @brief Construct a new, default Directory.
         */
        Directory();

        /**
         * @brief Construct a new Directory with the given size.
         *
         * @param size The initial directory size.
         */
        Directory(int size);

        /**
         * @brief The size of the directory.
         *
         * @return The size of the directory as an int.
         */
        int size();

        /**
         * @brief Resize this directory using the given size.
         *
         * @param size The new size of the directory.
         */
        void resize(int size);

    private:
        /**
         * @brief A helper function to compute the number of sigificant bits needed.
         *
         * @param size The directory size.
         * @return The number of signifcant bits the directory must consider as an int.
         */
        int static computeSigBits(int size);
    };

    /**
     * @brief The maximum number of "records" that fit on one block.
     *
     * Do not change this.
     */
    const int BLOCKSIZE = 4;

    /**
     * @brief The maximum number of bits to store.
     *
     * The example on slide 67 uses 6 bits. Here, we'll use 32. Do not change this.
     */
    const int INT_BITS = 32;

private:
    /**
     * @brief The root-level of the table (see slide 67).
     */
    Directory directory;

    /**
     * @brief Returns the first size bits of data as base 10 integer.
     *
     * This is essentially the hash function.
     *
     * @param data The data for which to obtain a key (hash).
     * @param size The number of significant bit to consider.
     * @return The first size bits of data as base 10 integer.
     */
    int getKey(int data, int size);

    /**
     * @brief Splits the directory.
     *
     * Doubles it (see slide 68).
     */
    void doubleDirectory();

public:
    /**
     * @brief Instantiates a new, default extendible hash table with a directory of size 2 that considers 1 signficant bit.
     *
     * The directory is initially size 2 and the number of significant bits is 1.
     */
    ExtendHash();

    /**
     * @brief Insert the given data into this extended hash table.
     *
     * @param d The data to insert.
     */
    void insert(int d);

    /**
     * @brief Overloaded insertion operator for extendible hash tables.
     *
     * @param out The output stream for which to insert.
     * @param eh The extendible hash table to insert into the stream.
     * @return The given ostream references as a ostream&.
     */
    friend ostream &operator<<(ostream &out, const ExtendHash &eh);
};

#endif