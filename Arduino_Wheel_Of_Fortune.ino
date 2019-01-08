int goButton;
int stopButton;
int yellowLeft;
int yellowRight;
int blueLeft;
int blueRight;
int redRight;
int redLeft;
int currentLED;
int buzzer;

int numRight = 0;
int numWrong = 0;
int tries = 0;

int money = 0;
int potentialGain = 0;

int yellowRightValue = 75;
int yellowLeftValue = 0;
int blueRightValue = 200;
int blueLeftValue = 500;
int redRightValue = 50;
int redLeftValue = 25;

long old;
long old2;

long future = 0;
boolean go = false;
boolean cycle1 = false;

boolean repeat = false;
boolean printing = false;
boolean win = false;

boolean allowStop = true;

String food[] = 
{
 "chicken", "steak", "hamburger", "bread", "salmon", "cookies", "sandwich", 
 "cereal", "pancakes", "apple", "noodles", "pizza", "bagel", "potato", "chocolate", 
 "coconut", "pretzel", "oatmeal"
};

String cities[] = 
{
 "new york", "tokyo", "ibiza", "greece", "dubai", "london", "paris", 
 "egypt", "brazil", "chicago", "dallas", "singapore", "taipei", "beijing", "los angeles", 
 "seattle", "portland", "venice"
};

String foodWord; 
int len;

char guesses[20];
char checking[20];

int randomNum;
int topicNum;

boolean correct = false;
boolean incorrect = false;

double ab = 29.14;
double bb7 = 3729.31;
double eb7 = 2489.02;
double db6 = 1108.73;
double f7 = 2793.83;
double g7 = 3135.96;
double c7 = 2093.00;
double c3 = 130.81;
double c4 = 261.63;
double c5 = 523.25;
double c6 = 1046.50;
double fg4 = 369.99;
double d4 = 293.6;
double e4 = 329.63;
double f4 = 349.23;
double g4 = 392.00;
double a4 = 440.00;
double b4 = 493.88;
double db4 = 277.18;
double ab4 = 466.16;
double e5 = 659.25;
double eb4 = 311.13;
double db5 = 277.18;

String topic;

String pics[] = 
{
   "_____________\n|/    \n|     \n|    \n|    \n|", "_____________\n|/    |\n|     \n|    \n|    \n|", 
   "_____________\n|/    |\n|     O\n|    \n|    \n|", "_____________\n|/    |\n|     O\n|    /\n|    \n|",
   "_____________\n|/    |\n|     O\n|    /|\n|    \n|", "_____________\n|/    |\n|     O\n|    /|\\\n|    \n|",
   "_____________\n|/    |\n|     O\n|    /|\\\n|    /\n|", "_____________\n|/    |\n|     O\n|    /|\\\n|    / \\\n|"

};

void setup()
{
   Serial.begin(9600);
   randomSeed(analogRead(0));
   
   goButton = 13; 
   stopButton = 12;
   yellowLeft = 11;
   yellowRight = 10;
   blueLeft = 9;
   blueRight = 8;
   redRight = 7;
   redLeft = 6;
   buzzer = 5;
   
   pinMode(yellowLeft, OUTPUT);
   pinMode(yellowRight, OUTPUT);
   pinMode(blueLeft, OUTPUT);
   pinMode(redRight, OUTPUT);
   pinMode(redLeft, OUTPUT);
   pinMode(blueRight, OUTPUT);
   pinMode(goButton, INPUT);
   pinMode(stopButton, INPUT);
   
   Serial.println("Spin the wheel!");
   
   int r = random(0,19);
   
   foodWord = food[r];
   len = foodWord.length();
   guesses[len];

   for (int i = 0; i < len; i++)       
   {
       Serial.print("-");
       guesses[i] = '-';
   }
}
  
