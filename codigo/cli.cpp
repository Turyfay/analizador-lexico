#include <string>
#include<iostream>
using namespace std;


void imprimirTitulo(){

    cout << "   ###    ##    ##    ###    ##       #### ########    ###    ########   #######  ########     ##       ######## ##     ## ####  ######   #######     ##     ##    ##         #####   \n";
    cout << "  ## ##   ###   ##   ## ##   ##        ##       ##    ## ##   ##     ## ##     ## ##     ##    ##       ##        ##   ##   ##  ##    ## ##     ##    ##     ##  ####        ##   ##  \n";
    cout << " ##   ##  ####  ##  ##   ##  ##        ##      ##    ##   ##  ##     ## ##     ## ##     ##    ##       ##         ## ##    ##  ##       ##     ##    ##     ##    ##       ##     ## \n";
    cout << "##     ## ## ## ## ##     ## ##        ##     ##    ##     ## ##     ## ##     ## ########     ##       ######      ###     ##  ##       ##     ##    ##     ##    ##       ##     ## \n";
    cout << "######### ##  #### ######### ##        ##    ##     ######### ##     ## ##     ## ##   ##      ##       ##         ## ##    ##  ##       ##     ##     ##   ##     ##       ##     ## \n";
    cout << "##     ## ##   ### ##     ## ##        ##   ##      ##     ## ##     ## ##     ## ##    ##     ##       ##        ##   ##   ##  ##    ## ##     ##      ## ##      ##   ###  ##   ##  \n";
    cout << "##     ## ##    ## ##     ## ######## #### ######## ##     ## ########   #######  ##     ##    ######## ######## ##     ## ####  ######   #######        ###     ###### ###   #####   \n";
}


 void menu(){
    
    string linea;
    string lineaCodigo;
    string direccionArchivo;
    string archivoResumen;
    int opcion = 0;
    

    imprimirTitulo();
    cout << "\n---------------------------------------------------------------------------\n";
    cout<< "\nElija una opcion\n";
    cout<<"1. Analizar archivo\n";
    cout<<"2. Analizar linea\n";
    cout<<"3. Salir\n";
    cin >> linea;
    opcion = stoi(linea);



    switch (opcion)
    {
    case 1:
        system("cls");
        cout<<"Escriba la direccion de archivo de texto: ";
        cin >> direccionArchivo;

        system("cls");
        cout << "Escriba el nombre del archivo resumen: ";
        cin >> archivoResumen;
        break;
    case 2:
        system("cls");
        cout << "Escriba la linea de codigo: ";
        cin >> lineaCodigo;
        break;
    default:
        cout<<"No existe esa opcion";
        break;
    }
    
    

}
