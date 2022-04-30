#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <typeinfo>
#include <cstdio>

using namespace std;

class Interface
{
public:
    virtual istream& citire(istream& in) = 0;
    virtual ostream& afisare(ostream& out) const = 0 ;
};

class film: public Interface {
protected:
    string nume;
    int an_ap, durata;
public:
    //constr initializare fara parametrii
    film();

    //constructor initializare parametrii
    film(string nume_, int an_ap_, int durata_);

    //constructor copiere
    film(const film &film_);

    //destructor
     virtual ~film () {};

    //supracscriem op =
    film& operator = (const film &film2);

    //getters setters
    void set_nume (string alt_nume);
    string get_nume () const{
        return nume;
    }

    void set_an_ap (int an);
    int get_an_ap () const;

    void set_durata (int min);
    int get_durata () const;

    //supraincarcare operator <<
    friend ostream &operator<<(ostream& out, film& film);

    //supraincarcare operator >>
    friend istream &operator>>(istream& in, film& film);

    istream& citire(istream& in) override;
    ostream& afisare(ostream& out) const override;

    virtual void timp_secvente() = 0;
};

film :: film() {
//    strcpy(this -> nume, "$");
    this -> nume = "$";
    this -> an_ap = 0;
    this -> durata = 0;

}

film :: film (string const nume_, int an_ap_, int durata_)
{
//    size_t len = strlen(nume_);
//    nume = new char[len];
//    strcpy(nume, nume_);
    nume = nume_;
    an_ap = an_ap_;
    durata = durata_;
}

film :: film (const film &film_){
    nume = "$";
    an_ap = film_.an_ap;
    durata = film_.durata;

}


film &film :: operator = (const film& film2) {
    if (this!=&film2) {
        this->nume = film2.nume;
        this->an_ap = film2.an_ap;
        this->durata = film2.durata;
    }
    return *this;

}

void film ::set_nume(string const alt_nume) {
//    delete[] nume;
//    strcpy(nume, alt_nume);
    this->nume=alt_nume;
}


void film::set_an_ap(int an) {
    an_ap = an;
}

int film::get_an_ap() const {
    return an_ap;
}

void film::set_durata(int min) {
    durata = min;
}

int film::get_durata() const {
    return durata;
}


istream& film :: citire(istream& in) {
    cout << "Care este numele filmului?";
    in.ignore();
    getline(in, nume);
    cout << "In ce an a aparut filmul?";
    in >> this-> an_ap;
    try{
        if (an_ap < 0)
            throw(an_ap);
    }
    catch (int an){
        cout << "An incorect - Anul aparitiei nu poate fi negativ.\n";
        cout << "Anul introdus este: " << an << endl;
    }
    cout << "Care e durata (in minute) a filmului?";
    in >> this->durata;
    return in;
}

ostream &film ::afisare(ostream &out) const {
    out << "Numele filmului este: "<< this->nume;
    out << "Anul aparitiei filmului este: "<<this->an_ap;
    out << "Durata (in minute) a filmului este: "<< this->durata;
    return out;
}

istream& operator>>(istream& in, film& film){
    return film.citire(in);
}

ostream &operator<<(ostream& out, film& film){
    return film.afisare(out);
}


///----------------------------------------------------------------------------------------------------------------------------------------------------------///



class film_alb_negru: public film{
private:
    int color;
    int an_ap_color, nr_cadre;
public:
    //constr initializare fara parametrii
    film_alb_negru();

    //constructor initializare parametrii
    film_alb_negru(string nume, int an_ap, int durata, int color, int an_ap_color, int nr_cadre);

    //constructor copiere
    film_alb_negru(const film_alb_negru& film_);

    //destructor
    ~film_alb_negru() = default;

    //supracscriem op =
    film_alb_negru& operator=(const film_alb_negru &film2);

    istream& citire(istream& in) override;
    ostream& afisare(ostream& out) const override;
    void distanta();
    void timp_secvente();

};

film_alb_negru :: film_alb_negru():film(){
    color = 0;
    an_ap_color = 0;
    nr_cadre = 0;
}

film_alb_negru :: film_alb_negru(string const nume_, int an_ap_, int durata_, int color_, int an_ap_color_, int nr_cadre_) : film(nume_, an_ap_, durata_)
{
    nume = nume_;
    color = color_;
    an_ap = an_ap_;
    durata = durata_;
    an_ap_color = an_ap_color_;
    nr_cadre = nr_cadre_;

}

film_alb_negru :: film_alb_negru (const film_alb_negru &film_): film(film_){
    color = film_.color;
    an_ap_color = film_.an_ap_color;
    nr_cadre = film_.nr_cadre;

}

