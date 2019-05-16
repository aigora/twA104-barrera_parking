#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define N 3
#include<stdio.h>
#include<ctime>
#include<vector>
#include<string.h>
struct PARKING { // Declaraci�n de la estructura de un coche cuando quiera entrar al parking
	char matricula[8];
	int horaentrada;
	int horasalida;
	char dni[10];
	char nombre[10];
	int minentrada;
	int minsalida;
	char matriculasalida[10];
};
int tiempo(int, int, int, int);
float pago(int);
int hora(int *);
void entrada(void);
void salida(void);
void cambio(float);

int hora(int *p) {
	int a;
	time_t now = time(0);
	tm * time = localtime(&now);
	a = time->tm_hour;
	*p = time->tm_min;

	return(a); //Funcion que devuelve la hora y los minutos en el presente.
}
int tiempo(int a, int b, int c, int d) {
	int x, y, tiempo;
	x = c - a;
	y = d - b;
	tiempo = (x * 60) + y;
	return(tiempo); //Esta funcion devuelve el tiempo total en minutos que ha estado el coche en el parking.
}
float pago(int x) {
	//5 euros el minuto si esta mas de 3 minutos se le cobra un 20% mas.
	float v;
	if (x > 3) {
		v = 5 * x;
		v = v * 1.20;
	}
	else {
		v = 5 * x;
	}
	return (v); //Esta funci�n devuelve el valor de 'v' que corresponde con el precio a pagar seg�n el tiempo que haya estado en el parking
}

