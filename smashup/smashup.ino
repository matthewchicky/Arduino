// Assign I/O Pin Names
const int p1LED = 9;
const int p2LED = 6;
const int p3LED = 5;
const int p4LED = 3;
const int p1Button = 8;
const int p2Button = 7;
const int p3Button = 4;
const int p4Button = 2;
const int redActivatedLED = 10;
const int greenActivatedLED = 11;
const int activatedButton = 12;
const int computerTypeToggler = 13;

// Create Button State Variables
boolean p1LastButton = 0;
boolean p1CurrentButton = 0;
boolean p2LastButton = 0;
boolean p2CurrentButton = 0;
boolean p3LastButton = 0;
boolean p3CurrentButton = 0;
boolean p4LastButton = 0;
boolean p4CurrentButton = 0;
boolean activatedLastButton = 0;
boolean activatedCurrentButton = 0;

boolean computerType = 0;  // 0 corresponds to Windows OS, 1 to OSX
boolean activated = 0;
boolean musicPlaying = 0;
boolean p1 = 0;
boolean p2 = 0;
boolean p3 = 0;
boolean p4 = 0;

int playerCombination = 0;
int it = 0;

void setup() {

  // Set I/O Pin Modes
  pinMode(p1LED, OUTPUT);
  pinMode(p2LED, OUTPUT);
  pinMode(p3LED, OUTPUT);
  pinMode(p4LED, OUTPUT);
  pinMode(p1Button, INPUT);
  pinMode(p2Button, INPUT);
  pinMode(p3Button, INPUT);
  pinMode(p4Button, INPUT);
  pinMode(redActivatedLED, OUTPUT);
  pinMode(greenActivatedLED, OUTPUT);
  pinMode(activatedButton, INPUT);
  pinMode(computerTypeToggler, INPUT_PULLUP);

  // Activate Keyboard Emulation
  Keyboard.begin();

}

boolean debounce(boolean last, int BUTTON)
{
  boolean current = digitalRead(BUTTON);       //Read the button state
  if (last != current)                         //if it's different…
  {
    delay(5);                                  //wait 5ms
    current = digitalRead(BUTTON);             //read it again
  }
  return current;                              //return the current value
}

