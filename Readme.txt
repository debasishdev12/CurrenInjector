****This is a high voltage project.so be carefull with connection******

In this project a high voltage vaiac from servo-stabilizer is used. A 12 volt DC motor shaft is
coupled with the variac rotator. A normal variac can also be used. In that case we have to couple
a de motor or servo motor with that variac.

Current injector is such a device from which we can consume a limited amount of current.

Generaly we use variac for changing the voltage. and Changing voltage means changing current.
But in this way have to manually change voltage by varying the variac and read voltage by meter
and then by ohm's law get the current.

This project maintains everything after just giving input to it. We have to just set the current
pressing keypad in the lcd. and the motor which is coupled with the variac turn automaticaly to
output the desired current. if load is increased then motor turns and increases the volatge to maintain
the desired current.

Here instantaneous current is always compared with the desired current we set in the lcd and by PD
algorithm motor moves accordingly to maintain the vairac voltage thus output current.

This project has been made for Relay testing purpose.for high voltage relay it is sometimes required
to test the amount of current in which it is tripped. In this case, we have to set the current on the
display, connect the relay, and the ouput current is pushed to that amount. 

For testing purpose some bulbs in parallel can be used as load as current injector can not operate with
open terminal.

The project is under development till now.  