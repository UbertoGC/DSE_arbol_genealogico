#ifndef PERSONA_H
#define PERSONA_H
#include <vector>
#include <iostream>
using namespace std;
class arbol_genealogico;
class persona;
vector<persona*> Hermanos_Hermanas(persona*a){
    int c=0;
    vector<persona*>resultado;
    if(a->padre != nullptr){
        resultado = a->padre->hijos;
        if(a->madre != nullptr){
            for (auto it:a->madre->hijos){
                bool bandera = true;
                for (int i = 0; i < a->padre->hijos.size(); i++){
                    if(resultado[i] == it){
                        bandera = false;
                        break;
                    }
                }
                if(bandera){
                    resultado.push_back(it);
                }
            }
        }
    }
    else if(a->madre != nullptr){
        resultado = a->madre->hijos;
    }
    return resultado;
}
persona* Tio(persona*a){

}
persona* Padre(persona*a){
    return a->padre;
}
persona* Madre(persona*a){
    return a->madre;
}
class persona
{
private:
    string nombres;
    string apellido1;
    string apellido2;
    persona * padre;
    persona * madre;
    bool genero;
    vector<persona*> hijos;
public:
    persona(string,string,string,bool);
    persona * anadir_padre(string,string);
    void anadir_padre(persona*);
    persona * anadir_madre(string,string);
    void anadir_madre(persona*);
    persona ** anadir_hijos(string*,string*,bool*,int);
    persona ** anadir_hijos(string*,persona*,bool*,int);
    ~persona();
    bool operator==(const string*datos);
    friend persona* Padre(persona*a);
    friend persona* Madre(persona*a);
    friend class arbol_genealogico;
    friend vector<persona*> Hermanos_Hermanas(persona*a);
};
persona::persona(string n, string a1, string a2, bool g)
{
    nombres = n;
    apellido1 = a1;
    apellido2 = a2;
    genero = g;
    this->padre = nullptr;
    this->madre = nullptr;
}
persona * persona::anadir_padre(string n, string a2){
    this->padre = new persona(n,this->apellido1,a2,1);
    this->padre->hijos.push_back(this);
    return this->padre;
}
void persona::anadir_padre(persona* p){
    this->padre = p;
    this->padre->hijos.push_back(this);
}
persona * persona::anadir_madre(string n, string a2){
    this->madre = new persona(n,this->apellido2,a2,0);
    this->madre->hijos.push_back(this);
    return this->madre;
}
void persona::anadir_madre(persona* m){
    this->madre = m;
    this->madre->hijos.push_back(this);
}
persona ** persona::anadir_hijos(string *n,string*a,bool*g,int c){
    persona ** nuevos_hijos = new persona*[c];
    for (int i = 0; i < c; i++){
        if(this->genero){
            nuevos_hijos[i] = new persona(n[i],this->apellido1,a[i],g[i]);
            nuevos_hijos[i]->padre = this;
        }
        else{
            nuevos_hijos[i] = new persona(n[i],a[i],this->apellido1,g[i]);
            nuevos_hijos[i]->madre = this;
        }
        this->hijos.push_back(nuevos_hijos[i]);
    }
    return nuevos_hijos;
}
persona ** persona::anadir_hijos(string *n,persona*pareja,bool*g,int c){
    persona ** nuevos_hijos = new persona*[c];
    for (int i = 0; i < c; i++){
        if(this->genero){
            nuevos_hijos[i] = new persona(n[i],this->apellido1,pareja->apellido1,g[i]);
            nuevos_hijos[i]->madre = pareja;
            nuevos_hijos[i]->padre = this;
        }
        else{
            nuevos_hijos[i] = new persona(n[i],pareja->apellido1,this->apellido1,g[i]);
            nuevos_hijos[i]->madre = this;
            nuevos_hijos[i]->padre = pareja;
        }
        this->hijos.push_back(nuevos_hijos[i]);
        pareja->hijos.push_back(nuevos_hijos[i]);
    }
    return nuevos_hijos;
}
bool persona::operator==(const string*datos){
    return this->nombres == datos[0] && this->apellido1 == datos[1] && this->apellido2 == datos[2];
}
persona::~persona()
{
}
#endif