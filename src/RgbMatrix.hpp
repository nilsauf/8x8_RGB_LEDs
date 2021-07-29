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
	}

	RgbMatrix *WithRowAt(RgbMatrixLedRow *row, uint8_t index)
	{
		this->CheckIndex(index, this->_rowCount);
		this->_rows[index] = row;
		return this;
	}

	uint8_t *GetShiftRegisterValues()
	{
		uint8_t *data = (uint8_t *)malloc(sizeof(uint8_t) * (3 * this->_rowCount + this->_columnCount));
		uint8_t dataindex = 0;
		for (uint8_t rowindex = 0; rowindex < this->_rowCount; rowindex++)
		{
			data[0 + 3 * rowindex] = this->_rows[rowindex]->GetMaxLedState(Red);
			data[1 + 3 * rowindex] = this->_rows[rowindex]->GetMaxLedState(Green);
			data[2 + 3 * rowindex] = this->_rows[rowindex]->GetMaxLedState(Blue);
			dataindex += 3;
		}

		for (uint8_t columnIndex = 0; columnIndex < this->_columnCount; columnIndex++)
		{
			uint8_t value = 0;
			for (uint8_t rowindex = 0; rowindex < this->_rowCount; rowindex++)
			{
				value = max(value, this->_rows[rowindex]->GetMaxLedState(columnIndex));
			}

			data[dataindex++] = value;
		}

		Serial.println("final dataindex = " + String(dataindex));
		return data;
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
};

#endif