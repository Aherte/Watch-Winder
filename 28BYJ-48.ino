volatile uint8_t counter = 0;
volatile unsigned long lastPressTime = 0;
const uint8_t debounceDelay = 200;
volatile uint8_t pinChange = 0;

const uint8_t ButtonPin = 0;
const uint8_t pin1 = 1;
const uint8_t pin2 = 2;
const uint8_t pin3 = 3;
const uint8_t pin4 = 4;

double speed = 2;  //arttırırsan hız düşer
const double motorStepsPerRevolution = (360 / 5.625) * 8;

int main(void) {
  DDRB |= (1 << pin1) | (1 << pin2) | (1 << pin3) | (1 << pin4);
  setup_Interrupt();

  while (1) {
    if (counter == 0) {
      ModeOne();
    } else if (counter == 1) {
      ModeTwo();
    } else if (counter == 2) {
      ModeThree();
    } else {
      counter = 0;
    }
  }

  return 0;
}
void setup_Interrupt() {
  DDRB &= ~(1 << ButtonPin);
  PCMSK |= (1 << ButtonPin);
  GIMSK |= (1 << PCIE);
  sei();
}
ISR(PCINT0_vect) {
  unsigned long currentMillis = millis();

  if (currentMillis - lastPressTime >= debounceDelay) {
    if (!(PINB & (1 << ButtonPin))) {
      pinChange = 1;
      counter++;
      lastPressTime = currentMillis;
    }
  }
}
void ModeThree() {
  if (pinChange == 1) {
    Alteration(3);
  }
  for (int i = 0; i < motorStepsPerRevolution * 1; i++) {
    if (counter == 2) {
      rotateCW();
    } else {
      break;
    }
  }
  Stop();
  delay(100);
  for (int i = 0; i < motorStepsPerRevolution * 1; i++) {
    if (counter == 2) {
      rotateCCW();
    } else {
      break;
    }
  }
  Stop();
  Delay(5000, 2);
}
void ModeTwo() {
  if (pinChange == 1) {
    Alteration(2);
  }
  for (int i = 0; i < motorStepsPerRevolution * 1; i++) {
    if (counter == 1) {
      rotateCCW();
    } else {
      break;
    }
  }
  Stop();
  Delay(5000, 1);
}
void ModeOne() {
  if (pinChange == 1) {
    Alteration(1);
  }
  for (int i = 0; i < motorStepsPerRevolution * 1; i++) {
    if (counter == 0) {
      rotateCW();
    } else {
      break;
    }
  }
  Stop();
  Delay(5000, 0);
}
void Stop() {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}
void rotateCW() {

  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
  delay(speed);

  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
  delay(speed);

  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
  delay(speed);

  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, LOW);
  delay(speed);

  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, LOW);
  delay(speed);

  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, HIGH);
  delay(speed);

  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, HIGH);
  delay(speed);

  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, HIGH);
  delay(speed);
}
void rotateCCW() {
  digitalWrite(pin4, HIGH);
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  delay(speed);

  digitalWrite(pin4, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  delay(speed);

  digitalWrite(pin3, HIGH);
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin4, LOW);
  delay(speed);

  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin1, LOW);
  digitalWrite(pin4, LOW);
  delay(speed);

  digitalWrite(pin2, HIGH);
  digitalWrite(pin1, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
  delay(speed);

  digitalWrite(pin2, HIGH);
  digitalWrite(pin1, HIGH);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
  delay(speed);

  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
  delay(speed);

  digitalWrite(pin1, HIGH);
  digitalWrite(pin4, HIGH);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  delay(speed);
}
void Delay(unsigned long milliseconds, uint8_t mode) {
  unsigned long startTime = millis();

  while (millis() - startTime < milliseconds) {
    if (counter != mode) {
      break;
    }
  }
}
void Alteration(uint8_t turn) {
  cli();
  DDRB |= (1 << ButtonPin);
  delay(10);
  for (int i = 0; i < turn; i++) {
    PORTB |= (1 << ButtonPin);
    delay(500);
    PORTB &= ~(1 << ButtonPin);
    delay(500);
  }
  setup_Interrupt();
  delay(10);
  pinChange = 0;
}