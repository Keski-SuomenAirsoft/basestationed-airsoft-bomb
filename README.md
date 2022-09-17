# basestationed-airsoft-bomb
An airsoft prop bomb that activates when put on a base station.

This project is powered by Arduino and uses a pair of RFID tags to know when the bomb is inserted to the base station.

All parts are 3D-printable but the material recommendation for the base station is wood.

Some pointers on the construction of this prop:

* Dimensions on the base unit are just a guideline. 
* The lid and lower part of the bomb are intended to be secured to each other with 45mm long M5 bolts. 
* Be aware that the 3D model of the lid has no holes for the external components, like the screen, the piezo element or the buttons, so make sure to design them yourself to suit your needs. 

Where are we now:

* The RFID based activation and pausing are functional.
* The countdown timer is functional, but the timing is not completely accurate (I have no idea idea why). 
* The DIP switch needs some more ideas (partially figured out). 

Libraries you need for this are following:
* RFID     https://github.com/miguelbalboa/rfid
* TM1637   https://github.com/avishorp/TM1637
