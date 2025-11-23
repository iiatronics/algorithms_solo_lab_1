#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>

using namespace std;

struct Op {
    char type; // 'S' substitute, 'D' delete, 'I' insert, 'M' match (не використовується в виводі)
    int pos;   // позиція в поточному слові для операції (0-based)
    char from; // символ який замінюється / видаляється (для insert пустий)
    char to;   // символ вставки або результат заміни
};


void levenshtein_realisation(string word1, string word2);
vector<Op> backtrace_ops(const string &word1, const string &word2, const vector<vector<int>> &matrix);

#endif