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


int main(int argc, char *argv[]) {


    //Po³aczenie
    int coid = name_open("ps", NULL);

    while (1) {
        //Wpisanie danych
        int a;
        int b;
        char operation;
        char type;
//        printf("Podaj pierwsz  liczb : ");
//        scanf("%d", &a); // Wczytanie pierwszej liczby
//        printf("Podaj drug  liczb : ");
//        scanf("%d", &b);
//        printf("Podaj rodzaj operacji ");
//        scanf("%c", &operation);
//        printf("Podaj typ operacji ");
//        scanf("%c", &type);
a=11;
b=33;
operation='+';
type='C';

//Przygotowanie wiadomoœci
        struct Operation to_send;
        to_send.number_A = a;
        to_send.number_B = b;
        to_send.operation = operation;
        to_send.type = type;

        //Tablica przychodz¹ca
        struct Operation incoming_msg;

        //Wys³anie wiadomoœci
        if (MsgSend(coid, &to_send, sizeof(to_send), &incoming_msg, sizeof(incoming_msg)) == -1) {
            printf("NOT SEND\n");
        } else {
            printf("Wynik to: %d\n\n\n", incoming_msg.wynik);

        }
    }

	return EXIT_SUCCESS;

}

