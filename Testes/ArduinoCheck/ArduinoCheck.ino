

/*  Coloque neste define qual o tipo de arduino que está sendo testado. 
Opções atuais: 
    - MEGA: Arduino mega

*/
#define MEGA


/*  Coloque neste define o tipo de teste que está sendo realizado. 
Opções atuais: 
    - IN: Todos os pinos são setados como input (menos o pino 1*) com pullup. O monitor serial mostrará quais pinos digitais ficam com valor LOW, e quais portas analógicas possuem um valor abaixo de 1000.
          Para testar: conecte um jumper com uma ponta em um GND do arduino, e a outra ponta em cada uma das outras portas digitais, e cheque, pelo monitor serial, se aquela porta aparece na tela;
                       Para as portas analógicas, teste cada uma delas tanto com o pino 3.3V quanto com o GND do arduino, e cheque no monitor serial se a porta selecionada aparece, e se os valores lidos são condizentes

        *: o pino 1 é utilizado pela porta serial, e esta é utilizada neste teste. Para testar esse pino específico como entrada digital, realizar um teste separado
    
    - OUT: Todos os pinos digitais são setados como output, e ficam alternando entre HIGH e LOW a cada segundo.
          Para testar: Com um multímetro ou um osciloscópio, cheque qual o valor lido em cada uma das portas. Espera-se que as leituras alternem-se entre aproximadamente 0V e 5V.
          
    
    - PWM: Todos os pinos digitais são setados como output, e os pinos de pwm enviam sinais pwm com duty cicle alternando entre 50/255, 125/255 e 200/255 a cada segundo.
          Para testar: Com um osciloscópio, cheque cada uma das entradas pwm e verifique se a onda que aparece está de acordo com o esperado.

    - INTERRUPT: Deixa os pinos de interrupt da placa como interrupt, detectando borda de descida, e um pullup na entrada.
          Para testar: Conecte uma ponta de um jumper no ground, e a outra ponta nos pinos de interrupt. No monitor serial, será indicado caso um sinal de interrupt fora detectado

*/
#define PWM





//Setando variável que determinará se os pinos digitais serão de input com pull-up ou de output
#if defined(IN) || defined(INTERRUPT)
  int XPUT = INPUT_PULLUP;
#endif

#if defined(OUT) || defined(PWM)
  int XPUT = OUTPUT;
#endif


//Flag utilizada pela função de interrupt, para indicar quando uma das portas foi utilizada
bool flagInt = false;

//Função de interrupt
void interrupt(){
  flagInt = true;
}


void setup() {
  //Coisas serão printadas, pra ver qq acontece
  Serial.begin(9600);

  #ifdef MEGA
    pinMode(0, XPUT);
    pinMode(1, XPUT);    //Pino 1 é usado para comunicação serial, e aqui a gente testa as coisas pela porta serial. Testar esse pino de um jeito diferente
    
    //Pinos digitais PWM
    pinMode(2, XPUT);
    pinMode(3, XPUT);
    pinMode(4, XPUT);
    pinMode(5, XPUT);
    pinMode(6, XPUT);
    pinMode(7, XPUT);
    pinMode(8, XPUT);
    pinMode(9, XPUT);
    pinMode(10, XPUT);
    pinMode(11, XPUT);
    pinMode(12, XPUT);
    pinMode(13, XPUT);

    //pinos digitais especiais
    pinMode(14, XPUT);
    pinMode(15, XPUT);
    pinMode(16, XPUT);
    pinMode(17, XPUT);
    pinMode(18, XPUT);
    pinMode(19, XPUT);
    
    //Outros pinos digitais
    pinMode(20, XPUT);
    pinMode(21, XPUT);
    pinMode(22, XPUT);
    pinMode(23, XPUT);
    pinMode(24, XPUT);
    pinMode(25, XPUT);
    pinMode(26, XPUT);
    pinMode(27, XPUT);
    pinMode(28, XPUT);
    pinMode(29, XPUT);
    
    pinMode(30, XPUT);
    pinMode(31, XPUT);
    pinMode(32, XPUT);
    pinMode(33, XPUT);
    pinMode(34, XPUT);
    pinMode(35, XPUT);
    pinMode(36, XPUT);
    pinMode(37, XPUT);
    pinMode(38, XPUT);
    pinMode(39, XPUT);
    
    pinMode(40, XPUT);
    pinMode(41, XPUT);
    pinMode(42, XPUT);
    pinMode(43, XPUT);
    pinMode(44, XPUT);
    pinMode(45, XPUT);
    pinMode(46, XPUT);
    pinMode(47, XPUT);
    pinMode(48, XPUT);
    pinMode(49, XPUT);
    
    pinMode(50, XPUT);
    pinMode(51, XPUT);
    pinMode(52, XPUT);
    pinMode(53, XPUT);


    //Pinos analógicos
    pinMode(A0, INPUT_PULLUP);
    pinMode(A1, INPUT_PULLUP);
    pinMode(A2, INPUT_PULLUP);
    pinMode(A3, INPUT_PULLUP);
    pinMode(A4, INPUT_PULLUP);
    pinMode(A5, INPUT_PULLUP);
    pinMode(A6, INPUT_PULLUP);
    pinMode(A7, INPUT_PULLUP);
    pinMode(A8, INPUT_PULLUP);
    pinMode(A9, INPUT_PULLUP);
    
    pinMode(A10, INPUT_PULLUP);
    pinMode(A11, INPUT_PULLUP);
    pinMode(A12, INPUT_PULLUP);
    pinMode(A13, INPUT_PULLUP);
    pinMode(A14, INPUT_PULLUP);
    pinMode(A15, INPUT_PULLUP);

    #ifdef INTERRUPT
      //Faz com que os pinos de interrupt do arduino sejam tratados como tal, sempre que houver uma borda de descida detectada, chamando todos a função interrupt()
      attachInterrupt(digitalPinToInterrupt(2), interrupt, FALLING);
      attachInterrupt(digitalPinToInterrupt(3), interrupt, FALLING);
      attachInterrupt(digitalPinToInterrupt(18), interrupt, FALLING);
      attachInterrupt(digitalPinToInterrupt(19), interrupt, FALLING);
      attachInterrupt(digitalPinToInterrupt(20), interrupt, FALLING);
      attachInterrupt(digitalPinToInterrupt(21), interrupt, FALLING);
    #endif
    
  #endif

}

