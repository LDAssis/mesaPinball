//Matriz que relaciona o numero do led(0,1,2,3,4) com o pino conectado ao arduino
int leds[8][3] = {
  {32, 53, 30},
  {34, 40, 48},
  {38, 44, 51},
  {36, 42, 52},
  {37, 45, 46},
  {39, 43, 49},
  {41, 47, 50},
  {33, 35, 31}
};

//Utilizado somente para criar o efeito de onda inicial
int wave[4][2] = {
  {4, 5},
  {3, 6},
  {2, 7},
  {1, 8}
};

//Pinos dos botoes que estão ligados ao arduino
int btns[] = {29, 23, 25, 24, 26, 22, 28, 27};

//Separa os botões em grupos sendo a posição 1 representado pelo led 1 e a posição 2 pelos leds 2,3 e 4
int controlaEstados[] = {0, 0, 0, 0};

//Botoes de comando
int commandBtns[] = {3,2,4}; //3 = direito, 4 = lauch, 2 = esquerdo



//Só controla se é a primeiro loop do arduino.
boolean isFirstLoop = true;

int gameMode = 0; //0 = Automatico, 1 = Manual

unsigned long Time;
unsigned long TimeOld;


int esq = 7; // Porta braço esquerdo
int dir = 6; // Porta braço direito
int launch = 5; //Porta do lancador


void setup()
{
  TimeOld = 0;
  Time = millis();
  Serial.begin(9600);
  pinMode(esq, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(launch, OUTPUT);
  digitalWrite(esq, HIGH);
  digitalWrite(dir, HIGH);
  digitalWrite(launch, HIGH);


  // Definindo todos pinos como output
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      pinMode(leds[i][j], OUTPUT);
    }
  }
  for (int i = 1; i < 7; i++) {
    for (int j = 0; j < 3; j++) {
      digitalWrite(leds[i][j], HIGH);
    }
  }

  // Definindo botões como pullup
  for (int i = 0; i < 8; i++) {
    pinMode(btns[i], INPUT_PULLUP);
  }

  for (int i = 0; i < 3; i++) {
    pinMode(commandBtns[i], INPUT_PULLUP);
  }

}

// Este código é chamado automáticamente pelo Arduino, ficará em
// loop até que seu Arduino seja desligado
void loop()
{
  char leitura = Serial.read();
  Time = millis();

  leBtnMode();

  if (isFirstLoop) {
    reset();
    animStart();
    for (int i = 0; i < 20; i++) {
      animStart2();
    }
  }

  if (gameMode == 0) {
    if (leitura == '1') {
      digitalWrite(esq, LOW);
      delay(200);
      digitalWrite(esq, HIGH);
    }
    else if (leitura == '2') {
      digitalWrite(dir, LOW);
      delay(200);
      digitalWrite(dir, HIGH);
    }
    else if(leitura == '3') {
      digitalWrite(launch, LOW);
      delay(200);
      digitalWrite(launch, HIGH);
    }
    lePin();
    lancaBolinha();
  }else{
    lancaBolinha();
    leBtnManualMode();
    lePin();
  }


  isFirstLoop = false;
}

void reset(){
  digitalWrite(esq, HIGH);
  digitalWrite(dir, HIGH);
  digitalWrite(launch, HIGH);
  controlaEstados[0] = 0;
  controlaEstados[1] = 0;
  controlaEstados[2] = 0;
  controlaEstados[3] = 0;
}

void leBtnManualMode(){
  if (digitalRead(commandBtns[0]) == LOW){
    digitalWrite(dir, LOW);
  }else{
    digitalWrite(dir, HIGH);
  }
  
  if (digitalRead(commandBtns[1]) == LOW){
    digitalWrite(esq, LOW);
  }else{
    digitalWrite(esq, HIGH);
  }
}

void lancaBolinha(){
  if (digitalRead(commandBtns[2]) == LOW){
    digitalWrite(launch, LOW);
  }else{
    digitalWrite(launch, HIGH);
  }
}



void leBtnMode() {
  if (digitalRead(commandBtns[0]) == LOW && digitalRead(commandBtns[1]) == LOW) {
    
    if (TimeOld == 0) {
      TimeOld = Time;
    } else {
      if (Time - TimeOld > 1000) {
        if (gameMode == 0) {
          gameMode = 1;
        } else {
          gameMode = 0;
        }
        controlaEstados[0] = 0;
        controlaEstados[1] = 0;
        controlaEstados[2] = 0;
        controlaEstados[3] = 0;
        animStart();
        TimeOld = 0;
      }
    }
  } else {
    TimeOld = 0;
  }
}

