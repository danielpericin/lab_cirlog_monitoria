#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
#define botaoClock 8

bool Q1 = 0, Q1bar = 1;
bool Q2 = 0, Q2bar = 1;
bool Q3 = 0, Q3bar = 1;

bool QM1 = 0, QM1bar = 1;
bool QM2 = 0, QM2bar = 1;
bool QM3 = 0, QM3bar = 1;

bool lastCLK = 0;

// Funções lógicas
bool AND(bool a, bool b){return a && b;}
bool NAND(bool a, bool b){return !(a && b);}
bool OR(bool a, bool b){return a || b;}
bool NOT(bool a){return !a;}

// FFD mestre-escravo com estado próprio
void FFD(bool D, bool CLK, bool &Q, bool &Qbar, bool &QM, bool &QMbar) {
  // LATCH MESTRE (ativo em CLK=1)
  bool Sm = NAND(D, CLK);
  bool Rm = NAND(NOT(D), CLK);
  QM    = NAND(Sm, QMbar);
  QMbar = NAND(Rm, QM);

  // LATCH ESCRAVO (ativo em CLK=0)
  bool CLKbar = NOT(CLK);
  bool Se = NAND(QM, CLKbar);
  bool Re = NAND(QMbar, CLKbar);
  Q    = NAND(Se, Qbar);
  Qbar = NAND(Re, Q);
}

void setup() {
  Serial.begin(9600);
  Serial.println("=== Contador 3 bits com FFD ===");
  Serial.println("Pressione o botão para gerar clock.");
  Serial.println("-----------------------------");

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(botaoClock, INPUT_PULLUP);

  // Inicializa os FFDs
  FFD(LOW, LOW, Q1, Q1bar, QM1, QM1bar);
  FFD(LOW, LOW, Q2, Q2bar, QM2, QM2bar);
  FFD(LOW, LOW, Q3, Q3bar, QM3, QM3bar);
}

void loop() {
  bool CLK = !digitalRead(botaoClock);

  // Detecta flanco de subida
  if (CLK && !lastCLK) {

    // Calcula os próximos estados do contador
    bool D1 = NOT(Q1);
    bool D2 = Q2 ^ Q1;
    bool D3 = Q3 ^ (Q2 && Q1);

    // Atualiza flip-flops independentes
    FFD(D1, CLK, Q1, Q1bar, QM1, QM1bar);
    FFD(D2, CLK, Q2, Q2bar, QM2, QM2bar);
    FFD(D3, CLK, Q3, Q3bar, QM3, QM3bar);

    // Saídas (para LEDs ou driver)
    digitalWrite(IN1, Q1);
    digitalWrite(IN2, Q2);
    digitalWrite(IN3, Q3);
    digitalWrite(IN4, LOW);

    // Mostra resultado no Serial
    Serial.print("CLK ↑  |  Estado: ");
    Serial.print(Q3);
    Serial.print(Q2);
    Serial.println(Q1);
  }

  lastCLK = CLK;
  delay(80); // debounce simples
}