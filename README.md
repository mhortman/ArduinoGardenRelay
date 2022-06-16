# ArduinoGardenRelay
A very simple program to allow an Arduino to turn a relay off and on for a given interval. 
I am using it to turn my water pump on, through a relay, for 5 minutes then stay off for 25 minutes.   
A bonus is if you have an Arduino with and onboard LED hooked to pin 13.  The program will flash telling you how many minutes until the 5 minute power cycle is. 
So if you have 10 minutes left, it flashes 10 times, etc.

Hook Pin 2 to a relay, and that is it!

A relay like this.  https://www.amazon.com/HiLetgo-Channel-optocoupler-Support-Trigger/dp/B00LW15A4W/ref=sr_1_4?keywords=relay+module+5v&qid=1655345166&s=industrial&sprefix=relay+module%2Cindustrial%2C292&sr=1-4
Then just put your power across the relay and you are good to go.
