#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
char ngay,thang,thu,gio,phut,giay;
int nam;
void setup()
{
  lcd.begin();
  lcd.noBacklight();
  lcd.print("Dong ho DS1307 ");
  delay(1500);
  lcd.clear();
  setTime(13,25,0,5,30,7,20);
  Serial.begin(9600);
  pinMode(A3,OUTPUT); digitalWrite(A3,1);
}
char buff[20];
void loop()
{
  Get_time();
  hengio();
  if(thu == 1)
  {
    sprintf(buff,"CN  %02d:%02d:%02d",gio,phut,giay);
    lcd.print(buff);
    Serial.println(buff);
  }
  else
  {
    sprintf(buff,"T%d  %02d:%02d:%02d",thu,gio,phut,giay);
    lcd.setCursor(0,0);
    lcd.print(buff);
    Serial.println(buff);
  }
  sprintf(buff,"%02d/%02d/%02d",ngay,thang,nam);
  lcd.setCursor(3,1);
  lcd.print(buff);
  Serial.println(buff);
  delay(900);
}


void hengio()
{
  if(gio == 10 && phut == 1)
  {
    //Serial.println("den gio hen gio");
    digitalWrite(A3,0);// bat A3
  }
}


int BCDtoDEC(byte num)
{
  return((num / 16) * 10 + (num % 16));
}

int DECtoBCD( byte num)
{
  return((num / 10) * 16 + (num % 10));
}

void setTime(byte gio,byte phut, byte giay, byte thu, byte ngay, byte thang, byte nam)
{
  Wire.beginTransmission(0x68);
  Wire.write(byte(0x00)); 
  Wire.write(DECtoBCD(giay));
  Wire.write(DECtoBCD(phut));
  Wire.write(DECtoBCD(gio));
  Wire.write(DECtoBCD(thu));
  Wire.write(DECtoBCD(ngay));
  Wire.write(DECtoBCD(thang));
  Wire.write(DECtoBCD(nam));
  Wire.endTransmission();
}

void Get_time()
{
  Wire.beginTransmission(0x68);
  Wire.write(byte(0x00)); 
  Wire.endTransmission();
  Wire.requestFrom(0x68, 7);
  giay = BCDtoDEC(Wire.read());
  phut = BCDtoDEC(Wire.read());
  gio = BCDtoDEC(Wire.read());
  thu = BCDtoDEC(Wire.read());
  ngay = BCDtoDEC(Wire.read());
  thang = BCDtoDEC(Wire.read());
  nam = BCDtoDEC(Wire.read());
  nam = nam+2000;
}
