#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
struct persona{
    persona*padre = nullptr;
    persona*madre = nullptr;
    vector<persona*> hijos;
    string nombres[2];
    string apellido_1;
    string apellido_2;
    bool genero;
    bool visitado = false;
};
void generar_familia_nuclear(vector<persona*> *grupo_de_personas,persona*hijo,string*apellidos,string*nombres_m,string*nombres_f,int contador);
void generar_hijos(vector<persona*> *grupo_de_personas,int c,persona*p,persona*m,string*apellidos,string*nombres_m,string*nombres_f,int contador){
    if(contador){
        for (int i = 0; i < c; i++){
            persona *nueva_persona= new persona();
            int n_1 = rand()%21;
            int n_2 = rand()%21;
            int g = rand()%2;
            nueva_persona->apellido_1 = p->apellido_1;
            nueva_persona->apellido_2 = m->apellido_1;
            nueva_persona->genero = g;
            if(g){
                nueva_persona->nombres[0] = nombres_m[n_1];
                nueva_persona->nombres[1] = nombres_m[n_2];
            }
            else{
                nueva_persona->nombres[0] = nombres_f[n_1];
                nueva_persona->nombres[1] = nombres_f[n_2];
            }
            nueva_persona->padre = p;
            nueva_persona->madre = m;
            grupo_de_personas->push_back(nueva_persona);
            m->hijos.push_back(nueva_persona);
            p->hijos.push_back(nueva_persona);
            /*Generación de hijos*/
            int hijos_p = rand()%2;
            if(hijos_p && contador != 1){
                int hijos_c = 1+rand()%3;
                /*Generación de esposa o esposo*/
                persona*pareja = new persona();
                n_1 = rand()%21;
                n_2 = rand()%21;
                int a_1 = rand()%30;
                int a_2 = rand()%30;
                pareja->genero = !nueva_persona->genero;
                persona * nuevo_padre;
                persona * nueva_madre;
                pareja->apellido_1 = apellidos[a_1];
                pareja->apellido_2 = apellidos[a_2];
                if(pareja->genero){
                    pareja->nombres[0] = nombres_m[n_1];
                    pareja->nombres[1] = nombres_m[n_2];
                    nuevo_padre = pareja;
                    nueva_madre = nueva_persona;
                }
                else{
                    pareja->nombres[0] = nombres_f[n_1];
                    pareja->nombres[1] = nombres_f[n_2];
                    nuevo_padre = nueva_persona;
                    nueva_madre = pareja;
                    
                }
                grupo_de_personas->push_back(pareja);
                /**/
                generar_hijos(grupo_de_personas,hijos_c,nuevo_padre,nueva_madre,apellidos,nombres_m,nombres_f,contador-1);
                /*Generar padres de pareja*/
                generar_familia_nuclear(grupo_de_personas,pareja,apellidos,nombres_m,nombres_f,contador-1);
            }
        }
    }
}
void generar_familia_nuclear(vector<persona*> *grupo_de_personas,persona*hijo,string*apellidos,string*nombres_m,string*nombres_f,int contador){
    if(contador){
        hijo->padre = new persona();
        hijo->madre = new persona();
        int a_p_2 = rand()%30;
        int a_m_2 = rand()%30;
        int n_p_1 = rand()%21;
        int n_p_2 = rand()%21;
        int n_m_1 = rand()%21;
        int n_m_2 = rand()%21;
        hijo->padre->apellido_1 = hijo->apellido_1;
        hijo->madre->apellido_1 = hijo->apellido_2;
        hijo->padre->genero = 1;
        hijo->madre->genero = 0;
        hijo->padre->apellido_2 = apellidos[a_p_2];
        hijo->madre->apellido_2 = apellidos[a_m_2];
        hijo->padre->nombres[0] = nombres_m[n_p_1];
        hijo->padre->nombres[1] = nombres_m[n_p_2];
        hijo->madre->nombres[0] = nombres_f[n_m_1];
        hijo->madre->nombres[1] = nombres_f[n_m_2];
        grupo_de_personas->push_back(hijo->padre);
        grupo_de_personas->push_back(hijo->madre);
        hijo->padre->hijos.push_back(hijo);
        hijo->madre->hijos.push_back(hijo);
        /*Generación de hijos*/
        int hijos_p = rand()%2;
        if(hijos_p){
            int hijos_c = 1+rand()%3;
            generar_hijos(grupo_de_personas,hijos_c,hijo->padre,hijo->madre,apellidos,nombres_m,nombres_f,contador-1);
        }
        /*Generación de abuelos*/
        generar_familia_nuclear(grupo_de_personas,hijo->padre,apellidos,nombres_m,nombres_f,contador-1);
        generar_familia_nuclear(grupo_de_personas,hijo->madre,apellidos,nombres_m,nombres_f,contador-1);
    }
}
void imprimir_graphiz(persona* sujeto){
    if(!sujeto->visitado){    
        sujeto->visitado = true;
        for(int i=0; i < sujeto->hijos.size(); i++){
            cout<<char(34);
            cout<<sujeto->nombres[0]<<" "<<sujeto->nombres[1]<<" "<<sujeto->apellido_1<<" "<<sujeto->apellido_2;
            cout<<char(34);
            cout<<" -> ";
            cout<<char(34);
            cout<<sujeto->hijos[i]->nombres[0]<<" "<<sujeto->hijos[i]->nombres[1]<<" "<<sujeto->hijos[i]->apellido_1<<" "<<sujeto->hijos[i]->apellido_2;
            cout<<char(34);
            cout<<"\n";
        }
        if(sujeto->padre != nullptr){
            imprimir_graphiz(sujeto->padre);
            imprimir_graphiz(sujeto->madre);
        }
        for(int i=0; i < sujeto->hijos.size(); i++){
            imprimir_graphiz(sujeto->hijos[i]);
        }
    }
}
void imprimir_arbol(persona* sujeto){
    if(!sujeto->visitado){    
        sujeto->visitado = true;
        cout<<sujeto->nombres[0]<<" "<<sujeto->nombres[1]<<" "<<sujeto->apellido_1<<" "<<sujeto->apellido_2<<":\n";
        if(sujeto->padre != nullptr){
            cout<<"Padre: "<<sujeto->padre->nombres[0]<<" "<<sujeto->padre->nombres[1]<<" "<<sujeto->padre->apellido_1<<" "<<sujeto->padre->apellido_2<<"\n";
            cout<<"Madre: "<<sujeto->madre->nombres[0]<<" "<<sujeto->madre->nombres[1]<<" "<<sujeto->madre->apellido_1<<" "<<sujeto->madre->apellido_2<<"\n";
        }
        for(int i=0; i < sujeto->hijos.size(); i++){
            cout<<"Hijo "<<i+1<<": "<<sujeto->hijos[i]->nombres[0]<<" "<<sujeto->hijos[i]->nombres[1]<<" "<<sujeto->hijos[i]->apellido_1<<" "<<sujeto->hijos[i]->apellido_2<<"\n";
        }
        cout<<"\n";
        if(sujeto->padre != nullptr){
            imprimir_arbol(sujeto->padre);
            imprimir_arbol(sujeto->madre);
        }
        for(int i=0; i < sujeto->hijos.size(); i++){
            imprimir_arbol(sujeto->hijos[i]);
        }
    }
}
int main(){
    string apellidos[30]={"Perez","Jimenez","Garcia","Rodriguez","Navarro", "Ruiz","Diaz","Serrano", "Hernandez","Munoz","Saez","Rubio","Sumar","Molina","Cano","Gonzales","Ortega","Alarcon","Pardo","Nunez", "Moya","Arenas","Collado", "Ramirez","Picazo","Chipana","Ancaesh","Mamani","Quispe","Zumaran"};
    string nombres_m[21]={"Jose","Abelardo","Mario","Pedro","Angel","David","Alejandro","Carlos","Rafael","Juan","Daniel","Miguel","Jesus","Fernando","Francisco""Javier","Antonio","Luis","Manuel","Joaquin","Sergio","Andres"};
    string nombres_f[21]={"Nina","Elena","Marta","Manuela","Rosa","Rosario","Carmen","Isabela","Laura","Teresa","Ana","Alicia","Andrea","Irene","Juana","Jun","Luna","Serena","Ruri","Rin","Lupe"};
    int n=1;
    int nivel_de_familiaridad = 4;
    vector<persona*> grupo_de_personas;
    persona*funcionarios;
    funcionarios = new persona[n];
    for (int i = 0; i < n; i++){
        int n_1 = rand()%21;
        int n_2 = rand()%21;
        int a_1 = rand()%30;
        int a_2 = rand()%30;
        int g = rand()%2;
        funcionarios[i].genero = g;
        funcionarios[i].apellido_1 = apellidos[a_1];
        funcionarios[i].apellido_2 = apellidos[a_2];
        if(g){
            funcionarios[i].nombres[0] = nombres_m[n_1];
            funcionarios[i].nombres[1] = nombres_m[n_1];
        }
        else{
            funcionarios[i].nombres[0] = nombres_f[n_1];
            funcionarios[i].nombres[1] = nombres_f[n_1];
        }
        grupo_de_personas.push_back(&funcionarios[i]);
        generar_familia_nuclear(&grupo_de_personas,&funcionarios[i],apellidos,nombres_m,nombres_f,nivel_de_familiaridad);
        int hijos_p = rand()%2;
        if(hijos_p){
            int hijos_c = 1+rand()%3;
            /*Generación de esposa o esposo*/
            persona*pareja = new persona();
            n_1 = rand()%21;
            n_2 = rand()%21;
            a_1 = rand()%30;
            a_2 = rand()%30;
            pareja->genero = !funcionarios[i].genero;
            persona * nuevo_padre;
            persona * nueva_madre;
            pareja->apellido_1 = apellidos[a_1];
            pareja->apellido_2 = apellidos[a_2];
            if(pareja->genero){
                pareja->nombres[0] = nombres_m[n_1];
                pareja->nombres[1] = nombres_m[n_2];
                nuevo_padre = pareja;
                nueva_madre = &funcionarios[i];
            }
            else{
                pareja->nombres[0] = nombres_f[n_1];
                pareja->nombres[1] = nombres_f[n_2];
                nuevo_padre = &funcionarios[i];
                nueva_madre = pareja;
            }
            grupo_de_personas.push_back(pareja);
            /**/
            generar_hijos(&grupo_de_personas,hijos_c,nuevo_padre,nueva_madre,apellidos,nombres_m,nombres_f,nivel_de_familiaridad);
            /*Generar padres de pareja*/
            generar_familia_nuclear(&grupo_de_personas,pareja,apellidos,nombres_m,nombres_f,nivel_de_familiaridad);
        }
    }
    for (int i = 0; i < n; i++){
        imprimir_graphiz(&funcionarios[i]);
    }
    return 0;
}