#include "iPixel.hpp"



#include <sstream>
void ArduinoDebug(std::ostringstream& oss);

iPixel::iPixel(void) :
	start(7)
{
	this->red = 0;
	this->green = 0;
	this->blue = 0;
	this->global = 0x1F;
}

iPixel::iPixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t global) :
	start(7)
{
this->red = red;
this->green = green;
this->blue = blue;
this->global = global;
}


uint8_t iPixel::Red(void)
{
	return red;
}

uint8_t iPixel::Blue(void)
{
	return blue;
}

uint8_t iPixel::Green(void)
{
	return green;
}

void iPixel::setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t global)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->global = global;
}
iPixel& iPixel::operator=(iPixel& t)
{
	this->red = t.red;
	this->green = t.green;
	this->blue = t.blue;
	this->global = t.global;
	return *this;
}

bool iPixel::operator==(const iPixel& b) const
{
	if (red != b.red) return false;
	if (green != b.green) return false;
	if (blue != b.blue) return false;
	if (global != b.global) return false;
	return true;
}


iPixel iPixel::Interpolate(iPixel& A, iPixel& B, float f)
{
  std::ostringstream debug;
	if (f > 1.0) {
		f = 1.0;
	}
	if (f < -1.0) {
		f = -1.0;
	}

	iPixel newColor;

	newColor.red = (size_t)((float)A.red+((float)B.red - (float)A.red) * f)%256;
	newColor.green = (size_t)((float)A.green + ((float)B.green - (float)A.green) * f)%256;
	newColor.blue = (size_t)((float)A.blue + ((float)B.blue - (float)A.blue) * f)%256;
	newColor.global = (size_t)((float)A.global + ((float)B.global - (float)A.global) * f)%256;

  debug << "f: " << f << ". Color: " << (size_t)newColor.red << "|"<< (size_t)newColor.green << "|"<< (size_t)newColor.blue << "|"<< (size_t)newColor.global;


   ArduinoDebug(debug);

	return newColor;
}