void loop()
{ 
  cycle();
  //allOn();
  char let = ' ';
  String input = "";

  topic = "Food";
   
 if (topic.equals("Food"))
 {   
    if (Serial.available() > 0 && go && !allowStop)
    { 
       tries++;
       let = Serial.read(); 
       input += let;
       checking[tries - 1] = input.charAt(0);
       
       Serial.println(pics[numWrong]);
       Serial.println(foodWord);
       Serial.print("You guessed ");
       Serial.println(input);
  
       int index = foodWord.indexOf(input);
       int wordLength = foodWord.length();
       
       if (index > -1)
       {
          if (numRight == wordLength - 1)
          {
            money += potentialGain;
            Serial.println(foodWord);
            Serial.println();
            Serial.print("Congratulations, You won in ");
            Serial.print(tries);
            Serial.println(" tries!");
            Serial.print("Money Won: $");
            Serial.println(money);
            win = true;
            correct = true;
          }
          else
          {
            boolean printCorrect = true;;
  
            for (int i = 0; i < foodWord.length(); i++)
            {
              if (foodWord.charAt(i) == input.charAt(0))
              {
                 if (guesses[i] == input.charAt(0))
                 {
                    printCorrect = false;
                 }
                 else
                 {
                   guesses[i] =  input.charAt(0); 
                   numRight++;
                 }
              } 
            }

            if (printCorrect)
            {
                Serial.println("Correct!");
                money += potentialGain;
                old = millis();
                correct = true;
            }
            else
               Serial.println("Try again, you already entered that letter");

            for (int i = 0; i < len; i++)
            {
              Serial.print(guesses[i]);
            }
            
          }
       }
       else
       {
          numWrong++;
  
          if (numWrong == 7)
          {
            Serial.println(pics[numWrong]);
            Serial.print("Game Over! The word was: ");
            Serial.println(foodWord);
            Serial.print("Money Won: $");
            Serial.println(money);
            incorrect = true;
          }
          else
          {
            Serial.println("Incorrect!");
            old2 = millis();
            incorrect = true;
            
            //money -= potentialGain;
            
            Serial.println(pics[numWrong]);
            
            for (int i = 0; i < len; i++)
            {
              Serial.print(guesses[i]);
            }
            
          }
          
        }
        
       repeat = false;
       Serial.println();
       go = false;

       Serial.print("Money : $");
       Serial.println(money);
       
       if (!win)
        Serial.println("Spin the wheel!");

       //Serial.println(incorrect);

    }    
 }
}

void allOn()
{
  digitalWrite(yellowLeft, HIGH);
  digitalWrite(blueLeft, HIGH);
  digitalWrite(blueRight, HIGH);
  digitalWrite(yellowRight, HIGH);
  digitalWrite(redRight, HIGH);
  digitalWrite(redLeft, HIGH);
}

void checkButtons()
{
  int goState = digitalRead(goButton);
  int stopState = digitalRead(stopButton);

  Serial.print("go = ");
  Serial.print(goState);
  Serial.print(", stop = ");
  Serial.println(stopState);
}

