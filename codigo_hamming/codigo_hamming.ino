#define botaoD1 2
#define botaoD2 3
#define botaoD3 4
#define botaoD4 5

#define ledP1 6    // P1 - paridade(D1, D2, D4)
#define ledP2 7    // P2 - paridade(D1, D3, D4)
#define ledD1 8    // D1
#define ledP3 9    // P3 - paridade(D2, D3, D4)
#define ledD2 10   // D2
#define ledD3 11   // D3
#define ledD4 12   // D4

bool d1 = false;
bool d2 = false;
bool d3 = false;
bool d4 = false;

// Tanto faz ser HIGH ou LOW, essa parte serve para que a variável não fique vaga
bool lastLeituraD1 = HIGH;
bool lastLeituraD2 = HIGH;
bool lastLeituraD3 = HIGH;
bool lastLeituraD4 = HIGH;

void setup() {
  pinMode(botaoD1, INPUT_PULLUP);
  pinMode(botaoD2, INPUT_PULLUP);
  pinMode(botaoD3, INPUT_PULLUP);
  pinMode(botaoD4, INPUT_PULLUP);

  pinMode(ledP1, OUTPUT);
  pinMode(ledP2, OUTPUT);
  pinMode(ledD1, OUTPUT);
  pinMode(ledP3, OUTPUT);
  pinMode(ledD2, OUTPUT);
  pinMode(ledD3, OUTPUT);
  pinMode(ledD4, OUTPUT);
}

void loop() {
  // como o códico é executado de cima pra baixo, primeiro fazemos as leituras dos botoes para depois considerar como um lastBotao
  // logo a comparação será sempre com o leituraD do loop anterior que será escrito como lastBotao antes que o loop atual o escreva como leituraD
  // usamos ! pois estes pins estão como INPUT_PULLOUT
  bool leituraD1 = !digitalRead(botaoD1);
  bool leituraD2 = !digitalRead(botaoD2);
  bool leituraD3 = !digitalRead(botaoD3);
  bool leituraD4 = !digitalRead(botaoD4);

  // por se tratar de uma porta AND o if só será verdadeiro se leituraD seja HIGH e lastBotao seja LOW ou seja: borda de subida
  // depois de apertar o botão tornando leituraD HIGH 
  if (leituraD1 && !lastLeituraD1) d1 = !d1;
  if (leituraD2 && !lastLeituraD2) d2 = !d2;
  if (leituraD3 && !lastLeituraD3) d3 = !d3;
  if (leituraD4 && !lastLeituraD4) d4 = !d4;

  // constantemente copia o estado atual do botão pra comparar com o estado seguinte
  lastLeituraD1 = leituraD1;
  lastLeituraD2 = leituraD2;
  lastLeituraD3 = leituraD3;
  lastLeituraD4 = leituraD4;

  // operações de paridade
  bool p1 = (d1 ^ d2 ^ d4);
  bool p2 = (d1 ^ d3 ^ d4);
  bool p3 = (d2 ^ d3 ^ d4);

  // display dos bits nos leds
  digitalWrite(ledP1, p1);
  digitalWrite(ledP2, p2);
  digitalWrite(ledD1, d1);
  digitalWrite(ledP3, p3);
  digitalWrite(ledD2, d2);
  digitalWrite(ledD3, d3);
  digitalWrite(ledD4, d4);
}
