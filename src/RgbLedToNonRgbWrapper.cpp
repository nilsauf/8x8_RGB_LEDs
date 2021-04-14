#ifndef RGB_MATRIX_LED_WRAPPER_C
#define RGB_MATRIX_LED_WRAPPER_C

#include <Arduino.h>
#include <RgbLedToNonRgbWrapper.hpp>
#include <RgbMatrixLed.hpp>

RgbLedToNonRgbWrapper::RgbLedToNonRgbWrapper(RgbMatrixLed *rgbLed)
	: MatrixLed(rgbLed->GetCathodeIndex(), rgbLed->GetAnodeColorIndex(Red), 255)
{
	this->_rgbLed = rgbLed;
}

uint8_t RgbLedToNonRgbWrapper::GetPwmState()
{
	uint8_t maxState = 0;
	uint8_t *ledStates = this->_rgbLed->GetPwmStates();

	for (size_t ledIndex = 0; ledIndex < 3; ledIndex++)
	{
		maxState = max(maxState, ledStates[ledIndex]);
	}

	return maxState;
}

#endif