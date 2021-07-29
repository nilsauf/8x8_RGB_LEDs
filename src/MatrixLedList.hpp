#ifndef MATRIX_LED_LIST
#define MATRIX_LED_LIST

#include <Arduino.h>
#include <MatrixLed.hpp>

class MatrixLedList
{
public:
	MatrixLedList(const uint8_t rowIndex)
	{
		this->RowIndex = rowIndex;
		this->_ledsInList = (MatrixLed **)malloc(this->_ledCount * sizeof(MatrixLed *));
	}

	MatrixLedList *WithLedAt(MatrixLed *led, uint8_t index)
	{
		this->CheckIndex(index, this->_ledCount);
		this->_ledsInList[index] = led;
		return this;
	}

	uint8_t GetMaxLedState()
	{
		uint8_t maxState = 0;

		for (size_t ledIndex = 0; ledIndex < this->_ledCount; ledIndex++)
		{
			maxState = max(maxState, this->_ledsInList[ledIndex]->GetPwmState());
		}

		return maxState;
	}

	uint8_t GetLedState(uint8_t index)
	{
		this->CheckIndex(index, this->_ledCount);
		return this->_ledsInList[index]->GetPwmState();
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

	const uint8_t _ledCount = 8;
	MatrixLed **_ledsInList;
};

#endif