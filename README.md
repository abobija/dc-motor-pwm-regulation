# dc-motor-pwm-regulation
DC Motor PWM speed regulation and IR tachometer

## Description

One MCU is responsible for regulation speed of DC motor with Pulse Width Modulation (PWM), while other MCU have responsibility for measuring that speed. Everything will be easy if there is wire connection between this two MCUs, but there are no physical connection between them. CD which contains four drilled holes, rotates between IR emitting diode, and phototransistor on opposite side. When the hole drilled on CD comes to the sensor, and IR light pass from diode to transistor, internal MCU interrupt will be triggered. Applications for both MCUs are written in plain C.

## Demo
[![Tachometer - Optical Infra Red](https://img.youtube.com/vi/YdqVJecZhuM/mqdefault.jpg)](https://www.youtube.com/watch?v=YdqVJecZhuM)

## Microcontrollers

- PWM Generator - `PIC12F628`
- Tachometer - `PIC16F886`
