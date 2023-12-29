#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define tauxChangeEUR_TND 3.39
#define tauxChangeUSD_TND 3.06
#define tauxChangeGBP_TND 3.9
int nbCompte = 0;

typedef struct transaction{
    char type[30];  //versement ou retrait
    float montant;
    char date[10];  //format jj/mm/aaaa
    struct transaction *suiv;
}transaction;

typedef struct compte {
    long  nTel, CIN;
    int numeroCompte;
    char mail[50];
    float solde;
    char nomClient[100];
    char Adresse[100];
    transaction *transaction;
    struct compte *suiv;
}compte;

compte *banque = NULL;

int DateEstValide(char *date);
compte* creationCompte();
void ajouterCompte(compte *compte);
void miseajour(compte *compte);
void retrait(compte *compte);
void versement(compte *compte);
void virement(compte *c1); // virement fait à partir du compte c1 vers le compte c2
void afficherTransactions(compte *compte);
compte* rechercherCompte(int numero); // rechercher le compte dont le numéro est numero
void supprimerTransactions(transaction *transaction);
void supprimerCompte(int numero);
void afficherDetailsCompte(compte *compte);
void afficherListeClients();
void changeDevise(compte *compte);

int main(){
    int choix;
    printf("\nBienvenue à la banque!\n");
    do{
            printf("\nOptions disponibles:\n");
            printf("1. Afficher la liste des comptes\n");
            printf("2. Créer un nouveau compte\n");
            printf("3. Afficher les détails d'un compte\n");
            printf("4. Modifier un compte\n");
            printf("5. Versement d'argent\n");
            printf("6. Retrait d'argent\n");
            printf("7. Virement vers un autre compte:\n");
            printf("8. Échanger de la devise\n");
            printf("9. Afficher les transactions d'un compte\n");
            printf("10. Supprimer un compte\n");
            printf("11. Quitter l'application\n");
            printf("Votre choix: ");
            scanf("%d", &choix);
            getchar();
            switch (choix)
            {
            case 1:
                afficherListeClients();
                break;
            case 2:
                {compte *c = creationCompte();
                if (c != NULL){
                ajouterCompte(c);
                };
                break;}
            case 3:
                {int num;
                compte *c;
                printf("Donner le numéro de compte: ");
                scanf("%d",&num);
                getchar();
                c = rechercherCompte(num);
                if (c != NULL){
                    afficherDetailsCompte(c);
                }
                break;}
            case 4:
                {int num;
                compte *c;
                printf("Donner le numéro de compte à modifier: ");
                scanf("%d",&num);
                getchar();
                c = rechercherCompte(num);
                if (c != NULL)
                miseajour(c);
                break;}
                
            case 5:
                {int num;
                compte *c;
                printf("Donner le numéro de compte: ");
                scanf("%d",&num);
                getchar();
                c = rechercherCompte(num);
                if (c != NULL)
                versement(c);
                break;
                }
                
            case 6:
                {int num;
                compte *c;
                printf("Donner le numéro de compte: ");
                scanf("%d",&num);
                getchar();
                c = rechercherCompte(num);
                if (c != NULL)
                retrait(c);
                break;
                }
                
            case 7:
                {int num;
                compte *c;
                printf("Veuillez saisir le numéro de compte de l'éxpéditeur: ");
                scanf("%d",&num);
                getchar();
                c = rechercherCompte(num);
                if (c != NULL)
                virement(c);
                break;
                }
                
            case 8:
                {int num;
                compte *c;
                printf("Donner le numéro de compte: ");
                scanf("%d",&num);
                getchar();
                c = rechercherCompte(num);
                if (c != NULL)
                changeDevise(c);
                break;
                }
            case 9:
                {int num;
                compte *c;
                printf("Donner le numéro de compte : ");
                scanf("%d",&num);
                getchar();
                c = rechercherCompte(num);
                if (c != NULL)
                afficherTransactions(c);
                break;}
                
            case 10:
                {int num;
                printf("Donner le numéro de compte à supprimer: ");
                scanf("%d",&num);
                getchar();
                supprimerCompte(num);
                break;
                }
            case 11:    
                printf("Merci pour votre attention !");
                break;
            };

            }while(choix < 11);
    return 0;
};

int DateEstValide(char *date) {
    // format: JJ/MM/AAAA
    if (strlen(date) != 10) {
        printf("%d\n",strlen(date));
        return 0;}
    if (date[2] != '/' || date[5] != '/') return 0;

    for (int i = 0; i < strlen(date); i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(date[i])) return 0;
    }

    int jour, mois, annee;
    sscanf(date, "%2d/%2d/%4d", &jour, &mois, &annee);

    if (jour < 1 || jour > 31) return 0;
    if (mois < 1 || mois > 12) return 0;
    if (annee < 1000 || annee > 2024) return 0; 
    return 1;
}

