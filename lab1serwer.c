#include <stdlib.h>
#include <stdio.h>
#include <sys/neutrino.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <string.h>

struct Operation{
	char type;
	int number_A;
	int number_B;
	char operation;
	int wynik;
};

struct avaliable_services{
    //struktura która jest tworzona przy rejestracji nowego usługodawcy
    char operation;
    int rcvid;
};

int rcvid_klient;
struct avaliable_services services_online[4]; //tabica tych struktur, mowi jakie mamy aktywne uslugi


// Funkcja dodaj�ca operacj� do tablicy us�ug
void addOperationToServices(struct Operation op, int rcvid) {
    // Sprawdzenie, czy tablica us�ug nie jest pe�na
    int i;
    for (i = 0; i < 4; i++) {
        //sprawdzenie czy jest miejsce w tablicy i czy jest to typ rejesracji
        if (services_online[i].type == '\0'&& op.type=='R' ) {
            // Dodanie operacji do tablicy us�ug
            services_online[i].operation=op.operation;
            services_online[i].rcvid=rcvid;
            //type_services[i] = op.operation;
            printf("Dodano operacj %c\\n",services_online[i].operation);
            break;
        }
    }

    // Sprawdzenie, czy tablica us�ug jest pe�na
    if (i == 4) {
        printf("Tablica us�ug jest pe�na. Nie mo�na doda� nowej operacji. Lub to nie jest operacja rejestracji.\n");
    }
}
//Sprawdzenie czy operacja jest dostepna, czy us�ugodawca jest zalogowany
int isOperationInServicesOnline(char operation) {
	int i;
    for(i = 0; i < 4; i++) {
        if (services_online[i].operation == operation) {
            return 1; // Znaleziono operacj� w tablicy us�ug
        }
    }
    return 0; // Nie znaleziono operacji w tablicy us�ug
}

struct  Operation sendToService(struct Operation struct_from_client,name_attach_t Structura){
    //znalezienie rcvid serwisu, wysłanie rplay do serwisu z strukturą od klienta
}
    int i;
    int rcvidService;
    struct  Operation fromService;
    for(i = 0; i < 4; i++) {
        if (services_online[i].operation == struct_from_client.operation) {
            rcvidService = services_online[i].rcvid;// Znaleziono operacj� w tablicy us�ug
            MsgReply(rcvidService,1,&struct_from_client,sizeof(struct_from_client));
            printf("Wyslano do uslugodawcy zadanie");

            //czekanie na odpowiedz i przypisanie nowego rcvid ale nie wiem czy trza
            services_online[i].rcvid=MsgReceive(Structura->chid,&fromService,sizeof(fromService),NULL);
        }
}


int main(int argc, char *argv[]) {


    //Kanał dla serwisów
	name_attach_t *Structura_services;
	Structura_services = name_attach(NULL,"service",0);
    //Dodanie 4 serwisantów, bedzie czekac aż 4 sie zaloguje, trzeba by delaya ustawić i po czasie oczekiwnie jak sie nie zgłosi idzie dalej po prstu ale nie wiem na 100%
    int i;
    for (i = 0; i < 4; i++) {
        struct Operation ServiceR;
        int rcvid_service;
        rcvid_service=MsgReceive(Structura_services->chid,&ServiceR,sizeof(ServiceR),NULL);
        addOperationToServices(ServiceR,rcvid_service);
    }
    //jeden klient
    name_attach_t *Structura;
    Structura = name_attach(NULL,"ps",0);// Pytanie czy to w petli while tez musi byc czy otwiera kanał dla każdego

    while(1){
        struct Operation struct_from_client;

        rcvid_klient = MsgReceive(Structura->chid,&struct_from_client,sizeof(struct_from_client),NULL);
        printf("Klient przysyla wiadomosc");


    //Sprawdzenie czy us�uga jest dost�pna to co klient wys�a�:
    if(isOperationInServices(struct_from_client.operation)){
        struct Operation struct_to_Client;
        //funkcja przyjmuje dane co przysłał klient i struktureKanału a zwraca strukture danych policzonych dla klienta
        struct_to_Client = sendToService(struct_from_client,Structura_services) //tu może apersand ???

        MsgReply(rcvid_klient,1,&struct_to_Client,sizeof(struct_to_Client));
        printf("Wyslano do klienta odpowiedz")
    }
    else {
        printf("Nie znaleziono takiego uslugodawcy")
    }

}

	return EXIT_SUCCESS;
}

