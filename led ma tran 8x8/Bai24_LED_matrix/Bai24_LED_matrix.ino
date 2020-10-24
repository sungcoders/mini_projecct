/*
  Demo code of P22 - 8x8 Red LED Matrix Driver
  by maker studio
*/
#include <TM1638.h>

TM1638 LED_Matrix(4,5,6);
uint8_t lineDat = 0b11011100;
uint8_t columeDat = 0b11011100;

//demo pic
uint8_t picDat0[] ={  0b11111111,
      0b10000001,
      0b10000001,
      0b10000001,
      0b10000001,
      0b10000001,
      0b10000001,
      0b11111111};
uint8_t picDat1[] ={  0b00000000,
      0b01111110,
      0b01000010,
      0b01000010,
      0b01000010,
      0b01000010,
      0b01111110,
      0b00000000};      
uint8_t picDat2[] ={  0b00000000,
      0b00000000,
      0b00111100,
      0b00100100,
      0b00100100,
      0b00111100,
      0b00000000,
      0b00000000};
uint8_t picDat3[] ={  0b00000000,
      0b00000000,
      0b00000000,
      0b00011000,
      0b00011000,
      0b00000000,
      0b00000000,
      0b00000000};      
void setup()
{
  LED_Matrix.displayAll();
  delay(500);
  LED_Matrix.clear();
}

void loop()
{
  int line =0;
  int colume = 0;
  
  //test set point
  for(line = 0; line < 8;){
    for(colume = 0; colume < 8; colume++){
      LED_Matrix.setPoint(line,colume,1);
      delay(50);
    }
    line++;
    for(colume = 7; colume >= 0; colume--){
      LED_Matrix.setPoint(line,colume,1);
      delay(50);
    }
    line++;
  }
  
  //test clear display
  LED_Matrix.clear();
  delay(500);
  
  //test set line
  for(line = 0; line < 8; line++){
    LED_Matrix.displayLine(line);
    delay(50);
  }
  for(line = 7; line >= 0; line--){
    LED_Matrix.clearLine(line);
    delay(50);
  }
  for(line = 0; line < 8; line++){
    LED_Matrix.setLine(line,lineDat);
    delay(50);
  }
  for(line = 7; line >= 0; line--){
    LED_Matrix.clearLine(line);
    delay(50);
  }
  delay(500);
  
  //test set colume
    //test set line
  for(colume = 0; colume < 8; colume++){
    LED_Matrix.displayColume(colume);
    delay(50);
  }
  for(colume = 7; colume >= 0; colume--){
    LED_Matrix.clearColume(colume);
    delay(50);
  }
  for(colume = 0; colume < 8; colume++){
    LED_Matrix.setColume(colume,columeDat);
    delay(50);
  }
  for(colume = 7; colume >= 0; colume--){
    LED_Matrix.clearColume(colume);
    delay(50);
  }
  delay(500);
  
  //test display pic
  LED_Matrix.displayPic(picDat0);
  delay(150);
  LED_Matrix.displayPic(picDat1);
  delay(150);
  LED_Matrix.displayPic(picDat2);
  delay(150);
  LED_Matrix.displayPic(picDat3);
  delay(150);
  LED_Matrix.displayPic(picDat2);
  delay(150);
  LED_Matrix.displayPic(picDat1);
  delay(150);
  LED_Matrix.displayPic(picDat0);
  delay(500);
  //
    
    for(colume = 0; colume < 8; colume++){
      LED_Matrix.setPoint(0,colume,1);
      delay(50);}   
    for(line = 1; line < 8;line++);{
      LED_Matrix.setPoint(line,7,0);
      delay(50);}
    for(colume = 6; colume >= 0; colume--){
      LED_Matrix.setPoint(7,colume,1);
      delay(50);}
    for(line = 6; line >= 1;line--);{
      LED_Matrix.setPoint(line,0,0);
      delay(50);}//0
      
    
    for(colume = 1; colume < 7; colume++){
      LED_Matrix.setPoint(1,colume,1);
      delay(50);
    }
    for(line = 3; line < 7;line++);
    {LED_Matrix.setPoint(line,6,1);
      delay(50);}
    for(colume = 5; colume >= 2; colume--){
      LED_Matrix.setPoint(6,colume,1);
      delay(50);}
    for(line = 5; line >= 2;line--);
    {LED_Matrix.setPoint(line,1,1);
      delay(50);}//1
      
    
    for(colume = 2; colume < 6; colume++){
      LED_Matrix.setPoint(2,colume,1);
      delay(50);
    }
    for(line = 4; line < 6;line++);
    {LED_Matrix.setPoint(line,5,1);
      delay(50);}
    for(colume = 5; colume >= 3; colume--){
      LED_Matrix.setPoint(5,colume,1);
      delay(50);}
    for(line = 4; line >= 3;line--);
    {LED_Matrix.setPoint(line,2,1);
      delay(50);}//2
      
    
    for(colume = 3; colume < 5; colume++){
      LED_Matrix.setPoint(3,colume,1);
      delay(50);
    }
    for(line = 3; line < 5;line++);
    {LED_Matrix.setPoint(line,4,1);
      delay(50);}
    for(colume = 4; colume >= 4; colume--){
      LED_Matrix.setPoint(4,colume,1);
      delay(50);}
    for(line = 3; line >= 3;line--);
    {LED_Matrix.setPoint(line,3,1);
      delay(50);}//3
      
      
  
}

//this is left for you to implement
void displayZigZag()
{
  
}
