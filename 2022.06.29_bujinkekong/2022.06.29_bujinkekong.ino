const int dirPin   = 2;    //方向引脚   顺逆  接Arduino
const int stepPin  = 3;   //步进引脚   脉冲
const int sleepPin = 4;
const int resetPin = 5;
const int ms3Pin   = 6;
const int ms2Pin   = 7;
const int ms1Pin   = 8;
const int enPin    = 9; 


//电机每圈步数
const int STEPS_PER_REV = 200;

char cmd;              //用户指令字符
int data;              //用户指令数据
int stepMode = 1;      //步进方式
int motorSpeed = 2000; //电机转速 

void setup() {
  // put your setup code here, to run once:
  pinMode(stepPin,OUTPUT);   //A4988
  pinMode(dirPin,OUTPUT);
  pinMode(sleepPin,OUTPUT);   //A4988
  pinMode(resetPin,OUTPUT);
  pinMode(ms3Pin,OUTPUT);   //A4988
  pinMode(ms2Pin,OUTPUT);
  pinMode(ms1Pin,OUTPUT);   //A4988
  pinMode(enPin,OUTPUT);

  //初始化电机步进模式为全步速
  digitalWrite(sleepPin,HIGH);
  digitalWrite(resetPin,HIGH);
  digitalWrite(enPin,LOW);
  
  //初始化电机步进模式为全步进
  digitalWrite(ms1Pin,LOW);
  digitalWrite(ms2Pin,LOW);
  digitalWrite(ms3Pin,LOW);

  Serial.begin(9600);
  Serial.println("++++++++++++++++");
  Serial.println("+Taichi-Maker A4988c Steper Demo");
  Serial.println("+  www.taichi-maker.com"); 
  Serial.println("++++++++++++++++");
  Serial.println("");
  Serial.println("Please input motor command"); 
  
}

void loop() {
  // put your main code here, to run repeatedly:
   if (Serial.available())  //检查串口缓存是否有数据等待传输
   {                        //获取电机指令中电机编号信息
    cmd = Serial.read();
    Serial.print("cmd = ");
    Serial.print(cmd);
    Serial.print("  , " );

    data = Serial.parseInt();
    Serial.print("data = ");
    Serial.print(data);
    Serial.println("");

    runUsrCmd();
    }
}

void runUsrCmd()
 {
  switch(cmd)
    {
      case 'x':               //设置步进电机旋转（顺/逆）
        Serial.print("Set Rotation To" );
         if (data == 0)
           {
            digitalWrite(dirPin,0);
            Serial.println("Clockwise.");
            } else 
               {
                  digitalWrite(dirPin,1);
                  Serial.println("Counter Clockwise.");
                }
                break;

        case 'g':               //设置步进电机旋转（顺/逆）
        Serial.print("Set Rotation To ");
         if (data == 0)
           {
            digitalWrite(dirPin,0);
            Serial.println("Clockwise.");
            } else 
               {
                  digitalWrite(dirPin,1);
                  Serial.println("Counter Clockwise.");
                }
                break;

         case 'm':               //设置步进电机旋转（顺/逆）
        Serial.print("Set Rotation To" );
         if (data == 0)
           {
            digitalWrite(dirPin,0);
            Serial.println("Clockwise.");
            } else 
               {
                  digitalWrite(dirPin,1);
                  Serial.println("Counter Clockwise.");
                }
                break;

        case 'b':               //设置步进模式
        if(data == 1 || data == 2 || data == 4 || data ==8 ||data == 16)
        {
        Serial.print("Set Rotation To" );
        setStepMode(data);     //后  调用程序
        } else 
          {
            Serial.println("Wrong Step Mode Cmd!");
             }
                break;

                case 'z':
                Serial.print("Motor Go ");
                Serial.print(data);
                Serial.println("Steps.");
                runStepper(motorSpeed,data); //后 调用
                break;

                default:
                Serial.println("Unknown Command");
      }
  }

  
    void runStepper (int rotationSpeed,int stepNum)
    {
       for (int x = 0;x < stepNum;x++)
          {
            digitalWrite(stepPin,HIGH);
            delayMicroseconds(rotationSpeed);
            digitalWrite(stepPin,LOW);
            delayMicroseconds(rotationSpeed);
            }
      }


    //设置步进模式
     void setStepMode(int modeNum)
      {
        switch(modeNum)
         {
          case 1:  //全步进
          digitalWrite(ms1Pin,LOW);
          digitalWrite(ms2Pin,LOW);
          digitalWrite(ms3Pin,LOW);
          Serial.println("Stepping MOde: Full");
          break;

           case 2:  //1/2步进
          digitalWrite(ms1Pin,HIGH);
          digitalWrite(ms2Pin,LOW);
          digitalWrite(ms3Pin,LOW);
          Serial.println("Stepping MOde: 1/2");
          break;

          case 4:  //1/4步进
          digitalWrite(ms1Pin,LOW);
          digitalWrite(ms2Pin,HIGH);
          digitalWrite(ms3Pin,LOW);
          Serial.println("Stepping MOde: 1/4");
          break;

          case 8:  //1/8步进
          digitalWrite(ms1Pin,HIGH);
          digitalWrite(ms2Pin,HIGH);
          digitalWrite(ms3Pin,LOW);
          Serial.println("Stepping MOde: 1/8");
          break;
          
          case 16:  //1/16步进
          digitalWrite(ms1Pin,HIGH);
          digitalWrite(ms2Pin,HIGH);
          digitalWrite(ms3Pin,HIGH);
          Serial.println("Stepping MOde: 1/16");
          break;
          }
        }
