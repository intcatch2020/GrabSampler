#include <Wire.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
/*Manually define these after we get the pumps */

SoftwareSerial SoftSerial(10, 11); //rx tx
//need to change this
int numPumps = 4;
int pumpAddr[] = {1,2,3,4};
bool active[] = {true,true,true,true}; //can pump be used

const size_t INPUT_BUFFER_SIZE = 512;
char input_buffer[INPUT_BUFFER_SIZE+1];
int input_index = 0;
const size_t OUTPUT_BUFFER_SIZE = 512;
char output_buffer[OUTPUT_BUFFER_SIZE+1];

int vol = 400;

void setup()
{

  Serial.begin(9600); //transfer from eboard to samplerard
  SoftSerial.begin(9600); //debug serial

  // Wire1.setClock(400000);
  Wire.begin();
}

void loop()
{
  if (SoftSerial.available() > 0)
    {
      //serial.read isnt working
      char c = SoftSerial.read();
      if (c != '\n' && c != '\r'){
        input_buffer[input_index] = c;
        input_index++;
      }
      //Serial.print(c);
      if (input_index >= INPUT_BUFFER_SIZE || c == '\n' || c == '\r')
        {
          Serial.print("-> ");
          Serial.print(input_buffer);
          Serial.print("\n");
          input_buffer[input_index] = '\0';
          input_index = 0;
          handleCommand(input_buffer);
        }
    }
  else
    {
      //  Serial.print("no serial avail\n");
    }
}

/*

  {"e":0-4} //enables 0-4 (turn on)
  {"d":0-4} //disables 0-4 (turn off)
  {"s":} //stops all of them
  {"r":} //resets all of them and puts them back in an active state
  {"c":0-4} //get status of pump (either enabled or disabled)
  {"v":ml} //sets how many ml of water to pump
*/

int handleCommand(char *buffer)
{
  char param;
  char value[512]; //this has to be null terminated!!
  //value[0] = '\0';
  sscanf(buffer, "{\"%c\":%s}", &param, &value);
  //Serial.print("value is: ");
  // Serial.println(value);
  if (param == 'e')
    {
      /*
        Serial.print("enabling pump ");
        Serial.print(atoi(value));
        Serial.print("\n");
      */
      int pump = atoi(value); //addresses start at 1 not 0
      enable(pump);
    }
  if (param == 'd')
    {
      Serial.print("disabling pump ");
      //Serial.print(atoi(value));
      Serial.print(value);
      Serial.print("\n");
      int pump = atoi(value);
      disable(pump);
    }
  if (param == 's')
    {
      // Serial.print("stopping all pumps\n");
      stop();
    }
  if (param == 'r')
    {
      Serial.print("resetting all pumps \n");
      for (int i = 0; i < 4; i++)
        {
          active[i] = true;
        }
    }
  if (param == 'c')
    {
      int pump = atoi(value);

      //Serial.print("<-");
      if (active[pump] == true)
        {
	  char str[500];
	  snprintf(str,500,"{\"e\":\"%d\"\r",pump);
          SoftSerial.print(str); //Meaning you can use it
        }
      else
        {
	  char str[500];
	  snprintf(str,500,"{\"d\":\"%d\"\r",pump);
          SoftSerial.print(str);//Meaning you cannot use it
        }
    }
  if (param == 'v')
    {
      vol = atoi(value);
      Serial.print("volume is now: ");
      Serial.println(vol);
    }
}
/*
  Replace the cont flow with volumetric flow eventually
  Wire.write("D,");
  Wire.Write(vol);
  Wire.write("\r");
*/
void enable(int pump)
{
  if (active[pump] == true)
    {
      Serial.print("enabling pump :");
      Serial.print(pumpAddr[pump]);
      Serial.println();
      char str[500];
      Wire.beginTransmission(pumpAddr[pump]);
      snprintf(str,500,"D,%d\r",vol);
      //  Serial.print(str);
      Wire.write(str);
      Wire.endTransmission();
      active[pump] = false;
      delay(300);
    }
}
void disable(int pump)
{
  Wire.beginTransmission(pumpAddr[pump]);
  Wire.write("P\r");
  Wire.endTransmission();
  delay(300);
  active[pump] = false;
}
void stop()
{
  for (int i = 1; i < 5; i++)
    {
      disable(i);
    }
}

void send(char *str)
{
  size_t len = strlen(str);
  str[len] = '\0';
  SoftSerial.print(str);
  /* Serial.print("-> "); */
  /* Serial.print(str); */
}