void loop() {

  
  #ifdef MEGA
    /*********************** ROTINA PARA TESTE DE ENTRADA DOS PINOS **************************/
    #ifdef IN
    
      //Percorre todas as portas digitais
      Serial.print("LOW: ");
      for(int i=0; i<=53; i++){
        
        //Printa na tela as leituras que forem diferentes de HIGH
        if((digitalRead(i) == LOW) &&(i != 1)){   //Tira leitura da porta 1, essa é usada pelo serial print
          Serial.print(i);
          Serial.print(", ");
        }
        
      }
  
      //Percorre todas as portas analogicas
      for(int i=A0; i<=A15; i++){
        
        //Printa na tela se tiver recebido alguma leitura acima de 0
        int leitura = analogRead(i);
        if(leitura < 1000){
          Serial.print("A");
          Serial.print(i-A0);
          Serial.print(": ");
          Serial.print(leitura);
          Serial.print("; ");
        }
        
      }
  
      //Fim de linha pro fim de todos os prints
      Serial.println();
  
      delay(300);
    #endif
    /************************************************************************************/
  
  
  
  
  
    /*********************** ROTINA PARA TESTE DE SAIDA DOS PINOS **************************/
    #ifdef OUT
  
      //Faz todos os pinos digitais mandarem HIGH
      for(int i=2; i<=53; i++){
        digitalWrite(i, HIGH);
      }
  
      //Espera 1 segundo antes de trocar o estado do pino
      delay(1000);
  
      //Faz todos os pinos digitais mandarem LOW
      for(int i=0; i<=53; i++){
        digitalWrite(i, LOW);
      }
  
      
      //Espera 1 segundo antes de trocar o estado do pino
      delay(1000);
      
    #endif
  
    /******************************************************************************************/
    
  
  /*********************** ROTINA PARA TESTE DOS PINOS PWM **************************/
    #ifdef PWM
  
      //Faz todos os pinos pwm mandarem sinal com duty cicle de 50/255
      for(int i=0; i<=13; i++){
        analogWrite(i, 50);
      }
  
      //Espera 1 segundo antes de alterar o duty cicle
      delay(1000);
  
      //Faz todos os pinos pwm mandarem sinal com duty cicle de 125/255
      for(int i=0; i<=13; i++){
        analogWrite(i, 125);
      }
  
      //Espera 1 segundo antes de alterar o duty cicle
      delay(1000);
  
      //Faz todos os pinos pwm mandarem sinal com duty cicle de 200/255
      for(int i=0; i<=13; i++){
        analogWrite(i, 200);
      }
  
      //Espera 1 segundo antes de alterar o duty cicle
      delay(1000);
      
    #endif
  
    /******************************************************************************************/


  /*********************** ROTINA PARA TESTE DOS PINOS INTERRUPT **************************/
    #ifdef INTERRUPT
      if(flagInt){
        Serial.println("Interrupt detectado.");
        flagInt = false;
      }
      
    #endif
  
    /******************************************************************************************/

  #endif

}
