#ifndef RGB_MATRIX_LED_WRAPPER_H
#define RGB_MATRIX_LED_WRAPPER_H

#include <Arduino.h>
#include <MatrixLed.hpp>

class RgbMatrixLed;

class RgbLedToNonRgbWrapper : public MatrixLed
{
public:
	RgbLedToNonRgbWrapper(RgbMatrixLed *rgbLed);

	uint8_t GetPwmState();

private:
	RgbMatrixLed *_rgbLed;
};

#endif