film_alb_negru &film_alb_negru :: operator = (const film_alb_negru &film2){

    film::operator=(film2);
    this->color = film2.color;
    this->an_ap = film2.an_ap;
    this->durata = film2.durata;
    this->an_ap_color = film2.an_ap_color;
    this->nr_cadre = film2.nr_cadre;

    return *this;

}

istream& film_alb_negru::citire(istream &in){
    film ::citire(in);
    string test;
    cout << "Filmul are si o varianta color? (DA/NU): ";

    in >> test;
    if (test == "DA" || test == "da" || test == "Da")
        color = 1;
    
    if (color){
        cout<<"Care este anul in care a aparut varianta color?";
        in>>this->an_ap_color;

    }
    else
        an_ap_color = 0;
    cout << "Cate cadre sunt prezentate in film?\n";
    in >> nr_cadre;
    return in;
}

ostream &film_alb_negru::afisare(ostream &out) const {
    film::afisare(out);
    if (color)
        out << "Filmul are si o varianta color."<<endl;
    else
        out <<"Filmul nu are si o varianta color."<<endl;
    if(color)
        out << "Anul aparitiei variantei color este " << this->an_ap_color<< " ."<<endl;
    out << "Filmul are " << this-> nr_cadre << " cadre.";
    return out;

}


void film_alb_negru::distanta() {
    if (!color)
        cout << "Filmul nu are o varianta color.";
    else
        cout << "Varianta color a filmului orginial a aparut dupa "<<an_ap_color-an_ap<< " ani.";
}

void film_alb_negru::timp_secvente() {
    cout << "Stiind ca filmul are " << nr_cadre << " de cadre, minutele alocate unui singur cadru sunt aproximativ " << durata/nr_cadre;
}


///-----------------------------------------------------------------------------------------------------------------------------------------------------------------///



class film_documentar: public film{
private:
    string tema;
    int nr_elem;
public:
    film_documentar();
    film_documentar(string nume, int an_ap, int durata, string tema, int nr_elem);
    film_documentar(const film_documentar& film_);
    film_documentar& operator = (const film_documentar& documentar);
    ~film_documentar() = default;
    istream& citire(istream& in) override;
    ostream& afisare(ostream& out) const override;
    //virtual void timp_elem();
    void timp_secvente();
};

film_documentar::film_documentar(): film() {
    this->tema = "fara_tema";
    this->nr_elem=0;
}

film_documentar::film_documentar (string const nume_, int an_ap_, int durata_, string tema_, int nr_elem_):film(nume_, an_ap_, durata_){
    this->tema=tema_;
    this->nr_elem=nr_elem_;
}


film_documentar ::film_documentar (const film_documentar &film_): film(film_){
    this->tema=film_.tema;
    this->nr_elem=film_.nr_elem;
}

film_documentar &film_documentar :: operator = (const film_documentar &documentar){

    film::operator=(documentar);
    this->tema =documentar.tema;
    this->nr_elem =documentar.nr_elem;

    return *this;

}
istream& film_documentar ::citire(istream &in) {
    film::citire(in);
    cout <<"Tema documentarului este (animale/plante/masini): ";
    in >> this->tema;
    cout << "Cate tipuri de " <<tema<<" sunt prezenetate in documentar?";
    in >> this->nr_elem;
    return in;
}

ostream &film_documentar::afisare(ostream &out) const {
    film::afisare(out);
    out<<"Tema documentarului este " <<tema<<endl;
    out <<"Sunt documentate " <<nr_elem<<" tipuri de"<<tema<<".\n";
    return out;
}

void film_documentar::timp_secvente() {
    cout << "Stiind ca timpul dedicat fiecarui tip de "<<tema<< " e aproximatix egal, timpul dedicat unui singur tip este de " <<  durata/nr_elem << " minute.";

}


///-----------------------------------------------------------------------------------------------------------------------------------------------------------------------///



class film_comedie: public film{
private:
    int sitcom;
    int nr_punchl;
public:
    film_comedie();
    film_comedie(string nume, int an_ap, int durata, int sitcom, int nr_punchl);
    film_comedie(const film_comedie& film_);
    film_comedie& operator = (const film_comedie& comedie);
    ~film_comedie() = default;
    istream& citire(istream& in) override;
    ostream& afisare(ostream& out) const override;
    //virtual void timp_elem();
    void timp_secvente();
};

film_comedie::film_comedie(): film() {
    this->sitcom = 0;
    this->nr_punchl=0;
}

film_comedie::film_comedie (string const nume_, int an_ap_, int durata_, int sitcom_, int nr_punchl_):film(nume_, an_ap_, durata_){
    this->sitcom=sitcom_;
    this->nr_punchl=nr_punchl_;
}


film_comedie::film_comedie(const film_comedie &film_): film(film_){
    this->sitcom=film_.sitcom;
    this->nr_punchl=film_.nr_punchl;
}

