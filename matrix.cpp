#include "matrix.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;


Matrix::Matrix()
{
   int** mat;
   n = 0;
   m = 0;
}
void Matrix::txt_file_to_matrix(unsigned int n, unsigned int m, string file_name){
    ifstream file;
    file.open(file_name);
    //change if name of the gene is an integer
    string str;
    for(unsigned int i = 0; i < n; i++){
        string line;
        getline(file,line);
        file >> str;
        for(unsigned int j = 0; j < m; j++){
            file >> mat[i][j];
        }
    }
    file.close();
}

void Matrix::csv_file_to_matrix(unsigned int n, unsigned int m, string file_name){
    string row,job[n+1][m+1];
    ifstream jobfile(file_name);
    std::string fileCommand;

    if(jobfile.is_open())
    {
//      cout << "Successfully open file"<<endl;

      int i = 0, j = 0;
      while(getline(jobfile,row,','))
      {
        //cout << "|" << arrival << "|" << endl;
        size_t found = row.find("\n");
        if (found != std::string::npos) // if newline was found
        {
                string lastToken = row.substr(0, found);
                string nextLineFirstTOken = row.substr(found + 1);
                job[i++][j] = lastToken;
                j = 0;
                if(nextLineFirstTOken != "\n") // when you read the last token of the last line
                        job[i][j++] = nextLineFirstTOken;
        }
        else
        {
                job[i][j++] = row;
        }

      }//end while

      for(int i = 0; i < n+1; ++i)
      {
        for(int j = 0; j < m+1; ++j)
        {
//                cout << job[i][j] << " ";
                if(i > 0 && j > 0){
                    mat[i-1][j-1] = stoi(job[i][j]);
                }
        }
//        cout << endl;
      }

    }//end if for jobfile open
    jobfile.close();

}

void Matrix::file_to_matrix(unsigned int n, unsigned int m, string file_name, string file_type){
    mat = new int*[n];
    this->n = n;
    this->m = m;
    for(unsigned int i = 0; i < n; i++){
        mat[i] = new int[m];
    }
    if(file_type == "csv"){
        Matrix::csv_file_to_matrix(n,m,file_name);
    }
    else if(file_type == "txt"){
        Matrix::txt_file_to_matrix(n,m,file_name);
    }
    else return;
}

void Matrix::print_matrix(){
    cout<<"[";
    for (unsigned int i=0;i<n;i++){
        cout<<"[";
        for (unsigned int j=0;j<m;j++){
          cout<<mat[i][j]<<' ';
        }
        if (i!=n-1){
          cout<<"]"<<"\n";
        }
        else{
          cout<<"]"<<"]";

        }
    }
}
