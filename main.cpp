#include <iostream>
#include <string>
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
    ~film () = default;

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
    virtual void vorbeste(){};
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
//        delete[] nume;
//        strcpy(nume, film2.nume);
        nume = film2.nume;
        an_ap = film2.an_ap;
        durata = film2.durata;
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
////    in >> gets(this->nume);
//    in >> this-> nume;
    in.ignore();
    getline(in, nume);
    cout << "In ce an a aparut filmul?";
    in >> this-> an_ap;
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



class film_alb_negru: virtual public film{
private:
//    bool color;
    int color;
    int an_ap_color;
public:
    //constr initializare fara parametrii
    film_alb_negru();

    //constructor initializare parametrii
    film_alb_negru(string nume, int an_ap, int durata, int color, int an_ap_color);

    //constructor copiere
    film_alb_negru(const film_alb_negru& film_);

    //destructor
    ~film_alb_negru() = default;

    //supracscriem op =
    film_alb_negru& operator=(const film_alb_negru &film2);

    istream& citire(istream& in) override;
    ostream& afisare(ostream& out) const override;
    void distanta();
    void vorbeste() override{
        cout << "E film alb negru";
    };

};

film_alb_negru :: film_alb_negru():film(){
    color = 0;
    an_ap_color = 0;
}

film_alb_negru :: film_alb_negru(string const nume_, int an_ap_, int durata_, int color_, int an_ap_color_) : film(nume_, an_ap_, durata_)
{
//    size_t len = strlen(nume_);
//    nume = new char[len];
//    strcpy(nume, nume_);
    nume = nume_;
    color = color_;
    an_ap = an_ap_;
    durata = durata_;
    an_ap_color = an_ap_color_;

}

film_alb_negru :: film_alb_negru (const film_alb_negru &film_): film(film_){
    color = film_.color;
    an_ap_color = film_.an_ap_color;

}

film_alb_negru &film_alb_negru :: operator = (const film_alb_negru &film2){

    film::operator=(film2);
    this->color = film2.color;
    this->an_ap = film2.an_ap;
    this->durata = film2.durata;
    this->an_ap_color = film2.an_ap_color;

    return *this;

}

istream& film_alb_negru::citire(istream &in){
    film ::citire(in);
    string test;
    cout << "Filmul are si o varianta color? (DA/NU): ";
//    in>>this->color;
    in >> test;
    if (test == "DA" || test == "da" || test == "Da")
        color = 1;
    ///EXCEPTIE - an_ap_color > an_ap
    if (color){
        cout<<"Care este anul in care a aparut varianta color?";
        in>>this->an_ap_color;

    }
    else
        an_ap_color = 0;
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
    return out;

}


void film_alb_negru::distanta() {
    if (!color)
        cout << "Filmul nu are o varianta color, deci nu puteti accesa aceasta optiune.";
    else
        cout << "Varianta color a filmului orginial a aparut dupa "<<an_ap_color-an_ap<< " ani.";
}



///-----------------------------------------------------------------------------------------------------------------------------------------------------------------///



class film_documentar: virtual public film{
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
    virtual void timp_elem();
    void vorbeste() override{
        cout << "E film documentar";
    };
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

void film_documentar::timp_elem() {
    cout << "Stiind ca timpul dedicat fiecarui tip de "<<tema<< " e aproximatix egal, timpul dedicat unui singur tip este de " <<  durata/nr_elem << " minute.";

}


///-----------------------------------------------------------------------------------------------------------------------------------------------------------------------///



class film_comedie: virtual public film{
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
    virtual void timp_elem();
    void vorbeste() override{
        cout << "E film comedie";
    };
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

void film_comedie::timp_elem() {
    cout << "Stiind ca pe parcursul filmului sunt " << nr_punchl <<"punchlineuri";
    cout << "timpul dedicat unui singur tip este de " <<  durata/nr_punchl << " minute";

}


///-----------------------------------------------------------------------------------------------------------------------------------------------------------------------///



class festival{
private:
    string locatie;
    int editie, nr_filme;
public:
    festival();
    festival(string locatie, int editie, int nr_filme);
    festival(const festival& fest);
    festival& operator = (const festival& fest);
    friend istream& operator>>(istream& in, festival& fest);
    friend ostream& operator<<(ostream& out, const festival& fest);
     ~festival(){};
    int get_nr_filme () const{ return nr_filme;}


};

festival::festival() {
    this->locatie = "$";
    this->editie=0;
    this-> nr_filme= 0;
}

festival::festival(string locatie, int editie, int nr_filme){
    this->locatie=locatie;
    this->editie=editie;
    this->nr_filme=nr_filme;
}

festival::festival(const festival& fest){
    this->locatie=fest.locatie;
    this->editie=fest.editie;
    this->nr_filme = fest.nr_filme;
}
festival& festival::operator = (const festival& fest){
    if(this!=&fest){
        this->locatie=fest.locatie;
        this->editie=fest.editie;
        this->nr_filme=fest.nr_filme;

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
    cout<<"Cate filme se vor proiecta la aceasta editie?";
    in>>fest.nr_filme;
    return in;

}


ostream& operator<<(ostream& out, const festival& fest){
    out<<"Locatia festivaluui este: "<<fest.locatie<<endl;
    out<<"Este a "<<fest.editie<<"-a a festivalului."<<endl;
    out<<"Se vor proiecta "<<fest.nr_filme <<"filme."<<endl;
    return out;

}
int main() {

    festival fest;
    film_alb_negru AlbNegru;
    film_documentar Documentar;
    film_comedie Comedie;

    cin >> fest;

//    for (int j = 0; j  < fest.get_nr_filme(); j++) {

        film **list_film = new film *[3];
        list_film[0] = &AlbNegru;
        list_film[1] = &Documentar;
        list_film[2] = &Comedie;

        int citire;
        cout << "Tasteaza 0 pentru a citi filmul alb-negru.\n" << "Tasteaza 1 pentru a afisa filmul documentar. \n"
             << "Tasteaza 2 pentru a citi filmul comedie.\n";
        cin >> citire;
        if (citire == 0){
            cout << "Ai ales categoria  - FILME ALB NEGRU.\n";
            cin >> AlbNegru;
            AlbNegru.distanta();

        }
        else if (citire == 1) {
            cin >> Documentar;
            Documentar.timp_elem();
        } else if (citire == 2)
            cin >> Comedie;
        else cout << "Comanda " << citire << " nu exista!";

//        cout << AlbNegru << endl;
//        cout << Documentar << endl;
//        cout << Comedie;


//    char name[30];
//    printf("Enter name: ");
//    scanf("%[^\n]",name);
//
//    printf("Name is: %s\n",name);
    return 0;
}