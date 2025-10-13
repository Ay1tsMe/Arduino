/* LiBoard
 * Copyright (C) 2021 Philipp Leclercq
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as published by
 * the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#include "LiBoard.h"

// Option 1 - Global Threshold (Applies to all photoresistors)
const unsigned short THRESHOLD = 500;

// Option 2 - Per-square threshold (Applies to each individual photoresistor)
/*
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
*/

LiBoard board = LiBoard();
unsigned long long lastBinBoard = 0;
unsigned long long currentBinBoard = 0;

void writeBinaryBoard(unsigned long long binBoard) {
  for (unsigned char i = 0; i<8; ++i)
    Serial.write((unsigned char)(binBoard>>(8*(7-i))));
}

void setup() {
  delay(3000);
  Serial.begin(9600);
}

void loop() {
  currentBinBoard = board.getBinaryBoard(THRESHOLD);
  if (currentBinBoard != lastBinBoard) {
    writeBinaryBoard(currentBinBoard);
    lastBinBoard = currentBinBoard;
  }
}
