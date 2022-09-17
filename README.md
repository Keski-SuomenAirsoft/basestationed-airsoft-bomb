# basestationed-airsoft-bomb
Airsoft prop a bomb that activates when put on base station

This projet is going to be powered by arduino and it uses RFID tags to know when bomb is on base station.

All parts are 3d printable but base stadion is better to be wood.

Some pointers on construct of this airsoft prop:

* Dimensions on base unit are just guideline.
* Lid and lower part of bomb is intented to secured to each other with 45mm long m5 bolts.



Where are we now.
* RFID activation and stoping is woking
* Countdown time is working and timings are nearly accurate ( i have no idea idea why delays are not accurate.)
* DIP switchs needs some more ideas ( partialy figured out.) 
* Piezo elemeents connection needs to be switched to PWM pin


Librareis you need for this are following:
* RFID     https://github.com/miguelbalboa/rfid
* TM1637   https://github.com/avishorp/TM1637
