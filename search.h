#ifndef SEARCH_H
#define SEARCH_H
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class search
{
public:
    vector<string> l;
    string s;

    search(vector<string> l, string s);

    vector<string> simpleSearch(); // basic search : find all strings in l matching s ignoring the case

    vector<string> prefixSearch(); // prefix search : find all strings in l that have s as a prefix

    // TO DO
    vector<string> trieSearch(); // trie search : efficiently find all strings in l that have s as a prefix thanks to a trie structure

};

#endif // SEARCH_H
