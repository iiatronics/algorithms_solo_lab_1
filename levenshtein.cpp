#include "header.h"

void show_step_by_step(string word1, const string& word2, const vector<Op>& ops)
{
    string cur = word1;
    if (ops.empty())
    {
        cout << "Слова однакові: " << cur << " = " << word2 << "\n";
        return;
    }

    cout << "\n=== Step by step transformation ===\n";

    int offset = 0; // зміщення індексів відносно оригіналу word1

    for (size_t k = 0; k < ops.size(); ++k)
    {
        const Op& op = ops[k];
        int adjusted_pos = op.pos + offset; // скоригована позиція у поточному слові

        cout << "Before:   " << cur << "\n";

        if (op.type == 'S')
        {
            // перевірка безпеки
            if (adjusted_pos >= 0 && adjusted_pos < (int)cur.size())
            {
                cout << "Operation: SUBSTITUTE '" << op.from << "' -> '" << op.to
                     << "' at pos " << adjusted_pos << "\n";
                cur[adjusted_pos] = op.to;
            }
            else
            {
                cout << "Operation: SUBSTITUTE (invalid pos " << adjusted_pos << ")\n";
            }
            // offset не змінюється
        }
        else if (op.type == 'D')
        {
            if (adjusted_pos >= 0 && adjusted_pos < (int)cur.size())
            {
                cout << "Operation: DELETE '" << op.from << "' at pos " << adjusted_pos << "\n";
                cur.erase(adjusted_pos, 1);
                offset -= 1; // після видалення індекси зсуваються вліво
            }
            else
            {
                cout << "Operation: DELETE (invalid pos " << adjusted_pos << ")\n";
            }
        }
        else if (op.type == 'I')
        {
            // вставка в позицію adjusted_pos (0..size)
            if (adjusted_pos >= 0 && adjusted_pos <= (int)cur.size())
            {
                cout << "Operation: INSERT '" << op.to << "' at pos " << adjusted_pos << "\n";
                cur.insert(adjusted_pos, 1, op.to);
                offset += 1; // після вставки індекси зсуваються вправо
            }
            else
            {
                cout << "Operation: INSERT (invalid pos " << adjusted_pos << ")\n";
            }
        }

        cout << "After:    " << cur << "\n";
        cout << "Target:   " << word2 << "\n";
        cout << "---------------------\n";
    }

    cout << "Final result: " << cur << " -> " << word2 << "\n";
}



vector<Op> backtrace_ops(const string& word1, const string& word2, const vector<vector<int>>& matrix)
{
    int i = (int)word1.size();
    int j = (int)word2.size();
    vector<Op> ops_rev; // operations in reverse order (from end to start)

    while (i > 0 || j > 0)
    {
        // match (move diag)
        if (i > 0 && j > 0 && word1[i - 1] == word2[j - 1] && matrix[i][j] == matrix[i - 1][j - 1])
        {
            // можна додавати 'M' якщо потрібно, але нам не потрібно виводити матчі
            i--; j--;
        }
        // substitution
        else if (i > 0 && j > 0 && matrix[i][j] == matrix[i - 1][j - 1] + 1)
        {
            Op op;
            op.type = 'S';
            op.pos = i - 1;
            op.from = word1[i - 1];
            op.to = word2[j - 1];
            ops_rev.push_back(op);
            i--; j--;
        }
        // deletion (remove word1[i-1])
        else if (i > 0 && matrix[i][j] == matrix[i - 1][j] + 1)
        {
            Op op;
            op.type = 'D';
            op.pos = i - 1;
            op.from = word1[i - 1];
            op.to = '\0';
            ops_rev.push_back(op);
            i--;
        }
        // insertion (insert word2[j-1] at position i)
        else if (j > 0 && matrix[i][j] == matrix[i][j - 1] + 1)
        {
            Op op;
            op.type = 'I';
            op.pos = i; // insert at i (after i-1), 0-based
            op.from = '\0';
            op.to = word2[j - 1];
            ops_rev.push_back(op);
            j--;
        }
        else
        {
            // резервний вихід (не повинно статися)
            break;
        }
    }

    // перевернемо порядок — отримаємо операції у прямому порядку
    reverse(ops_rev.begin(), ops_rev.end());
    return ops_rev;
}


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
    }

    return (i - 1);
}

int levenshtein_index(string word1, string word2)
{
    int index = 0, word1_lenght = 0, word2_lenght = 0;

    word1_lenght = size_of_str(word1);
    word2_lenght = size_of_str(word2);
    cout << word1_lenght << "  " << word2_lenght << "\n";

    vector<vector<int>> matrix(word1_lenght+1, vector<int> (word2_lenght+1));
    //vector<coordinates> reverse;

    for (int j = 0; j <= word1_lenght; j++)
    {
        matrix[j][0] = j;
    }  

    for (int i = 0; i <= word2_lenght; i++)
    {
        matrix[0][i] = i;
    }

    for (int i = 1; i <= word1_lenght; i++)
    {
        for (int j = 1; j <= word2_lenght; j++)
        {
            matrix[i][j] = trio_min(
                matrix[i - 1][j] + 1,
                matrix[i][j - 1] + 1,
                matrix[i - 1][j - 1] + equal(word1[i - 1], word2[j - 1])
            );
            cout << "index (" << i << "; " << j << ") :" << matrix[i][j] << "\n";
        }
    }

    vector<Op> ops = backtrace_ops(word1, word2, matrix);
    show_step_by_step(word1, word2, ops);

    return matrix[word1_lenght - 1][word2_lenght - 1];
}


void levenshtein_realisation(string word1, string word2)
{
    int index = 0;
    //add string transformation
    index = levenshtein_index(word1, word2);
    cout << "final index: " << index << "\n";

    

    return;
}