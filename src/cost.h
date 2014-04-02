#ifndef COST_H
#define COST_H

#include "Data/Edge/Matrix.h"

int cost( const Matrix<int> &matrix,const vector<vector<int>> &routes,int depot){
	int result = 0; 
	
	for (auto rout : routes){
		result += matrix[depot][rout.at(0)];
		result += matrix[depot][rout.at(rout.size() - 1)];

		for (unsigned int node = 1; node < rout.size(); node++) {
			result += matrix[rout.at(node - 1)][rout.at(node)];
		}
	}

	return result;
}

#endif
