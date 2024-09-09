#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Timer.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4


const unsigned char ship [] PROGMEM = {
	0x00, 0x3e, 0x58, 0xfc, 0xfc, 0x58, 0x3e, 0x00
};

const unsigned char meteor [] PROGMEM = {
	0x18, 0x7a, 0x5e, 0xff, 0xfd, 0x4e, 0x7e, 0x18
};

const unsigned char cop [] PROGMEM = {
	0x00, 0x24, 0x18, 0x48, 0x3e, 0x20, 0x04, 0x00
};

const unsigned char ates [] PROGMEM = {
	0x00, 0x02, 0x7c, 0xe6, 0x7c, 0x02, 0x00, 0x00
};

const unsigned char heal [] PROGMEM = {
	0x00, 0x24, 0x5a, 0x42, 0x24, 0x18, 0x00, 0x00
};

class Engel
{
  public:
    int tip;
    int satir;
    
};

class Oyuncu
{
  public:
    int satir;
    int sutun;   
};

class Silah
{
  public:
    bool ekrandaMi;   
    int satir;
    int sira;
};

int menuitem = 1;
int page = 1;

volatile boolean up = false;
volatile boolean down = false;
volatile boolean middle = false;
volatile boolean gun = false;

int downButtonState = 0;
int upButtonState = 0;  
int selectButtonState = 0;  
int silahButtonState = 0;
        
int lastDownButtonState = 0;
int lastSelectButtonState = 0;
int lastUpButtonState = 0;
int lastSilahButtonState = 0;

int skor = 0;

int zorluk = 0;
int can = 3;
int silah = 3;
bool dokunulmazlik = false;

bool bittiMi = false;
bool basladiMi = false;

int potValue;
int ldrValue;

bool olustuMu = false;

int engelSutun = 0;
int silahSutun = 120;

int dly = 1000;
bool sayiyorMu = false;

bool silahAteslendiMi = false;

int tmp;
int orta;


Oyuncu oyuncu1;

Timer timer;
Timer timerBuzzer;
Timer timerDly;

Engel e1;
Engel e2;
Engel e3;
Engel e4;
Engel e5;
Engel e6;
Engel e7;

Engel e14;

Silah s1;



Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define YUKARI_BUTTON 8
#define ASAGI_BUTTON 10
#define SEC_BUTTON 9

#define LED_1 5
#define LED_2 6
#define LED_3 7

#define LED_S_1 50
#define LED_S_2 51
#define LED_S_3 52

#define SILAH_BUTTON 53

#define BUZZER 3

#define POT A0

#define LDR A2

void setup() 
{

  pinMode(ASAGI_BUTTON, INPUT_PULLUP);
  pinMode(SEC_BUTTON, INPUT_PULLUP);
  pinMode(YUKARI_BUTTON, INPUT_PULLUP);
  pinMode(SILAH_BUTTON, INPUT_PULLUP);

  Serial.begin(9600);
  
  display.begin();      
  display.clearDisplay(); 
  display.display();


  oyuncu1.sutun = 120;

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  pinMode(LED_S_1, OUTPUT);
  pinMode(LED_S_2, OUTPUT);
  pinMode(LED_S_3, OUTPUT);

  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);

  pinMode(29, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);

  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(42, OUTPUT);
  
  
 
}

