#include <Encabulator.h>;
#include <Wire.h>;
#include <I2C.h>;   // NOTE: For reasons buried in the Encabulator.cpp file, you might want to download and use this library instead.

// 9241082682

int loopCounter = 0;

int tempR = 0;
int tempG = 0;
int tempB = 0;

uint8_t crap[192];
uint8_t crap1[192];

boolean redalert=false;
boolean redalertflicker=false;
int redalertcounter=0;

int rot=0;
//int split=96;
char p;

void setup() {
    Serial.begin(9600);
    Serial.println("setup()");
    Encabulator.upUpDownDownLeftRightLeftRightBA();
    Encabulator.addressable.setMode(1);
    // enable some debugging on the serial port
    
    Encabulator.setVerbose(false);
    for (int i=0;i<(64*3);i+=3){
        //crap[i]=crap[(i+1)%64];
        crap[i]=random(255);
        crap[i+1]=random(255);
        crap[i+2]=random(255);
        crap[i]=0;
        crap[i+1]=0;
        crap[i+2]=0;
    }
    crap[0]=255;
    crap[4]=255;
    crap[8]=255;
    
    crap[0+96]=255;
    crap[4+96]=255;
    crap[8+96]=255;
    
    crap[0+48]=255;
    crap[4+48]=255;
    crap[8+48]=255;
    
    crap[0+144]=255;
    crap[4+144]=255;
    crap[8+144]=255;
    
    
    crap1[2]=255;
    crap1[4]=255;
    crap1[6]=255;
    
    crap1[0+96]=255;
    crap1[4+96]=255;
    crap1[8+96]=255;
    
    crap1[2+48]=255;
    crap1[4+48]=255;
    crap1[6+48]=255;
    
    crap1[0+144]=255;
    crap1[4+144]=255;
    crap1[8+144]=255;
//    for (int i=0;i<192;i++){crap1[i]=crap[i];}
//    Encabulator.stripBankA.fadeHeaderToRGB(1,255,255,255,5); 
  //  Encabulator.stripBankA.fadeHeaderToRGB(2,255,255,255,5); 
  //  Encabulator.addressable.drawFrame(64,crap);
}

