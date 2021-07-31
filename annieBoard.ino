#include "annieBoard.h"

void setup() {
  
  initializePins();
  
}

void loop() {

  secretButton();
  buttonHandler();
  stateLoopHandler();
  handleArray();

}