void loop() 
{
  potValue = analogRead(POT);
  potValue = map(potValue, 0, 1023, 0, 8);

  ldrValue = analogRead(LDR);
  
  engelRandomSet();
  
  drawMenu();
  


  downButtonState = digitalRead(ASAGI_BUTTON);
  selectButtonState = digitalRead(SEC_BUTTON);
  upButtonState =   digitalRead(YUKARI_BUTTON);
  
 
  checkIfDownButtonIsPressed();
  checkIfUpButtonIsPressed();
  checkIfSelectButtonIsPressed();
  

  if (up && page == 1) 
  {
    up = false;
    menuitem--;
    if (menuitem==0)
    {
      menuitem = 1;
    }      
  }
  else if (up && page == 2) 
  {
    up = false;
    menuitem--;
    if (menuitem==0)
    {
      menuitem = 1;
    }
    
  }


  if (down && page == 1) 
  {
    down = false;
    menuitem++;
    if (menuitem == 3) 
    {
      menuitem = 2;
    }      
  }
  else if (down && page == 2) 
  {
    down = false;
    menuitem++;
    if (menuitem == 3) 
    {
      menuitem = 2;
    } 
    
  }


  
  if (middle && page == 1) 
  {
    middle = false;
    
    if (page == 1 && menuitem == 1) 
    {
      page = 2;
    }
    else if (page == 1 && menuitem == 2)
    {
      basladiMi = true;
      bittiMi= false;
      can = 3;
      silah = 3;
      engelSutun = 0;
      engelSutun = 0;
      engelSutun = 0;
      engelSutun = 0;
      engelSutun = 0;
      engelSutun = 0;
      engelSutun = 0;
    }
    else if (page == 2) 
    {
      page = 1;
    }

  }
  if (middle && page == 2) 
  {
 
    if (page == 2 && menuitem == 1 && middle) 
    {
      zorluk = 1;
    }
    else if (page == 2 && menuitem == 2 && middle) 
    {
      zorluk = 2;
    }

  }
  if(middle && page == 2 && zorluk != 0)
  {
    page = 1;
    menuitem = 1;
    middle = false;
  }

  while(basladiMi && !bittiMi)
  {
    randomSeed(analogRead(A1));

    
    
    if(zorluk == 1)
    {
      silahButtonState = digitalRead(SILAH_BUTTON);
      checkIfSilahButtonIsPressed();
      if(gun)
      {
        gun = false;
        silah--;
        if(silah < 0)
        {
          silah = 0;
        } 
        if(silah >= 0)
        {
          silahAteslendiMi = true;
          if(potValue < 1)
          {
            s1.satir = 0;
            s1.sira = 1;
          }
          else if(potValue >= 1 && potValue < 2)
          {
            s1.satir = 8;
            s1.sira = 2;
          }
          else if(potValue >= 2 && potValue < 3) 
          {
            s1.satir = 16;
            s1.sira = 3;
          }
          else if(potValue >= 3 && potValue < 4) 
          {
            s1.satir = 24;
            s1.sira = 4;
          }
          else if(potValue >= 4 && potValue < 5) 
          {
            s1.satir = 32;
            s1.sira = 5;
          }
          else if(potValue >= 5 && potValue < 6) 
          {
            s1.satir = 40;
            s1.sira = 6;
          }
          else if(potValue >= 6 && potValue < 7) 
          {
            s1.satir = 48;
            s1.sira = 7;
          } 
          else if(potValue >= 7 && potValue <= 8) 
          {
            s1.satir = 56;
            s1.sira = 8;
          }
        }
        
   
      }
      if(silah == 3)
      {
        digitalWrite(LED_S_3, HIGH);
        digitalWrite(LED_S_2, HIGH);
        digitalWrite(LED_S_1, HIGH);        
      }
      else if(silah == 2)
      {
        digitalWrite(LED_S_3, HIGH);
        digitalWrite(LED_S_2, HIGH);
        digitalWrite(LED_S_1, LOW);        
      }
      else if(silah == 1)
      {
        digitalWrite(LED_S_3, HIGH);
        digitalWrite(LED_S_2, LOW);
        digitalWrite(LED_S_1, LOW);        
      }
      else if(silah == 0)
      {
        digitalWrite(LED_S_3, LOW);
        digitalWrite(LED_S_2, LOW);
        digitalWrite(LED_S_1, LOW);        
      }

      if(can == 3)
      {
        digitalWrite(LED_3, HIGH);
        digitalWrite(LED_2, HIGH);
        digitalWrite(LED_1, HIGH);
      }
      else if(can == 2)
      {
        digitalWrite(LED_3, HIGH);
        digitalWrite(LED_2, HIGH);
        digitalWrite(LED_1, LOW);        
      }
      else if(can == 1)
      {
        digitalWrite(LED_3, HIGH);
        digitalWrite(LED_2, LOW);
        digitalWrite(LED_1, LOW);        
      } 

      if(oyuncu1.satir == e14.satir && oyuncu1.sutun == engelSutun && e14.tip == 3 || e14.tip == 4)
      {
        if(e14.tip == 3)
        {
          can++;
          delay(10);
          if(can > 3)
          {
            can = 3;
          }
        }
        else if(e14.tip == 4)
        {
          silah++;
          delay(10);
          if(silah > 3)
          {
            silah = 3;
          }          
        }
      }            
      
      if(oyuncu1.satir == e1.satir && oyuncu1.sutun == engelSutun && dokunulmazlik == false && e1.tip != 0|| oyuncu1.satir == e2.satir && oyuncu1.sutun == engelSutun && dokunulmazlik == false && e2.tip != 0 
      || oyuncu1.satir == e3.satir && oyuncu1.sutun == engelSutun && dokunulmazlik == false && e3.tip != 0|| oyuncu1.satir == e4.satir && oyuncu1.sutun == engelSutun && dokunulmazlik == false && e4.tip != 0
      || oyuncu1.satir == e5.satir && oyuncu1.sutun == engelSutun && dokunulmazlik == false && e5.tip != 0|| oyuncu1.satir == e6.satir && oyuncu1.sutun == engelSutun && dokunulmazlik == false && e6.tip != 0
      || oyuncu1.satir == e7.satir && oyuncu1.sutun == engelSutun && dokunulmazlik == false && e7.tip != 0)
      {
        timerBuzzer.start();
        tone(BUZZER,261);
        can--;
        dokunulmazlik = true;
        timer.start();

        if(can < 1)
        {
          digitalWrite(LED_3, LOW);
          digitalWrite(LED_2, LOW);
          digitalWrite(LED_1, LOW);
          bittiMi = true;
          basladiMi = false;
          gameOver();          
        }
      }
      if(timerBuzzer.read() > 500)
      {
        timerBuzzer.stop();  
        noTone(BUZZER);  
      }
      if(timer.read() > 3000)
      {
        timer.stop();
        dokunulmazlik = false;
      }

      skorAyarla();

      
      if(engelSutun == silahSutun || engelSutun - 8 == silahSutun && s1.sira == e1.satir)
      {
        e1.tip--;  
        silahAteslendiMi = false;    
        silahSutun = 120;  
      }
      else if(engelSutun == silahSutun || engelSutun - 8 == silahSutun && s1.sira == e2.satir)
      {
        e2.tip--; 
        silahAteslendiMi = false; 
        silahSutun = 120; 
      }
      else if(engelSutun == silahSutun || engelSutun - 8 == silahSutun && s1.sira == e3.satir)
      {
        e3.tip--;
        silahAteslendiMi = false;  
        silahSutun = 120; 
      }
      else if(engelSutun == silahSutun || engelSutun - 8 == silahSutun && s1.sira == e4.satir)
      {
        e4.tip--;
        silahAteslendiMi = false;  
        silahSutun = 120; 
      }
      else if(engelSutun == silahSutun || engelSutun - 8 == silahSutun && s1.sira == e5.satir)
      {
        e5.tip--;
        silahAteslendiMi = false; 
        silahSutun = 120;  
      }
      else if(engelSutun == silahSutun || engelSutun - 8 == silahSutun && s1.sira == e6.satir)
      {
        e6.tip--;
        silahAteslendiMi = false;  
        silahSutun = 120; 
      }
      else if(engelSutun == silahSutun || engelSutun - 8 == silahSutun && s1.sira == e7.satir)
      {
        e7.tip--;
        silahAteslendiMi = false;  
        silahSutun = 120; 
      }      
      
      if(potValue < 1)
      {
        display.clearDisplay();
        if(ldrValue > 975/2)
        {
          display.fillRect(0,0,128,64,WHITE);          
        }
        shipDisplay();
        if(silahAteslendiMi)
        {
          silahDisplay();          
        }        
        if(!olustuMu)
        {
          engelRandomSet();        
        }
        engelDisplay();        
        display.display();
        potGuncelle();
      }
      else if(potValue >= 1 && potValue < 2)
      {
        display.clearDisplay();
        if(ldrValue > 975/2)
        {
          display.fillRect(0,0,128,64,WHITE);          
        }
        shipDisplay();
        if(silahAteslendiMi)
        {
          silahDisplay();          
        }
        if(!olustuMu)
        {
          engelRandomSet();        
        }
        engelDisplay();
        display.display();
        potGuncelle();
      }
      else if(potValue >= 2 && potValue < 3)
      {
        display.clearDisplay();
        if(ldrValue > 975/2)
        {
          display.fillRect(0,0,128,64,WHITE);          
        }
        shipDisplay();
        if(silahAteslendiMi)
        {
          silahDisplay();          
        }
        if(!olustuMu)
        {
          engelRandomSet();        
        }
        engelDisplay();
        display.display();
        potGuncelle();
      }
      else if(potValue >= 3 && potValue < 4)
      {
        display.clearDisplay();
        if(ldrValue > 975/2)
        {
          display.fillRect(0,0,128,64,WHITE);          
        }
        shipDisplay();
        if(silahAteslendiMi)
        {
          silahDisplay();          
        }
        if(!olustuMu)
        {
          engelRandomSet();        
        }
        engelDisplay();
        display.display();
        potGuncelle();
      }
      else if(potValue >= 4 && potValue < 5)
      {
        display.clearDisplay();
        if(ldrValue > 975/2)
        {
          display.fillRect(0,0,128,64,WHITE);          
        }
        shipDisplay();
        if(silahAteslendiMi)
        {
          silahDisplay();          
        }
        if(!olustuMu)
        {
          engelRandomSet();        
        }
        engelDisplay();
        display.display();
        potGuncelle();
      }
      else if(potValue >= 5 && potValue < 6)
      {
        display.clearDisplay();
        if(ldrValue > 975/2)
        {
          display.fillRect(0,0,128,64,WHITE);          
        }
        shipDisplay();
        if(silahAteslendiMi)
        {
          silahDisplay();          
        }
        if(!olustuMu)
        {
          engelRandomSet();        
        }
        engelDisplay();
        display.display();
        potGuncelle();
      }
      else if(potValue >= 6 && potValue < 7)
      {
        display.clearDisplay();
        if(ldrValue > 975/2)
        {
          display.fillRect(0,0,128,64,WHITE);          
        }
        shipDisplay();
        if(silahAteslendiMi)
        {
          silahDisplay();          
        }
        if(!olustuMu)
        {
          engelRandomSet();        
        }
        engelDisplay();
        display.display();
        potGuncelle();
      }
      else if(potValue >= 7 && potValue <= 8)
      {
        display.clearDisplay();
        if(ldrValue > 975/2)
        {
          display.fillRect(0,0,128,64,WHITE);          
        }
        shipDisplay();
        if(silahAteslendiMi)
        {
          silahDisplay();          
        }
        if(!olustuMu)
        {
          engelRandomSet();        
        }
        engelDisplay();
        display.display();
        potGuncelle();
      }
      delay(150);
    }

    else if(zorluk == 2)
    {
      
      silahButtonState = digitalRead(SILAH_BUTTON);
      checkIfSilahButtonIsPressed();
      if(gun)
      {
        gun = false;
        silah--;
        if(silah < 0)
        {
          silah = 0;
        }
        if(silah >= 0)
        {
          silahAteslendiMi = true;
          if(potValue < 1)
          {
            s1.satir = 0;
            s1.sira = 1;
          }
          else if(potValue >= 1 && potValue < 2)
          {
            s1.satir = 8;
            s1.sira = 2;
          }
          else if(potValue >= 2 && potValue < 3) 
          {
            s1.satir = 16;
            s1.sira = 3;
          }
          else if(potValue >= 3 && potValue < 4) 
          {
            s1.satir = 24;
            s1.sira = 4;
          }
          else if(potValue >= 4 && potValue < 5) 
          {
            s1.satir = 32;
            s1.sira = 5;
          }
          else if(potValue >= 5 && potValue < 6) 
          {
            s1.satir = 40;
            s1.sira = 6;
          }
          else if(potValue >= 6 && potValue < 7) 
          {
            s1.satir = 48;
            s1.sira = 7;
          } 
          else if(potValue >= 7 && potValue <= 8) 
          {
            s1.satir = 56;
            s1.sira = 8;
          }
        }       
      }
      if(silah == 3)
      {
        digitalWrite(LED_S_3, HIGH);
        digitalWrite(LED_S_2, HIGH);
        digitalWrite(LED_S_1, HIGH);        
      }
      else if(silah == 2)
      {
        digitalWrite(LED_S_3, HIGH);
        digitalWrite(LED_S_2, HIGH);
        digitalWrite(LED_S_1, LOW);        
      }
      else if(silah == 1)
      {
        digitalWrite(LED_S_3, HIGH);
        digitalWrite(LED_S_2, LOW);
        digitalWrite(LED_S_1, LOW);        
      }
      else if(silah == 0)
      {
        digitalWrite(LED_S_3, LOW);
        digitalWrite(LED_S_2, LOW);
        digitalWrite(LED_S_1, LOW);        
      }

      if(can == 3)
      {
        digitalWrite(LED_3, HIGH);
        digitalWrite(LED_2, HIGH);
        digitalWrite(LED_1, HIGH);
      }
      else if(can == 2)
      {
        digitalWrite(LED_3, HIGH);
        digitalWrite(LED_2, HIGH);
        digitalWrite(LED_1, LOW);        
      }
      else if(can == 1)
      {
        digitalWrite(LED_3, HIGH);
        digitalWrite(LED_2, LOW);
        digitalWrite(LED_1, LOW);        
      }
      
      if(oyuncu1.satir == e14.satir && oyuncu1.sutun == engelSutun && e14.tip == 3 || e14.tip == 4)
      {
        if(e14.tip == 3)
        {
          can++;
          delay(10);
          if(can > 3)
          {
            can = 3;
          }
        }
        else if(e14.tip == 4)
        {
          silah++;
          delay(10);
          if(silah > 3)
          {
            silah = 3;
          }          
        }
      } 
      
      if(oyuncu1.satir == e1.satir && oyuncu1.sutun == engelSutun && dokunulmazlik == false || oyuncu1.satir == e2.satir && oyuncu1.sutun == engelSutun && dokunulmazlik == false 
      || oyuncu1.satir == e3.satir && oyuncu1.sutun == engelSutun && dokunulmazlik == false || oyuncu1.satir == e4.satir && oyuncu1.sutun == engelSutun && dokunulmazlik == false 
      || oyuncu1.satir == e5.satir && oyuncu1.sutun == engelSutun && dokunulmazlik == false || oyuncu1.satir == e6.satir && oyuncu1.sutun == engelSutun && dokunulmazlik == false 
      || oyuncu1.satir == e7.satir && oyuncu1.sutun == engelSutun && dokunulmazlik == false)
      {
        timerBuzzer.start();
        tone(BUZZER,261);
        can--;
        dokunulmazlik = true;
        timer.start();

        if(can < 1)
        {
          digitalWrite(LED_3, LOW);
          digitalWrite(LED_2, LOW);
          digitalWrite(LED_1, LOW);
          bittiMi = true;
          basladiMi = false;
          gameOver();          
        }
      }
      if(timerBuzzer.read() > 500)
      {
        timerBuzzer.stop();  
        noTone(BUZZER);  
      }
      if(timer.read() > 3000)
      {
        timer.stop();
        dokunulmazlik = false;
      } 
      if(!sayiyorMu)
      {
        timerDly.start();
        sayiyorMu = true;
        
      }
      if(sayiyorMu)
      {
        if(timerDly.read() > 10000)
        {
          timerDly.stop();
          sayiyorMu = false;
          dly = (dly / 100) * 80;
        }
      }

      skorAyarla();

      if(engelSutun == silahSutun || engelSutun - 8 == silahSutun && s1.sira == e1.satir)
      {
        e1.tip--;  
        silahAteslendiMi = false;    
        silahSutun = 120;  
      }
      else if(engelSutun == silahSutun || engelSutun - 8 == silahSutun && s1.sira == e2.satir)
      {
        e2.tip--; 
        silahAteslendiMi = false; 
        silahSutun = 120; 
      }
      else if(engelSutun == silahSutun || engelSutun - 8 == silahSutun && s1.sira == e3.satir)
      {
        e3.tip--;
        silahAteslendiMi = false;  
        silahSutun = 120; 
      }
      else if(engelSutun == silahSutun || engelSutun - 8 == silahSutun && s1.sira == e4.satir)
      {
        e4.tip--;
        silahAteslendiMi = false;  
        silahSutun = 120; 
      }
      else if(engelSutun == silahSutun || engelSutun - 8 == silahSutun && s1.sira == e5.satir)
      {
        e5.tip--;
        silahAteslendiMi = false; 
        silahSutun = 120;  
      }
      else if(engelSutun == silahSutun || engelSutun - 8 == silahSutun && s1.sira == e6.satir)
      {
        e6.tip--;
        silahAteslendiMi = false;  
        silahSutun = 120; 
      }
      else if(engelSutun == silahSutun || engelSutun - 8 == silahSutun && s1.sira == e7.satir)
      {
        e7.tip--;
        silahAteslendiMi = false;  
        silahSutun = 120; 
      }     
      
      if(potValue < 1)
      {
        display.clearDisplay();
        if(ldrValue > 975/2)
        {
          display.fillRect(0,0,128,64,WHITE);          
        }
        shipDisplay();
        if(silahAteslendiMi)
        {
          silahDisplay();          
        }
        if(!olustuMu)
        {
          engelRandomSet();        
        }
        engelDisplay();        
        display.display();
        potGuncelle();
      }
      else if(potValue >= 1 && potValue < 2)
      {
        display.clearDisplay();
        if(ldrValue > 975/2)
        {
          display.fillRect(0,0,128,64,WHITE);          
        }
        shipDisplay();
        if(silahAteslendiMi)
        {
          silahDisplay();          
        }
        if(!olustuMu)
        {
          engelRandomSet();        
        }
        engelDisplay();
        display.display();
        potGuncelle();
      }
      else if(potValue >= 2 && potValue < 3)
      {
        display.clearDisplay();
        if(ldrValue > 975/2)
        {
          display.fillRect(0,0,128,64,WHITE);          
        }
        shipDisplay();
        if(silahAteslendiMi)
        {
          silahDisplay();          
        }
        if(!olustuMu)
        {
          engelRandomSet();        
        }
        engelDisplay();
        display.display();
        potGuncelle();
      }
      else if(potValue >= 3 && potValue < 4)
      {
        display.clearDisplay();
        if(ldrValue > 975/2)
        {
          display.fillRect(0,0,128,64,WHITE);          
        }
        shipDisplay();
        if(silahAteslendiMi)
        {
          silahDisplay();          
        }
        if(!olustuMu)
        {
          engelRandomSet();        
        }
        engelDisplay();
        display.display();
        potGuncelle();
      }
      else if(potValue >= 4 && potValue < 5)
      {
        display.clearDisplay();
        if(ldrValue > 975/2)
        {
          display.fillRect(0,0,128,64,WHITE);          
        }
        shipDisplay();
        if(silahAteslendiMi)
        {
          silahDisplay();          
        }
        if(!olustuMu)
        {
          engelRandomSet();        
        }
        engelDisplay();
        display.display();
        potGuncelle();
      }
      else if(potValue >= 5 && potValue < 6)
      {
        display.clearDisplay();
        if(ldrValue > 975/2)
        {
          display.fillRect(0,0,128,64,WHITE);          
        }
        shipDisplay();
        if(silahAteslendiMi)
        {
          silahDisplay();          
        }
        if(!olustuMu)
        {
          engelRandomSet();        
        }
        engelDisplay();
        display.display();
        potGuncelle();
      }
      else if(potValue >= 6 && potValue < 7)
      {
        display.clearDisplay();
        if(ldrValue > 975/2)
        {
          display.fillRect(0,0,128,64,WHITE);          
        }
        shipDisplay();
        if(silahAteslendiMi)
        {
          silahDisplay();          
        }
        if(!olustuMu)
        {
          engelRandomSet();        
        }
        engelDisplay();
        display.display();
        potGuncelle();
      }
      else if(potValue >= 7 && potValue <= 8)
      {
        display.clearDisplay();
        if(ldrValue > 975/2)
        {
          display.fillRect(0,0,128,64,WHITE);          
        }
        shipDisplay();
        if(silahAteslendiMi)
        {
          silahDisplay();          
        }
        if(!olustuMu)
        {
          engelRandomSet();        
        }
        engelDisplay();
        display.display();
        potGuncelle();
      }

      delay(dly);
    }
    
    else
    {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE, BLACK);
      display.setCursor(15, 0);
      display.print("Zorluk Secilmedi");
      display.display();  
      page = 1;
      menuitem = 1;
      delay(1000);
      basladiMi = false;
      bittiMi = true;
      drawMenu();   
    }  
          
  }
   
}

