# Cloud_Chamber

## Project

This project is a colaboration between Dr. A. Knoll, Suzan Eyre and Imperial's Space Society. 

The aim of the project is to fly a temperature driven isopropyl alcool cloud chamber on a high altitude baloon. The aim of the flight is to aquire video data from the cloud chamber and suroundings.

## Contents
This repository contains the control code for the cloud chambers heaters. 

Cloud chambers allow the visualisation of the trajectory of particles going through the chamber by creating a region of oversaturated vapor. In this region the enegy deposited by the passage of a particle will  lead to the localised condensation of the gas, forming visible droplets which can be observed. To drive the formation of regions of oversatured vapor a temperature gradient can be created. Gas diffusing down this gradient can reach the necessary conditions to form droplets in the vicinity of a passing particle.

The aim of the cloud chamber's control system si to guarantee the existence and strength of the temperature gradient. In addition to this the conditions insides the payload box must be kept appropriate for the operation of the control system itself. This is achived by temperature controlling a compartement of the craft at a set temprature. 

The control system is implemented using and Arduino Nano ATmegaP328P.

## Features and implementation.

The hardware features the following components:
- Board environment temperature sensor (TMP36) on A0
- External temperature sensor 1 (TMP36) on A1
- External temperature sensor 2 (TMP36) on A2
- Power supply Buck "not ON" pin on D1
- Builting LED as heating indicator

All temperature sensors run off the arduino's regulated 5V supply.

Code comes with debug version, implemented through compiler directives. To compile in debug mode define `DEBUG` as 1. This allows for measured temperatures to be sent on serial.

```
#define DEBUG 1 //Debug version
#define DEBUG 0 //Flight version
```
