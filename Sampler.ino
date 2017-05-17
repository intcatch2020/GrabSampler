#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <string.h>

const size_t INPUT_BUFFER_SIZE = 512;
char input_buffer[INPUT_BUFFER_SIZE];

const size_t OUTPUT_BUFFER_SIZE = 512;
char output_buffer[INPUT_BUFFER_SIZE];

bool run_time_exceeded[4];
bool active[4];
long start_time[4];
long prev_run_time[4];

bool first_command_recvd = false;

long run_time = 10000; //ms

/*Pumps need an rx and tx pin each
we dont actually need the recieve data
actually do we need to check if its finished sending a string before sending it one???
*/
const int pump0RX = -1;
const int pump0TX = 36;

const int pump1RX = -1;
const int pump1TX = 37;

const int pump2RX = -1;
const int pump2TX = 38;

const int pump3RX = -1;
const int pump3TX = 39;

//initialize serial ports for pumps
SoftwareSerial pump0(pump0RX,pump0TX);
SoftwareSerial pump1(pump1RX,pump1TX);
SoftwareSerial pump2(pump2RX,pump2TX);
SoftwareSerial pump3(pump3RX,pump3TX);

//^ combine these
SoftwareSerial pumps[4] = {pump0,pump1,pump2,pump3}; 

/*
  possible json commands to handle

  {'e':'0-4'} //enables 0-4 (turn on)
  {'d':'0-4'} //disables 0-4 (turn off)
  {'s':''} //stops all of them
  {'t':'time'} //sets runtime in millis
*/
int handleCommand(char *buffer)
{
  char param;
  char value[512]; //this has to be null terminated!!
  sscanf(buffer,{"\"%c\":\"%s\""});

  if (param == 'e')
    {
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
      stop();
    }
  if (param == 't') //set pump runtime
    {
      run_time = atoi(value); //in milis!!
    }
}
void setup()
{
  delay(1000);
  Serial.begin(9600);
  pump0.begin(9600);
  pump1.begin(9600);
  pump2.begin(9600);
  pump3.begin(9600);

  input_buffer[INPUT_BUFFER_SIZE] = '\0';
  output_buffer[OUTPUT_BUFFER_SIZE] = '\0';


}
void loop()
{
}
void enable(int pump)
{
  //send it c,0
  //will continuously run pump
  //disables reporting (we dont care about this)
  pumps[i].print("C,0");
}
void disable(int pump)
{
  //P pauses 
  pumps[i].print("P");
}
void stop()
{
  for (int i = 0; i < 4; i++)
    {
      disable(i);
    }
}