
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
string palabrasReservadas[MAX_RES] = {"SI", "FIN-SI", "SINO", "PARA", "DESDE", "HASTA",
                                      "INCREMENTO", "FIN-PARA", "REPETIR", "MIENTRAS", "FIN-MIENTRAS",
                                      "salida->", "entrada->", "verdad", "falso", "sqrt", "int",
                                      "char", "strring", "booleano", "float", "double"};
string tokenPalabraReservada[MAX];
string tokenIdentificador[MAX];

//PROCEDIMIENTOS
vector<string> split(string str);
bool palabraReservada(string palabra);
bool Identificador(string palabra);
void imprimirResultado();

//Identificador auxiliares para guardar en Tokens
int auxTR = 0;
int auxTV = 0;

main()
{
    //INICIAR Identificador
    int cont = 0;
    string LineaCodigo;
    vector<string> ListaPalabras;
    for (int i = 0; i < MAX; i++)
    {
        tokenPalabraReservada[i] = "";
    }
    for (int i = 0; i < MAX; i++)
    {
        tokenIdentificador[i] = "";
    }

    //ENTRADA DE LINEA DE CODIGO.
    system("COLOR 0A");
    printf("Ingrese una linea de codigo: ");
    //fflush(stdin);
    getline(cin, LineaCodigo);
    ListaPalabras = split(LineaCodigo);
    //fflush(stdin);
    system("cls");
    system("COLOR 0B");
    while (cont < ListaPalabras.size())
    {
        if (palabraReservada(ListaPalabras[cont]) == true)
        {
            tokenPalabraReservada[auxTR] = ListaPalabras[cont];
            auxTR++;
        }
        else if (Identificador(ListaPalabras[cont]) == true)
        {
            tokenIdentificador[auxTV] = ListaPalabras[cont];
            auxTV++;
        }
        cont++;
    }

    

    //IMPRIMIR EL RESULTADO
    cout << "EXPRESION: " + LineaCodigo;
    imprimirResultado();
    getch();
}

//IMPRIMIR RESULTADOS
void imprimirResultado()
{
    puts("\n-----------------------\n|Palabras Reservadas|\n-----------------------");
    for (int i = 0; i < auxTR; i++)
    {
        cout << i + 1;
        cout << " " + tokenPalabraReservada[i] + "\n";
    }
    puts("\n-----------------------\n|Identificador|\n-----------------------");
    for (int i = 0; i < auxTV; i++)
    {
        cout << i + 1;
        cout << " " + tokenIdentificador[i] + "\n";
    }
}

//VERIFICAR VARIABLE
bool Identificador(string palabra)
{
    int cont = 0;
    enum TEstado
    {
        q0,
        q1,
        qe
    };
    TEstado Estado = q0;
    while (cont < palabra.size())
    {
        switch (Estado)
        {
        case q0:
            if (isalpha(palabra[cont]))
            {
                Estado = q1;
            }
            else
            {
                Estado = qe;
            }
            break;
        case q1:
            if (isalpha(palabra[cont]) || isdigit(palabra[cont]))
            {
                Estado = q1;
            }
            else
            {
                Estado = qe;
            }
            break;
        }
        return Estado == q1 ? true : false;
    }
}

//VERIFICAR PALARA RESERVADA
bool palabraReservada(string palabra)
{
    bool esReservada = false;
    for (int i = 0; i < MAX_RES; i++)
    {
        if (palabra.compare(palabrasReservadas[i]) == 0)
        {
            esReservada = true;
            break;
        }
    }
    return esReservada;
}

//CADENA EN VECTOR OBTENER PALABRAS
vector<string> split(string str)
{
    vector<string> resultado;
    string palabra;
    int i = 0;
    while (str.size() > i)
    {
        if (str[i] == ' ')
        {
            resultado.push_back(palabra);
            palabra = "";
        }
        else
        {
            palabra += str[i];
        }
        i++;
    }
    return resultado;
}