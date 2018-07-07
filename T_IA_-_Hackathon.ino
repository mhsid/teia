// inclui biblioteca
#include <Tone.h>
Tone speakerpin;

// define nota e duração
int melody[] = {NOTE_F4};
int noteDurations[] = {50};

// definir dados
int analogValue0 = 0;
int analogValue1 = 1;

// definir os pinos do Arduino
#define VMPC  6  // vermelho para carros
#define APC  5  // amarelo para carros
#define VPC  4  // verde para carros
#define VPP  2  // verde para pedestres
#define VMPP  3  // vermelho para pedestres
#define SPK  12 // buzzer

// esta seção roda somente na inicialização
void setup() {
  speakerpin.begin(SPK);   // inicializa buzzer
  pinMode(VMPC, OUTPUT);    // definição de cada um dos pinos
  pinMode(APC, OUTPUT);
  pinMode(VPC, OUTPUT);
  pinMode(VPP, OUTPUT);
  pinMode(VMPP, OUTPUT);
  Serial.begin(9600);
}

// loop prinicpal do programa
void loop() {

  
  Serial.println("b"); // dado para comunicação com o sensor na pulsiera (vibra)
  delay(1000);
  
  digitalWrite(VMPC, HIGH);  // acendo o vermelho para carros, pedestres liberados
  digitalWrite(VMPP, LOW);   // apaga o vermelho pedestres
  digitalWrite(VPP, HIGH);  // acende o verde pedestres

  // aviso sonoro durante passagem de pedestres
  for (int z = 0; z < 40; z++) { // gera também a temporização de 10s
    speakerpin.play(NOTE_C6, 50);
    delay(125);
  }

  // acabou o tempo do pedestre passar, apaga verde e pisca vermelho por 3 segundos
  digitalWrite(VPP, LOW); // apaga verde pedestres
  for (int i = 0; i < 10; i++) { // pisca VMP
    speakerpin.play(NOTE_C6, 50); // gera aviso sonoro durante os últimos 5s de passagem, gera a temporização
    digitalWrite(VMPP, HIGH);
    delay(250);
    digitalWrite(VMPP, LOW);
    delay(250);
  }
  speakerpin.stop(); // finaliza o uso do Buzzer

  // parou de piscar, libera o tráfego de veículos
  digitalWrite(VMPP, HIGH); // acende a lâmpada vermelha de pedestre
  delay(3000);             // fica mais um tempo para completar o ciclo
  // pare dos carros e dar segurança aos pedestres
  digitalWrite(VMPC, LOW);  // apaga a lâmpada vermelha de tráfego
  Serial.println("a"); // dado para comunicação com o sensor na pulseira (não vibra)
  delay(1000);
  digitalWrite(VPC, HIGH); // acende a lâmpada verde de tráfego
  delay(30000);            // temporização do loop

  // terminou o tempo de tráfego dos carros,apaga o verde e ascende amarelo por 5 segundos
  digitalWrite(VPC, LOW);  // apaga lâmpada verde de tráfego
  digitalWrite(APC, HIGH); // acende lâmpada amarela de tráfego
  delay(3000);             // temporiza
  digitalWrite(APC, LOW);  // apaga lâmpada amarela de tráfego

  // acabou o tempo de atenção, vai parar o tráfego de veículos e liberar pedestres
  // retorna o loop inicial
}
// FIM DA COMPILAÇÃO
