
#include "Dictionary.h"
#include "Boggle.h"

Dictionary Boggle::GetDictionary() {
    return dict;
}


Dictionary Boggle::WordsFound() {
    return wordsFound;
}

Boggle::Boggle() {
    dict.LoadDictionaryFile("dictionary.txt");
    for (int r = 0; r < BOARD_SIZE; r++) {    //row of board
        for (int c = 0; c < BOARD_SIZE; c++) { //column of board
            board[r][c] = "";
            visited[r][c] = false;
        }
    }
}

Boggle::Boggle(string filename) {
    dict.LoadDictionaryFile(filename);
    for (int r = 0; r < BOARD_SIZE; r++) {    //row of board
        for (int c = 0; c < BOARD_SIZE; c++) { //column of board
            board[r][c] = "";
            visited[r][c] = false;
        }
    }
}

void Boggle::SetBoard(string board[BOARD_SIZE][BOARD_SIZE]) {
    for (int r = 0; r < BOARD_SIZE; r++) {    //row of board
        for (int c = 0; c < BOARD_SIZE; c++) { //column of board
            this->board[r][c] = board[r][c]; //copy board from left to right
        }
    }
}

void Boggle::SolveBoard(bool printBoard, ostream &output) {
    string currPrefix = "";
    int count = 1;         //used to keep track of direction for finding words
    wordsFound.MakeEmpty();

    //call solveboard for each position
    for (int row = 0; row < BOARD_SIZE; row++) {    //row of board
        for (int col = 0; col < BOARD_SIZE; col++) { //column of board
            SolveBoardHelper(row, col, currPrefix, output, printBoard, count);
        }
    }
}

void Boggle::SaveSolve(string filename) {
    wordsFound.SaveDictionaryFile(filename);
}

void Boggle::PrintBoard(ostream &output) {
    //output board with quotes
    for (int r = 0; r < BOARD_SIZE; r++) {    //row of visited
        for (int c = 0; c < BOARD_SIZE; c++) { //column of visited
            //output row of board with quotes if necessary
            if (visited[r][c] > 0) {
                //add quotes
                output << " '" << board[r][c] << "' ";
            } else {
                output << "  " << board[r][c] << "  ";
            }
        }
            output << "\t";           //output sequence words were found
            for (int i = 0; i < BOARD_SIZE; i++) {
                //output sequence
                output << "  " << visited[r][i] << "  ";
            }

        output << endl;
    }
    output << endl;
}

void Boggle::SolveBoardHelper(int row, int col, string currPrefix, ostream &output, bool printBoard, int count) {
    if (row < 0 || col < 0 || row >= BOARD_SIZE || col >= BOARD_SIZE) {
        return;                         //keep the search in bounds
    }

    if (visited[row][col] > 0) {
        return;                         //Already visited
    }

    currPrefix = currPrefix + board[row][col];  //update the prefix

    if (!dict.IsPrefix(currPrefix)) {
        return;                        //direction gives invalid prefix
    }

    visited[row][col] = count;

    if (dict.IsWord(currPrefix)) {       //check to see if the prefix is a word
        if (!wordsFound.IsWord(currPrefix)) { //make sure we havent found the word already
            wordsFound.AddWord(currPrefix); //add the word if it is valid
            if (printBoard == false) {
                output << wordsFound.WordCount() << "\t" << currPrefix << endl; //prints regularly
            } else {
                output << "Word: " << currPrefix << endl;
                output << "Number of Words: " << wordsFound.WordCount() << endl;
                PrintBoard(output); //prints sequence words were found
            }
        }

    }
    SolveBoardHelper(row - 1, col, currPrefix, output, printBoard, count + 1); // Checking north
    SolveBoardHelper(row - 1, col + 1, currPrefix, output, printBoard, count + 1); // Checking northeast
    SolveBoardHelper(row, col + 1, currPrefix, output, printBoard, count + 1); // Checking east
    SolveBoardHelper(row + 1, col + 1, currPrefix, output, printBoard, count + 1); // Checking southeast
    SolveBoardHelper(row + 1, col, currPrefix, output, printBoard, count + 1); //checking south
    SolveBoardHelper(row + 1, col - 1, currPrefix, output, printBoard, count + 1); //checking southwest
    SolveBoardHelper(row, col - 1, currPrefix, output, printBoard, count + 1); //checking west
    SolveBoardHelper(row - 1, col - 1, currPrefix, output, printBoard, count + 1); //checking northwest

    visited[row][col] = 0;
}



