#include "bioprocesslist.h"

bioprocesslist::bioprocesslist()
{

}

void bioprocesslist::makelist(std::string filename){

    inFile.open(filename); //NOTE: file path must be specified (API team???)

    if (inFile.is_open()){ //checking whether the file is open

        while(getline(inFile, str)){ //read data from file object and convert it into strings

            if(str.substr(0,3) == "id:" || str.substr(0,5) == "name:"){ //scan for lines starting with "id:" or "name:"
                start = str.find(": ");
                str2 = str.substr(start+2);
                BPlist.push_back(str2);
            }

            if(str.substr(0,8) == "synonym:"){ //scan for lines starting with "synonym:"
                end = str.find("\" ");
                str3 = str.substr(10, end-10);
                BPlist.push_back(str3);
            }
        }

        inFile.close(); //close the file
    }

    /*std::cout << "\nVector elements are: " << std::endl;
    for (int i = 0; i < BPlist.size(); i++) {
        std::cout << BPlist[i] << std::endl;
    }*/
    //this prints out the vector BPlist so that you can see the elements inside (takes a while!!)

    //TODO: verify whether IDs for [typedef] objects in the .obo file should be added, otherwise delete them from the .txt
}
