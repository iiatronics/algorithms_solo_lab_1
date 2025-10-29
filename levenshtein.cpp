#include "header.h"

// int put_in_matrix(int l1, int l2, int dif)
// {

// }
int equal(char a, char b)
{
    if(a == b)
    {
        return 0;
    }

    return 1;
}

int size_of_str(string word)
{
    char temp;
    int i = 0;
    temp = word[i];

    while(temp != '\0')
    {
        temp = word[i];
        i++;
        //cout << i << "\n";
    }

    return (i - 1);
}

// void fill_matrix (vector<vector<char>> matrix, string word1, string word2)
// {
//     for (int i = 3;)
// }

int levenshtein_index(string word1, string word2)
{
    int index = 0, word1_lenght = 0, word2_lenght = 0;

    //cout << word1 << "  " << word2 << " nice \n";

    word1_lenght = size_of_str(word1);
    word2_lenght = size_of_str(word2);
    cout << word1_lenght << "  " << word2_lenght << "\n";
    // char** array = new char*[word1_lenght];

    // for (int i = 0; i < word2_lenght; i++)
    // {

    // }

    vector<vector<char>> matrix;

    for (int i = 0; i <= word1_lenght; i++)
    {
        for (int j = 0; j <= word2_lenght; j++)
        {
            matrix[0][i] = i;
            matrix[j][0] = j;
        }
    }

    for (int i = 1; i <= word1_lenght; i++)
    {
        for (int j = 1; j <= word2_lenght; j++)
        {
            //matrix[i][j] = put_in_matrix(matrix)
            matrix[i][j] = min({(matrix[i][j - 1] + 1), (matrix[i - 1][j] + 1), matrix[i - 1][j - 1] + equal(word1[i], word2[j])});
            index = matrix[i][j];
            cout << "index: " << index << "\n";
        }
    }

    return index;
}

void levenshtein_realisation(string word1, string word2)
{
    int index = 0;

    //cout << word1 << "  " << word2 << "\n";
    index = levenshtein_index(word1, word2);
    cout << "index: " << index << "\n";

    return;
}