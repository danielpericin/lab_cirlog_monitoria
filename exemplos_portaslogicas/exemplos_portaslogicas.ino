int som1 = 2;
int botao1 = 3;
int botao2 = 4;

void setup() {
  pinMode(som1, OUTPUT);
  pinMode(botao1, INPUT_PULLUP); // INPUT_PULLUP é uma forma diferente de leitura onde é enviado um sinal e se chegar ao ground a leitura será LOW
  pinMode(botao2, INPUT_PULLUP); // para que essa forma funcione o botao deve estar conectado entre o GND e o pino do arduino
}

void loop() {
  bool entrada1 = !digitalRead(botao1); // O INPUT_PULLUP inverte a logica de leitura do botão, quando apertado envia LOW, logo vou inverter a leitura inicial para torar intuitivo
  bool entrada2 = !digitalRead(botao2);

  if (entrada1 && entrada2) {
    digitalWrite(som1, HIGH);
    delay(100);
    digitalWrite(som1, LOW);
    delay(100);
  }
}
/*
 PORTA LÓGICA OR
  if (entrada1 || entrada2) {
    digitalWrite(som1, HIGH);
    delay(100);
    digitalWrite(som1, LOW);
    delay(100);
  }

PORTA LÓGICA XOR

  if (entrada1 ^ entrada2) {
    digitalWrite(som1, HIGH);
    delay(100);
    digitalWrite(som1, LOW);
    delay(100);
  }

PORTA LÓGICA XNOR

  if (!(entrada1 && entrada2)) { 
    digitalWrite(som1, HIGH);
    delay(100);
    digitalWrite(som1, LOW);
    delay(100);
  }
  */