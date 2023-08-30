# Arduino-Rc-car

This Arduino project turns your Arduino board into a remote-controlled car using two NRF24L01 wireless modules. It allows you to control the car's movement and direction wirelessly.

## Components

- 2 Arduino boards (Uno or similar)
- 2 NRF24L01 wireless modules
- 1 Joystick module
- 1 Servo motor
- 2 DC motors
- Motor driver module (L298N or similar)

## Wiring

### Transmitter (Controller)

- Connect the joystick's X-axis to analog pin 1 and the Y-axis to analog pin 0 on the Arduino.
- NRF24L01 module connections:
  - CE pin to digital pin 9
  - CSN pin to digital pin 10

### Receiver (RC Car)

- Servo motor connections:
  - Signal wire to digital pin 0
  - Power and ground as per servo specifications
- Motor driver connections (L298N or similar):
  - Motor A:
    - Enable pin to digital pin 6
    - IN1 to digital pin 7
    - IN2 to digital pin 4
  - Motor B:
    - Enable pin to digital pin 5
    - IN3 to digital pin 3
    - IN4 to digital pin 2
- NRF24L01 module connections:
  - CE pin to digital pin 9
  - CSN pin to digital pin 10

## Usage

1. Upload the transmitter code to one Arduino board (the controller).
2. Upload the receiver code to the other Arduino board (the RC car).
3. Power both Arduinos.
4. The joystick on the controller Arduino can now be used to wirelessly control the RC car's movement and direction.

## Additional Notes

- The NRF24L01 modules are used for wireless communication between the two Arduinos. Ensure they are correctly connected and configured.
- Adjust the thresholds (`THRESHOLD_FORWARD` and `THRESHOLD_BACKWARD`) in the code to match your joystick's behavior.
- Calibrate the servo motor's range by adjusting `SERVO_MIN` and `SERVO_MAX` to suit your needs.
- Ensure that the servo and motor driver connections are accurate for your specific hardware setup.

For any issues or questions, please refer to the Arduino documentation or seek help from the Arduino community.

Enjoy your Arduino RC car project!
