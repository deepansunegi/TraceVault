#include "vault.h"
#include "utils.h"
#include "sha256.h"
#include "storage.h"
#include <stdio.h>
#include <string.h>

static const char *status_name(EvidenceStatus s) {
    switch(s){case STATUS_NEW:return "NEW";case STATUS_REVIEW:return "UNDER_REVIEW";case STATUS_VERIFIED:return "VERIFIED";case STATUS_ARCHIVED:return "ARCHIVED";default:return "UNKNOWN";}
}
static Evidence *find_id(Vault *v,int id){for(int i=0;i<v->count;i++)if(v->items[i].id==id)return &v->items[i];return NULL;}
static void print_item(const Evidence *e){
    printf("\nID: %d | Status: %s\nTitle: %s\nCase: %s\nCreated: %s\nFile: %s\nSHA-256: %s\nDescription: %s\n",
    e->id,status_name(e->status),e->title,e->case_id,e->created_at,e->file_path,e->sha256,e->description);
}
void vault_init(Vault *v){memset(v,0,sizeof(*v));}
void vault_add(Vault *v){
    if(v->count>=MAX_EVIDENCE){puts("Vault is full.");return;}
    Evidence *e=&v->items[v->count]; memset(e,0,sizeof(*e)); e->id=v->count? v->items[v->count-1].id+1:1;
    read_line("Title: ",e->title,sizeof(e->title));read_line("Case ID: ",e->case_id,sizeof(e->case_id));
    read_line("Description: ",e->description,sizeof(e->description));read_line("File path: ",e->file_path,sizeof(e->file_path));
    if(!sha256_file(e->file_path,e->sha256)){puts("Could not read file. Record not created.");return;}
    timestamp_now(e->created_at);e->status=STATUS_NEW;v->count++;
    audit_log("ADD_EVIDENCE",e->title);puts("Evidence added and SHA-256 baseline stored.");
}
void vault_list(const Vault *v){if(!v->count){puts("No evidence records.");return;}for(int i=0;i<v->count;i++)print_item(&v->items[i]);}
void vault_search(const Vault *v){
    char q[100];read_line("Search keyword: ",q,sizeof(q));int found=0;
    for(int i=0;i<v->count;i++){Evidence *e=&v->items[i];if(contains_icase(e->title,q)||contains_icase(e->case_id,q)||contains_icase(e->description,q)){print_item(e);found=1;}}
    if(!found)puts("No matches.");
}
void vault_verify(Vault *v){
    int id=read_int("Evidence ID: ",1,1000000);Evidence *e=find_id(v,id);char now[65];
    if(!e){puts("ID not found.");return;}if(!sha256_file(e->file_path,now)){puts("File is unavailable.");return;}
    if(strcmp(now,e->sha256)==0){puts("INTEGRITY OK: file matches baseline hash.");audit_log("VERIFY_OK",e->title);}
    else {puts("WARNING: TAMPER DETECTED! Current hash differs from baseline.");audit_log("VERIFY_FAILED",e->title);}
}
void vault_update_status(Vault *v){
    int id=read_int("Evidence ID: ",1,1000000);Evidence *e=find_id(v,id);if(!e){puts("ID not found.");return;}
    printf("1.NEW  2.UNDER_REVIEW  3.VERIFIED  4.ARCHIVED\n");e->status=(EvidenceStatus)read_int("New status: ",1,4);
    audit_log("STATUS_UPDATE",e->title);puts("Status updated.");
}
void vault_add_event(Vault *v){
    int id=read_int("Evidence ID: ",1,1000000);Evidence *e=find_id(v,id);if(!e){puts("ID not found.");return;}
    if(e->event_count>=MAX_EVENTS){puts("Event limit reached.");return;}CustodyEvent *x=&e->events[e->event_count++];
    timestamp_now(x->timestamp);read_line("Person responsible: ",x->person,sizeof(x->person));read_line("Action/event: ",x->action,sizeof(x->action));
    audit_log("CUSTODY_EVENT",e->title);puts("Custody event recorded.");
}
void vault_generate_report(const Vault *v){
    FILE *f=fopen("data/report.txt","w");if(!f){puts("Cannot create report.");return;}
    fprintf(f,"TRACEVAULT SECURITY REPORT\n==========================\nTotal records: %d\n\n",v->count);
    for(int i=0;i<v->count;i++){const Evidence *e=&v->items[i];fprintf(f,"[%d] %s\nCase: %s\nStatus: %s\nSHA-256: %s\nCreated: %s\nEvents: %d\n\n",e->id,e->title,e->case_id,status_name(e->status),e->sha256,e->created_at,e->event_count);}
    fclose(f);audit_log("REPORT_GENERATED","data/report.txt");puts("Report generated: data/report.txt");
}
void vault_show_audit(void){
    FILE *f=fopen("data/audit.log","r");char line[512];if(!f){puts("No audit log yet.");return;}while(fgets(line,sizeof(line),f))fputs(line,stdout);fclose(f);
}
