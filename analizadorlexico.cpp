
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
#define MAX_RES 23

using namespace std;
vector <string> split(string str);

main(){


    string LineaCodigo;
    vector <string> ListaPalabras;
    //ENTRADA DE LINEA DE CODIGO.
    system("COLOR 0A");
    printf("Ingrese una linea de codigo: ");
    //fflush(stdin);
    getline(cin,LineaCodigo);
    ListaPalabras = split(LineaCodigo);
    //fflush(stdin);
    system("cls");  
    system("COLOR 0B");


    //IMPRIMIR EL RESULTADO
    cout << ListaPalabras[0];
	getch();

    
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