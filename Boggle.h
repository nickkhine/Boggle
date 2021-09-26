#ifndef BOGGLE_BOGGLE_H
#define BOGGLE_BOGGLE_H

#include <string>
#include "Dictionary.h"

using namespace std;

const int BOARD_SIZE = 4;



class Boggle {
public:
    Boggle(); //Constructor
    explicit Boggle(string filename);
    //Constructor given file name
    //Pre:      filename must be valid, Dictionary object must be initialized
    //Post:     visited initialized to false and board initialized to ""
    //          Dictionary object is loaded with words from file

    void SetBoard(string board[BOARD_SIZE][BOARD_SIZE]);
    //Function: Copies board to this->board
    //Pre:      Boggle object must be initialized
    //Post:     instance of boggle object contains the board of given board array

    void SolveBoard(bool printBoard, ostream& output);
    //Function: Finds all the words stored by board and saves them
    //          wrapper for SolveBoardHelper
    //Pre:      Boggle object must be initialized
    //Post:     Words that were found are stored in the wordsFound dictionary
    //          output of words is written with or without sequence
    //          empties wordsFound

    void SaveSolve(string filename);
    //Function: Saves all the words from the last solve
    //Pre:      Boggle object must be initialized
    //Post:     Filename provided contains all the words that were found


    Dictionary GetDictionary();
    //Function: returns the dict Dictionary
    //Pre:      Boggle object must be initialized
    //Post:     dict is returned

    Dictionary WordsFound();
    //Function: returns the wordsFound dictionary
    //Pre:      Boggle object must be initialized
    //Post:     wordsFound is returned

private:
    Dictionary dict;
    Dictionary wordsFound;
    string board[BOARD_SIZE][BOARD_SIZE];
    int visited[BOARD_SIZE][BOARD_SIZE];

    void PrintBoard(ostream& output);
    //Function: Prints the path for the solution
    //Pre:      Boggle object must be initialized
    //Post:     outputs the path solution was found and the word
    //          found in single quotes on the board display

    void SolveBoardHelper(int row, int col, string prefix,ostream &output,bool printBoard,int count);
    //Function: Finds all the words on the current board and saves them
    //          helper for SolveBoard
    //Pre:      Boggle object must be initialized
    //Post:     Words that were found are stored in the wordsFound dictionary
    //          output of words is written with or without sequence
};

#endif //BOGGLE_BOGGLE_H
