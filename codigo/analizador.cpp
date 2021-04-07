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

string simbolosAritmeticos[] = {"+", "-", "*", "/", "%"};

string operadoresComparacion[] = {"==", "!=", "&&", "||"};

string operadoresAsignacion[] = {"=", "->"};

string tokenPalabraReservada[MAX];
string tokenIdentificador[MAX];
//PROCEDIMIENTOS
vector<string> split(string str);
bool palabraReservada(string palabra);
bool Identificador(string palabra);
void imprimirResultado();

//Listas de elementos encontrados
vector<string> simbolos;
vector<string> identificador;
vector<string> numeroEntero;
vector<string> numeroFlotante;
vector<string> palabraReservada;

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

vector<string> analizar(vector<char>* contenido){
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
                //Borrar primer caracter del vector para continuar leyendo
                contenido->erase(contenido->begin());
                //Pasa al estado de aceptación 1
                estado=1;
            }else if((c >= '(' && c<='+')|| c=='{'|| c=='}' || c=='-'|| c=='/'|| c=='%'||c== '<' || c== '>'|| c== '='|| c== ';'){
                //Se identifica simbolos aceptados
                //Guardar elemento en la cadena de simbolo
                elemento.push_back(c);
                //Guardar elemento en el vector de simbolos
                simbolos.push_back(elemento);
                cout<<"elemento guardado: "<<elemento<<endl;
                //Borrado de cadena elemento para leer uno nuevo
                elemento.clear();
                //Borrar el primer caracter del vector para continuar leyendo
                contenido->erase(contenido->begin());
            }else if(c==' '|| c=='\n'){
                //Se identifica un salto de linea o espacio
                //Borrado de salto de linea o espacio del vector
                contenido->erase(contenido->begin());
            }else if(c >= '0' && c<= '9'){
                //Se idenficica digito
                //guardar digito en cadena de elemento
                elemento.push_back(c);
                //Borrar primer caracter del vector para continuar leyendo
                contenido->erase(contenido->begin());
                //Pasa al estado de aceptación 2
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
                //Guardar letra en la cadena de elemento
                elemento.push_back(c);
                //Borrar primer caracter del vector para continuar leyendo
                contenido->erase(contenido->begin());
                //Continua en estado 1 hasta que deje de leer letras o digitos
            }else{
		if(esPalabraReservada(elemento)){
		    palabraReservada.push_back(elemento);
		}else{
		    identificador.push_back(elemento);
		}
		identificador.push_back(elemento);
		cout<<"elemento guardado: "<<elemento<<endl;
		elemento.clear();
		estado = 0;
            }
            break;
        case 2:
            //cout<<"case 2"<<endl;
            if(c >= '0' && c<= '9'){
                //Se identifica el primer caracter como digito
                //Guarda digito en la cadena de elemento
                elemento.push_back(c);
                //Borra el primer caracter del vector para continuar leyendo
                contenido->erase(contenido->begin());
                //Continua en estado 2 hasta que deje de leer digitos

            }else if(c == '.'){
                //Se identifica el primer caracter como punto
                //Guarda el punto en la cadena de elemento
                elemento.push_back(c);
                //Borra el primer caracter del vector para continuar leyendo
                contenido->erase(contenido->begin());
                //Cambia al estado 3
                estado = 3;

            }else{
                //Se guarda el elemento en el vector entero
                numeroEntero.push_back(elemento);
                cout<<"elemento guardado: "<<elemento<<endl;
                //Borrado de arreglo elemento para almacenar uno nuevo
                elemento.clear();
                //Pasa al estado 0 a leer nuevo elemento
                estado = 0;
            }
            break;
        case 3:
            //cout<<"Case 3"<<endl;
            if(c >= '0' && c<= '9'){
                //Se identifica el primer caracter como digito
                //Guarda digito en la cadena de elemento
                elemento.push_back(c);
                //Borra el primer caracter del vector para continuar leyendo
                contenido->erase(contenido->begin());
                //Cambia a estado 4
                estado = 4;
            }else{
                //Definir estado de error
            }
            break;
        case 4:
            //cout<<"case 4"<<endl;
            if(c >= '0' && c<= '9'){
                //Se identifica el primer caracter como dígito
                //Guarda dígito en la cadena de elemento
                elemento.push_back(c);
                //Borra el primer caracter del vector para continuar leyendo
                contenido->erase(contenido->begin());
                //Continua en estado 4 hasta que deje de leer dígitos
            }else{
                //Se guarda el elemento en el vector flotantes
                numeroFlotante.push_back(elemento);
                cout<<"elemento guardado: "<<elemento<<endl;
                //Borrado de arreglo elemento para almacenar uno nuevo
                elemento.clear();
                //Pasa al estado 0 a leer nuevo elemento
                estado = 0;
            }
            break;
        }
    }

    cout<<"\n////////////// TOKENS SIMBOLOS //////////////"<<endl;
    for(int i = 0; i<simbolos.size();i++){
        cout<<simbolos[i]<<endl;
    }
    cout<<"\n////////// TOKENS IDENTIFICADORES //////////"<<endl;
    for(int i = 0; i<identificador.size();i++){
        cout<<identificador[i]<<endl;
    }
    cout<<"\n////////////// TOKENS ENTEROS //////////////"<<endl;
    for(int i = 0; i<numeroEntero.size();i++){
        cout<<numeroEntero[i]<<endl;
    }
    cout<<"\n///////////// TOKENS FLOTANTES /////////////"<<endl;
    for(int i = 0; i<numeroFlotante.size();i++){
        cout<<numeroFlotante[i]<<endl;
    }

	return simbolos;
}
void archivoResumen(){
    ofstream file;
    file.open("ResumenLexico.txt");
    file << "\n-----------------------\n|Identificador|\n-----------------------";
    for (int i = 0; i < auxTV; i++)
    {
        file << tokenIdentificador[i] + "\n";
    }
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


//RECIBE EL VECTOR Y LO COMPARA CON LAS PALABRAS RESERVADAS
vector<string> comparar(vector<string> vec){
	vector<string> final;
	
	//recorremos cada elemento del vector que recibe
	for(int i=0; i<vec.size(); i++){
		//comparar con cada palabra reservada
		for(int j=0; j<palabrasReservadas.size(); j++){
			//si son iguales entonces guardamos en final el tipo y el dato
			if(vec[i] == palabrasReservadas[j]){
				final.push_back("Palabra reservada "+vec[i]);
			}
		}
		//comparar con cada operador Aritmetico
		for(int k=0; k<simbolosAritmeticos.size(); k++){
			//si son iguales entonces guardamos en final el tipo y el dato
			if(vec[i] == simbolosAritmeticos[k]){
	  	    	        final.push_back("Operador Aritmetico "+vec[i]);
		    }
		}
		//comparar con cada operador de Comparacion
		for(int l=0; l<operadoresComparacion.size(); l++){
			//si son iguales entonces guardamos en final el tipo y el dato
			if(vec[i] == operadoresComparacion[l]){
				final.push_back("Operador Comparacion "+vec[i]);
			}
		}
		//comparar con cada operador de asignacion
		for(int m=0; m<operadoresAsignacion.size(); m++){
			//si son iguales entonces guardamos en final el tipo y el dato
			if(vec[i] == operadoresAsignacion[m]){
				final.push_back("Operador Asingnacion"+vec[i]);
			}
		}
	}
	return final;

}




