
#include <iostream>
#include <fstream>
#include <string>
#include<string.h>

using namespace std;

int main()
{
      string line;
      ifstream file ("project_c++.csv");
      int n;
      cout << "Type the number of cells: ";
      cin >> n;
      double* matrix[n];
      int i = 0;

      if (file.is_open()){
          while (!file.eof()){
              // while still have line in the file
              getline(file,line);
              //line = current line
              string temp = "";
              int count = 0;
              if (count == 0){
                  for (int i=0; i<=line.length(); i++){
                      if (line[i]==',' or i==(line.length())){
                          count += 1;
                      }
                  }
              }
              //see how many cells there are
              double temporary[count]; //create array with spaces for the number of cells we found
              int temp_num = 0;
              for (int i=0; i<=line.length(); i++){ //for each character in the line
                  if (line[i]==',' or i==(line.length())){ //if the character is , or ends then it means it is a different value or it stops
                      temporary[temp_num] = stoi(temp); //add the corresponding value to the array
                      temp = "";
                      temp_num += 1;
                  }
                  else{
                      temp += line[i]; // add the character to temp
                  }
              }
              //now we have an array with the values of the first line called temporary
              matrix[i] = temporary; //we add each line to the matrix
              i += 1;
          }
      }

    return 0;
}