film_comedie &film_comedie :: operator = (const film_comedie &comedie){

    film::operator=(comedie);
    this->sitcom =comedie.sitcom;
    this->nr_punchl =comedie.nr_punchl;

    return *this;

}

istream& film_comedie::citire(istream &in) {
    film::citire(in);
    string test;
    cout << "Este filmul un sitcom? (DA/NU) ";
    in >> test;
    if (test == "DA" || test == "da" || test == "Da")
        sitcom = 1;
    cout << "Numarul de punchline-uri din film este de: ";
    in >> this->nr_punchl;
    return in;
}

ostream& film_comedie::afisare(ostream &out) const {
    film::afisare(out);
    if(sitcom)
        out << "Filmul " << nume<< "este un sitcom."<<endl;
    else
        cout <<"Filmul " << nume << "nu este un sitcom."<<endl;

    out <<"Filmul contine  " <<nr_punchl<<" de punchline-uri.\n";
    return out;
}

void film_comedie::timp_secvente() {
    cout << "Stiind ca pe parcursul filmului sunt " << nr_punchl <<"punchline-uri";
    cout << "timpul dedicat unui singur tip este de " <<  durata/nr_punchl << " minute";

}


///-----------------------------------------------------------------------------------------------------------------------------------------------------------------------///



class festival{
private:
    string locatie;
    int editie, nrmax_filme;
public:
    festival();
    festival(string locatie, int editie, int nrmax_filme);
    festival(const festival& fest);
    festival& operator = (const festival& fest);
    friend istream& operator>>(istream& in, festival& fest);
    friend ostream& operator<<(ostream& out, const festival& fest);
     ~festival(){};
    int get_nr_filme () const{ return nrmax_filme;}


};

festival::festival() {
    this->locatie = "$";
    this->editie=0;
    this-> nrmax_filme= 0;
}

festival::festival(string locatie, int editie, int nr_filme){
    this->locatie=locatie;
    this->editie=editie;
    this->nrmax_filme=nr_filme;
}

festival::festival(const festival& fest){
    this->locatie=fest.locatie;
    this->editie=fest.editie;
    this->nrmax_filme = fest.nrmax_filme;
}
festival& festival::operator = (const festival& fest){
    if(this!=&fest){
        this->locatie=fest.locatie;
        this->editie=fest.editie;
        this->nrmax_filme=fest.nrmax_filme;

    }
    return *this;
}

istream& operator>>(istream& in, festival& fest)
{
    cout << "Care este locatia festivalului?";
//    in>>fest.locatie;
    in.ignore();
    getline(in, fest.locatie);
    cout <<"A cata editie a festivalului este?";
    in>>fest.editie;
    cout<<"Care este numarul maxim de filme care se se pot proiecta la aceasta editie?";
    in>>fest.nrmax_filme;
    return in;

}


ostream& operator<<(ostream& out, const festival& fest){
    out<<"Locatia festivaluui este: "<<fest.locatie<<endl;
    out<<"Este a "<<fest.editie<<"-a a festivalului."<<endl;
    out<<"Se vor proiecta "<<fest.nrmax_filme <<"filme."<<endl;
    return out;

}
int main() {

    festival fest;

    cin >> fest;

    vector <film*> filme;

    int k = 0, nr =0 ;

    while(k!=3) {
        cout << "\n 1 - Adaugarea unui film care va fi proiectat la festival\n\n 2 - Afisarea filmelor care vor fi proiectate la festival. \n\n 3 - STOP!\n\n";
        cin >> k;
        switch (k) {
            case 1:{
                int f;
                cout << "Tasteaza 1 daca urmeaza sa adaugi un film alb-negru.\n Tasteaza 2 daca urmeaza sa adaugi un film documentar.\n Tasteaza 3 daca urmeaza sa adaugi un film de comedie.";
                if (f==1 & nr <= fest.get_nr_filme()){
                        film_alb_negru *film = new film_alb_negru;
                        cin >> *film;

                        filme.push_back(film);
                        nr++;
                    }

                else if (f==2 & nr <= fest.get_nr_filme()){
                        film_documentar *film = new film_documentar;
                        cin >> *film;

                        filme.push_back(film);
                        nr++;
                    }

                else if (f==3 & nr <= fest.get_nr_filme()) {
                    film_comedie *film = new film_comedie;
                    cin >> *film;

                    filme.push_back(film);
                    nr++;

                }
                else if(f>3)
                    cout << "Nu exista categoria de filme " << f;

                break;
            }

            case 2:{
                for (auto i = filme.begin(); i != filme.end(); ++i)
                    cout << *i << endl;

                break;
            }
            case 3:{
                break;
            }
            default:{
                cout << "Comanda incorecta!\n";
                break;
            }

        }

    }

    return 0;
}