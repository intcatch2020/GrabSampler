This is the ardunio firmware for the grab sampler designed to work with the Platypus eBoard.

Notes
- It should be used as a json passthrough
- It should be powered via the sensor port


Setting Up Arduino:
1) On the sensor cable use the white (RX+) and brown (TX+) to transfer serial commands from the eboard to the sampler.
2) Connect the ground (grey on sensor cable) to the ground on the arduino.
3) If you're using a due RX and TX should go into Serial1 (Brown -> pin 19, White -> pin 18)
4) On the sensor cable the red wire should go into either vin or 5v on the samplers arduino. (Dont know if its safe to power it over usb and 5v so probably dont?)
5) The [find out which color wire] is the power cable that comes through the sensor port from the battery. It says 12v on the sensor cable diagram but will be the voltage of the batter (16v~). Power the pumps using this line. The pumps operate on 12-24v.

Setting Up Pumps: (Note this still needs to be tested and stuff)
https://www.atlas-scientific.com/_files/code/pmp-i2c.pdf

1) You have to first put the pumps in I2C mode instead of UART mode. You will also need to specify the I2C address (1-127). To do this over serial you will have to send it the ascii string "I2C,addr" where addr is a number from 1-127. The LED on motor controller on the pump should then be blue, if not it probably failed so try again or something.
2) There are 4 wires you will have to connect from the pump to the samplers arduino. Red should go to 5v, Black to ground, Green to SDA, White to SCL. (Note it might be a good idea to use a small breadboard for this then just layer some kind of epoxy over it after everything works.


Calibrating The pumps:
These pumps give you alot of control and can do volumetric
Page 10 of https://www.atlas-scientific.com/_files/_datasheets/_peristaltic/EZO_PMP_Datasheet.pdf explains how to calibrate the pumps.
1) Send pump "D,10" it will attempt to pump 10 ml of liquid
2) Measure how much liquid was actually pumped
3) Send pump "Cal, v" where v the amount that was actually pumped.

After this the pump should be calibrated. This is useful because the code (while it doesnt yet) will pump the exact volume of water that the specific container has (no overflow).

Small Ardunio Programs will also be written to help with setting the addresses of the pumps as well as calibrating them easily!. 

