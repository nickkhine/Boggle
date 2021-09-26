
#include <iostream>
#include "Dictionary.h"

using namespace std;

int main() {

    Dictionary dict;
    dict.LoadDictionaryFile("dictionary.txt");
    cout << dict.WordCount() << " words loaded." << endl << endl;

    string word;
    while (word != "!") {
        cout << "Enter string: ";
        cin >> word;

        try {
            if (dict.IsWord(word)) {
                cout << word << " is a valid word" << endl;
            } else {
                cout << word << " is NOT a valid word" << endl;
            }

            if (dict.IsPrefix(word)) {
                cout << word << " is a valid prefix" << endl;
            } else {
                cout << word << " is NOT a valid prefix" << endl;
            }
        }
        catch (DictionaryError error) {
            cout << "ERROR: " << error.Msg() << endl;
        }

        cout << endl;
    }

}
