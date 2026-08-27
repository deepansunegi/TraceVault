#include "vault.h"
#include "storage.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
    Vault vault;vault_init(&vault);if(!load_vault(&vault)){fprintf(stderr,"Warning: database could not be loaded.\n");}
    for(;;){
        printf("\n========== TRACEVAULT ==========\n1. Add evidence\n2. List evidence\n3. Search evidence\n4. Verify integrity\n5. Update status\n6. Add custody event\n7. Generate report\n8. View audit log\n0. Exit\n================================\n");
        int c=read_int("Choose: ",0,8);
        switch(c){
            case 1:vault_add(&vault);save_vault(&vault);break;case 2:vault_list(&vault);break;
            case 3:vault_search(&vault);break;case 4:vault_verify(&vault);break;case 5:vault_update_status(&vault);save_vault(&vault);break;
            case 6:vault_add_event(&vault);save_vault(&vault);break;case 7:vault_generate_report(&vault);break;case 8:vault_show_audit();break;
            case 0:save_vault(&vault);puts("TraceVault closed safely.");return 0;
        }
    }
}