compte* creationCompte(){
    compte* nouvCompte = malloc(sizeof(compte));
    nbCompte ++;
    nouvCompte->numeroCompte = nbCompte;
    printf("Veuillez saisir les coordonnées du client:\n");
    printf("Nom et Prénom du client: ");
    fgets(nouvCompte->nomClient,100,stdin);
    printf("Numéro de téléphone: ");
    scanf("%ld",&nouvCompte->nTel);
    getchar();
    printf("Numéro de la cin: ");
    scanf("%ld",&nouvCompte->CIN);
    getchar();
    printf("Adresse: ");
    fgets(nouvCompte->Adresse,100,stdin);
    printf("Mail: ");
    fgets(nouvCompte->mail,50,stdin);
    printf("Solde Initial: ");
    scanf("%f",&nouvCompte->solde);
    getchar();
    nouvCompte->transaction = NULL;
    nouvCompte->suiv = NULL;
    printf("Compte créé avec succès\nLe numéro de compte est %d\n",nouvCompte->numeroCompte);
    return nouvCompte;
};

void ajouterCompte(compte *compte){
    compte->suiv = banque;
    banque = compte;
};

void miseajour(compte *compte){
    int choix;
    long num;
    char mail[50];
    char adr[100];
    if (compte == NULL){
        printf("Compte invalide.\n");
        return;
    };
    printf("\nQuel paramètre voulez-vous modifier?\n");
    printf("1.Numéro de téléphone\n");
    printf("2.Adresse\n");
    printf("3.Mail\n");
    scanf("%d",&choix);
    getchar();
    switch(choix){
        case 1:
            printf("Nouveau numéro de téléphone: ");
            scanf("%ld",&num);
            getchar();
            compte->nTel = num;
            printf("Modification effectuée avec succès !\n");
            break;
        case 2:
            printf("Nouvelle adresse: ");
            fgets(adr,100,stdin);
            strcpy(compte->Adresse,adr);
            printf("Modification effectuée avec succès !\n");
            break;
        case 3:
            printf("Nouvelle adresse mail: ");
            fgets(mail,50,stdin);
            strcpy(compte->mail,mail);
            printf("Modification effectuée avec succès !\n");
            break;
    };
};

void retrait(compte *compte){
    float montant;
    char date[12];
    int dateValide = 0;
    if (compte == NULL){
        printf("Compte invalide.\n");
        return;
    };
    
    transaction* nouvTrans = malloc(sizeof(transaction));
    while (!dateValide) {
        printf("Date de retrait (jj/mm/aaaa) : ");
        scanf("%s",date);
        getchar();
        if (DateEstValide(date)) {
            dateValide = 1;
        } else {
            printf("Format de date invalide. Veuillez réessayer.\n");
        }
    }
    //printf("Date de retrait (jj/mm/aaaa) : ");
    //fgets(date,12,stdin);
    printf("Montant de retrait: ");
    scanf("%f",&montant);
    getchar();
    if (montant > compte->solde){
        printf("Le solde du compte est insuffisant.\n");
        return;
    }
    strcpy(nouvTrans->type,"retrait");
    nouvTrans->montant = montant;
    strcpy(nouvTrans->date,date);
    nouvTrans->suiv = compte->transaction;
    compte->transaction = nouvTrans;
    compte->solde -= montant;
    printf("Opération éffectuée ave succès\n");
    printf("Nouveau solde: %f\n", compte->solde);

        };

void versement(compte *compte){
    float montant;
    char date[20];
    int dateValide = 0;
    if (compte == NULL){
        printf("Compte invalide\n");
        return;
    };
    
    transaction* nouvTrans = malloc(sizeof(transaction));
    while (!dateValide) {
        printf("Date du versement (jj/mm/aaaa) : ");
        scanf("%s",date);
        getchar(); 
        if (DateEstValide(date)) {
            dateValide = 1;
        } else {
            printf("Format de date invalide. Veuillez réessayer.\n");
        }
    };
    printf("Montant du versement: ");
    scanf("%f",&montant);
    getchar();
    strcpy(nouvTrans->type,"versement");
    nouvTrans->montant = montant;
    strcpy(nouvTrans->date,date);
    nouvTrans->suiv = compte->transaction;
    compte->transaction = nouvTrans;
    compte->solde += montant;
    printf("Opération éffectuée avec succès\n");
    printf("Nouveau solde: %f\n", compte->solde);
};

