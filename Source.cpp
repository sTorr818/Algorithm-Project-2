#include<iostream>
#include<cmath>
#include <cstdint>
#include<map>
#include <vector>
#include <ctime>
#include <csignal>
#include<queue>
#include<fstream>
#include<string>
#include <sstream>
#include <bitset>
using namespace std;

map<char, string> queMap;
map<char, int> frequencyMap;
string g;
float origSize, newSize;

struct MinHeapNode
{
    char data;
    int frequency;
    MinHeapNode* left;
    MinHeapNode* right;

    MinHeapNode(char data, int frequency)
    {
        
        left = right = NULL;
        this->data = data;
        this->frequency = frequency;
    }
};

struct compare
{
    bool operator()(MinHeapNode* left, MinHeapNode* right)
    {
        return (left->frequency > right->frequency);
    }
};



void printInput(struct MinHeapNode* root, string inputString)
{
    
    if (!root)
    {
        return;
    }
    
    if (root->data != '$')
    {
        cout << root->data << ": " << inputString << "\n";
    }
    printInput(root->left, inputString + "0");
    printInput(root->right, inputString + "1");
    
    
    
}

void storeQueue(struct MinHeapNode* root, string inputString)
{
    if (root == NULL)
    {
        
        return;
        
    }

    if (root->data != '$')
    {
        queMap[root->data] = inputString;
    }

    storeQueue(root->left, inputString + "0");
    storeQueue(root->right, inputString + "1");
}

priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;


void HuffmanCodes(int size)
{
    
    struct MinHeapNode* left, * right, * top;
    for (map<char, int>::iterator v = frequencyMap.begin(); v != frequencyMap.end(); v++)
    {
        minHeap.push(new MinHeapNode(v->first, v->second));
    }

    while (minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new MinHeapNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    storeQueue(minHeap.top(), "");

    cout << "Characters and their Codes:\n";
    printInput(minHeap.top(), "");
    // Attempting to reset the heap
   
    frequencyMap.clear();
   
  
   
}

void clearQue(int size)
{
    while (!minHeap.empty()) {        //check whether pq empty or not
        MinHeapNode* m = minHeap.top();
        minHeap.pop();                 //erasing content one by one

    }
    if (minHeap.empty())
        cout << "Queue cleared" << endl;



}


void calculateFrequency(string inputString)
{
    
    for (int i = 0; i < inputString.size(); i++)
    {
        frequencyMap[inputString[i]]++;
    }
    
}


void displayFrequency(string inputString)
{
    map<char, int >m;

    map<char, int >::iterator itr;

    for (long i = 0; i < inputString.length(); i++)
    {
        m[inputString[i]]++;
    }
    cout << "Frequencies of characters: " << endl;
    for (itr = m.begin(); itr != m.end(); itr++)
    {
        cout << itr->first << " - " << itr->second << endl;
    }


    cout << "\n";
    m.clear();
   // itr.clear(begin, end);
}

string decodeString(struct MinHeapNode* root, string inputString)
{
    string answer = "";
    struct MinHeapNode* current = root;
    for (int i = 0; i < inputString.size(); i++)
    {
        if (inputString[i] == '0')
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }

        if (current->left == NULL && current->right == NULL)
        {
            answer += current->data;
            current = root;
        }
    }
    return answer + '\0';
}

string encodeHuffman(string inputString)
{
    string encodedString;
    calculateFrequency(inputString);
    HuffmanCodes(inputString.length());

    for (auto i : inputString)
    {
        encodedString += queMap[i];
    }
    return encodedString;
    
}

void resetTree(struct MinHeapNode* root, string inputString)
{
    struct MinHeapNode* current = root;
    storeQueue(NULL,inputString);
    //queMap.clear();
    frequencyMap.clear();

}


