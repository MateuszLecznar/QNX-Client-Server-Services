#include <stdlib.h>
#include <stdio.h>
#include <sys/neutrino.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <string.h>

//int
struct Operation{
	char type;
	int number_A;
	int number_B;
	char operation;
	int wynik;
};

struct Operation plus_rej;



//Struktura kt�ra otrzymujemy
struct Operation plus_receive;

int main(int argc, char *argv[]) {
	plus_rej.operation = '+';
	plus_rej.type='R';

	int coid=name_open("service",NULL);

	//W p�tli bedzie wysy�a� i odbiera� zadania przy czym pierwszy raz wysy�a rejestracje
while(1) {
    if (MsgSend(coid, &plus_rej, sizeof(plus_rej), &plus_receive, sizeof(plus_receive)) == -1) {
        printf("NOT SEND\n");
    } else {

        if (plus_receive.type == 'C') {
            plus_rej.wynik=plus_receive.number_A+plus_receive.number_B;

            plus_rej.type='W';


        }
    }

}
	return EXIT_SUCCESS;

}

