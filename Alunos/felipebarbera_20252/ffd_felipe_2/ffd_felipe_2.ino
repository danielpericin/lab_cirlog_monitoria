#define entrada_D 3
#define entrada_clock 4
#define saida_Q 22
#define saida_nQ 26
#define led_D 24

void setup() {
  Serial.begin(9600);
  pinMode(entrada_D, INPUT_PULLUP);
  pinMode(entrada_clock, INPUT_PULLUP);
  pinMode(saida_Q, OUTPUT);
  pinMode(saida_nQ, OUTPUT);
  pinMode(led_D, OUTPUT);
}

bool last_entrada_D = 0;
bool last_entrada_clock = 0;
bool estado_D = 0;
bool clock = 0;
bool D = 0;
bool Q = 0;
bool nQ = 1; // nQ representa Q barrado

bool Q1 = 0;
bool Q2 = 1;
bool nQ1 = !Q1;
bool nQ2 = !Q2;

bool FFD(bool estado_D, bool clock, bool &Q, bool &Qn){
    Q = 0;
    nQ = 1;
    clock = !digitalRead(entrada_clock);
    bool NAND1 = !(estado_D && clock);
    bool NAND2 = !(!estado_D && clock);
    Q = !(NAND1 && nQ); //1
    nQ = !(NAND2 && Q); //0
  }

void loop() {
  if(!digitalRead(entrada_D) && !last_entrada_D){
    estado_D = !estado_D;
  }else{
    estado_D = estado_D;
  }
  last_entrada_D = !digitalRead(entrada_D);

  if(!digitalRead(entrada_clock) && !last_entrada_clock){
    clock = !digitalRead(entrada_clock);
    bool D1 = Q2;
    bool D2 = Q1;
    FFD(D1, clock, Q1, nQ1);
    FFD(D2, clock, Q2, nQ2);
  }

  last_entrada_clock = !digitalRead(entrada_clock);

  digitalWrite(led_D, estado_D);
  digitalWrite(saida_Q, Q);
  digitalWrite(saida_nQ, nQ);

  Serial.print(Q1);
  Serial.print("----");
  Serial.println(Q2);
  delay(100);
}