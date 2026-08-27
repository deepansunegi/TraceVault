#ifndef STORAGE_H
#define STORAGE_H

#include "vault.h"

int load_vault(Vault *vault);
int save_vault(const Vault *vault);
void audit_log(const char *action, const char *details);

#endif
