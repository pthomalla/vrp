#include <exception>
#include "File_tsp.h"

File_tsp::File_tsp() :name("non"), comment(""), 
				      dimension(0), capacity(0)
{}

shared_ptr<const Matrix<int>> to_full(shared_ptr<const Matrix<int>> matrix){

	if(matrix->get_format() == Edge_weight_format::FULL_MATRIX)return matrix;
	shared_ptr<Matrix<int>> result(make_shared<Matrix<int>>(*matrix));
	switch (result->get_format()){
	case Edge_weight_format::LOWER_ROW:
	case Edge_weight_format::LOWER_DIAG_ROW:
		for (unsigned int row = 0; row < result->matrix_size; row++)
		for (unsigned int column = row + 1; column < result->matrix_size; column++)
			(*result)[row][column] = (*result)[column][row];
		break;
	case Edge_weight_format::UPPER_ROW:
		for (unsigned int row = 0; row < result->matrix_size; row++)
		for (unsigned int column = row + 1; column < result->matrix_size; column++)
			(*result)[column][row] = (*result)[row][column];
		break;
	default:
		throw logic_error("not yet implemented"+ result->get_format().to_string());
	}
	return result;


}
shared_ptr<const Matrix<int>> File_tsp::get_full_matrix()const{
	if (matrix.get() != nullptr) {
		return to_full(matrix);
	}
	return nodes->get_full_matrix(edge_weight_type);
}