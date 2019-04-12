#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
using namespace std;


struct matriz {
	double matriz[10][10];
	int I;
	int J;
}; typedef struct matriz Matriz;

void AGAMAT(){
	cout << " _______________________________________" << endl
		<< "|					|" << endl
		<< "|		AGAMAT			|"	<< endl 
		<< "|_______________________________________|" << endl;
}

void InicializarMatriz (Matriz & A) {
	
	int i=0, j=0;
	A.I = 0;
	A.J = 0;
	while(i < 10){
		j=0;
		while(j < 10){
			A.matriz[i][j] = 0;
			j++;
		}
		i++;
	}
}

void MostrarMatriz(Matriz M, char N){
	
	// M: Matriz; N: Identificador de matriz
	
	int i=1, j=1;

	
	char opcion;
	do{
		system ("cls");
		AGAMAT();
		cout << "		MATRIZ " << char(N) << ":" << endl;
		
		while(i <= M.I){
			j=1;
			cout << "	";
			while(j<=M.J){
				cout << " " << M.matriz[i][j];
				j++;
			}
			cout << endl;
			i++;
		}
		cout << endl << "	1.Volver" << endl;
		opcion = getch ();
	}while(opcion != '1');
}

Matriz TranspuestaMatriz(Matriz Ai){
	//Devuelve la transpuesta de Ai
	Matriz Ci;
	InicializarMatriz(Ci);
	Ci.I = Ai.J;
	Ci.J = Ai.I;
	
	int i=1, j=1;
	while(i <= Ci.I){
		j=0;
		while(j <= Ci.J){
			
			Ci.matriz[i][j] = Ai.matriz[j][i];
			j++;
		}
		i++;
	}
	
	return Ci;
}

Matriz MenorMatriz (Matriz Ai, int I, int J){
	//Devuelve la matriz menor a la matriz dada, sin las filas dadas
	Matriz Ci;
	Ci.I = (Ai.I - 1);
	Ci.J = (Ai.J - 1);
	int i=1, j=1, a=1, b=1; 
	
	while (i <= Ai.I){
		j=1;
		b=1;
		if (i != I){
			
			while (j <= Ai.J){
				
				if (j != J){
					
					Ci.matriz[a][b] = Ai.matriz[i][j];
					b++;
				}
				j++;
			}
			a++;
		}
		i++;
	}
	
	return Ci;
}

int DeterminanteMatriz (Matriz Ai){
	//Devuelve un entero
	system ("cls");
	AGAMAT();
	int D = 0;
	if (Ai.I == Ai.J){
		
		switch(Ai.I){
			
		case 0:{
			cout << "Error: es una matriz nula";
			char opcion;
			do{
				cout << endl << "	1.Volver" << endl;
				opcion = getch ();
			}while(opcion != '1');
		}break;
		
		case 1: D = Ai.matriz[1][1];
		break;
		
		case 2: D = ( ( Ai.matriz[1][1] *  Ai.matriz[2][2] ) - ( Ai.matriz[1][2] *  Ai.matriz[2][1] ) );
		break;
		
		default:
			
			int i=1;
			while(i <= Ai.I){
				
				D += ( ( Ai.matriz[i][1] * pow((-1),(i+1)) ) * DeterminanteMatriz(MenorMatriz(Ai, i, 1)) );
				i++;
			}
			break;
		}
		
		
	}else{
		cout << endl << "Error: esta matriz no es cuadrada" << endl;
		char opcion;
		do{
			cout << endl << "	1.Volver" << endl;
			opcion = getch ();
		}while(opcion != '1');
	}


	
	return D;
}

Matriz AdjuntaMatriz (Matriz Ai){
	//Devuelve la adjunta de la matriz Ai
	Matriz Ci;
	Ci.I = Ai.I;
	Ci.J = Ai.J;
	
	int i=1, j=1; 
	
	while(i<=Ai.I){
		j=1;
		while(j<=Ai.J){
			
			Ci.matriz[i][j] = ( pow((-1),(i+j)) * DeterminanteMatriz(MenorMatriz(Ai, i, j)) );
			j++;
		}
		i++;
	}
	return Ci;
}

