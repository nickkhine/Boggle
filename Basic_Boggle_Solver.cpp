
#include <iostream>
#include "Boggle.h"
#include "Dictionary.h"

using namespace std;

void GetBoard(string board[BOARD_SIZE][BOARD_SIZE]) {
    cout << "Enter Board" << endl;
    cout << "-----------" << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << "Row " << i << ": ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            cin >> board[i][j];
        }
    }
    cout << endl;
}

void HardCodedBoard(string board[BOARD_SIZE][BOARD_SIZE]) {
    board[0][0] = "a";
    board[0][1] = "b";
    board[0][2] = "c";
    board[0][3] = "d";

    board[1][0] = "x";
    board[1][1] = "y";
    board[1][2] = "z";
    board[1][3] = "a";

    board[2][0] = "l";
    board[2][1] = "m";
    board[2][2] = "n";
    board[2][3] = "o";

    board[3][0] = "q";
    board[3][1] = "t";
    board[3][2] = "v";
    board[3][3] = "g";
}

int main() {
    Boggle boggle;

    string board[BOARD_SIZE][BOARD_SIZE];

    HardCodedBoard(board);      // Provides a hard coded board
    //GetBoard(board);          // Gets a board from a user

    cout << boggle.GetDictionary().WordCount() << " words loaded." << endl << endl;

    boggle.SetBoard(board);

    string yesno;
    cout << "Show board? (y/n):  ";
    getline(cin, yesno);
    cout << endl;

    // Output to the screen.
    boggle.SolveBoard(yesno == "y", cout);

    // Output to a file.
    ofstream solveOutput;
    solveOutput.open("solve_output_basic.txt");
    boggle.SolveBoard(yesno == "y", solveOutput);
    solveOutput.close();


    boggle.WordsFound().SaveDictionaryFile("solve_dictionary.txt");

    return 0;
}