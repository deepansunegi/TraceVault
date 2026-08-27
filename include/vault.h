#ifndef VAULT_H
#define VAULT_H

#define MAX_EVIDENCE 100
#define MAX_EVENTS 20

typedef enum {
    STATUS_NEW = 1,
    STATUS_REVIEW,
    STATUS_VERIFIED,
    STATUS_ARCHIVED
} EvidenceStatus;

typedef struct {
    char timestamp[32];
    char person[64];
    char action[128];
} CustodyEvent;

typedef struct {
    int id;
    char title[80];
    char case_id[40];
    char description[256];
    char file_path[256];
    char sha256[65];
    char created_at[32];
    EvidenceStatus status;
    CustodyEvent events[MAX_EVENTS];
    int event_count;
} Evidence;

typedef struct {
    Evidence items[MAX_EVIDENCE];
    int count;
} Vault;

void vault_init(Vault *vault);
void vault_add(Vault *vault);
void vault_list(const Vault *vault);
void vault_search(const Vault *vault);
void vault_verify(Vault *vault);
void vault_update_status(Vault *vault);
void vault_add_event(Vault *vault);
void vault_generate_report(const Vault *vault);
void vault_show_audit(void);

#endif
