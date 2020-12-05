# Algorithm-Project-2
Part I: Implement Huffman Algorithm.

 

Implement the Huffman algorithm we studied in the class and run the huffman encoding experiment for string input. You program should have the following functions, besides the main function.

 1. Huffman: takes a set of characters and their frequencies specified, returns a prefix tree.   

You should use heap data structure, for this you can use your work from your lab2 or the container class priority_queue in C++.

2. Traverse: given a prefix tree, generate the code word of the characters in the tree.

 

What to turn in:

Well documented source code in C++.
For your input, please print out the characters and the frequencies and the huffman code for each character.
* If you can print out the prefix tree, it will be great!  This is optional.
 Part II: Implement text compression.

 In this part, use a text file as input, read through the text file, calculate the frequencies of each character, apply your Huffman Algorithm to encode the text file into a new file.

 You program should have the following functions, besides the above functions.

 1. Encode: takes a text file name, calls the Huffman coding algorithm, traverse the tree to get the code word, and then encode the text file into a new file.

2. Decode: takes a prefix tree, and an encoded file, decode the file.
