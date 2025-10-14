#define CLK_PERIOD_MS 1000UL // Clock de 1 Hz
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5


bool AND(bool a, bool b){return a && b;}
bool NAND(bool a, bool b){return !(a && b);}
bool NOT(bool a){return !a;}
bool OR(bool a, bool b){return (a || b);}

int passos = 0;

bool Q1=0, Q2=0, Q3=0;
bool Q1bar=1, Q2bar=1, Q3bar=1;

bool QM1=0, QMbar1=1;
bool QM2=0, QMbar2=1;
bool QM3=0, QMbar3=1;

bool CLK=0, lastCLK=0;
unsigned long lastToggle=0;
unsigned long halfPeriod = CLK_PERIOD_MS/2;

bool m1 = 0, m2 = 0, m3 = 0, m4 = 0;

// ---------- Função que simula um FFD completo ----------
void FFD(bool D, bool CLK, bool &Q, bool &Qbar, bool &QM, bool &QMbar){
  bool Sm = NAND(D, CLK);
  bool Rm = NAND(NOT(D), CLK);
  QM = NAND(Sm, QMbar);
  QMbar = NAND(Rm, QM);

  bool CLKbar = NOT(CLK);
  bool Se = NAND(QM, CLKbar);
  bool Re = NAND(QMbar, CLKbar);
  Q = NAND(Se, Qbar);
  Qbar = NAND(Re, Q);
}

bool MUX(bool S0, bool S1, bool I0, bool I1, bool I2, bool I3) {
    bool S0bar = !S0;
    bool S1bar = !S1;

    bool T0 = AND(AND(S1bar, S0bar), I0);
    bool T1 = AND(AND(S1bar, S0), I1);
    bool T2 = AND(AND(S1, S0bar), I2);
    bool T3 = AND(AND(S1, S0), I3);

    bool Y = OR(OR(T0, T1), OR(T2, T3));
    return Y;
}

void setup(){
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

}

void loop(){
  unsigned long now = millis();
  if (now - lastToggle >= halfPeriod){
    lastToggle = now;
    CLK = !CLK; // alterna clock
    passos = passos + 1;
    Serial.println("Passo: ");
    Serial.print(passos);
  }

  bool D1 = !Q1;
  bool D2 = Q2 ^ Q1;
  bool D3 = Q3 ^ (Q2 && Q1);

  FFD(D1, CLK, Q1, Q1bar, QM1, QMbar1);
  FFD(D2, CLK, Q2, Q2bar, QM2, QMbar2);
  FFD(D3, CLK, Q3, Q3bar, QM3, QMbar3);
  

  delay(5);

  m1 = MUX(Q1, Q2, Q3bar, Q3bar, LOW, Q3);
  m2 = MUX(Q1, Q2, LOW, Q3bar, Q3bar, Q3bar);
  m3 = MUX(Q1, Q2, Q3, Q3, LOW, Q3bar);
  m4 = MUX(Q1, Q2, LOW, Q3, Q3, Q3);

  digitalWrite(IN1, m1);
  digitalWrite(IN2, m2);
  digitalWrite(IN3, m3);
  digitalWrite(IN4, m4);



  lastCLK = CLK;
  delay(3);
}
