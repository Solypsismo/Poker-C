#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SUITS 4
#define FACE 13
#define CARDS 52

typedef struct{
	char segno[10];
	char faccia[10];	
}carta;

void crea(carta *);

void distribuisci(carta *, carta *, int);
int controllo_pesca(int * , int, int);
int punteggio(carta *);
	int coppia(int *x);
	int tris(int *x);
	int poker(int *x);
	int colore(int *x);
	int doppia_coppia(int *x);
	int scala(int *x);

void sostituzione(carta *, carta *, int *, carta*);
void vincitore(int, int);
void stampa_mano(carta *x);

const char *segni[4] = {"Picche", "Fiori", "Quadri", "Cuori"};
const char *facce[13] = {"Asso", "Due", "Tre", "Quattro", "Cinque", "Sei", "Sette", "Otto", "Nove", "Dieci", "Jack", "Regina", "Re"};
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	srand(time(NULL));
	
	carta mazzo[CARDS];
	
	crea(mazzo);
	
	carta casa[5];
	carta avversario[5];
	
	for(int i = 0; i< 5; i++)	
		distribuisci(mazzo, casa, i);
	puts("CASA :");
	stampa_mano(casa);
	int punt_casa = punteggio(casa);
	
	
	for(int i = 0; i < 5; i++)
		distribuisci(mazzo, avversario, i);
	puts("\n\nAVVERSARIO :");
	stampa_mano(avversario);
	int punt_avv = punteggio(avversario);
	
	sostituzione(mazzo, casa, &punt_casa, avversario);
	
	vincitore(punt_casa, punt_avv);
	
	system("pause");
	return 0;
}

void crea(carta *mazzo){
	
	int k = 0;
	for(int i = 0; i < SUITS; i++){
		for(int j = 0; j < FACE; j++){
			strcpy(mazzo[k].faccia, facce[j]);
			strcpy(mazzo[k].segno, segni[i]);	
			k++;
		}
	}
	
}

void distribuisci(carta* mazzo, carta* giocatore, int x){
	
	static int carte_pescate[52] = {-1};
	static int indice = 0;
	
	int pesca;
			
	do{
		pesca = rand() % CARDS;
		giocatore[x] = mazzo[pesca];
		carte_pescate[indice] = pesca;
		 	
	}while(controllo_pesca(carte_pescate, pesca, indice) == 1);
			
	indice++;	
}

int controllo_pesca(int* x, int card, int indice){
	
	for(int i = 0; i<CARDS; i++){
		if(i != indice){
			if(card == x[i]){
				return 1;
			}
		}	
	}
	return 0;
}

void stampa_mano(carta *x){
	
	for(int i = 0; i<5; i++){
		printf("|%s di %s| ", x[i].faccia, x[i].segno);
	}
	printf("\n");
}

int punteggio(carta *giocatore){
	
	int vet_facce[13] = {0};
	
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 13; j++){
			if(( strcmp(giocatore[i].faccia, facce[j])) == 0){
				vet_facce[j]++;
				j = 14;
			}
		}
	}
	
	int vet_colore[4] = {0};
	
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 4; j++){
			if(( strcmp(giocatore[i].segno, segni[j])) == 0){
				vet_colore[j]++;
			}
		}
	}
	
	if(colore(vet_colore) == 1){
		puts("colore");
		return 6;
	}else if(doppia_coppia(vet_facce) == 1){
		puts("doppia coppia");
		return 2;
	}else if(scala(vet_facce) == 1){
		puts("scala");
		return 5;
	}else if(coppia(vet_facce) == 1 && tris(vet_facce) == 1){
		puts("full");
		return 7;
	}else if(tris(vet_facce) == 1){
		puts("tris");
		return 3;
	}else if(poker(vet_facce) == 1){
		puts("poker");
		return 4;
	}else if(coppia(vet_facce) == 1){
		puts("coppia");
		return 1;
	}else{
		puts("nulla");
		return 0;
	}

}

int coppia(int *x){
	for(int i = 0; i < 13; i++){
		if(x[i] == 2){
			return 1;
		}
	}
	return 0;
}

int tris(int *x){
	for(int i = 0; i < 13; i++){
		if(x[i] == 3){
			return 1;
		}
	}
	return 0;
}

int poker(int *x){
	for(int i = 0; i < 13; i++){
		if(x[i] == 4){
			return 1;
		}
	}
	return 0;	
}

int colore(int *x){
	for(int i=0; i<4; i++){
        if(x[i] == 5){
            return 1;
        }
    }
    return 0;
}

int doppia_coppia(int *x){
	int fl = 0;
	for(int i = 0; i < 13; i++){
		if(x[i] == 2){
			fl++;
		}
	}
	if(fl == 2){
		return 1;
	}
	return 0;
}

int scala(int *x){
	int vet[] = {0, 1, 2, 3, 4};

    for(int i = 0; i < 9 ; i++) { // 9 volte perch� secondo il calcolo che ho fatto sul foglio se scorriamo di 5 in 5 un vettore da 13 elementi faremo 9 giri
        for (int j = 0; j < 5; j++) {
            if(x[vet[j]] == 0){
                /*scorre i primi 5 elementi del vettore nel quale sono contenute tutte le carte trovate
               con il numero di volte che sono state trovate, e controlla che ogni posizione non sia nulla,
               se anche solo una posizione consecutiva � nulla allora interrompe il ciclo*/
                break;
            }else{
                if(j == 5-1){ // se e' arrivato all'ultimo giro del ciclo senza mai interromperlo vuol dire che ha trovato una scala dunque la funzione pu� restituire 1
                    return 1;
                }
            }
        }

        for(int j = 0; j<5; j++){
            vet[j]++;
        }
    }

    return 0;
}

void vincitore(int x, int y){
	
	if(x == y){
		puts("\npareggio");
	}else if(x > y){
		puts("\nvince la casa");
	}else if(x < y){
		puts("\nvince l'avversario");
	}
	
}

void sostituzione(carta* mazzo, carta* giocatore, int* punt, carta* avversario){
	printf("\n\nDesideri cambiare le tue carte ? : ");
	int ris = 0;
	scanf("%d", &ris);
	if(ris == 1){
		system("cls");
		printf("\nmano precedente :");
		stampa_mano(giocatore);
		printf("\n\n");
		printf("quante carte desideri cambiare ? (max. 3 carte) : ");
		int num_carte = 0;
		scanf("%d", &num_carte);
		printf("\nquali ? : ");
		int carte_da_cambiare[3];
		for(int i = 0; i < num_carte; i++){
			printf("\ncarta %d : ", i+1);
			scanf("%d", &carte_da_cambiare[i]);
		}
		if(num_carte > 0 && num_carte <4){
			for(int i = 0; i < num_carte; i++ )
				distribuisci(mazzo, giocatore, carte_da_cambiare[i]-1);
			puts("CASA :");
			stampa_mano(giocatore);
			*punt = punteggio(giocatore);
			
			puts("\n\nAVVERSARIO :");
			stampa_mano(avversario);
			punteggio(avversario);
		}
	}
}
