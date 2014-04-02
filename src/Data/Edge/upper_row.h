#ifndef UPPER_ROW_H
#define UPPER_ROW_H

template<typename>
class Matrix;

template<typename Stream, typename Type>
Stream& upper_row_read(Stream &stream, Matrix<Type>& matrix)
{
	for (unsigned row = 0; row < matrix.matrix_size; row++)
		for (unsigned column = row + 1; column < matrix.matrix_size; column++)
		{
			stream >> matrix[row][column];
		}
	
	return stream;
}

#endif