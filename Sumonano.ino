#define sensor_L 2
#define sensor_R 3
#define L digitalRead(sensor_L)
#define R digitalRead(sensor_R)

#define TrigPin A5
#define EchoPin A4

#define D0 10
#define D1 9
#define D2 6
#define D3 5

int duration, cm;
float  speed = 90.5;
int ea = 100;

void setup() {
  Serial.begin(9600);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(sensor_L, INPUT);
  pinMode(sensor_R, INPUT);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}

void loop() {
  readSensor();
  if (cm < ea){
    int forwardspeed  = 255;
  analogWrite(D0, forwardspeed);
  digitalWrite(D1, LOW);
  analogWrite(D2, forwardspeed);
  digitalWrite(D3, LOW);
  }
   else if (L == 1 && R == 1) {
    fd();
  }
  else if (L == 0 && R == 0) {
    stop();
    bk();
    delay(500);
    sl();
    delay(400);
  }

  else if (L == 0 && R == 1) {
   
    stop();
   
    bk();
    delay(500);
    sr();
    delay(400);
  }
  else if (L == 1 && R == 0) {
    stop();
    bk();
    delay(500);
    sl();
    delay(400);
  }
}

void readSensor() {
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(TrigPin, LOW);

  duration = pulseIn(EchoPin, HIGH);
  cm = duration / 29 / 2;
  Serial.print(String(cm) + "\t");
  Serial.print(String(L) + "\t");
  Serial.println(R);
  delay(10);
}

void fd() {
  analogWrite(D1, speed);
  digitalWrite(D0, LOW);
  analogWrite(D3, speed);
  digitalWrite(D2, LOW);
}

void bk() {
  analogWrite(D0, speed);
  digitalWrite(D1, LOW);
  analogWrite(D2, speed);
  digitalWrite(D3, LOW);
}

void sl() {
  analogWrite(D1, speed);
  digitalWrite(D0, LOW);
  analogWrite(D2, speed);
  digitalWrite(D3, LOW);
}

void sr() {
  analogWrite(D0, speed);
  digitalWrite(D1, LOW);
  analogWrite(D3, speed);
  digitalWrite(D2, LOW);
}

void stop() {
  digitalWrite(D0, HIGH);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
}
