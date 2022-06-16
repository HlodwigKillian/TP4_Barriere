//Importation de la librairie pour les servomoteurs.
#include<Servo.h>;


/*Par défaut le feu est rouge et la barrière baissée
lors de l'appuie sur le bouton, la barrière s'ouvre
une fois la barrière ouverte, le feu rouge s'éteint
le feu vert s'allume pour 5 secondes, puis 
la barrière se referme et le feu rouge est le seul a
rester allumee.*/

// ! Dans mon code je déclare des fonctions, dans CodeCast 
//cela ne fonctionne pas. !

//Déclaration de l'objet servomoteur.
Servo servomoteur;

//Déclaration de variables avec leurs broches respectives.
int feuRouge = 3; //Led rouge, broche 3.
int feuVert = 4; //Led verte, broche 4.
int bouton = 2; //Bouton poussoir, broche 2.

//Déclaration de la variable pour la position du servomoteur.
int position = 0;
//Déclaration d'une variable pour la pression sur le bouton.
int appel = false;

void setup()
{
  //Ouverture de la connection série.
  Serial.begin(9600);
  //Spécification des entrée et sorties.
  pinMode(feuRouge, OUTPUT);
  pinMode(feuVert, OUTPUT);
  pinMode(bouton, INPUT);
  //Feu rouge allumé.
  digitalWrite(feuRouge, HIGH);
  //Spécifie l'attache du servomoteur en broche 9.
  servomoteur.attach(9);
  //Initialise le servomoteur en position 0 degré.
  servomoteur.write(0); 
}

void loop()
{
  //Boucle qui garde la barrière fermée, tant
  //que le bouton n'est pas pressé.
  while(appel == false)
  {
    //Si la position est supérieure à 0 degré, la barrière se ferme.
    if(position > 0)
    {
      Serial.println("Fermeture barriere");
      fermetureBarriere();
    }
    appel = digitalRead(bouton);
  }  
  Serial.println("Bouton appuye");
  ouvertureBarriere();
}

void fermetureBarriere()
{
  digitalWrite(feuRouge, HIGH); //Feu rouge allumé.
  digitalWrite(feuVert, LOW); //Feu vert éteint.
  //On commence à 90 degrés pour arriver à 0 degré.
  for(position = 90; position >= 0; position--)
  {
    servomoteur.write(position);
    delay(15);
  }
  Serial.print("Barriere fermee a ");
  Serial.print(servomoteur.read());
  Serial.println(" degre.");
}

void ouvertureBarriere()
{  
  //On part de 0 dégré pour arriver à 90 degrés.
  for(position = 0; position <= 90; position++)
  {
    servomoteur.write(position);
    delay(15);
  }
  digitalWrite(feuRouge, LOW);
  digitalWrite(feuVert, HIGH);
  Serial.print("Barriere ouverte a ");
  Serial.print(servomoteur.read());
  Serial.println(" degres.");
  delay(5000); //Attente de 5 secondes.
  appel = false; //Annule l'appel au cas ou.
}