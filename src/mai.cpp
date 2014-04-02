#include "Data/Vrp_Paths.h"
#include "Data/Wraper_read.h" 
#include "Data/Result.h"
#include "cost.h"
#include "Algorithm/rrtr.h"

#include <fstream>
#include <iostream>

#include <thread>
#include <random>

#include <regex>

//using namespace std;
using namespace std;

bool test_opt(string path);
void test_algorytm();

int main(){

    Vrp_Paths ppp;
    int test_all = 0, fail_test = 0;
    string p("../magisterka_git/src/Vrp-All");

    ppp.add_from_folder(p);
    for (auto str : ppp){
        
        test_all++;
		if (str.second.result_path == "") continue;
		if (!test_opt(str.second.result_path)){
			fail_test++;
			cout << str.first << "\t" << str.second.data_path << "\t" << str.second.result_path << endl;
		}

    }

    cout<<"\n\n\ntest: "<<test_all<<"\tfail: "<<fail_test<<"\n\n\n";

    cout<<"suport thread: "<< thread::hardware_concurrency();


    test_algorytm();

	int i;
	cin >> i;
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
        }
        else throw runtime_error(("file not open " + path).c_str());

        int my_cost = cost(*data.get_full_matrix(), result.get_routs(),0);
        if(my_cost != result.get_cost() )
            cout << "\tcost: " << my_cost <<"\t=\t"<<result.get_cost()<<"\t";

        cout<<result.get_cost()<<endl;

//        Rrtr algorytm;
//        algorytm.run();

        return my_cost == result.get_cost();
    }
    catch (exception& exe){
        cout << exe.what();
    }

    return false;
}
//        neighbors, // n
//        closest_neighbors,// N
void test_algorytm(){
    std::mt19937 rng;
    rng.seed();
    auto cost = [](const Path& path){
        int cost = 0 ;
        for(int i = path.size()-1; i >=0 ; i--){
            cost += path[i]*(i+1);
        }
        return cost;
    };
    auto pertub = [&](Path& path){
        swap(path[rng()%path.size()],path[rng()%path.size()]);
    };
    vector<Operator> operators{
        [&](Path path, int i){
            swap(path[i],path[rng()%path.size()]);
            //std::cout<<"operator cost:"<<cost(path)<<std::endl;
            return path;
        }
    };
    Path path(100);
    std::iota(path.begin(),path.end(),1);
    std::cout<<"\n\noptimum: "<<cost({path.rbegin(),path.rend()})<<std::endl;
    Rrtr algorytm(cost,pertub,operators,5);

    Solution mbest;
    mbest.path = path;
    mbest.cost = cost(mbest.path);
    std::cout<<mbest.cost;
    while(true){
        std::cout<<"======================================================="<<std::endl;
    algorytm.run(mbest.path);//path);

    std::cout<<"\n\noptimum: "<<cost({path.rbegin(),path.rend()})
               <<"\t my solution "<<mbest.cost<<"\t{";
    for(auto elem : mbest.path)
        std::cout<<elem<<" ";
    std::cout<<"}"<<std::endl;


    std::cout<<"----------------------"<<std::endl;
    for(auto best : algorytm.getBest()){
        std::cout<<"{";
        for(auto e : best.path) std::cout<<e<<" ";
        std::cout<<"} cost: "<<best.cost<<std::endl;

        if(best.cost < mbest.cost) mbest = best;
    }
    std::cout<<"^^^^^^^^^^^^^^^^^^^^^^"<<std::endl;
    char i ;
    std::cin >>i;
    }



}

/*

int suma = 0;
if(d[i] >= 128){
    sum += d[i];
}

//druga możliwość
int t = (d[i] - 128) >> 31;
    sumt = ~t&d[i];
*/



