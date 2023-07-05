#include "arbol_genealogico.h"
int main(){
    arbol_genealogico arbol;
    int consulta = 1;
    while (consulta){
        cout<<"Seleccionar persona(1)"<<endl;
        cout<<"Añadir persona(2)"<<endl;
        cout<<"Anadir padre(3)"<<endl;
        cout<<"Anadir madre(4)"<<endl;
        cout<<"Anadir hijos(5)"<<endl;
        cout<<"Imprimir(6)"<<endl;
        cout<<"Leer(7)"<<endl;
        cout<<"Salir(0)"<<endl;
        cin>>consulta;
        if(consulta == 1){
            string datos[3];
            cout<<"Nombres: ";cin>>datos[0];
            cout<<"Primer Apellido: "; cin>>datos[1];
            cout<<"Segundo Apellido: "; cin>>datos[2];
            arbol.seleccionar(datos);
        }
        else if(consulta == 2){
            string datos[3];
            bool g,s;
            cout<<"Nombres: ";cin>>datos[0];
            cout<<"Primer Apellido: "; cin>>datos[1];
            cout<<"Segundo Apellido: "; cin>>datos[2];
            cout<<"Genero: ";cin>>g;
            cout<<"Desea seleccionarlo?: ";cin>>s;
            if(!arbol.anadir(datos,g,s)){
                cout<<"Error, duplicación de persona\n";
            }
            else{
                cout<<"Persona añadida\n";
            }
        }
        else if(arbol.elegido() != nullptr){
            if(consulta == 3){
                string datos[3];
                bool g,s;
                cout<<"Nombres: ";cin>>datos[0];
                cout<<"Segundo Apellido: "; cin>>datos[2];
                cout<<"Desea seleccionarlo?: ";cin>>s;
                arbol.anadir_padre(datos,g,s);
            }
            else if(consulta == 4){
                string datos[3];
                bool g,s;
                cout<<"Nombres: ";cin>>datos[0];
                cout<<"Segundo Apellido: "; cin>>datos[2];
                cout<<"Desea seleccionarlo?: ";cin>>s;
                arbol.anadir_madre(datos,g,s);
            }
            else if(consulta == 5){
                int c;
                bool d;
                cout<<"Cuantos hijos desea añadir?: ";cin>>c;
                cout<<"Desea anadir pareja?: ";cin>>d;
                string n[c];
                bool g[c];
                if(d){
                    persona*ant_select = arbol.elegido();
                    string datos[3];
                    cout<<"Nombres: ";cin>>datos[0];
                    cout<<"Primer Apellido: "; cin>>datos[1];
                    cout<<"Segundo Apellido: "; cin>>datos[2];
                    while (!arbol.anadir(datos,!arbol.genero_selec(),1)){
                        cout<<"Error, duplicacion de persona, vuelva a ingresar la pareja\n";
                        cout<<"Nombres: ";cin>>datos[0];
                        cout<<"Primer Apellido: "; cin>>datos[1];
                        cout<<"Segundo Apellido: "; cin>>datos[2];
                    }
                    for (int i = 0; i < c; i++){
                        cout<<"Hijo "<<i+1<<":\n";
                        cout<<"Nombres: ";cin>>n[i];
                    }
                    arbol.anadir_hijos(n,ant_select,g,c);
                }
                else{
                    string a[c];
                    for (int i = 0; i < c; i++){
                        cout<<"Hijo "<<i+1<<":\n";
                        cout<<"Nombres: ";cin>>n[i];
                        cout<<"Apellido Faltante: "; cin>>a[i];
                    }
                    arbol.anadir_hijos(n,a,g,c);
                }
                
            }
            else if(consulta == 6){
                
            }
            else if(consulta == 7){
                
            }
            else{
                consulta = 0;
            }
        }
        else{
            consulta = 0;
        }
    }
}