void cycle()
{
  int goState = digitalRead(goButton);
  int stopState = digitalRead(stopButton);
  
  long now = millis();
  
  if (goState == 1) 
  {
    cycle1 = true;
    allowStop = true;
  }

  if (cycle1)
   tone(buzzer, 1760.00);
    
  if (stopState == 1) 
  {
    cycle1 = false;
    go = true;
    printing = true;
    noTone(buzzer);

    if (printing && now > future && allowStop)
    {
      future = now + 1000;
      Serial.println();
      Serial.println("Guess a letter"); 
      allowStop = false; 
      printing = false;
    }
  }
  
  long ms = millis();
  long sec = ms/50;
    
  if (cycle1)
  {
    currentLED = sec % 6;
    
    if(sec%6==0)
    {  
      digitalWrite(yellowLeft, HIGH);
    }
    else
    {
      digitalWrite(blueLeft, LOW);
      digitalWrite(blueRight, LOW);
      digitalWrite(yellowRight, LOW);
      digitalWrite(redLeft, LOW);
      digitalWrite(redRight, LOW);
    }
     if(sec%6==1)
    {
      digitalWrite(redLeft, HIGH);
    }
    else
    {
      digitalWrite(yellowLeft, LOW);
      digitalWrite(blueRight, LOW);
      digitalWrite(yellowRight, LOW);
      digitalWrite(blueLeft, LOW);
      digitalWrite(redRight, LOW);
    }
     if(sec%6==2)
    {
       digitalWrite(blueRight, HIGH);
    }
    else
    {
      digitalWrite(yellowLeft, LOW);
      digitalWrite(redLeft, LOW);
      digitalWrite(yellowRight, LOW);
      digitalWrite(blueRight, LOW);
      digitalWrite(redRight, LOW);
    }
     if(sec%6==3)
    {
       digitalWrite(yellowRight, HIGH);
    }
    else
    {
      digitalWrite(yellowLeft, LOW);
      digitalWrite(blueLeft, LOW);
      digitalWrite(blueRight, LOW);
      digitalWrite(redLeft, LOW);
      digitalWrite(redRight, LOW);
    }
    if (sec % 6 == 4)
    {
      digitalWrite(redRight, HIGH);
    }
    else
    {
      digitalWrite(yellowLeft, LOW);
      digitalWrite(blueLeft, LOW);
      digitalWrite(blueRight, LOW);
      digitalWrite(redLeft, LOW);
      digitalWrite(yellowRight, LOW);
    }
    if (sec % 6 == 5)
    {
      digitalWrite(blueLeft, HIGH);
    }
    else
    {
      digitalWrite(yellowLeft, LOW);
      digitalWrite(yellowRight, LOW);
      digitalWrite(redRight, LOW);
      digitalWrite(redLeft, LOW);
      digitalWrite(blueRight, LOW);
    }
  }
  else
  {
    if(currentLED==0)
    {
      digitalWrite(yellowLeft, HIGH);
      digitalWrite(blueLeft, LOW);
      digitalWrite(blueRight, LOW);
      digitalWrite(yellowRight, LOW);
      digitalWrite(redLeft, LOW);
      digitalWrite(redRight, LOW);
      money = 0;
      potentialGain = 0;
    }
    if(currentLED==1)
    {
      digitalWrite(blueLeft, HIGH);
      digitalWrite(yellowLeft, LOW);
      digitalWrite(blueRight, LOW);
      digitalWrite(yellowRight, LOW);
      digitalWrite(redLeft, LOW);
      digitalWrite(redRight, LOW);
      potentialGain = 500;
    }
    if(currentLED==2)
    {
      digitalWrite(redLeft, HIGH);
      digitalWrite(blueLeft, LOW);
      digitalWrite(blueRight, LOW);
      digitalWrite(yellowRight, LOW);
      digitalWrite(yellowLeft, LOW);
      digitalWrite(redRight, LOW);
      potentialGain = 25;
    }
    if(currentLED==3)
    {
      digitalWrite(redRight, HIGH);
      digitalWrite(blueLeft, LOW);
      digitalWrite(blueRight, LOW);
      digitalWrite(yellowRight, LOW);
      digitalWrite(redLeft, LOW);
      digitalWrite(yellowLeft, LOW);
      potentialGain = 50;
    }
    if(currentLED==4)
    {
      digitalWrite(blueRight, HIGH);
      digitalWrite(blueLeft, LOW);
      digitalWrite(yellowLeft, LOW);
      digitalWrite(yellowRight, LOW);
      digitalWrite(redLeft, LOW);
      digitalWrite(redRight, LOW);
      potentialGain = 200;
    }
    if(currentLED==5)
    {
      digitalWrite(yellowRight, HIGH);
      digitalWrite(blueLeft, LOW);
      digitalWrite(blueRight, LOW);
      digitalWrite(yellowLeft, LOW);
      digitalWrite(redLeft, LOW);
      digitalWrite(redRight, LOW);
      potentialGain = 75;
    }

  }
}

void playTones(int buzz, int tones[], int durations[], int length)
{
  if(sizeof(tones)/sizeof(int) == sizeof(durations)/sizeof(int))
  {
    long sum = 0;
    for(int i = 0; i<length;i++)
    {
      sum += durations[i];
    }
    //calculate which index we should be working with
    int musicI = 0;
    for(musicI = 0; millis()%sum>=sumUntil(durations,musicI,length);musicI++)//super bananas
    {    }
    if(millis()%sum<sumUntil(durations,musicI,length))    //bananas
    {
      if(tones[musicI]!= 0)
      {
        tone(buzz, tones[musicI]);
      }
      else
      {
        noTone(buzz);
      }
    }
  }
}

long sumUntil(int arr[], int index,int length)
{
  long sum = 0;
  for(int i = 0;i<=index;i++)
  {
    sum+=arr[i];
  }
  return sum;
}
