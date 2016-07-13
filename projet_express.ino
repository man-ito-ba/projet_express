// Adresse du montage sur 123D.circuits.io où tu trouveras l'ensemble des composants nommés ! Pour cela, clique simplement sur chaque élément :)
	// https://circuits.io/circuits/2435021
// Adresse du plan sur Sketchboard
	// https://sketchboard.me/Pz0gaDj1ZIQG
// Adresse des MAJ que tu m'as donné sur Asana pour effectuer cette nouvelle version :
	// https://app.asana.com/0/inbox/89529756025108/151877453969690/154799563809514

/*Déclarations*/
//matériel
// source d'entrée en volt
const int Entree_V = A0;
int Entree_reelle;	// Ce que le potard va vraiment envoyer
int V_entree;		// Les limites imposées par le produit (une entrée entre 0 et 1,86 V) ; avec cette variable, qu'importe l'entrée en volts réelle, tu auras toujours le bon ratio pour déclencher les différents élements (en dessous ou au dessus de 100V)

// Potar pour modifier le PWM
const int Potar_PWM = A1;	// Potar qui fait varier la fréquence du signal PWM
int Valeur_PWM;

// Ce qui sera allumé si V >= 1
const int LedVerte = 2;
const int No_220_24 = 3;			// pin pour le No_220 et No_24
const int Lampe_Compteur_220 = 4;	// pin pour la lampe et le compteur
const int Sortie_PWM = 5;
// Ce qui sera déclenché si V < 1
const int LedRouge = 7;
const int NF_220_24 = 8;						// pin pour le NF_220 et NF_24
const int Buzzer_Lampe_24_MOC_304X_3 = 9;		// pin pour le Buzzer, la Lampe_24, et le MOC 304X 3

//pratique
const int Sec=1000; //Une variable qui me permet de compter en secondes dans le reste du programme :)


void setup()
{
	for(int i=2; i<9; i++)
	{ // initialisation de l'ensemble des pins liés en sortie (sauf pour V_entrée)
	    pinMode(i, OUTPUT);
	    digitalWrite(i, LOW);
	}
	pinMode(Entree_V, INPUT); // initialisation du matos d'entrée qui déclenche le reste
	pinMode(Potar_PWM, INPUT);
	V_entree, Entree_reelle, Valeur_PWM = 0;
}

void loop()
{
	Entree_reelle = analogRead(Entree_V);
	V_entree = map(Entree_reelle, 0, 1023, 0, 186); // On mappe l'entrée électrique lu analogiquement entre 0 et 186 (pour simuler le rapport entre 0 et 1,86V)
	if(V_entree < 100)
	{		// en dessous de 100 (1V, cf. le mappage de 0 à 186), on a la première fonction
	    Zero_a_Un();
	}
	if(V_entree >= 100)
	{		// au dessus de 100 (1V), on appelle la deuxième fonction
	    Un_et_Plus();
	}
	delay(10);
}

void Zero_a_Un()
{
	for(int i=2; i<6; i++){
	    digitalWrite(i, LOW);
	}
	for(int j=7; j<10; j++){
	    digitalWrite(j, HIGH);
	}
}

void Un_et_Plus()
{
	for(int i=3; i<6; i++)
	{
	    digitalWrite(i, HIGH);
	}
	for(int j=7; j<10; j++)
	{
	    digitalWrite(j, LOW);
	}
	int Valeur_PWM = analogRead(Potar_PWM);
	analogWrite(LedVerte, Valeur_PWM/4);
}