#include <SD.h>
#include <SPI.h>

const int chipSelect = 53;

void setup() {
  Serial.begin(9600);
  pinMode(chipSelect, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("Échec de l'initialisation de la carte SD !");
    return;
  }
}

void loop() {
  if (Serial.available()) {
    String commande = Serial.readStringUntil('\n');
    if (commande == "GET_DATA") {
      lireDernieresLignes();
    }
    else if(commande.startsWith("get_value_")){
      Serial.println("je suis ici");
      String dateRecherchee = commande.substring(10);
      chercherLigneParDate(dateRecherchee);
    }
  
  }
}

void lireDernieresLignes() {
  unsigned long tempsDebut = millis();

  File fichier = SD.open("DATA1.CSV");
  if (!fichier) {
    Serial.println("Erreur lors de l'ouverture du fichier !");
    return;
  }

  long tailleFichier = fichier.size();
  long position = tailleFichier;
  int lignesLues = 0;

  while (position--) {
    fichier.seek(position);
    char caractere = fichier.read();

    if (caractere == '\n' || position == 0) {
      String ligne = fichier.readString();
      Serial.println(ligne);
      lignesLues++;
      if (lignesLues >= 5) {
        break;
      }
    }
  }
  
  fichier.close();
  
  unsigned long tempsFin = millis();
  unsigned long tempsEcoule = tempsFin - tempsDebut;
  Serial.print("Temps écoulé : ");
  Serial.print(tempsEcoule);
  Serial.println(" ms");
}

String chercherLigneParDate(String dateRecherchee) {
    unsigned long tempsDebut = millis();

  File fichier = SD.open("DATA1.CSV");
  if (!fichier) {
    Serial.println("Erreur lors de l'ouverture du fichier !");
    return "";
  }

  long tailleFichier = fichier.size();
  long position = tailleFichier;
  String ligneTrouvee = "";
  int iterations =0;

  while (position-- && iterations<10) {
    fichier.seek(position);
    char caractere = fichier.read();

    if (caractere == '\n' || position == 0) {
      String ligne = fichier.readStringUntil('\n');
      if (ligne.indexOf(dateRecherchee) != -1) {
        ligneTrouvee = ligne;
        break;
      }
    }
  }

  fichier.close();

  if (ligneTrouvee == "") {
    Serial.println("Aucune ligne contenant la date recherchée n'a été trouvée !");
  }
  Serial.println(ligneTrouvee);
  

  unsigned long tempsFin = millis();
  unsigned long tempsEcoule = tempsFin - tempsDebut;
  Serial.print("Temps écoulé : ");
  Serial.print(tempsEcoule);
  Serial.println(" ms");
  int tailleEnOctets = ligneTrouvee.length()*sizeof(char);
  Serial.print("Taille de la ligne trouvée en octets: ");
  Serial.println(tailleEnOctets);


  return ligneTrouvee;

}
