#ifndef RGB_MATRIX_LED_ROW
#define RGB_MATRIX_LED_ROW

#include <Arduino.h>
#include <MatrixLedList.hpp>
#include <RgbMatrixLed.hpp>

class RgbMatrixLedRow
{
public:
	RgbMatrixLedRow(const uint8_t rowIndex)
	{
		this->RowIndex = rowIndex;
		this->_redLedLists = new MatrixLedList(0 + rowIndex * this->_listCount);
		this->_greenLedLists = new MatrixLedList(1 + rowIndex * this->_listCount);
		this->_blueLedLists = new MatrixLedList(2 + rowIndex * this->_listCount);
	}

	RgbMatrixLedRow *WithRgbLedAt(RgbMatrixLed *led, uint8_t index)
	{
		this->_redLedLists->WithLedAt(led->GetColorLed(Red), index);
		this->_greenLedLists->WithLedAt(led->GetColorLed(Green), index);
		this->_blueLedLists->WithLedAt(led->GetColorLed(Blue), index);

		return this;
	}

	uint8_t GetMaxLedState(ERgbLedColor color)
	{
		switch (color)
		{
		case Red:
			return this->_redLedLists->GetMaxLedState();
		case Green:
			return this->_greenLedLists->GetMaxLedState();
		case Blue:
			return this->_blueLedLists->GetMaxLedState();
		}
		return 0;
	}

	uint8_t GetMaxLedState(uint8_t index)
	{
		this->CheckIndex(index, 8);
		return max(
			this->_redLedLists->GetLedState(index),
			max(
				this->_greenLedLists->GetLedState(index),
				this->_blueLedLists->GetLedState(index)));
	}

	uint8_t RowIndex;

private:
	void CheckIndex(uint8_t index, uint8_t max)
	{
		if (index < 0 || index > max)
		{
			throw "Index need to be less than 0 and greater than " + String(max) + ", but was " + String(index);
		}
	}

	const uint8_t _listCount = 3;
	MatrixLedList *_redLedLists;
	MatrixLedList *_greenLedLists;
	MatrixLedList *_blueLedLists;
};

#endif