void virement(compte *c1){
    compte *c2;
    int num;
    float montant;
    char date[20];
    int dateValide = 0;
    transaction* nouvTrans = malloc(sizeof(transaction));
    printf("Veuillez saisir le numéro du compte du destinataire: ");
    scanf("%d",&num);
    getchar();
    c2 = rechercherCompte(num);
    if (c2 == NULL){
        printf("Compte introuvable.\n");
        return;
    }
    while (!dateValide) {
        printf("Date du versement (jj/mm/aaaa) : ");
        scanf("%s",date);
        getchar(); 
        if (DateEstValide(date)) {
            dateValide = 1;
        } else {
            printf("Format de date invalide. Veuillez réessayer.\n");
        }
    };
    printf("Saisir le montant du virement: ");
    scanf("%f", &montant);
    getchar();
    strcpy(nouvTrans->type,"virement");
    nouvTrans->montant = montant;
    strcpy(nouvTrans->date,date);
    nouvTrans->suiv = c1->transaction;
    c1->transaction = nouvTrans;
    c2->solde += montant;
    c1->solde -= montant;
    printf("Virement effectué avec succès\n");
    printf("Le nouveau solde du compte %d est: %f\n",c1->numeroCompte,c1->solde);
    printf("Le nouveau solde du compte %d est: %f\n",c2->numeroCompte,c2->solde);
}
    
void afficherTransactions(compte *compte){
    transaction *tr = compte->transaction;
    if (compte == NULL){
        printf("Compte invalide.\n");
        return;
    };
    if (tr == NULL){
        printf("Aucune transaction n'a encore été effectuée\n");
        return;
    }
    printf("Les transaction du compte %d:\n", compte->numeroCompte);
    while (tr != NULL){
        printf("DATE: %s, Type: %s, Montant: %f\n",tr->date, tr->type, tr->montant);
        tr = tr->suiv;
    };
};

compte* rechercherCompte(int numero){
    compte *courant = banque;
    while (courant != NULL){
        if (courant->numeroCompte == numero ){
            return courant;
        }
        courant = courant->suiv;
    }
    printf("Aucun compte trouvé\n");
    return NULL;

};

void supprimerTransactions(transaction *tr){
    transaction *tmp;
    while (tr != NULL){
        tmp = tr;
        tr = tr->suiv;
        free(tmp);
    }
};

void supprimerCompte(int numero){
    compte *courant= banque, *prev = NULL;
    while (courant != NULL){
        if (courant->numeroCompte == numero){
            if (prev == NULL){
                banque = courant->suiv;
            }
            else{
                prev->suiv = courant->suiv;
            }
            supprimerTransactions(courant->transaction);
            free(courant);
            printf("Le compte numéro %d a été supprimé avec succès\n",numero);
            return;
        }
        prev = courant;
        courant = courant->suiv;
    };
    printf("Le compte numéro %d n'existe pas\n",numero);

    
}

void afficherDetailsCompte(compte *compte){
    printf("Compte N°: %d\n",compte->numeroCompte);
    printf("Nom du titulaire: %s\n",compte->nomClient);
    printf("Numéro de téléphone: %ld\n",compte->nTel);
    printf("CIN N°: %ld\n",compte->CIN);
    printf("Adresse: %s\n",compte->Adresse);
    printf("Mail: %s\n",compte->mail);
    printf("Solde du compte: %f\n",compte->solde);
};

void afficherListeClients(){
    if (banque == NULL){
        printf("La liste des clients est vide\n");
        return;
    }
    printf("La liste des clients:\n");
    compte *courant = banque;
    while (courant != NULL){
        printf("Nom du client: %s    Numéro du compte: %d\n",courant->nomClient,courant->numeroCompte);
        courant = courant->suiv;
    }
}

void changeDevise(compte *compte){
    int choix;
    float montant;
    char date[20];
    int dateValide = 0;
    transaction* nouvTrans = malloc(sizeof(transaction));
    if (compte == NULL){
        printf("Compte Invalide");
        return;
    }
    while (!dateValide) {
        printf("Date du retrait (jj/mm/aaaa) : ");
        scanf("%s",date);
        getchar(); 
        if (DateEstValide(date)) {
            dateValide = 1;
        } else {
            printf("Format de date invalide. Veuillez réessayer.\n");
        }
    };
    printf("Choisir la devise:\n1.EUR\n2.USD\n3.GBP\n");
    scanf("%d",&choix);
    getchar();
    printf("Saisir le montant à extraire en TND: ");
    scanf("%f",&montant);
    getchar();
    strcpy(nouvTrans->type,"Retrait en devise");
    nouvTrans->montant = montant;
    strcpy(nouvTrans->date,date);
    nouvTrans->suiv = compte->transaction;
    compte->transaction = nouvTrans;
    compte->solde -= montant;
    switch(choix){
        case 1:
            printf("Le montant en EUR est: %f\n", montant / tauxChangeEUR_TND);
            break;
        case 2:
            printf("Le montant en USD est: %f\n", montant / tauxChangeUSD_TND);
            break;
        case 3:
            printf("Le montant en GBP est: %f\n", montant / tauxChangeGBP_TND);
            break;
    };
    printf("Le nouveau solde du client %s est: %f\n",compte->nomClient,compte->solde);
}
