#include "Dictionary.h"

Dictionary::Node::Node() {
    isWord = false;
    for (int i = 0; i < NUM_CHARS; i++) {
        next[i] = nullptr;
    }
}

Dictionary::Dictionary() {
    root = new Node;
    numWords = 0;
}

Dictionary::~Dictionary() {
}

Dictionary::Dictionary(string filename) {
    root = new Node;
    numWords = 0;
    LoadDictionaryFile(filename);
}

void Dictionary::LoadDictionaryFile(string filename) {
    string word;
    ifstream infile;
    infile.open(filename);
    if (!infile.is_open()) {
        cout << "Could not open file" << endl;
        return;
    }
    while (!infile.eof()) {
        //add all words from file into dictionary
        infile >> word;
        AddWord(word);
    }
    infile.close();
}

void Dictionary::AddWord(string word) {
    Node *currNode = root;
    //search through each character
    for (int i = 0; i < word.size(); i++) {
        int charIndex = int(word[i]) - int('a'); //the index for the char in the string word
        if (currNode->next[charIndex] == nullptr) {
            //set branch of character to new Node
            Node *newNode = new Node;           //make new path
            currNode->next[charIndex] = newNode;
        }
        currNode = currNode->next[int(charIndex)];
    }
    currNode->isWord = true; //end of word is reached so this is now valid word
    numWords++;
}

bool Dictionary::IsWord(string word) {
    Node *currNode = root;
    //search through each character
    for (int i = 0; i < word.size(); i++) {
        int charIndex = int(word[i]) - int('a'); //the index for the char in the string word
        if (charIndex < 0 || charIndex > 25) {   //make sure that the character is valid
            throw (DictionaryError("Invalid character"));
        }
        if (currNode->next[charIndex] == nullptr) { //return false if path does not exist
            return false;
        }
        currNode = currNode->next[int(charIndex)];
    }
    if (currNode->isWord == true) {
        return true; //return true if valid word
    }

    return false; //return false if invalid word

}

bool Dictionary::IsPrefix(string word) {
    Node *currNode = root;
    //search through each character
    for (int i = 0; i < word.size(); i++) {
        int charIndex = int(word[i]) - int('a'); //the index for the char in the string word
        if (charIndex < 0 || charIndex > 25) {   //make sure that the character is valid
            throw (DictionaryError("Invalid character"));
        }
        if (currNode->next[charIndex] == nullptr) {
            return false;
        }
        currNode = currNode->next[int(charIndex)];

    }
    return true; //return true if valid prefix
}

int Dictionary::WordCount() {
    return numWords;
}

void Dictionary::MakeEmpty() {
    destroyHelper(root);
    root = new Node;
    numWords = 0;
}

void Dictionary::destroyHelper(Dictionary::Node *thisTree) {
    if (thisTree == nullptr) {  //base case
        return;
    }
    for (int i = 0; i < NUM_CHARS; i++) { //traverse tree
        destroyHelper(thisTree->next[i]);
    }
    delete thisTree;        //delete nodes
}

Dictionary &Dictionary::operator=(const Dictionary &otherDict) {
    this->MakeEmpty();  //make empty clears a tree and resets root
    numWords = otherDict.numWords;
    for (int i = 0; i < NUM_CHARS; i++) { //traverse for root since one already exists
        copyHelper(root->next[i], otherDict.root->next[i]);
    }
    return *this;
}

void Dictionary::copyHelper(Dictionary::Node *&thisTree, Dictionary::Node *&otherTree) {
    if (otherTree == nullptr) {  //base case
        thisTree = nullptr;
        return;
    }
    thisTree = new Node;    //add data to new nodes
    thisTree->isWord = otherTree->isWord;
    for (int i = 0; i < NUM_CHARS; i++) { //traverse all nodes
        copyHelper(thisTree->next[i], otherTree->next[i]);
    }
}

void Dictionary::SaveDictionaryFile(string filename) {
    ofstream outfile;
    outfile.open(filename);
    //throw error message if file could not open
    if (!outfile.is_open()) {
        string msg = filename;
        msg = msg + " failed to open";
        throw (DictionaryError(msg));
    }
    //write the words to file if open
    SaveDictionaryHelper(root, "", outfile);
    outfile.close();

}

void Dictionary::SaveDictionaryHelper(Dictionary::Node *curr, string currPrefix, ofstream &outFile) {
    if (curr == nullptr) {  //base case
        return;
    }
    if (curr->isWord) {
        outFile << currPrefix << endl;  //write data
    }
    for (int i = 0; i < NUM_CHARS; i++) {
        //call for every element of array and update prefix with the current character
        SaveDictionaryHelper(curr->next[i], currPrefix + (char) (i + (int) 'a'), outFile);
    }
}


Dictionary::Dictionary(const Dictionary &otherDict) {
    root = new Node;
    numWords = 0;
    *this = otherDict;
}


