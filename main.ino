#define SPEAKER 8 //スピーカーの出力ピン番号
#define r 1.7320 / 3  //√3/3
#define Q -1.7320 / 3  //-√3/ //Qではないぞ(元はm)
int Sd = 0; //流れている音の周波数
int rpm;
int sec = 0;//開始からの秒数
unsigned char tv[1500];//1秒間の計測値
int count = 0;
int val1; //First 読み取りの値
int val2; //Second　読み取りの値


void setup() {
  Serial.begin(9600) ;      // ArduinoIDEとシリアル通信の準備を行う
  pinMode(13, OUTPUT);
}

void loop() {

  int ans;
  ans = analogRead(0) ;              // アナログ０番ピンからセンサー値を読込む
  tv[count]  = map(ans, 0, 1023, 0, 255) ; // センサー値を8bitに変換する

  if (count == 999) { // countが999なら1秒経過したので計測結果をrpmで表示
    int hit = 0;
    int rpm = 0;

    // 1秒間の回転数を平均して算出する
    // 1秒間に何回刃先を検出したかをカウントしてrpmを算出
    // 2枚刃のエンドミルを前提として計算

    for (int i = 1; i < 1000; i++) { //電圧アップしたら刃先検出
      if ((tv[i] - tv[i - 1]) > 2) {
        hit++;


      }
    }

    rpm = hit * 30;

    Serial.print("RPM: ");
    Serial.print(rpm);             // 値をパソコン(ＩＤＥ)に送る
    Serial.print(", Time(second): ");
    Serial.println(sec);

    int n = 300;
    int m = 100;

      
      if (rpm < 200) {
        /*
        for (int i = 4 * m; i < n + 4 * m; i--) {
          digitalWrite(13, LOW);
          tone(SPEAKER, i) ; // ド
          delay(15);
          */
          Serial.println("減速");
        } else if (300 < rpm < 350) {
      /*
      for (int i = 50; i <= n; i++) {
        digitalWrite(13, LOW);
        tone(SPEAKER, i) ; // ド
        delay(15);
        digitalWrite(13, HIGH);
      }
      for (int i = m; i <= n + m; i++) {
        digitalWrite(13, LOW);
        tone(SPEAKER, i) ; // ド
        delay(15);
        digitalWrite(13, HIGH);
      }
      for (int i = 2 * m; i <= n + 2 * m; i++) {
        digitalWrite(13, LOW);
        tone(SPEAKER, i) ; // ド
        delay(15);
        digitalWrite(13, HIGH);
      }
      for (int i = 3 * m; i <= n + 3 * m; i++) {
        digitalWrite(13, LOW);
        tone(SPEAKER, i) ; // ド
        delay(15);
        digitalWrite(13, HIGH);
      }
      for (int i = 4 * m; i <= n + 4 * m; i++) {
        digitalWrite(13, LOW);
        tone(SPEAKER, i) ; // ド
        delay(15);
        digitalWrite(13, HIGH);

      }*/
      Serial.println("加速");

      

     
  }else if (400 < rpm) {
      /*
    
        tone(SPEAKER, n + 4 * m) ; // ド
        delay(15);*/
        
        Serial.println("平走");
    }


      

      sec++;
      count = 0; //カウントを初期化


    } else {
      count ++;
    }
    delayMicroseconds(997) ;   // 1ミリ秒毎に繰り返す

  
  }

  /*
    int val1 = rpm; //first読み取り
    delay(500);
    int  val2 = rpm; //second読み取り

    int o = val2 - val1; //output = second - first
    Serial.println(o);

    //第1象限の条件分岐
    if (r <= o) {
    digitalWrite(1, HIGH);
    for (int Sd = Q; Sd <= P; Sd++) {
      digitalWrite(13, LOW);
      tone(SPEAKER, Sd) ;

      int P = P + 100;
      int Q = Q + 100;
      delay (100);
    }
    } else if (m <= o < r) { //第2象限の条件分岐
    digitalWrite(2, HIGH);
    tone(SPEAKER, Sd) ;
    delay (100);        //第1,3象限に合わせる必要がある(鳴らす時間)
    } else if (o < m) { //第3象限の条件分岐
    digitalWrite(3, HIGH);
    for (int Sd = P; Sd <= Q; Sd--) {
      tone(SPEAKER, Sd) ;

      int Q = Q - 200;
      int P = P - 200;
      delay (100);
    }
    }
    digitalWrite(1, LOW);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    }
  */
  //}
