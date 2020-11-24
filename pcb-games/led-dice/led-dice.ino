int LED_1 = 8;
int LED_2 = 9;
int LED_3 = 1;
int LED_4 = 0;
int LED_5 = 10;
int LED_6 = 3;
int LED_7 = 2;
int BUTTON = 7;

int displayTime = 2000;  
int pendingTime = 100;
int num = 1;

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);
  pinMode(LED_7, OUTPUT);
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {
    num = random(1, 7);  
    displayRandom(num);
  }
  delay(pendingTime);    
}


void displayRandom(int numDisplayed) {
  reset();
  if (numDisplayed == 1) {
    digitalWrite(LED_3, HIGH);
  }
    
  if (numDisplayed == 2) {
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_6, HIGH);
  }
    
  if (numDisplayed == 3) {
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
  }
    
  if (numDisplayed == 4) {
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_5, HIGH);
    digitalWrite(LED_7, HIGH);
  }
    
  if (numDisplayed == 5) {
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_5, HIGH);
    digitalWrite(LED_7, HIGH);
    
  }
    
  if (numDisplayed == 6) {
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_5, HIGH);
    digitalWrite(LED_6, HIGH);
    digitalWrite(LED_7, HIGH);
  }
    
  delay(displayTime);
}

void reset() {
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW);   
  digitalWrite(LED_5, LOW);
  digitalWrite(LED_6, LOW);
  digitalWrite(LED_7, LOW);
}
