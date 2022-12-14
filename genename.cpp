/*What to put in the main:
#include "genename.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;
using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector; using std::istringstream;
using std::stringstream;
int main(){
    string l="[136,[\"HGNC:35077\",\"HGNC:35019\",\"HGNC:77\",\"HGNC:35013\",\"HGNC:35114\",\"HGNC:24098\",\"HGNC:16638\"],null,[[\"TRR-CCT8-1\",\"tRNA-Arg-CCT-8-1\",\"TRNAR32P\"],[\"TRR-CCT6-2\",\"tRNA-Arg-CCT-6-2\",\"TRNAR31P\"],[\"ABL2\",\"ARG\",\"ABLL\"],[\"TRR-CCT7-1\",\"tRNA-Arg-CCT-7-1\",\"TRNAR30P\"],[\"TRR-CCT9-1\",\"tRNA-Arg-CCT-9-1\",\"TRNAR34P\"],[\"SORBS2\",\"ARGBP2|KIAA0777\",\"\"],[\"SRRM1\",\"SRM160|POP101|MGC39488\",\"\"]]]";
    string search="\"ARG\"";
    Genename test;
    test.listgene(l, search);
    return 0;
}
*/



#include "genename.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;

using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector; using std::istringstream;
using std::stringstream;


using namespace std;


Genename::Genename()
{

}

int Genename::isSubstring(string s1, string s2)
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

string Genename::listgene(string l, string search){
    int o=0; //nb of [
    int c=0; //nb of ]
    string len;
    string v;
    string index;
    string name;
    string list;
    string true_list;
    int j;

    for (int i=0;i<l.length();i++){
        v=l[i];

        if (v=="["){
            o+=1;
            j=i;}
        else if (v=="]"){
            c+=1;}

        if (o==1 and i!=0 and v!=","){
            len+=v;
        }
        else if (o==2 and c==0 and j!=i){
            index+=v;
        }
        else if (o>3 and (o-c)>1){
            name+=v;
        }
    }
    cout<<'\n';
    cout<<len<<'\n';
    cout<<index<<'\n';
    cout<<name<<'\n';

    o=0;
    c=0;
    for (int i=0;i<name.length();i++){
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

  cout<<true_list<<'\n';


    return true_list;}
