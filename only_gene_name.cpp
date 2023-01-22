
//Parse the “API answer” to only keep some informations (for both gene name and biological process API)



#include "only_gene_name.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <set>


only_gene_name::only_gene_name()
{

}

//check if a string is a substring of another
int only_gene_name::isSubstring(string s1, string s2)
{
    int M = s1.length();
    int N = s2.length();

    for (int i = 0; i <= N - M; i++)
    {
        int j;

        for (j = 0; j < M; j++)
            if (s2[i + j] != s1[j])
                break;

        if (j == M)
            return i;
    }
    return -1;
}

//parse the API answer for gene name
//Takes the string of the answer of the API as input and the "search parameter”(=the gene we are looking for)
//and returns a set with all the different names of this gene 
//(it was only gene like “GENE”, so I added the names like “Gene” and “gene” since there was some issue later with this)

std::set<std::string> only_gene_name::listgene(std::string l, std::string search){
    //if the search parameter is not only in upper case
    std::string upper_search = search;
    transform(upper_search.begin(), upper_search.end(), upper_search.begin(), ::toupper);

    //insert the gene name in the set to be sure the original name given by the researcher is in the set
    res.insert(search);


    int o=0; //nb of [
    int c=0; //nb of ]
    std::string v;
    std::string list;
    std::string name="[";
    std::string true_list;

    if(l.empty()){
        return res;
    }else{
        //First look for the last list of list (the only part of the string we are interrested in
        for (unsigned int i=0;i<l.length()-2;i++){
            v=l[i];
            if (o!=2){
                if (v=="["){
                    o+=1;}
                else{
                    o=0;
                }}
            else{
                name+=v;
            }}


        //Then look for each list of this list and check if our "search" parameter is in it
        std::string value;
        std::set<std::string> res;
        std::string val;
        std::string gene;

        o=0;
        c=0;
        for (unsigned int i=0;i<name.length();i++){
            v=name[i];
            if (v=="["){
                o+=1;}
            else if (v=="]"){
                c+=1;}

            if ((o-c)==1 and v!="["){
                list+=v;
            }

            else if (c==o) {
                int res = isSubstring(upper_search,list);
                if (res !=-1){
                    true_list=list;
                }
                list="";
            }

            // If the search parameter is in it: list becomes true_list, then we need to add every element of the list in the set
            for (unsigned int j=0; j<true_list.length();j++){
                value=true_list[j];
                if (value==","){
                    res.insert(val);
                    val.clear();
                }
                else if (value!="\0" and value!="\""){
                    val+=value;
                    value.clear();
                }}
                res.insert(val);
                val.clear();


        }

        //remove the " " at the beginning and at the end of the string if they are present
        //gene=upper_search.substr(1, upper_search.length() - 2);
        gene.reserve(upper_search.size());
        std::remove_copy_if(
            begin(upper_search), end(upper_search),
            std::back_inserter(gene),
            [m = std::locale{}](auto ch) { return std::isspace(ch, m); }
        );


        for (const std::string& str : res) {
            std::string lowercase_str = str;
            transform(lowercase_str.begin(), lowercase_str.end(), lowercase_str.begin(), ::tolower);
            res.insert(lowercase_str);

            if (str.size()>0){
            std::string capitalized_str = str;
                    capitalized_str[0] = toupper(capitalized_str[0]);
                    transform(capitalized_str.begin() + 1, capitalized_str.end(), capitalized_str.begin() + 1, ::tolower);
                    res.insert(capitalized_str);}
        }
    }

    for (const std::string& str : res) {
//        std::cout << str << std::endl;
    }
    return res;}


//parse the API answer for biological process 
//takes the string of the answer of the API as input 3 "search parameter” (normally it will be number_in_list, id and label)
//return these info for the first biological process in API answer
set<Info> only_gene_name::list_bio_process(string json, string search1, string search2, string search3){
    cout<<json<<'\n';
    set<Info> infoSet;
    stringstream ss(json);
    string line;
    int number_in_list;
    string id;
    string label;

    while(getline(ss, line)) {
        if (isSubstring(search1,line) != -1) {
            // Extract the number_in_list value
            number_in_list = stoi(line.substr(line.find(":") + 1));}
        else if (isSubstring(search2,line) != -1) {
            // Extract the number_in_list value
            id = line.substr(line.find(":") + 3, line.find(",") - line.find(":") - 4);
        }
        else if (isSubstring(search3,line) != -1) {
            // Extract the number_in_list value
            label=line.substr(line.find(":") + 2, line.find("\"") - line.find(":")-4);
            // Add the extracted information to the set
            infoSet.insert({number_in_list, id, label});

            // Print the Info set
            for (auto info : infoSet) {
                cout << "number_in_list: " << info.number_in_list << endl;
                cout << "id: " << info.id << endl;
                cout << "label: " << info.label << endl;
            }

            return infoSet; //we want to stop the code as soon as a label is find
        }
    }
return infoSet;
}



//print a set
void only_gene_name::printset(std::set<std::string> result){
    std::cout<<'\n'<<"Set is: { ";
    for(auto& str: result)
      {
        std::cout << str << ' ';
      }
    std::cout<<"}";
}

