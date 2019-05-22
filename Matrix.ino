/*
 * Matrix
 * 点阵屏显示驱动
 */
 
int leds[8] = {6, 11, 5, 9, 14, 4, 15, 2}; //点阵屏正极引脚
int gnds[8] = {10, 16, 17, 7, 3, 8, 12, 13}; //点阵屏负极引脚
 
void setup() {
  for (int i = 0; i < 8; i++)
  {
    pinMode(leds[i], OUTPUT);
    pinMode(gnds[i], OUTPUT);
    digitalWrite(gnds[i], HIGH); //负极引脚拉高，熄灭所有LED
  }
}


unsigned char ccharacer[8][8] =      // C  
{  
  0,0,1,1,1,1,0,0,  
  0,1,0,0,0,0,1,0,  
  1,0,0,0,0,0,0,1,  
  1,0,0,0,0,0,0,0,  
  1,0,0,0,0,0,0,0, 
  1,0,0,0,0,0,0,1, 
  0,1,0,0,0,0,1,0,  
  0,0,1,1,1,1,0,0,  
};
unsigned char mcharacer[8][8] =      // M
{  
  1,0,0,0,0,0,0,1,  
  1,1,0,0,0,0,1,1,  
  1,0,1,0,0,1,0,1,  
  1,0,0,1,1,0,0,1,  
  1,0,0,0,0,0,0,1, 
  1,0,0,0,0,0,0,1, 
  1,0,0,0,0,0,0,1,  
  1,0,0,0,0,0,0,1,  
};

unsigned char fivecharacer[8][8] =      // 5
{  
  1,1,1,1,1,1,1,1,  
  1,0,0,0,0,0,0,0,  
  1,0,0,0,0,0,0,0,  
  1,1,1,1,1,1,1,1,  
  0,0,0,0,0,0,0,1, 
  0,0,0,0,0,0,0,1, 
  0,0,0,0,0,0,0,1,  
  1,1,1,1,1,1,1,1,  
};
unsigned char twocharacer[8][8] =      // 2
{  1,1,1,1,1,1,1,1,  
  0,0,0,0,0,0,0,1,  
  0,0,0,0,0,0,0,1,  
  1,1,1,1,1,1,1,1,  
  1,0,0,0,0,0,0,0, 
  1,0,0,0,0,0,0,0, 
  1,0,0,0,0,0,0,0,  
  1,1,1,1,1,1,1,1,  
};

unsigned char zerocharacer[8][8] =      // 0
{  1,1,1,1,1,1,1,1,  
  1,1,0,0,0,0,0,1,  
  1,0,1,0,0,0,0,1,  
  1,0,0,1,0,0,0,1,  
  1,0,0,0,1,0,0,1, 
  1,0,0,0,0,1,0,1, 
  1,0,0,0,0,0,1,1, 
  1,1,1,1,1,1,1,1, 
};

unsigned char biglove[8][8] =       //大“心型”的数据
{
  0,0,0,0,0,0,0,0,
  0,1,1,0,0,1,1,0,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,0,
  0,0,1,1,1,1,0,0,
  0,0,0,1,1,0,0,0,
};

unsigned char smalllove[8][8] =      //小“心型”的数据  
{  
  0,0,0,0,0,0,0,0,  
  0,0,0,0,0,0,0,0,  
  0,0,1,0,0,1,0,0,  
  0,1,1,1,1,1,1,0,  
  0,1,1,1,1,1,1,0,  
  0,0,1,1,1,1,0,0,  
  0,0,0,1,1,0,0,0,  
  0,0,0,0,0,0,0,0,  
};  

void Display(unsigned char dat[8][8])   //显示函数
{
  for(int c = 0; c<8; c++)
  {
    digitalWrite(gnds[c], LOW);//选通第c列
    
    for(int r = 0; r<8; r++)
    {
      digitalWrite(leds[r], dat[r][c]);
    }
    delay(1);
    ledclean();
  }
}

void ledopen()
{
  
  for (int i = 0; i < 8; i++)//将点阵屏正极拉高，负极拉低，开启显示
  {
    digitalWrite(leds[i], HIGH);
    digitalWrite(gnds[i], LOW);
  }
}
 
void ledclean()
{
  for (int i = 0; i < 8; i++)//将点阵屏正极ladies，负极拉高，关断显示
  {
    digitalWrite(leds[i], LOW); 
    digitalWrite(gnds[i], HIGH);
  }
}
 
//逐列扫描
void ledCol()
{
  for (int i = 0 ; i < 8; i++)
  {
    digitalWrite(gnds[i], LOW);
    for (int j = 0; j < 8; j++)
    {
      digitalWrite(leds[j], HIGH);
    }
    delay(80);
    ledclean();
  }
}
 
//逐行扫描
void ledRow()
{
  for (int i = 0 ; i < 8; i++)
  {
    digitalWrite(leds[i], HIGH);
    for (int j = 0; j < 8; j++)
    {
      digitalWrite(gnds[j], LOW);
    }
    delay(80);
    digitalWrite(leds[i], LOW);
    ledclean();
  }
}
 
void loop() {
  // TEST
  ledCol();   //列扫描
  ledRow(); //行扫描
  ledopen();
  delay(800);
  ledclean(); //全部关闭
  delay(100);
  for(int i = 0 ; i < 50 ; i++)         //C 
  {     
    Display(ccharacer);
  }
  for(int i = 0 ; i < 50 ; i++)         //M  
  {     
    Display(mcharacer);
  }
  for(int i = 0 ; i < 50 ; i++)         //5  
  {     
    Display(fivecharacer);
  }
  for(int i = 0 ; i < 50 ; i++)         //2  
  {     
    Display(twocharacer);
  }
  for(int i = 0 ; i < 50 ; i++)         //0  
  {     
    Display(zerocharacer);
  }
  for(int i = 0 ; i < 30 ; i++)         //循环显示50次  
  {     
    Display(biglove);
  }
  for(int i = 0 ; i < 30 ; i++  )         //循环显示50次  
  {     
    Display(smalllove);                 //显示小“心形”  
  }
  for(int i = 0 ; i < 30 ; i++)         //循环显示50次  
  {     
    Display(biglove);
  }
  for(int i = 0 ; i < 30 ; i++  )         //循环显示50次  
  {     
    Display(smalllove);                 //显示小“心形”  
  }
  ledclean(); //全部关闭
}
