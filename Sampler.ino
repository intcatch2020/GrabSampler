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
      if (atoi(value) == 0)
        {
          enable(0);
        }
      if (atoid(value) == 1)
        {
          enable(1);
        }
      if (atoid(value) == 2)
        {
          enable(2);
        }
      if (atoid(value) == 3)
        {
          enable(3);
        }
    }

  if (param == 'd')
    {
      if (atoid(value) == 0)
        {
          disable(0);
        }
      if (atoid(value) == 1)
        {
          disable(1);
        }
      if (atoid(value) == 2)
        {
          disable(2);
        }
      if (atoid(value) == 3)
        {
          disable(3);
        }
    }
  if (param == 's') 
    {
      disable(0);
      disable(1);
      disable(2);
      disable(3);
    } 
  if (param == 't') //set pump runtime
    {
      run_time = atoi(value); //in milis!!
    }
}
void setup()
{
}
void loop()
{
}
void enable(int pump)
{

}
void disable(int pump)
{

}