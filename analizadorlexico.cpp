
/*AUTOMATAS

*/
#include <stdio.h>
#include <conio.h>
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <iterator>
#include <iomanip>
#define MAX 650
#define MAX_RES 22

using namespace std;
//
string palabrasReservadas[MAX_RES] = {"SI","FIN-SI","SINO","PARA","DESDE","HASTA",
                                "INCREMENTO","FIN-PARA","REPETIR","MIENTRAS","FIN-MIENTRAS",
                                "salida->","entrada->","verdad","falso","sqrt","int",
                                "char","strring","booleano","float","double"};
string tokenPalabraReservada[MAX];


//PROCEDIMIENTOS
vector <string> split(string str);
bool palabraReservada(string palabra);
void imprimirResultado();

//Variables auxiliares para guardar en Tokens
int auxTR=0;


main(){
    //INICIAR VARIABLES
    int cont = 0;
    string LineaCodigo;
    vector <string> ListaPalabras;
    for(int i=0;i<MAX;i++){tokenPalabraReservada[i] = "";}

    //ENTRADA DE LINEA DE CODIGO.
    system("COLOR 0A");
    printf("Ingrese una linea de codigo: ");
    //fflush(stdin);
    getline(cin,LineaCodigo);
    ListaPalabras = split(LineaCodigo);
    //fflush(stdin);
    system("cls");  
    system("COLOR 0B");
    while(cont < ListaPalabras.size()){
        if(palabraReservada(ListaPalabras[cont]) == true){
        tokenPalabraReservada[auxTR] = ListaPalabras[cont];
    	auxTR++;
        }
        cont++;
    }
    //IMPRIMIR EL RESULTADO
    cout << "EXPRESION: " + LineaCodigo;
    imprimirResultado();
	getch();

    
}

//IMPRIMIR RESULTADOS
void imprimirResultado(){
	puts("\n-----------------------\n|Palabras Reservadas|\n-----------------------");
	for(int i=0;i<auxTR;i++){
    cout << i + 1;
    cout << " " + tokenPalabraReservada[i] + "\n";
    }
}




//VERIFICAR PALARA RESERVADA
bool palabraReservada(string palabra){
    bool esReservada=false;
    for(int i=0; i<MAX_RES; i++){
        if(palabra.compare(palabrasReservadas[i])==0){
            esReservada = true;
            break;
        }
    }
    return esReservada;
    
}

//CADENA EN VECTOR OBTENER PALABRAS
vector<string> split(string str){
    vector<string> resultado;
    string palabra;
    int i = 0;
    while(str.size() > i){
        if(str[i]== ' '){
            resultado.push_back(palabra);
            palabra = "";
        }else{
            palabra+=str[i];
        }
        i++;
    }
    return resultado;
}