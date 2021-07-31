#include "buttonDebounce.h"

#define ledDelay 300

int arrayCount = 0;
int rows[49];
int cols[49];

unsigned long patternTimer;

enum heartStates {all, off, pulse, text1, text2, secret};
heartStates heartState = off;


void addLed(int row, int col) { //add LED to LED array
    if (row <= 7 && col <= 7) {
      rows[arrayCount] = row;
      cols[arrayCount] = col;
      arrayCount++;
    }
}

void turnOnLed(int row, int col) { //turn LEDs on via port manipulation
  PORTB = 0xFF;
  PORTC = 0x0;
  PORTD = 0xFF;
  
  switch(row) { //grounds
    case 1: //pin D5
      PORTD = ~0x20;  
      break;
    case 2: //pin D6
      PORTD = ~0x40;
      break;
    case 3: //pin D7
      PORTD = ~0x80;
      break;
    case 4: //pin D8
      PORTB = ~0x11; //add 0x1 for PORTB to keep pin D12 low
      break;
    case 5: //pin D9
      PORTB = ~0x12;
      break;
    case 6: //pin D10
      PORTB = ~0x14;
      break;
    case 7: //pin D11
      PORTB = ~0x18;
      break;
  }
  
  switch(col) { //5V
    case 1: //pin D12
      PORTB |= 0x10;
      break;
    case 2: //pin A0
      PORTC |= 0x01;
      break;
    case 3: //pin A1
      PORTC |= 0x02;
      break;
    case 4: //pin A2
      PORTC |= 0x04;
      break;
    case 5: //pin A3
      PORTC |= 0x08;
      break;
    case 6: //pin A4
      PORTC |= 0x10;
      break;
    case 7: //pin A5
      PORTC |= 0x20;
      break;
  }
} //end of turnOnLed

void handleArray() { //run through array and call turnOnLed
  for (int i = 0; i < arrayCount; i++) {
    turnOnLed(rows[i], cols[i]);
    delayMicroseconds(ledDelay);
  }
}

void initializePins() { //sets pinMode for each pin
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
}

void allOn() {
  for (int i = 1; i <= 7; i++) {
    for (int j = 1; j <= 7; j++) {
      addLed(i,j);
    }
  }
}

void allOff() {
  //memset(rows, 0, sizeof(rows));
  //memset(cols, 0, sizeof(rows)); //memset seems to be too slow
  arrayCount = 0;
  PORTB = 0xFF;
  PORTC = 0x0;
  PORTD = 0xFF;
}

unsigned long testTimer;

void pulsate() {
  testTimer = millis();
  if (testTimer - patternTimer >= 800) {
    allOff();
    patternTimer = millis();
  }
  if (testTimer - patternTimer <= 100 || testTimer - patternTimer >= 700) {
    allOff();
    addLed(4,4); //addLed(row,col)
  }
  else if (testTimer - patternTimer <= 200 || testTimer - patternTimer >= 600) {
    allOff();
    addLed(4,3);
    addLed(4,5);
    addLed(3,4);
    addLed(5,4);
    addLed(5,3);
    addLed(5,5);
    
  }
  else if (testTimer - patternTimer <= 300 || testTimer - patternTimer >= 500) {
    allOff();
    addLed(2,4);
    addLed(4,6);
    addLed(4,2);
    addLed(3,3);
    addLed(3,5);
    addLed(5,2);
    addLed(5,6);
    addLed(6,3);
    addLed(6,5);
    addLed(6,2);
    addLed(6,6);
  }
  else if (testTimer - patternTimer <= 400) {
    allOff();
    addLed(1,4);
    addLed(2,3);
    addLed(2,5);
    addLed(3,2);
    addLed(3,6);
    addLed(4,1);
    addLed(4,7);
    addLed(5,1);
    addLed(5,7);
    addLed(6,4);
    addLed(6,1);
    addLed(6,7);
    addLed(7,2);
    addLed(7,3);
    addLed(7,5);
    addLed(7,6);
  }
} // end of pulsate


