
# Project 3

The parts of assignment were completed:
```
From extendiblehash.cpp:
Directory functions: 
default constructor, size, resize, doubleDirectory, ExtendHash, insert

From hash_driver.cpp:
int main(): Create, insert, and output hashtable.
```

Any bugs that you have encountered: 
```
1.Segmentation fault for insert function:
p.push_back(d) 
//p is the node ptr to the node vector "data"
//d is the data to be inserted
therefore this is the correct implementation
p->data.pushback(d)

2.Poor wording/instructions for project which caused bugs & misunderstanding of doubleDirectory.
doubleDirectory post condition after implementation does not look like slide 68 of Lecture 7 Slides
(which assumes you're handling the case for the block which caused the collision).
Bugs occured while handling case for block which caused collision^.

3. Not enough examples of handling vector pointers given the context of this particular project.
Standard ways of allocating and deallocating pointers don't apply here because of the Node and Directory
structs functionality. Also no examples of proper copying of vector pointer to vector pointer. 
Bugs occured before removing dynamic pointers all together for doubleDirectory. 

```

The input file (if any) and the output files (if any):
```
None needed for this assignment assuming you submit the extendible_hash.cpp file, extendible_hash.h, hash_driver.cpp and 
READ.md file.

```

Complete instructions of how to run your program(s):
To compile on terminal using the MAKEFILE, type: 
```
make 
./hash_driver
```
OPTIONAL: Add clean object files to MAKEFILE when testing locally
```
# Clean obj files
clean:
	(rm -f *.o; rm -f hash_driver; rm -f extendible_hash)

(:
```
To run type 
```
make clean
```
## To Compile

Type the command:

```bash
make
```

will produce the library file `extendible_hash.o` and executable `hash_driver`.


## To Run

Type the command:

```bash
./hash_driver
```