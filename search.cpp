#include "search.h"

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

search::search(vector<string> l, string s)
{
    this->l = l;
    this->s = s;
}

vector<string> search::simpleSearch()
{
    // resluting list with all matching strings
    vector<string> res = {};

    // put every character in s to lowercase, store it in s2
    string s2 = this->s;
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

    // for range to test every element st of the list
    for(const string& st : this->l) {
        // put every character in st to lowercase, store it in st2
        string st2 = st;
        transform(st2.begin(), st2.end(), st2.begin(), ::tolower);

        // append it to res if lowercase strings are the same
        if (s2.compare(st2)) res.push_back(st);
    }

    return res;
}

vector<string> search::prefixSearch()
{
    // resluting list with all matching strings
    vector<string> res = {};

    // put every character in s to lowercase, store it in s2
    string s2 = this->s;
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

    // for range to test every element st of the list
    for(const string& st : this->l) {
        // put every character in st to lowercase, store it in st2
        string st2 = st;
        transform(st2.begin(), st2.end(), st2.begin(), ::tolower);

        // append it to res if lowercase strings are the same
        if (s2.compare(0,s2.size(),st2)) res.push_back(st);
    }

    return res;
}
