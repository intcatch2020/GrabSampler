//The pumps are by default in UART mode
//Attach the pump to Serial1 (pins 18 and 19)
//White goes to tx on arduino
//Green goes to rx on arduino


void setup()
{
  Serial1.begin(9600); //debug serial
  while(!Serial);
  Serial1.begin(9600); //pump serial
  while(!Serial1);
  //change that 1 to what you want to make the address
  Serial1.write("I2C,1\r")
}


//If response from pump is "*OK\r" it worked!
//If response from pump i "*ER\r" it didnt :(
void loop()
{
  if (Serial1.available() > 0)
    {
      char c = Serial1.read();
      if (c == '\r')
	{
	  Serial.println();
	}
      else
	{
	  Serial.print(c);
	}
    }
}