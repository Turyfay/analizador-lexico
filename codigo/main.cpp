
/*
ANALIZADOR LEXICO V1.0

*/
#include <conio.h>
#include <string>
#include <iostream>
#include <iterator>
#include "analizador.cpp"
#include "menu.cpp"
#define MAX 650
#define MAX_RES 22



using namespace std;


int main()
{
    //INICIAR Identificador
    string direccionArchivo;
    string LineaCodigo;
   
    //ENTRADA DE LINEA DE CODIGO.
    system("COLOR 0A");    
    switch (menu())
    {
    case 1:
        system("cls");
        cout<<"Escriba la direccion de archivo de texto: ";
        cin >> direccionArchivo;
        analizar(leerArchivo(direccionArchivo));
        break;
    case 2:
        system("cls");
        cout << "Escriba la linea de codigo: ";
        cin >> LineaCodigo;
        break;
    case 3:
        cout << "Saliendo del analizador.";
        return 0;
        break;
    default:
        cout<<"No existe esa opcion";
        break;
    }
    system("COLOR 0B");
    getch();
    return 0;
}

