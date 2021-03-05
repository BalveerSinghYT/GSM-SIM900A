#include <LiquidCrystal.h> 
int Contrast=95;
 LiquidCrystal lcd(12, 11, A0, A1, A2, A3);  
char mess[] = "Hi Hello";
 void setup()
 {
    analogWrite(6,Contrast);
     lcd.begin(16, 2);
     //lcd.print("hello, world!");
  } 


void printme(char *message)
{
  lcd.setCursor(0,0);
     lcd.print(message);
     lcd.setCursor(0,1);
     lcd.print("......");
     delay(750);
     lcd.scrollDisplayLeft();//shifting data on LCD
     lcd.clear();
}

void loop()
 { 
     
     printme(mess);
 }