void loop() {
    
    // draw some gradients on the addressable based on the loop counter
    
    // uint8_t temp=crap[0];
    
    //crap[191]=temp;
    
    p=-1;
    //while(p==-1){
        p=Serial.read(); // read the serial data which is charecter store it in p
    //}
    if (p=='1'){Encabulator.stripBankA.fadeHeaderToRGB(1,0,0,50,5); }//front shields off
    
    if (p=='A'){Encabulator.stripBankA.fadeHeaderToRGB(1,0,0,0,5); }//front shields on
    if (p=='a'){Encabulator.stripBankA.fadeHeaderToRGB(1,0,255,0,5); }//front shields on
    if (p=='b'){Encabulator.stripBankA.fadeHeaderToRGB(1,50,200,0,5); }//front shields on
    if (p=='c'){Encabulator.stripBankA.fadeHeaderToRGB(1,100,150,0,5); }//front shields on
    if (p=='d'){Encabulator.stripBankA.fadeHeaderToRGB(1,150,100,0,5); }//front shields on
    if (p=='e'){Encabulator.stripBankA.fadeHeaderToRGB(1,200,50,0,5); }//front shields on
    if (p=='f'){Encabulator.stripBankA.fadeHeaderToRGB(1,255,0,0,5); }//front shields on
    
    if (p=='2'){Encabulator.stripBankA.fadeHeaderToRGB(2,0,0,50,5); }//front shields off
    
    if (p=='G'){Encabulator.stripBankA.fadeHeaderToRGB(2,0,0,0,5); }//back shields on
    if (p=='g'){Encabulator.stripBankA.fadeHeaderToRGB(2,0,255,0,5); }//back shields on
    if (p=='h'){Encabulator.stripBankA.fadeHeaderToRGB(2,50,200,0,5); }//back shields on
    if (p=='i'){Encabulator.stripBankA.fadeHeaderToRGB(2,100,150,0,5); }//back shields on
    if (p=='j'){Encabulator.stripBankA.fadeHeaderToRGB(2,150,100,0,5); }//back shields on
    if (p=='k'){Encabulator.stripBankA.fadeHeaderToRGB(2,200,50,0,5); }//back shields on
    if (p=='l'){Encabulator.stripBankA.fadeHeaderToRGB(2,255,0,0,5); }//front shields on
    
    if (p=='4' && rot<2){
        rot=1;
        //split=(split+3)%192;
    }
    if (p=='5' && rot<2){rot=0;}
    if (p=='5' && rot>=2){rot=rot-1;}
    if (p=='6' && rot<2){
       rot=-1;
       //split=(split+189)%192;
     }
    if (p=='8'){rot=2;}
    if (p=='9'){rot=3;}
    if (p=='z'){rot=4;}
    if (p=='y'){rot=5;}
  //  if (p=='x'){fwd=0;}
    
    if (p=='7'){
        Encabulator.stripBankA.jumpHeaderToRGB(2,255,255,255);
        Encabulator.stripBankA.jumpHeaderToRGB(1,255,255,255);
        Encabulator.stripBankA.jumpHeaderToRGB(3,255,255,255);
        Encabulator.stripBankA.jumpHeaderToRGB(4,255,255,255);
        redalertcounter=1;
      }
    
    if (p=='3'){redalert=!redalert;
        if (redalert){
        Encabulator.stripBankA.jumpHeaderToRGB(3,255,0,0);
        Encabulator.stripBankA.jumpHeaderToRGB(4,255,0,0);
      }
    }
    if (redalert){
        redalertcounter=redalertcounter+1;
        if (redalertcounter%8==0){
            redalertflicker=!redalertflicker;
            if (redalertflicker){
                Encabulator.stripBankA.fadeHeaderToRGB(3,0,0,0,4);
                Encabulator.stripBankA.fadeHeaderToRGB(4,0,0,0,4);
            }
            else {
                Encabulator.stripBankA.fadeHeaderToRGB(3,255,0,0,3);
                Encabulator.stripBankA.fadeHeaderToRGB(4,255,0,0,3);
            }
        }
    }
    else {if (redalertcounter>0){
        Encabulator.stripBankA.fadeHeaderToRGB(3,0,0,0,5);
        Encabulator.stripBankA.fadeHeaderToRGB(4,0,0,0,5);
        redalertcounter=0;redalertflicker=false;}}
    if (rot==-1){
    //left
    uint8_t temp0=crap[0];
    uint8_t temp1=crap[1];
    uint8_t temp2=crap[2];
    for(int i=0;i<192;i+=3){
        crap[i]=crap[i+3];
        crap[i+1]=crap[i+4];
        crap[i+2]=crap[i+5];
    }
        crap[191]=temp2;
    crap[190]=temp1;
    crap[189]=temp0;
    //Encabulator.addressable.drawFrame(64,crap);
   }
    
    //right
    if (rot==1){
    uint8_t temp0=crap[189];
    uint8_t temp1=crap[190];
    uint8_t temp2=crap[191];
    for(int i=191;i>=0;i-=3){
        crap[i]=crap[i-3];
        crap[i-1]=crap[i-4];
        crap[i-2]=crap[i-5];
    }
    crap[2]=temp2;
    crap[1]=temp1;
    crap[0]=temp0;

    }
    
    //forward
    if (rot>1){
      for (int r=rot;r>1;r--){
    uint8_t temp0=crap1[0];
    uint8_t temp1=crap1[1];
    uint8_t temp2=crap1[2];
    for(int i=0;i<93;i+=3){
        crap1[i]=crap1[i+3];
        crap1[i+1]=crap1[i+4];
        crap1[i+2]=crap1[i+5];
    }
    crap1[93]=temp0;
    crap1[94]=temp1;
    crap1[95]=temp2;
    
    temp0=crap1[189];
    temp1=crap1[190];
    temp2=crap1[191];
    for(int i=191;i>=96;i-=3){
        crap1[i]=crap1[i-3];
        crap1[i-1]=crap1 [i-4];
        crap1[i-2]=crap1[i-5];
    }
    crap1[96]=temp0;
    crap1[97]=temp1;
    crap1[98]=temp2;
      }
      
 //   Encabulator.addressable.drawFrame(64,crap1);
    }
    if (rot>1)  Encabulator.addressable.drawFrame(64,crap1);
else Encabulator.addressable.drawFrame(64,crap);
//    rot=0;
//    int g=random(192);
    //if (random(10000)<=100)
    //crap[g]=crap[g]+10;

    //Encabulator.addressable.shiftBufferOnce(1,1);
    //Encabulator.addressable.testPattern();
    //Encabulator.addressable.drawFrame(64,crap1);
    //--------------------------------------
    
    
    //Encabulator.addressable.drawGradient(tempR,0,tempB,255 - tempR,0,255 - tempB,64);
    
    // cycle through RGB on the headers.  this is a great way to make sure the strip is fastened properly
    
    //for (int i = 1 ; i < 5 ; i++) {  //
        //    Encabulator.stripBankA.jumpHeaderToRGB(i,255,0,0);
        //    Encabulator.stripBankB.jumpHeaderToRGB(i,255,0,0);
    // }
    //delay(1000);
    //for (int i = 1 ; i < 5 ; i++) {
        //    Encabulator.stripBankA.fadeHeaderToRGB(i,0,0,0,5);
        //    Encabulator.stripBankB.fadeHeaderToRGB(i,0,0,0,5);
    //}
    //delay(500);
    //for (int i = 1 ; i < 5 ; i++) {
        //    Encabulator.stripBankA.jumpHeaderToRGB(i,0,255,0);
        //    Encabulator.stripBankB.jumpHeaderToRGB(i,0,255,0);
    // }
    //delay(1000);
    //for (int i = 1 ; i < 5 ; i++) {
        //    Encabulator.stripBankA.fadeHeaderToRGB(i,0,0,0,5);
        //    Encabulator.stripBankB.fadeHeaderToRGB(i,0,0,0,5);
    //}
    
    // delay(500);
    // for (int i = 1 ; i < 5 ; i++) {
        //      Encabulator.stripBankA.jumpHeaderToRGB(i,0,0,255);
        //      Encabulator.stripBankB.jumpHeaderToRGB(i,0,0,255);
    // }
    // delay(1000);
    
    //  for (int i = 1 ; i < 5 ; i++) {
        //    Encabulator.stripBankA.fadeHeaderToRGB(i,0,0,0,5);
        //     Encabulator.stripBankB.fadeHeaderToRGB(i,0,0,0,5);
    // }
    //delay(500);
    
}
