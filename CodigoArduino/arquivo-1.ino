#include <IRremote.h>

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
  
  receptor.enableIRIn(); //Inicia o receptor
  
  Serial.begin(9600);
}
 
void loop()
{
  estadoBotao = digitalRead(portaBotao);
  if(Serial.available() > 0){
  recebeJava = Serial.read();
  Serial.print(recebeJava);
  }
  if(recebeJava == 'L'){
      digitalWrite(porta_led, HIGH);
  }
  if(recebeJava == 'D'){
      digitalWrite(porta_led, LOW);
  }
  intensidadeLed = map(recebeJava, 0, 1023, 0, 255); 
  analogWrite(porta_led,intensidadeLed);
  
  
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
