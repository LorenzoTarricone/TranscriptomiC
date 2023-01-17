#ifndef INTERSECTION_SETS_H
#define INTERSECTION_SETS_H

#include <iostream>
#include <string.h>
#include <set>

class intersection_sets
{
public:
    intersection_sets();
    std::set<std::string> set_intersection(std::set<std::string> set1, std::set<std::string> set2);
};

#endif // INTERSECTION_SETS_H
