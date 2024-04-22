import socket
import time

UDP_IP = "192.168.1.140"  # Adresse IP du serveur Arduino
UDP_PORT = 12345           # Port utilisé par le serveur Arduino

# Création du socket UDP
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

print("En attente de données...")

# Ouverture du fichier en mode écriture binaire
with open('received_data.txt', 'wb') as f:
    start_time = time.time()  # Enregistrement du temps de début
    while True:
        # Réception des données
        data, addr = sock.recvfrom(20480)  # Taille maximale du paquet en octets
        print("Données reçues :", data.decode('utf-8'))

        # Écriture des données dans le fichier
        f.write(data)

        # Vérifier si les données reçues contiennent "FIN"
        if "FIN" in data.decode('utf-8'):
            print("Fin de la transmission, fermeture du fichier.")
            end_time = time.time()  # Enregistrement du temps de fin
            break  # Sortir de la boucle si "FIN" est reçu

# Calcul du temps écoulé
elapsed_time = end_time - start_time
print("Temps écoulé :", elapsed_time, "secondes")

# Fermeture du socket
sock.close()
