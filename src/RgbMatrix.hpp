#ifndef RGB_MATRIX
#define RGB_MATRIX

#include <Arduino.h>
#include <RgbMatrixLedRow.hpp>
#include <MatrixLedList.hpp>

class RgbMatrix
{
public:
	RgbMatrix(const uint8_t rowCount, const uint8_t columnCount)
	{
		this->_rowCount = rowCount;
		this->_columnCount = columnCount;

		this->_rows = (RgbMatrixLedRow **)malloc(rowCount * sizeof(RgbMatrixLedRow *));
		this->_columns = (MatrixLedList **)malloc(columnCount * sizeof(MatrixLedList *));
	}

	RgbMatrix *WithRowAt(RgbMatrixLedRow *row, uint8_t index)
	{
		this->CheckIndex(index, this->_rowCount);
		this->_rows[index] = row;
		return this;
	}

	RgbMatrix *WithColumnAt(MatrixLedList *row, uint8_t index)
	{
		this->CheckIndex(index, this->_columnCount);
		this->_columns[index] = row;
		return this;
	}

	RgbMatrixLedRow GetRowAt(uint8_t index)
	{
		this->CheckIndex(index, this->_rowCount);
		return *this->_rows[index];
	}

	MatrixLedList GetColumnAt(uint8_t index)
	{
		this->CheckIndex(index, this->_columnCount);
		return *this->_columns[index];
	}

private:
	void CheckIndex(uint8_t index, uint8_t max)
	{
		if (index < 0 || index > max)
		{
			throw "Index need to be less than 0 and greater than " + String(max) + ", but was " + String(index);
		}
	}

	uint8_t _rowCount;
	uint8_t _columnCount;

	RgbMatrixLedRow **_rows;
	MatrixLedList **_columns;
};

#endif