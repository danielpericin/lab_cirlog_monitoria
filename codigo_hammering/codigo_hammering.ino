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
  bool d1 = !digitalRead(botaoD1); // O INPUT_PULLUP inverte a logica de leitura do botão, quando apertado envia LOW, logo vou inverter a leitura inicial para torar intuitivo
  bool d2 = !digitalRead(botaoD2);
  bool d3 = !digitalRead(botaoD3);
  bool d4 = !digitalRead(botaoD4);

  bool p1 = (d1 ^ d2 ^ d4);
  bool p2 = (d1 ^ d4 ^ d4);
  bool p3 = (d2 ^ d3 ^ d4);
  
  }
}
/*
comentários:
  
  */