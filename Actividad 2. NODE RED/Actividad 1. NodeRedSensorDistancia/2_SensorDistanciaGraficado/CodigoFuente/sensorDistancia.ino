const int GND = 18;   // GND a ground de arduino
const int Echo = 3;   //Pin digital 3 para el Echo del sensor
const int Trigger = 2;   //Pin digital 2 para el Trigger del sensor
const int VCC = 21;   //VCC a voltaje de arduino
unsigned long nowTime=0,lastTime=0;
int contador=0;
int tmuestreo=300; //tiempo de muestreo en milisegundos
char arreglo[5]={0 , 0 , 0 , 0, 0};
char data;
int pwm=0, unidades, decenas, centenas;

void setup() {
  Serial.begin(115200);//iniciailzamos la comunicación
  pinMode(GND, OUTPUT); //pin como salida
  pinMode(VCC, OUTPUT); //pin como salida
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
  digitalWrite(GND, LOW);//Inicializamos el pin con 0V
  digitalWrite(VCC, HIGH);//Inicializamos el pin con 5V
  pinMode(13, OUTPUT);  
  
 
}

void loop()
{

  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros
  nowTime = millis();  //Se realiza una lecura del tiempo de ejecución

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Se realiza la lectura del sensor
  if ((nowTime-lastTime)>tmuestreo){
    lastTime=nowTime;
    digitalWrite(Trigger, HIGH);
    delayMicroseconds(10);          //Enviamos un pulso de 10us
    digitalWrite(Trigger, LOW);
  
    t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
    d = t*0.17;             //escalamos el tiempo a una distancia en mm
  
    Serial.print('D');
    Serial.print('=');      //Enviamos serialmente el valor de la distancia
    Serial.println(d);
  }
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Se modifica la salida PWM
  if (Serial.available()>0){
    data=Serial.read();
    if (data=='L'){unidades=0; decenas=0; centenas=0;}
    if (data < 47){pwm=centenas*100+decenas*10+unidades; analogWrite(13,pwm);Serial.println(pwm);}
    if ((data > 47)&&(data < 58)){centenas=decenas; decenas=unidades; unidades=data-'0';   }
  }
}
