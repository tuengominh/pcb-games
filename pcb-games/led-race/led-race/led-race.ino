int LED_1 = 8;
int LED_2 = 9;
int LED_3 = 1;
int LED_4 = 0;
int LED_5 = 10;
int LED_6 = 3;
int LED_7 = 2;
int BUTTON = 7;

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);
  pinMode(LED_7, OUTPUT);
  Serial.begin(115200);
}

void loop() {
    Serial.println("Start the loop!");
    check(LED_1);
    check(LED_5);
    check(LED_2);
    check(LED_3);
    check(LED_6);
    check(LED_7);
    check(LED_4);
    delay(2000);    
}

void check(int led) {
    digitalWrite(led, HIGH);
    Serial.println(led);
    delay(200);
    digitalWrite(led, LOW);
    if (led == 1) {
        if (digitalRead(BUTTON) == LOW && digitalRead(led) == HIGH) {
            Serial.println("Awesome! You win!");
        } 
        else {
            Serial.println("You missed it!");
        }
    } 
}
