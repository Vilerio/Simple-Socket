#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    const char* message = "Bonjour, serveur !";
    char buffer[1024] = {0};
       
    // Création du socket client
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Erreur de création du socket \n");
        return -1;
    }
       
    memset(&serv_addr, '0', sizeof(serv_addr));
       
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9876);
       
    // Conversion de l'adresse IP en format binaire
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\n Adresse invalide / non prise en charge \n");
        return -1;
    }
       
    // Connexion au serveur
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\n Connexion échouée \n");
        return -1;
    }
       
    // Envoi de la chaîne de caractères au serveur
    send(sock, message, strlen(message), 0 );
    printf("Chaîne de caractères envoyée au serveur\n");

    // Lecture de la réponse du serveur
    valread = read(sock, buffer, 1024);
    printf("%s\n",buffer );

    // Fermeture de la connexion
    close(sock);
    return 0;
}
