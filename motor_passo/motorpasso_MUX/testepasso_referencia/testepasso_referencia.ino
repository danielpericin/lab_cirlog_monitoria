#include <Stepper.h>

#define STEPS_PER_REV 200

#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

Stepper motor(STEPS_PER_REV, IN1, IN3, IN2, IN4);

void setup() {
  Serial.begin(9600);
  motor.setSpeed(60);
  Serial.println("Motor de passo 4 fios - contador 3 bits");
}

void loop() {
  static int contador = 0;
  contador = (contador + 1) % 8;

  Serial.print((contador >> 2) & 1);
  Serial.print((contador >> 1) & 1);
  Serial.println(contador & 1);

  motor.step(1);

  delay(100);
}