void loop() {

  while (!activated) {   //while waiting in menu

    if (digitalRead(computerTypeToggler) == LOW)
    {
      computerType = !computerType;

      digitalWrite(p1LED, LOW);
      digitalWrite(p2LED, LOW);
      digitalWrite(p3LED, LOW);
      digitalWrite(p4LED, LOW);

      if (computerType == 0)
      {
        for (int i = 1; i < 4; i++)
        {
          digitalWrite(p1LED, HIGH);
          delay(250);
          digitalWrite(p1LED, LOW);
          analogWrite(p2LED, 20);
          delay(250);
          digitalWrite(p2LED, LOW);
          digitalWrite(p3LED, HIGH);
          delay(250);
          digitalWrite(p3LED, LOW);
          digitalWrite(p4LED, HIGH);
          delay(250);
          digitalWrite(p4LED, LOW);
        }
      }
      else if (computerType == 1)
      {
        for (int i = 1; i < 4; i++)
        {
          digitalWrite(p1LED, HIGH);
          digitalWrite(p3LED, HIGH);
          delay(500);
          digitalWrite(p1LED, LOW);
          digitalWrite(p3LED, LOW);
          analogWrite(p2LED, 20);
          digitalWrite(p4LED, HIGH);
          delay(500);
          digitalWrite(p2LED, LOW);
          digitalWrite(p4LED, LOW);
        }
      }
    }

    if (p1 && p2 && p3 && p4) {
      digitalWrite(p1LED, HIGH);
      analogWrite(p2LED, 20);
      digitalWrite(p3LED, HIGH);
      digitalWrite(p4LED, HIGH);
    }
    else if (p1 && p2 && p3 && !p4) {
      digitalWrite(p1LED, HIGH);
      analogWrite(p2LED, 20);
      digitalWrite(p3LED, HIGH);
    }
    else if (!p1 && p2 && p3 && p4) {
      analogWrite(p2LED, 20);
      digitalWrite(p3LED, HIGH);
      digitalWrite(p4LED, HIGH);
    }
    else if (p1 && !p2 && p3 && p4) {
      digitalWrite(p1LED, HIGH);
      digitalWrite(p3LED, HIGH);
      digitalWrite(p4LED, HIGH);
    }
    else if (p1 && p2 && !p3 && p4) {
      digitalWrite(p1LED, HIGH);
      analogWrite(p2LED, 20);
      digitalWrite(p4LED, HIGH);
    }
    else if (p1 && p2 && !p3 && !p4) {
      digitalWrite(p1LED, HIGH);
      analogWrite(p2LED, 20);
    }
    else if (!p1 && p2 && p3 && !p4) {
      analogWrite(p2LED, 20);
      digitalWrite(p3LED, HIGH);
    }
    else if (!p1 && !p2 && p3 && p4) {
      digitalWrite(p3LED, HIGH);
      digitalWrite(p4LED, HIGH);
    }
    else if (p1 && !p2 && !p3 && p4) {
      digitalWrite(p1LED, HIGH);
      digitalWrite(p4LED, HIGH);
    }
    else if (p1 && !p2 && p3 && !p4) {
      digitalWrite(p1LED, HIGH);
      digitalWrite(p3LED, HIGH);
    }
    else if (!p1 && p2 && !p3 && p4) {
      analogWrite(p2LED, 20);
      digitalWrite(p4LED, HIGH);
    }

    playerCombination = 0;
    it = 0;
    digitalWrite(redActivatedLED, !activated);

    // toggle activated if activatedButton has been pressed
    activatedCurrentButton = debounce(activatedLastButton, activatedButton);
    if (activatedLastButton == LOW && activatedCurrentButton == HIGH)
    {
      activated = !activated;
      digitalWrite(greenActivatedLED, activated);
      digitalWrite(redActivatedLED, !activated);
    }
    activatedLastButton = activatedCurrentButton;

    // toggle p1 if p1Button has been pressed
    p1CurrentButton = debounce(p1LastButton, p1Button);
    if (p1LastButton == LOW && p1CurrentButton == HIGH)
    {
      p1 = !p1;
      digitalWrite(p1LED, p1);
    }
    p1LastButton = p1CurrentButton;

    // toggle p2 if p2Button has been pressed
    p2CurrentButton = debounce(p2LastButton, p2Button);
    if (p2LastButton == LOW && p2CurrentButton == HIGH)
    {
      p2 = !p2;
      digitalWrite(p2LED, p2);
    }
    p2LastButton = p2CurrentButton;

    // toggle p3 if p3Button has been pressed
    p3CurrentButton = debounce(p3LastButton, p3Button);
    if (p3LastButton == LOW && p3CurrentButton == HIGH)
    {
      p3 = !p3;
      digitalWrite(p3LED, p3);
    }
    p3LastButton = p3CurrentButton;

    // toggle p4 if p4Button has been pressed
    p4CurrentButton = debounce(p4LastButton, p4Button);
    if (p4LastButton == LOW && p4CurrentButton == HIGH)
    {
      p4 = !p4;
      digitalWrite(p4LED, p4);
    }
    p4LastButton = p4CurrentButton;

  }

  digitalWrite(p1LED, LOW);
  digitalWrite(p2LED, LOW);
  digitalWrite(p3LED, LOW);
  digitalWrite(p4LED, LOW);

  //  int val = 0;
  //  boolean equalize = 0;
  //
  //  int minutes = 0;
  //  int ten_sec = 0;
  //  int five_sec = 0;
  //  int one_sec = 0;
  //
  //  while (val <= 350)
  //  {
  //    activatedCurrentButton = debounce(activatedLastButton, activatedButton);
  //    if (activatedLastButton == LOW && activatedCurrentButton == HIGH)
  //    {
  //      equalize = 1;
  //    }
  //    activatedLastButton = activatedCurrentButton;
  //
  //    delay(1);
  //    val = val + 1;
  //  }
  //
  //  while (activated && equalize)
  //  {
  //    if (minutes == 11)  {
  //      minutes = 0;
  //    }
  //    if (ten_sec == 6)  {
  //      ten_sec = 0;
  //    }
  //    if (five_sec == 2)  {
  //      five_sec = 0;
  //    }
  //    if (one_sec == 5)  {
  //      one_sec = 0;
  //    }
  //
  //    analogWrite(p1LED, (25 * minutes));
  //    analogWrite(p2LED, (50 * ten_sec));
  //    analogWrite(p3LED, (250 * five_sec));
  //    analogWrite(p4LED, (63 * one_sec));
  //
  //    p1CurrentButton = debounce(p1LastButton, p1Button);
  //    if (p1LastButton == LOW && p1CurrentButton == HIGH)
  //    {
  //      minutes = minutes + 1;
  //    }
  //    p1LastButton = p1CurrentButton;
  //
  //    p2CurrentButton = debounce(p2LastButton, p2Button);
  //    if (p2LastButton == LOW && p2CurrentButton == HIGH)
  //    {
  //      ten_sec = ten_sec + 1;
  //    }
  //    p2LastButton = p2CurrentButton;
  //
  //    p3CurrentButton = debounce(p3LastButton, p3Button);
  //    if (p3LastButton == LOW && p3CurrentButton == HIGH)
  //    {
  //      five_sec = five_sec + 1;
  //    }
  //    p3LastButton = p3CurrentButton;
  //
  //    p4CurrentButton = debounce(p4LastButton, p4Button);
  //    if (p4LastButton == LOW && p4CurrentButton == HIGH)
  //    {
  //      one_sec = one_sec + 1;
  //    }
  //    p4LastButton = p4CurrentButton;
  //
  //    int number_intervals = ((60 * minutes) + (10 * ten_sec) + (5 * five_sec)) / 5;
  //
  //    activatedCurrentButton = debounce(activatedLastButton, activatedButton);
  //    if (activatedLastButton == LOW && activatedCurrentButton == HIGH)
  //    {
  //      // Turn off LEDs
  //      digitalWrite(p1LED, LOW);
  //      digitalWrite(p2LED, LOW);
  //      digitalWrite(p3LED, LOW);
  //      digitalWrite(p4LED, LOW);
  //
  //      // Equalize Song Lengths
  //      if (p1)  {      // P1 Song Equalization
  //
  //        if (computerType == 1)  {
  //          Keyboard.press(KEY_LEFT_GUI);
  //        }
  //        else  {
  //          Keyboard.press(KEY_LEFT_CTRL);
  //        }
  //
  //        Keyboard.press('1');
  //        Keyboard.releaseAll();
  //        delay(250);
  //        Keyboard.press('9');
  //        Keyboard.release('9');
  //
  //        for (int i = 1; i < 13; i++)  {
  //          Keyboard.press(KEY_RIGHT_ARROW);
  //          Keyboard.release(KEY_RIGHT_ARROW);
  //          delay(50);
  //        }
  //
  //        for (int i = 1; i <= number_intervals; i++)  {
  //          Keyboard.press(KEY_LEFT_ARROW);
  //          Keyboard.release(KEY_LEFT_ARROW);
  //          delay(50);
  //        }
  //
  //        Keyboard.press('k');
  //        Keyboard.release('k');
  //        delay(50);
  //
  //      }
  //
  //      if (p2)  {      // P2 Song Equalization
  //
  //        if (computerType == 1)  {
  //          Keyboard.press(KEY_LEFT_GUI);
  //        }
  //        else  {
  //          Keyboard.press(KEY_LEFT_CTRL);
  //        }
  //
  //        Keyboard.press('2');
  //        Keyboard.releaseAll();
  //        delay(250);
  //        Keyboard.press('9');
  //        Keyboard.release('9');
  //
  //        for (int i = 1; i < 13; i++)  {
  //          Keyboard.press(KEY_RIGHT_ARROW);
  //          Keyboard.release(KEY_RIGHT_ARROW);
  //          delay(50);
  //        }
  //
  //        for (int i = 1; i <= number_intervals; i++)  {
  //          Keyboard.press(KEY_LEFT_ARROW);
  //          Keyboard.release(KEY_LEFT_ARROW);
  //          delay(50);
  //        }
  //
  //        Keyboard.press('k');
  //        Keyboard.release('k');
  //        delay(50);
  //
  //      }
  //
  //      if (p3)  {      // P3 Song Equalization
  //
  //        if (computerType == 1)  {
  //          Keyboard.press(KEY_LEFT_GUI);
  //        }
  //        else  {
  //          Keyboard.press(KEY_LEFT_CTRL);
  //        }
  //
  //        Keyboard.press('3');
  //        Keyboard.releaseAll();
  //        delay(250);
  //        Keyboard.press('9');
  //        Keyboard.release('9');
  //
  //        for (int i = 1; i < 13; i++)  {
  //          Keyboard.press(KEY_RIGHT_ARROW);
  //          Keyboard.release(KEY_RIGHT_ARROW);
  //          delay(50);
  //        }
  //
  //        for (int i = 1; i <= number_intervals; i++)  {
  //          Keyboard.press(KEY_LEFT_ARROW);
  //          Keyboard.release(KEY_LEFT_ARROW);
  //          delay(50);
  //        }
  //
  //        Keyboard.press('k');
  //        Keyboard.release('k');
  //        delay(50);
  //
  //      }
  //
  //      if (p4)  {      // P4 Song Equalization
  //
  //        if (computerType == 1)  {
  //          Keyboard.press(KEY_LEFT_GUI);
  //        }
  //        else  {
  //          Keyboard.press(KEY_LEFT_CTRL);
  //        }
  //
  //        Keyboard.press('4');
  //        Keyboard.releaseAll();
  //        delay(250);
  //        Keyboard.press('9');
  //        Keyboard.release('9');
  //
  //        for (int i = 1; i < 13; i++)  {
  //          Keyboard.press(KEY_RIGHT_ARROW);
  //          Keyboard.release(KEY_RIGHT_ARROW);
  //          delay(50);
  //        }
  //
  //        for (int i = 1; i <= number_intervals; i++)  {
  //          Keyboard.press(KEY_LEFT_ARROW);
  //          Keyboard.release(KEY_LEFT_ARROW);
  //          delay(50);
  //        }
  //
  //        Keyboard.press('k');
  //        Keyboard.release('k');
  //        delay(50);
  //
  //      }
  //
  //      equalize = 0;
  //      Keyboard.releaseAll();
  //
  //    }
  //    activatedLastButton = activatedCurrentButton;

  if (p1 && p2 && p3 && p4) {  // 1
    playerCombination = 1;
    for (int i = 1; i < 4; i++) {
      digitalWrite(p1LED, LOW);
      digitalWrite(p2LED, LOW);
      digitalWrite(p3LED, LOW);
      digitalWrite(p4LED, LOW);
      delay(250);
      digitalWrite(p1LED, HIGH);
      analogWrite(p2LED, 20);
      digitalWrite(p3LED, HIGH);
      digitalWrite(p4LED, HIGH);
      delay(250);
    }
  }
  else if (p1 && p2 && p3 && !p4) {  // 2
    playerCombination = 2;
    for (int i = 1; i < 4; i++) {
      digitalWrite(p1LED, LOW);
      digitalWrite(p2LED, LOW);
      digitalWrite(p3LED, LOW);
      delay(250);
      digitalWrite(p1LED, HIGH);
      analogWrite(p2LED, 20);
      digitalWrite(p3LED, HIGH);
      delay(250);
    }
  }
  else if (!p1 && p2 && p3 && p4) {  // 3
    playerCombination = 3;
    for (int i = 1; i < 4; i++) {
      digitalWrite(p2LED, LOW);
      digitalWrite(p3LED, LOW);
      digitalWrite(p4LED, LOW);
      delay(250);
      analogWrite(p2LED, 20);
      digitalWrite(p3LED, HIGH);
      digitalWrite(p4LED, HIGH);
      delay(250);
    }
  }
  else if (p1 && !p2 && p3 && p4) {  // 4
    playerCombination = 4;
    for (int i = 1; i < 4; i++) {
      digitalWrite(p1LED, LOW);
      digitalWrite(p3LED, LOW);
      digitalWrite(p4LED, LOW);
      delay(250);
      digitalWrite(p1LED, HIGH);
      digitalWrite(p3LED, HIGH);
      digitalWrite(p4LED, HIGH);
      delay(250);
    }
  }
  else if (p1 && p2 && !p3 && p4) {  // 5
    playerCombination = 5;
    for (int i = 1; i < 4; i++) {
      digitalWrite(p1LED, LOW);
      digitalWrite(p2LED, LOW);
      digitalWrite(p4LED, LOW);
      delay(250);
      digitalWrite(p1LED, HIGH);
      analogWrite(p2LED, 20);
      digitalWrite(p4LED, HIGH);
      delay(250);
    }
  }
  else if (p1 && p2 && !p3 && !p4) {  // 6
    playerCombination = 6;
    for (int i = 1; i < 4; i++) {
      digitalWrite(p1LED, LOW);
      digitalWrite(p2LED, LOW);
      delay(250);
      digitalWrite(p1LED, HIGH);
      analogWrite(p2LED, 20);
      delay(250);
    }
  }
  else if (!p1 && p2 && p3 && !p4) {  // 7
    playerCombination = 7;
    for (int i = 1; i < 4; i++) {
      digitalWrite(p2LED, LOW);
      digitalWrite(p3LED, LOW);
      delay(250);
      analogWrite(p2LED, 20);
      digitalWrite(p3LED, HIGH);
      delay(250);
    }
  }
  else if (!p1 && !p2 && p3 && p4) {  // 8
    playerCombination = 8;
    for (int i = 1; i < 4; i++) {
      digitalWrite(p3LED, LOW);
      digitalWrite(p4LED, LOW);
      delay(250);
      digitalWrite(p3LED, HIGH);
      digitalWrite(p4LED, HIGH);
      delay(250);
    }
  }
  else if (p1 && !p2 && !p3 && p4) {  // 9
    playerCombination = 9;
    for (int i = 1; i < 4; i++) {
      digitalWrite(p1LED, LOW);
      digitalWrite(p4LED, LOW);
      delay(250);
      digitalWrite(p1LED, HIGH);
      digitalWrite(p4LED, HIGH);
      delay(250);
    }
  }
  else if (p1 && !p2 && p3 && !p4) {  // 10
    playerCombination = 10;
    for (int i = 1; i < 4; i++) {
      digitalWrite(p1LED, LOW);
      digitalWrite(p3LED, LOW);
      delay(250);
      digitalWrite(p1LED, HIGH);
      digitalWrite(p3LED, HIGH);
      delay(250);
    }
  }
  else if (!p1 && p2 && !p3 && p4) {  // 11
    playerCombination = 11;
    for (int i = 1; i < 4; i++) {
      digitalWrite(p2LED, LOW);
      digitalWrite(p4LED, LOW);
      delay(250);
      analogWrite(p2LED, 20);
      digitalWrite(p4LED, HIGH);
      delay(250);
    }
  }


  while (activated) {   //while the game is being played

    // toggle activated if activatedButton has been pressed
    activatedCurrentButton = debounce(activatedLastButton, activatedButton);
    if (activatedLastButton == LOW && activatedCurrentButton == HIGH)
    {
      activated = !activated;
      digitalWrite(redActivatedLED, !activated);
      digitalWrite(greenActivatedLED, activated);
    }
    activatedLastButton = activatedCurrentButton;

    // play p1 music if p1Button has been pressed
    p1CurrentButton = debounce(p1LastButton, p1Button);
    if ((p1LastButton == LOW && p1CurrentButton == HIGH) && (playerCombination == 1 || playerCombination == 2 || playerCombination == 4 || playerCombination == 5 || playerCombination == 6 || playerCombination == 9 || playerCombination == 10))
    {
      it = 1;
      digitalWrite(p1LED, p1);
      digitalWrite(p2LED, !p1);
      digitalWrite(p3LED, !p1);
      digitalWrite(p4LED, !p1);

      if (computerType == 1)
      {
        Keyboard.press(KEY_LEFT_GUI);
      }
      else
      {
        Keyboard.press(KEY_LEFT_CTRL);
      }

      // Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('1');
      Keyboard.releaseAll();
      delay(50);
      Keyboard.press('k');
      Keyboard.release('k');
      musicPlaying = 1;
    }
    p1LastButton = p1CurrentButton;

    // play p2 music if p2Button has been pressed
    p2CurrentButton = debounce(p2LastButton, p2Button);
    if ((p2LastButton == LOW && p2CurrentButton == HIGH) && (playerCombination == 1 || playerCombination == 2 || playerCombination == 3 || playerCombination == 5 || playerCombination == 6 || playerCombination == 7 || playerCombination == 11))
    {
      it = 2;
      digitalWrite(p1LED, !p2);
      digitalWrite(p2LED, p2);
      digitalWrite(p3LED, !p2);
      digitalWrite(p4LED, !p2);

      if (computerType == 1)
      {
        Keyboard.press(KEY_LEFT_GUI);
      }
      else
      {
        Keyboard.press(KEY_LEFT_CTRL);
      }

      // Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('2');
      Keyboard.releaseAll();
      delay(50);
      Keyboard.press('k');
      Keyboard.release('k');
      musicPlaying = 1;
    }
    p2LastButton = p2CurrentButton;

    // play p3 music if p3Button has been pressed
    p3CurrentButton = debounce(p3LastButton, p3Button);
    if ((p3LastButton == LOW && p3CurrentButton == HIGH) && (playerCombination == 1 || playerCombination == 2 || playerCombination == 3 || playerCombination == 4 || playerCombination == 7 || playerCombination == 8 || playerCombination == 10))
    {
      it = 3;
      digitalWrite(p1LED, !p3);
      digitalWrite(p2LED, !p3);
      digitalWrite(p3LED, p3);
      digitalWrite(p4LED, !p3);

      if (computerType == 1)
      {
        Keyboard.press(KEY_LEFT_GUI);
      }
      else
      {
        Keyboard.press(KEY_LEFT_CTRL);
      }

      // Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('3');
      Keyboard.releaseAll();
      delay(50);
      Keyboard.press('k');
      Keyboard.release('k');
      musicPlaying = 1;
    }
    p3LastButton = p3CurrentButton;

    // play p4 music if p4Button has been pressed
    p4CurrentButton = debounce(p4LastButton, p4Button);
    if ((p4LastButton == LOW && p4CurrentButton == HIGH) && (playerCombination == 1 || playerCombination == 3 || playerCombination == 4 || playerCombination == 5 || playerCombination == 8 || playerCombination == 9 || playerCombination == 11))
    {
      it = 4;
      digitalWrite(p1LED, !p4);
      digitalWrite(p2LED, !p4);
      digitalWrite(p3LED, !p4);
      digitalWrite(p4LED, p4);

      if (computerType == 1)
      {
        Keyboard.press(KEY_LEFT_GUI);
      }
      else
      {
        Keyboard.press(KEY_LEFT_CTRL);
      }

      // Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('4');
      Keyboard.releaseAll();
      delay(50);
      Keyboard.press('k');
      Keyboard.release('k');
      musicPlaying = 1;
    }
    p4LastButton = p4CurrentButton;

    while (musicPlaying) {

      // toggle activated if activatedButton has been pressed
      activatedCurrentButton = debounce(activatedLastButton, activatedButton);
      if (activatedLastButton == LOW && activatedCurrentButton == HIGH)
      {
        activated = 0;
        musicPlaying = 0;
        digitalWrite(redActivatedLED, !activated);
        digitalWrite(greenActivatedLED, activated);

        if (it == 1)
        {
          if (computerType == 1)
          {
            Keyboard.press(KEY_LEFT_GUI);
          }
          else
          {
            Keyboard.press(KEY_LEFT_CTRL);
          }

          // Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('1');
          Keyboard.releaseAll();
          delay(50);
          Keyboard.press('k');
          Keyboard.release('k');
        }

        else if (it == 2)
        {
          if (computerType == 1)
          {
            Keyboard.press(KEY_LEFT_GUI);
          }
          else
          {
            Keyboard.press(KEY_LEFT_CTRL);
          }

          // Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('2');
          Keyboard.releaseAll();
          delay(50);
          Keyboard.press('k');
          Keyboard.release('k');
        }

        else if (it == 3)
        {
          if (computerType == 1)
          {
            Keyboard.press(KEY_LEFT_GUI);
          }
          else
          {
            Keyboard.press(KEY_LEFT_CTRL);
          }

          // Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('3');
          Keyboard.releaseAll();
          delay(50);
          Keyboard.press('k');
          Keyboard.release('k');
        }

        else if (it == 4)
        {
          if (computerType == 1)
          {
            Keyboard.press(KEY_LEFT_GUI);
          }
          else
          {
            Keyboard.press(KEY_LEFT_CTRL);
          }

          // Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('4');
          Keyboard.releaseAll();
          delay(50);
          Keyboard.press('k');
          Keyboard.release('k');
        }
      }

      activatedLastButton = activatedCurrentButton;

      // play/pause p1 music if p1Button has been pressed
      p1CurrentButton = debounce(p1LastButton, p1Button);
      if ((p1LastButton == LOW && p1CurrentButton == HIGH) && (playerCombination == 1 || playerCombination == 2 || playerCombination == 4 || playerCombination == 5 || playerCombination == 6 || playerCombination == 9 || playerCombination == 10))
      {
        if (it == 1) {
          it = 0;
          digitalWrite(p1LED, !p1);

          Keyboard.press('k');
          Keyboard.release('k');
          musicPlaying = 0;
        }
        else {
          it = 1;
          digitalWrite(p1LED, p1);
          digitalWrite(p2LED, !p1);
          digitalWrite(p3LED, !p1);
          digitalWrite(p4LED, !p1);

          Keyboard.press('k');
          Keyboard.release('k');
          delay(50);

          if (computerType == 1)
          {
            Keyboard.press(KEY_LEFT_GUI);
          }
          else
          {
            Keyboard.press(KEY_LEFT_CTRL);
          }

          // Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('1');
          Keyboard.releaseAll();
          delay(50);
          Keyboard.press('k');
          Keyboard.release('k');
        }
      }

      p1LastButton = p1CurrentButton;

      // play/pause p2 music if p2Button has been pressed
      p2CurrentButton = debounce(p2LastButton, p2Button);
      if ((p2LastButton == LOW && p2CurrentButton == HIGH) && (playerCombination == 1 || playerCombination == 2 || playerCombination == 3 || playerCombination == 5 || playerCombination == 6 || playerCombination == 7 || playerCombination == 11))
      {
        if (it == 2) {
          it = 0;
          digitalWrite(p2LED, !p2);

          Keyboard.press('k');
          Keyboard.release('k');
          musicPlaying = 0;
        }
        else {
          it = 2;
          digitalWrite(p1LED, !p2);
          digitalWrite(p2LED, p2);
          digitalWrite(p3LED, !p2);
          digitalWrite(p4LED, !p2);

          Keyboard.press('k');
          Keyboard.release('k');
          delay(50);

          if (computerType == 1)
          {
            Keyboard.press(KEY_LEFT_GUI);
          }
          else
          {
            Keyboard.press(KEY_LEFT_CTRL);
          }

          // Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('2');
          Keyboard.releaseAll();
          delay(50);
          Keyboard.press('k');
          Keyboard.release('k');
        }
      }

      p2LastButton = p2CurrentButton;

      // play/pause p3 music if p3Button has been pressed
      p3CurrentButton = debounce(p3LastButton, p3Button);
      if ((p3LastButton == LOW && p3CurrentButton == HIGH) && (playerCombination == 1 || playerCombination == 2 || playerCombination == 3 || playerCombination == 4 || playerCombination == 7 || playerCombination == 8 || playerCombination == 10))
      {
        if (it == 3) {
          it = 0;
          digitalWrite(p3LED, !p3);

          Keyboard.press('k');
          Keyboard.release('k');
          musicPlaying = 0;
        }
        else {
          it = 3;
          digitalWrite(p1LED, !p3);
          digitalWrite(p2LED, !p3);
          digitalWrite(p3LED, p3);
          digitalWrite(p4LED, !p3);

          Keyboard.press('k');
          Keyboard.release('k');
          delay(50);

          if (computerType == 1)
          {
            Keyboard.press(KEY_LEFT_GUI);
          }
          else
          {
            Keyboard.press(KEY_LEFT_CTRL);
          }

          // Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('3');
          Keyboard.releaseAll();
          delay(50);
          Keyboard.press('k');
          Keyboard.release('k');
        }
      }
      p3LastButton = p3CurrentButton;

      // play/pause p4 music if p4Button has been pressed
      p4CurrentButton = debounce(p4LastButton, p4Button);
      if ((p4LastButton == LOW && p4CurrentButton == HIGH) && (playerCombination == 1 || playerCombination == 3 || playerCombination == 4 || playerCombination == 5 || playerCombination == 8 || playerCombination == 9 || playerCombination == 11))
      {
        if (it == 4) {
          it = 0;
          digitalWrite(p4LED, !p4);

          Keyboard.press('k');
          Keyboard.release('k');
          musicPlaying = 0;
        }
        else {
          it = 4;
          digitalWrite(p1LED, !p4);
          digitalWrite(p2LED, !p4);
          digitalWrite(p3LED, !p4);
          digitalWrite(p4LED, p4);

          Keyboard.press('k');
          Keyboard.release('k');
          delay(50);

          if (computerType == 1)
          {
            Keyboard.press(KEY_LEFT_GUI);
          }
          else
          {
            Keyboard.press(KEY_LEFT_CTRL);
          }

          // Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('4');
          Keyboard.releaseAll();
          delay(50);
          Keyboard.press('k');
          Keyboard.release('k');
        }
      }
      p4LastButton = p4CurrentButton;

    }
  }
}