void checkIfSilahButtonIsPressed()
{
  if(silahButtonState != lastSilahButtonState)
  {
    if(silahButtonState == 0)
    {
      gun = true;   
    }
    delay(50);
  }  
  lastSilahButtonState = silahButtonState;
}

void checkIfDownButtonIsPressed()
{
    if (downButtonState != lastDownButtonState) 
    {
      if (downButtonState == 0) 
      {
        down=true;
      }
      delay(50);
    }
   lastDownButtonState = downButtonState;
}

void checkIfUpButtonIsPressed()
{
  if (upButtonState != lastUpButtonState) 
  {
    if (upButtonState == 0) {
      up=true;
    }
    delay(50);
  }
   lastUpButtonState = upButtonState;
}

void checkIfSelectButtonIsPressed()
{
   if (selectButtonState != lastSelectButtonState) 
  {
    if (selectButtonState == 0) {
      middle=true;
    }
    delay(50);
  }
   lastSelectButtonState = selectButtonState;
}

void silahDisplay()
{
  silahSutun = silahSutun - 8;
  if(silahSutun < 0)
  {
    silahSutun = 120;
  }
  
  if(ldrValue > 975/2)
  {
    display.drawBitmap(silahSutun, s1.satir, ates, 128/16, 64/8, BLACK);
  }
  else
  {
    display.drawBitmap(silahSutun, s1.satir, ates, 128/16, 64/8, WHITE);
  }
  
}


void gameOver()
{
  while(1)
  {
    if(ldrValue > 975/2)
    {
      display.clearDisplay();
      display.setTextSize(1);
      display.fillRect(0,0,128,64,WHITE);
      display.setTextColor(BLACK, WHITE);
      display.setCursor(15, 0);
      display.print("Oyun Bitti");
      display.display(); 
      dly = 1000;  
      skor = 0;
      tmp = 0;
      orta = 0; 
      page = 1;
      menuitem = 1;
      delay(1000);
      break;
    }
    else
    {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE, BLACK);
      display.setCursor(15, 0);
      display.print("Oyun Bitti");
      display.display(); 
      dly = 1000;
      skor = 0;
      tmp = 0;
      orta = 0;  
      page = 1;
      menuitem = 1;
      delay(1000);
      break;      
    }
    
  }
  drawMenu(); 
}  

void drawMenu()
{  
  if(ldrValue > 975/2)
  {
    if (page==1) 
    {    
      display.setTextSize(1);
      display.clearDisplay();
      display.fillRect(0,0,128,64,WHITE);
      display.setTextColor(BLACK, WHITE);
      display.setCursor(15, 0);
      display.print("MAIN MENU");
      display.setCursor(0, 15);
   
      if (menuitem==1) 
      { 
        display.setTextColor(WHITE, BLACK);
      }
      else 
      {
        display.setTextColor(BLACK, WHITE);
      }
      display.print(">> Zorluk");
      display.setCursor(0, 25);
   
      if (menuitem==2) 
      {
        display.setTextColor(WHITE, BLACK);
      }
      else 
      {
        display.setTextColor(BLACK, WHITE);
      }    
      display.print(">> Baslat");
    
      display.display();
    
    }
    
 
    else if (page==2) 
    {
    
      display.setTextSize(1);
      display.clearDisplay();
      display.fillRect(0,0,128,64,WHITE);
      display.setTextColor(BLACK, WHITE);
      display.setCursor(15, 0);
      display.print("Zorluklar");
      display.setCursor(5, 15);

      if (menuitem==1) 
      { 
        display.setTextColor(WHITE, BLACK);
      }
      else 
      {
        display.setTextColor(BLACK, WHITE);
      }
      display.print(">> 1");
      display.setCursor(5, 25);
   
      if (menuitem==2) 
      {
        display.setTextColor(WHITE, BLACK);
      }
      else 
      {
        display.setTextColor(BLACK, WHITE);
      }    
      display.print(">> 2");
    
      display.display();
    }

  }
  else
  {
    if (page==1) 
    {    
      display.setTextSize(1);
      display.clearDisplay();
      display.setTextColor(WHITE, BLACK);
      display.setCursor(15, 0);
      display.print("MAIN MENU");
      display.setCursor(0, 15);
   
      if (menuitem==1) 
      { 
        display.setTextColor(BLACK, WHITE);
      }
      else 
      {
        display.setTextColor(WHITE, BLACK);
      }
      display.print(">> Zorluk");
      display.setCursor(0, 25);
   
      if (menuitem==2) 
      {
        display.setTextColor(BLACK, WHITE);
      }
      else 
      {
        display.setTextColor(WHITE, BLACK);
      }    
      display.print(">> Baslat");
    
      display.display();
    
    }
    
 
    else if (page==2) 
    {
    
      display.setTextSize(1);
      display.clearDisplay();
      display.setTextColor(WHITE, BLACK);
      display.setCursor(15, 0);
      display.print("Zorluklar");
      display.setCursor(5, 15);

      if (menuitem==1) 
      { 
        display.setTextColor(BLACK, WHITE);
      }
      else 
      {
        display.setTextColor(WHITE, BLACK);
      }
      display.print(">> 1");
      display.setCursor(5, 25);
   
      if (menuitem==2) 
      {
        display.setTextColor(BLACK, WHITE);
      }
      else 
      {
        display.setTextColor(WHITE, BLACK);
      }    
      display.print(">> 2");
    
      display.display();
    }
  
  }  
  
  
}

void potGuncelle()
{
  potValue = analogRead(POT);
  potValue = map(potValue, 0, 1023, 0, 8);  
}

void shipDisplay()
{
  if(ldrValue > 975/2)
  {
    if(potValue < 1)
    {
      oyuncu1.satir = 1;
      display.drawBitmap(oyuncu1.sutun, 0, ship, 128/16, 64/8, BLACK);
    }
    else if(potValue >= 1 && potValue < 2)
    {
      oyuncu1.satir = 2;
      display.drawBitmap(oyuncu1.sutun, 8, ship, 128/16, 64/8, BLACK);
    }
    else if(potValue >= 2 && potValue < 3)
    {
      oyuncu1.satir = 3;
      display.drawBitmap(oyuncu1.sutun, 16, ship, 128/16, 64/8, BLACK);
    }
    else if(potValue >= 3 && potValue < 4)
    {
      oyuncu1.satir = 4;
      display.drawBitmap(oyuncu1.sutun, 24, ship, 128/16, 64/8, BLACK);
    }
    else if(potValue >= 4 && potValue < 5)
    {
      oyuncu1.satir = 5;
      display.drawBitmap(oyuncu1.sutun, 32, ship, 128/16, 64/8, BLACK);
    }
    else if(potValue >= 5 && potValue < 6)
    {
      oyuncu1.satir = 6;
      display.drawBitmap(oyuncu1.sutun, 40, ship, 128/16, 64/8, BLACK);
    }
    else if(potValue >= 6 && potValue < 7)
    {
      oyuncu1.satir = 7;
      display.drawBitmap(oyuncu1.sutun, 48, ship, 128/16, 64/8, BLACK);
    }
    else if(potValue >= 7 && potValue <= 8)
    {
      oyuncu1.satir = 8;
      display.drawBitmap(oyuncu1.sutun, 56, ship, 128/16, 64/8, BLACK);
    }
  }
  else
  {
    if(potValue < 1)
    {
      oyuncu1.satir = 1;
      display.drawBitmap(oyuncu1.sutun, 0, ship, 128/16, 64/8, WHITE);
    }
    else if(potValue >= 1 && potValue < 2)
    {
      oyuncu1.satir = 2;
      display.drawBitmap(oyuncu1.sutun, 8, ship, 128/16, 64/8, WHITE);
    }
    else if(potValue >= 2 && potValue < 3)
    {
      oyuncu1.satir = 3;
      display.drawBitmap(oyuncu1.sutun, 16, ship, 128/16, 64/8, WHITE);
    }
    else if(potValue >= 3 && potValue < 4)
    {
      oyuncu1.satir = 4;
      display.drawBitmap(oyuncu1.sutun, 24, ship, 128/16, 64/8, WHITE);
    }
    else if(potValue >= 4 && potValue < 5)
    {
      oyuncu1.satir = 5;
      display.drawBitmap(oyuncu1.sutun, 32, ship, 128/16, 64/8, WHITE);
    }
    else if(potValue >= 5 && potValue < 6)
    {
      oyuncu1.satir = 6;
      display.drawBitmap(oyuncu1.sutun, 40, ship, 128/16, 64/8, WHITE);
    }
    else if(potValue >= 6 && potValue < 7)
    {
      oyuncu1.satir = 7;
      display.drawBitmap(oyuncu1.sutun, 48, ship, 128/16, 64/8, WHITE);
    }
    else if(potValue >= 7 && potValue <= 8)
    {
      oyuncu1.satir = 8;
      display.drawBitmap(oyuncu1.sutun, 56, ship, 128/16, 64/8, WHITE);
    }
  }
    
}

void engelRandomSet()
{
  e1.satir = random(1,9);
  e2.satir = random(1,9);
  e3.satir = random(1,9);
  e4.satir = random(1,9);
  e5.satir = random(1,9);
  e6.satir = random(1,9);
  e7.satir = random(1,9);
  
  e1.tip = random(1,3);
  e2.tip = random(1,3);
  e3.tip = random(1,3);
  e4.tip = random(1,3);
  e5.tip = random(1,3);
  e6.tip = random(1,3);
  e7.tip = random(1,3);



  while(e1.satir == e2.satir || e1.satir == e3.satir || e1.satir == e4.satir || e1.satir == e5.satir || e1.satir == e6.satir || e1.satir == e7.satir)
  {
    e1.satir = random(1,9);
  }

  while(e2.satir == e1.satir || e2.satir == e3.satir || e2.satir == e4.satir || e2.satir == e5.satir || e2.satir == e6.satir || e2.satir == e7.satir)
  {
    e2.satir = random(1,9);
  }

  while(e3.satir == e1.satir || e3.satir == e2.satir || e3.satir == e4.satir || e3.satir == e5.satir || e3.satir == e6.satir || e3.satir == e7.satir)
  {
    e3.satir = random(1,9);
  }
  
  while(e4.satir == e1.satir || e4.satir == e2.satir || e4.satir == e3.satir || e4.satir == e5.satir || e4.satir == e6.satir || e4.satir == e7.satir)
  {
    e4.satir = random(1,9);
  }

  while(e5.satir == e1.satir || e5.satir == e2.satir || e5.satir == e3.satir || e5.satir == e4.satir || e5.satir == e6.satir || e5.satir == e7.satir)
  {
    e5.satir = random(1,9);
  }

  while(e6.satir == e1.satir || e6.satir == e2.satir || e6.satir == e3.satir || e6.satir == e4.satir || e6.satir == e5.satir || e6.satir == e7.satir)
  {
    e6.satir = random(1,9);
  }

  while(e7.satir == e1.satir || e7.satir == e2.satir || e7.satir == e3.satir || e7.satir == e4.satir || e7.satir == e5.satir || e7.satir == e6.satir)
  {
    e7.satir = random(1,9);
  }

  if(skor % 14 == 0)
  {
    e14.satir = random(1,9);
    while(e14.satir == e1.satir || e14.satir == e2.satir || e14.satir == e3.satir || e14.satir == e4.satir || e14.satir == e5.satir || e14.satir == e6.satir || e14.satir == e7.satir)
    {
      e14.satir = random(1,9);
    }
    e14.tip = random(3,5);
  }
  else
  {
    e14.satir = -1;
    e14.tip = -1;
  }

  

  olustuMu = true;

}

