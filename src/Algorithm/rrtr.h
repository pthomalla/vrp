#ifndef RRTR_H
#define RRTR_H

#include <vector>
#include <functional>

typedef std::vector<int> Path;
typedef std::function<Path(Path,int node)> Operator;

struct  Solution{
    int cost;
    Path path;
};

class Rrtr
{
    typedef std::function<int(const Path&)> Cost;
    typedef std::function<void(Path&)> Pertub;
    int record_to_record, // I
        pertubation, // P
        counter, // K
        bestCost; // R
    size_t bestMaxSize;
    float delta;

    Cost cost;
    Pertub pertub;

    std::vector<Solution> bestList;
    std::vector<Operator> operators;
    std::vector<Operator> subset_operators;

    bool applyOperator(Operator&,Solution&,int t = 0);
    void tryAddTooBest(const Solution&);
public:
    Rrtr
    (
       Cost costFunction,
       Pertub pertubFunction,
       std::vector<Operator> operators,
       int bestMaxSize=50
    );
    void run(Path);
    std::vector<Solution> getBest();

};

#endif // RRTR_H
