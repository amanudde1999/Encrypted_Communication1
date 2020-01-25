# Encrypted_Communication1
#Description: The first part of this assignment was to create a program that uses RSA encryption and decryption to have a secure communication between two arduinos. 

# Included files:
- encrypted_communication_part1.cpp
- Makefile


# Required Components: 
- 1 x 550 Ohms
- 2 x Arduino MEGA Boards
- 1 x Breadboard

# Wiring Instructions:
- Arduino 1 Pin 13 <--> Arduino 1 GND 
- Arduino 1 GND <--> Arduino 2 GND 
- Arduino 2 5V <--> Breadboard/550 ohm resistor <--> Arduino 2 Pin 13
- Arduino 1 Pin TX3 <--> Arduino 2 Pin RX3
- Arduino 2 Pin TX3 <--> Arduino 1 Pin RX3

# Running Instructions:
While in the directory that contains the MakeFile and the encrypted_communication_part1.cpp file, open two separate terminals and ensure that both the arduino's have been selected using "arduino-port-select" and appoint one of them as port 0 and the other as port 1. In one of the terminals use the command "make upload-0 && serial-mon-0" and in the other terminal use "make upload-1 && serial-mon-1". Now you are able to type into one or the other serial monitor and it will appear on the other one.

# Assumptions:
- Will not hold down a key.Holding down a key will flood the input buffer and will give wrong output on the other serial-monitor
- Will not type extremely extremely fast. Doing this will also flood the input buffer, giving wrong output on the other end. 

