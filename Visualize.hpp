#ifndef VISUALIZE_H
#define VISUALIZE_H
#include <iostream>

using namespace std;

class CSV{
public:
    void read_csv_file(string myFilePath);
    void visualize_csv();
};
class TXT{
public:
    void read_txt_file(string myFilePath);
    void visualize_txt();
};
#endif // VISUALIZE_H
