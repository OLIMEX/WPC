// Enjoy the random names for variables and function at moments. 
// and learn how to write down the year that Olimex was founded in Roman numerals
// For completion, i give you the foundation of their fraction system: A twelfth !
// DISCLAIMER : Any similarities with attempt at comedy is pure coincidence !

char plaintext[]="1991"; // Why a char[] array? More user friendly with both c and c++
// and because i can !! :)

int tocipher[sizeof(plaintext)];
int ciphered[sizeof(tocipher)];

boolean stringComplete = false;  // whether the string is complete
boolean done = false; // no relationship between the name and function ! ;)

void setup() {
  // DO NOT put your code here to run once ?!?!
  Serial.begin(9600);
  Serial.println("Roman Numeral History Lesson with Olimex Pt.1");
}

void loop() 
{ 
  while(Serial){
    if(stringComplete == true)  // How long is a piece of string ?!
    {
      calculate();
      Serial.println("string complete");
      fractions();
      //
    }
    if(stringComplete == false){
      Serial.println("string NOT complete");
      // put your debug code here, to find out where you was going wrong: 
      uint8_t sizeofarray = sizeof(plaintext);
      uint8_t i;
      //
      for(i=0;i<=sizeofarray;i++)
      {
        uint16_t retrieved;
        retrieved=plaintext[i];
        leap(retrieved,i);
        Serial.println(retrieved);

        if(retrieved==0){
          Serial.print(i);
          Serial.println(" characters in the string processed.END OF STRING "); // Thats how long a string is :)
          Serial.println("null CHARACTER");
          stringComplete = true; 
          // The use of goto's is highly frowned upon...
          // ...but can be quite handy as well !
          goto bailout; 
        }
      }
bailout: // " Bloody bankers taken all !"
      delay(1); // As the tradition says:" Rome and Pavia weren't made in one day!
    }  
    while(done==true){
      // Allowing time for Nero to play with fire !
    }
  }
}

int leap(int in,int il){
  switch (in) {
  case '0':  
    //
    Serial.println("tocipher- 0 ");
    tocipher[il]=0;
    break;
  case '1':
    Serial.println("tocipher- 1 ");
    tocipher[il]=1;  
    //
    break;
  case '2': 
    Serial.println("tocipher- 2 ");
    tocipher[il]=2;  
    //
    break;
  case '3': 
    Serial.println("tocipher- 3 ");
    tocipher[il]=3;  
    //
    break;
  case '4':
    Serial.println("tocipher- 4 ");
    tocipher[il]=4;  
    //
    break;
  case '5': 
    Serial.println("tocipher- 5 ");
    tocipher[il]=5;  
    //
    break;
  case '6':
    Serial.println("tocipher- 6 ");
    tocipher[il]=6;  
    //
    break;
  case '7':
    Serial.println("tocipher- 7 "); 
    tocipher[il]=7;  
    //
    break;
  case '8':
    Serial.println("tocipher- 8 ");
    tocipher[il]=8;  
    //
    break;
  case '9': 
    Serial.println("tocipher- 9 ");
    tocipher[il]=9;  
    //
    break;
    //
  default:
    //
    break;
    //
  }
}

void calculate(){
  uint16_t sizeofarray = sizeof(tocipher);
  int i;
  //
  for(i=0;i<=sizeofarray;i++)
  {
    int retrieved;
    retrieved=tocipher[i];
    bigjump(retrieved,i);
    //
  }
}

int bigjump(int coming, int il){

  switch (il) { 
  case 0:
    int k;
    Serial.print("Year Olimex was founded in Roman numerals- ");
    for(k=0;k<coming;k++){
      Serial.print("M");
    }
    break;

  case 1:
    if(coming==9){
      Serial.print("CM");
    }
    if (coming==8){
      Serial.print("DCCC");
    }
    if (coming==7){
      Serial.print("DCC");
    }
    if (coming==6){
      Serial.print("DC");
    }
    if (coming==5){
      Serial.print("D");
    }
    if (coming==4){
      Serial.print("CD");
    }
    if (coming==3){
      Serial.print("CCC");
    }
    if (coming==2){
      Serial.print("CC");
    }
    if (coming==1){
      Serial.print("C");
    }
    break;

  case 2:
    if(coming==9){
      Serial.print("XC");
    }
    else if (coming==8){
      Serial.print("LXXX");
    }
    else if (coming==7){
      Serial.print("LXX");
    }
    else if (coming==6){
      Serial.print("LX");
    }
    else if (coming==5){
      Serial.print("L");
    }
    else if (coming==4){
      Serial.print("XL");
    }
    else if (coming==3){
      Serial.print("XXX");
    }
    else if (coming==2){
      Serial.print("XX");
    }
    else if (coming==1){
      Serial.print("X");
    }
    break;

  case 3:
    if(coming==9){
      Serial.print("IX");
    }
    else if (coming==8){
      Serial.print("VIII");
    }
    else if (coming==7){
      Serial.print("VII");
    }
    else if (coming==6){
      Serial.print("VI");
    }
    else if (coming==5){
      Serial.print("V");
    }
    else if (coming==4){
      Serial.print("IV");
    }
    else if (coming==3){
      Serial.print("III");
    }
    else if (coming==2){
      Serial.print("II");
    }
    else if (coming==1){
      Serial.print("I");
    }
    done=true;
    break;

  case 4:
    Serial.println("");
    break;  

  default:
    break;
  }
}


void fractions(){
  // Any similarites with attempt at comedy is pure coincidence !
  uint16_t sizeofarray = sizeof(tocipher);
  int i;
  //
  for(i=0;i<=sizeofarray;i++)
  {
    int retrieved;
    int accum;
    retrieved=tocipher[i];
    int result=0;
    switch (i) {
    case 0:  
      //
      accum=(retrieved*1000);
      Serial.print("result thou ");
      Serial.println(accum);
      break;
    case 1:
      accum+=(retrieved*100); 
      Serial.print("result with hundr");
      Serial.println(accum); 
      //
      break;
    case 2: 
      accum+=(retrieved*10); 
      Serial.print("result with decim ");
      Serial.println(accum); 
      //
      break;
    case 3: 
      accum+=retrieved; 
      Serial.print("total result ");
      Serial.println(accum);
      //
      break;

    case 4:
      Serial.print("Proverbial 1/12 (twelfth) Roman fracction ");
      Serial.print((float)(accum/12));
      break;

    default:
      break;
      //
    } 
  }
}
















