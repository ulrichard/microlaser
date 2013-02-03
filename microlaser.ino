// This program is free software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.

// This program is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
// PARTICULAR PURPOSE.  See the GNU General Public License for more details.

// This program is a minimalist laser show 
// Created by Richard Ulrich <richi@paraeasy.ch>
// Inspired by : 
// http://www.instructables.com/id/Micro-LASER-Show-with-a-CD-Lens-Mechanism/#intro
// http://spt06.chez-alice.fr/00/scan1.htm
// http://luckylarry.co.uk/arduino-projects/control-a-dc-motor-with-arduino-and-l293d-chip/
// http://letsmakerobots.com/node/2074
// http://www.atmel.com/devices/atmega8.aspx

const uint8_t laserPin     =  8;
const uint8_t enablePin    =  7;   // pin 1 on L293D
const uint8_t motorXPinPos = 10;   // pin 2 on L293D
const uint8_t motorXPinNeg = 11;   // pin 7 on L293D
const uint8_t motorYPinPos =  6;   // pin 10 on L293D
const uint8_t motorYPinNeg =  9;   // pin 15 on L293D
const uint8_t steps = 50;
const uint8_t pause = 0;
const float scaleX = 0.35;
const float scaleY = 0.5;

const float offsetX = 0;
const float offsetY = 0.5; // to compensate the missing 4th PWM of the AtMega8
const float scaleXPos = scaleX;
const float scaleXNeg = scaleX;
const float scaleYPos = scaleY;
const float scaleYNeg = 0; // scaleY; -> as the atmega 8 has only 3 PWM channels, this one doesn't work anyway

void setup()
{
    // set all the other pins you're using as outputs:
    pinMode(laserPin,     OUTPUT);
    pinMode(enablePin,    OUTPUT);
    pinMode(motorXPinPos, OUTPUT);
    pinMode(motorXPinNeg, OUTPUT);
    pinMode(motorYPinPos, OUTPUT);
    pinMode(motorYPinNeg, OUTPUT);

    digitalWrite(enablePin, HIGH);
    digitalWrite(laserPin,  HIGH);
}

float angle = 0;

void loop()
{    
    const float x = sin(angle) + offsetX;
    const float y = cos(angle) + offsetY;

//	if(angle < 45.0 || angle > 370)
//		y = 0.75 - (y - 0.75);
    
    if(x >= 0)
    {
        digitalWrite(motorXPinPos, LOW);
        analogWrite(motorXPinNeg, x * scaleXPos * 255);
    }
    else
    {
        analogWrite(motorXPinPos, -x * scaleXNeg * 255);
        digitalWrite(motorXPinNeg, LOW);
    }
    if(y >= 0)
    {
        digitalWrite(motorYPinPos, LOW);
        analogWrite(motorYPinNeg, y * scaleYPos * 255);
    }
    else
    {
        analogWrite(motorYPinPos, -y * scaleYNeg * 255);
        digitalWrite(motorYPinNeg, LOW);
    }
  
    angle += 2 * PI / steps;
    if(angle > 2 * PI)
        angle = 0.0;
    delay(pause);
}
