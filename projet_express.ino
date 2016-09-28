int Entree_V = A0;		//entrée du signal principal
int Entree_reelle;
int V_entree; 

int Entree_Pot = A1;	// entrée du potard
int Valeur_PWM;

// ===== Ce qui sera allumé si V >= 1
int Compt_LP   = 2;		// pin pour le MOC COMPTEUR + LAMPE AC
int No230      = 3;		// pin pour le MOC No230V
int LEDvt      = 4;		// pin pour led verte
int No24       = 5; 	// pin pour le 4N35 NO 24V
int Sortie_PWM = 6; 	// pin6 pour la sortie PWM
int Gnd        = 7; 	// pin pour couper le Gnd du ventilo et du bandeau de leds

// ===== Ce qui sera déclenché si V < 1
int NF230      = 8;		// pin pour le MOC NF230V
int LP230      = 9;		// pin pour le MOC LAMPE AC
int Buzzer     = 10;	// pin pour le Buzzer
int NF24       = 11;	// pin pour le 4N35 NF 24V
int LEDrg      = 12;	// pin pour la LED rouge

void setup()
{
	for(int i=2; i<13; i++){
		pinMode(i, OUTPUT);			// initialisation de l'ensemble des pins sortantes NO (sauf pour A0 et A1)
		digitalWrite(i, LOW);
	}
	
	// ===== Allumage des Leds pour marquer le début du setup()
	digitalWrite(LEDvt, HIGH);
	digitalWrite(LEDrg, HIGH);


	pinMode(Entree_V, INPUT);		// initialisation du matos d'entrée qui déclenche le reste et simule l'entrée en Volts
	pinMode(Entree_Pot, INPUT);		// initialisation du potar utilisé pour régler le PWM
	V_entree, Entree_reelle = 0; 
	Valeur_PWM = 0;

	// ===== Extinction des Leds pour marquer la fin du setup()
	digitalWrite(LEDvt, LOW);		// Cela permet en même temps de visualiser le bon fonctionnement des LED
	digitalWrite(LEDrg, LOW);
}

void loop()
{
	LectureEntreeVolts();
	ChoixDesFonctions();
}

void LectureEntreeVolts(){
	Entree_reelle = analogRead(Entree_V);
	V_entree = map(Entree_reelle, 0, 1023, 0, 5000); 
}

void ChoixDesFonctions(){
	// ===== au dessus de 1V, on appelle la deuxième fonction
	if(V_entree > 1000){	 
		delay(700); 			// timelaps pour éviter un phénomène du ballaste
		Un_et_Plus();
	}
	// ===== au dessous de 1V, on appelle la première fonction
	else{
		Zero_a_Un();
	}
}

void Zero_a_Un()
{
	digitalWrite(Compt_LP, LOW); 					// on coupe le compteur
	digitalWrite(No230, LOW); 						// on coupe un premier relai 230VAC via un MOC3041
	digitalWrite(LEDvt, LOW); 						// on coupe la led verte
	analogWrite(Sortie_PWM, 0); 					// signal sortant de la sortie PWM à 0
	digitalWrite(No24, LOW); 						// on coupe un premier relai 24VDC via un 4N35
	digitalWrite(Gnd, LOW); 						// on coupe le Gnd du ventilo et du bandeau de leds via un BC337
	
	digitalWrite(Buzzer, HIGH); 					// on allume le buzzer
	digitalWrite(NF24, HIGH); 						// on actionne un deuxième relai 24VDC via un 4N35
	digitalWrite(LEDrg, HIGH); 						// on allume la led rouge
	digitalWrite(NF230, HIGH); 						// on actionne un deuxième relai 230VAC via un MOC3041
	digitalWrite(LP230, HIGH); 						// on actionne une lampe 230V via un MOC3041
}

void Un_et_Plus()
{
	digitalWrite(Compt_LP, HIGH); 					// on alimente le compteur horaire via un MOC3041
	digitalWrite(No230, HIGH); 						// on actionne le premier relai 230VAC via le MOC3041
	digitalWrite(LEDvt, HIGH); 						// on allume la led verte

	Valeur_PWM = analogRead(Entree_Pot); 			// lecture de la tension sur A1 réglée par le potard
	Valeur_PWM = map(Valeur_PWM, 0, 1023, 0, 255);		// map de la tension - de 0 à 5V en entrée donnent 0 à 255 en signal PWM
	analogWrite(Sortie_PWM, Valeur_PWM); 			// cmde PWM envoyée sur Sortie_PWM de 0 à 255 - signaux carrés envoyés sur un 4N35

	digitalWrite(No24, HIGH); 						// on actionne le premier relai 24VDC via le 4N35
	digitalWrite(Gnd, HIGH); 						// on ferme le circuit du Gnd du ventilo et du bandeau de leds via un BC337

	digitalWrite(Buzzer, LOW); 						// on coupe le buzzer
	digitalWrite(NF24, LOW); 						// on ouvre le deuxième relai 24VDC via le 4N35
	digitalWrite(LEDrg, LOW); 						// on coupe la led rouge
	digitalWrite(NF230, LOW); 						// on ouvre le deuxième relai 230VAC via le MOC3041
	digitalWrite(LP230, LOW); 						// on coupe la lampe 230VAC via le MOC3041
}
