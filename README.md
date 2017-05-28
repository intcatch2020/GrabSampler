This is the arduino firmware for the grab sampler designed to work with the Platypus EBoard.

Notes
- It should be used as a json passthrough
- It should be powered via the sensor port

Issues
- At the moment there is some malformed json or something coming through which isnt letting enable commands work correctly. Not sure if its how they are being sent from the eboard or the actual parsing but enabling 1 then enabling 2 will only enable 1.
- Get rid of the timing system entirely. Volumetric dispense should be the only option.
- Add calibration files to this one that get called with certain json strings. This will allow the tablet app to be able to calibrate it (although this probably wont be fun to code on any level).
- Add a disable call to the pump between resets.
- Add a jsonpassthrough set call that takes a string and an int, this will be useful for passing and parsing args values that are more than 1 char long, such as volume. 


Setting Up Arduino:
1) On the sensor cable use the white (RX+) and brown (TX+) to transfer serial commands from the eboard to the sampler.
2) Connect the ground (grey on sensor cable) to the ground on the arduino.
3) If you're using a due RX and TX should go into Serial1 (Brown -> pin 19, White -> pin 18)
4) On the sensor cable the red wire should go into either vin or 5v on the samplers arduino. (Dont know if its safe to power it over usb and 5v so probably dont?)
5) The [find out which color wire] is the power cable that comes through the sensor port from the battery. It says 12v on the sensor cable diagram but will be the voltage of the batter (16v~). Power the pumps using this line. The pumps operate on 12-24v.

Setting Up Pumps: (Note this still needs to be tested and stuff)
https://www.atlas-scientific.com/_files/code/pmp-i2c.pdf

1) You have to first put the pumps in I2C mode instead of UART mode. You will also need to specify the I2C address (1-127). To do this over serial you will have to send it the ascii string "I2C,addr" where addr is a number from 1-127. The LED on motor controller on the pump should then be blue, if not it probably failed so try again or something.
2) There are 4 wires you will have to connect from the pump to the samplers arduino. Red should go to 5v, Black to ground. All the green wires from your 4 samplers should connect to each other and go to to SDA1, White to SCL1. NOTE WERE USING SDA1 AND SCL1 NOT SDA AND SCL. You will also need to connect pullup resistors between each sda1 and scl1 from 3.3v on the arduino. I used 20.5kohm resistors. (Note it might be a good idea to use a small breadboard for this then just layer some kind of epoxy over it after everything works.


Calibrating The pumps:
These pumps give you alot of control and can do volumetric
Page 10 of https://www.atlas-scientific.com/_files/_datasheets/_peristaltic/EZO_PMP_Datasheet.pdf explains how to calibrate the pumps.
1) Send pump "D,10" it will attempt to pump 10 ml of liquid
2) Measure how much liquid was actually pumped
3) Send pump "Cal, v" where v the amount that was actually pumped.

After this the pump should be calibrated. This is useful because the code (while it doesnt yet) will pump the exact volume of water that the specific container has (no overflow).

Folders have been added with .ino files for putting the pump in i2c mode and calibrating them. (Note neither have these have been tested yet).
They should be run in that order! Put the pumps in I2C mode and give them a dedicated unique address (relative to the other pumps on the same sampler) before calibrating!!