int main()
{
    fstream originalFile, encodedFile;
    string inputString;
    // string inputString = "All falls into place";
    string encodedString;
    string decodedString;
    //needed this to create the original file
    cout << "This is the original String\n";
    originalFile.open("original_1.txt", ios::out);  // open a file to perform write operation using file object
    if (originalFile.is_open())     //checking whether the file is open
    {
        originalFile << "Hopefully this gets decoded soon" << endl;; //inserting text
        originalFile.close(); //close the file object
    }
    //Can cut here to above to create for to save space and leave files as is once created


    originalFile.open("original_1.txt", ios::in); //open a file to perform read operation using file object
    if (originalFile.is_open()) {   //checking whether the file is open
        string fileString;
        string inputString;
        while (getline(originalFile, fileString)) {  //read data from file object and put it into string.
            cout << fileString << "\n";   //print the data of the string
            g = fileString;
            origSize = fileString.length();
            cout << "This string is " << origSize << " bytes. \n";
        }
        //Combine test phase with reading from a file
    //CLear file flags
        originalFile.clear();
    }


    inputString = g;
    displayFrequency(inputString);


    encodedString = encodeHuffman(inputString);
   
//Prints the Binary
       //cout << "\nEncoded String:\n" << encodedString << endl;
    //Converts to the ASCII

    stringstream sstream(encodedString);
    string output;
    while (sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }
    

   
    //std::cout << output;
    cout << "\nEncoded String:\n" << output << endl;

    g = output;
    // g = encodedString;





    //Create a new file for encoded text
    encodedFile.open("encoded_1.txt", ios::out);  // open a file to perform write operation using file object
    if (encodedFile.is_open())     //checking whether the file is open
    {
        string fileString2;
        fileString2 = g;
        encodedFile << fileString2 << "\n"; //inserting text
        encodedFile.close(); //close the file object
    }
    encodedFile.open("encoded_1.txt", ios::in); //open a file to perform read operation using file object
    if (encodedFile.is_open()) {   //checking whether the file is open
        string fileString2;
        string encodedString;
        while (getline(encodedFile, fileString2)) {  //read data from file object and put it into string.
            //cout << fileString2 << "\n";   //print the data of the string
            newSize = fileString2.length();
            cout << "This string is " << newSize << " bytes. \n";
        }
        //CLear file flags
        encodedFile.clear();
        //Combine test phase with reading from a file
    }

    //Show the difference in bytes
    cout << "The Compression ratio of the original file size and the size of the compressed file is " << (newSize / origSize) << "%" << endl;

    //Now decode and print
   decodedString = decodeString(minHeap.top(), encodedString);
   cout << "\nDecoded String:\n" << decodedString << endl;

    cout << "Next File\n";
    newSize = 0;
    origSize = 0;
    clearQue(inputString.length());
    
    
   // clearQue(inputString.length());
    //File2/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    fstream originalFile_2, encodedFile_2;
    //needed this to create the original file
    cout << "This is the original String\n";
    originalFile_2.open("original_2.txt", ios::out);  // open a file to perform write operation using file object
    if (originalFile.is_open())     //checking whether the file is open
    {
        originalFile_2 << "The world has seen nothing new during the entirety of this year" << endl;; //inserting text
        originalFile_2.close(); //close the file object
    }

    originalFile_2.open("original_2.txt", ios::in); //open a file to perform read operation using file object
    if (originalFile_2.is_open()) {   //checking whether the file is open
        string fileString;
        string inputString;
        while (getline(originalFile_2, fileString)) {  //read data from file object and put it into string.
            cout << fileString << "\n";   //print the data of the string
            g = fileString;
            origSize = fileString.length();
            cout << "This string is " << origSize << " bytes. \n";
        }
        //Combine test phase with reading from a file
   //CLear file flags
        originalFile_2.clear();
    }


    inputString = g;


    


    displayFrequency(inputString);
    
    encodedString = encodeHuffman(inputString);
    //Prints the Binary
    //cout << "\nEncoded String:\n" << encodedString << endl;
    output.clear();
    stringstream satream(encodedString);
    while (satream.good())
    {
        std::bitset<8> bits;
        satream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

    //std::cout << output;
    cout << "\nEncoded String:\n" << output << endl;

    g = output;
    // g = encodedString;

    //Create a new file for encoded text
    encodedFile_2.open("encoded_2.txt", ios::out);  // open a file to perform write operation using file object
    if (encodedFile_2.is_open())     //checking whether the file is open
    {
        string fileString;
        fileString = g;
        encodedFile_2 << fileString << "\n"; //inserting text
        encodedFile_2.close(); //close the file object
    }
    encodedFile_2.open("encoded_2.txt", ios::in); //open a file to perform read operation using file object
    if (encodedFile_2.is_open()) {   //checking whether the file is open
        string fileString;
        string encodedString;
        while (getline(encodedFile_2, fileString)) {  //read data from file object and put it into string.

           // cout << fileString << "\n";   //print the data of the string
            newSize = fileString.length() ;
            cout << "This string is " << newSize << " bytes. \n";
        }
        //CLear file flags
        encodedFile_2.clear();
        //Combine test phase with reading from a file
    }

    //Show the difference in bytes
    cout << "The Compression ratio of the original fie size and the size of the compressed file is " << (newSize / origSize) << "%" << endl;

    //Now decode and print
    decodedString = decodeString(minHeap.top(), encodedString);
    cout << "\nDecoded String:\n" << decodedString << endl;

    cout << "\nNext File\n\n";
    newSize = 0;
    origSize = 0;
    
    //Remove these when done fixing problem
    clearQue(inputString.length());
    //File3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    fstream originalFile_3, encodedFile_3;
    //needed this to create the original file
    cout << "This is the original String\n";
    originalFile_3.open("original_3.txt", ios::out);  // open a file to perform write operation using file object
    if (originalFile.is_open())     //checking whether the file is open
    {
        originalFile_3 << "By all means please go ahead" << endl;; //inserting text
        originalFile_3.close(); //close the file object
    }

    originalFile_3.open("original_3.txt", ios::in); //open a file to perform read operation using file object
    if (originalFile_3.is_open()) {   //checking whether the file is open
        string fileString;
        string inputString;
        while (getline(originalFile_3, fileString)) {  //read data from file object and put it into string.
            cout << fileString << "\n";   //print the data of the string
            g = fileString;
            origSize = fileString.length();
            cout << "This string is " << origSize << " bytes. \n";
        }
        //Combine test phase with reading from a file
   //CLear file flags
        originalFile_3.clear();
    }


    inputString = g;


    //m.clear();
  //  map<char, int >::iterator itr;


    displayFrequency(inputString);
    

    encodedString = encodeHuffman(inputString);
    //Prints the Binary
    //cout << "\nEncoded String:\n" << encodedString << endl;
    output.clear();
    stringstream sbtream(encodedString);
    while (sbtream.good())
    {
        std::bitset<8> bits;
        sbtream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

    //std::cout << output;
    cout << "\nEncoded String:\n" << output << endl;

    g = output;
    // g = encodedString;

    //Create a new file for encoded text
    encodedFile_3.open("encoded_3.txt", ios::out);  // open a file to perform write operation using file object
    if (encodedFile_3.is_open())     //checking whether the file is open
    {
        string fileString;
        fileString = g;
        encodedFile_3 << fileString << "\n"; //inserting text
        encodedFile_3.close(); //close the file object
    }
    encodedFile_3.open("encoded_3.txt", ios::in); //open a file to perform read operation using file object
    if (encodedFile_3.is_open()) {   //checking whether the file is open
        string fileString;
        string encodedString;
        while (getline(encodedFile_3, fileString)) {  //read data from file object and put it into string.

           // cout << fileString << "\n";   //print the data of the string
            newSize = fileString.length() ;
            cout << "This string is " << newSize << " bytes. \n";
        }
        //CLear file flags
        encodedFile_3.clear();
        //Combine test phase with reading from a file
    }

    //Show the difference in bytes
    cout << "The Compression ratio of the original fie size and the size of the compressed file is " << (newSize / origSize) << "%" << endl;

    //Now decode and print
    decodedString = decodeString(minHeap.top(), encodedString);
    cout << "\nDecoded String:\n" << decodedString << endl;

    cout << "\nNext File\n\n";
    newSize = 0;
    origSize = 0;
    clearQue(inputString.length());
    //File4/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    fstream originalFile_4, encodedFile_4;
    //needed this to create the original file
    cout << "This is the original String\n";
    originalFile_4.open("original_4.txt", ios::out);  // open a file to perform write operation using file object
    if (originalFile.is_open())     //checking whether the file is open
    {
        originalFile_4 << "Apples and oranges are tasty " << endl;; //inserting text
        originalFile_4.close(); //close the file object
    }

    originalFile_4.open("original_4.txt", ios::in); //open a file to perform read operation using file object
    if (originalFile_4.is_open()) {   //checking whether the file is open
        string fileString;
        string inputString;
        while (getline(originalFile_4, fileString)) {  //read data from file object and put it into string.
            cout << fileString << "\n";   //print the data of the string
            g = fileString;
            origSize = fileString.length();
            cout << "This string is " << origSize << " bytes. \n";
        }
        //Combine test phase with reading from a file
   //CLear file flags
        originalFile_4.clear();
    }


    inputString = g;


    //m.clear();
  //  map<char, int >::iterator itr;


    displayFrequency(inputString);


    encodedString = encodeHuffman(inputString);
    //Prints the Binary
    //cout << "\nEncoded String:\n" << encodedString << endl;

    while (sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

    //std::cout << output;
    cout << "\nEncoded String:\n" << output << endl;

    g = output;
    // g = encodedString;

    //Create a new file for encoded text
    encodedFile_4.open("encoded_4.txt", ios::out);  // open a file to perform write operation using file object
    if (encodedFile_4.is_open())     //checking whether the file is open
    {
        string fileString;
        fileString = g;
        encodedFile_4 << fileString << "\n"; //inserting text
        encodedFile_4.close(); //close the file object
    }
    encodedFile_4.open("encoded_4.txt", ios::in); //open a file to perform read operation using file object
    if (encodedFile_4.is_open()) {   //checking whether the file is open
        string fileString;
        string encodedString;
        while (getline(encodedFile_4, fileString)) {  //read data from file object and put it into string.

           // cout << fileString << "\n";   //print the data of the string
            newSize = fileString.length() ;
            cout << "This string is " << newSize << " bytes. \n";
        }
        //CLear file flags
        encodedFile_4.clear();
        //Combine test phase with reading from a file
    }

    //Show the difference in bytes
    cout << "The Compression ratio of the original fie size and the size of the compressed file is " << (newSize / origSize) << "%" << endl;

    //Now decode and print
    decodedString = decodeString(minHeap.top(), encodedString);
    cout << "\nDecoded String:\n" << decodedString << endl;

    cout << "\nNext File\n\n";
    newSize = 0;
    origSize = 0;
    clearQue(inputString.length());
    //File5/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    fstream originalFile_5, encodedFile_5;
    //needed this to create the original file
    cout << "This is the original String\n";
    originalFile_5.open("original_5.txt", ios::out);  // open a file to perform write operation using file object
    if (originalFile.is_open())     //checking whether the file is open
    {
        originalFile_5 << "By all means please go ahead" << endl;; //inserting text
        originalFile_5.close(); //close the file object
    }

    originalFile_5.open("original_5.txt", ios::in); //open a file to perform read operation using file object
    if (originalFile_5.is_open()) {   //checking whether the file is open
        string fileString;
        string inputString;
        while (getline(originalFile_5, fileString)) {  //read data from file object and put it into string.
            cout << fileString << "\n";   //print the data of the string
            g = fileString;
            origSize = fileString.length();
            cout << "This string is " << origSize << " bytes. \n";
        }
        //Combine test phase with reading from a file
   //CLear file flags
        originalFile_5.clear();
    }


    inputString = g;


    //m.clear();
  //  map<char, int >::iterator itr;


    displayFrequency(inputString);


    encodedString = encodeHuffman(inputString);
    //Prints the Binary
   //cout << "\nEncoded String:\n" << encodedString << endl;

    while (sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

    //std::cout << output;
    cout << "\nEncoded String:\n" << output << endl;

    g = output;
    // g = encodedString;

    //Create a new file for encoded text
    encodedFile_5.open("encoded_5.txt", ios::out);  // open a file to perform write operation using file object
    if (encodedFile_5.is_open())     //checking whether the file is open
    {
        string fileString;
        fileString = g;
        encodedFile_5 << fileString << "\n"; //inserting text
        encodedFile_5.close(); //close the file object
    }
    encodedFile_5.open("encoded_5.txt", ios::in); //open a file to perform read operation using file object
    if (encodedFile_5.is_open()) {   //checking whether the file is open
        string fileString;
        string encodedString;
        while (getline(encodedFile_5, fileString)) {  //read data from file object and put it into string.

           // cout << fileString << "\n";   //print the data of the string
            newSize = fileString.length() ;
            cout << "This string is " << newSize << " bytes. \n";
        }
        //CLear file flags
        encodedFile_5.clear();
        //Combine test phase with reading from a file
    }

    //Show the difference in bytes
    cout << "The Compression ratio of the original fie size and the size of the compressed file is " << (newSize / origSize) << "%" << endl;

    //Now decode and print
    decodedString = decodeString(minHeap.top(), encodedString);
    cout << "\nDecoded String:\n" << decodedString << endl;

    cout << "\nNext File\n\n";
    newSize = 0;
    origSize = 0;
    clearQue(inputString.length());
    //File6/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    fstream originalFile_6, encodedFile_6;
    //needed this to create the original file
    cout << "This is the original String\n";
    originalFile_6.open("original_6.txt", ios::out);  // open a file to perform write operation using file object
    if (originalFile.is_open())     //checking whether the file is open
    {
        originalFile_6 << "Why would you tell me no if there is no problem" << endl;; //inserting text
        originalFile_6.close(); //close the file object
    }

    originalFile_6.open("original_6.txt", ios::in); //open a file to perform read operation using file object
    if (originalFile_6.is_open()) {   //checking whether the file is open
        string fileString;
        string inputString;
        while (getline(originalFile_6, fileString)) {  //read data from file object and put it into string.
            cout << fileString << "\n";   //print the data of the string
            g = fileString;
            origSize = fileString.length();
            cout << "This string is " << origSize << " bytes. \n";
        }
        //Combine test phase with reading from a file
   //CLear file flags
        originalFile_6.clear();
    }


    inputString = g;


    //m.clear();
  //  map<char, int >::iterator itr;


    displayFrequency(inputString);


    encodedString = encodeHuffman(inputString);
    //Prints the Binary
   //cout << "\nEncoded String:\n" << encodedString << endl;

    while (sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

    //std::cout << output;
    cout << "\nEncoded String:\n" << output << endl;

    g = output;
    // g = encodedString;

    //Create a new file for encoded text
    encodedFile_6.open("encoded_6.txt", ios::out);  // open a file to perform write operation using file object
    if (encodedFile_6.is_open())     //checking whether the file is open
    {
        string fileString;
        fileString = g;
        encodedFile_6 << fileString << "\n"; //inserting text
        encodedFile_6.close(); //close the file object
    }
    encodedFile_6.open("encoded_6.txt", ios::in); //open a file to perform read operation using file object
    if (encodedFile_6.is_open()) {   //checking whether the file is open
        string fileString;
        string encodedString;
        while (getline(encodedFile_6, fileString)) {  //read data from file object and put it into string.

           // cout << fileString << "\n";   //print the data of the string
            newSize = fileString.length() ;
            cout << "This string is " << newSize << " bytes. \n";
        }
        //CLear file flags
        encodedFile_6.clear();
        //Combine test phase with reading from a file
    }

    //Show the difference in bytes
    cout << "The Compression ratio of the original fie size and the size of the compressed file is " << (newSize / origSize) << "%" << endl;

    //Now decode and print
    decodedString = decodeString(minHeap.top(), encodedString);
    cout << "\nDecoded String:\n" << decodedString << endl;

    cout << "\nNext File\n\n";
    newSize = 0;
    origSize = 0;
    clearQue(inputString.length());
    //File7/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    fstream originalFile_7, encodedFile_7;
    //needed this to create the original file
    cout << "This is the original String\n";
    originalFile_7.open("original_7.txt", ios::out);  // open a file to perform write operation using file object
    if (originalFile.is_open())     //checking whether the file is open
    {
        originalFile_7 << "I hate the sharks in the ocean" << endl;; //inserting text
        originalFile_7.close(); //close the file object
    }

    originalFile_7.open("original_7.txt", ios::in); //open a file to perform read operation using file object
    if (originalFile_7.is_open()) {   //checking whether the file is open
        string fileString;
        string inputString;
        while (getline(originalFile_7, fileString)) {  //read data from file object and put it into string.
            cout << fileString << "\n";   //print the data of the string
            g = fileString;
            origSize = fileString.length();
            cout << "This string is " << origSize << " bytes. \n";
        }
        //Combine test phase with reading from a file
   //CLear file flags
        originalFile_7.clear();
    }


    inputString = g;


    //m.clear();
  //  map<char, int >::iterator itr;


    displayFrequency(inputString);


    encodedString = encodeHuffman(inputString);
    //Prints the Binary
   //cout << "\nEncoded String:\n" << encodedString << endl;

    while (sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

    //std::cout << output;
    cout << "\nEncoded String:\n" << output << endl;

    g = output;
    // g = encodedString;

    //Create a new file for encoded text
    encodedFile_7.open("encoded_7.txt", ios::out);  // open a file to perform write operation using file object
    if (encodedFile_7.is_open())     //checking whether the file is open
    {
        string fileString;
        fileString = g;
        encodedFile_7 << fileString << "\n"; //inserting text
        encodedFile_7.close(); //close the file object
    }
    encodedFile_7.open("encoded_7.txt", ios::in); //open a file to perform read operation using file object
    if (encodedFile_7.is_open()) {   //checking whether the file is open
        string fileString;
        string encodedString;
        while (getline(encodedFile_7, fileString)) {  //read data from file object and put it into string.

           // cout << fileString << "\n";   //print the data of the string
            newSize = fileString.length() ;
            cout << "This string is " << newSize << " bytes. \n";
        }
        //CLear file flags
        encodedFile_7.clear();
        //Combine test phase with reading from a file
    }

    //Show the difference in bytes
    cout << "The Compression ratio of the original fie size and the size of the compressed file is " << (newSize / origSize) << "%" << endl;

    //Now decode and print
    decodedString = decodeString(minHeap.top(), encodedString);
    cout << "\nDecoded String:\n" << decodedString << endl;

    cout << "\nNext File\n\n";
    newSize = 0;
    origSize = 0;
    clearQue(inputString.length());
    //File8/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    fstream originalFile_8, encodedFile_8;
    //needed this to create the original file
    cout << "This is the original String\n";
    originalFile_8.open("original_8.txt", ios::out);  // open a file to perform write operation using file object
    if (originalFile.is_open())     //checking whether the file is open
    {
        originalFile_8 << "Please take care of my pets while I am away" << endl;; //inserting text
        originalFile_8.close(); //close the file object
    }

    originalFile_8.open("original_8.txt", ios::in); //open a file to perform read operation using file object
    if (originalFile_8.is_open()) {   //checking whether the file is open
        string fileString;
        string inputString;
        while (getline(originalFile_8, fileString)) {  //read data from file object and put it into string.
            cout << fileString << "\n";   //print the data of the string
            g = fileString;
            origSize = fileString.length();
            cout << "This string is " << origSize << " bytes. \n";
        }
        //Combine test phase with reading from a file
   //CLear file flags
        originalFile_8.clear();
    }


    inputString = g;


    //m.clear();
  //  map<char, int >::iterator itr;


    displayFrequency(inputString);


    encodedString = encodeHuffman(inputString);
    //Prints the Binary
   //cout << "\nEncoded String:\n" << encodedString << endl;

    while (sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

    //std::cout << output;
    cout << "\nEncoded String:\n" << output << endl;

    g = output;
    // g = encodedString;

    //Create a new file for encoded text
    encodedFile_8.open("encoded_8.txt", ios::out);  // open a file to perform write operation using file object
    if (encodedFile_8.is_open())     //checking whether the file is open
    {
        string fileString;
        fileString = g;
        encodedFile_8 << fileString << "\n"; //inserting text
        encodedFile_8.close(); //close the file object
    }
    encodedFile_8.open("encoded_8.txt", ios::in); //open a file to perform read operation using file object
    if (encodedFile_8.is_open()) {   //checking whether the file is open
        string fileString;
        string encodedString;
        while (getline(encodedFile_8, fileString)) {  //read data from file object and put it into string.

           // cout << fileString << "\n";   //print the data of the string
            newSize = fileString.length() ;
            cout << "This string is " << newSize << " bytes. \n";
        }
        //CLear file flags
        encodedFile_8.clear();
        //Combine test phase with reading from a file
    }

    //Show the difference in bytes
    cout << "The Compression ratio of the original fie size and the size of the compressed file is " << (newSize / origSize) << "%" << endl;

    //Now decode and print
    decodedString = decodeString(minHeap.top(), encodedString);
    cout << "\nDecoded String:\n" << decodedString << endl;

    cout << "\nNext File\n\n";
    newSize = 0;
    origSize = 0;
    clearQue(inputString.length());
    //File9/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    fstream originalFile_9, encodedFile_9;
    //needed this to create the original file
    cout << "This is the original String\n";
    originalFile_9.open("original_9.txt", ios::out);  // open a file to perform write operation using file object
    if (originalFile.is_open())     //checking whether the file is open
    {
        originalFile_9 << "Christmas is right around the corner" << endl;; //inserting text
        originalFile_9.close(); //close the file object
    }

    originalFile_9.open("original_9.txt", ios::in); //open a file to perform read operation using file object
    if (originalFile_9.is_open()) {   //checking whether the file is open
        string fileString;
        string inputString;
        while (getline(originalFile_9, fileString)) {  //read data from file object and put it into string.
            cout << fileString << "\n";   //print the data of the string
            g = fileString;
            origSize = fileString.length();
            cout << "This string is " << origSize << " bytes. \n";
        }
        //Combine test phase with reading from a file
   //CLear file flags
        originalFile_9.clear();
    }


    inputString = g;


    //m.clear();
  //  map<char, int >::iterator itr;


    displayFrequency(inputString);


    encodedString = encodeHuffman(inputString);
    //Prints the Binary
    //cout << "\nEncoded String:\n" << encodedString << endl;

    while (sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

    //std::cout << output;
    cout << "\nEncoded String:\n" << output << endl;

    g = output;
    // g = encodedString;

    //Create a new file for encoded text
    encodedFile_9.open("encoded_9.txt", ios::out);  // open a file to perform write operation using file object
    if (encodedFile_9.is_open())     //checking whether the file is open
    {
        string fileString;
        fileString = g;
        encodedFile_9 << fileString << "\n"; //inserting text
        encodedFile_9.close(); //close the file object
    }
    encodedFile_9.open("encoded_9.txt", ios::in); //open a file to perform read operation using file object
    if (encodedFile_9.is_open()) {   //checking whether the file is open
        string fileString;
        string encodedString;
        while (getline(encodedFile_9, fileString)) {  //read data from file object and put it into string.

           // cout << fileString << "\n";   //print the data of the string
            newSize = fileString.length() ;
            cout << "This string is " << newSize << " bytes. \n";
        }
        //CLear file flags
        encodedFile_9.clear();
        //Combine test phase with reading from a file
    }

    //Show the difference in bytes
    cout << "The Compression ratio of the original fie size and the size of the compressed file is " << (newSize / origSize) << "%" << endl;

    //Now decode and print
    decodedString = decodeString(minHeap.top(), encodedString);
    cout << "\nDecoded String:\n" << decodedString << endl;

    cout << "\nNext File\n\n";
    newSize = 0;
    origSize = 0;
    clearQue(inputString.length());
    //File10/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    fstream originalFile_10, encodedFile_10;
    //needed this to create the original file
    cout << "This is the original String\n";
    originalFile_10.open("original_10.txt", ios::out);  // open a file to perform write operation using file object
    if (originalFile.is_open())     //checking whether the file is open
    {
        originalFile_10 << "Do you believe in the tooth fairy" << endl;; //inserting text
        originalFile_10.close(); //close the file object
    }

    originalFile_10.open("original_10.txt", ios::in); //open a file to perform read operation using file object
    if (originalFile_10.is_open()) {   //checking whether the file is open
        string fileString;
        string inputString;
        while (getline(originalFile_10, fileString)) {  //read data from file object and put it into string.
            cout << fileString << "\n";   //print the data of the string
            g = fileString;
            origSize = fileString.length();
            cout << "This string is " << origSize << " bytes. \n";
        }
        //Combine test phase with reading from a file
   //CLear file flags
        originalFile_10.clear();
    }


    inputString = g;


    //m.clear();
  //  map<char, int >::iterator itr;


    displayFrequency(inputString);


    encodedString = encodeHuffman(inputString);
    //Prints the Binary
     //cout << "\nEncoded String:\n" << encodedString << endl;

    while (sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

    //std::cout << output;
    cout << "\nEncoded String:\n" << output << endl;

    g = output;
    // g = encodedString;

    //Create a new file for encoded text
    encodedFile_10.open("encoded_10.txt", ios::out);  // open a file to perform write operation using file object
    if (encodedFile_10.is_open())     //checking whether the file is open
    {
        string fileString;
        fileString = g;
        encodedFile_10 << fileString << "\n"; //inserting text
        encodedFile_10.close(); //close the file object
    }
    encodedFile_10.open("encoded_10.txt", ios::in); //open a file to perform read operation using file object
    if (encodedFile_10.is_open()) {   //checking whether the file is open
        string fileString;
        string encodedString;
        while (getline(encodedFile_10, fileString)) {  //read data from file object and put it into string.

           // cout << fileString << "\n";   //print the data of the string
            newSize = fileString.length() ;
            cout << "This string is " << newSize << " bytes. \n";
        }
        //CLear file flags
        encodedFile_10.clear();
        //Combine test phase with reading from a file
    }

    //Show the difference in bytes
    cout << "The Compression ratio of the original fie size and the size of the compressed file is " << (newSize / origSize) << "%" << endl;

    //Now decode and print
    decodedString = decodeString(minHeap.top(), encodedString);
    cout << "\nDecoded String:\n" << decodedString << endl;

    cout << "\nNext File\n\n";
    newSize = 0;
    origSize = 0;
    clearQue(inputString.length());
    //File11/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    fstream originalFile_11, encodedFile_11;
    //needed this to create the original file
    cout << "This is the original String\n";
    originalFile_11.open("original_11.txt", ios::out);  // open a file to perform write operation using file object
    if (originalFile.is_open())     //checking whether the file is open
    {
        originalFile_11 << "Easter is such a nice family holiday" << endl;; //inserting text
        originalFile_11.close(); //close the file object
    }

    originalFile_11.open("original_11.txt", ios::in); //open a file to perform read operation using file object
    if (originalFile_11.is_open()) {   //checking whether the file is open
        string fileString;
        string inputString;
        while (getline(originalFile_11, fileString)) {  //read data from file object and put it into string.
            cout << fileString << "\n";   //print the data of the string
            g = fileString;
            origSize = fileString.length();
            cout << "This string is " << origSize << " bytes. \n";
        }
        //Combine test phase with reading from a file
   //CLear file flags
        originalFile_11.clear();
    }


    inputString = g;


    //m.clear();
  //  map<char, int >::iterator itr;


    displayFrequency(inputString);


    encodedString = encodeHuffman(inputString);
    //Prints the Binary
    //cout << "\nEncoded String:\n" << encodedString << endl;

    while (sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

    //std::cout << output;
    cout << "\nEncoded String:\n" << output << endl;

    g = output;
    // g = encodedString;

    //Create a new file for encoded text
    encodedFile_11.open("encoded_11.txt", ios::out);  // open a file to perform write operation using file object
    if (encodedFile_11.is_open())     //checking whether the file is open
    {
        string fileString;
        fileString = g;
        encodedFile_11 << fileString << "\n"; //inserting text
        encodedFile_11.close(); //close the file object
    }
    encodedFile_11.open("encoded_11.txt", ios::in); //open a file to perform read operation using file object
    if (encodedFile_11.is_open()) {   //checking whether the file is open
        string fileString;
        string encodedString;
        while (getline(encodedFile_11, fileString)) {  //read data from file object and put it into string.

           // cout << fileString << "\n";   //print the data of the string
            newSize = fileString.length() ;
            cout << "This string is " << newSize << " bytes. \n";
        }
        //CLear file flags
        encodedFile_11.clear();
        //Combine test phase with reading from a file
    }

    //Show the difference in bytes
    cout << "The Compression ratio of the original fie size and the size of the compressed file is " << (newSize / origSize) << "%" << endl;

    //Now decode and print
    decodedString = decodeString(minHeap.top(), encodedString);
    cout << "\nDecoded String:\n" << decodedString << endl;

    cout << "\nNext File\n\n";
    newSize = 0;
    origSize = 0;
    clearQue(inputString.length());
    //File12/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    fstream originalFile_12, encodedFile_12;
    //needed this to create the original file
    cout << "This is the original String\n";
    originalFile_12.open("original_12.txt", ios::out);  // open a file to perform write operation using file object
    if (originalFile.is_open())     //checking whether the file is open
    {
        originalFile_12 << "Oh where oh where have my pets gone" << endl;; //inserting text
        originalFile_12.close(); //close the file object
    }

    originalFile_12.open("original_12.txt", ios::in); //open a file to perform read operation using file object
    if (originalFile_12.is_open()) {   //checking whether the file is open
        string fileString;
        string inputString;
        while (getline(originalFile_12, fileString)) {  //read data from file object and put it into string.
            cout << fileString << "\n";   //print the data of the string
            g = fileString;
            origSize = fileString.length();
            cout << "This string is " << origSize << " bytes. \n";
        }
        //Combine test phase with reading from a file
   //CLear file flags
        originalFile_12.clear();
    }


    inputString = g;


    //m.clear();
  //  map<char, int >::iterator itr;


    displayFrequency(inputString);


    encodedString = encodeHuffman(inputString);
    //Prints the Binary
   //cout << "\nEncoded String:\n" << encodedString << endl;

    while (sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

    //std::cout << output;
    cout << "\nEncoded String:\n" << output << endl;

    g = output;
    // g = encodedString;

    //Create a new file for encoded text
    encodedFile_12.open("encoded_12.txt", ios::out);  // open a file to perform write operation using file object
    if (encodedFile_12.is_open())     //checking whether the file is open
    {
        string fileString;
        fileString = g;
        encodedFile_12 << fileString << "\n"; //inserting text
        encodedFile_12.close(); //close the file object
    }
    encodedFile_12.open("encoded_12.txt", ios::in); //open a file to perform read operation using file object
    if (encodedFile_12.is_open()) {   //checking whether the file is open
        string fileString;
        string encodedString;
        while (getline(encodedFile_12, fileString)) {  //read data from file object and put it into string.

           // cout << fileString << "\n";   //print the data of the string
            newSize = fileString.length() ;
            cout << "This string is " << newSize << " bytes. \n";
        }
        //CLear file flags
        encodedFile_12.clear();
        //Combine test phase with reading from a file
    }

    //Show the difference in bytes
    cout << "The Compression ratio of the original fie size and the size of the compressed file is " << (newSize / origSize) << "%" << endl;

    //Now decode and print
    decodedString = decodeString(minHeap.top(), encodedString);
    cout << "\nDecoded String:\n" << decodedString << endl;

    cout << "\nNext File\n\n";
    newSize = 0;
    origSize = 0;
    clearQue(inputString.length());
    //File13/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    fstream originalFile_13, encodedFile_13;
    //needed this to create the original file
    cout << "This is the original String\n";
    originalFile_13.open("original_13.txt", ios::out);  // open a file to perform write operation using file object
    if (originalFile.is_open())     //checking whether the file is open
    {
        originalFile_13 << "I will find you and I will hurt you" << endl;; //inserting text
        originalFile_13.close(); //close the file object
    }

    originalFile_13.open("original_13.txt", ios::in); //open a file to perform read operation using file object
    if (originalFile_13.is_open()) {   //checking whether the file is open
        string fileString;
        string inputString;
        while (getline(originalFile_13, fileString)) {  //read data from file object and put it into string.
            cout << fileString << "\n";   //print the data of the string
            g = fileString;
            origSize = fileString.length();
            cout << "This string is " << origSize << " bytes. \n";
        }
        //Combine test phase with reading from a file
   //CLear file flags
        originalFile_13.clear();
    }


    inputString = g;


    //m.clear();
  //  map<char, int >::iterator itr;


    displayFrequency(inputString);


    encodedString = encodeHuffman(inputString);
    //Prints the Binary
   //cout << "\nEncoded String:\n" << encodedString << endl;

    while (sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

    //std::cout << output;
    cout << "\nEncoded String:\n" << output << endl;

    g = output;
    // g = encodedString;

    //Create a new file for encoded text
    encodedFile_13.open("encoded_13.txt", ios::out);  // open a file to perform write operation using file object
    if (encodedFile_13.is_open())     //checking whether the file is open
    {
        string fileString;
        fileString = g;
        encodedFile_13 << fileString << "\n"; //inserting text
        encodedFile_13.close(); //close the file object
    }
    encodedFile_13.open("encoded_13.txt", ios::in); //open a file to perform read operation using file object
    if (encodedFile_13.is_open()) {   //checking whether the file is open
        string fileString;
        string encodedString;
        while (getline(encodedFile_13, fileString)) {  //read data from file object and put it into string.

           // cout << fileString << "\n";   //print the data of the string
            newSize = fileString.length() ;
            cout << "This string is " << newSize << " bytes. \n";
        }
        //CLear file flags
        encodedFile_13.clear();
        //Combine test phase with reading from a file
    }

    //Show the difference in bytes
    cout << "The Compression ratio of the original fie size and the size of the compressed file is " << (newSize / origSize) << "%" << endl;

    //Now decode and print
    decodedString = decodeString(minHeap.top(), encodedString);
    cout << "\nDecoded String:\n" << decodedString << endl;

    cout << "\nNext File\n\n";
    newSize = 0;
    origSize = 0;
    clearQue(inputString.length());
    //File14/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    fstream originalFile_14, encodedFile_14;
    //needed this to create the original file
    cout << "This is the original String\n";
    originalFile_14.open("original_14.txt", ios::out);  // open a file to perform write operation using file object
    if (originalFile.is_open())     //checking whether the file is open
    {
        originalFile_14 << "Nevermind I will find someone like you" << endl;; //inserting text
        originalFile_14.close(); //close the file object
    }

    originalFile_14.open("original_14.txt", ios::in); //open a file to perform read operation using file object
    if (originalFile_14.is_open()) {   //checking whether the file is open
        string fileString;
        string inputString;
        while (getline(originalFile_14, fileString)) {  //read data from file object and put it into string.
            cout << fileString << "\n";   //print the data of the string
            g = fileString;
            origSize = fileString.length();
            cout << "This string is " << origSize << " bytes. \n";
        }
        //Combine test phase with reading from a file
   //CLear file flags
        originalFile_14.clear();
    }


    inputString = g;


    //m.clear();
  //  map<char, int >::iterator itr;


    displayFrequency(inputString);


    encodedString = encodeHuffman(inputString);
    //Prints the Binary
   //cout << "\nEncoded String:\n" << encodedString << endl;

    while (sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

    //std::cout << output;
    cout << "\nEncoded String:\n" << output << endl;

    g = output;
    // g = encodedString;

    //Create a new file for encoded text
    encodedFile_14.open("encoded_14.txt", ios::out);  // open a file to perform write operation using file object
    if (encodedFile_14.is_open())     //checking whether the file is open
    {
        string fileString;
        fileString = g;
        encodedFile_14 << fileString << "\n"; //inserting text
        encodedFile_14.close(); //close the file object
    }
    encodedFile_14.open("encoded_14.txt", ios::in); //open a file to perform read operation using file object
    if (encodedFile_14.is_open()) {   //checking whether the file is open
        string fileString;
        string encodedString;
        while (getline(encodedFile_14, fileString)) {  //read data from file object and put it into string.

           // cout << fileString << "\n";   //print the data of the string
            newSize = fileString.length() ;
            cout << "This string is " << newSize << " bytes. \n";
        }
        //CLear file flags
        encodedFile_14.clear();
        //Combine test phase with reading from a file
    }

    //Show the difference in bytes
    cout << "The Compression ratio of the original fie size and the size of the compressed file is " << (newSize / origSize) << "%" << endl;

    //Now decode and print
    decodedString = decodeString(minHeap.top(), encodedString);
    cout << "\nDecoded String:\n" << decodedString << endl;

    cout << "\nNext File\n\n";
    newSize = 0;
    origSize = 0;
    clearQue(inputString.length());
    //File15/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    fstream originalFile_15, encodedFile_15;
    //needed this to create the original file
    cout << "This is the original String\n";
    originalFile_15.open("original_15.txt", ios::out);  // open a file to perform write operation using file object
    if (originalFile.is_open())     //checking whether the file is open
    {
        originalFile_15 << "Ninetyfive percent of the ocean is unexplored" << endl;; //inserting text
        originalFile_15.close(); //close the file object
    }

    originalFile_15.open("original_15.txt", ios::in); //open a file to perform read operation using file object
    if (originalFile_15.is_open()) {   //checking whether the file is open
        string fileString;
        string inputString;
        while (getline(originalFile_15, fileString)) {  //read data from file object and put it into string.
            cout << fileString << "\n";   //print the data of the string
            g = fileString;
            origSize = fileString.length();
            cout << "This string is " << origSize << " bytes. \n";
        }
        //Combine test phase with reading from a file
   //CLear file flags
        originalFile_15.clear();
    }


    inputString = g;


    //m.clear();
  //  map<char, int >::iterator itr;


    displayFrequency(inputString);


    encodedString = encodeHuffman(inputString);
    //Prints the Binary
   //cout << "\nEncoded String:\n" << encodedString << endl;

    while (sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

    //std::cout << output;
    cout << "\nEncoded String:\n" << output << endl;

    g = output;
    // g = encodedString;

    //Create a new file for encoded text
    encodedFile_15.open("encoded_15.txt", ios::out);  // open a file to perform write operation using file object
    if (encodedFile_15.is_open())     //checking whether the file is open
    {
        string fileString;
        fileString = g;
        encodedFile_15 << fileString << "\n"; //inserting text
        encodedFile_15.close(); //close the file object
    }
    encodedFile_15.open("encoded_15.txt", ios::in); //open a file to perform read operation using file object
    if (encodedFile_15.is_open()) {   //checking whether the file is open
        string fileString;
        string encodedString;
        while (getline(encodedFile_15, fileString)) {  //read data from file object and put it into string.

           // cout << fileString << "\n";   //print the data of the string
            newSize = fileString.length() ;
            cout << "This string is " << newSize << " bytes. \n";
        }
        //CLear file flags
        encodedFile_15.clear();
        //Combine test phase with reading from a file
    }

    //Show the difference in bytes
    cout << "The Compression ratio of the original fie size and the size of the compressed file is " << (newSize / origSize) << "%" << endl;

    //Now decode and print
    decodedString = decodeString(minHeap.top(), encodedString);
    cout << "\nDecoded String:\n" << decodedString << endl;

    cout << "\nNext File\n\n";
    newSize = 0;
    origSize = 0;
    clearQue(inputString.length());
    //File16/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    fstream originalFile_16, encodedFile_16;
    //needed this to create the original file
    cout << "This is the original String\n";
    originalFile_16.open("original_16.txt", ios::out);  // open a file to perform write operation using file object
    if (originalFile.is_open())     //checking whether the file is open
    {
        originalFile_16 << "When will we travel at lightspeed to mars and back to earth" << endl;; //inserting text
        originalFile_16.close(); //close the file object
    }

    originalFile_16.open("original_16.txt", ios::in); //open a file to perform read operation using file object
    if (originalFile_16.is_open()) {   //checking whether the file is open
        string fileString;
        string inputString;
        while (getline(originalFile_16, fileString)) {  //read data from file object and put it into string.
            cout << fileString << "\n";   //print the data of the string
            g = fileString;
            origSize = fileString.length();
            cout << "This string is " << origSize << " bytes. \n";
        }
        //Combine test phase with reading from a file
   //CLear file flags
        originalFile_16.clear();
    }


    inputString = g;


    //m.clear();
  //  map<char, int >::iterator itr;


    displayFrequency(inputString);


    encodedString = encodeHuffman(inputString);
    //Prints the Binary
     //cout << "\nEncoded String:\n" << encodedString << endl;

    while (sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

    //std::cout << output;
    cout << "\nEncoded String:\n" << output << endl;

    g = output;
    // g = encodedString;

    //Create a new file for encoded text
    encodedFile_16.open("encoded_16.txt", ios::out);  // open a file to perform write operation using file object
    if (encodedFile_16.is_open())     //checking whether the file is open
    {
        string fileString;
        fileString = g;
        encodedFile_16 << fileString << "\n"; //inserting text
        encodedFile_16.close(); //close the file object
    }
    encodedFile_16.open("encoded_16.txt", ios::in); //open a file to perform read operation using file object
    if (encodedFile_16.is_open()) {   //checking whether the file is open
        string fileString;
        string encodedString;
        while (getline(encodedFile_16, fileString)) {  //read data from file object and put it into string.

           // cout << fileString << "\n";   //print the data of the string
            newSize = fileString.length() ;
            cout << "This string is " << newSize << " bytes. \n";
        }
        //CLear file flags
        encodedFile_16.clear();
        //Combine test phase with reading from a file
    }

    //Show the difference in bytes
    cout << "The Compression ratio of the original fie size and the size of the compressed file is " << (newSize / origSize) << "%" << endl;

    //Now decode and print
    decodedString = decodeString(minHeap.top(), encodedString);
    cout << "\nDecoded String:\n" << decodedString << endl;

    cout << "\nNext File\n\n";
    newSize = 0;
    origSize = 0;
    clearQue(inputString.length());
    //File17/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    fstream originalFile_17, encodedFile_17;
    //needed this to create the original file
    cout << "This is the original String\n";
    originalFile_17.open("original_17.txt", ios::out);  // open a file to perform write operation using file object
    if (originalFile.is_open())     //checking whether the file is open
    {
        originalFile_17 << "This is going to cut it close my friend" << endl;; //inserting text
        originalFile_17.close(); //close the file object
    }

    originalFile_17.open("original_17.txt", ios::in); //open a file to perform read operation using file object
    if (originalFile_17.is_open()) {   //checking whether the file is open
        string fileString;
        string inputString;
        while (getline(originalFile_17, fileString)) {  //read data from file object and put it into string.
            cout << fileString << "\n";   //print the data of the string
            g = fileString;
            origSize = fileString.length();
            cout << "This string is " << origSize << " bytes. \n";
        }
        //Combine test phase with reading from a file
   //CLear file flags
        originalFile_17.clear();
    }


    inputString = g;


    //m.clear();
  //  map<char, int >::iterator itr;


    displayFrequency(inputString);


    encodedString = encodeHuffman(inputString);
    //Prints the Binary
     //cout << "\nEncoded String:\n" << encodedString << endl;

    while (sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

    //std::cout << output;
    cout << "\nEncoded String:\n" << output << endl;

    g = output;
    // g = encodedString;

    //Create a new file for encoded text
    encodedFile_17.open("encoded_17.txt", ios::out);  // open a file to perform write operation using file object
    if (encodedFile_17.is_open())     //checking whether the file is open
    {
        string fileString;
        fileString = g;
        encodedFile_17 << fileString << "\n"; //inserting text
        encodedFile_17.close(); //close the file object
    }
    encodedFile_17.open("encoded_17.txt", ios::in); //open a file to perform read operation using file object
    if (encodedFile_17.is_open()) {   //checking whether the file is open
        string fileString;
        string encodedString;
        while (getline(encodedFile_17, fileString)) {  //read data from file object and put it into string.

           // cout << fileString << "\n";   //print the data of the string
            newSize = fileString.length() ;
            cout << "This string is " << newSize << " bytes. \n";
        }
        //CLear file flags
        encodedFile_17.clear();
        //Combine test phase with reading from a file
    }

    //Show the difference in bytes
    cout << "The Compression ratio of the original fie size and the size of the compressed file is " << (newSize / origSize) << "%" << endl;

    //Now decode and print
    decodedString = decodeString(minHeap.top(), encodedString);
    cout << "\nDecoded String:\n" << decodedString << endl;

    cout << "\nNext File\n\n";
    newSize = 0;
    origSize = 0;
    clearQue(inputString.length());
    //File18/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    fstream originalFile_18, encodedFile_18;
    //needed this to create the original file
    cout << "This is the original String\n";
    originalFile_18.open("original_18.txt", ios::out);  // open a file to perform write operation using file object
    if (originalFile.is_open())     //checking whether the file is open
    {
        originalFile_18 << "Where is rachael because batman needs to know" << endl;; //inserting text
        originalFile_18.close(); //close the file object
    }

    originalFile_18.open("original_18.txt", ios::in); //open a file to perform read operation using file object
    if (originalFile_18.is_open()) {   //checking whether the file is open
        string fileString;
        string inputString;
        while (getline(originalFile_18, fileString)) {  //read data from file object and put it into string.
            cout << fileString << "\n";   //print the data of the string
            g = fileString;
            origSize = fileString.length();
            cout << "This string is " << origSize << " bytes. \n";
        }
        //Combine test phase with reading from a file
   //CLear file flags
        originalFile_18.clear();
    }


    inputString = g;


    //m.clear();
  //  map<char, int >::iterator itr;


    displayFrequency(inputString);


    encodedString = encodeHuffman(inputString);
    //Prints the Binary
   //cout << "\nEncoded String:\n" << encodedString << endl;

    while (sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

    //std::cout << output;
    cout << "\nEncoded String:\n" << output << endl;

    g = output;
    // g = encodedString;

    //Create a new file for encoded text
    encodedFile_18.open("encoded_18.txt", ios::out);  // open a file to perform write operation using file object
    if (encodedFile_18.is_open())     //checking whether the file is open
    {
        string fileString;
        fileString = g;
        encodedFile_18 << fileString << "\n"; //inserting text
        encodedFile_18.close(); //close the file object
    }
    encodedFile_18.open("encoded_18.txt", ios::in); //open a file to perform read operation using file object
    if (encodedFile_18.is_open()) {   //checking whether the file is open
        string fileString;
        string encodedString;
        while (getline(encodedFile_18, fileString)) {  //read data from file object and put it into string.

           // cout << fileString << "\n";   //print the data of the string
            newSize = fileString.length() ;
            cout << "This string is " << newSize << " bytes. \n";
        }
        //CLear file flags
        encodedFile_18.clear();
        //Combine test phase with reading from a file
    }

    //Show the difference in bytes
    cout << "The Compression ratio of the original fie size and the size of the compressed file is " << (newSize / origSize) << "%" << endl;

    //Now decode and print
    decodedString = decodeString(minHeap.top(), encodedString);
    cout << "\nDecoded String:\n" << decodedString << endl;

    cout << "\nNext File\n\n";
    newSize = 0;
    origSize = 0;
    clearQue(inputString.length());
    //File19/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    fstream originalFile_19, encodedFile_19;
    //needed this to create the original file
    cout << "This is the original String\n";
    originalFile_19.open("original_19.txt", ios::out);  // open a file to perform write operation using file object
    if (originalFile.is_open())     //checking whether the file is open
    {
        originalFile_19 << "Space the final frontier these are the voyages of the starship enterprise" << endl;; //inserting text
        originalFile_19.close(); //close the file object
    }

    originalFile_19.open("original_19.txt", ios::in); //open a file to perform read operation using file object
    if (originalFile_19.is_open()) {   //checking whether the file is open
        string fileString;
        string inputString;
        while (getline(originalFile_19, fileString)) {  //read data from file object and put it into string.
            cout << fileString << "\n";   //print the data of the string
            g = fileString;
            origSize = fileString.length();
            cout << "This string is " << origSize << " bytes. \n";
        }
        //Combine test phase with reading from a file
   //CLear file flags
        originalFile_19.clear();
    }


    inputString = g;


  
  //  map<char, int >::iterator itr;


    displayFrequency(inputString);


    encodedString = encodeHuffman(inputString);
    //Prints the Binary
    //cout << "\nEncoded String:\n" << encodedString << endl;

    while (sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

    //std::cout << output;
    cout << "\nEncoded String:\n" << output << endl;

    g = output;
    // g = encodedString;

    //Create a new file for encoded text
    encodedFile_19.open("encoded_19.txt", ios::out);  // open a file to perform write operation using file object
    if (encodedFile_19.is_open())     //checking whether the file is open
    {
        string fileString;
        fileString = g;
        encodedFile_19 << fileString << "\n"; //inserting text
        encodedFile_19.close(); //close the file object
    }
    encodedFile_19.open("encoded_19.txt", ios::in); //open a file to perform read operation using file object
    if (encodedFile_19.is_open()) {   //checking whether the file is open
        string fileString;
        string encodedString;
        while (getline(encodedFile_19, fileString)) {  //read data from file object and put it into string.

           // cout << fileString << "\n";   //print the data of the string
            newSize = fileString.length() ;
            cout << "This string is " << newSize << " bytes. \n";
        }
        //CLear file flags
        encodedFile_19.clear();
        //Combine test phase with reading from a file
    }

    //Show the difference in bytes
    cout << "The Compression ratio of the original fie size and the size of the compressed file is " << (newSize / origSize) << "%" << endl;

    //Now decode and print
    decodedString = decodeString(minHeap.top(), encodedString);
    cout << "\nDecoded String:\n" << decodedString << endl;

    cout << "\nNext File\n\n";
    newSize = 0;
    origSize = 0;


    clearQue(inputString.length());
   
        
    //File20/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    fstream originalFile_20, encodedFile_20;
    //needed this to create the original file
    cout << "This is the original String\n";
    originalFile_20.open("original_20.txt", ios::out);  // open a file to perform write operation using file object
    if (originalFile.is_open())     //checking whether the file is open
    {
        originalFile_20 << "The unanimous Declaration of the thirteen united States of America, When in the Course of human events, it becomes necessary for one people to dissolve the political bands which have connected them with another, and to assume among the powers of the earth, the separate and equal station to which the Laws of Nature and of Nature's God entitle them, a decent respect to the opinions of mankind requires that they should declare the causes which impel them to the separation. We hold these truths to be self - evident, that all men are created equal, that they are endowed by their Creator with certain unalienable Rights, that among these are Life, Libertyand the pursuit of Happiness.--That to secure these rights, Governments are instituted among Men, deriving their just powers from the consent of the governed, --That whenever any Form of Government becomes destructive of these ends, it is the Right of the People to alter or to abolish it, and to institute new Government, laying its foundation on such principlesand organizing its powers in such form, as to them shall seem most likely to effect their Safetyand Happiness.Prudence, indeed, will dictate that Governments long established should not be changed for lightand transient causes;and accordingly all experience hath shewn, that mankind are more disposed to suffer, while evils are sufferable, than to right themselves by abolishing the forms to which they are accustomed.But when a long train of abusesand usurpations, pursuing invariably the same Object evinces a design to reduce them under absolute Despotism, it is their right, it is their duty, to throw off such Government, and to provide new Guards for their future security.--Such has been the patient sufferance of these Colonies;and such is now the necessity which constrains them to alter their former Systems of Government.The history of the present King of Great Britain is a history of repeated injuriesand usurpations, all having in direct object the establishment of an absolute Tyranny over these States.To prove this, let Facts be submitted to a candid world." << endl;; //inserting text
        originalFile_20.close(); //close the file object
    }

    originalFile_20.open("original_20.txt", ios::in); //open a file to perform read operation using file object
    if (originalFile_20.is_open()) {   //checking whether the file is open
        string fileString;
        string inputString;
        while (getline(originalFile_20, fileString)) {  //read data from file object and put it into string.
            cout << fileString << "\n";   //print the data of the string
            g = fileString;
            origSize = fileString.length();
            cout << "This string is " << origSize << " bytes. \n";
        }
        //Combine test phase with reading from a file
   //CLear file flags
        originalFile_20.clear();
    }


    inputString = g;


    //m.clear();
  //  map<char, int >::iterator itr;


    displayFrequency(inputString);


    encodedString = encodeHuffman(inputString);
    //Prints the Binary
    cout << "\nEncoded String:\n" << encodedString << endl;
    output.clear();
    stringstream sztream(encodedString);
    while (sztream.good())
    {
        std::bitset<8> bits;
        sztream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

    //std::cout << output;
    cout << "\nEncoded String:\n" << output << endl;

    g = output;
    // g = encodedString;

    //Create a new file for encoded text
    encodedFile_20.open("encoded_20.txt", ios::out);  // open a file to perform write operation using file object
    if (encodedFile_20.is_open())     //checking whether the file is open
    {
        string fileString;
        fileString = g;
        encodedFile_20 << fileString << "\n"; //inserting text
        encodedFile_20.close(); //close the file object
    }
    encodedFile_20.open("encoded_20.txt", ios::in); //open a file to perform read operation using file object
    if (encodedFile_20.is_open()) {   //checking whether the file is open
        string fileString;
        string encodedString;
        while (getline(encodedFile_20, fileString)) {  //read data from file object and put it into string.

           // cout << fileString << "\n";   //print the data of the string
            newSize = fileString.length() ;
            cout << "This string is " << newSize << " bytes. \n";
        }
        //CLear file flags
        encodedFile_20.clear();
        //Combine test phase with reading from a file
    }

    //Show the difference in bytes
    cout << "The Compression ratio of the original fie size and the size of the compressed file is " << (newSize / origSize) << "%" << endl;

    //Now decode and print
    decodedString = decodeString(minHeap.top(), encodedString);
    cout << "\nDecoded String:\n" << decodedString << endl;

    clearQue(inputString.length());

    return 0;
}
