#define IN1 3 
#define IN2 4          // Mesma notação usada na placa do driver
#define IN3 5
#define IN4 6

#define botaoClock 2 

bool lastClock = LOW;
bool lastCP2= LOW;
bool lastCP3 = LOW;

bool Q1 = LOW;
bool Q2 = LOW;
bool Q3 = LOW;

bool Q1bar = !Q1;
bool Q2bar = !Q2;
bool Q3bar = !Q3;

bool last 

bool AND(bool a, bool b){return a && b;}
bool NAND(bool a, bool b){return !(a && b);}
bool OR(bool a, bool b){return a || b;}

void FFD(bool D, bool CLK, bool &Q, bool &Qbar, bool lastCLK) {
    if (CLK && !lastCLK){          //

    bool S = AND(D, CLK);       
    bool R = AND(!D, CLK);  

    bool nextQ  = NAND(S, Qbar);
    bool nextQbar = NAND(R, nextQ);

    Q = nextQ;
    Qbar = nextQbar;
    }
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

void setup() {
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    pinMode(botaoClock, INPUT_PULLUP);
}

void loop() {
    bool clock = !digitalRead(botaoClock);

    // Entrada de cada flipflop
    bool D1 = Q1bar;
    bool D2 = Q2bar;
    bool D3 = Q3bar;

    bool CP1 = clock;
    bool CP2 = Q1bar;
    bool CP3 = Q2bar;

    // Essa ordem é essencial pro funcionamento
    FFD(D3, CP3, Q3, Q3bar, lastClock);   // Q3 (mais significativo)
    FFD(D2, CP2, Q2, Q2bar, lastCP2);   // Q2 
    FFD(D1, clock, Q1, Q1bar, lastCP3); // Q1 (menos significativo)

    // Entradas do esquema de circuito contido na mesma pasta desse código
    m1 = MUX(Q1, Q2, Q3bar, Q3bar, LOW, Q3);
    m2 = MUX(Q1, Q2, LOW, Q3bar, Q3bar, Q3bar);
    m3 = MUX(Q1, Q2, Q3, Q3, LOW, Q3bar);
    m4 = MUX(Q1, Q2, LOW, Q3, Q3, Q3);

    digitalWrite(IN1, m1);
    digitalWrite(IN2, m2);
    digitalWrite(IN3, m3);
    digitalWrite(IN4, m4);

    lastClock = clock;
    lastCP2 = CP2
    lastCP3 = CP3
}