void engelDisplay()
{
  engelSutun = engelSutun + 8;
  if(engelSutun > 136)
  {
    skor++;
    engelSutun = 0;
    engelRandomSet();
  }

  if(ldrValue > 975/2)
  {

    if(e1.satir == 1)
    {
      if(e1.tip == 1)
      {
        display.drawBitmap(engelSutun, 0, cop, 128/16, 64/8, BLACK);     
      }
      if(e1.tip == 2)
      {
        display.drawBitmap(engelSutun, 0, meteor, 128/16, 64/8, BLACK);                
      }

    }
    else if(e1.satir == 2)
    {
      if(e1.tip == 1)
      {
        display.drawBitmap(engelSutun, 8, cop, 128/16, 64/8, BLACK);    
      }
      if(e1.tip == 2)
      {
        display.drawBitmap(engelSutun, 8, meteor, 128/16, 64/8, BLACK);     
      }        
    }
    else if(e1.satir == 3)
    {
      if(e1.tip == 1)
      {
        display.drawBitmap(engelSutun, 16, cop, 128/16, 64/8, BLACK);   
      }
      if(e1.tip == 2)
      {
        display.drawBitmap(engelSutun, 16, meteor, 128/16, 64/8, BLACK);       
      }   
    }
    else if(e1.satir == 4)
    {
     if(e1.tip == 1)
     {
        display.drawBitmap(engelSutun, 24, cop, 128/16, 64/8, BLACK);  
     }
     if(e1.tip == 2)
     {
        display.drawBitmap(engelSutun, 24, meteor, 128/16, 64/8, BLACK);    
     }         
    }
    else if(e1.satir == 5)
    {
      if(e1.tip == 1)
      {
        display.drawBitmap(engelSutun, 32, cop, 128/16, 64/8, BLACK);   
      }
      if(e1.tip == 2)
      {
        display.drawBitmap(engelSutun, 32, meteor, 128/16, 64/8, BLACK);       
      }         
    }
    else if(e1.satir == 6)
    {
      if(e1.tip == 1)
      {
        display.drawBitmap(engelSutun, 40, cop, 128/16, 64/8, BLACK);     
      }
      if(e1.tip == 2)
      {
        display.drawBitmap(engelSutun, 40, meteor, 128/16, 64/8, BLACK);     
      }         
    }
    else if(e1.satir == 7)
    {
      if(e1.tip == 1)
      {
        display.drawBitmap(engelSutun, 48, cop, 128/16, 64/8, BLACK);    
      }
      if(e1.tip == 2)
      {
        display.drawBitmap(engelSutun, 48, meteor, 128/16, 64/8, BLACK);     
      }         
    }
    else if(e1.satir == 8)
    {
      if(e1.tip == 1)
      {
        display.drawBitmap(engelSutun, 56, cop, 128/16, 64/8, BLACK);      
      }
      if(e1.tip == 2)
      {
        display.drawBitmap(engelSutun, 56, meteor, 128/16, 64/8, BLACK);     
      }         
    }

    if(e2.satir == 1)
    {
      if(e2.tip == 1)
      {
        display.drawBitmap(engelSutun, 0, cop, 128/16, 64/8, BLACK);    
      }
      if(e2.tip == 2)
      {
        display.drawBitmap(engelSutun, 0, meteor, 128/16, 64/8, BLACK);      
      }
      
    }
    else if(e2.satir == 2)
    {
      if(e2.tip == 1)
      {
        display.drawBitmap(engelSutun, 8, cop, 128/16, 64/8, BLACK);     
      }
      if(e2.tip == 2)
      {
        display.drawBitmap(engelSutun, 8, meteor, 128/16, 64/8, BLACK);      
      }        
    }
    else if(e2.satir == 3)
    {
      if(e2.tip == 1)
      {
        display.drawBitmap(engelSutun, 16, cop, 128/16, 64/8, BLACK);     
      }
      if(e2.tip == 2)
     {
        display.drawBitmap(engelSutun, 16, meteor, 128/16, 64/8, BLACK);      
      }   
    }
    else if(e2.satir == 4)
    {
      if(e2.tip == 1)
      {
        display.drawBitmap(engelSutun, 24, cop, 128/16, 64/8, BLACK);      
      }
      if(e2.tip == 2)
      {
        display.drawBitmap(engelSutun, 24, meteor, 128/16, 64/8, BLACK);       
      }         
    }
    else if(e2.satir == 5)
    {
      if(e2.tip == 1)
      {
        display.drawBitmap(engelSutun, 32, cop, 128/16, 64/8, BLACK);    
      }
      if(e2.tip == 2)
      {
        display.drawBitmap(engelSutun, 32, meteor, 128/16, 64/8, BLACK);      
      }         
    }
    else if(e2.satir == 6)
    {
      if(e2.tip == 1)
      {
        display.drawBitmap(engelSutun, 40, cop, 128/16, 64/8, BLACK);     
      }
      if(e2.tip == 2)
      {
        display.drawBitmap(engelSutun, 40, meteor, 128/16, 64/8, BLACK);     
      }         
    }
    else if(e2.satir == 7)
    {
      if(e2.tip == 1)
      {
        display.drawBitmap(engelSutun, 48, cop, 128/16, 64/8, BLACK);      
      }
      if(e2.tip == 2)
      {
        display.drawBitmap(engelSutun, 48, meteor, 128/16, 64/8, BLACK);      
      }         
    }
    else if(e2.satir == 8)
    {
      if(e2.tip == 1)
      {
        display.drawBitmap(engelSutun, 56, cop, 128/16, 64/8, BLACK);     
      }
      if(e2.tip == 2)
      {
        display.drawBitmap(engelSutun, 56, meteor, 128/16, 64/8, BLACK);        
      }         
    }

    if(e3.satir == 1)
    {
      if(e3.tip == 1)
      {
        display.drawBitmap(engelSutun, 0, cop, 128/16, 64/8, BLACK);      
      }
      if(e3.tip == 2)
      {
        display.drawBitmap(engelSutun, 0, meteor, 128/16, 64/8, BLACK);        
      }
      
    }
    else if(e3.satir == 2)
    {
      if(e3.tip == 1)
      {
        display.drawBitmap(engelSutun, 8, cop, 128/16, 64/8, BLACK);      
      }
      if(e3.tip == 2)
      {
        display.drawBitmap(engelSutun, 8, meteor, 128/16, 64/8, BLACK);       
      }        
    }
    else if(e3.satir == 3)
    {
      if(e3.tip == 1)
      {
        display.drawBitmap(engelSutun, 16, cop, 128/16, 64/8, BLACK);       
      }
      if(e3.tip == 2)
      {
        display.drawBitmap(engelSutun, 16, meteor, 128/16, 64/8, BLACK);       
      }   
    }
    else if(e3.satir == 4)
    {
      if(e3.tip == 1)
      {
        display.drawBitmap(engelSutun, 24, cop, 128/16, 64/8, BLACK);      
      }
      if(e3.tip == 2)
      {
        display.drawBitmap(engelSutun, 24, meteor, 128/16, 64/8, BLACK);    
      }         
    }
    else if(e3.satir == 5)
    {
      if(e3.tip == 1)
      {
        display.drawBitmap(engelSutun, 32, cop, 128/16, 64/8, BLACK);     
      }
      if(e3.tip == 2)
      {
        display.drawBitmap(engelSutun, 32, meteor, 128/16, 64/8, BLACK);      
      }         
    }
    else if(e3.satir == 6)
    {
      if(e3.tip == 1)
      {
        display.drawBitmap(engelSutun, 40, cop, 128/16, 64/8, BLACK);      
      }
     if(e3.tip == 2)
      {
        display.drawBitmap(engelSutun, 40, meteor, 128/16, 64/8, BLACK);       
      }         
    }
    else if(e3.satir == 7)
    {
      if(e3.tip == 1)
      {
        display.drawBitmap(engelSutun, 48, cop, 128/16, 64/8, BLACK);      
      }
      if(e3.tip == 2)
      {
        display.drawBitmap(engelSutun, 48, meteor, 128/16, 64/8, BLACK);       
      }         
    }
    else if(e3.satir == 8)
    {
      if(e3.tip == 1)
      {
        display.drawBitmap(engelSutun, 56, cop, 128/16, 64/8, BLACK);     
      }
      if(e3.tip == 2)
      {
        display.drawBitmap(engelSutun, 56, meteor, 128/16, 64/8, BLACK);      
      }         
    }

    if(e4.satir == 1)
    {
      if(e4.tip == 1)
      {
        display.drawBitmap(engelSutun, 0, cop, 128/16, 64/8, BLACK);      
      }
      if(e4.tip == 2)
      {
        display.drawBitmap(engelSutun, 0, meteor, 128/16, 64/8, BLACK);      
      }
      
    }
    else if(e4.satir == 2)
    {
      if(e4.tip == 1)
      {
        display.drawBitmap(engelSutun, 8, cop, 128/16, 64/8, BLACK);     
      }
      if(e4.tip == 2)
      {
        display.drawBitmap(engelSutun, 8, meteor, 128/16, 64/8, BLACK);       
      }        
    }
    else if(e4.satir == 3)
    {
      if(e4.tip == 1)
      {
        display.drawBitmap(engelSutun, 16, cop, 128/16, 64/8, BLACK);     
      }
      if(e4.tip == 2)
      {
        display.drawBitmap(engelSutun, 16, meteor, 128/16, 64/8, BLACK);       
      }   
    }
    else if(e4.satir == 4)
    {
      if(e4.tip == 1)
      {
        display.drawBitmap(engelSutun, 24, cop, 128/16, 64/8, BLACK);      
      }
      if(e4.tip == 2)
      {
        display.drawBitmap(engelSutun, 24, meteor, 128/16, 64/8, BLACK);       
      }         
    }
    else if(e4.satir == 5)
      {
      if(e4.tip == 1)
      {
        display.drawBitmap(engelSutun, 32, cop, 128/16, 64/8, BLACK);      
      }
      if(e4.tip == 2)
      {
        display.drawBitmap(engelSutun, 32, meteor, 128/16, 64/8, BLACK);       
      }         
    }
    else if(e4.satir == 6)
    {
      if(e4.tip == 1)
      {
        display.drawBitmap(engelSutun, 40, cop, 128/16, 64/8, BLACK);    
      }
      if(e4.tip == 2)
      {
        display.drawBitmap(engelSutun, 40, meteor, 128/16, 64/8, BLACK);      
      }         
    }
    else if(e4.satir == 7)
    {
      if(e4.tip == 1)
      {
        display.drawBitmap(engelSutun, 48, cop, 128/16, 64/8, BLACK);     
      }
      if(e4.tip == 2)
      {
        display.drawBitmap(engelSutun, 48, meteor, 128/16, 64/8, BLACK);      
      }         
    }
    else if(e4.satir == 8)
    {
      if(e4.tip == 1)
      {
        display.drawBitmap(engelSutun, 56, cop, 128/16, 64/8, BLACK);      
      }
      if(e4.tip == 2)
      {
        display.drawBitmap(engelSutun, 56, meteor, 128/16, 64/8, BLACK);       
      }         
    }

    if(e5.satir == 1)
    {
      if(e5.tip == 1)
      {
        display.drawBitmap(engelSutun, 0, cop, 128/16, 64/8, BLACK);      
      }
      if(e5.tip == 2)
      {
        display.drawBitmap(engelSutun, 0, meteor, 128/16, 64/8, BLACK);      
      }
      
    }
    else if(e5.satir == 2)
    {
      if(e5.tip == 1)
      {
        display.drawBitmap(engelSutun, 8, cop, 128/16, 64/8, BLACK);       
      }
      if(e5.tip == 2)
        {
        display.drawBitmap(engelSutun, 8, meteor, 128/16, 64/8, BLACK);      
      }        
    }
    else if(e5.satir == 3)
    {
      if(e5.tip == 1)
      {
        display.drawBitmap(engelSutun, 16, cop, 128/16, 64/8, BLACK);      
      }
      if(e5.tip == 2)
      {
        display.drawBitmap(engelSutun, 16, meteor, 128/16, 64/8, BLACK);      
      }   
    }
    else if(e5.satir == 4)
    {
      if(e5.tip == 1)
      {
        display.drawBitmap(engelSutun, 24, cop, 128/16, 64/8, BLACK);      
      }
      if(e5.tip == 2)
      {
        display.drawBitmap(engelSutun, 24, meteor, 128/16, 64/8, BLACK);      
      }         
    }
    else if(e5.satir == 5)
    {
      if(e5.tip == 1)
      {
        display.drawBitmap(engelSutun, 32, cop, 128/16, 64/8, BLACK);      
      }
      if(e5.tip == 2)
      {
        display.drawBitmap(engelSutun, 32, meteor, 128/16, 64/8, BLACK);      
      }         
    }
    else if(e5.satir == 6)
    {
      if(e5.tip == 1)
      {
        display.drawBitmap(engelSutun, 40, cop, 128/16, 64/8, BLACK);      
      }
      if(e5.tip == 2)
      {
        display.drawBitmap(engelSutun, 40, meteor, 128/16, 64/8, BLACK);       
      }         
    }
    else if(e5.satir == 7)
    {
      if(e5.tip == 1)
      {
        display.drawBitmap(engelSutun, 48, cop, 128/16, 64/8, BLACK);     
      }
      if(e5.tip == 2)
      {
        display.drawBitmap(engelSutun, 48, meteor, 128/16, 64/8, BLACK);       
      }         
    }
    else if(e5.satir == 8)
    {
      if(e5.tip == 1)
      {
        display.drawBitmap(engelSutun, 56, cop, 128/16, 64/8, BLACK);     
      }
      if(e5.tip == 2)
      {
        display.drawBitmap(engelSutun, 56, meteor, 128/16, 64/8, BLACK);       
      }         
    }

    if(e6.satir == 1)
    {
      if(e6.tip == 1)
      {
        display.drawBitmap(engelSutun, 0, cop, 128/16, 64/8, BLACK);     
      }
      if(e6.tip == 2)
      {
        display.drawBitmap(engelSutun, 0, meteor, 128/16, 64/8, BLACK);       
      }
      
    }
    else if(e6.satir == 2)
    {
      if(e6.tip == 1)
      {
        display.drawBitmap(engelSutun, 8, cop, 128/16, 64/8, BLACK);      
      }
      if(e6.tip == 2)
      {
        display.drawBitmap(engelSutun, 8, meteor, 128/16, 64/8, BLACK);         
      }        
    }
    else if(e6.satir == 3)
    {
      if(e6.tip == 1)
      {
        display.drawBitmap(engelSutun, 16, cop, 128/16, 64/8, BLACK);      
      }
      if(e6.tip == 2)
      {
        display.drawBitmap(engelSutun, 16, meteor, 128/16, 64/8, BLACK);      
      }   
    }
    else if(e6.satir == 4)
    {
      if(e6.tip == 1)
      {
        display.drawBitmap(engelSutun, 24, cop, 128/16, 64/8, BLACK);     
      }
      if(e6.tip == 2)
      {
        display.drawBitmap(engelSutun, 24, meteor, 128/16, 64/8, BLACK);       
      }         
    }
    else if(e6.satir == 5)
    {
      if(e6.tip == 1)
      {
        display.drawBitmap(engelSutun, 32, cop, 128/16, 64/8, BLACK);     
      }
      if(e6.tip == 2)
      {
        display.drawBitmap(engelSutun, 32, meteor, 128/16, 64/8, BLACK);     
      }         
    }
    else if(e6.satir == 6)
    {
      if(e6.tip == 1)
      {
        display.drawBitmap(engelSutun, 40, cop, 128/16, 64/8, BLACK);      
      }
      if(e6.tip == 2)
      {
        display.drawBitmap(engelSutun, 40, meteor, 128/16, 64/8, BLACK);      
      }         
    }
    else if(e6.satir == 7)
    {
      if(e6.tip == 1)
      {
        display.drawBitmap(engelSutun, 48, cop, 128/16, 64/8, BLACK);     
      }
      if(e6.tip == 2)
      {
        display.drawBitmap(engelSutun, 48, meteor, 128/16, 64/8, BLACK);     
      }         
    }
    else if(e6.satir == 8)
    {
      if(e6.tip == 1)
      {
        display.drawBitmap(engelSutun, 56, cop, 128/16, 64/8, BLACK);     
      }
      if(e6.tip == 2)
      {
        display.drawBitmap(engelSutun, 56, meteor, 128/16, 64/8, BLACK);       
      }         
    }

    if(e7.satir == 1)
    {
      if(e7.tip == 1)
      {
        display.drawBitmap(engelSutun, 0, cop, 128/16, 64/8, BLACK);     
      }
      if(e7.tip == 2)
      {
        display.drawBitmap(engelSutun, 0, meteor, 128/16, 64/8, BLACK);     
      }
      
    }
    else if(e7.satir == 2)
    {
      if(e7.tip == 1)
      {
        display.drawBitmap(engelSutun, 8, cop, 128/16, 64/8, BLACK);      
      }
      if(e7.tip == 2)
      {
        display.drawBitmap(engelSutun, 8, meteor, 128/16, 64/8, BLACK);       
      }   
           
    }
    else if(e7.satir == 3)
    {
      if(e7.tip == 1)
      {
        display.drawBitmap(engelSutun, 16, cop, 128/16, 64/8, BLACK);     
      }
      if(e7.tip == 2)
      {
       display.drawBitmap(engelSutun, 16, meteor, 128/16, 64/8, BLACK);     
      }   
    }
    else if(e7.satir == 4)
    {
      if(e7.tip == 1)
      {
        display.drawBitmap(engelSutun, 24, cop, 128/16, 64/8, BLACK);      
      }
      if(e7.tip == 2)
      {
        display.drawBitmap(engelSutun, 24, meteor, 128/16, 64/8, BLACK);      
      }         
    }
    else if(e7.satir == 5)
    {
      if(e7.tip == 1)
      {
        display.drawBitmap(engelSutun, 32, cop, 128/16, 64/8, BLACK);      
      }
      if(e7.tip == 2)
      {
        display.drawBitmap(engelSutun, 32, meteor, 128/16, 64/8, BLACK);     
      }         
    }
    else if(e7.satir == 6)
    {
      if(e7.tip == 1)
      {
        display.drawBitmap(engelSutun, 40, cop, 128/16, 64/8, BLACK);     
      }
      if(e7.tip == 2)
      {
        display.drawBitmap(engelSutun, 40, meteor, 128/16, 64/8, BLACK);      
      }         
    }
    else if(e7.satir == 7)
    {
      if(e7.tip == 1)
      {
        display.drawBitmap(engelSutun, 48, cop, 128/16, 64/8, BLACK);    
      }
      if(e7.tip == 2)
      {
        display.drawBitmap(engelSutun, 48, meteor, 128/16, 64/8, BLACK);      
      }         
    }
    else if(e7.satir == 8)
    {
      if(e7.tip == 1)
      {
        display.drawBitmap(engelSutun, 56, cop, 128/16, 64/8, BLACK);     
      }
      if(e7.tip == 2)
      {
        display.drawBitmap(engelSutun, 56, meteor, 128/16, 64/8, BLACK);        
      }         
    }

    if(e14.satir == 1)
    {
      if(e14.tip == 3)
      {
        display.drawBitmap(engelSutun, 0, heal, 128/16, 64/8, BLACK);     
      }
      if(e14.tip == 4)
      {
        display.drawBitmap(engelSutun, 0, ates, 128/16, 64/8, BLACK);     
      }
      
    }
    else if(e14.satir == 2)
    {
      if(e14.tip == 3)
      {
        display.drawBitmap(engelSutun, 8, heal, 128/16, 64/8, BLACK);      
      }
      if(e14.tip == 4)
      {
        display.drawBitmap(engelSutun, 8, ates, 128/16, 64/8, BLACK);       
      }   
           
    }
    else if(e14.satir == 3)
    {
      if(e14.tip == 3)
      {
        display.drawBitmap(engelSutun, 16, heal, 128/16, 64/8, BLACK);     
      }
      if(e14.tip == 4)
      {
       display.drawBitmap(engelSutun, 16, ates, 128/16, 64/8, BLACK);     
      }   
    }
    else if(e14.satir == 4)
    {
      if(e14.tip == 3)
      {
        display.drawBitmap(engelSutun, 24, heal, 128/16, 64/8, BLACK);      
      }
      if(e14.tip == 4)
      {
        display.drawBitmap(engelSutun, 24, ates, 128/16, 64/8, BLACK);      
      }         
    }
    else if(e14.satir == 5)
    {
      if(e14.tip == 3)
      {
        display.drawBitmap(engelSutun, 32, heal, 128/16, 64/8, BLACK);      
      }
      if(e14.tip == 4)
      {
        display.drawBitmap(engelSutun, 32, ates, 128/16, 64/8, BLACK);     
      }         
    }
    else if(e14.satir == 6)
    {
      if(e14.tip == 3)
      {
        display.drawBitmap(engelSutun, 40, heal, 128/16, 64/8, BLACK);     
      }
      if(e14.tip == 4)
      {
        display.drawBitmap(engelSutun, 40, ates, 128/16, 64/8, BLACK);      
      }         
    }
    else if(e14.satir == 7)
    {
      if(e14.tip == 3)
      {
        display.drawBitmap(engelSutun, 48, heal, 128/16, 64/8, BLACK);    
      }
      if(e14.tip == 4)
      {
        display.drawBitmap(engelSutun, 48, ates, 128/16, 64/8, BLACK);      
      }         
    }
    else if(e14.satir == 8)
    {
      if(e14.tip == 3)
      {
        display.drawBitmap(engelSutun, 56, heal, 128/16, 64/8, BLACK);     
      }
      if(e14.tip == 4)
      {
        display.drawBitmap(engelSutun, 56, ates, 128/16, 64/8, BLACK);        
      }         
    }

    
  }
  else 
  {
    if(e1.satir == 1)
    {
      if(e1.tip == 1)
      {
        display.drawBitmap(engelSutun, 0, cop, 128/16, 64/8, WHITE);     
      }
      if(e1.tip == 2)
      {
        display.drawBitmap(engelSutun, 0, meteor, 128/16, 64/8, WHITE);                
      }
    }
    else if(e1.satir == 2)
    {
      if(e1.tip == 1)
      {
        display.drawBitmap(engelSutun, 8, cop, 128/16, 64/8, WHITE);    
      }
      if(e1.tip == 2)
      {
        display.drawBitmap(engelSutun, 8, meteor, 128/16, 64/8, WHITE);     
      }        
    }
    else if(e1.satir == 3)
    {
      if(e1.tip == 1)
      {
        display.drawBitmap(engelSutun, 16, cop, 128/16, 64/8, WHITE);   
      }
      if(e1.tip == 2)
      {
        display.drawBitmap(engelSutun, 16, meteor, 128/16, 64/8, WHITE);       
      }   
    }
    else if(e1.satir == 4)
    {
     if(e1.tip == 1)
     {
        display.drawBitmap(engelSutun, 24, cop, 128/16, 64/8, WHITE);  
     }
     if(e1.tip == 2)
     {
        display.drawBitmap(engelSutun, 24, meteor, 128/16, 64/8, WHITE);    
     }         
    }
    else if(e1.satir == 5)
    {
      if(e1.tip == 1)
      {
        display.drawBitmap(engelSutun, 32, cop, 128/16, 64/8, WHITE);   
      }
      if(e1.tip == 2)
      {
        display.drawBitmap(engelSutun, 32, meteor, 128/16, 64/8, WHITE);       
      }         
    }
    else if(e1.satir == 6)
    {
      if(e1.tip == 1)
      {
        display.drawBitmap(engelSutun, 40, cop, 128/16, 64/8, WHITE);     
      }
      if(e1.tip == 2)
      {
        display.drawBitmap(engelSutun, 40, meteor, 128/16, 64/8, WHITE);     
      }         
    }
    else if(e1.satir == 7)
    {
      if(e1.tip == 1)
      {
        display.drawBitmap(engelSutun, 48, cop, 128/16, 64/8, WHITE);    
      }
      if(e1.tip == 2)
      {
        display.drawBitmap(engelSutun, 48, meteor, 128/16, 64/8, WHITE);     
      }         
    }
    else if(e1.satir == 8)
    {
      if(e1.tip == 1)
      {
        display.drawBitmap(engelSutun, 56, cop, 128/16, 64/8, WHITE);      
      }
      if(e1.tip == 2)
      {
        display.drawBitmap(engelSutun, 56, meteor, 128/16, 64/8, WHITE);     
      }         
    }

    if(e2.satir == 1)
    {
      if(e2.tip == 1)
      {
        display.drawBitmap(engelSutun, 0, cop, 128/16, 64/8, WHITE);    
      }
      if(e2.tip == 2)
      {
        display.drawBitmap(engelSutun, 0, meteor, 128/16, 64/8, WHITE);      
      }
      
    }
    else if(e2.satir == 2)
    {
      if(e2.tip == 1)
      {
        display.drawBitmap(engelSutun, 8, cop, 128/16, 64/8, WHITE);     
      }
      if(e2.tip == 2)
      {
        display.drawBitmap(engelSutun, 8, meteor, 128/16, 64/8, WHITE);      
      }        
    }
    else if(e2.satir == 3)
    {
      if(e2.tip == 1)
      {
        display.drawBitmap(engelSutun, 16, cop, 128/16, 64/8, WHITE);     
      }
      if(e2.tip == 2)
     {
        display.drawBitmap(engelSutun, 16, meteor, 128/16, 64/8, WHITE);      
      }   
    }
    else if(e2.satir == 4)
    {
      if(e2.tip == 1)
      {
        display.drawBitmap(engelSutun, 24, cop, 128/16, 64/8, WHITE);      
      }
      if(e2.tip == 2)
      {
        display.drawBitmap(engelSutun, 24, meteor, 128/16, 64/8, WHITE);       
      }         
    }
    else if(e2.satir == 5)
    {
      if(e2.tip == 1)
      {
        display.drawBitmap(engelSutun, 32, cop, 128/16, 64/8, WHITE);    
      }
      if(e2.tip == 2)
      {
        display.drawBitmap(engelSutun, 32, meteor, 128/16, 64/8, WHITE);      
      }         
    }
    else if(e2.satir == 6)
    {
      if(e2.tip == 1)
      {
        display.drawBitmap(engelSutun, 40, cop, 128/16, 64/8, WHITE);     
      }
      if(e2.tip == 2)
      {
        display.drawBitmap(engelSutun, 40, meteor, 128/16, 64/8, WHITE);     
      }         
    }
    else if(e2.satir == 7)
    {
      if(e2.tip == 1)
      {
        display.drawBitmap(engelSutun, 48, cop, 128/16, 64/8, WHITE);      
      }
      if(e2.tip == 2)
      {
        display.drawBitmap(engelSutun, 48, meteor, 128/16, 64/8, WHITE);      
      }         
    }
    else if(e2.satir == 8)
    {
      if(e2.tip == 1)
      {
        display.drawBitmap(engelSutun, 56, cop, 128/16, 64/8, WHITE);     
      }
      if(e2.tip == 2)
      {
        display.drawBitmap(engelSutun, 56, meteor, 128/16, 64/8, WHITE);        
      }         
    }

    if(e3.satir == 1)
    {
      if(e3.tip == 1)
      {
        display.drawBitmap(engelSutun, 0, cop, 128/16, 64/8, WHITE);      
      }
      if(e3.tip == 2)
      {
        display.drawBitmap(engelSutun, 0, meteor, 128/16, 64/8, WHITE);        
      }
      
    }
    else if(e3.satir == 2)
    {
      if(e3.tip == 1)
      {
        display.drawBitmap(engelSutun, 8, cop, 128/16, 64/8, WHITE);      
      }
      if(e3.tip == 2)
      {
        display.drawBitmap(engelSutun, 8, meteor, 128/16, 64/8, WHITE);       
      }        
    }
    else if(e3.satir == 3)
    {
      if(e3.tip == 1)
      {
        display.drawBitmap(engelSutun, 16, cop, 128/16, 64/8, WHITE);       
      }
      if(e3.tip == 2)
      {
        display.drawBitmap(engelSutun, 16, meteor, 128/16, 64/8, WHITE);       
      }   
    }
    else if(e3.satir == 4)
    {
      if(e3.tip == 1)
      {
        display.drawBitmap(engelSutun, 24, cop, 128/16, 64/8, WHITE);      
      }
      if(e3.tip == 2)
      {
        display.drawBitmap(engelSutun, 24, meteor, 128/16, 64/8, WHITE);    
      }         
    }
    else if(e3.satir == 5)
    {
      if(e3.tip == 1)
      {
        display.drawBitmap(engelSutun, 32, cop, 128/16, 64/8, WHITE);     
      }
      if(e3.tip == 2)
      {
        display.drawBitmap(engelSutun, 32, meteor, 128/16, 64/8, WHITE);      
      }         
    }
    else if(e3.satir == 6)
    {
      if(e3.tip == 1)
      {
        display.drawBitmap(engelSutun, 40, cop, 128/16, 64/8, WHITE);      
      }
     if(e3.tip == 2)
      {
        display.drawBitmap(engelSutun, 40, meteor, 128/16, 64/8, WHITE);       
      }         
    }
    else if(e3.satir == 7)
    {
      if(e3.tip == 1)
      {
        display.drawBitmap(engelSutun, 48, cop, 128/16, 64/8, WHITE);      
      }
      if(e3.tip == 2)
      {
        display.drawBitmap(engelSutun, 48, meteor, 128/16, 64/8, WHITE);       
      }         
    }
    else if(e3.satir == 8)
    {
      if(e3.tip == 1)
      {
        display.drawBitmap(engelSutun, 56, cop, 128/16, 64/8, WHITE);     
      }
      if(e3.tip == 2)
      {
        display.drawBitmap(engelSutun, 56, meteor, 128/16, 64/8, WHITE);      
      }         
    }

    if(e4.satir == 1)
    {
      if(e4.tip == 1)
      {
        display.drawBitmap(engelSutun, 0, cop, 128/16, 64/8, WHITE);      
      }
      if(e4.tip == 2)
      {
        display.drawBitmap(engelSutun, 0, meteor, 128/16, 64/8, WHITE);      
      }
      
    }
    else if(e4.satir == 2)
    {
      if(e4.tip == 1)
      {
        display.drawBitmap(engelSutun, 8, cop, 128/16, 64/8, WHITE);     
      }
      if(e4.tip == 2)
      {
        display.drawBitmap(engelSutun, 8, meteor, 128/16, 64/8, WHITE);       
      }        
    }
    else if(e4.satir == 3)
    {
      if(e4.tip == 1)
      {
        display.drawBitmap(engelSutun, 16, cop, 128/16, 64/8, WHITE);     
      }
      if(e4.tip == 2)
      {
        display.drawBitmap(engelSutun, 16, meteor, 128/16, 64/8, WHITE);       
      }   
    }
    else if(e4.satir == 4)
    {
      if(e4.tip == 1)
      {
        display.drawBitmap(engelSutun, 24, cop, 128/16, 64/8, WHITE);      
      }
      if(e4.tip == 2)
      {
        display.drawBitmap(engelSutun, 24, meteor, 128/16, 64/8, WHITE);       
      }         
    }
    else if(e4.satir == 5)
      {
      if(e4.tip == 1)
      {
        display.drawBitmap(engelSutun, 32, cop, 128/16, 64/8, WHITE);      
      }
      if(e4.tip == 2)
      {
        display.drawBitmap(engelSutun, 32, meteor, 128/16, 64/8, WHITE);       
      }         
    }
    else if(e4.satir == 6)
    {
      if(e4.tip == 1)
      {
        display.drawBitmap(engelSutun, 40, cop, 128/16, 64/8, WHITE);    
      }
      if(e4.tip == 2)
      {
        display.drawBitmap(engelSutun, 40, meteor, 128/16, 64/8, WHITE);      
      }         
    }
    else if(e4.satir == 7)
    {
      if(e4.tip == 1)
      {
        display.drawBitmap(engelSutun, 48, cop, 128/16, 64/8, WHITE);     
      }
      if(e4.tip == 2)
      {
        display.drawBitmap(engelSutun, 48, meteor, 128/16, 64/8, WHITE);      
      }         
    }
    else if(e4.satir == 8)
    {
      if(e4.tip == 1)
      {
        display.drawBitmap(engelSutun, 56, cop, 128/16, 64/8, WHITE);      
      }
      if(e4.tip == 2)
      {
        display.drawBitmap(engelSutun, 56, meteor, 128/16, 64/8, WHITE);       
      }         
    }

    if(e5.satir == 1)
    {
      if(e5.tip == 1)
      {
        display.drawBitmap(engelSutun, 0, cop, 128/16, 64/8, WHITE);      
      }
      if(e5.tip == 2)
      {
        display.drawBitmap(engelSutun, 0, meteor, 128/16, 64/8, WHITE);      
      }
      
    }
    else if(e5.satir == 2)
    {
      if(e5.tip == 1)
      {
        display.drawBitmap(engelSutun, 8, cop, 128/16, 64/8, WHITE);       
      }
      if(e5.tip == 2)
        {
        display.drawBitmap(engelSutun, 8, meteor, 128/16, 64/8, WHITE);      
      }        
    }
    else if(e5.satir == 3)
    {
      if(e5.tip == 1)
      {
        display.drawBitmap(engelSutun, 16, cop, 128/16, 64/8, WHITE);      
      }
      if(e5.tip == 2)
      {
        display.drawBitmap(engelSutun, 16, meteor, 128/16, 64/8, WHITE);      
      }   
    }
    else if(e5.satir == 4)
    {
      if(e5.tip == 1)
      {
        display.drawBitmap(engelSutun, 24, cop, 128/16, 64/8, WHITE);      
      }
      if(e5.tip == 2)
      {
        display.drawBitmap(engelSutun, 24, meteor, 128/16, 64/8, WHITE);      
      }         
    }
    else if(e5.satir == 5)
    {
      if(e5.tip == 1)
      {
        display.drawBitmap(engelSutun, 32, cop, 128/16, 64/8, WHITE);      
      }
      if(e5.tip == 2)
      {
        display.drawBitmap(engelSutun, 32, meteor, 128/16, 64/8, WHITE);      
      }         
    }
    else if(e5.satir == 6)
    {
      if(e5.tip == 1)
      {
        display.drawBitmap(engelSutun, 40, cop, 128/16, 64/8, WHITE);      
      }
      if(e5.tip == 2)
      {
        display.drawBitmap(engelSutun, 40, meteor, 128/16, 64/8, WHITE);       
      }         
    }
    else if(e5.satir == 7)
    {
      if(e5.tip == 1)
      {
        display.drawBitmap(engelSutun, 48, cop, 128/16, 64/8, WHITE);     
      }
      if(e5.tip == 2)
      {
        display.drawBitmap(engelSutun, 48, meteor, 128/16, 64/8, WHITE);       
      }         
    }
    else if(e5.satir == 8)
    {
      if(e5.tip == 1)
      {
        display.drawBitmap(engelSutun, 56, cop, 128/16, 64/8, WHITE);     
      }
      if(e5.tip == 2)
      {
        display.drawBitmap(engelSutun, 56, meteor, 128/16, 64/8, WHITE);       
      }         
    }

    if(e6.satir == 1)
    {
      if(e6.tip == 1)
      {
        display.drawBitmap(engelSutun, 0, cop, 128/16, 64/8, WHITE);     
      }
      if(e6.tip == 2)
      {
        display.drawBitmap(engelSutun, 0, meteor, 128/16, 64/8, WHITE);       
      }
      
    }
    else if(e6.satir == 2)
    {
      if(e6.tip == 1)
      {
        display.drawBitmap(engelSutun, 8, cop, 128/16, 64/8, WHITE);      
      }
      if(e6.tip == 2)
      {
        display.drawBitmap(engelSutun, 8, meteor, 128/16, 64/8, WHITE);         
      }        
    }
    else if(e6.satir == 3)
    {
      if(e6.tip == 1)
      {
        display.drawBitmap(engelSutun, 16, cop, 128/16, 64/8, WHITE);      
      }
      if(e6.tip == 2)
      {
        display.drawBitmap(engelSutun, 16, meteor, 128/16, 64/8, WHITE);      
      }   
    }
    else if(e6.satir == 4)
    {
      if(e6.tip == 1)
      {
        display.drawBitmap(engelSutun, 24, cop, 128/16, 64/8, WHITE);     
      }
      if(e6.tip == 2)
      {
        display.drawBitmap(engelSutun, 24, meteor, 128/16, 64/8, WHITE);       
      }         
    }
    else if(e6.satir == 5)
    {
      if(e6.tip == 1)
      {
        display.drawBitmap(engelSutun, 32, cop, 128/16, 64/8, WHITE);     
      }
      if(e6.tip == 2)
      {
        display.drawBitmap(engelSutun, 32, meteor, 128/16, 64/8, WHITE);     
      }         
    }
    else if(e6.satir == 6)
    {
      if(e6.tip == 1)
      {
        display.drawBitmap(engelSutun, 40, cop, 128/16, 64/8, WHITE);      
      }
      if(e6.tip == 2)
      {
        display.drawBitmap(engelSutun, 40, meteor, 128/16, 64/8, WHITE);      
      }         
    }
    else if(e6.satir == 7)
    {
      if(e6.tip == 1)
      {
        display.drawBitmap(engelSutun, 48, cop, 128/16, 64/8, WHITE);     
      }
      if(e6.tip == 2)
      {
        display.drawBitmap(engelSutun, 48, meteor, 128/16, 64/8, WHITE);     
      }         
    }
    else if(e6.satir == 8)
    {
      if(e6.tip == 1)
      {
        display.drawBitmap(engelSutun, 56, cop, 128/16, 64/8, WHITE);     
      }
      if(e6.tip == 2)
      {
        display.drawBitmap(engelSutun, 56, meteor, 128/16, 64/8, WHITE);       
      }         
    }

    if(e7.satir == 1)
    {
      if(e7.tip == 1)
      {
        display.drawBitmap(engelSutun, 0, cop, 128/16, 64/8, WHITE);     
      }
      if(e7.tip == 2)
      {
        display.drawBitmap(engelSutun, 0, meteor, 128/16, 64/8, WHITE);     
      }
      
    }
    else if(e7.satir == 2)
    {
      if(e7.tip == 1)
      {
        display.drawBitmap(engelSutun, 8, cop, 128/16, 64/8, WHITE);      
      }
      if(e7.tip == 2)
      {
        display.drawBitmap(engelSutun, 8, meteor, 128/16, 64/8, WHITE);       
      }   
           
    }
    else if(e7.satir == 3)
    {
      if(e7.tip == 1)
      {
        display.drawBitmap(engelSutun, 16, cop, 128/16, 64/8, WHITE);     
      }
      if(e7.tip == 2)
      {
       display.drawBitmap(engelSutun, 16, meteor, 128/16, 64/8, WHITE);     
      }   
    }
    else if(e7.satir == 4)
    {
      if(e7.tip == 1)
      {
        display.drawBitmap(engelSutun, 24, cop, 128/16, 64/8, WHITE);      
      }
      if(e7.tip == 2)
      {
        display.drawBitmap(engelSutun, 24, meteor, 128/16, 64/8, WHITE);      
      }         
    }
    else if(e7.satir == 5)
    {
      if(e7.tip == 1)
      {
        display.drawBitmap(engelSutun, 32, cop, 128/16, 64/8, WHITE);      
      }
      if(e7.tip == 2)
      {
        display.drawBitmap(engelSutun, 32, meteor, 128/16, 64/8, WHITE);     
      }         
    }
    else if(e7.satir == 6)
    {
      if(e7.tip == 1)
      {
        display.drawBitmap(engelSutun, 40, cop, 128/16, 64/8, WHITE);     
      }
      if(e7.tip == 2)
      {
        display.drawBitmap(engelSutun, 40, meteor, 128/16, 64/8, WHITE);      
      }         
    }
    else if(e7.satir == 7)
    {
      if(e7.tip == 1)
      {
        display.drawBitmap(engelSutun, 48, cop, 128/16, 64/8, WHITE);    
      }
      if(e7.tip == 2)
      {
        display.drawBitmap(engelSutun, 48, meteor, 128/16, 64/8, WHITE);      
      }         
    }
    else if(e7.satir == 8)
    {
      if(e7.tip == 1)
      {
        display.drawBitmap(engelSutun, 56, cop, 128/16, 64/8, WHITE);     
      }
      if(e7.tip == 2)
      {
        display.drawBitmap(engelSutun, 56, meteor, 128/16, 64/8, WHITE);        
      }         
    }

    if(e14.satir == 1)
    {
      if(e14.tip == 3)
      {
        display.drawBitmap(engelSutun, 0, heal, 128/16, 64/8, WHITE);     
      }
      if(e14.tip == 4)
      {
        display.drawBitmap(engelSutun, 0, ates, 128/16, 64/8, WHITE);     
      }
      
    }
    else if(e14.satir == 2)
    {
      if(e14.tip == 3)
      {
        display.drawBitmap(engelSutun, 8, heal, 128/16, 64/8, WHITE);      
      }
      if(e14.tip == 4)
      {
        display.drawBitmap(engelSutun, 8, ates, 128/16, 64/8, WHITE);       
      }   
           
    }
    else if(e14.satir == 3)
    {
      if(e14.tip == 3)
      {
        display.drawBitmap(engelSutun, 16, heal, 128/16, 64/8, WHITE);     
      }
      if(e14.tip == 4)
      {
       display.drawBitmap(engelSutun, 16, ates, 128/16, 64/8, WHITE);     
      }   
    }
    else if(e14.satir == 4)
    {
      if(e14.tip == 3)
      {
        display.drawBitmap(engelSutun, 24, heal, 128/16, 64/8, WHITE);      
      }
      if(e14.tip == 4)
      {
        display.drawBitmap(engelSutun, 24, ates, 128/16, 64/8, WHITE);      
      }         
    }
    else if(e14.satir == 5)
    {
      if(e14.tip == 3)
      {
        display.drawBitmap(engelSutun, 32, heal, 128/16, 64/8, WHITE);      
      }
      if(e14.tip == 4)
      {
        display.drawBitmap(engelSutun, 32, ates, 128/16, 64/8, WHITE);     
      }         
    }
    else if(e14.satir == 6)
    {
      if(e14.tip == 3)
      {
        display.drawBitmap(engelSutun, 40, heal, 128/16, 64/8, WHITE);     
      }
      if(e14.tip == 4)
      {
        display.drawBitmap(engelSutun, 40, ates, 128/16, 64/8, WHITE);      
      }         
    }
    else if(e14.satir == 7)
    {
      if(e14.tip == 3)
      {
        display.drawBitmap(engelSutun, 48, heal, 128/16, 64/8, WHITE);    
      }
      if(e14.tip == 4)
      {
        display.drawBitmap(engelSutun, 48, ates, 128/16, 64/8, WHITE);      
      }         
    }
    else if(e14.satir == 8)
    {
      if(e14.tip == 3)
      {
        display.drawBitmap(engelSutun, 56, heal, 128/16, 64/8, WHITE);     
      }
      if(e14.tip == 4)
      {
        display.drawBitmap(engelSutun, 56, ates, 128/16, 64/8, WHITE);        
      }         
    }

  }
  
}

