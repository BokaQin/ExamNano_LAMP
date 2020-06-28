#include <stdio.h>
#include <DS3231.h>
DS3231  rtc(15, 14);
Time  t;

#include <FastLED.h>
#define NUM_LEDS 16
#define DATA_PIN 2
#define Clock_PIN 12
CRGB leds[NUM_LEDS];

int Sen_Pin = A7;
int InPut_Pin  = 0;
#include <Arduino.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0,SCL,SDA,U8X8_PIN_NONE); 

void setup() { 
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(Clock_PIN, INPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(3, LOW); 
  digitalWrite(6, LOW);
  digitalWrite(8, LOW); 
  digitalWrite(4, HIGH); 
  digitalWrite(7, HIGH);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); 
  u8g2.begin();
  rtc.begin();
  Serial.begin(115200);
}


void loop() { 
    t = rtc.getTime(); 
    int day1[3], day2[3];
    int day = 0;
    day1[0] = t.year, DEC;
    day1[1] = t.mon, DEC;
    day1[2] = t.date, DEC;
    day2[0] = 2020;
    day2[1] = 7;
    day2[2] = 24;
    day = days(day1, day2);
    int day_time = day;
  
  {
    u8g2.firstPage();
    do {
      {//before days
    u8g2.setFont(u8g2_font_6x12_mf); 
    u8g2.setCursor(20,15);
    u8g2.print("Only");
    
    u8g2.setFont(u8g2_font_profont22_tn); 
    u8g2.setCursor(50,15);
    u8g2.print(day);
    
    u8g2.setFont(u8g2_font_6x12_mf); 
    u8g2.drawStr(80,15,"Days");
    u8g2.drawStr(15,30,"Remained b4 Exam");
    }
    
    {//Bright
    u8g2.setFont(u8g2_font_blipfest_07_tr); 
    u8g2.setCursor(47,40);
    u8g2.print("Bright");
    u8g2.setCursor(71,40);
    u8g2.print(InPut_Pin);
    }
    
    {//tem
    float Fahrenheit = rtc.getTemp()*1.8 + 32; 
    u8g2.setFont(u8g2_font_tom_thumb_4x6_mf); 
    u8g2.setCursor(0,50);
    u8g2.print("The Weather");
    u8g2.setCursor(0,60);
    u8g2.print(rtc.getTemp());
    u8g2.print("C");
    u8g2.setCursor(30,60);
    u8g2.print(Fahrenheit);
    u8g2.print("F");     
    }
    
    { //clock
    u8g2.setCursor(84,50);
    u8g2.setFont(u8g2_font_blipfest_07_tr); 
    u8g2.print(t.year);
    
    u8g2.setFont(u8g2_font_4x6_mf); 
    u8g2.print("/");
    
    u8g2.setFont(u8g2_font_blipfest_07_tr); 
    u8g2.print(t.mon);
    
    u8g2.setFont(u8g2_font_4x6_mf); 
    u8g2.print("/");
    
    u8g2.setFont(u8g2_font_blipfest_07_tr); 
    u8g2.print(t.date);  
    
    u8g2.setCursor(89,60);
    u8g2.setFont(u8g2_font_blipfest_07_tr); 
    u8g2.print(rtc.getTimeStr());
    }
    }
    while ( u8g2.nextPage() );
  }
    int x = t.min;
    int Clock_Beat = beatsin8(10, 0, 255);
    InPut_Pin = analogRead(Sen_Pin)/4;
    FastLED.setBrightness(InPut_Pin);
    fill_solid(leds, 16, CRGB(255,255,255));
    FastLED.show();
    delay(50);
    
    {//早上闹钟
    if(t.hour == 4)
        if(x >= 10 && x < 20 )
          if( Clock_PIN == 0)
          analogWrite(A2,255);
          delay(400);
    }
    
    {//下午闹钟
      if(t.hour == 15)
        if( x >= 50 && x < 55 )
          if( Clock_PIN == 0)
          analogWrite(A2,255);
          delay(400);
    }
}
