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
unsigned short THRESHOLD = 100;

// Option 2 - Per-square threshold (Applies to each individual photoresistor)
//unsigned short THRESHOLD[64] = {
  // A1-A8
//  387,  398,  424,  493,  361,  353,  501,  309,
  // B1-B8
//  416,  422,  412,  417,  483,  426,  353,  419,
  // C1-C8
//  288,  266,  297,  229,  298,  267,  269,  309,
  // D1-D8
//  311,  328,  287,  300,  290,  313,  255,  438,
  // E1-E8
//  675,  708,  724,  717,  706,  690,  783,  729,
  // F1-F8
//  708,  707,  707,  686,  719,  722,  710,  662,
  // G1-G8
//  555,  573,  590,  659,  581,  580,  643,  650,
  // H1-H8
//  504,  474,  490,  643,  623,  651,  526,  647,
//};

bool calibrating = false;

LiBoard board = LiBoard();
unsigned long long lastBinBoard = 0;
unsigned long long currentBinBoard = 0;

void writeBinaryBoard(unsigned long long binBoard) {
  for (unsigned char i = 0; i<8; ++i)
    Serial.write((unsigned char)(binBoard>>(8*(7-i))));
}

// print a single CSV snapshot of raw ADC values (A1..H8 in LiBoard order)
void printRawSnapshotCSV() {
  board.getData();                   // fills board.values[0..63]
  for (int i = 0; i < 64; ++i) {
    Serial.print(board.values[i]);
    if (i < 63) Serial.print(',');
  }
  Serial.println();
}

void setup() {
  delay(3000);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    int c = Serial.read();
    // if host sends '?', reply with one CSV line of raw ADC values
    if (c == '?') {
      printRawSnapshotCSV();
    }

    if (c == 'c') {
      calibrating = true;
      Serial.println("Calibration Mode Activated!");
    }

    while (calibrating) {
      if (Serial.available()){
        int p = Serial.peek();
        if (isDigit(p)) {
          int newValue = Serial.parseInt();
          THRESHOLD = newValue;
          Serial.print("THRESHOLD is now: ");
          Serial.println(THRESHOLD);
          calibrating = false;
        }
        // eat non-numeric to avoid getting stuck
        else {
          Serial.read();
        }
      }
    }
  }

  currentBinBoard = board.getBinaryBoard(THRESHOLD);
  if (currentBinBoard != lastBinBoard) {
    writeBinaryBoard(currentBinBoard);
    lastBinBoard = currentBinBoard;
  }
}