void bir_sifir()
{
  digitalWrite(22,HIGH);
  digitalWrite(23,HIGH);
  digitalWrite(24,HIGH);
  digitalWrite(25,HIGH);
  digitalWrite(26,HIGH);
  digitalWrite(27,HIGH);
  digitalWrite(28,LOW);    
}
void iki_sifir()
{
  digitalWrite(29,HIGH);
  digitalWrite(30,HIGH);
  digitalWrite(31,HIGH);
  digitalWrite(32,HIGH);
  digitalWrite(33,HIGH);
  digitalWrite(34,HIGH);
  digitalWrite(35,LOW);    
}
void uc_sifir()
{
  digitalWrite(36,HIGH);
  digitalWrite(37,HIGH);
  digitalWrite(38,HIGH);
  digitalWrite(39,HIGH);
  digitalWrite(40,HIGH);
  digitalWrite(41,HIGH);
  digitalWrite(42,LOW);    
}

void bir_bir()
{
  digitalWrite(22,LOW);
  digitalWrite(23,HIGH);
  digitalWrite(24,HIGH);
  digitalWrite(25,LOW);
  digitalWrite(26,LOW);
  digitalWrite(27,LOW);
  digitalWrite(28,LOW);
}
void iki_bir()
{
  digitalWrite(29,LOW);
  digitalWrite(30,HIGH);
  digitalWrite(31,HIGH);
  digitalWrite(32,LOW);
  digitalWrite(33,LOW);
  digitalWrite(34,LOW);
  digitalWrite(35,LOW);
}
void uc_bir()
{
  digitalWrite(36,LOW);
  digitalWrite(37,HIGH);
  digitalWrite(38,HIGH);
  digitalWrite(39,LOW);
  digitalWrite(40,LOW);
  digitalWrite(41,LOW);
  digitalWrite(42,LOW);
}

