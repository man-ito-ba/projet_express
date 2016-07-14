// Adresse du montage sur 123D.circuits.io où tu trouveras l'ensemble des composants nommés ! Pour cela, clique simplement sur chaque élément :)
	// https://circuits.io/circuits/2435021
// Adresse du plan sur Sketchboard
	// https://sketchboard.me/Pz0gaDj1ZIQG
// Adresse des MAJ que tu m'as donné sur Asana pour effectuer cette nouvelle version :
	// https://app.asana.com/0/inbox/89529756025108/151877453969690/154799563809514

/*Déclarations*/
//matériel
// source d'entrée en volt
const int Entree_V = A3;
int Entree_reelle;	// Ce que le potard va vraiment envoyer
int V_entree;		// Variable utilisée dans la fonction map(), représentant les limites imposées par le produit (une entrée entre 0 et 1,86 V) ; avec cette variable, qu'importe l'entrée en volts réelle, tu auras toujours le bon ratio pour déclencher les différents élements (en dessous ou au dessus de 100V).

// Potar pour modifier le PWM
const int Potar_PWM = A4;	// Potar qui fait varier la fréquence du signal PWM
int Valeur_PWM;				// Variable mémorisant la valeur du potar PWM

// Ce qui sera allumé si V >= 1
const int No220_24 = A0;				// pin pour le No_220 et No_24
const int Lampe_Compteur_220 = 10;		// pin pour la lampe et le compteur
const int Sortie_PWM = 11;				// pin pour la sortie PWM, cette sortie 11 est adaptée car elle peut être utilisée pour du PWM
// Ce qui sera déclenché si V < 1
const int NF_220_24 = 12;						// pin pour le NF_220 et NF_24
const int Buzzer_Lampe_24_MOC_304X_3 = 13;		// pin pour le Buzzer, la Lampe_24, et le MOC 304X 3

//pratique
const int Sec=1000; //Une variable qui me permet de compter en secondes dans le reste du programme :)


void setup()
{
	for(int i=10; i<14; i++)
	{ // initialisation de l'ensemble des pins liés en sortie (sauf pour V_entrée)
	    pinMode(i, OUTPUT);
	    digitalWrite(i, LOW);
	}
	pinMode(No220_24, OUTPUT);
	digitalWrite(No220_24, LOW);
	pinMode(Entree_V, INPUT); 					// initialisation du matos d'entrée qui déclenche le reste et simule l'entrée en Volts
	pinMode(Potar_PWM, INPUT);					// initialisation du potar utilisé pour régler le PWM
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
	digitalWrite(No220_24, LOW);
	digitalWrite(Lampe_Compteur_220, LOW);
	digitalWrite(Sortie_PWM, LOW);

	digitalWrite(NF_220_24, HIGH);
	digitalWrite(Buzzer_Lampe_24_MOC_304X_3, HIGH);
}

void Un_et_Plus()
{
	digitalWrite(No220_24, HIGH);
	digitalWrite(Lampe_Compteur_220, HIGH);
	Valeur_PWM = analogRead(Potar_PWM);
	analogWrite(Sortie_PWM, Valeur_PWM/4);

	digitalWrite(NF_220_24, LOW);
	digitalWrite(Buzzer_Lampe_24_MOC_304X_3, LOW);
}