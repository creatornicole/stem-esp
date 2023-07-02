/////////////////////////////////////////////////////////////////////////////
//
// Program to test how to control the direction and speed of a DC motor
// Using ESP32 and L298N Motor Driver
//
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// TODO:
// Check Function of DC motor (PWM and Enable Pin implemented correct?)
//
/////////////////////////////////////////////////////////////////////////////

// Motor A //////////////////////////////////////////////////////////////////
// GPIOs the motor pins are connected to
// Motor Spin Forward: IN1 LOW, IN2 HIGH
// Motor Spin Backwards: IN1 HIGH, IN2 LOW
const int motor1Pin1 = 32; // connected to IN1 L298N Motor Driver
const int motor1Pin2 = 33; // connected to IN2 L298N Motor Driver

// Sensor Pins //////////////////////////////////////////////////////////////
// Sensor check position of flap to determine direction of motor spin
const int sensor1FlapClosed = 14; // GPIO-pin connected to sensor which symbolizes closed flap
const int sensor2FlapOpened = 25; // GPIO-pin connected to sensor which symbolizes open flap

// Magnetfeld nicht vorhanden 3090-3100
// Magnet vor Sensor 4095
int sensor1Value = 0;
int sensor2Value = 0;

// Set Up Code
void setup() {
  // Set Up Pins as Outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);

  Serial.begin(9600);
}

// Main Code - run repeadtedly
void loop() {

  //if signal is detected (land esp button pressed) check position
  //if() {

    sensor1Value = analogRead(sensor1FlapClosed); // read value from pin
    sensor2Value = analogRead(sensor2FlapOpened); 

    // 4095 MAX Value
    if(sensor1Value >= 4090) { // in case of closed flap -> open

      while(sensor2Value <= 4090) { // as long as flap is not opened completely

        // move DC motor forward at maximum speed
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, HIGH);

        // read value to check if opened position is reached
        sensor2Value = analogRead(sensor2FlapOpened); 

      }

      // Wait until measurement from sensor is detected

      // Send measurement data to Land-ESP

    } else if(sensor2Value >= 4090) { // in case of opened flap -> close

      while(sensor1Value <= 4090) { // as long as flap is not closed completely

        // move DC motor backwards at maximum speed
        digitalWrite(motor1Pin1, HIGH);
        digitalWrite(motor1Pin2, LOW);

        // read value to check if closed position is reached
        sensor1Value = analogRead(sensor1FlapClosed); 

      }

    }

     // Once flap is closed, stop DC motor
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);

    delay(5000);

  //}
}