#define IN1 3 
#define IN2 4          // Mesma notação usada na placa do driver
#define IN3 5
#define IN4 6

#define botaoClock 2 

bool lastClock = HIGH;
bool Q1 = LOW;
bool Q2 = LOW;


bool AND(bool a, bool b) { return a && b; }
bool NAND(bool a, bool b){ return !(a && b); }

bool FFD(bool D, bool CLK, bool &Q, bool &Qn) {
    if (clock && !lastClock){          //

    bool S = AND(D, CLK);       
    bool R = AND(!D, CLK);  

    bool nextQ  = NAND(S, Qbar);
    bool nextQbar = NAND(R, nextQ);

    Q = nextQ;
    Qbar = nextQbar;

    return Q;
    
    }

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
    bool D1 = Q1bar;
    bool D2 = (Q1 ^ Q2);
    
    FFD(D1, clock, Q1, Q1bar); // Q1 (menos significativo)
    FFD(D2, clock, Q2, Q2bar); // Q2 (mais significativo)

   



}