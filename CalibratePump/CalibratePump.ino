//At this point the pump should be in i2c mode
#include <Wire.h>

char buf[100];
//change this to the pumps address
int address = 1;
void setup()
{
  Serial.begin(9600); //debug serial
  while(!Serial);
  Wire.begin();


  Wire.beginTransmission(address);
  //change 10 to the amount of water you want to calibrate with
  Wire.write("D,10\r");
  Wire.endTransmission();
}

void loop()
{
  if (Serial.available() > 0)
    {
      //Now you have to send it how much water actually pumped, send this though the serial monitor followed by a \r
      int index = 0;
      char c = Serial.read();
      if (c != '\r')
        {
          buf[index] = c;
          index++;
        }
      else
        {
          buf[index] == '\0';
          Serial.print("You measured: ");
          Serial.print(buf);
          Serial.print("ml \n");
          int ml = atoi(buf);
          Wire.beginTransmission(address);
          Wire.write("Cal,");
          Wire.write(ml);
          Wire.write("\r");
          Wire.endTransmission();
        }
    }
}