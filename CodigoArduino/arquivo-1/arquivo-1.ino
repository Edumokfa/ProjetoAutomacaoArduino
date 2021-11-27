#include <IRremote.h>

//Variaveis medidor de consumo
int portaSensor = A0;
float voltsporUnidade = 0.004887586;
float potencia = 0;
int sensorValueAux = 0;
float valorSensor = 0;
float valorCorrente = 0;

float sensibilidade = 0.066;//De acordo com o datasheet do sensor
int tensao = 242;


//Variavis cotrole luzes
int porta_led = 9;
int porta_led2 = 4;
int portaRele = 8;

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
  pinMode(portaRele, OUTPUT);
  receptor.enableIRIn(); //Inicia o receptor
  //IrReceiver.begin(receptor_infra, ENABLE_LED_FEEDBACK);
  
  Serial.begin(9600);
}
 
void loop()
{
  
  estadoBotao = digitalRead(portaBotao);
  char recebeJava = Serial.read();
  if(recebeJava == 'L'){
     digitalWrite(portaRele,HIGH);
  }
  if(recebeJava == 'D'){
      digitalWrite(portaRele,LOW);
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
  if(recebeJava == 'S'){
    for(int i=5000; i>0; i--){
    /* Leitura do  sensor analogico A0  subtraindo o ajuste 
     *  pela metade da resolução (1023)vcc/2 */
    sensorValueAux = (analogRead(portaSensor) -511.5); 
    // Soma dos quadrados das leituras
    valorSensor += pow(sensorValueAux,2); 

  }

  // Calculo da média dos quadrados e conversão para Volts
  valorSensor = (sqrt(valorSensor/ 5000)) * voltsporUnidade; 
  // Calculo da corrente considerando a sensibilidade do sensor (185 mV por ampere) para o sensor de exemplo
  valorCorrente = (valorSensor/sensibilidade); 

  /*Tratamento para possivel ruido
  O ACS712 de 30 Amperes é projetado para fazer leituras
   de valores altos acima de 0.25 Amperes até 30,
   por isso é normal ocorrer ruidos de até 0.20A */
  if(valorCorrente <= 0.25){
    valorCorrente = 0; 
  }

  valorSensor = 0;

  potencia = valorCorrente * tensao;
  
  //Mostra o valor da corrente
  Serial.println((String)valorCorrente+":" +(String) potencia);
  //Delay para evitar overflow
  //  delay(1000);
  }
  
  if (receptor.decode(&valorSaida)) {
    receptor.resume();
    Serial.println(valorSaida.value);
    if(valorSaida.value == 1077952703){
       Serial.println(valorSaida.value);
    }else if(valorSaida.value == 4294967295){
       Serial.println(valorSaida.value);
    }
  }
//  delay(500);
}