Matriz InversaMatriz(Matriz Ai){
	//Estructura: Ai^-1 = Ci
	
	Matriz Ci;
	InicializarMatriz(Ci);

	int i=1, j=1, d=0;
	
	d = DeterminanteMatriz(Ai);
	
	if (d!=0){
		Ci = AdjuntaMatriz(Ai);
		Ci = TranspuestaMatriz(Ci);
		while(i<=Ai.I){
			j=0;
			while(j<=Ai.J){
				
				Ci.matriz[i][j] = ( Ci.matriz[i][j] / d );
				j++;
			}
			i++;
		}
		
		
	}else cout << endl << "El determinante es igual a 0" << endl;
	
	char opcion;
	do{
		cout << endl << "	1.Volver" << endl;
		opcion = getch ();
	}while(opcion != '1');
	
	return Ci;
}

Matriz ProductoPorUnEscalar(Matriz Ai, int N){
	//Estructura: Ai*N = Ci
	Matriz Ci;
	Ci.I = Ai.I;
	Ci.J = Ai.J;
	
	int i=1, j=1;
	while(i <= Ai.I){
		j=1;
		while(j <= Ai.J){
			
			Ci.matriz[i][j] = ( Ai.matriz[i][j] * N );
			j++;
		}
		i++;
	}
	return Ci;
}

Matriz MultiplicarMatrices(Matriz Ai, Matriz Bi){
	
	//Estructura: Matriz Ai * Matriz Bi = Ci
	system ("cls");
	AGAMAT();
	
	Matriz Ci;
	InicializarMatriz(Ci);
	Ci.I = Ai.I;
	Ci.J = Bi.J;
	
	if (Ai.J == Bi.I){
		
		//A [i][j] B [p][k] C [l][m] 
		
		int i=1, k=1, m=1, temp=0;
		
		while(i <= Ai.I){
			m=1;
			while(m <= Ci.J){
				k=1;
				while(k <= Bi.J){
					
					temp += ( Ai.matriz[i][k] * Bi.matriz[k][m] );
					k++;
				}
				Ci.matriz[i][m] = temp;
				temp=0;
				m++;
			}
			i++;
		}
		
	}else cout << endl << "	Las Matrices no son operables" << endl;
	
	char opcion;
	do{
		cout << endl << "	1.Volver" << endl;
		opcion = getch ();
	}while(opcion != '1');
	
	return Ci;
}

Matriz MultiplicarMatricesParaPotencias(Matriz Ai, Matriz Bi){
	
	//Estructura: Matriz Ai * Matriz Bi = Ci
	Matriz Ci;
	InicializarMatriz(Ci);
	Ci.I = Ai.I;
	Ci.J = Bi.J;
	
	if (Ai.J == Bi.I){
		
		//A [i][j] B [p][k] C [l][m] 
		
		int i=1, k=1, m=1, temp=0;
		
		while(i <= Ai.I){
			m=1;
			while(m <= Ci.J){
				k=1;
				while(k <= Bi.J){
					
					temp += ( Ai.matriz[i][k] * Bi.matriz[k][m] );
					k++;
				}
				Ci.matriz[i][m] = temp;
				temp=0;
				m++;
			}
			i++;
		}
	}
	return Ci;
}

Matriz PotenciaMatriz (Matriz Ai, int N){
	//Estructura Ai^N = Ci
	
	Matriz Ci;
	InicializarMatriz(Ci);
	
	if (N >=0 ){
		
		switch(N){
			
		case 0:{
			cout << "Error: A^0";
			char opcion;
			do{
				system("cls");
				AGAMAT();
				cout << endl << "	1.Volver" << endl;
				opcion = getch ();
			}while(opcion != '1');
		}break;
		case 1: return Ai;
			break;
		default:
			Ci.I = Ai.I;
			Ci.J = Ai.J;
			Ci = MultiplicarMatricesParaPotencias(Ai, Ai);
			for(int i=2;i<N;i++){
				Ci = MultiplicarMatricesParaPotencias(Ci, Ai);
			}
			break;
		}
	}else{
		cout << endl <<"Error: No se puede elevar una matriz a un numero negativo" << endl;
		char opcion;
		do{
			system("cls");
			AGAMAT();
			cout << endl << "	1.Volver" << endl;
			opcion = getch ();
		}while(opcion != '1');
	}



	return Ci;
}