void letterDefinition(char letter) {
  switch (letter) {
    case 'A':
      addLed(2,3);
      addLed(3,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(6,4);
      addLed(4,4);
      addLed(2,5);
      addLed(3,5);
      addLed(4,5);
      addLed(5,5);
      addLed(6,5);
      break;
    case 'B':
      addLed(2,3);
      addLed(3,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(6,4);
      addLed(4,4);
      addLed(2,4);
      addLed(2,5);
      addLed(3,5);
      addLed(5,5);
      addLed(6,5);
      break;
    case 'C':
      addLed(2,3);
      addLed(3,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(6,4);
      addLed(2,4);
      addLed(2,5);
      addLed(6,5);
      break;
    case 'D':
      addLed(2,3);
      addLed(3,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(6,4);
      addLed(2,4);
      addLed(3,5);
      addLed(4,5);
      addLed(5,5);
      break;
    case 'E':
      addLed(2,3);
      addLed(3,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(6,4);
      addLed(4,4);
      addLed(2,4);
      addLed(2,5);
      addLed(4,5);
      addLed(6,5);
      break;
    case 'F':
      addLed(2,3);
      addLed(3,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(6,4);
      addLed(4,4);
      addLed(4,5);
      addLed(6,5);
      break;
    case 'G':
      addLed(2,3);
      addLed(3,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(6,4);
      addLed(2,4);
      addLed(2,5);
      addLed(3,5);
      addLed(4,5);
      addLed(6,5);
      break;
    case 'H':
      addLed(2,3);
      addLed(3,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(4,4);
      addLed(2,5);
      addLed(3,5);
      addLed(4,5);
      addLed(5,5);
      addLed(6,5);
      break;
    case 'I':
      addLed(2,3);
      addLed(6,3);
      addLed(2,4);
      addLed(3,4);
      addLed(4,4);
      addLed(5,4);
      addLed(6,4);
      addLed(2,5);
      addLed(6,5);
      break;
    case 'J':
      addLed(2,3);
      addLed(3,3);
      addLed(2,4); 
      addLed(2,5);
      addLed(3,5);
      addLed(4,5);
      addLed(5,5);
      addLed(6,5);
      break;
    case 'K':
      addLed(2,3);
      addLed(3,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(4,4);
      addLed(2,5);
      addLed(3,5);
      addLed(5,5);
      addLed(6,5);
      break;
    case 'L':
      addLed(2,3);
      addLed(3,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(2,4);
      addLed(2,5);
      break;
    case 'M':
      addLed(3,2);
      addLed(4,2);
      addLed(5,2);
      addLed(6,2);
      addLed(5,3);
      addLed(4,4);
      addLed(5,5);
      addLed(3,6);
      addLed(4,6);
      addLed(5,6);
      addLed(6,6);
      break;
    case 'N':
      addLed(3,2);
      addLed(4,2);
      addLed(5,2);
      addLed(6,2);
      addLed(6,3);
      addLed(5,4);
      addLed(4,5);
      addLed(3,6);
      addLed(4,6);
      addLed(5,6);
      addLed(6,6);
      break;
    case 'O':
      addLed(2,3);
      addLed(3,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(6,4);
      addLed(2,4);
      addLed(2,5);
      addLed(3,5);
      addLed(4,5);
      addLed(5,5);
      addLed(6,5);
      break;
    case 'P':
      addLed(2,3);
      addLed(3,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(6,4);
      addLed(4,4);
      addLed(4,5);
      addLed(5,5);
      addLed(6,5);
      break;
    case 'Q':
      break; // probs won't use
    case 'R':
      addLed(2,3);
      addLed(3,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(6,4);
      addLed(4,4);
      addLed(2,5);
      addLed(3,5);
      addLed(5,5);
      addLed(6,5);
      break;
    case 'S':
      addLed(2,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(6,4);
      addLed(4,4);
      addLed(2,4);
      addLed(2,5);
      addLed(3,5);
      addLed(4,5);
      addLed(6,5);
      break;
    case 'T':
      addLed(6,3);
      addLed(2,4);
      addLed(3,4);
      addLed(4,4);
      addLed(5,4);
      addLed(6,4);
      addLed(6,5);
      break;
    case 'U':
      addLed(2,3);
      addLed(3,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(2,4);
      addLed(2,5);
      addLed(3,5);
      addLed(4,5);
      addLed(5,5);
      addLed(6,5);
      break;
    case 'V':
      addLed(3,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(2,4);
      addLed(3,5);
      addLed(4,5);
      addLed(5,5);
      addLed(6,5);
      break;
    case 'W':
      addLed(3,2);
      addLed(4,2);
      addLed(5,2);
      addLed(6,2);
      addLed(4,3);
      addLed(5,4);
      addLed(4,5);
      addLed(3,6);
      addLed(4,6);
      addLed(5,6);
      addLed(6,6);
      break;
    case 'X':
      break; // probs won't use
    case 'Y':
      addLed(5,3);
      addLed(6,3);
      addLed(2,4);
      addLed(3,4);
      addLed(4,4);
      addLed(5,5);
      addLed(6,5);
      break;
    case 'Z':
      break; // probs won't use
    case '0':
      addLed(2,3);
      addLed(3,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(6,4);
      addLed(2,4);
      addLed(2,5);
      addLed(3,5);
      addLed(4,5);
      addLed(5,5);
      addLed(6,5);
      break;
    case '1':
      addLed(2,3);
      addLed(6,3);
      addLed(2,4);
      addLed(3,4);
      addLed(4,4);
      addLed(5,4);
      addLed(6,4);
      addLed(2,5);
      break;
    case '2':
      addLed(2,3);
      addLed(3,3);
      addLed(4,3);
      addLed(6,3);
      addLed(6,4);
      addLed(4,4);
      addLed(2,4);
      addLed(2,5);
      addLed(4,5);
      addLed(5,5);
      addLed(6,5);
      break;
    case '3':
      addLed(2,3);
      addLed(4,3);
      addLed(6,3);
      addLed(6,4);
      addLed(4,4);
      addLed(2,4);
      addLed(2,5);
      addLed(3,5);
      addLed(4,5);
      addLed(5,5);
      addLed(6,5);
      break;
    case '4':
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(4,4);
      addLed(2,5);
      addLed(3,5);
      addLed(4,5);
      addLed(5,5);
      addLed(6,5);
      break;
    case '5':
      addLed(2,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(6,4);
      addLed(4,4);
      addLed(2,4);
      addLed(2,5);
      addLed(3,5);
      addLed(4,5);
      addLed(6,5);
      break;
    case '6':
      addLed(2,3);
      addLed(3,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(6,4);
      addLed(4,4);
      addLed(2,4);
      addLed(2,5);
      addLed(3,5);
      addLed(4,5);
      addLed(6,5);
      break;
    case '7':
      addLed(6,3);
      addLed(6,4);
      addLed(2,5);
      addLed(3,5);
      addLed(4,5);
      addLed(5,5);
      addLed(6,5);
      break;
    case '8':
      addLed(2,3);
      addLed(3,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(6,4);
      addLed(4,4);
      addLed(2,4);
      addLed(2,5);
      addLed(3,5);
      addLed(4,5);
      addLed(5,5);
      addLed(6,5);
      break;
    case '9':
      addLed(2,3);
      addLed(4,3);
      addLed(5,3);
      addLed(6,3);
      addLed(6,4);
      addLed(4,4);
      addLed(2,4);
      addLed(2,5);
      addLed(3,5);
      addLed(4,5);
      addLed(5,5);
      addLed(6,5);
      break;
    case ' ':
      allOff();
      break;
    case '~': // tilde for heart
      allOn();
      break;
    case '-':
      addLed(4,3);
      addLed(4,4);
      addLed(4,5);
      break;
  } // extend this
}

unsigned long printTimer = 0;
int charCount = 0;
void printText(char string[], int interval) {
  if (millis() - printTimer >= interval && string[charCount] != '#') { // Using # as a delimiter
    allOff();
    letterDefinition(string[charCount]);
    printTimer = millis();
    charCount++;
  }
  else if (string[charCount] == '#') {
    charCount = 0;
    printTimer = millis();
  }
} // end of printText

void stateLoopHandler() {
  switch (heartState) {
    case pulse:
      pulsate();
      break;
    case text1:
      printText("I~U #", 500); //Using # as a delimiter
      break;
    case text2:
      printText("1-15-21 #", 1000);
      break;
    case secret:
      printText("I LOVE YOU FOREVER #", 750);
      break;
  }
}

void stateHandler() {
  switch (heartState) {
    case all:
      allOff();
      allOn();
      break;
    case off:
      allOff();
      break;
    case pulse:
      allOff();
      patternTimer = millis();
      break;
    case text1:
      charCount = 0;
      allOff();
      break;
    case text2:
      charCount = 0;
      allOff();
      break;
  }
}

void incrementState() {
  switch (heartState) {
    case off:
      heartState = all;
      break;
    case all:
      heartState = pulse;
      break;
    case pulse:
      heartState = text1;
      break;
    case text1:
      heartState = text2;
      break;
    case text2:
      heartState = all;
      break;
    case secret:
      heartState = all;
      break;
  }
}

void buttonHandler() {
  switch(ButtonNextState(digitalRead(3))) {
    case 1: //button press
      break;
    case 2: //button release
      incrementState();
      stateHandler();
      break;
    case 3: //long press
      heartState = off;
      stateHandler();
      break;
  }
}

bool hasSecretReset = true;

void secretButton() {
  if (digitalRead(4) == HIGH && hasSecretReset == true) {
    heartState = secret;
    charCount = 0;
    hasSecretReset = false;
  }
  else if (digitalRead(4) == LOW && hasSecretReset == false) {
    hasSecretReset = true;
  }
}
