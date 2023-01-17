/*#include <iostream>
#include <set>
#include "intersection_sets.h"
using namespace std;


int main() {
    set<string> set1 = {"je","h", "j"};
    set<string> set2 = {"h", "k", "je"};
    Intersection_sets test;
    set<string> intersection_set;
    intersection_set = test.set_intersection(set1, set2);
    for (string x : intersection_set) {
        cout << x << " ";
    }
    return 0;
}

*/

#include "intersection_sets.h"
#include <iostream>
#include <set>

intersection_sets::intersection_sets()
{

}


std::set<std::string> intersection_sets::set_intersection(std::set<std::string> set1, std::set<std::string> set2) {
    std::set<std::string> result;
    for (std::string x : set1) {
        if (set2.count(x)) {
            result.insert(x);
        }
    }
    return result;
}

