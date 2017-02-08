const int LED = 9;

void setup() {
  
  pinMode(LED,OUTPUT);

}

void loop() {
  
  for (int i=10; i<256; i++)
  {
    
    analogWrite(LED, i);
    delay(7);
    
  }
  
  for (int i=255; i>=10; i--)
  {
    
    analogWrite(LED, i);
    delay(7);
    
  }

}
