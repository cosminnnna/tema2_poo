#include <iostream>
#include <cstring>

using namespace std;
class Interface
{
public:
    virtual istream& citire(istream& in) = 0;
    virtual ostream& afisare(ostream& out) const = 0 ;
};

class film: public Interface {
protected:
    char* nume;
    int an_ap, durata;
public:
    //constr initializare fara parametrii
    film();

    //constructor initializare parametrii
    film(const char *nume_, int an_ap_, int durata_);

    //constructor copiere
    film(const film &film_);

    //destructor
    ~film();

    //supracscriem op =
    film& operator = (const film &film2);

    //getters setters
    void set_nume (char *alt_nume);
    char* get_nume () const{
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

    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

};

film :: film() {
    this -> nume = "NiciunFilm";
    this -> an_ap = 0;
    this -> durata = 0;

}

film :: film (const char *nume_, int an_ap_, int durata_)
{
    size_t len = strlen(nume_);
    nume = new char[len];
    strcpy(nume, nume_);
    an_ap = an_ap_;
    durata = durata_;
}

film :: film (const film &film_){
    strcpy(nume, film_.nume);
    an_ap = film_.an_ap;
    durata = film_.durata;

}

film :: ~film() {
    delete[] nume;
}

film &film :: operator = (const film& film2) {
    if (this!=&film2) {
        delete[] nume;
        strcpy(nume, film2.nume);
        an_ap = film2.an_ap;
        durata = film2.durata;
    }
    return *this;

}

void film ::set_nume(char *alt_nume) {
    delete[] nume;
    strcpy(nume, alt_nume);
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


istream& film :: citire(istream& in){
    cout << "Care este numele filmului?";
    in >> this->nume;
    cout << "In ce an a aparut filmul?";
    in >> this-> an_ap;
    cout << "Care e durata (in minute) a filmului?";
    in >> this->durata;
}

ostream &film ::afisare(ostream &out) const {
    out << "Numele filmului este: "<< this->nume;
    out << "Anul aparitiei filmului este: "<<this->an_ap;
    out << "Durata (in minute) a filmului este: "<< this->durata;
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
    bool color;
    int an_ap_color;
public:
    //constr initializare fara parametrii
    film_alb_negru();

    //constructor initializare parametrii
    film_alb_negru(const char *nume, int an_ap, int durata, bool color, int an_ap_color);

    //constructor copiere
    film_alb_negru(const film_alb_negru& film_);

    //destructor
    ~film_alb_negru(){};

    //supracscriem op =
    film_alb_negru& operator=(const film_alb_negru &film2);

    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    virtual void distanta();

};

film_alb_negru :: film_alb_negru():film(){
    color = false;
    an_ap_color = 0;
}

film_alb_negru :: film_alb_negru(const char *nume_, int an_ap_, int durata_, bool color_, int an_ap_color_) : film(nume, an_ap, durata)
{
    size_t len = strlen(nume_);
    nume = new char[len];
    strcpy(nume, nume_);
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

istream& film_alb_negru::citire(istream &in) {
    film ::citire(in);
    cout << "Filmul are si o varianta color? (Tastati true in caz afirmativ, iar in caz contrar, tastati false): ";
    in>>this->color;
    if (color){
        cout<<"Care este anul in care a aparut varianta color?";
        in>>this->an_ap_color;

    }
    else
        an_ap_color = 0;
}

ostream &film_alb_negru::afisare(ostream &out) const {
    film::afisare(out);
    cout << "Este " << this->color << "ca filmul are o varianta color."<<endl;
    if(this->color)
        cout << "Anul aparitiei variantei color este " << this->an_ap_color<<endl;

}


void film_alb_negru::distanta() {
    if (!color)
        cout << "Nu puteti folosi aceasta optiune!";
    else
        cout << "Varianta color a filmului orginial a aparut dupa "<<an_ap-an_ap_color << " ani.";
}



///-----------------------------------------------------------------------------------------------------------------------------------------------------------------///



class film_documentar: virtual public film{
private:
    string tema;
    int nr_elem;
public:
    film_documentar();
    film_documentar(char *nume, int an_ap, int durata, string tema, int nr_elem);
    film_documentar(const film_documentar& film_);
    film_documentar& operator = (const film_documentar& documentar);
    ~film_documentar(){};
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    virtual void timp_elem();
};

film_documentar::film_documentar(): film() {
    this->tema = "fara_tema";
    this->nr_elem=0;
}

film_documentar::film_documentar (char *nume_, int an_ap_, int durata_, string tema_, int nr_elem_):film(nume, an_ap, durata){
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
    cout << "Tipurile de " <<tema<<" prezenetate in documentar sunt: ";
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
    cout << "Stiind ca timpul dedicat fiecarui tip de "<<tema<< " e aproximatix egal,";
    cout << "timpul dedicat unui singur tip este de " <<  durata/nr_elem << " minute";

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
   // ~festival(){};


};

festival::festival() {
    this->locatie = "no";
    this->editie=0;
    this-> editie = 0;
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
    in>>fest.locatie;
    cout <<"A cata editie a festivalului este?";
    in>>fest.editie;
    cout<<"Cate filme se vor proiecta la aceasta editie?";
    in>>fest.nr_filme;
    return in;
    
}


ostream& operator<<(ostream& out, const festival& fest){
    cout<<"Locatia festivaluui este: "<<fest.locatie<<endl;
    cout<<"Este a "<<fest.editie<<"-a a festivalului."<<endl;
    cout<<"Se vor proiecta "<<fest.nr_filme <<"filme."<<endl;
    
}
int main() {



    return 0;
}