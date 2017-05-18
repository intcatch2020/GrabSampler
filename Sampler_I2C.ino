#include <Wire.h>
#include <ArduinoJson.h>
/*Manually define these after we get the pumps */

//need to change this
int pumpAddr[4] = {1,2,3,4};

const size_t INPUT_BUFFER_SIZE = 512;
char input_buffer[INPUT_BUFFER_SIZE+1];
int input_index = 0;
const size_t OUTPUT_BUFFER_SIZE = 512;
char output_buffer[OUTPUT_BUFFER_SIZE+1];


int run_time = 10000; //in millis
bool active[4] = {true,true,true,true};
bool ran[4] = {false,false,false,false};
long start_time[4]; //if value is -1 it means pump is not in use from being onstart/reset


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
  {"c":0-4} //get status of pump (either enabled or disabled)
*/

int handleCommand(char *buffer)
{
  char param;
  char value[512]; //this has to be null terminated!!
  sscanf(buffer, "{\"%c\":%c}", &param, &value);

  if (param == 'e')
    {
      Serial.print("enabling pump ");
      Serial.print(atoi(value));
      Serial.print("\n");
      int pump = atoi(value);
      enable(pump);
    }
  if (param == 'd')
    {
      Serial.print("disabling pump ");
      Serial.print(atoi(value));
      Serial.print("\n");
      int pump = atoi(value);
      disable(pump);
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
  if (param == 'c')
    {
      int pump = atoi(value);
      Serial.print("<-");
      if (active[pump] == true)
	{
	  Serial.print("E\n"); //Meaning you can use it
	}
      else
	{
	  Serial.print("D\n"); //Meaning you cannot use it
	}
    }
}
void stop()
{
  for (int i = 0; i < 4; i++)
    {
      disable(i);
    }
}
void enable(int pump)
{
  if (active[pump] == true)
    {
      Wire.beginTransmission(pumpAddr[pump]);
      Wire.write("C,0\r");
      Wire.endTransmission();
      active[pump] = false;
      start_time[pump] = millis();
      ran[pump] = true;
    }
  else
    {
      Serial.println("Pump needs to be reset\n");
    }
  delay(300);
}
void disable(int pump)
{
  Wire.beginTransmission(pumpAddr[pump]);
  Wire.write("P\r");
  Wire.endTransmission();
  delay(300);
  active[pump] = false;
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
