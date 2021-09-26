#ifndef BOGGLE_DICTIONARY_H
#define BOGGLE_DICTIONARY_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


const int NUM_CHARS = 26;

class DictionaryError{
public:
    explicit DictionaryError(string msg) {
        this->msg = msg;
    }
    string Msg(){
        return msg;
    }
private:
    string msg;
};

class Dictionary
{

public:
    Dictionary(); //Constructor
    ~Dictionary();
    Dictionary(const Dictionary& otherDict);
    // Copy constructor.
    //Pre: Dictionary must be initialized.
    //Post: Copies all values from one Dictionary into another.

    explicit Dictionary(string filename);
    //Pre: filename must be valid for reading.
    //Post: Adds words to Dictionary object from file after establishing root node.


    Dictionary& operator=(const Dictionary& otherDict);
    //Function: Overloading operator for copying one dictionary to another.
    //          Wrapper for copyHelper function.
    //Pre:      Dictionary must be initialized
    //Post:     Copies all values from one Dictionary into another.

    void LoadDictionaryFile(string filename);
    //Function: Adds all words from file into Dictionary object.
    //Pre:      File name must be valid, Dictionary object must be initialized.
    //Post:     Dictionary object contains valid paths that correspond to words from file.

    void SaveDictionaryFile(string filename);
    //Function: Finds every word in a tree, and saves it to a file.
    //          Wrapper for SaveDictionaryHelper function.
    //Pre:      File name must be valid. Dictionary must be initialized.
    //Post:     File contains valid words that were found in the tree


    void AddWord(string word);
    //Function: Adds a word to the tree.
    //Pre:      Dictionary must be initialized.
    //Post:     Path containing all characters is created.
    //          IsWord for last character is set to true, numWords incremented.

    void MakeEmpty();
    //Function: Destroys all nodes in the tree and remakes root.
    //          Wrapper for destroyHelper function.
    //Pre:      Dictionary must be initialized
    //Post:     All nodes are deleted, numWords is 0, root is remade.


    bool IsWord(string word);
    //Function: Determines if a word given is a valid word in the tree.
    //Pre:      Dictionary must be initialized.
    //          Characters in word must be valid.
    //Post:     Returns false if the word is not a valid word, true if it is a valid word.

    bool IsPrefix(string word);
    //Function: Determines if a word given is a prefix in the tree.
    //Pre:      Dictionary must be initialized.
    //          Characters in word must be valid.
    //Post:     Returns false if the word is not a valid prefix, true if it is a valid prefix.

    int WordCount();
    //Function: Determines the number of words in a tree.
    //Pre:      Dictionary must be initialized.
    //Post:     Returns the number of words.

private:

    class Node {
    public:
        bool isWord;
        Node* next[NUM_CHARS];
        Node(); //Node constructor
    };

    Node* root;
    int numWords;


    void destroyHelper(Node* thisTree);
    //Function: Destroys all nodes in the tree.
    //          Helper for MakeEmpty function.
    //Pre:      Dictionary must be initialized.
    //Post:     All nodes are deleted.

    void copyHelper(Node*& thisTree, Node*& otherTree);
    //Function: Copies all values from one Dictionary into another.
    //Pre:      Dictionary must be initialized.
    //          Helper for copy constructor and, = operator.
    //Post:     Creates a new tree and copies an existing tree into it.

    void SaveDictionaryHelper(Node* curr, string currPrefix, ofstream& outFile);
    //Function: Finds every word in a tree, and saves it to a file.
    //          Helper for SaveDictionaryFile function.
    //Pre:      File name must be valid. Dictionary must be initialized.
    //Post:     File contains valid words that were found in the tree.

};

#endif //BOGGLE_DICTIONARY_H
