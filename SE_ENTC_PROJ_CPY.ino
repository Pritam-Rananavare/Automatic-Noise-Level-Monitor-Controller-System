#include <LiquidCrystal.h>


LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

const int green = A5;
const int red = A4;
const int buzzer = 12;
const int entr = 4;
const int bck = 1;
const int up = 2;
const int dwn = 3;   // the number of the pushbutton pin

const int pinSignal1 = A0;
const int pinSignal2 = A1;
const int pinSignal3 = A2;

int thershold;
const int school = 60;
const int college = 75;
const int office = 45;
const int Library = 30;

int e_chk1 = 0;
int e_chk2 = 0;
int menu = 1;
int menu_sel = 1;

long sum1;
long sum2;
long sum3;

long level1 = 0;
long level2 = 0;
long level3 = 0;

long Sound_signal1;
long Sound_signal2;
long Sound_signal3;

void setup()
{
  lcd.begin(20, 4);
  Serial.begin(9600);
  pinMode(entr, INPUT);
  pinMode(bck, INPUT);
  pinMode(up, INPUT);
  pinMode(dwn, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  digitalWrite(buzzer, HIGH);
  digitalWrite(green, HIGH);
  digitalWrite(red, HIGH);
  pinMode (pinSignal1, INPUT);
  pinMode (pinSignal2, INPUT);
  pinMode (pinSignal3, INPUT);
  lcd.clear();
  lcd.print(F("   Automatic Noise"));
  lcd.setCursor(0, 1);
  lcd.print(F("   Level Monitor &"));
  lcd.setCursor(0, 2);
  lcd.print(F("  Controller System"));
  delay(2000);
  lcd.clear();
  lcd.print(F("   Select the mode"));
  delay(2000);
  // put your setup code here, to run once:

}

void loop()
{
  digitalWrite(buzzer, HIGH);
  digitalWrite(green, LOW);
  digitalWrite(red, HIGH);
  while (1)
  {
    while (menu == 1)
    {
      if (menu_sel == 1)
      {
        lcd.clear();
        lcd.print(F("->>1.School"));
        lcd.setCursor(0, 1);
        lcd.print(F("   2.College"));
        lcd.setCursor(0, 2);
        lcd.print(F("   3.Office"));
        lcd.setCursor(0, 3);
        lcd.print(F("   4.Library"));
      }
      else if (menu_sel == 2)
      {
        lcd.clear();
        lcd.print(F("   1.School"));
        lcd.setCursor(0, 1);
        lcd.print(F("->>2.College"));
        lcd.setCursor(0, 2);
        lcd.print(F("   3.Office"));
        lcd.setCursor(0, 3);
        lcd.print(F("   4.Library"));
      }
      else if (menu_sel == 3)
      {
        lcd.clear();
        lcd.print(F("   1.School"));
        lcd.setCursor(0, 1);
        lcd.print(F("   2.College"));
        lcd.setCursor(0, 2);
        lcd.print(F("->>3.Office"));
        lcd.setCursor(0, 3);
        lcd.print(F("   4.Library"));
      }
      else if (menu_sel == 4)
      {
        lcd.clear();
        lcd.print(F("   1.School"));
        lcd.setCursor(0, 1);
        lcd.print(F("   2.College"));
        lcd.setCursor(0, 2);
        lcd.print(F("   3.Office"));
        lcd.setCursor(0, 3);
        lcd.print(F("->>4.Library"));
      }

      if (digitalRead(up) == 0)
      {
        menu_sel = menu_sel + 1;
        if ( menu_sel >= 4)
        {
          menu_sel = 4;
        }
        delay(200);
      }
      else if (digitalRead(dwn) == 0)
      {
        menu_sel = menu_sel - 1;
        if ( menu_sel <= 0)
        {
          menu_sel = 0;
        }
        delay(200);
      }
      else if (digitalRead(entr) == LOW)
      {
        menu = 0;
        delay(200);
      }
      delay(200);
    }
    break;
  }
  digitalWrite(buzzer, HIGH);
  digitalWrite(green, LOW);
  digitalWrite(red, HIGH);
  if (menu_sel == 1)
  {
    thershold = school;
  }
  if (menu_sel == 2)
  {
    thershold = college;
  }
  if (menu_sel == 3)
  {
    thershold = office;
  }
  if (menu_sel == 4)
  {
    thershold = Library;
  }
  lcd.clear();
  lcd.print(F("Set db limit"));
  lcd.setCursor(8, 1);
  lcd.print(thershold);
  delay(1000);
  while (digitalRead(entr) == HIGH)
  {

    lcd.setCursor(8, 1);
    lcd.print(thershold);
    if (digitalRead(up) == LOW)
    {
      thershold = thershold + 5;
      lcd.setCursor(8, 1); // Move cursor to the threshold value
      lcd.print("   ");
      delay(200);
    }
    else if (digitalRead(dwn) == LOW)
    {
      thershold = thershold - 5;
      lcd.setCursor(8, 1); // Move cursor to the threshold value
      lcd.print("   ");
      delay(200);
    }
  }
  while (digitalRead(bck) == HIGH)
  {
    level1 = analogRead (pinSignal1);
    level2 = analogRead (pinSignal2);
    level3 = analogRead (pinSignal3);
    Serial.print("level:" + String(level1) + "leve2:" + String(level2) + "level3:" + String(level3));
    delay(500);
    lcd.clear();
    lcd.print("Sound Level1 =");
    lcd.setCursor(14, 0);
    lcd.print(String(level1) + "db");
    lcd.setCursor(0, 1);
    lcd.print("Sound Level2 =");
    lcd.setCursor(14, 1);
    lcd.print(String(level2) + "db");
    lcd.setCursor(0, 2);
    lcd.print("Sound Level3 =");
    lcd.setCursor(14, 2);
    lcd.print(String(level3) + "db");

    if ((level1 >= thershold) || (level2 >= thershold) || (level3 >= thershold))
    {
      digitalWrite(green, HIGH);
      digitalWrite(red, LOW);
      digitalWrite(buzzer, LOW);
      delay(1000);
      digitalWrite(buzzer, HIGH);
      delay(500);
    }
    else
    {
      digitalWrite(green, LOW);
      digitalWrite(red, HIGH);
      digitalWrite(buzzer, HIGH);
    }
  }
  menu = 1;
}
