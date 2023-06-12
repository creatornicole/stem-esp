# How to use ESP32 to control DC motor

## How to control the speed and direction of DC motor?

(using L298N motor driver - e.g. [1.5 A 2 way DC motor driver module speed dual H-bridge replacement stepper L298N](https://www.amazon.de/dp/B09KN522CK?psc=1&ref=ppx_yo2ov_dt_b_product_details) and ESP 32 - e.g.  TTGO LoRa32-OLED)

---

## Introduction to DC Motor

### DC Motor Pinout
- DC motor includes two wires (negative (black), positive (red))

### How DC Motor Works
- direction and speed of DC motor determined by [how we provide power](https://esp32io.com/images/tutorial/how-to-control-dc-motor.jpg) to it
- using PWM: the bigger duty cycle PWM is, the bigger speed the motor spins


## How to control speed and direction of DC motor using ESP32
- DC motor works with high voltage
	- can burn ESP32 -> cannot connect DC motor directly to ESP32
	- need hardware driver between DC motor and ESP32
- [Driver takes three responsiblities](https://esp32io.com/images/tutorial/esp32-controls-dc-motor.jpg)
	- protecting ESP32 from high voltage
	- receiving signal from ESP32 to change the pole of power supply to control the motor's direction
	- amplifying the PWM signal from ESP32 (current and voltage) to control the motor's speed

---

## L298N Motor Driver
- [L298N Driver Pinout](https://esp32io.com/images/tutorial/l298n-driver-pinout.jpg)
	- can control two DC motor independently
		- first (motor A): controlled by IN1, IN2, ENA, OUT1, OUT2 pins
		- second (motor B): controlled by IN3, IN4, ENB, OUT3, OUT4 pins

---

## Control DC Motor

### Control Speed of DC Motor
- control speed of DC motor by generating PWM signal to the ENA/ENB pin of L298N
	- connect ESP32's digital output pin to L298N's ENA/ENB pin
	- or create PWM signal to ENA/ENB pin by using analogWrite() function
```C
/* Speed is value between 0 and 255 (255 maximum speed, 0 motor stops) */*
analogWrite(PIN_ENA, speed); //control motor A
analogWrite(PIN_ENB, speed); //control motor B
```

### Control Direction of DC Motor
- by IN1 and IN2 pins for motor A
| IN1 pin | IN2 pin | Direction |
|---------|----------|-----------|
| HIGH | LOW | DC Motor A rotates clockwise direction |
| LOW | HIGH | DC Motor A rotates in anticlockwise direction |
| HIGH | HIGH | DC Motor A stops |
| LOW | LOW | DC Motor A stops |
```C
/* Control motor A clockwise */
digitalWrite(PIN_IN1, HIGH);
digitalWrite(PIN_IN2, LOW);
```
```C
/* Control motor A anti-clockwise */
digitalWrite(PIN_IN1, LOW);
digitalWrite(PIN_IN2, HIGH);
```

- by IN3 and IN4 pins for motor B
| IN3 pin | IN4 pin | Direction |
|---------|----------|-----------|
| HIGH | LOW | DC Motor B rotates clockwise direction |
| LOW | HIGH | DC Motor B rotates in anticlockwise direction |
| HIGH | HIGH | DC Motor B stops |
| LOW | LOW | DC Motor B stops |

### Stop DC Motor
- two ways
	- controlling speed to 0
	```C
analogWrite(PIN_ENA, 0);
```
	- controlling IN1 and IN2 pins to same LOW or HIGH
	```C
	digitalWrite(PIN_IN1, HIGH);
	digitalWrite(PIN_IN2, HIGH);

	/* OR */

	digitalWrite(PIN_IN1, LOW);
	digitalWrite(PIN_IN2, LOW);
```

---

## Control DC Motor with L298 driver
- remove three jumpers on L298N module (before [wiring](https://esp32io.com/images/tutorial/esp32-dc-motor-l298n-wiring-diagram.jpg))

---

## ESP32 Code
- Test code:
	- ESP32 controls the DC motor's speed increasingly
	- ESP32 inverts the DC motor's direction
	- ESP32 controls the DC motor's speed decreasingly
	- ESP32 stops the DC motor
```C
/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-dc-motor
 */

#define PIN_IN1  27 // ESP32 pin GIOP27 connected to the IN1 pin L298N
#define PIN_IN2  26 // ESP32 pin GIOP26 connected to the IN2 pin L298N
#define PIN_ENA  14 // ESP32 pin GIOP14 connected to the EN1 pin L298N

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins as outputs.
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_ENA, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(PIN_IN1, HIGH); // control the motor's direction in clockwise
  digitalWrite(PIN_IN2, LOW);  // control the motor's direction in clockwise

  for (int speed = 0; speed <= 255; speed++) {
    analogWrite(PIN_ENA, speed); // speed up
    delay(10);
  }

  delay(2000); // rotate at maximum speed 2 seconds in clockwise direction

  // change direction
  digitalWrite(PIN_IN1, LOW);   // control the motor's direction in anti-clockwise
  digitalWrite(PIN_IN2, HIGH);  // control the motor's direction in anti-clockwise

  delay(2000); // rotate at maximum speed for 2 seconds in anti-clockwise direction

  for (int speed = 255; speed >= 0; speed--) {
    analogWrite(PIN_ENA, speed); // speed down
    delay(10);
  }

  delay(2000); // stop motor 2 second
}

```


## References
12.06.2023
[ESP32 - DC Motor](https://esp32io.com/tutorials/esp32-dc-motor?utm_content=cmp-true)

### Further Read
[Interface L298N DC Motor Driver Module with ESP32](https://microcontrollerslab.com/l298n-dc-motor-driver-module-esp32-tutorial/)
[ESP32 with DC Motor and L298N Motor Driver – Control Speed and Direction](https://randomnerdtutorials.com/esp32-dc-motor-l298n-motor-driver-control-speed-direction/)
[Arduino - DC Motor](https://arduinogetstarted.com/tutorials/arduino-dc-motor#content_about_l298n_driver)

