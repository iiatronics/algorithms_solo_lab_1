#include "header.h"

int trio_min(int a, int b, int c)
{
    if(a <= b && a <= c)
    {
        return a;
    }
    else if(b <= a && b <= c)
    {
        return b;
    }
    else
    {
        return c;
    }
}

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

    vector<vector<int>> matrix(word1_lenght+1, vector<int> (word2_lenght+1));

    for (int j = 0; j <= word1_lenght; j++)
    {
        matrix[j][0] = j;
    }  

    for (int i = 0; i <= word2_lenght; i++)
    {
        matrix[0][i] = i;
    }

    int temp = 0, a = 0, b = 0, c = 0;
    for (int j = 1; j <= word2_lenght; j++)
    {
        for (int i = 1; i <= word1_lenght; i++)
        {
            //matrix[i][j] = put_in_matrix(matrix)
            //matrix[i][j] = min({((int)(matrix[i][j - 1]) + 1), ((int)(matrix[i - 1][j]) + 1), ((int)(matrix[i - 1][j - 1]) + (int)equal(word2[i - 1], word1[j - 1]))});
            // temp = (matrix[i - 1][j - 1]) + equal(word2[i - 1], word1[j - 1]);
            // matrix[i][j] = trio_min(((int)(matrix[i][j - 1]) + 1), ((int)matrix[i - 1][j] + 1), temp);
            // cout << "min of : " << (int)(matrix[i][j - 1]) + 1 << " : " << (int)(matrix[i - 1][j]) + 1 << " : " << (int)(matrix[i - 1][j - 1]) << " + " << equal(word1[i - 1], word2[j - 1]) << endl;
            // index = matrix[i][j];
            // cout << "index (" << i << "; " << j << ") :" << index << "\n";

            a = (int)matrix[i][j - 1] + 1;
            //a = a + 1;
            b = (int)matrix[i - 1][j] + 1;
            //b = b + 1;
            c = (int)matrix[i - 1][j - 1] + equal(word1[i - 1], word2[j - 1]);

            cout << "min of : "<< a <<" | "<<b<< " | " << c << " | word1[i]: "<< word1[i - 1] << " | word2[j]: "<< word2[j - 1]  << endl;
            index = trio_min(a, b, c);
            cout << "index (" << i << "; " << j << ") :" << index << "\n";
            matrix[i][j] = index;
        }
    }

    return index;
}

void levenshtein_realisation(string word1, string word2)
{
    int index = 0;

    //cout << word1 << "  " << word2 << "\n";
    index = levenshtein_index(word1, word2);
    cout << "final index: " << index << "\n";

    return;
}