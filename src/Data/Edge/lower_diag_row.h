#ifndef LOWER_DIAG_ROW_H
#define LOWER_DIAG_ROW_H

template<typename>
class Matrix;

template<typename Stream, typename Type>
Stream& lower_diag_row_read(Stream &stream, Matrix<Type>& matrix)
{
	for (unsigned row = 0; row < matrix.matrix_size; row++)
		for (unsigned column = 0; column <= row; column++)
		{
			stream >> matrix[row][column];
		}
	return stream;
}

#endif