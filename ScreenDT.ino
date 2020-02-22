//add new files
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDR   0x3C


#define time_interval 1000
#define max_time 4294967295
//time syntax is HH:MM:SS Am/Pm 12hr format
String day_inter[2]={"AM","PM"};
char data_ar[15];
String data_str1;
String data_str2;
byte minute=0;
byte hour=0;
byte second=0;
String inter;
String out_min,out_hr,out_sec,out_data;
unsigned long prev_time,curr_time;
unsigned int diff;
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);


void time_init()
{
  Serial.println("Enter time in HH:MM:SS AM/PM format");
  while(Serial.available()==0);
  data_str1=Serial.readStringUntil(';');
  data_str2=Serial.readStringUntil(';');
  data_str1.trim();
  data_str2.trim();
  hour=byte(data_str1.substring(0,2).toInt());
  minute=byte(data_str1.substring(3,5).toInt());
  second=byte(data_str1.substring(6,8).toInt());
  inter=data_str1.substring(9);
  prev_time=curr_time=0;
}

void update_time()
{
  curr_time=millis();
  if(prev_time<=curr_time)
  {
    diff=curr_time-prev_time;
  }
  else
  {
    diff=(max_time-prev_time)+curr_time;
  }
  if(diff>=time_interval)
  {
    second+=1;
    if(second>=60)
    {
      second=0;
      minute+=1;
      if(minute>=60)
      {
        minute=0;
        hour+=1;
        if(hour==12)
        {
          if(inter.equals("AM"))
          {
            inter="PM";
          }
          else
          {
            inter="AM";
          }
        }
        else if(hour>12)
        {
          hour=1;
        }
      }
    }
    prev_time=curr_time;
    out_put();
  }
}

void out_put()
{
  out_sec=String(second);
  out_sec.concat(" ");
  out_min=String(minute);
  out_min.concat(":");
  out_hr=String(hour);
  out_hr.concat(":");
  out_data=String("");
  out_data.concat(out_hr);
  out_data.concat(out_min);
  out_data.concat(out_sec);
  out_data.concat(inter);
  Serial.println(out_data);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,17);
  display.println(out_data);
  display.println(data_str2);
  display.display();
}

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  time_init();
}

void loop()
{
  display.clearDisplay();
  update_time();  ///update time in reguler interval of time;
 // out_put(); ///Showing data on screen;
}
