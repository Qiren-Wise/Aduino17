const int dirPin = 2;    //方向引脚   顺逆  接Arduino
const int stepPin = 3;   //步进引脚   脉冲


//电机每圈步数
const int STEPS_PER_REV = 200;

void setup() {
  // put your setup code here, to run once:
  pinMode(stepPin,OUTPUT);   //A4988
  pinMode(dirPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

 digitalWrite(dirPin,LOW);//设置电机顺时针旋转

 //电机慢速旋转
 for (int x = 0;x < STEPS_PER_REV;x++)
   {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(2000);    //数值越小，速度越快
      digitalWrite(stepPin,LOW);
      delayMicroseconds(2000);
    }

    delay(1000);

    digitalWrite(dirPin,HIGH); //电机逆旋转

    for (int x = 0;x < (STEPS_PER_REV*2);x++)
    {
       digitalWrite(stepPin,HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(1000);
      }

      delay(1000);
    }
