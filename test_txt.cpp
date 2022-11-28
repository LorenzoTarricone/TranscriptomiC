#include "test_txt.h"

#include <iostream>
#include <fstream>
#include <string>
#include<string.h>
#include <bits/stdc++.h>

using namespace std;

test_txt::test_txt()
{
}


bool test_txt::check_number(string str) {
   std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
   str.erase(end_pos, str.end());
   for (int i = 0; i < str.length(); i++)
   if (isdigit(str[i]) == false)
      return false;
      return true;
}

double test_txt::stringTodouble(string str){
    std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
    str.erase(end_pos, str.end());
    double temp = 0;
    for (int i = 0; i < str.length(); i++) {

        // Since ASCII value of character from '0'
        // to '9' are contiguous. So if we subtract
        // '0' from ASCII value of a digit, we get
        // the integer value of the digit.
        temp = temp * 10 + (str[i] - '0');
    }
    return temp;
}



void test_txt::log2_nk ()
{
  string line;
  ifstream file ("test_nk.txt");
  string value;
  double number;
  ofstream copy("test_nk_modify.txt", std::ofstream::out);

  if (file.is_open())

  {
      while (!file.eof()){
          // while still have line in the file
          getline(file,line);
          //line= current line
          value='\0'; //reset value to 0
          for (int i=0; i<=line.length(); i++){
              if (line[i]==' ' or i==(line.length())){
                  cout<<value;
                  //iterate to take the values as a block when they are not separated by spaces

                  //always print 0, why?
                  cout<<check_number(value);
                  if (check_number(value)==1){

                      // check if the string is an integer
                      cout<<value;
                      number=stringTodouble(value);
                      //convert the string value into a double
                      cout<<number;
                      number=log2(number);

                      if(i==line.length()){
                          copy <<number<< "\n";
                      }
                      else{
                          copy<<number;}
                  }
                  else{

                      if(i==line.length()){

                          copy <<value<< "\n";
                      }
                      else{
                          copy<<value;}
                  }
                  //if it is an integer, we are interested by its value
                  value='\0';
                  number=0;}

              else{
                  value+=line[i];}}}

      file.close();
      copy.close();
  }
  else cout << "Can not open the file";

}