Matriz RestarMatrices(Matriz Ai, Matriz Bi){
	
	//Estructura: Matriz Ai - Matriz Bi = Ci
	system ("cls");
	AGAMAT();
	
	Matriz Ci;
	InicializarMatriz(Ci);
	if( ( ( Ai.I == Bi.I ) && ( Ai.J == Bi.J ) ) && ( Ai.I !=0 ) ){
		Ci.I = Ai.I;
		Ci.J = Ai.J;
		
		int i=1, j=1;
		
		while(i <= Ai.I){
			j=1;
			while(j<=Ai.J){
				Ci.matriz[i][j] = (Ai.matriz[i][j] - Bi.matriz[i][j]);
				j++;
			}
			
			i++;
		}
	}else cout << "\n	Las Matrices no son operables\n";
	
	char opcion;
	do{
		cout << endl << "	1.Volver" << endl;
		opcion = getch ();
	}while(opcion != '1');
	
	return Ci;
}

Matriz SumarMatrices(Matriz Ai, Matriz Bi){
	
	//Estructura: Matriz Ai + Matriz Bi = Ci
	system ("cls");
	AGAMAT();
	
	Matriz Ci;
	InicializarMatriz(Ci);
	if( ( ( Ai.I == Bi.I ) && ( Ai.J == Bi.J ) ) && ( Ai.I !=0 ) ){
		Ci.I = Ai.I;
		Ci.J = Ai.J;
		
		int i=1, j=1;
		
		while(i <= Ai.I){
			j=1;
			while(j<=Ai.J){
				Ci.matriz[i][j] = (Ai.matriz[i][j] + Bi.matriz[i][j]);
				j++;
			}
			
			i++;
		}
	}else cout << "\n	Las Matrices no son operables\n";
	
	char opcion;
	do{
		cout << endl << "	1.Volver" << endl;
		opcion = getch ();
	}while(opcion != '1');
	
	return Ci;
}	

Matriz IngresoMatriz(Matriz & M, char N){
	// M: Matriz; N: Identificador o nombre de la matriz
	char opcion;
	do{
		system ("cls");
		int i=1, j=1;
		
		AGAMAT();
		cout << "		MATRIZ " << char(N) << ":" << endl
			<< "	Filas: ";cin >> M.I; cout << endl 
			<< "	Columnas: ";cin >> M.J; cout << endl;
				
				
		while(i <= M.I){
			j=1;
			while(j<=M.J){
				cout << "	Posicion " << i << " " << j << ": ";
				cin >> M.matriz[i][j];
				cout << endl;
				j++;
			}
			i++;
		}
		cout << endl << "	1.Guardar" << endl
			<< "	2.Volver a ingresar la matriz" << endl;
		opcion = getch ();
	}while(opcion != '1');
	
	return M;
}

void MenuIngresoMatriz(Matriz & M, char N){
	
	// M: Matriz; N: Identificador de matriz
		
	system ("cls");
	
	char opcion;
	do{
		system ("cls");
		
		AGAMAT();
		cout << "|					|" << endl
			<< "|		MATRIZ " << char(N) << ":		|" << endl
			<< "|					|" << endl
			<< "|	1. Cargar			|" 	<< endl 
			<< "|	2. Ver				|"	<< endl 
			<< "|	3. Volver			|"		<< endl 
			<< "|_______________________________________|" << endl;

		
		opcion = getch ();
		
		switch(opcion){
			
		case '1': M = IngresoMatriz(M, N);
			break;
		case '2': MostrarMatriz(M, N);
			break;
		}
	}while(opcion !='3');
	
}

void MenuIngresarMatrices(Matriz & A, Matriz & B, Matriz & C){
	
	char opcion;
	do{
		system ("cls");
		
		AGAMAT();
		cout << "|					|" << endl
			<< "|	INGRESAR O VER MATRIZ		|" << endl
			<< "|					|" << endl
			<< "|	1. A				|" 	<< endl 
			<< "|	2. B				|"	<< endl 
			<< "|	3. C				|"		<< endl 
			<< "|	4. Volver			|"		<< endl 
			<< "|_______________________________________|" << endl;
		
		opcion = getch ();
		
		switch(opcion){
			
		case '1': MenuIngresoMatriz(A, 'A');
			break;
		case '2': MenuIngresoMatriz(B, 'B');
			break;
		case '3': MenuIngresoMatriz(C, 'C');
			break;
		}
	}while(opcion !='4');
	
}

