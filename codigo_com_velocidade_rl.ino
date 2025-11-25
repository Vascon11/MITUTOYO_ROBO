#include <Bluepad32.h>

ControllerPtr myControllers[BP32_MAX_GAMEPADS];

// Motor A (direito)
#define ENA 25
#define IN1 2
#define IN2 4

// Motor B (esquerdo)
#define ENB 26
#define IN3 12
#define IN4 13

// Canais PWM do ESP32
#define PWM_FREQ 5000
#define PWM_RES 8  // 0–255
#define CH_A 0
#define CH_B 1

void onConnectedController(ControllerPtr ctl) {
  Serial.printf("Controle conectado: %s\n", ctl->getModelName().c_str());
  myControllers[0] = ctl;
}

void onDisconnectedController(ControllerPtr ctl) {
  Serial.println("Controle desconectado!");
  myControllers[0] = nullptr;
}

void processGamepad(ControllerPtr ctl) {
  int r2 = ctl->throttle();  // 0–1023
  int l2 = ctl->brake();     // 0–1023
  bool r1 = ctl->r1();
  bool l1 = ctl->l1();

  // Mapeia intensidade para 0–255
  int speedA = map(r2, 0, 1023, 0, 255);
  int speedB = map(l2, 0, 1023, 0, 255);

  // Motor A (direito)
  if (r2 > 200) {  // Frente
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    ledcWrite(CH_A, speedA);
  } else if (r1) { // Ré
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    ledcWrite(CH_A, 200);  // Velocidade fixa na ré
  } else {  // Parado
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    ledcWrite(CH_A, 0);
  }

  // Motor B (esquerdo)
  if (l2 > 200) {  // Frente
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    ledcWrite(CH_B, speedB);
  } else if (l1) { // Ré
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    ledcWrite(CH_B, 200);
  } else {  // Parado
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    ledcWrite(CH_B, 0);
  }

  Serial.printf("A:%d(%d)  B:%d(%d)\n", r2, speedA, l2, speedB);
}

void processControllers() {
  for (auto ctl : myControllers) {
    if (ctl && ctl->isConnected() && ctl->isGamepad())
      processGamepad(ctl);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Configura PWM
  ledcSetup(CH_A, PWM_FREQ, PWM_RES);
  ledcSetup(CH_B, PWM_FREQ, PWM_RES);
  ledcAttachPin(ENA, CH_A);
  ledcAttachPin(ENB, CH_B);

  Serial.println("Iniciando Bluepad32...");
  BP32.setup(&onConnectedController, &onDisconnectedController);
  BP32.forgetBluetoothKeys();
}

void loop() {
  bool updated = BP32.update();
  if (updated) processControllers();
  delay(20);
}
