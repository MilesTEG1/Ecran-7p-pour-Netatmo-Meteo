class Capteur {
    public:
        Capteur ();
    public:
        float  val_num;
        float  val_num_prec;    // La valeur précédente pour la comparaison
        String tendance;        // La variable text récupérée du flux Internet
        String val_texte;       // La variable text récupérée du flux Internet
};

class Capteur_CO2 : public Capteur {
    public:
        Capteur_CO2() :
                      un_membre_en_plus ( 0 ) {}
    public:
        int un_membre_en_plus;
};


class Salon {
    public:
        Capteur     temperature;
        Capteur     humidite;
        Capteur     pression;
        Capteur_CO2 CO2;
};



