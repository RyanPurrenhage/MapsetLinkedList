#include "mapset.h"
#include<vector>
using std::vector;
#include<string>
using std::string;
#include<utility>
using std::pair;
#include <iostream>
using std::cout; using std::endl;using std::boolalpha;

int main(){
    cout << boolalpha;
    MapSet<string,long> ms1({ {"bill",1},{"alan",2},{"abby",3} });
    MapSet<string, long> ms2({ {"alan",4},{"abby", 5},{"john",7} });
    MapSet<string, long> ms3({ {"abby",5}, {"alan",17} });
    cout << endl;
    MapSet<string,long> ms_union = ms1.mapset_union(ms2);
    ostringstream oss;
    oss << ms_union;
    string result1 = oss.str();
    
    string ans1 = "abby:3, alan:2, bill:1, john:7";
    cout << result1 << ans1 << endl;
    //cout << "1: " << ms1 << endl;
    //cout << "2: " << ms2 << endl;
    ms_union = ms2.mapset_union(ms1);
    //cout << "heh" << endl;
    //cout << ms_union << endl;
    oss.str("");
    oss << ms_union;
    string result2 = oss.str();
    string ans2 = "abby:5, alan:4, bill:1, john:7";
    cout << ans2 << result2 << endl;
    ms_union.add({"clarence",8});
    ms_union.add({"Dick",8});
    ms_union.add({"bob",8});
    ms_union.add({"bob",8});
    ms_union.add({"clair",8});
    ms_union.remove("clarence");
    ms_union.remove("bob");
    ms_union.remove("john");
    ms_union.add({"aaa", 9});
    ms_union.add({"abbx", 9});
    if("aaa" > "abbx"){
        cout << "hehe" << endl;
    }
    oss.str("");
    oss << ms_union;
    string result3 = oss.str();
    cout << result3 << endl;
    //MapSet<string,long> ms1 ({{"b",0},{"a",0},{"c",0},{"d",0},{"e",0},{"f",0},{"g",0},{"h",0},{"i",0},{"j",0},{"k",0},{"l",0},{"m",0},{"n",0},{"o",0},{"p",0},{"q",0},{"R",0},{"z",0},{"t",0},{"u",0},{"v",0},{"w",0},{"x",0},{"y",0},{"s",0}});
    
   // cout << ms1 << endl;
    
}