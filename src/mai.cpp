#include "Data/Vrp_Paths.h"
#include "Data/Wraper_read.h" //File_tsp
#include "Data/Result.h"
#include "cost.h"

#include <fstream>
#include <iostream>

using namespace std;

bool test_read(string paht);
bool test_opt(string path);

bool test_bardzo_dluga_funkcja(int aaaaaaaaaaaaaaaaaa,int bbbbbbbbbbb, int cccccccccccc, int kuuuuuuuuuuuuuuu,int ddddd);
int main(){

    Vrp_Paths ppp;
    int test_all = 0, fail_test = 0;
    string p("../../src/Vrp-All");

    ppp.add_from_folder(p);
    for (auto str : ppp){
        cout << str.first << "\t" << str.second.data_path<4<"\t"<<str.second.result_path<<endl;
        test_all++;
        if(!test_opt(str.second.result_path))
            fail_test++;

    }

    cout<<"\n\n\ntest: "<<test_all<<"\tfail: "<<fail_test<<"\n\n\n";

}

bool test_read(string path){
    File_tsp data;
    ifstream file;
    file.open(path);

    if (file.is_open()){
        try{
            file >> data;
            return true;
        }
        catch(exception& exe){
            cout <<"\n"<< exe.what();
            return false;
        }
    }
    cout << "\nFail to read\n";
    return false;
}

bool test_opt(string path){
    Result result;
    File_tsp data;
    ifstream file;

    try{
        file.open(path);
        if (file.is_open()){
            file >> result;
        }
        else throw runtime_error(("file not open "+path).c_str());
        file.close();
        file.open(path.replace(path.length() - 3, path.length(), "vrp"));
        if (file.is_open()){
            file >> data;
            cout << data;
        }
        else throw runtime_error(("file not open " + path).c_str());

        int my_cost = cost(*data.get_full_matrix(), result.get_routs(),0);
        cout << "\tcost: " << my_cost <<"\t=\t"<<result.get_cost()<<"\t";
        if (my_cost != result.get_cost()){
            //cout << "\n" << *data.get_full_matrix() << "\n";
        }
        return my_cost == result.get_cost();
    }
    catch (exception& exe){
        cout << exe.what();
    }

    return false;
}

string file(){
    return R"(NAME : A-n32-k5
COMMENT : (Augerat et al, No of trucks: 5, Optimal value: 784)
TYPE : CVRP
DIMENSION : 32
EDGE_WEIGHT_TYPE : EUC_2D
CAPACITY : 100
NODE_COORD_SECTION
 1 82 76
 2 96 44
 3 50 5
 4 49 8
 5 13 7
 6 29 89
 7 58 30
 8 84 39
 9 14 24
 10 2 39
 11 3 82
 12 5 10
 13 98 52
 14 84 25
 15 61 59
 16 1 65
 17 88 51
 18 91 2
 19 19 32
 20 93 3
 21 50 93
 22 98 14
 23 5 42
 24 42 9
 25 61 62
 26 9 97
 27 80 55
 28 57 69
 29 23 15
 30 20 70
 31 85 60
 32 98 5
DEMAND_SECTION
1 0
2 19
3 21
4 6
5 19
6 7
7 12
8 16
9 6
10 16
11 8
12 14
13 21
14 16
15 3
16 22
17 18
18 19
19 1
20 24
21 8
22 12
23 4
24 8
25 24
26 24
27 2
28 20
29 15
30 2
31 14
32 9
DEPOT_SECTION
 1
 -1
EOF
)";
}
