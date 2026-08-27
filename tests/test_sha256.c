#include "sha256.h"
#include <stdio.h>
#include <string.h>
int main(void){
    const char *msg="abc"; uint8_t hash[32]; char hex[65]; SHA256_CTX ctx;
    sha256_init(&ctx);sha256_update(&ctx,(const uint8_t*)msg,strlen(msg));sha256_final(&ctx,hash);
    for(int i=0;i<32;i++)sprintf(hex+i*2,"%02x",hash[i]);hex[64]=0;
    if(strcmp(hex,"ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad")==0){puts("SHA-256 test PASSED");return 0;}
    puts("SHA-256 test FAILED");return 1;
}
