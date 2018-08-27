/****** Controle do LED por temperatura ******/

int valor; //Variável em que será armazenado o valor de leitura do sensor

int pinoTemperatura = 0; //Variável que representa o pino analógico conectado ao sensor, no caso o pino 0

int alimentacao = 5; //Tensão em volts da alimentação

//Valores dos pinos dos LEDs 
const int vermelho = 5; 
const int amarelo = 6; 
const int azul = 9;

void setup() { //Parte de inicialização
  
  //Inicializa pino do sensor como entrada
  pinMode(INPUT, pinoTemperatura);

  //Inicializa pinos como saídas
  pinMode(azul, OUTPUT);
  pinMode(amarelo, OUTPUT); 
  pinMode(vermelho, OUTPUT);

  //Inicializa com LEDs apagados
  digitalWrite(azul,LOW);
  digitalWrite(amarelo,LOW);
  digitalWrite(vermelho,LOW); 

  //Inicializa comunicação serial
  Serial.begin(9600);
}

void loop() { //Parte que se repetirá indefinidamente

nikolas.yugi@gmail.com

  /*** Parte de leitura da temperatura no monitor serial ***/

  valor = analogRead(pinoTemperatura); //Leitura do sensor -> número de 0 a 1024

  float intermediario = (valor/1024.0)*alimentacao; // Regra de 3 para converter a leitura do sensor para tensão em mV
  
  intermediario = intermediario*1000; // Conversão de mV para V
  
  float celsius = intermediario/10; //Sensor: cada 10mV -> 1 grau Celsius
  
  /* Texto que será mostrado no monitor serial */
  Serial.print("TEMPERATURA = "); 
  Serial.print(celsius);
  Serial.print("*C");
  Serial.println();
  
  delay(1000); //Atraso de 1000ms para fazer nova leitura do sensor 

  /*** Parte que controla o LED ***/

  //Se temperatura menor que 25 graus
  if (celsius<25){
    //Azul
    digitalWrite(azul,HIGH);
    digitalWrite(amarelo,LOW);
    digitalWrite(vermelho,LOW);
  }

  //Se temperatura menor que 30 graus
  else if (celsius < 30){
    //Amarelo
    digitalWrite(azul,LOW);
    digitalWrite(amarelo,HIGH);
    digitalWrite(vermelho,LOW);
  }

  //Para temperaturas maiores ou iguais a 30 graus
  else{
    //Vermelho
    digitalWrite(azul,LOW);
    digitalWrite(amarelo,LOW);
    digitalWrite(vermelho,HIGH); 
  }

}
