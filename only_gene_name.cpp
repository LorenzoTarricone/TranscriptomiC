
/* main to test listgene
 * #include "only_gene_name.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include<set>
using namespace std;

//For gene names
int main(){
    string l="[136,[\"HGNC:35077\",\"HGNC:35019\",\"HGNC:77\",\"HGNC:35013\",\"HGNC:35114\",\"HGNC:24098\",\"HGNC:16638\"],null,[[\"TRR-CCT8-1\",\"tRNA-Arg-CCT-8-1\",\"TRNAR32P\"],[\"TRR-CCT6-2\",\"tRNA-Arg-CCT-6-2\",\"TRNAR31P\"],[\"ABL2\",\"ARG\",\"ABLL\"],[\"TRR-CCT7-1\",\"tRNA-Arg-CCT-7-1\",\"TRNAR30P\"],[\"TRR-CCT9-1\",\"tRNA-Arg-CCT-9-1\",\"TRNAR34P\"],[\"SORBS2\",\"ARGBP2|KIAA0777\",\"\"],[\"SRRM1\",\"SRM160|POP101|MGC39488\",\"\"]]]";
    string search="\"ARG\"";
    only_gene_name test;
    set<string> result;
    result=test.listgene(l, search);
    test.printset(result);
    return 0;
}

//For list biological processes
int main(){
    string json = R"({"results": {
    "reference": {
        "organism": "Homo sapiens",
        "mapped_count": 20589,
        "unmapped_count": 0
    },
    "input_list": {
        "organism": "Homo sapiens",
        "mapped_count": 3,
        "mapped_id": [
            "GPI",
            "NDRG1",
            "VEGFA"
        ],
        "unmapped_count": 0
    },
    "result": [
        {
            "number_in_list": 2,
            "fold_enrichment": 175.97435897435898,
            "fdr": 0.6994197998675634,
            "expected": 0.011365292146291709,
            "number_in_reference": 78,
            "pValue": 4.46030100036709E-5,
            "term": {
                "id": "GO:0043154",
                "label": "negative regulation of cysteine-type endopeptidase activity involved in apoptotic process"
            },
            "plus_minus": "+"
        }
    ]
}})";
    string search1="\"number_in_list\"";
    string search2="\"id\"";
    string search3="\"label\"";
    only_gene_name test;
    set<Info> result;
    result=test.list_bio_process(json, search1,search2,search3);
    return 0;
}
*/

#include "only_gene_name.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;



only_gene_name::only_gene_name()
{

}

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


set<string> only_gene_name::listgene(string l, string search){
    //if the search parameter is not only in upper case
    string upper_search = search;
    transform(upper_search.begin(), upper_search.end(), upper_search.begin(), ::toupper);
    cout<<"UP"<<upper_search<<'\n';

    int o=0; //nb of [
    int c=0; //nb of ]
    string v;
    string list;
    string name="[";
    string true_list;
    cout<<l<<'\n';
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

    cout<<'\n';
    cout<<name<<'\n'<<'\n';

    //Then look for each list of this list and check if our "search" parameter is in it
    string value;
    set<string> res;
    string val;
    string gene;

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
            cout<<list<<'\n';
            cout<<"search= "<<upper_search<<'\n';
            int res = isSubstring(upper_search,list);
            if (res !=-1){
                cout<<"Found"<<'\n';
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

    //remove the " " at the beginning and at the end of the string
    gene=upper_search.substr(1, upper_search.length() - 2);

    //insert the gene name in the set to be sure the original name given by the researcher is in the set
    res.insert(gene);

    for (const string& str : res) {
        string lowercase_str = str;
        transform(lowercase_str.begin(), lowercase_str.end(), lowercase_str.begin(), ::tolower);
        res.insert(lowercase_str);

        if (str.size()>0){
        string capitalized_str = str;
                capitalized_str[0] = toupper(capitalized_str[0]);
                transform(capitalized_str.begin() + 1, capitalized_str.end(), capitalized_str.begin() + 1, ::tolower);
                res.insert(capitalized_str);}
    }

    for (const string& str : res) {
        cout << str << endl;
    }
    return res;}


void only_gene_name::printset(set<string> result){
    cout<<'\n'<<"Set is: { ";
    for(auto& str: result)
      {
        std::cout << str << ' ';
      }
    cout<<"}";
}

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
            std::cout<<line<<'\n';
            number_in_list = stoi(line.substr(line.find(":") + 1));}
        else if (isSubstring(search2,line) != -1) {
            // Extract the number_in_list value
            std::cout<<line<<'\n';
            id = line.substr(line.find(":") + 3, line.find(",") - line.find(":") - 4);
        }
        else if (isSubstring(search3,line) != -1) {
            std::cout<<line<<'\n';
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


