This is the arduino firmware for the grab sampler designed to work with the Platypus EBoard.


Notes
- BUILD THE SENSOR CABLE BASED ON THE DESIGN IN THE BINDER. Ill post a picture of it here eventually.
- Used as a JsonPassThrough Sensor

Setting Up Arduino: (Only tested on leonardo)
1) On the sensor cable use the white (RX+) and brown (TX+) to transfer serial commands from the eboard to the sampler.
2) Connect the ground (grey on sensor cable) to the ground on the arduino.
3) If you're using a due RX and TX should go into the software serial ports RX->10, TX->11
4) On the sensor cable the red wire should go into either Vin
5) Ground the arduino with the grey wire from the sensor cable

Setting Up Pumps: (Note this still needs to be tested and stuff)
https://www.atlas-scientific.com/_files/code/pmp-i2c.pdf

1) You have to first put the pumps in I2C mode instead of UART mode. You will also need to specify the I2C address (1-127). To do this over serial you will have to send it the ascii string "I2C,addr" where addr is a number from 1-127. The LED on motor controller on the pump should then be blue, if not it probably failed so try again or something.
2) There are 4 wires you will have to connect from the pump to the samplers arduino. Red should go to 5v, Black to ground. All the green wires from your 4 samplers should connect to each other and go to to SDA1, White to SCL1. You will also need to connect pullup resistors between each SDA and SCL from 3.3v on the arduino. I used 1kohm resistors.
3) To power the pumps use the green wire to go into a proper voltage regulator. Tune the regulator to 12 volts (although its operating voltage is 12-24). Attach ground to the ground wire on the sensor cable.
4) Use a power crimp piece to crimp all red wires and black wires coming out of the regulator to the pumps


Calibrating The pumps: (Not always necessary the error is minimal)

These pumps give you alot of control and can do volumetric
Page 10 of https://www.atlas-scientific.com/_files/_datasheets/_peristaltic/EZO_PMP_Datasheet.pdf explains how to calibrate the pumps.
1) Send pump "D,10" it will attempt to pump 10 ml of liquid
2) Measure how much liquid was actually pumped
3) Send pump "Cal, v" where v the amount that was actually pumped.

After this the pump should be calibrated. This is useful because the code (while it doesnt yet) will pump the exact volume of water that the specific container has (no overflow).

Folders have been added with .ino files for putting the pump in i2c mode and calibrating them. (Note neither have these have been tested yet).
They should be run in that order! Put the pumps in I2C mode and give them a dedicated unique address (relative to the other pumps on the same sampler) before calibrating!!

