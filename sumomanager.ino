#define sensor_L 2
#define sensor_R 3

#define TrigPin A5
#define EchoPin A4

#define D0 10
#define D1 9
#define D2 6
#define D3 5

int duration, cm;
int speed = 50;
int attackSpeed = 150; // ความเร็วสำหรับพุ่งชน

void setup() {
 // Serial.begin(9600);
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
  // อ่านค่าจากเซ็นเซอร์
  int sensorLeft = digitalRead(sensor_L);
  int sensorRight = digitalRead(sensor_R);
  readSensor();

  // ตรวจจับคู่ต่อสู้
  if (cm > 0 && cm <= 20) {
    rushAttack(); // พุ่งชน
  }
  else {
    // การควบคุมตามเซ็นเซอร์ L และ R
    if (sensorLeft == 0 && sensorRight == 0) {
      stop();
      bk();
      delay(500);
      sl();
      delay(400);
    }
    else if (sensorLeft == 1 && sensorRight == 1) {
      fd();
    }
    else if (sensorLeft == 0 && sensorRight == 1) {
      stop();
      bk();
      delay(500);
      sr();
      delay(400);
    }
    else if (sensorLeft == 1 && sensorRight == 0) {
      stop();
      bk();
      delay(500);
      sl();
      delay(400);
    }
  }
}

// อ่านค่าจาก ultrasonic sensor
void readSensor() {
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);  // ปรับเป็น 10 ไมโครวินาที
  digitalWrite(TrigPin, LOW);

  duration = pulseIn(EchoPin, HIGH);
  cm = duration / 29 / 2;

  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.println(" cm");
  
  delay(50);
}

// ฟังก์ชันพุ่งชน
void rushAttack() {
  Serial.println("ATTACK!!");
  analogWrite(D1, attackSpeed);
  digitalWrite(D0, LOW);
  analogWrite(D3, attackSpeed);
  digitalWrite(D2, LOW);
  delay(300);  // พุ่งชน 0.3 วินาที
}

// ฟังก์ชันเดินหน้า
void fd() {
  analogWrite(D1, speed);
  digitalWrite(D0, LOW);
  analogWrite(D3, speed);
  digitalWrite(D2, LOW);
}

// ฟังก์ชันถอยหลัง
void bk() {
  analogWrite(D0, speed);
  digitalWrite(D1, LOW);
  analogWrite(D2, speed);
  digitalWrite(D3, LOW);
}

// ฟังก์ชันเลี้ยวซ้าย
void sl() {
  analogWrite(D1, speed);
  digitalWrite(D0, LOW);
  analogWrite(D2, speed);
  digitalWrite(D3, LOW);
}

// ฟังก์ชันเลี้ยวขวา
void sr() {
  analogWrite(D0, speed);
  digitalWrite(D1, LOW);
  analogWrite(D3, speed);
  digitalWrite(D2, LOW);
}

// ฟังก์ชันหยุด
void stop() {
  digitalWrite(D0, HIGH);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
}
