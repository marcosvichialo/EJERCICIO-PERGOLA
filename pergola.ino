/* EL EJERCICIO CONSISTE EN CONTROLAR EL MOTOR DE UNA PERGOLA
CON UN PULSADOR, DOS FINALES DE CARRERA, UN PONTE H Y UN 
SENSOR LDR QUE CONTROLA LA VELOCIDAD DE DESPLIEGE Y CIERRE
SEGÚN LA LUZ QUE DETECTA EL LA LDR */
#define finalMotorAbrir 3
#define finalMotorCerrar 4
#define salidaldr 11
#define entradaldr A0
#define pulsador 2
#define motorAbrir 10
#define motorCerrar 9



bool estadoPulsador = 0;
bool ultimoMotor = 0;
bool estadoMotorAbrir = 0;
bool estadoMotorCerrar = 0;
int velocidade = 0;
int lecturaldr = 0;

void setup() {
  pinMode(motorAbrir, OUTPUT);
  pinMode(motorCerrar, OUTPUT);
  pinMode(pulsador, INPUT);
  pinMode(finalMotorAbrir, INPUT);
  pinMode(finalMotorCerrar, INPUT);
  Serial.begin(9600);
}

void loop() {
  lecturaldr = analogRead(entradaldr);
  velocidade = map(lecturaldr, 54, 974, 0, 5);
  Serial.println(velocidade);
  switch (velocidade){
    case 0: analogWrite(salidaldr, 255*0.05);break;
    case 1: analogWrite(salidaldr, 255*0.2);break;
    case 2: analogWrite(salidaldr, 255*0.4);break;
    case 3: analogWrite(salidaldr, 255*0.6);break;
    case 4: analogWrite(salidaldr, 255*0.8);break;
    case 5: analogWrite(salidaldr, 255);break;
  }
  if(digitalRead(pulsador)) {
    estadoPulsador = !estadoPulsador;
    estadoMotorAbrir = 0;
    estadoMotorCerrar = 0;
    while(digitalRead(pulsador)) {
      delay(20);
    }
    if(estadoPulsador == !0){
      ultimoMotor = !ultimoMotor;
    }
  }  
  if(estadoPulsador == 0 && ultimoMotor == !0) {
    digitalWrite(motorAbrir, 1);
    digitalWrite(motorCerrar, 0);
    estadoMotorAbrir = 1;
  }
  else if(estadoPulsador == 0 && ultimoMotor == 0){
    digitalWrite(motorAbrir, 0);
    digitalWrite(motorCerrar, 1);
    estadoMotorCerrar = 1;
  }else{
    digitalWrite(motorAbrir, 0);
    digitalWrite(motorCerrar, 0);
    estadoMotorAbrir = 0;
    estadoMotorCerrar = 0;
  }
  if(digitalRead(finalMotorAbrir)) {
    if(estadoMotorAbrir == 1){
      digitalWrite(motorAbrir, 0);
      estadoPulsador = !estadoPulsador;
      estadoMotorAbrir = 0;
      ultimoMotor = !ultimoMotor;
    }
    while(digitalRead(finalMotorAbrir)) {
      delay(20);
    }
  }
  if(digitalRead(finalMotorCerrar)) {
    if(estadoMotorCerrar == 1){
      digitalWrite(motorCerrar, 0);
      estadoPulsador = !estadoPulsador;
      estadoMotorCerrar = 0;
      ultimoMotor = !ultimoMotor;
    }
    while(digitalRead(finalMotorCerrar)) {
      delay(20);
    }
  }
}
