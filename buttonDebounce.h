// Set up pin and button state.
enum buttonStates {BS_Idle, BS_Wait, BS_Low};
buttonStates buttonState = BS_Idle;
unsigned long buttonTimer;


// Function called in loop to check for button release.
// Returns a 1 on the buttons release.
int ButtonNextState( int Press )
{
  // Read in the buttons current value.
  int ReturnValue = 0;
  switch ( buttonState )
  {
    case BS_Idle: // if we are waiting for a press,
      if ( Press == HIGH )
      {
        // Once press occurs
        buttonTimer = millis();  // record time
        buttonState = BS_Wait;        // and move to next state
      }
      break;
    case BS_Wait: // button just went low
      if ( Press == LOW ) // and now goes high
      {
        buttonState = BS_Idle;  // return to 0 state.
      }
      else // if still low
      {
        // and sufficient time has passed.
        if ( millis() - buttonTimer >= 10 )
        {
          ReturnValue = 1; // Return 1 indicating pressed.
          buttonState = BS_Low; // move on to state two
        }
      }
      break;
    case BS_Low:
      if ( Press == LOW )
      {
        ReturnValue = 2; // Return 2 indicating release.
        if( millis() - buttonTimer >= 500 ) {
            ReturnValue = 3; // Return 3 indicating long press.
        }
        buttonState = BS_Idle;
      } // End of high test.
      break;
  } // End of switch on buttonState

  return ReturnValue;

} // End of ButtonRead
