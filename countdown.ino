void countdown() {
  // this is the countdown ISR
  if(runCountdown == true) {
    digitalWrite(PIN_RELAY,LOW); // turn relay ON
    if(LR == 1){
      currentTime1 = currentTime1 - 1;
      if(currentTime1 <= 0) {
        runCountdown = false;
      }
    }
    else{
      currentTime0 = currentTime0 - 1;
      if( currentTime0 <= 0){
        runCountdown = false;
      }
    }
  }
  if(runCountdown == false && alwaysOn == false) {
    digitalWrite(PIN_RELAY,HIGH); // turn relay OFF
  }
}