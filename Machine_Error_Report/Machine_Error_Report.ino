#include <SoftwareSerial.h>
#include <LiquidCrystal.h> 

SoftwareSerial mySerial(2,3);

// buttons..........
int red_button = 8;
int yellow_button = 9;
int green_button = 10;

// 16*2 LCD...........
int Contrast=95;
LiquidCrystal lcd(12, 11, A0, A1, A2, A3);

// Message to send for different buttons

char red_str[] = "Machine has problem";
char yellow_str[] = "Repairing";
char green_str[] = "Repaired";
char fine[] = "All is Fine";


// Blink LED
int red = 4;
int yellow = 5;
int green = 7;

int sms_count = 0;


void setup() {
  // LCD
  analogWrite(6,Contrast);
  lcd.begin(16, 2);

  // setup butttons
  pinMode(red_button, INPUT_PULLUP);
  pinMode(yellow_button, INPUT_PULLUP);
  pinMode(green_button, INPUT_PULLUP);

  // LED PINMODE
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  // Serial Monitor Begin
  Serial.begin(9600);
}

void sendMessage(char *message)
{
  if (sms_count<1)
  {
    //Begin serial communication with Arduino and SIM900
    mySerial.begin(9600);
  
    Serial.println("Initializing..."); 
    delay(1000);
  
    mySerial.println("AT"); //Handshaking with SIM900
    updateSerial();
  
    mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
    updateSerial();
    mySerial.println("AT+CMGS=\"+91***********\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
    updateSerial();
    mySerial.print(message); //text content
    updateSerial();
    mySerial.write(26);
    printMe("SMS sent");
    sms_count++;
  }
  else
  {
    printMe("SMS count++");
  }
  
}
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}

void printMe(char *message)
{
  lcd.setCursor(0,0);
     lcd.print(message);
     lcd.setCursor(0,1);
     lcd.print("......");
     delay(750);
     lcd.scrollDisplayLeft();//shifting data on LCD
     lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (digitalRead (red_button) == HIGH && digitalRead(yellow_button)==LOW && digitalRead(green_button) == LOW)
  {
      digitalWrite(red, HIGH);
      sms_count = 0;
      Serial.println("Red Button pressed..");
      sendMessage(red_str);  
      printMe(red_str);
      delay(700);
  }
  else if (digitalRead (yellow_button) == HIGH && digitalRead(red_button) == HIGH && digitalRead(green_button)==LOW)
  {
      digitalWrite(yellow, HIGH);
      sms_count = 0; 
      Serial.println("Yellow Button pressed..");
      sendMessage(yellow_str);  
      printMe(yellow_str);
      delay(700);
  }
  else if (digitalRead (green_button) == HIGH && digitalRead(red_button) == HIGH && digitalRead(yellow_button) == HIGH)
  {
      digitalWrite(green, HIGH);
      sms_count = 0;
      Serial.println("Green Button pressed..");
      sendMessage(green_str);  
      printMe(green_str);
      delay(700);
  }
  else
  {
      digitalWrite(red, LOW);
      digitalWrite(yellow, LOW);
      digitalWrite(green, LOW);
      
      Serial.println("No Input....");
      printMe(fine);
      delay(100);
      //lcd.clear();
  }
}
