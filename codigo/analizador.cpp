#include <string>
#include <iostream>
//Libreria fstream  que sirve para la creacion la escritura y lecturas de archivos
#include <fstream>
//Permite almacenar datos que se ingresan dentro de un vector
#include <vector>
#define MAX 650
#define MAX_RES 22


using namespace std;

//TABLA DE SIMBOLOS
string palabrasReservadas[MAX_RES] =  {"SI", "FIN-SI", "SINO", "PARA", "DESDE", "HASTA",
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
/* for (int i = 0; i < MAX; i++)
    {
        tokenPalabraReservada[i] = "";
    }
    for (int i = 0; i < MAX; i++)
    {
        tokenIdentificador[i] = "";
    }
 *//*  while (cont < ListaPalabras.size())
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
    imprimirResultado(); */



vector<char>* leerArchivo(string direccionArchivo){

    ifstream archivo;
    vector<char> *contenido = new vector<char>();
    archivo.open(direccionArchivo,ios::in);//Abrir el archivo
    if(archivo.fail()){
        cout << "No se pudo leer el archivo.";
        exit(1);
    }
    while(!archivo.eof()){ //Leer mientras no sea el final del archivo.
        
        contenido->push_back(archivo.get());
    }
    return contenido;
}

void analizar(vector<char>* contenido){
    //Identificador de simbolo
    string simbolo;
    //Lista de simbolos encontrados
    vector<string> simbolos;
    //estado del automata, estado inicial 0
    int estado = 0;
    while(contenido->size()!=0){
        //Leyendo primer caracter del vector que contiene el codigo
        char c = contenido->front();
        switch(estado){
        case 0:
            //cout<<"case 0"<<endl;
            if((c >= 'a' && c <= 'z')||(c >= 'A' && c<= 'Z')){
                //Se identifica el primer caracter como una letra
                //Guardar letra en la cadena de simbolo
                simbolo.push_back(c);
                //Borrar primer caracter del vector para continuar leyendo
                contenido->erase(contenido->begin());
                //Pasa al estado de aceptación 1
                estado=1;
            }else if((c >= '(' && c<='+')|| c=='{'|| c=='}'){
                //Se identifica simbolos aceptados
                //Guardar simbolo en la cadena de simbolo
                simbolo.push_back(c);
                //Guardar simbolo en el vector de simbolos
                simbolos.push_back(simbolo);
                cout<<"simbolo guardado: "<<simbolo<<endl;
                //Borrado de cadena simbolo para leer uno nuevo
                simbolo.clear();
                //Borrar el primer caracter del vector para continuar leyendo
                contenido->erase(contenido->begin());
            }else if(c==' '|| c=='\n'){
                //Se identifica un salto de linea o espacio
                //Borrado de salto de linea o espacio del vector
                contenido->erase(contenido->begin());
            }else{
                estado = 2;
            }
            break;
        case 1:
            //cout<<"case 1"<<endl;
            //Estado de aceptación 1, si continua leyendo letras se guardan en simbolo
            if((c >= 'a' && c <= 'z')||(c >= 'A' && c<= 'Z')){
                //Se identifica el primer caracter como una letra
                //Guardar letra en la cadena de simbolo
                simbolo.push_back(c);
                //Borrar primer caracter del vector para continuar leyendo
                contenido->erase(contenido->begin());
                //Continua en estado 1 hasta que deje de leer letras
            }else{
                //Se guarda el simbolo en el vector simbolos
                simbolos.push_back(simbolo);
                cout<<"simbolo guardado: "<<simbolo<<endl;
                //Borrado de arreglo simbolo para almacenar uno nuevo
                simbolo.clear();
                //Pasa al estado 0 a leer nuevo simbolo
                estado = 0;
            }
            break;
        case 2:
            //cout<<"case 2"<<endl;
            contenido->erase(contenido->begin());
            break;
        }
    }

    cout<<"\nLista de simbolos encontrados: "<<endl;

    for(int i=0;i<simbolos.size();i++){
        cout<<simbolos[i]<<endl;
    }
}



void archivoReumen(){

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