void lePin() {
  for (int i = 0; i < 8; i++) {
    if (digitalRead(btns[i]) == LOW) {
      btnHit(i);
    } else {
    }
  }
}

void btnHit(int btn) {
  if (btn == 0) {
    controlaEstados[0] = controlaEstados[0] + 1;
  }
  if (btn >= 1 && btn <= 3) {
    controlaEstados[1] = controlaEstados[1] + 1;
  }
  if (btn >= 4 && btn <= 6) {
    controlaEstados[2] = controlaEstados[2] + 1;
  }
  if (btn == 7) {
    controlaEstados[3] = controlaEstados[3] + 1;
  }
  atualizaLeds();
}

void atualizaLeds() {
  if (controlaEstados[0] == 1) {
    led(1, true, false, false);
  }
  if (controlaEstados[0] == 2) {
    led(1, false, true, false);
  }
  if (controlaEstados[0] == 3) {
    led(1, false, false, true);
  }
  if (controlaEstados[0] == 4) {
    led(1, true, true, true);
  }

  if (controlaEstados[1] == 1) {
    led(2, true, false, false);
    led(3, true, false, false);
    led(4, true, false, false);
  }
  if (controlaEstados[1] == 2) {
    led(2, false, true, false);
    led(3, false, true, false);
    led(4, false, true, false);
  }
  if (controlaEstados[1] == 3) {
    led(2, false, false, true);
    led(3, false, false, true);
    led(4, false, false, true);
  }
  if (controlaEstados[1] == 4) {
    led(2, true, true, true);
    led(3, true, true, true);
    led(4, true, true, true);
  }

  if (controlaEstados[2] == 1) {
    led(5, true, false, false);
    led(6, true, false, false);
    led(7, true, false, false);
  }
  if (controlaEstados[2] == 2) {
    led(5, false, true, false);
    led(6, false, true, false);
    led(7, false, true, false);
  }
  if (controlaEstados[2] == 3) {
    led(5, false, false, true);
    led(6, false, false, true);
    led(7, false, false, true);
  }
  if (controlaEstados[2] == 4) {
    led(5, true, true, true);
    led(6, true, true, true);
    led(7, true, true, true);
  }

  if (controlaEstados[3] == 1) {
    led(8, true, false, false);
  }
  if (controlaEstados[3] == 2) {
    led(8, false, true, false);
  }
  if (controlaEstados[3] == 3) {
    led(8, false, false, true);
  }
  if (controlaEstados[3] == 4) {
    led(8, true, true, true);
  }

  delay(300);
}

void animStart() {

  for (int i = 0; i < 5; i++) {
    leBtnManualMode();
    int v1 = random(100);
    int v2 = random(100);
    int v3 = random(100);
    boolean b1, b2, b3 = false;
    if (v1 > 50) {
      b1 = true;
    } else {
      b1 = false;
    }
    if (v2 > 50) {
      b2 = true;
    } else {
      b2 = false;
    }
    if (v3 > 50) {
      b3 = true;
    } else {
      b3 = false;
    }


    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 2; j++) {
        int ledNum = wave[i][j];
        led(ledNum, true, false, false);
      }
      delay(60);
    }


    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 2; j++) {
        int ledNum = wave[i][j];
        led(ledNum, false, false, false);
      }
      delay(60);
    }
  }
}

void animStart2() {


  for (int i = 1; i < 9; i++) {
    leBtnManualMode();
    int v1 = random(100);
    int v2 = random(100);
    int v3 = random(100);
    boolean b1, b2, b3 = false;
    if (v1 > 50) {
      b1 = true;
    } else {
      b1 = false;
    }
    if (v2 > 50) {
      b2 = true;
    } else {
      b2 = false;
    }
    if (v3 > 50) {
      b3 = true;
    } else {
      b3 = false;
    }

    led(i, b1, b2, b3);

  }
  delay(50);

  for (int i = 1; i < 9; i++) {
    led(i, false, false, false);
  }

  delay(50);
}


void led(int nLed, boolean red, boolean green, boolean blue) {
  nLed = nLed - 1;
  if (nLed >= 1 && nLed <= 6) {
    digitalWrite(leds[nLed][0], !red);
    digitalWrite(leds[nLed][1], !green);
    digitalWrite(leds[nLed][2], !blue);
  } else {
    digitalWrite(leds[nLed][0], red);
    digitalWrite(leds[nLed][1], green);
    digitalWrite(leds[nLed][2], blue);
  }
}
