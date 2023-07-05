#ifndef ARBOL_GENEALOGICO_H
#define ARBOL_GENEALOGICO_H
#include "persona.h"
using namespace std;
class arbol_genealogico
{
private:
    vector<persona*> grupo_de_personas[26];
    persona * seleccionado;
public:
    arbol_genealogico();
    persona * elegido();
    persona * buscar(string*);
    void seleccionar(string*);
    int genero_selec();
    bool anadir(string*,bool,bool);
    void anadir_madre(string*,bool,bool);
    void anadir_padre(string*,bool,bool);
    void anadir_hijos(string*,string*,bool*,int);
    void anadir_hijos(string*,persona*,bool*,int);
    ~arbol_genealogico();
};

arbol_genealogico::arbol_genealogico()
{
    seleccionado = nullptr;
}
persona* arbol_genealogico::elegido(){
    return seleccionado;
}
persona* arbol_genealogico::buscar(string *datos){
    persona * resultado = nullptr;
    int grupo = datos[0][0]-'A';
    if(!grupo_de_personas[grupo].empty()){
        for (auto it:grupo_de_personas[grupo]){
            if(*it == datos){
                resultado = it;
                break;
            }
        }
    }
    return resultado;
}
void arbol_genealogico::seleccionar(string *datos){
    persona * resultado = this->buscar(datos);
    if(resultado != nullptr){
        this->seleccionado = resultado;
        cout<<"Persona seleccionada\n";
    }
    else{
        cout<<"No se ha encontrado dicha persona\n";
    }
}
int arbol_genealogico::genero_selec(){
    if(this->seleccionado != nullptr){
        return this->seleccionado->genero;
    }
    else{
        return -1;
    }
}
bool arbol_genealogico::anadir(string *datos, bool g,bool s){
    if(this->buscar(datos) == nullptr){
        persona * nueva_persona = new persona(datos[0],datos[1],datos[2],g);
        int grupo = datos[0][0]-'A';
        grupo_de_personas[grupo].push_back(nueva_persona);
        if(s)
            this->seleccionado = nueva_persona;
        return true;
    }
    else{
        return false;
    }
}
void arbol_genealogico::anadir_madre(string *datos, bool g,bool s){
    datos[1] = this->seleccionado->apellido2;
    if(this->buscar(datos) == nullptr){
        persona * m = Madre(this->seleccionado);
        if(m != nullptr){
            m = this->seleccionado->anadir_madre(datos[0],datos[2]);
            int grupo = datos[0][0]-'A';
            grupo_de_personas[grupo].push_back(m);
            if(s){
                this->seleccionado = m;
            }
        }
        else{
            cout<<"Error, el objeto seleccionado ya tiene madre\n";
        }
    }
    else{
        cout<<"Error, duplicación de persona\n";
    }
}
void arbol_genealogico::anadir_padre(string *datos, bool g,bool s){
    datos[1] = this->seleccionado->apellido1;
    if(this->buscar(datos) == nullptr){
        persona * p = Padre(this->seleccionado);
        if(p != nullptr){
            p = this->seleccionado->anadir_padre(datos[0],datos[2]);
            int grupo = datos[0][0]-'A';
            grupo_de_personas[grupo].push_back(p);
            if(s){
                this->seleccionado = p;
            }
        }
        else{
            cout<<"Error, el objeto seleccionado ya tiene padre\n";
        }
    }
    else{
        cout<<"Error, duplicación de persona\n";
    }
}
void arbol_genealogico::anadir_hijos(string* n,string* a,bool* g, int c){
    this->seleccionado->anadir_hijos(n,a,g,c);
}
void arbol_genealogico::anadir_hijos(string* n,persona* p,bool* g, int c){
    this->seleccionado->anadir_hijos(n,p,g,c);
}
arbol_genealogico::~arbol_genealogico()
{
}

#endif