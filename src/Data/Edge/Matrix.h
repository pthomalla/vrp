#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <memory>
#include "../InterfaceEnum/Edge_weight_format.h"
#include "Edge_read_headers.h"
#include "../Adapter.h"

template<class Integer>
class Matrix{
	vector<Integer> data;
	Adapter<Edge_weight_format> format;

	template<typename Matrix_>
	class Operator;
public:
	const unsigned int matrix_size;

    Matrix(unsigned int size, Adapter<Edge_weight_format> format = Edge_weight_format::FULL_MATRIX) :format(format),matrix_size(size){
		data.resize(matrix_size*matrix_size, 0);
	}
	Operator<Matrix> operator[](unsigned int x){ return Operator<Matrix>(*this, x); }
	Operator<const Matrix> operator[](unsigned int x)const { return Operator<const Matrix>(*this, x); }
	Adapter<Edge_weight_format> get_format()const { return format; }
};

template<typename Integer>
template<typename Matrix_>
class Matrix<Integer>::Operator{
	unsigned int row;
	typename add_lvalue_reference<Matrix_>::type matrix;
	using Result_Type = typename add_lvalue_reference
		<
		typename conditional<is_const<Matrix_>::value,
		typename add_const<Integer>::type,
         Integer>::type
		>::type;
public:
    explicit Operator(Matrix_ &edges, unsigned int i) : row(i),matrix(edges){}
	Result_Type operator [](unsigned int column){
		if (row >= matrix.matrix_size || column >= matrix.matrix_size)
			throw out_of_range("out of range"
			"\nMatrix::operator[][](unsigned int row,unsigned int column)"
			"\n\trow\t=\t" + to_string(row) +
			"\n\tcolumn\t=\t" + to_string(column)
			);
		return matrix.data[row*matrix.matrix_size + column];
	}
};

template<typename Stream, typename Type>
Stream&  operator>>(Stream& stream, Matrix<Type>& matrix){
	switch (matrix.get_format())
	{
	case Edge_weight_format::LOWER_ROW:
		return lower_row_read(stream, matrix);
	case Edge_weight_format::UPPER_ROW:
		return upper_row_read(stream, matrix);
	case Edge_weight_format::FULL_MATRIX:
		return full_matrix_read(stream, matrix);
	case Edge_weight_format::LOWER_DIAG_ROW:
		return lower_diag_row_read(stream, matrix);
	default:
		throw runtime_error("Stream&  operator>>(Stream& stream, Matrix<Type>& matrix)"
			"\n\tStream\t=\t" + string(typeid(Stream).name()) +
			"\n\tType\t=\t" + string(typeid(Type).name()) +
			"\n\tnot yet implemented:"
			"\n\t\tedge_weight_format: " + matrix.get_format().to_string());
		break;
	}
}

template<typename Stream, typename Type>
Stream& operator<<(Stream& stream, const Matrix<Type>& matrix){
	for (unsigned int row = 0; row < matrix.matrix_size; row++){
		for (unsigned int column = 0; column < matrix.matrix_size; column++)
			stream << "\t" << matrix[row][column];
        stream << "\n";
	}
	return stream;
}
#endif