void MenuOperacionesMatriciales(Matriz & A, Matriz & B, Matriz & C){
	int d;
	char opcion;
	do{
		system ("cls");
		
		AGAMAT();
		cout << "|					|" << endl
			<< "|	OPERACIONES MATRICIALES		|" << endl
			<< "|					|" << endl
			<< "|	1. A+B				|" 	<< endl 
			<< "|	2. A-B				|"	<< endl 
			<< "|	3. A*B				|"		<< endl 
			<< "|	4. A^x				|"		<< endl 
			<< "|	5. A.x				|"		<< endl 
			<< "|	6. Trn(A)			|"		<< endl 
			<< "|	7. |A|				|"		<< endl
			<< "|	8. Adj(A)			|"		<< endl
			<< "|	9. A^-1				|"		<< endl
			<< "|	0. Volver			|"		<< endl
			<< "|					|" << endl
			<< "|	Nota: El resultado de cada 	|"		<< endl
			<< "|	operaci" << char(162) << "n se almacena en C	|"		<< endl
			<< "|_______________________________________|" << endl;

		opcion = getch ();
		
		switch(opcion){
			
		case '1':
			C = SumarMatrices(A, B);
			if (C.I !=0)MostrarMatriz(C, 'C');
		break;
		
		case '2':
			C = RestarMatrices(A, B);
			if (C.I !=0)MostrarMatriz(C, 'C');
		break;
		
		case '3':
			C = MultiplicarMatrices(A, B);
			if (C.I != 0) MostrarMatriz(C, 'C');
		break;
		
		case '4':{
			int p=0;
			system("cls");
			AGAMAT();
			cout << "\n	x= " ;
			cin >> p;
			C = PotenciaMatriz(A, p);
			if (C.I !=0)MostrarMatriz(C, 'C');
		}break;
		case '5':{
			int e=0;
			system ("cls");
			AGAMAT();
			cout << "\n	x= " ;
			cin >> e;
			C = ProductoPorUnEscalar(A, e);
			MostrarMatriz(C, 'C');
		}break;
		case '6':
			C = TranspuestaMatriz(A);
			if (C.I !=0)MostrarMatriz(C, 'C');
		break;
		case '7':{
			d = DeterminanteMatriz(A);
			cout << endl << "	|A|= " << d << endl;
			char opcion;
			do{
				cout << endl << "	1.Volver" << endl;
				opcion = getch ();
			}while(opcion != '1');
		}break;
		case '8':
			C = AdjuntaMatriz(A);
			if (C.I !=0)MostrarMatriz(C, 'C');
		break;
		case '9':
			C = InversaMatriz(A);
			if (C.I !=0)MostrarMatriz(C, 'C');
		break;
	}
	}while(opcion !='0');
}

void Version(){
	system("cls");
	char opcion;
	do{
		AGAMAT();
		cout << "|					|" << endl
			<< "|	-Versi" << char (162) << "n: 1.0			|" 	<< endl 
			<< "|	-Fecha: Abril de 2016		|"	<< endl 
			<< "|	-Desarrollado por:		|"		<< endl 
			<< "|	Ignacio Kalbermatten		|" << endl
			<< "|					|" << endl
			<< "|	1.Volver			|" << endl
			<< "|_______________________________________|" << endl;
		opcion = getch ();
	}while(opcion != '1');
}

void MenuPrincipal (Matriz & A, Matriz & B, Matriz & C){
	
	char opcion;
	do{
		system ("cls");
		AGAMAT();
		cout << "|					|" << endl
			<< "|	1.Ingresar/Ver Matrices		|"	<< endl 
			<< "|	2.Operaciones Matriciales	|"	<< endl 
			<< "|	3.Versi" << char (162) << "n			|" 	<< endl 
			<< "|	4.Salir				|"		<< endl 
			<< "|_______________________________________|" << endl;
		
		opcion = getch ();
		
		switch(opcion){
			
		case '1': MenuIngresarMatrices(A, B, C);
		break;
		case '2': MenuOperacionesMatriciales(A, B, C);
		break;
		case '3': Version();
		break;
		}
	}while(opcion !='4');
	
}

int main(int argc, char *argv[]) {
	Matriz A, B, C;
	
	InicializarMatriz (A);
	InicializarMatriz (B);
	InicializarMatriz (C);
	
	MenuPrincipal(A, B, C);
	
	return 0;
}

