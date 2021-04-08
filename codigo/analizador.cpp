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
bool esPalabraReservada(string palabra);
bool Identificador(string palabra);
void archivoResumen();

//Listas de elementos encontrados
vector<string> simbolos;
vector<string> identificador;
vector<string> numeroEntero;
vector<string> numeroFlotante;
vector<string> palabraReservada;

//
string nombreArchivoResumen;



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
    //Identificador de elemento
    string elemento;

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
                elemento.push_back(c);
                contenido->erase(contenido->begin());
                estado=1;
		    
            }else if((c >= '(' && c<='+')|| c=='{'|| c=='}' || c=='-'|| c=='/'|| c=='%'||c== '<' || c== '>'|| c== '='|| c== ';'){
                //Se identifica simbolos aceptados
                elemento.push_back(c);
                //Guardar elemento en el vector de simbolos
                simbolos.push_back(elemento);
                //cout<<"elemento guardado: "<<elemento<<endl;
                elemento.clear();
                contenido->erase(contenido->begin());
		    
            }else if(c==' '|| c=='\n'){
                //Se identifica un salto de linea o espacio
                //Borrado de salto de linea o espacio del vector
                contenido->erase(contenido->begin());
		    
            }else if(c >= '0' && c<= '9'){
                //Se idenficica digito
                elemento.push_back(c);
                contenido->erase(contenido->begin());
                estado = 2;
		    
            }else{
                contenido->erase(contenido->begin());
            }
            break;
        case 1:
            //cout<<"case 1"<<endl;
            //Estado de aceptación 1, si continua leyendo letras se guardan en elemento
            if((c >= 'a' && c <= 'z')||(c >= 'A' && c<= 'Z')||(c >= '0' && c<= '9')){
                //Se identifica el primer caracter como una letra o digito
                elemento.push_back(c);
                contenido->erase(contenido->begin());
                //Continua en estado 1 hasta que deje de leer letras o digitos
		    
            }else{
		if(esPalabraReservada(elemento)){
		    palabraReservada.push_back(elemento);
		}else{
		    identificador.push_back(elemento);
		}
		//Se guarda el elemento en el vector palabraReservada o identificador
		//cout<<"elemento guardado: "<<elemento<<endl;
		elemento.clear();
		estado = 0;
            }
            break;
        case 2:
            //cout<<"case 2"<<endl;
            if(c >= '0' && c<= '9'){
                //Se identifica el primer caracter como digito
                elemento.push_back(c);
                contenido->erase(contenido->begin());
                //Continua en estado 2 hasta que deje de leer digitos

            }else if(c == '.'){
                //Se identifica el primer caracter como punto
                elemento.push_back(c);
                contenido->erase(contenido->begin());
                estado = 3;

            }else{
                //Se guarda el elemento en el vector entero
                numeroEntero.push_back(elemento);
                //cout<<"elemento guardado: "<<elemento<<endl;
                elemento.clear();
                estado = 0;
            }
            break;
        case 3:
            //cout<<"Case 3"<<endl;
            if(c >= '0' && c<= '9'){
                //Se identifica el primer caracter como digito
                elemento.push_back(c);
                contenido->erase(contenido->begin());
                estado = 4;
		    
            }else{
                //Definir estado de error
            }
            break;
        case 4:
            //cout<<"case 4"<<endl;
            if(c >= '0' && c<= '9'){
                //Se identifica el primer caracter como dígito
                elemento.push_back(c);
                contenido->erase(contenido->begin());
		    
            }else{
                //Se guarda el elemento en el vector flotantes
                numeroFlotante.push_back(elemento);
                //cout<<"elemento guardado: "<<elemento<<endl;
                elemento.clear();
                estado = 0;
		    
            }
            break;
        }
    }

    /* cout<<"\n////////////// TOKENS SIMBOLOS //////////////"<<endl;
    for(int i = 0; i<simbolos.size();i++){
        cout<<simbolos[i]<<endl;
    }
    cout<<"\n////////// TOKENS IDENTIFICADORES //////////"<<endl;
    for(int i = 0; i<identificador.size();i++){
        cout<<identificador[i]<<endl;
    }
    cout<<"\n//////// TOKENS PALABRAS RESERVADAS ////////"<<endl;
    for(int i = 0; i<palabraReservada.size();i++){
        cout<<palabraReservada[i]<<endl;
    }
    cout<<"\n////////////// TOKENS ENTEROS //////////////"<<endl;
    for(int i = 0; i<numeroEntero.size();i++){
        cout<<numeroEntero[i]<<endl;
    }
    cout<<"\n///////////// TOKENS FLOTANTES /////////////"<<endl;
    for(int i = 0; i<numeroFlotante.size();i++){
        cout<<numeroFlotante[i]<<endl;
    } */

    //CREAR EL ARCHIVO RESUMEN.
    archivoResumen();



}
void archivoResumen(){

    cout << "Escriba el nombre del archivo de texto: ";
    cin >> nombreArchivoResumen;



    ofstream file;
    file.open(nombreArchivoResumen + ".txt");
    file <<"\n////////////// TOKENS SIMBOLOS //////////////\n";
    for(int i = 0; i<simbolos.size();i++){
        file <<simbolos[i];
    }
    file <<"\n////////// TOKENS IDENTIFICADORES //////////\n";
    for(int i = 0; i<identificador.size();i++){
        file<<identificador[i] << "\n";
    }
    file <<"\n//////// TOKENS PALABRAS RESERVADAS ////////\n";
    for(int i = 0; i<palabraReservada.size();i++){
        file <<palabraReservada[i] << "\n";
    }
    file <<"\n////////////// TOKENS ENTEROS //////////////\n";
    for(int i = 0; i<numeroEntero.size();i++){
        file <<numeroEntero[i]<< "\n";
    }
    file <<"\n///////////// TOKENS FLOTANTES /////////////\n";
    for(int i = 0; i<numeroFlotante.size();i++){
        file << numeroFlotante[i] << "\n";
    }

    file.close();
    cout << "Archivo " +nombreArchivoResumen+ " creado" ;
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
bool esPalabraReservada(string palabra)
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


