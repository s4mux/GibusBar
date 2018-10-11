#include <SPI.h>

#include <iostream>
#include <sstream>

static const int spiClk = 100000; // 100 kHz

static const size_t NUMBER_OF_LEDS =  87+82+2+5*14;//251;

//Number of LEDs:
//10
//87 (Unter der Bar)
//82 (Über der Bar)
//2
//5*14 (5 Flaschen, 7 vorne, 7 hinten);


struct iLed{

  uint8_t start:3;
  uint8_t global:5;
  uint8_t blue;
  uint8_t green;
  uint8_t red;

  void off(void)
  {
    blue = 0;
    green = 0;
    red = 0;
    
  }
  
  void setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t global=0x1F)
  {
    
    this->blue = blue;
    this->green = green;
    this->red = red;
    this->global = global;
    start = 7;
  }

  iLed& operator=(iLed& t){
    global = t.global;
    blue = t.blue;
    green = t.green;
    red = t.red;
    start = 7;
  }
  
  
};


iLed ledBuffer[NUMBER_OF_LEDS];

//uninitalised pointers to SPI objects
SPIClass * vspi = NULL;
SPIClass * hspi = NULL;



size_t color;
size_t oldColor;
iLed colors[10];

void setup() {


  colors[0].setColor(0,0,0);
  colors[1].setColor(200,0,0);
  colors[2].setColor(0,200,0);
  colors[3].setColor(0,0,200);
  colors[4].setColor(35,250,170);
  colors[5].setColor(0,100,200);
  colors[6].setColor(0,200,100);
  colors[7].setColor(100,0,100);
  colors[8].setColor(0,255,100);
  colors[9].setColor(200,200,200);

  oldColor = 0;
  color = 1;


  
  //initialise two instances of the SPIClass attached to VSPI and HSPI respectively
  vspi = new SPIClass(VSPI);
  //hspi = new SPIClass(HSPI);

Serial.begin(115200);
  //std::cout << "Sizeof i_led_t: " << sizeof(i_led_t);

  std::ostringstream oss;
  oss << "Size of iLed: " << sizeof(iLed);

Serial.println(oss.str().c_str());
  
  //clock miso mosi ss

  //initialise vspi with default pins
  //SCLK = 18, MISO = 19, MOSI = 23, SS = 5
  vspi->begin(18, 23, 19, 5);
  //alternatively route through GPIO pins of your choice
  //hspi->begin(0, 2, 4, 33); //SCLK, MISO, MOSI, SS
  
  //initialise hspi with default pins
  //SCLK = 14, MISO = 12, MOSI = 13, SS = 15
  //hspi->begin(); 
  //alternatively route through GPIO pins
  //hspi->begin(25, 26, 27, 32); //SCLK, MISO, MOSI, SS

  //set up slave select pins as outputs as the Arduino API
  //doesn't handle automatically pulling SS low
  //pinMode(19, OUTPUT);

/*
  for(size_t i=0; i<NUMBER_OF_LEDS; i++){
    ledBuffer[i].start = 7;
    ledBuffer[i].global = 0x1F;
    ledBuffer[i].red = 100;
    ledBuffer[i].green = 100;
    ledBuffer[i].blue = 0xFF;

    std::ostringstream test;
    test << (int)((uint8_t*)&ledBuffer[i])[0] << ", ";
    test << (int)((uint8_t*)&ledBuffer[i])[1] << ", ";
    test << (int)((uint8_t*)&ledBuffer[i])[2] << ", ";
    test <<(int) ((uint8_t*)&ledBuffer[i])[3] << ", ";

    Serial.println(test.str().c_str());
  }

*/

}

// the loop function runs over and over again until power down or reset
void loop() {
  
  update();
  //setSingleColor();
  vspiCommand();
  //delay(1000);


  
  //digitalWrite(19, HIGH);
}

size_t moving = 0;
size_t fill = 0;


void setSingleColor(void)
{
  iLed color;

  for(size_t i=0; i<NUMBER_OF_LEDS; i++){
    ledBuffer[i].setColor(244, 65, 166);
  }

  
}

void update(void)
{
  for(size_t i=0; i<NUMBER_OF_LEDS; i++){
    ledBuffer[i] = colors[oldColor];
  }

  ledBuffer[moving] = colors[color];
  //ledBuffer[moving+1] = colors[color];
  //ledBuffer[moving+2] = colors[color];
  //ledBuffer[moving+3] = colors[color];
  //ledBuffer[moving+4] = colors[color];
  //ledBuffer[moving+5] = colors[color];
  //ledBuffer[moving+6] = colors[color];

  moving++;

  for(size_t i=NUMBER_OF_LEDS-fill; i<NUMBER_OF_LEDS; i++){
    ledBuffer[i] = colors[color];
  }
  

  if(moving + fill >= NUMBER_OF_LEDS){
    moving = 0;
    fill++;

    if(fill >= NUMBER_OF_LEDS){
      fill = 0;
      oldColor = color;
      color++;
      if(color >= 10){
        color = 0;
      }
      
    }
    
  }
  
}


void vspiCommand() {
  

  //use it as you would the regular arduino SPI API
  vspi->beginTransaction(SPISettings(spiClk, LSBFIRST, SPI_MODE0));
  //digitalWrite(5, LOW); //pull SS slow to prep other end for transfer
  vspi->transfer32(0);
  
  vspi->writeBytes((uint8_t*)ledBuffer, 4*NUMBER_OF_LEDS);
  //vspi->transfer32(0xFFFFFFFF);
  //digitalWrite(5, HIGH); //pull ss high to signify end of data transfer
  vspi->endTransaction();
}

