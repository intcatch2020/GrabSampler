#include <Wire.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>


//SoftwareSerial SoftSerial(10, 11); //rx tx
SoftwareSerial SoftSerial(6, 7); //rx tx
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
//int vol = 1;

void setup()
{

  Serial.begin(9600); //transfer from eboard to samplerard
  SoftSerial.begin(9600); //debug serial

  // Wire1.setClock(400000);
  Wire.begin();

  // enable(1);
  // enable(2);
  // enable(3);
  // enable(4);

}

void loop()
{
	
  // handleCommand("{e:3}");
  // delay(5000);
  // return;
	
  if (SoftSerial.available())
  {
    //serial.read isnt working
    char c = SoftSerial.read();
    if (c != '\n' && c != '\r'){
      input_buffer[input_index++] = c;
    }
    //Serial.print(c);
    if (input_index >= INPUT_BUFFER_SIZE || c == '\n' || c == '\r')
    {
      input_buffer[input_index++] = '\0';

      Serial.print("-> ");
      Serial.print(input_buffer);
      Serial.print("\n");
      handleCommand(input_buffer);
      input_index = 0;
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
  int value;

	//{e:0}
  sscanf(buffer,
         "{"
         "%c:"
         "%d"
         "}",
         &param, &value);
	
  Serial.print("param is: ");
  Serial.println(param);
  Serial.print("value is: ");
  Serial.println(value);

  if (param == 'e')
  {
    // Serial.print(atoi(value));
    // Serial.print("\n");
    //int pump = atoi(value); //addresses start at 1 not 0
    //enable(value[0]-'0');
		enable(value);
  }
  if (param == 'd')
  {
    //Serial.print("disabling pump ");
    //Serial.print(atoi(value));
    //Serial.print(value);
    //Serial.print("\n");
    //disable(value[0]-'0');
		disable(value);
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
    //int pump = atoi(value);
    //int pump = value[0]-'0';
		

    //Serial.print("<-");
    if (active[value] == true)
    {
      char str[500];
      snprintf(str,500,"{\"e\":\"%d\"\r",value);
      SoftSerial.print(str); //Meaning you can use it
    }
    else
    {
      char str[500];
      snprintf(str,500,"{\"d\":\"%d\"\r",value);
      SoftSerial.print(str);//Meaning you cannot use it
    }
  }
  if (param == 'v')
  {
    Serial.print("volume is now: ");
    Serial.println(value);
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
  // Serial.print("pump is: ");
  // Serial.println(pump);
  // Serial.print("enabling pump :");
  // Serial.print(pumpAddr[pump]);
  // Serial.println();

  if (active[pump] == true)
  {
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
