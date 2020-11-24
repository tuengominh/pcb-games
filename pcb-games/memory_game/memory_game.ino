/* Start button: press to start the game
   4 LEDs to display the sequences
   4 buttons for the player to play the sequence

   If the sequence is correct, all LEDs on for 1s
   Then the new sequence is displayed
   Each level the sequence increases by +1 LED and the speed increases

   If the sequence is correct, all LEDs flash 3 times and end the game
*/

#define NOTE_B3 246.94 
#define NOTE_C4 261.63 
#define NOTE_C4S 277.18 
#define NOTE_D4 293.66 
#define NOTE_E4 329.63 
#define NOTE_F4 349.23 
#define T_BLACK 1
#define T_WHITE 2
#define T_ROUND 4
#define T_QUAVER 0.5
#define T_SEMIQUAVER 0.25
#define T_FUSE 0.125
#define T_SEMIFUSE 0.0625

const int PIN_LED_GREEN = 2;
const int PIN_LED_YELLOW = 4;
const int PIN_LED_BLUE = 5;
const int PIN_LED_RED = 3;

const int PIN_BTN_GREEN = 10;
const int PIN_BTN_YELLOW = 12;
const int PIN_BTN_BLUE = 13;
const int PIN_BTN_RED = 11;

const int PIN_BTN_START = 8;
const int PIN_BUZZER = 6;

const int MAX_LEVEL = 16; 
int CURRENT_LEVEL = 0; 
int SPEED = 1000;  
int sequence[MAX_LEVEL+1];  

long btn_last_reading_green = 0;  
long btn_last_reading_yellow = 0; 
long btn_last_reading_blue = 0; 
long btn_last_reading_red = 0; 
long btn_delay = 50; 

void setup ()  {
  pinMode(PIN_BTN_GREEN, INPUT);
  pinMode(PIN_BTN_YELLOW, INPUT);
  pinMode(PIN_BTN_BLUE, INPUT);
  pinMode(PIN_BTN_RED, INPUT);
  pinMode(PIN_BTN_START, INPUT);
  
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  
  pinMode(PIN_BUZZER, OUTPUT);
 
  digitalWrite(PIN_LED_GREEN, LOW);
  digitalWrite(PIN_LED_YELLOW, LOW);
  digitalWrite(PIN_LED_BLUE, LOW);
  digitalWrite(PIN_LED_RED, LOW);

  digitalWrite(PIN_BTN_GREEN, LOW); 
  digitalWrite(PIN_BTN_YELLOW, LOW);
  digitalWrite(PIN_BTN_BLUE, LOW);
  digitalWrite(PIN_BTN_RED, LOW);
  digitalWrite(PIN_BTN_START, LOW);

  randomSeed(analogRead(0));
}

void loop (){
  while (CURRENT_LEVEL == 0){
    if(digitalRead(PIN_BTN_START) == HIGH){ 
      delay(500);
      CURRENT_LEVEL = 1;
      delay(50);
    }
  }
  generate_led_sequence();
  read_btn_sequence(); 
}

void generate_led_sequence()  {
  sequence[CURRENT_LEVEL] = random(2,6);  
  for(int i = 1; i <= CURRENT_LEVEL; i++){
    digitalWrite(sequence[i], HIGH);
    play_note_led(sequence[i], SPEED);
    digitalWrite(sequence[i], LOW);
    delay(SPEED/10);
  }
}

void read_btn_sequence(){
  boolean correct = true;
  int i = 1;
  int pressedBtn = 0;
  
  while(correct && i <= CURRENT_LEVEL){  
    if(digitalRead(PIN_BTN_RED) == HIGH){ 
      digitalWrite(PIN_LED_RED, HIGH);
      play_note_led(PIN_LED_RED, 250);
      digitalWrite (PIN_LED_RED, LOW);
      pressedBtn = PIN_LED_RED;
      btn_last_reading_red = millis();
    }
    else if(digitalRead (PIN_BTN_BLUE) == HIGH){ 
      digitalWrite (PIN_LED_BLUE, HIGH);
      play_note_led(PIN_LED_BLUE, 250);
      digitalWrite (PIN_LED_BLUE, LOW);
      pressedBtn = PIN_LED_BLUE;
      btn_last_reading_blue = millis();
    }
    else if(digitalRead(PIN_BTN_YELLOW) == HIGH){ 
      digitalWrite(PIN_LED_YELLOW, HIGH);
      play_note_led(PIN_LED_YELLOW, 250);
      digitalWrite(PIN_LED_YELLOW, LOW);
      pressedBtn = PIN_LED_YELLOW;
      btn_last_reading_yellow = millis();
    }
    else if (digitalRead(PIN_BTN_GREEN) == HIGH){ 
      digitalWrite(PIN_LED_GREEN, HIGH);
      play_note_led(PIN_LED_GREEN, 250);
      digitalWrite(PIN_LED_GREEN, LOW);
      pressedBtn = PIN_LED_GREEN;
      btn_last_reading_green = millis();
    }
  

    if((pressedBtn == PIN_LED_RED && (millis() - btn_last_reading_green) > btn_delay) ||
      (pressedBtn == PIN_LED_BLUE && (millis() - btn_last_reading_blue)  > btn_delay) ||
      (pressedBtn == PIN_LED_YELLOW && (millis() - btn_last_reading_yellow) > btn_delay) ||
      (pressedBtn == PIN_LED_GREEN && (millis() - btn_last_reading_green) > btn_delay)) {  
        
      if(pressedBtn != sequence[i]){  
        correct = false ;
      } else {
        i++;
        pressedBtn = 0;
      }
    }
  }  

  if(correct == true){ 
    delay (500);
    correct_response();
    CURRENT_LEVEL++; 
    if (SPEED >= 50){
      SPEED -= 50;
    }
  } else {  
    incorrect_response();
    CURRENT_LEVEL = 0; 
    SPEED = 1000;
  }
}

void play_note_led(int led, int speed){
  int notes[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4};
  tone(PIN_BUZZER, notes[led - 2], speed); 
  delay(speed); 
}

void play_melody(int notes[], int duration[], int tempo, int n_notes){
  for(int i = 0; i < n_notes; i++){
    tone(PIN_BUZZER, notes[i], duration[i] * tempo);
    delay(duration[i] * tempo * 1.30);
  }
}

void game_over_sound(){
  int notes[] = {NOTE_D4, NOTE_C4S, NOTE_C4, NOTE_B3};
  int duration[] = {T_BLACK, T_WHITE, T_BLACK, T_ROUND};
  play_melody(notes, duration, 300, 4);
}

void correct_response(){
  delay(1000);
}

void incorrect_response(){
  delay(500);
  digitalWrite(PIN_LED_GREEN, HIGH);
  digitalWrite(PIN_LED_YELLOW, HIGH);
  digitalWrite(PIN_LED_BLUE, HIGH);
  digitalWrite(PIN_LED_RED, HIGH); 
  game_over_sound();
  digitalWrite(PIN_LED_GREEN, LOW);
  digitalWrite(PIN_LED_YELLOW, LOW);
  digitalWrite(PIN_LED_BLUE, LOW);
  digitalWrite(PIN_LED_RED, LOW); 
  delay(1000);
}