int main() {
	int m; // m sera la opcion a elegir del menu del parkin, si no corresponde con ninguna, te la pedir� de nuevo.
	int plazas = N; //Numero de plazas disponibles definidas por #define N 3 que significa que hay 3 plazas 
	do {
		printf("Parking publico\nPlazas libres: %d\nIntroduzca 0 para entrar\nIntroduzca 1 para salir\nIntroduzca 2 para salir del programa\nOpcion:  ", plazas);
		scanf("%d", &m);

		if ((m == 0) && (plazas == 0)) { //Si m==0 (opci�n de entrar en el parking) y plazas==0 (no hay plazas) nos dir� que no hay plazas disponibles.
			printf("Lo sentimos no hay plazas disponibles vuelva mas tarde\n"); //No se puede entrar en el parking
			system("pause");
		}

		if ((m == 0) && (plazas <= N) && (plazas != 0)) { //Si le damos a la opci�n de entrar y plazas!=0 nos dejara entrar.
			entrada(); // Llamada a la funci�n entrada.
			plazas--; //Una vez hayamos entrado,restar� uno al numero de plazas disponibles. 

		}


		if ((m == 1) && (plazas < N) || (m == 1) && (plazas == 0)) { //Si m==1 (salir del parking) y hay alguna plaza ocupada,el coche sale
			salida(); //Llamada a la funci�n salida
			plazas++; //Al salir el numero de plazas disponibles aumentar� 1.

		}
		if ((m != 1) && (m != 0) && (m != 2)) { //Si se introduce una opci�n distinta de 0,1,2 te dice que el numero introducido es incorrecto y te llevar� al inicio del men�.
			printf("ATENCION NUMERO INCORRECTO\n");
			system("pause");
		}
		system("cls"); // Metodo para limpiar la pantalla de la aplicaci�n.

	} while (m != 2); //Cuando introduzcamos la opci�n '2' el programa se cerrara


}
void entrada(void) {
	struct PARKING coche;
	FILE *pf;
	errno_t err;
	int a;
	int i = 0, aux = 1, numero = 0, letra = 0, v;
	int t;
	float p;
	printf("PARKING\n\n");
	printf("Nombre: ");
	gets_s(coche.nombre); //Nombre del propietario del coche
	gets_s(coche.nombre);
	do {
		printf("DNI: ");
		gets_s(coche.dni);
		v = strlen(coche.dni); //DNI del conductor
		for (i = 0; i < v; i++) {
			if ((coche.dni[i] <91) && (coche.dni[i] >64)) { //Si el simbolo esta entre la 'A' y la 'Z'
				letra++; //Se a�ade la letra
			}
			if ((coche.dni[i] <58) && (coche.dni[i] >47)) { //Si el simbolo esta entre el '0' y el '9'
				numero++; //Se a�ade el numero
			}
		}
		if ((numero != 8) && (letra != 1)) { //Si no se introducen 8 numeros y una letra te pide introducir el dni de nuevo
			printf("ERROR INTRODUZCA DE NUEVO EL DNI\n");
		}
	} while ((numero != 8) && (letra != 1)); //Hasta que no se introduzca correctamente (8 n�meros y una letra) no sale del bucle

	v = 0, numero = 0; letra = 0;
	do {
		printf("Matricula: ");
		gets_s(coche.matricula);
		v = strlen(coche.matricula); //Matricula del conductor
		for (i = 0; i < v; i++) {
			if ((coche.matricula[i] <91) && (coche.matricula[i] >64)) { //Se a�ade la letra siempre que este comprendida entre 'A' y 'Z'
				letra++;
			}
			if ((coche.matricula[i] <58) && (coche.matricula[i] >47)) { //Se a�ade el numero si esta entre '0' y '9'
				numero++;
			}
		}
		if ((numero != 4) && (letra != 3)) { //Si no se introducen 4 numeros y 3 letras se pedira que se vuelva a introducir la matricula
			printf("ERROR INTRODUZCA DE NUEVO LA MATRICULA\n");
		}
		else {
			printf("Datos introducidos correctamente.\n");
			system("pause");
		}
	} while ((numero != 4) && (letra != 3)); //Saldra del bucle cuando se introduzca la matricula correctamente (4 numeros y 3 letras)
	coche.horaentrada = hora(&coche.minentrada);
	err = fopen_s(&pf, "PARKING.txt", "a"); //Abre el fichero PARKING (a�adir elementos)
	if (err)
		printf("No se pudo abrir el archivo");
	else
	{
		fprintf(pf, "%s %s %s %d:%d\n", coche.nombre, coche.dni, coche.matricula, coche.horaentrada, coche.minentrada); //Escribe el nombre del usuario.
		fclose(pf);
	}
}
void salida(void) {
	FILE *pt;
	struct PARKING coche;
	errno_t err;
	int t;
	float p;
	printf("Introduce tu matricula de salida: ");
	gets_s(coche.matriculasalida); //Matricula de salida
	gets_s(coche.matriculasalida);
	err = fopen_s(&pt, "PARKING.txt", "r"); //Abre el fichero PARKING (modo lectura)
	if (err)
		printf("No se pudo abrir el archivo");
	else
	{
		while (!feof(pt)) { //Lee todo el fichero
			fscanf(pt, "%s %s %s %d:%d\n", coche.nombre, coche.dni, coche.matricula, &coche.horaentrada, &coche.minentrada); //Lee los datos del fichero PARKING
			if (strcmp(coche.matriculasalida, coche.matricula) == 0) { //Compara la matricula de salida con la matricula de entrada para calcular el tiempo que ha permanecido en el parking.
				coche.horasalida = hora(&coche.minsalida);
				t = tiempo(coche.horaentrada, coche.minentrada, coche.horasalida, coche.minsalida); //Calcula el tiempo que ha estado en el parking
				p = pago(t); //Funci�n que indica la cantidad a pagar.
				printf("%s debe pagar %.2f euros\n\n", coche.nombre, p);
				cambio(p); //Funci�n que indica el cambio.
				printf("\n\n");
				printf("GRACIAS POR SU VISITA\nVUELVA PRONTO\n");
				system("pause");
			}
		}
		fclose(pt);
	}
}
void cambio(float p) {
	int credito, cred = 0;
	float cambio;
	printf("La maquina de cobro solo acepta billetes\nBilletes aceptados: 5 euros, 10 euros, 20 euros, 50 euros\n");
	do {
		do {
			printf("Introduce credito: ");
			scanf_s("%d", &credito);
			if ((credito != 5) && (credito != 10) && (credito != 20) && (credito != 50)) { //Solo se acepta cr�dito de 5,10,20 o 50 euros
				printf("CREDITO INCORRECTO\n");
			}
		} while ((credito != 5) && (credito != 10) && (credito != 20) && (credito != 50)); //Se repite el bucle hasta que no se introduzca el cr�dito que se acepta
		cred += credito; //Se suma la cantidad total billetes
		printf("\nCredito: %d\n", cred);
	} while (cred < p); //No se sale del bucle hasta que el cr�dito introducido sea superior al precio a pagar
	if (cred > p) {
		cambio = cred - p; //Cantidad de dinero a devolver
		printf("Cambio: %.2f euros", cambio);
	}

}