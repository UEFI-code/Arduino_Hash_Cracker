#include "sha256.h"
#define txtlenmax 16
BYTE in_hash[SHA256_BLOCK_SIZE];
BYTE out_hash[SHA256_BLOCK_SIZE];
char txt[64] = {0};
int txtlen = 0;

void show_result(){
    char texthash[2*SHA256_BLOCK_SIZE+1];
    for(int i=0; i<SHA256_BLOCK_SIZE; ++i)
    sprintf(texthash+2*i, "%02X", out_hash[i]);
    Serial.println(texthash);
}

int hashcmp()
{
  for(int i=0;i<SHA256_BLOCK_SIZE;i++)
    if(in_hash[i] != out_hash[i])
      return -1;
  return 0;
}

void gentxt()
{
  txtlen = random(1, txtlenmax+1);
  for(int i=0;i<txtlen;i++)
    txt[i] = random(32,127);
  txt[txtlen] = 0;
}

void setup() {
  Sha256 sha256Instance;
  randomSeed(analogRead(5));
  Serial.begin(9600);
  crackNow:
  while(1)
  {
    String gethash = Serial.readString();
    if(gethash.c_str()[0] != 0)
    {
      //Serial.println("got hash");
      char *cstr = gethash.c_str();
      char buf[3] = {0};
      for(int i=0;i<32;i++)
      {
        buf[0] = cstr[i*2];
        buf[1] = cstr[i*2+1];
        sscanf(buf,"%x",in_hash+i);
      }
      break;
    }
    delay(500);
  }
  while(1)
  {
    sha256Instance.init();
    gentxt();
    //Serial.println(txt);
    strcpy(sha256Instance.data,txt);
    sha256Instance.update(txtlen);
    sha256Instance.final(out_hash);
    if(hashcmp() == 0)
    {
      Serial.println("Cracked!!!");
      Serial.println(txt);
      show_result();
      break;
    }
    //show_result();
    //delay(500);
  }
  goto crackNow;
}

void loop() {
  
}
