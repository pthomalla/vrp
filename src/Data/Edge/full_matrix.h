#ifndef FULL_MATRIX_H
#define FULL_MATRIX_H

template<typename>
class Matrix;

template<typename Stream,typename Type>
Stream& full_matrix_read(Stream &stream, Matrix<Type>& matrix)
{
	for (unsigned row = 0; row < matrix.matrix_size; row++)
		for (unsigned column = 0; column < matrix.matrix_size; column++)
		{
			stream >> matrix[row][column];
		}
	return stream;
}

#endif