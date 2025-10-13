# LiBoard - Arduino library
This Arduino library provides the code running on the board's microcontroller.

## Installation
Clone this repo into `YOUR_ARDUINO_FOLDER/libraries/`.

## Usage
If you're just interested in using the board with a script or the app, you'll want
to run the `serial_binboard` sketch from the library's examples folder.

## Thresholds
Each photoresistor requires a threshold value which triggers when each square is occupied or not. There are two options you can use to set the threshold values for each square.

### Option 1 - Global Threshold
By default, a global threshold is set for every phtooresistor. If you need to change the sensitivity of the photoresistors, change the value of this variable:
```C
// Option 1 - Global Threshold (Applies to all photoresistors)
const unsigned short THRESHOLD = 500;
```

### Option 2 - Per-square threshold
If you require each photoresistor to have its own threshold rather than a global threshold, comment out Option 1 and uncomment Option 2. 

You can adjust each square threshold individually by editing each number.
```C
// Option 2 - Per-square threshold (Applies to each individual photoresistor)
unsigned short THRESHOLD[64] = {
  // A1..H1
  150, 150, 150, 150, 150, 150, 150, 150,
  // A2..H2
  150, 150, 150, 150, 150, 150, 150, 150,
  // A3..H3
  100, 100, 100, 100, 100, 100, 100, 100,
  // A4..H4
  100, 100, 100, 100, 100, 100, 100, 100,
  // A5..H5
  600, 600, 600, 600, 600, 600, 600, 600,
  // A6..H6
  600, 600, 600, 600, 600, 600, 600, 600,
  // A7..H7
  300, 300, 300, 300, 300, 300, 300, 300,
  // A8..H8
  300, 300, 300, 300, 300, 300, 300, 300
};
```
