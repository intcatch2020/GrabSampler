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

long max_run_time;

void send(char *str)
{
  size_t len = strlen(str);
  str[len++] = '\n'; //terminate
  str[len] = '\0';

  Serial1.print(str);
}

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
      if ((int)value == 48) //ascii 0
        {
        }
      if ((int)value == 49) //ascii 0
        {
        }
      if ((int)value == 50) //ascii 0
        {
        }
      if ((int)value == 51) //ascii 0
        {
        }
    }
}
void setup()
{
}
void loop()
{
}