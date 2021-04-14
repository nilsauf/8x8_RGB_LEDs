#include <Arduino.h>
#include <RgbMatrix.hpp>

#define ROW_COUNT 8
#define COLUMN_COUNT 8
#define MAX_BRIGHTNESS 255

RgbMatrix matrix(ROW_COUNT, COLUMN_COUNT);

void setup()
{
  // put your setup code here, to run once:
}

void SetupMatrix()
{
  for (size_t rowIndex = 0; rowIndex < ROW_COUNT; rowIndex++)
  {
    RgbMatrixLedRow *rgbRowAtIndex = new RgbMatrixLedRow(rowIndex);
    for (size_t ledIndex = 0; ledIndex < COLUMN_COUNT; ledIndex++)
    {
      RgbMatrixLed *rgbLedAtIndex = new RgbMatrixLed(
          ledIndex,
          0 + 3 * ledIndex,
          1 + 3 * ledIndex,
          2 + 3 * ledIndex,
          MAX_BRIGHTNESS);
      rgbRowAtIndex->WithRgbLedAt(rgbLedAtIndex, ledIndex);
    }

    matrix.WithRowAt(rgbRowAtIndex, rowIndex);
  }

  for (size_t columnIndex = 0; columnIndex < COLUMN_COUNT; columnIndex++)
  {
    MatrixLedList *columnAtIndex = new MatrixLedList(columnIndex);
    // Add LEDs

    for (size_t ledIndex = 0; ledIndex < ROW_COUNT; ledIndex++)
    {
      MatrixLed *ledAtIndex = new MatrixLed(0, 0, MAX_BRIGHTNESS);
      columnAtIndex->WithLedAt(ledAtIndex, ledIndex);
    }

    matrix.WithColumnAt(columnAtIndex, columnIndex);
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
}