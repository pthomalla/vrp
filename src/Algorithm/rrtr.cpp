#include "rrtr.h"
#include <random>
#include <algorithm>
#include <limits>
#include <cmath>

Rrtr::Rrtr(Cost costFunction, Pertub pertubFunction, std::vector<Operator> operators, int bestMaxSize)
    :bestMaxSize(bestMaxSize),cost(costFunction),pertub(pertubFunction),operators(operators)
{
    //losowanie domyślnych wartości
    static std::default_random_engine engine{std::random_device{}()};
    static std::uniform_int_distribution<> distribution;
    using param_t = std::uniform_int_distribution<>::param_type ;


    distribution.param(param_t{0,1});
    record_to_record = distribution(engine) ? 25 : 75;
    for(auto& function : operators)
        if(distribution(engine))
            subset_operators.push_back(function);

    distribution.param(param_t{5,10});
    pertubation = distribution(engine);
    counter = distribution(engine);

    static std::uniform_real_distribution<> real_distribution{
                std::nextafter(0.005,std::numeric_limits<decltype(delta)>::max()),
                0.015}; // betwen (0.005,0.015)
    delta = real_distribution(engine);


    bestCost = std::numeric_limits<int>::max();


}

void Rrtr::run(Path startSolution)
{
    int k = 0 , p = 0;
    Solution solution;
    solution.path =  startSolution;
    solution.cost =  cost(solution.path);
    tryAddTooBest(solution);
    int threshold = solution.cost *(1+delta); //T


    while(p<pertubation)
    {
        for(int i =0 ; i < record_to_record ; i++ )
            for(auto oper : subset_operators)
              if(applyOperator(oper,solution,threshold))
                 tryAddTooBest(solution);

        bool improvment;
        do{
            improvment = false;
            for(auto oper : operators)
                improvment = improvment || applyOperator(oper,solution,solution.cost);
        }while(improvment);

        if(solution.cost < bestCost)//sprawdzić czy solution jest nowym najlepszym
        {
            bestCost = solution.cost;
            threshold = bestCost * (1+delta);
            tryAddTooBest(solution);
            k = 0;
        }
        else k++;
        //if The current solution is a new record then Update R and T and set k = 0
        //wpp k= k + 1

        if(k==counter)
        {
            pertub(solution.path);
            solution.cost = cost(solution.path);
           // tryAddTooBest(solution);
            p++;
            k=0;
        }

    }
}

bool Rrtr::applyOperator(Operator& oper,Solution& solution, int threshold){
    Solution tmpSolution;
    bool result = false;
    for(size_t j=0 ; j < solution.path.size(); j++)//auto j : solution.path)
    {
        tmpSolution.path = oper(solution.path,j);
        tmpSolution.cost = cost(tmpSolution.path);
        if(tmpSolution.cost < threshold)
            std::swap(tmpSolution,solution),result =  true;
    }
    return result;

}
void Rrtr::tryAddTooBest(const Solution& solution){
    auto iterator = std::lower_bound
            (
                bestList.begin(),
                bestList.end(),
                solution,
                [](const Solution& first, const Solution& second)
                    {
                        return first.cost > second.cost;
                    }
            );
#pragma message("TODO size == bestMaxSize not 2*bestMaxSize")
    bestList.insert(iterator,solution);
    if(bestList.size() >= bestMaxSize*2)
        bestList.erase(bestList.begin(),bestList.begin()+ (bestList.size()-bestMaxSize));

}
std::vector<Solution> Rrtr::getBest(){
#pragma message("do poprawy")
    if(bestList.size() > bestMaxSize)
        bestList.erase(bestList.begin(),bestList.begin()+ (bestList.size()-bestMaxSize));
    bestList.shrink_to_fit();

    return std::move(bestList);
}
