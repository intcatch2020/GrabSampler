#include <ArduinoJson.h>

const int NUM_PUMPS = 4;
const int PUMP_ADDR[] = {1,2,3,4};
double cur_vol[NUM_PUMPS];
bool active[] = {true,true,true,true}; //can pump be used
bool finished[] = {false,false,false,false};

const size_t INPUT_BUFFER_SIZE = 512;
char input_buffer[INPUT_BUFFER_SIZE+1];
int input_index = 0;
const size_t OUTPUT_BUFFER_SIZE = 512;
char output_buffer[OUTPUT_BUFFER_SIZE+1];

int vol = 400;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop()
{
	if (Serial1.available())
  {
    char c = Serial1.read();
    if (c != '\n' && c != '\r'){
      input_buffer[input_index] = c;
      input_index++;
    }
    //Serial.print("char = "); Serial.println(c);
    if (input_index > INPUT_BUFFER_SIZE)
    {
      Serial.println("filled buffer, return to index 0");
      input_index = 0;
      return;
    }
    if (c == '\n' || c == '\r')
    {
      input_buffer[input_index++] = '\0';
      Serial.print("-> ");
      Serial.println(input_buffer);        
      //handleCommand(input_buffer);
      input_index = 0;
    }
  }
 else
 {
   //Serial.println("no serial avail");
 }

	/*Unfortunetly there is some error that arises with one of the pumps
	  That returns a ? symbol for the volume amount from pump 1 so for now
		we wont use this.*/
// if (currentTime - millis() >= 500)
//   {
//     feedbackLoop();
//   }
// currentTime = millis();

}

/*

  {e:0-4} //enables 0-4 (turn on)
  {d:0-4} //disables 0-4 (turn off)
  {s:} //stops all of them
  {r:} //resets all of them and puts them back in an active state
  {c:0-4} //get status of pump (either enabled or disabled)
  {v:ml} //sets how many ml of water to pump
  {f:0} //return finished status of a pump
*/


void handleCommand(char *buffer)
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

  //not sure what is happening but some times empty commands with value 62 are getting through
  if (value == 69)
  {
    return;
  }

  Serial.print("param is: ");
  Serial.println(param);
  Serial.print("value is: ");
  Serial.println(value,DEC);
  if (param == 'e')
  {
    enable(value);
  }
  if (param == 'd')
  {
    disable(value);
  }
  if (param == 's')
  {
    stop();
  }
  if (param == 'r')
  {
    for (int i = 0; i < 4; i++)
    {
      active[i] = true;
      finished[i] = false;
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
      snprintf(str,500,"{e:%d\r",value);
      //SoftSerial.print(str); //Meaning you can use it
    }
    else
    {
      char str[500];
      snprintf(str,500,"{d:%d\r",value);
      //SoftSerial.print(str);//Meaning you cannot use it
    }
  }
  if (param == 'v')
  {
    vol = value;
    Serial.print("volume is now: ");
    Serial.println(value);
  }
  // if (param == 'f')
  //   {
  //     char str[500];
  //     snprintf(str,500,"{%d,%d}\r",value,finished[value]);
  //     Serial.println(str);
  //     send(str);
  //   }
}
/*
  Replace the cont flow with volumetric flow eventually
  Wire.write("D,");
  Wire.Write(vol);
  Wire.write("\r");
*/
void enable(int pump)
{
}
void disable(int pump)
{
}

void stop()
{
  for (int i=0; i<4; i++)
  {
    disable(i);
  }
}

void reset()
{  
  for (int i=0; i<4; i++)
  {
    reset(i);
  }  
}

void reset(int i)
{  
}

void send(char *str)
{
  size_t len = strlen(str);
  str[len] = '\0';
  //SoftSerial.print(str);
  Serial.print("-> ");
  Serial.println(str);
}

void feedbackLoop()
{
}
