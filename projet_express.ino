// Adresse du montage sur 123D.circuits.io où tu trouveras l'ensemble des composants nommés ! Pour cela, clique simplement sur chaque élément :)
	// https://circuits.io/circuits/2409607
// Adresse du plan sur Sketchboard
	// https://sketchboard.me/Pz0gaDj1ZIQG

/*Déclarations*/
//matériel
// source d'entrée en volt
int Entree = A0;
int Entree_reelle;	// Ce que le potard va vraiment envoyer
int V_entree;		// Les limites imposées par le produit (une entrée entre 0 et 1,86 V) ; avec cette variable, qu'importe l'entrée en volts réelle, tu auras toujours le bon ratio pour déclencher les différents élements (en dessous ou au dessus de 100V)
// Ce qui sera allumé si V >= 1
int Led_Verte = 2;
int No_220 = 3;
int Compteur_220 = 4;
int Lampe_220 = 5;
int No_24 = 6;
// Ce qui sera déclenché si V < 1
int Led_Rouge = 8;
int NF_220 = 9;
int Lampe_24 = 10;
int MOC_304X_3 = 11;
int Buzzer = 12;
int NF_24 = 13;

//pratique
int Sec=1000; //Une variable qui me permet de compter en secondes dans le reste du programme :)


void setup()
{
	for(int i=2; i<13; i++){ // initialisation de l'ensemble des pins liés en sortie (sauf pour V_entrée)
	    pinMode(i, OUTPUT);
	    digitalWrite(i, LOW);
	}
	pinMode(Entree, INPUT); // initialisation du matos d'entrée qui déclenche le reste
	V_entree, Entree_reelle = 0;
}

void loop()
{
	Entree_reelle = analogRead(Entree);
	V_entree = map(Entree_reelle, 0, 1023, 0, 186); // On mappe l'entrée électrique lu analogiquement entre 0 et 186 (pour simuler le rapport entre 0 et 1,86V)
	if(V_entree < 100){		// en dessous de 100 (1V, cf. le mappage de 0 à 186), on a la première fonction
	    Zero_a_Un();
	}
	if(V_entree >= 100){
	    Un_et_Plus();
	}
}

void Zero_a_Un()
{
	for(int i=2; i<7; i++){
	    digitalWrite(i, LOW);
	}
	for(int j=8; j<14; j++){
	    digitalWrite(j, HIGH);
	}
}

void Un_et_Plus()
{
	for(int i=2; i<7; i++){
	    digitalWrite(i, HIGH);
	}
	for(int j=8; j<14; j++){
	    digitalWrite(j, LOW);
	}
}