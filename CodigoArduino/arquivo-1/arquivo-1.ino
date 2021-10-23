#include <IRremote.h>

//Variaveis medidor de consumo
int portaSensor = A0;
float recebidoSensor = 0;
float valorSensorAuxiliar = 0;
float corrente = 0;
float voltsUnidade = 0.004887586;
float potencia = 0;

float sensibilidade = 0.066;//De acordo com o datasheet do sensor
int tensao = 220;


//Variavis cotrole luzes
int porta_led = 9;
int porta_led2 = 4;

//Armazena o estado do rele - 0 (LOW) ou 1 (HIGH)
int estadorele1 = 1;
int portaBotao = 3;
int estadoBotao = 0;
int const receptor_infra = 11;
float intensidadeLed = 0;
int recebeJava = 655;

IRrecv receptor(receptor_infra);

decode_results valorSaida;
  
void setup()
{
  //Define pinos para o rele como saida
  pinMode(porta_led, OUTPUT);
  pinMode(porta_led2, OUTPUT);
  pinMode(portaBotao, INPUT);
  pinMode(portaSensor, INPUT);
  
  receptor.enableIRIn(); //Inicia o receptor
  
  Serial.begin(9600);
}
 
void loop()
{
  for(int i = 0; i < 10000; i++){
    valorSensorAuxiliar = (analogRead(pinoSensor) -511.5);
    recebidoSensor += pow(valorSensorAuxiliar, 2);
    delay(1);
  }

  recebidoSensor = ((sqrt(recebidoSensor/1000)) * voltsUnidade);
  corrente = (recebidoSensor/sensibilidade);

  //RUIDOS, verificar de acordo com o sensor
  if(corrente <= 0.098){
    corrente = 0;
  }

  potencia = corrente * tensao;

  Serial.print("Corrente: " + corrente + "A");
  Serial.print("Potência: " + potencia + "Watts);

  delay(100);
  
  estadoBotao = digitalRead(portaBotao);
  char recebeJava = Serial.read();
  if(recebeJava == 'L'){
      digitalWrite(porta_led, HIGH);
  }
  if(recebeJava == 'D'){
      digitalWrite(porta_led, LOW);
  }
  if(recebeJava == 'B'){
    analogWrite(porta_led,25);
  }
  if(recebeJava == 'M'){
    analogWrite(porta_led,127);
  }
  if(recebeJava == 'A'){
    analogWrite(porta_led,255);
  }
  
  
  if (receptor.decode(&valorSaida)) {
   
    receptor.resume();
    Serial.println(valorSaida.value);
    if(valorSaida.value == 1077952703){
       Serial.println(valorSaida.value);
      digitalWrite(porta_led, HIGH);
      digitalWrite(porta_led2, LOW);
    }else if(valorSaida.value == 4294967295){
       Serial.println(valorSaida.value);
      digitalWrite(porta_led, LOW);
      digitalWrite(porta_led2, HIGH);
    }
  }
  
}
