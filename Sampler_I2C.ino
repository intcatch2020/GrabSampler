#include <Wire.h>
#include <ArduinoJson.h>
/*Manually define these after we get the pumps */
#define pump0Addr 0
#define pump1Addr 1
#define pump2Addr 2
#define pump3Addr 3

/*
  Loop will read in the serial data, this will be a json string
  it will save the data into a global var
  loop will then parse this and do what it needs
*/


const size_t INPUT_BUFFER_SIZE = 512;
char input_buffer[INPUT_BUFFER_SIZE+1];
int input_index = 0;
const size_t OUTPUT_BUFFER_SIZE = 512;
char output_buffer[OUTPUT_BUFFER_SIZE+1];


int run_time = 10000; //in millis
bool active[4] = {true,true,true,true};
bool ran[4] = {false,false,false,false};
long start_time[4]; //if value is -1 it means pump is not in use from being disabled
//this will occur on start/reset/after running

void setup()
{
  Serial.begin(9600);
  Wire.begin();
}

void loop()
{
  if (Serial.available() > 0)
    {
      char c = Serial.read();
      if (c != '\n' && c != '\r' && c!= '+'){
        input_buffer[input_index] = c;
	input_index++;
      }
      //Serial.print(c);
      if (input_index >= INPUT_BUFFER_SIZE || c == '\n' || c == '\r' || c == '+')
        {
	  Serial.print("-> ");
	  Serial.print(input_buffer);
	  Serial.print("\n");
          input_buffer[input_index] = '\0';
          input_index = 0;
          handleCommand(input_buffer);
        }
    }
  // Index to last character in debug buffer.
  //  static size_t input_buffer_idx = 0;

  // Wait until characters are received.
  //note this is blocking the timer code
  /* while (!Serial.available()) yield(); */

  /* // Put the new character into the buffer, ignore \n and \r */

  // If it is the end of a line, or we are out of space, parse the buffer.
  //remove the + this is just to test with the arduino serial monitor since it
  //cant handle escape sequences

  /*For all pumps
    if the active is false and start time != -1 meaning its current running
    if current time is greather than the start time + run time disable it
  */

  for (int i = 0; i < 4; i++)
    {
      if (active[i] == false && start_time[i] != -1 && ran[i] == true)
        {
          if (millis() >= (start_time[i] + run_time))
            {
              disable(i);
              snprintf(output_buffer,sizeof(output_buffer),
                       "{"
                       "\"GS\":\"%d\""
                       "}",i);
              send(output_buffer);
	      ran[i] = false; //dont notify again
	    }
        }
    }
}

/*

  {"e":0-4} //enables 0-4 (turn on)
  {"d":0-4} //disables 0-4 (turn off)
  {"s":} //stops all of them
  {"t":time} //sets runtime in millis
  {"r":} //resets all of them and puts them back in an active state
*/

int handleCommand(char *buffer)
{
  char param;
  char value[512]; //this has to be null terminated!!
  sscanf(buffer, "{\"%c\":%c}", &param, &value);
  /* Serial.print("->"); */
  /* Serial.print(buffer); */
  /* Serial.print("param is: "); */
  /* Serial.print(param); */
  /* Serial.print("\n"); */
  /* Serial.print("value is: "); */
  /* Serial.print(value); */
  /* Serial.print("\n"); */

  if (param == 'e')
    {
      Serial.print("enabling pump ");
      Serial.print(atoi(value));
      Serial.print("\n");

      if (atoi(value) == 0)
        {
          enable(0);
        }
      if (atoi(value) == 1)
        {
          enable(1);
        }
      if (atoi(value) == 2)
        {
          enable(2);
        }
      if (atoi(value) == 3)
        {
          enable(3);
        }
    }
  if (param == 'd')
    {
      Serial.print("disabling pump ");
      Serial.print(atoi(value));
      Serial.print("\n");

      if (atoi(value) == 0)
        {
          disable(0);
        }
      if (atoi(value) == 1)
        {
          disable(1);
        }
      if (atoi(value) == 2)
        {
          disable(2);
        }
      if (atoi(value) == 3)
        {
          disable(3);
        }
    }
  if (param == 's')
    {
      Serial.print("stopping all pumps\n");
      stop();
    }
  if (param == 't') //set pump runtime
    {
      Serial.print("setting new time to ");
      Serial.print(atoi(value));
      run_time = atoi(value); //in milis!!
    }
  if (param == 'r')
    {
      Serial.print("resetting all pumps \n");
      for (int i = 0; i < 4; i++)
        {
          active[i] = true;
          start_time[i] = -1;
        }
    }
}
void stop()
{
  disable(0);
  disable(1);
  disable(2);
  disable(3);
  //disable all 4
}
void enable(int pump)
{
  if (pump == 0)
    {
      if (active[0] == true)
        {
          Wire.beginTransmission(pump0Addr);
          Wire.write("C,0\r");
          Wire.endTransmission();
          active[0] = false;
          start_time[0] = millis();
	  ran[0] = true;
        }
      else
	{
	  Serial.print("pump needs to be reset\n");
	}
    }
  else if (pump == 1)
    {
      if (active[1] == true)
        {
          Wire.beginTransmission(pump1Addr);
          Wire.write("C,0\r");
          Wire.endTransmission();
          active[1] = false;
          start_time[1] = millis();
	  ran[1] = true;
        }
      else
	{
	  Serial.print("pump needs to be reset\n");
	}
      
    }
  else if (pump == 2)
    {
      if (active[2] == true)
        {
          Wire.beginTransmission(pump2Addr);
          Wire.write("C,0\r");
          Wire.endTransmission();
          active[2] = false;
          start_time[2] = millis();
	  ran[2] = true;
        }
      else
	{
	  Serial.print("pump needs to be reset\n");
	}
      
    }
  else if (pump == 3)
    {
      if (active[3] == true)
        {
          Wire.beginTransmission(pump3Addr);
          Wire.write("C,0\r");
          Wire.endTransmission();
          active[3] = false;
          start_time[3] = millis();
	  ran[3] = true;
        }
      else
	{
	  Serial.print("pump needs to be reset\n");
	}
      
    }
  delay(300);
}
void disable(int pump)
{
  if (pump == 0)
    {
      Wire.beginTransmission(pump0Addr);
      Wire.write("P\r");
      Wire.endTransmission();
    }
  else if (pump == 1)
    {
      Wire.beginTransmission(pump1Addr);
      Wire.write("P\r");
      Wire.endTransmission();
    }
  else if (pump == 2)
    {
      Wire.beginTransmission(pump2Addr);
      Wire.write("P\r");
      Wire.endTransmission();
    }
  else if (pump == 3)
    {
      Wire.beginTransmission(pump3Addr);
      Wire.write("P\r");
      Wire.endTransmission();
    }
  delay(300);
}
void send(char *str)
{
  size_t len = strlen(str);
  str[len++] = '\n';
  str[len] = '\0';
  Serial.print(str);
  //Serial.print("-> ");
  //Serial.print(str);
}