void bir_iki()
{
  digitalWrite(22,HIGH);
  digitalWrite(23,HIGH);
  digitalWrite(24,LOW);
  digitalWrite(25,HIGH);
  digitalWrite(26,HIGH);
  digitalWrite(27,LOW);
  digitalWrite(28,HIGH);
}
void iki_iki()
{
  digitalWrite(29,HIGH);
  digitalWrite(30,HIGH);
  digitalWrite(31,LOW);
  digitalWrite(32,HIGH);
  digitalWrite(33,HIGH);
  digitalWrite(34,LOW);
  digitalWrite(35,HIGH);
}
void uc_iki()
{
  digitalWrite(36,HIGH);
  digitalWrite(37,HIGH);
  digitalWrite(38,LOW);
  digitalWrite(39,HIGH);
  digitalWrite(40,HIGH);
  digitalWrite(41,LOW);
  digitalWrite(42,HIGH);
}

void bir_uc()
{
  digitalWrite(22,HIGH);
  digitalWrite(23,HIGH);
  digitalWrite(24,HIGH);
  digitalWrite(25,HIGH);
  digitalWrite(26,LOW);
  digitalWrite(27,LOW);
  digitalWrite(28,HIGH);
}
void iki_uc()
{
  digitalWrite(29,HIGH);
  digitalWrite(30,HIGH);
  digitalWrite(31,HIGH);
  digitalWrite(32,HIGH);
  digitalWrite(33,LOW);
  digitalWrite(34,LOW);
  digitalWrite(35,HIGH);
}
void uc_uc()
{
  digitalWrite(36,HIGH);
  digitalWrite(37,HIGH);
  digitalWrite(38,HIGH);
  digitalWrite(39,HIGH);
  digitalWrite(40,LOW);
  digitalWrite(41,LOW);
  digitalWrite(42,HIGH);
}

