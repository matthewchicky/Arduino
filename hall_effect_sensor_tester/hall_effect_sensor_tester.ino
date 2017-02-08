int hall = 2;
int LED = 4;

void setup() {
  pinMode(hall,INPUT);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
}

void loop() {
  if (digitalRead(hall) == HIGH) {
    digitalWrite(LED,HIGH);
  }
  else {
    digitalWrite(LED,LOW);
  }
}
