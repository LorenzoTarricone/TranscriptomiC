#ifndef TEST_TXT_H
#define TEST_TXT_H


#include <string>

using namespace std;

class test_txt
{
private:
    string line;
    string value;
    double number;
public:
    test_txt();
    bool check_number(string);
    double stringTodouble(string);
    void log2_nk ();
};

#endif // TEST_TXT_H
