#include <SPI.h>

#include <iostream>
#include <sstream>
#include <chrono>

#include "Control.hpp"


void ArduinoDebug(std::ostringstream& oss)
{
  //Serial.println(oss.str().c_str());
}



void BottleFinish(Bottle& bottle) {


  uint8_t r = random(256);
  uint8_t g = random(256);
  uint8_t b = random(256);
  size_t time = random(5000, 20000);

  iPixel clr(r, g, b);
  bottle.SetColor(clr, std::chrono::milliseconds{ time }, BottleFinish);

  std::ostringstream oss;

  oss << "Set Color: " << (uint32_t)r <<"/"<< (uint32_t)g<<"/"<< (uint32_t)b << " with timeout: " << time;

Serial.println(oss.str().c_str());
}

std::chrono::milliseconds GetMsTime(void){

  return std::chrono::milliseconds(millis());
  
}

static const int spiClk = 100000; // 100 kHz

//static const size_t NUMBER_OF_LEDS =  87+82+2+5*14;//251;

//Number of LEDs:
//10
//87 (Unter der Bar)
//82 (Über der Bar)
//2
//5*14 (5 Flaschen, 7 vorne, 7 hinten);





//uninitalised pointers to SPI objects
SPIClass * vspi = NULL;
SPIClass * hspi = NULL;

Control ledControl;



class Button {
  public:
    Button(uint8_t PIN) : PIN(PIN)
    {
      buttonState = LOW;
      numberKeyPresses = 0;
      lastDebounceTime = 0;
      lastState = LOW;
      pinMode(PIN, INPUT_PULLUP);
    }
    bool Process(void){
      int reading = digitalRead(PIN);
      bool ret = false;

      //Serial.printf("Reading of PIN %d: %d\n", PIN, reading);

      if(reading != lastState){
        lastDebounceTime  = millis();
      }

      if ((millis() - lastDebounceTime) > buttonDebounceTime) {
        if (reading != buttonState) {
          buttonState = reading;
          if (buttonState == HIGH) {
            numberKeyPresses++;

            //Serial.printf("Button on PIN %d pressed", PIN, reading);
            
            ret = true;
          }
        }
      }
      lastState = reading;
      return ret;
    }

    bool Pressed(void)
    {
      return (buttonState == HIGH);
    }


    uint32_t numberKeyPresses;

  private:
    const size_t buttonDebounceTime = 50;
    const uint8_t PIN;
    int buttonState;
    int lastState;
    size_t lastDebounceTime;
};

Button button1 = {25};
Button button2 = {39};




void setup() {


randomSeed(analogRead(0));



    

  
  //initialise two instances of the SPIClass attached to VSPI and HSPI respectively
  vspi = new SPIClass(VSPI);
  //hspi = new SPIClass(HSPI);

Serial.begin(115200);
  //std::cout << "Sizeof i_led_t: " << sizeof(i_led_t);

  std::ostringstream oss;

  oss << "\nAnd size of Control: " << sizeof(Control);

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

  if(button1.Process()){
        Serial.printf("Button 1 has been pressed %u times\n", button1.numberKeyPresses);
        ledControl.PushButton();
    
  }
  
  if(button2.Process()){
        Serial.printf("Button 2 has been pressed %u times\n", button2.numberKeyPresses);
        ledControl.PushButton();
        
    
  }

    
    
  
  
  ledControl.Update();
  //setSingleColor();
  vspiCommand();
  delay(50);


  
  //digitalWrite(19, HIGH);
}

size_t moving = 0;
size_t fill = 0;







void vspiCommand() {
  
std::ostringstream debug;
  //use it as you would the regular arduino SPI API
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  //digitalWrite(5, LOW); //pull SS slow to prep other end for transfer
  

  auto ledBuffer = ledControl.GetLeds();

  debug << "Write Color: " << (size_t)ledBuffer.at(0).Red() << "|"<< (size_t)ledBuffer.at(0).Green() << "|"<< (size_t)ledBuffer.at(0).Blue();

debug << "\n" << (size_t)((uint8_t*)ledBuffer.data())[0] << " "<< (size_t)((uint8_t*)ledBuffer.data())[1] << " "<< (size_t)((uint8_t*)ledBuffer.data())[2] << " "<< (size_t)((uint8_t*)ledBuffer.data())[3] << " ";

   ArduinoDebug(debug);

  vspi->transfer32(0);
  vspi->writeBytes((uint8_t*)ledBuffer.data(), 4*ledBuffer.size());
  //vspi->transfer32(0xFFFFFFFF);
  //digitalWrite(5, HIGH); //pull ss high to signify end of data transfer
  vspi->endTransaction();
}

