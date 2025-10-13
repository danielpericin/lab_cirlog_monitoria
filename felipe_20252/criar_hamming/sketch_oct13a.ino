#define pino_A 5
#define pino_B 4
#define pino_C 3
#define pino_D 2
// A é o algarismo mais significativo e D é o menos
#define botao_seletor 30

//Para o código Hamming
#define led_portas 24
#define led_6 12
#define led_5 11
#define led_4 9
#define led_3 8
#define led_2 7
#define led_1 6


void setup() {
  pinMode(pino_A, INPUT_PULLUP);
  pinMode(pino_B, INPUT_PULLUP);
  pinMode(pino_C, INPUT_PULLUP);
  pinMode(pino_D, INPUT_PULLUP);
  pinMode(botao_seletor, INPUT_PULLUP);
  pinMode(led_portas, OUTPUT);
  pinMode(led_6, OUTPUT);
  pinMode(led_5, OUTPUT);
  pinMode(led_4, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_1, OUTPUT);
  Serial.begin(9600);
}

bool A=0;
bool B=0;
bool C=0;
bool D=0;
int saida = 0;
int seletor_porta = 5;

int switch_A = 0;
int switch_B = 0;
int switch_C = 0;
int switch_D = 0;

int paridade_1 = 0;
int paridade_2 = 0;
int paridade_3 = 0;





void loop() {
  if (!digitalRead(pino_A) == 1){
    A = true;
    }
  else{
    A = false;
  }
  if (!digitalRead(pino_B) == 1){
    B = true;
    }
  else{
    B = false;
  }
  if (!digitalRead(pino_C) == 1){
    C = true;
    }
  else{
    C = false;
  }
  if (!digitalRead(pino_D) == 1){
    D = true;
    }
  else{
    D = false;
  }


  if (!digitalRead(botao_seletor) == 1){
    seletor_porta += 1;
  }
  if (seletor_porta == 0){
    saida = A && B && C && D;
  }
  else if (seletor_porta == 1){
    saida = A||B||C||D;
  }
  else if (seletor_porta == 2){
    saida = !(A && B && C && D);
  }
  else if (seletor_porta == 3){
    saida = !(A || B || C || D);
  }
  else if (seletor_porta == 4){
    saida = A^B^C^D;
  }
  
  else if (seletor_porta == 5){
    //Código de hamming
    // Para que os botões virem switches:
    if (!digitalRead(pino_A) == 1){
      if (switch_A == 0){
        switch_A = 1;
      }
      else if (switch_A == 1){
        switch_A = 0;
      }
    }
    if (!digitalRead(pino_B) == 1){
      if (switch_B == 0){
        switch_B = 1;
      }
      else if (switch_B == 1){
        switch_B = 0;
      }
    }
    if (!digitalRead(pino_C) == 1){
      if (switch_C == 0){
        switch_C = 1;
      }
      else if (switch_C == 1){
        switch_C = 0;
      }
    }
    if (!digitalRead(pino_D) == 1){
      if (switch_D == 0){
        switch_D = 1;
      }
      else if (switch_D == 1){
        switch_D = 0;
      }
    }
    // Verificador de paridade
    paridade_1 = switch_A ^ switch_B ^ switch_D;
    paridade_2 = switch_A ^ switch_C ^ switch_D;
    paridade_3 = switch_B ^ switch_C ^ switch_D;

    digitalWrite(led_portas, paridade_1);
    digitalWrite(led_6, paridade_2);
    digitalWrite(led_5, switch_A);
    digitalWrite(led_4, paridade_3);
    digitalWrite(led_3, switch_B);
    digitalWrite(led_2, switch_C);
    digitalWrite(led_1, switch_D);

  }
  else if (seletor_porta == 6){
    seletor_porta = 0;
  }
  if (saida == true){
  saida = 1;
  }
  else {
    saida = 0;
  }

  Serial.println(seletor_porta);
  //Serial.println("valor botao seletor: ");
  //Serial.println(digitalRead(botao_seletor));
  Serial.print(paridade_1);
  Serial.print(paridade_2);
  Serial.print(switch_A);
  Serial.print(paridade_3);
  Serial.print(switch_B);
  Serial.print(switch_C);
  Serial.print(switch_D);
  Serial.println("---");
  delay(200);


}
