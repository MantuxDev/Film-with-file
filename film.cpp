#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Definizione tipi variabili
struct film{
    string titolo;
    string regista;
    string attore;
};

// Definizioni costanti
const int e=100;

// Prototipi
int menu();
void carica(fstream &film_old,int &n,fstream &var_counter);
void tabella(fstream &film_old,fstream &var_counter,film v[e]);
void ordina(film v[], int n, fstream &nuovo);


int main(){

    int s,n;
    film v[e];
    fstream film_old,film_new,var_counter;

    var_counter.open("var_counter.txt",ios::in);
    if(var_counter.is_open() && !(var_counter>>n)){
        n=0;
    }
    else{
        tabella(film_old,var_counter,v);
    }

    var_counter.close();

    do{
        s=menu();

        switch(s){

            case 1:{
                carica(film_old,n,var_counter);
                cin.ignore();
                tabella(film_old,var_counter,v);
                break;
            }

            case 2:{
                if(n>0){
                    ordina(v,n,film_new);
                }
                else{
                    cout<<"ERRORE: non ci sono film da ordinare"<<endl;
                }
                break;
            }

            case 0:{
                cout<<"Arrivederci"<<endl;
                break;
            }

            default:{
                cout<<"ERRORE: scelta non valida"<<endl;
                break;
            }
        }

    }while(s!=0);

    return 0;
}


// Prototipi
int menu(){
    int s;

    cout<<"\t-----MENU-----"<<endl;
    cout<<"1) Inserisci i film"<<endl;
    cout<<"2) Ordina film"<<endl;
    cout<<"0) Esci"<<endl;

    cout<<"\nInserisci scelta: ";
    cin>>s;

    return s;
}

void carica(fstream &film_old,int &n,fstream &var_counter){
    char ris='n';
    film temp;

    film_old.open("film_old.txt",ios::app);
    var_counter.open("var_counter.txt",ios::out);

    

    do{
        cin.ignore();

        if(ris=='S'){
            film_old<<endl;
        }

        cout<<"Inserisci il titolo dell' "<<n+1<<" film: ";
        getline(cin,temp.titolo);

        cout<<"Inserisci il regista dell' "<<n+1<<" film: ";
        getline(cin,temp.regista);

        cout<<"Inserisci l'attore dell' "<<n+1<<" film: ";
        getline(cin,temp.attore);

        film_old<<temp.titolo<<endl<<temp.regista<<endl<<temp.attore;

        cout<<"\nVuoi continuare[S/N]? ";
        cin>>ris;

        ris=toupper(ris);

        n++;

        cout<<endl;

    }while(ris=='S');

    var_counter<<n;

    var_counter.close();
    film_old.close();
}

void tabella(fstream &film_old,fstream &var_counter,film v[e]){
    film_old.open("film_old.txt",ios::in);
    var_counter.open("var_counter.txt",ios::in);

    int n;

    var_counter>>n;
    int i=0;

    while(!film_old.eof()){
        getline(film_old,v[i].titolo);
        getline(film_old,v[i].regista);
        getline(film_old,v[i].attore);
        i++;
    }
    
}

void ordina(film v[], int n, fstream &nuovo){

    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(v[i].titolo>v[j].titolo){
                swap(v[i],v[j]);
            }
        }
    }

    nuovo.open("film_new.txt",ios::out);

    for(int i=0;i<n;i++){
        nuovo<<v[i].titolo<<endl<<v[i].regista<<endl<<v[i].attore;
        if(i!=n-1){
            nuovo<<endl;
        }
    }

    nuovo.close();
}