void bir_dort()
{
  digitalWrite(22,LOW);
  digitalWrite(23,HIGH);
  digitalWrite(24,HIGH);
  digitalWrite(25,LOW);
  digitalWrite(26,LOW);
  digitalWrite(27,HIGH);
  digitalWrite(28,HIGH);
}
void iki_dort()
{
  digitalWrite(29,LOW);
  digitalWrite(30,HIGH);
  digitalWrite(31,HIGH);
  digitalWrite(32,LOW);
  digitalWrite(33,LOW);
  digitalWrite(34,HIGH);
  digitalWrite(35,HIGH);
}
void uc_dort()
{
  digitalWrite(36,LOW);
  digitalWrite(37,HIGH);
  digitalWrite(38,HIGH);
  digitalWrite(39,LOW);
  digitalWrite(40,LOW);
  digitalWrite(41,HIGH);
  digitalWrite(42,HIGH);
}

void bir_bes()
{
  digitalWrite(22,HIGH);//1
  digitalWrite(23,LOW);//2
  digitalWrite(24,HIGH);//3
  digitalWrite(25,HIGH);//4
  digitalWrite(26,LOW);//5
  digitalWrite(27,HIGH);//6
  digitalWrite(28,HIGH);//7
}
void iki_bes()
{
  digitalWrite(29,HIGH);//1
  digitalWrite(30,LOW);//2
  digitalWrite(31,HIGH);//3
  digitalWrite(32,HIGH);//4
  digitalWrite(33,LOW);//5
  digitalWrite(34,HIGH);//6
  digitalWrite(35,HIGH);//7
}
void uc_bes()
{
  digitalWrite(36,HIGH);//1
  digitalWrite(37,LOW);//2
  digitalWrite(38,HIGH);//3
  digitalWrite(39,HIGH);//4
  digitalWrite(40,LOW);//5
  digitalWrite(41,HIGH);//6
  digitalWrite(42,HIGH);//7
}

