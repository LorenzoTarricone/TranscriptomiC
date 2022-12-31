
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

using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector; using std::istringstream;
using std::stringstream;


int main(){
    string l="[136,[\"HGNC:35077\",\"HGNC:35019\",\"HGNC:77\",\"HGNC:35013\",\"HGNC:35114\",\"HGNC:24098\",\"HGNC:16638\"],null,[[\"TRR-CCT8-1\",\"tRNA-Arg-CCT-8-1\",\"TRNAR32P\"],[\"TRR-CCT6-2\",\"tRNA-Arg-CCT-6-2\",\"TRNAR31P\"],[\"ABL2\",\"ARG\",\"ABLL\"],[\"TRR-CCT7-1\",\"tRNA-Arg-CCT-7-1\",\"TRNAR30P\"],[\"TRR-CCT9-1\",\"tRNA-Arg-CCT-9-1\",\"TRNAR34P\"],[\"SORBS2\",\"ARGBP2|KIAA0777\",\"\"],[\"SRRM1\",\"SRM160|POP101|MGC39488\",\"\"]]]";
    string search="\"ARG\"";
    only_gene_name test;
    set<string> result;
    result=test.listgene(l, search);
    test.printset(result);
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

using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector; using std::istringstream;
using std::stringstream;


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
    int o=0; //nb of [
    int c=0; //nb of ]
    string v;
    string list;
    string name="[";
    string true_list;
    cout<<l<<'\n';
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
            int res = isSubstring(search,list);
            if (res !=-1){
                cout<<"Found"<<'\n';
                true_list=list;
            }
            list="";
        }

    }

    string value;
    set<string> res;
    string val;
    for (int i=0; i<true_list.length();i++){
        value=true_list[i];
        if (value==","){
            res.insert(val);
            val.clear();
        }
        else if (value!="\0" and value!="\""){
            val+=value;
            value.clear();
        }
    }
    res.insert(val);

    return res;}


void only_gene_name::printset(set<string> result){
    cout<<'\n'<<"Set is: { ";
    for(auto& str: result)
      {
        std::cout << str << ' ';
      }
    cout<<"}";
}
