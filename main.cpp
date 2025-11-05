#include "header.h"
using namespace std;

int main()
{
    int option = 0;

    string word1, word2;

    do
    {
        cout << "\n===== MENU =====\n";
        cout << "1. Levenshtein distance start\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> option;

        switch (option)
        {
        case 1:
            cout << "Enter word 1:\n";
            cin >> word1;

            cout << "Enter word 2:\n";
            cin >> word2;

            levenshtein_realisation(word1, word2);

            break;
        case 0:
            cout <<"Exit\n";
            break;
        default:
            cout <<"Wrong option\n";
            break;
        }
    } while (option != 0);
    
    return 0;
}