void bir_alti()
{
  digitalWrite(22,HIGH);//1
  digitalWrite(23,LOW);//2
  digitalWrite(24,HIGH);//3
  digitalWrite(25,HIGH);//4
  digitalWrite(26,HIGH);//5
  digitalWrite(27,HIGH);//6
  digitalWrite(28,HIGH);//7
}
void iki_alti()
{
  digitalWrite(29,HIGH);//1
  digitalWrite(30,LOW);//2
  digitalWrite(31,HIGH);//3
  digitalWrite(32,HIGH);//4
  digitalWrite(33,HIGH);//5
  digitalWrite(34,HIGH);//6
  digitalWrite(35,HIGH);//7
}
void uc_alti()
{
  digitalWrite(36,HIGH);//1
  digitalWrite(37,LOW);//2
  digitalWrite(38,HIGH);//3
  digitalWrite(39,HIGH);//4
  digitalWrite(40,HIGH);//5
  digitalWrite(41,HIGH);//6
  digitalWrite(42,HIGH);//7
}

void bir_yedi()
{
  digitalWrite(22,HIGH);//1
  digitalWrite(23,HIGH);//2
  digitalWrite(24,HIGH);//3
  digitalWrite(25,LOW);//4
  digitalWrite(26,LOW);//5
  digitalWrite(27,LOW);//6
  digitalWrite(28,LOW);//7
}
void iki_yedi()
{
  digitalWrite(29,HIGH);//1
  digitalWrite(30,HIGH);//2
  digitalWrite(31,HIGH);//3
  digitalWrite(32,LOW);//4
  digitalWrite(33,LOW);//5
  digitalWrite(34,LOW);//6
  digitalWrite(35,LOW);//7
}
void uc_yedi()
{
  digitalWrite(36,HIGH);//1
  digitalWrite(37,HIGH);//2
  digitalWrite(38,HIGH);//3
  digitalWrite(39,LOW);//4
  digitalWrite(40,LOW);//5
  digitalWrite(41,LOW);//6
  digitalWrite(42,LOW);//7
}

void bir_sekiz()
{
  digitalWrite(22,HIGH);//1
  digitalWrite(23,HIGH);//2
  digitalWrite(24,HIGH);//3
  digitalWrite(25,HIGH);//4
  digitalWrite(26,HIGH);//5
  digitalWrite(27,HIGH);//6
  digitalWrite(28,HIGH);//7
}
void iki_sekiz()
{
  digitalWrite(29,HIGH);//1
  digitalWrite(30,HIGH);//2
  digitalWrite(31,HIGH);//3
  digitalWrite(32,HIGH);//4
  digitalWrite(33,HIGH);//5
  digitalWrite(34,HIGH);//6
  digitalWrite(35,HIGH);//7
}
void uc_sekiz()
{
  digitalWrite(36,HIGH);//1
  digitalWrite(37,HIGH);//2
  digitalWrite(38,HIGH);//3
  digitalWrite(39,HIGH);//4
  digitalWrite(40,HIGH);//5
  digitalWrite(41,HIGH);//6
  digitalWrite(42,HIGH);//7
}

void bir_dokuz()
{
  digitalWrite(22,HIGH);//1
  digitalWrite(23,HIGH);//2
  digitalWrite(24,HIGH);//3
  digitalWrite(25,HIGH);//4
  digitalWrite(26,LOW);//5
  digitalWrite(27,HIGH);//6
  digitalWrite(28,HIGH);//7
}
void iki_dokuz()
{
  digitalWrite(29,HIGH);//1
  digitalWrite(30,HIGH);//2
  digitalWrite(31,HIGH);//3
  digitalWrite(32,HIGH);//4
  digitalWrite(33,LOW);//5
  digitalWrite(34,HIGH);//6
  digitalWrite(35,HIGH);//7
}
void uc_dokuz()
{
  digitalWrite(36,HIGH);//1
  digitalWrite(37,HIGH);//2
  digitalWrite(38,HIGH);//3
  digitalWrite(39,HIGH);//4
  digitalWrite(40,LOW);//5
  digitalWrite(41,HIGH);//6
  digitalWrite(42,HIGH);//7
}

void bir_kapali()
{
  digitalWrite(22,LOW);//1
  digitalWrite(23,LOW);//2
  digitalWrite(24,LOW);//3
  digitalWrite(25,LOW);//4
  digitalWrite(26,LOW);//5
  digitalWrite(27,LOW);//6
  digitalWrite(28,LOW);//7  
}
void iki_kapali()
{
  digitalWrite(29,LOW);//1
  digitalWrite(30,LOW);//2
  digitalWrite(31,LOW);//3
  digitalWrite(32,LOW);//4
  digitalWrite(33,LOW);//5
  digitalWrite(34,LOW);//6
  digitalWrite(35,LOW);//7  
}


void skorAyarla()
{
  
  if(skor < 10)
  {
    bir_kapali();
    iki_kapali();
    if(skor % 10 == 0)
    {
      uc_sifir();
    }
    else if(skor % 10 == 1)
    {
      uc_bir();
    }
    else if(skor % 10 == 2)
    {
      uc_iki();
    }
    else if(skor % 10 == 3)
    {
      uc_uc();
    }
    else if(skor % 10 == 4)
    {
      uc_dort();
    }
    else if(skor % 10 == 5)
    {
      uc_bes();
    }
    else if(skor % 10 == 6)
    {
      uc_alti();
    }
    else if(skor % 10 == 7)
    {
      uc_yedi();
    }
    else if(skor % 10 == 8)
    {
      uc_sekiz();
    }
    else if(skor % 10 == 9)
    {
      uc_dokuz();
    }        
  }
  
  else if(skor >= 10 && skor < 100)
  {
    bir_kapali();
    tmp = skor;
    tmp = tmp / 10;
    if(tmp == 1)
    {
      iki_bir();
    }
    else if(tmp == 2)
    {
      iki_iki();
    }
    else if(tmp == 3)
    {
      iki_uc();
    }
    else if(tmp == 4)
    {
      iki_dort();
    }
    else if(tmp == 5)
    {
      iki_bes();
    }
    else if(tmp == 6)
    {
      iki_alti();
    }
    else if(tmp == 7)
    {
      iki_yedi();
    }
    else if(tmp == 8)
    {
      iki_sekiz();
    }
    else if(tmp == 9)
    {
      iki_dokuz();
    }

    if(skor % 10 == 0)
    {
      uc_sifir();
    }
    else if(skor % 10 == 1)
    {
      uc_bir();
    }
    else if(skor % 10 == 2)
    {
      uc_iki();
    }
    else if(skor % 10 == 3)
    {
      uc_uc();
    }
    else if(skor % 10 == 4)
    {
      uc_dort();
    }
    else if(skor % 10 == 5)
    {
      uc_bes();
    }
    else if(skor % 10 == 6)
    {
      uc_alti();
    }
    else if(skor % 10 == 7)
    {
      uc_yedi();
    }
    else if(skor % 10 == 8)
    {
      uc_sekiz();
    }
    else if(skor % 10 == 9)
    {
      uc_dokuz();
    }
    
      
  }

  else if(skor >= 100 && skor < 1000)
  {
    tmp = skor;
    tmp = tmp / 100;

    orta = skor;
    orta = orta / 10;
        
    if(tmp == 1)
    {
      bir_bir();
    }
    else if(tmp == 2)
    {
      bir_iki();
    }
    else if(tmp == 3)
    {
      bir_uc();
    }
    else if(tmp == 4)
    {
      bir_dort();
    }
    else if(tmp == 5)
    {
      bir_bes();
    }
    else if(tmp == 6)
    {
      bir_alti();
    }
    else if(tmp == 7)
    {
      bir_yedi();
    }
    else if(tmp == 8)
    {
      bir_sekiz();
    }
    else if(tmp == 9)
    {
      bir_dokuz();
    }

    if(orta % 10 == 0)
    {
      iki_sifir();
    }
    else if(orta % 10 == 1)
    {
      iki_bir();
    }
    else if(orta % 10 == 2)
    {
      iki_iki();
    }
    else if(orta % 10 == 3)
    {
      iki_uc();
    }
    else if(orta % 10 == 4)
    {
      iki_dort();
    }
    else if(orta % 10 == 5)
    {
      iki_bes();
    }
    else if(orta % 10 == 6)
    {
      iki_alti();
    }
    else if(orta % 10 == 7)
    {
      iki_yedi();
    }
    else if(orta % 10 == 8)
    {
      iki_sekiz();
    }
    else if(orta % 10 == 9)
    {
      iki_dokuz();
    }
    
    if(skor % 10 == 0)
    {
      uc_sifir();
    }
    else if(skor % 10 == 1)
    {
      uc_bir();
    }
    else if(skor % 10 == 2)
    {
      uc_iki();
    }
    else if(skor % 10 == 3)
    {
      uc_uc();
    }
    else if(skor % 10 == 4)
    {
      uc_dort();
    }
    else if(skor % 10 == 5)
    {
      uc_bes();
    }
    else if(skor % 10 == 6)
    {
      uc_alti();
    }
    else if(skor % 10 == 7)
    {
      uc_yedi();
    }
    else if(skor % 10 == 8)
    {
      uc_sekiz();
    }
    else if(skor % 10 == 9)
    {
      uc_dokuz();
    }
  }
}
