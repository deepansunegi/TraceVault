#include "storage.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define DB "data/evidence.db"
#define AUDIT "data/audit.log"

int load_vault(Vault *v) {
    FILE *f=fopen(DB,"rb"); if(!f) return 1;
    size_t n=fread(v,sizeof(*v),1,f); fclose(f); return n==1;
}
int save_vault(const Vault *v) {
    FILE *f=fopen(DB,"wb"); if(!f) return 0;
    size_t n=fwrite(v,sizeof(*v),1,f); fclose(f); return n==1;
}
void audit_log(const char *action,const char *details) {
    FILE *f=fopen(AUDIT,"a"); if(!f)return;
    time_t now=time(NULL); struct tm *t=localtime(&now); char ts[32];
    strftime(ts,sizeof(ts),"%Y-%m-%d %H:%M:%S",t);
    fprintf(f,"[%s] %s | %s\n",ts,action,details); fclose(f);
}
