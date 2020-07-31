#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define RESTART -1
#define JA -2
#define NEI -3
#define FEIL -4

int running = 1;

void toUpper(char *ord){
    while(*ord){
        *ord = toupper(*ord);
        ord++;
    }
}

int isDigit(char *streng){
    int sum = 0;
    for(int i = 0 ; i < strlen(streng); i++){
        if(!isdigit(streng[i])){
            return -1;
        }
        //sum = sum * 10 + streng[i];
    }
}

int sjekkSvar(void){
    char tekst[255];
    scanf("%s", &tekst);
    if(isDigit(tekst) != -1){
        return atoi(tekst);
    }
    toUpper(tekst);
    if(!strcmp(tekst, "NEI")){
        return NEI;
    }
    if(!strcmp(tekst, "AVSLUTT")){
        exit(0);
    }else if(!strcmp(tekst, "RESTART")){
        running = 1;
        return RESTART;
    }
    else{
        return FEIL;
    }

}

int sjekker(int *tall, char error[]){
    *tall = sjekkSvar();
    if(*tall == RESTART){
        return RESTART;
    }
    while(*tall < 0){
        printf("Ugyldig %s! Skriv kun inn positive tall: ", error);
        *tall = sjekkSvar();
    }
}

int regner(int total, int knapp, int felle, int bord,int *pEkstra){
    int mellomrom;
    
    total -= bord;
    total -= felle;
    *pEkstra = total % (knapp - 1);
    total /= (knapp - 1);
    total -= felle; 

    return total;
}

void quiz(void){
    running = 0;
    int masketall, knapper, fellemasker, ekstra, bord, maksBord, antall;
    char svar[255];

    printf("Skriv inn det totale maskeantallet: ");
    if(sjekker(&masketall, "antall masker") == RESTART) return;

    printf("Skriv inn antall knapper som skal fordeles: ");
    if(sjekker(&knapper, "antall knapper") == RESTART) return;

    printf("Hvor mange masker trengs å felles per knapp? ");
    if(sjekker(&fellemasker, "antall fellinger") == RESTART) return;
    bordloop:
    printf("Ønsker du å oppgi antall masker til ytterkantene? Skriv inn: (antall masker/NEI): ");
    bord = sjekkSvar();
    if(bord == RESTART) return;
    if(bord == NEI){
        maksBord = masketall * 0.2;
        printf("\n--------------------------------------------------------------\n");
        for(int i = 0; i <= (maksBord*2); ++i){
            regner(masketall, knapper, fellemasker, i, &ekstra);
            if(ekstra == 0){
                antall++;
                if((i%2) == 1){
                    printf("               *NB - odde mengde masker*\n");
                    printf("Forslag til lengder på hver ytterkant: %d, med 1 maske til overs\n", (i/2));
                }else{
                    printf("Forslag til lengder på hver ytterkant: %d.\n", (i/2));
                }
                printf("Du må da ha %d masker mellom hver knapp\n", regner(masketall, knapper, fellemasker, i, &ekstra));
                printf("--------------------------------------------------------------\n");
            }
            
        }
        if(!antall){
            printf("Ingen forslag med %d masker til total ytterkant\n", maksBord);
            printf("---------------------------------------\n");
        }
    }else if(bord > 0){
        printf("\n---------------------------------------\n");
        printf("Du må ha %d masker mellom hver knapp\n", regner(masketall, knapper, fellemasker, bord*2, &ekstra));
        printf("Det er %d maske(r) igjen.\n", ekstra);
        printf("---------------------------------------\n");
    }else{
        printf("Ugyldig innskrivning!\n");
        goto bordloop;
    }
    sjekkSvar();
}

int main(void){
    while(running){
        printf("\nVelkommen til knappekalkulatoren!\n");
        printf("Hvis du har skrevet inn feil kan du skrive \"Avslutt/Restart\" for å avslutte/restarte programmet.\n");
        quiz();
    }

    return 0;
}