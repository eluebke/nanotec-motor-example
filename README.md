# Nanotec motor example
An example of how to control a Nanotec motor via the serial port.

This demo shows how to send and receive instructions to a Nanotec motor using serial communication. I used the serial components of Qt, but any serial connection library will do.

The program will establish a connection, set the target speed of the motor to 1000 Hz, then start the motor, let it spin for five seconds, then stop it and exit.

## Hints

If you are using Qt too, don't forget to add the line "QT += serialport" to the .pro-file of your project.
