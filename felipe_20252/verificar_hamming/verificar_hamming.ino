int codigo[7] = {1, 0, 0, 1, 1, 0, 1};

void setup() {
  Serial.begin(9600);

  Serial.print("Palavra recebida: ");
  for (int i = 0; i < 7; i++) {
    Serial.print(codigo[i]);
    Serial.print(" ");
  }
  Serial.println();

  int p1 = codigo[0];
  int p2 = codigo[1];
  int d1 = codigo[2];
  int p3 = codigo[3];
  int d2 = codigo[4];
  int d3 = codigo[5];
  int d4 = codigo[6];

  int c1 = p1 ^ d1 ^ d2 ^ d4;
  int c2 = p2 ^ d1 ^ d3 ^ d4; 
  int c3 = p3 ^ d2 ^ d3 ^ d4; 

  int erro_posicao = 0;

  if (c1 == 0 && c2 == 0 && c3 == 0) {
    erro_posicao = 0;
  } 
  else if (c1 == 1 && c2 == 0 && c3 == 0) erro_posicao = 1;
  else if (c1 == 0 && c2 == 1 && c3 == 0) erro_posicao = 2;
  else if (c1 == 1 && c2 == 1 && c3 == 0) erro_posicao = 3;
  else if (c1 == 0 && c2 == 0 && c3 == 1) erro_posicao = 4;
  else if (c1 == 1 && c2 == 0 && c3 == 1) erro_posicao = 5;
  else if (c1 == 0 && c2 == 1 && c3 == 1) erro_posicao = 6;
  else if (c1 == 1 && c2 == 1 && c3 == 1) erro_posicao = 7;

  if (erro_posicao != 0) {
    Serial.print("Erro no bit: ");
    Serial.println(erro_posicao);
    Serial.println("Corrigindo...");

    codigo[erro_posicao - 1] = !codigo[erro_posicao - 1];
  } else {
    Serial.println("Palavra sem erro de ruido.");
  }

  Serial.print("Palavra atualizada: ");
  for (int i = 0; i < 7; i++) {
    Serial.print(codigo[i]);
    Serial.print(" ");
  }
  Serial.println();

  Serial.print("Palavra decodificada (4 bits): ");
  Serial.print(codigo[2]); Serial.print(" ");
  Serial.print(codigo[4]); Serial.print(" ");
  Serial.print(codigo[5]); Serial.print(" ");
  Serial.print(codigo[6]); Serial.println();
}

void loop() {
}
