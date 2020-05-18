#include <iostream>

class Piesa
{
public:
	Piesa(char Culoare) : mCuloare(Culoare) {}
	~Piesa() {}
	virtual char GetPiesa() = 0;
	char GetCuloare() {
		return mCuloare;
	}
        bool VerificareMutare(int RandPlecare, int ColoanaPlecare, int RandDestinatie, int ColoanaDestinatie, Piesa* TablaDeJocRepr[8][8]) {
		Piesa* Destinatie = TablaDeJocRepr[RandDestinatie][ColoanaDestinatie];
		if ((Destinatie == 0) || (mCuloare != Destinatie->GetCuloare())) {
			return VerificareAdrese(RandPlecare, ColoanaPlecare, RandDestinatie, ColoanaDestinatie, TablaDeJocRepr);
		}
		return false;
	}
private:
	virtual bool VerificareAdrese(int RandPlecare, int ColoanaPlecare, int RandDestinatie, int ColoanaDestinatie, Piesa* TablaDeJocRepr[8][8]) = 0;
	char mCuloare;
};

class Pion : public Piesa
{
public:
	Pion(char Culoare) : Piesa(Culoare) {}
	~Pion() {}
private:
	virtual char GetPiesa() {
		return 'P';
	}
	bool VerificareAdrese(int RandPlecare, int ColoanaPlecare, int RandDestinatie, int ColoanaDestinatie, Piesa* TablaDeJocRepr[8][8]) {
		Piesa* Destinatie = TablaDeJocRepr[RandDestinatie][ColoanaDestinatie];
		if (Destinatie == 0) {
			// Locatia destinatiei este libera
			if (ColoanaPlecare == ColoanaDestinatie) {
				if (GetCuloare() == 'W') {
					if (RandDestinatie == RandPlecare + 1) {
						return true;
					}
				} else {
					if (RandDestinatie == RandPlecare - 1) {
						return true;
					}
				}
			}
		} else {
			// Locatia destinatiei are o piesa corecta(de cealalta culoare)
			if ((ColoanaPlecare == ColoanaDestinatie + 1) || (ColoanaPlecare == ColoanaDestinatie - 1)) {
				if (GetCuloare() == 'W') {
					if (RandDestinatie == RandPlecare + 1) {
						return true;
					}
				} else {
					if (RandDestinatie == RandPlecare - 1) {
						return true;
					}
				}
			}
		}
		return false;
	}
};

class Cal : public Piesa
{
public:
	Cal(char Culoare) : Piesa(Culoare) {}
	~Cal() {}
private:
	virtual char GetPiesa() {
		return 'N';
	}
	bool VerificareAdrese(int RandPlecare, int ColoanaPlecare, int RandDestinatie, int ColoanaDestinatie, Piesa* TablaDeJocRepr[8][8]) {
		// Locatia destinatiei nu e ocupata sau e ocupata de cealalta culoare
		if ((ColoanaPlecare == ColoanaDestinatie + 1) || (ColoanaPlecare == ColoanaDestinatie - 1)) {
			if ((RandPlecare == RandDestinatie + 2) || (RandPlecare == RandDestinatie - 2)) {
				return true;
			}
		}
		if ((ColoanaPlecare == ColoanaDestinatie + 2) || (ColoanaPlecare == ColoanaDestinatie - 2)) {
			if ((RandPlecare == RandDestinatie + 1) || (RandPlecare == RandDestinatie - 1)) {
				return true;
			}
		}
		return false;
	}
};

class Nebun : public Piesa
{
public:
	Nebun(char Culoare) : Piesa(Culoare) {}
	~Nebun() {}
private:
	virtual char GetPiesa() {
		return 'B';
	}
	bool VerificareAdrese(int RandPlecare, int ColoanaPlecare, int RandDestinatie, int ColoanaDestinatie, Piesa* TablaDeJocRepr[8][8]) {
		if ((ColoanaDestinatie - ColoanaPlecare == RandDestinatie - RandPlecare) || (ColoanaDestinatie - ColoanaPlecare == RandPlecare - RandDestinatie)) {
			// Verificam destinatiile diagonale pentru nebun
			int DiferentaDeRand = (RandDestinatie - RandPlecare > 0) ? 1 : -1;
			int DiferentaDeColoana = (ColoanaDestinatie - ColoanaPlecare > 0) ? 1 : -1;
			int RandPentruVerificat;
			int ColoanaPentruVerificat;
			for (RandPentruVerificat = RandPlecare + DiferentaDeRand, ColoanaPentruVerificat = ColoanaPlecare + DiferentaDeColoana;
				RandPentruVerificat !=  RandDestinatie;
				RandPentruVerificat = RandPentruVerificat + DiferentaDeRand, ColoanaPentruVerificat = ColoanaPentruVerificat + DiferentaDeColoana)
			{
				if (TablaDeJocRepr[RandPentruVerificat][ColoanaPentruVerificat] != 0) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
};

class Tura : public Piesa
{
public:
	Tura(char Culoare) : Piesa(Culoare) {}
	~Tura() {}
private:
	virtual char GetPiesa() {
		return 'R';
	}
	bool VerificareAdrese(int RandPlecare, int ColoanaPlecare, int RandDestinatie, int ColoanaDestinatie, Piesa* TablaDeJocRepr[8][8]) {
		if (RandPlecare == RandDestinatie) {
			// Verificam destinatiile posibile pentru tura cand randul ramane neschimbat
			int DiferentaDeColoana = (ColoanaDestinatie - ColoanaPlecare > 0) ? 1 : -1;
			for (int ColoanaPentruVerificat = ColoanaPlecare + DiferentaDeColoana; ColoanaPentruVerificat !=  ColoanaDestinatie; ColoanaPentruVerificat = ColoanaPentruVerificat + DiferentaDeColoana) {
				if (TablaDeJocRepr[RandPlecare][ColoanaPentruVerificat] != 0) {
					return false;
				}
			}
			return true;
		} else if (ColoanaDestinatie == ColoanaPlecare) {
			// Verificam destinatiile posibile pentru tura arunci cand coloana ramane neschimbata
			int DiferentaDeRand = (RandDestinatie - RandPlecare > 0) ? 1 : -1;
			for (int RandPentruVerificat = RandPlecare + DiferentaDeRand; RandPentruVerificat !=  RandDestinatie; RandPentruVerificat = RandPentruVerificat + DiferentaDeRand) {
				if (TablaDeJocRepr[RandPentruVerificat][ColoanaPlecare] != 0) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
};

class Regina : public Piesa
{
public:
	Regina(char Culoare) : Piesa(Culoare) {}
	~Regina() {}
private:
	virtual char GetPiesa() {
		return 'Q';
	}
	bool VerificareAdrese(int RandPlecare, int ColoanaPlecare, int RandDestinatie, int ColoanaDestinatie, Piesa* TablaDeJocRepr[8][8]) {
		if (RandPlecare == RandDestinatie) {
			// Verificam ca pentru tura pentru acelasi rand
			int DiferentaDeColoana = (ColoanaDestinatie - ColoanaPlecare > 0) ? 1 : -1;
			for (int ColoanaPentruVerificat = ColoanaPlecare + DiferentaDeColoana; ColoanaPentruVerificat !=  ColoanaDestinatie; ColoanaPentruVerificat = ColoanaPentruVerificat + DiferentaDeColoana) {
				if (TablaDeJocRepr[RandPlecare][ColoanaPentruVerificat] != 0) {
					return false;
				}
			}
			return true;
		} else if (ColoanaDestinatie == ColoanaPlecare) {
			// Verificam la fel pentru aceeasi coloana
			int DiferentaDeRand = (RandDestinatie - RandPlecare > 0) ? 1 : -1;
			for (int RandPentruVerificat = RandPlecare + DiferentaDeRand; RandPentruVerificat !=  RandDestinatie; RandPentruVerificat = RandPentruVerificat + DiferentaDeRand) {
				if (TablaDeJocRepr[RandPentruVerificat][ColoanaPlecare] != 0) {
					return false;
				}
			}
			return true;
		} else if ((ColoanaDestinatie - ColoanaPlecare == RandDestinatie - RandPlecare) || (ColoanaDestinatie - ColoanaPlecare == RandPlecare - RandDestinatie)) {
			// Verificam la fel ca la nebun
			int DiferentaDeRand = (RandDestinatie - RandPlecare > 0) ? 1 : -1;
			int DiferentaDeColoana = (ColoanaDestinatie - ColoanaPlecare > 0) ? 1 : -1;
			int RandPentruVerificat;
			int ColoanaPentruVerificat;
			for (RandPentruVerificat = RandPlecare + DiferentaDeRand, ColoanaPentruVerificat = ColoanaPlecare + DiferentaDeColoana;
				RandPentruVerificat !=  RandDestinatie;
				RandPentruVerificat = RandPentruVerificat + DiferentaDeRand, ColoanaPentruVerificat = ColoanaPentruVerificat + DiferentaDeColoana)
			{
				if (TablaDeJocRepr[RandPentruVerificat][ColoanaPentruVerificat] != 0) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
};

class Rege : public Piesa
{
public:
	Rege(char Culoare) : Piesa(Culoare) {}
	~Rege() {}
private:
	virtual char GetPiesa() {
		return 'K';
	}
	bool VerificareAdrese(int RandPlecare, int ColoanaPlecare, int RandDestinatie, int ColoanaDestinatie, Piesa* TablaDeJocRepr[8][8]) {
		int DiferentaRanduri = RandDestinatie - RandPlecare;
		int DiferentaColoane = ColoanaDestinatie - ColoanaPlecare;
		if (((DiferentaRanduri >= -1) && (DiferentaRanduri <= 1)) &&
			((DiferentaColoane >= -1) && (DiferentaColoane <= 1)))
		{
			return true;
		}
		return false;
	}
};

class TablaSah
{
public:
	TablaSah() {
		for (int NumarRand = 0; NumarRand < 8; ++NumarRand) {
			for (int NumarColoana = 0; NumarColoana < 8; ++NumarColoana) {
				mTablaDeJocRepr[NumarRand][NumarColoana] = 0;
			}
		}
		// Punem pe tabla piesele negre la desttinatia corespunzatoare
		for (int NumarColoana = 0; NumarColoana < 8; ++NumarColoana) {
			mTablaDeJocRepr[6][NumarColoana] = new Pion('B');
		}
		mTablaDeJocRepr[7][0] = new Tura('B');
		mTablaDeJocRepr[7][1] = new Cal('B');
		mTablaDeJocRepr[7][2] = new Nebun('B');
		mTablaDeJocRepr[7][3] = new Rege('B');
		mTablaDeJocRepr[7][4] = new Regina('B');
		mTablaDeJocRepr[7][5] = new Nebun('B');
		mTablaDeJocRepr[7][6] = new Cal('B');
		mTablaDeJocRepr[7][7] = new Tura('B');
		// Punem pe tabla piesele albe la destinatia corespunzatoare
		for (int NumarColoana = 0; NumarColoana < 8; ++NumarColoana) {
			mTablaDeJocRepr[1][NumarColoana] = new Pion('W');
		}
		mTablaDeJocRepr[0][0] = new Tura('W');
		mTablaDeJocRepr[0][1] = new Cal('W');
		mTablaDeJocRepr[0][2] = new Nebun('W');
		mTablaDeJocRepr[0][3] = new Rege('W');
		mTablaDeJocRepr[0][4] = new Regina('W');
		mTablaDeJocRepr[0][5] = new Nebun('W');
		mTablaDeJocRepr[0][6] = new Cal('W');
		mTablaDeJocRepr[0][7] = new Tura('W');
	}
	~TablaSah() {
		for (int NumarRand = 0; NumarRand < 8; ++NumarRand) {
			for (int NumarColoana = 0; NumarColoana < 8; ++NumarColoana) {
				delete mTablaDeJocRepr[NumarRand][NumarColoana];
				mTablaDeJocRepr[NumarRand][NumarColoana] = 0;
			}
		}
	}

	void Print() {
		using namespace std;
		const int LatimeUnitate = 4;
		const int InaltimeUnitate = 3;
		for (int NumarRand = 0; NumarRand < 8*InaltimeUnitate; ++NumarRand) {
			int NumarRandLocatie = NumarRand/InaltimeUnitate;
			// Adaugam numerele pozitiilor pentru randuri
			if (NumarRand % 3 == 1) {
				cout << '-' << (char)('1' + 7 - NumarRandLocatie) << '-';
			} else {
				cout << "---";
			}
			// Printam tabla de sah
			for (int NumarColoana = 0; NumarColoana < 8*LatimeUnitate; ++NumarColoana) {
				int NumarColoanaLocatie = NumarColoana/LatimeUnitate;
				if (((NumarRand % 3) == 1) && ((NumarColoana % 4) == 1 || (NumarColoana % 4) == 2) && mTablaDeJocRepr[7-NumarRandLocatie][NumarColoanaLocatie] != 0) {
					if ((NumarColoana % 4) == 1) {
						cout << mTablaDeJocRepr[7-NumarRandLocatie][NumarColoanaLocatie]->GetCuloare();
					} else {
						cout << mTablaDeJocRepr[7-NumarRandLocatie][NumarColoanaLocatie]->GetPiesa();
					}
				} else {
					if ((NumarRandLocatie + NumarColoanaLocatie) % 2 == 1) {
						cout << '*';
					} else {
						cout << ' ';
					}
				}
			}
			cout << endl;
		}
		// Adaugam numerele pozitiilor pentru coloane
		for (int NumarRand = 0; NumarRand < InaltimeUnitate; ++NumarRand) {
			if (NumarRand % 3 == 1) {
				cout << "---";
				for (int NumarColoana = 0; NumarColoana < 8*LatimeUnitate; ++NumarColoana) {
					int NumarColoanaLocatie = NumarColoana/LatimeUnitate;
					if ((NumarColoana % 4) == 1) {
						cout << (NumarColoanaLocatie + 1);
					} else {
						cout << '-';
					}
				}
				cout << endl;
			} else {
				for (int NumarColoana = 1; NumarColoana < 9*LatimeUnitate; ++NumarColoana) {
					cout << '-';
				}
				cout << endl;
			}
		}
	}

	bool EsteRegeleAtacat(char Culoare) {
		// Gasim regele respectiv
		int RandRege;
		int ColoanaRege;
		for (int NumarRand = 0; NumarRand < 8; ++NumarRand) {
			for (int NumarColoana = 0; NumarColoana < 8; ++NumarColoana) {
				if (mTablaDeJocRepr[NumarRand][NumarColoana] != 0) {
					if (mTablaDeJocRepr[NumarRand][NumarColoana]->GetCuloare() == Culoare) {
						if (mTablaDeJocRepr[NumarRand][NumarColoana]->GetPiesa() == 'K') {
							RandRege = NumarRand;
							ColoanaRege = NumarColoana;
						}
					}
				}
			}
		}
		//Parcurgem piesele adversarului sa vedem daca exista vreuna care ataca regele
		for (int NumarRand = 0; NumarRand < 8; ++NumarRand) {
			for (int NumarColoana = 0; NumarColoana < 8; ++NumarColoana) {
				if (mTablaDeJocRepr[NumarRand][NumarColoana] != 0) {
					if (mTablaDeJocRepr[NumarRand][NumarColoana]->GetCuloare() != Culoare) {
						if (mTablaDeJocRepr[NumarRand][NumarColoana]->VerificareMutare(NumarRand, NumarColoana, RandRege, ColoanaRege, mTablaDeJocRepr)) {
							return true;
						}
					}
				}
			}
		}

		return false;
	}

	bool PoateMuta(char Culoare) {
		// Parcurgem tabla de sah
		for (int NumarRand = 0; NumarRand < 8; ++NumarRand) {
			for (int NumarColoana = 0; NumarColoana < 8; ++NumarColoana) {
				if (mTablaDeJocRepr[NumarRand][NumarColoana] != 0) {
					// Verificam daca locatia este o piesa a jucatorului si daca poate muta legal
					if (mTablaDeJocRepr[NumarRand][NumarColoana]->GetCuloare() == Culoare) {
						for (int RandMutare = 0; RandMutare < 8; ++RandMutare) {
							for (int ColoanaMutarii = 0; ColoanaMutarii < 8; ++ColoanaMutarii) {
								if (mTablaDeJocRepr[NumarRand][NumarColoana]->VerificareMutare(NumarRand, NumarColoana, RandMutare, ColoanaMutarii, mTablaDeJocRepr)) {
									// Dupa mutare verificam daca regele este in sah
									Piesa* PointerTemp					= mTablaDeJocRepr[RandMutare][ColoanaMutarii];
									mTablaDeJocRepr[RandMutare][ColoanaMutarii]	= mTablaDeJocRepr[NumarRand][NumarColoana];
									mTablaDeJocRepr[NumarRand][NumarColoana]			= 0;
									bool bPoateMuta = !EsteRegeleAtacat(Culoare);
									// Revenirea la starea initiala
									mTablaDeJocRepr[NumarRand][NumarColoana]			= mTablaDeJocRepr[RandMutare][ColoanaMutarii];
									mTablaDeJocRepr[RandMutare][ColoanaMutarii]	= PointerTemp;
									if (bPoateMuta) {
										return true;
									}
								}
							}
						}
					}
				}
			}
		}
		return false;
	}

	Piesa* mTablaDeJocRepr[8][8];
};

class JoculDeSah
{
public:
	JoculDeSah() : JucatorLaMutare('W') {}
	~JoculDeSah() {}

	void Start() {
		do {
			GetMutare(mJocSah.mTablaDeJocRepr);
			UrmatorulJucator();
		} while (!FinalJoc());
		mJocSah.Print();
	}

	void GetMutare(Piesa* TablaDeJocRepr[8][8]) {
		using namespace std;
		bool EMutareaValida		= false;
		do {
			mJocSah.Print();

			// Primim input si transformam in coordonate
			cout << JucatorLaMutare << " la mutare: ";
			int AdresaInitialaMutare;
			cin >> AdresaInitialaMutare;
			int AdresaInitialaRand = (AdresaInitialaMutare / 10) - 1;
			int AdresaInitialaColoana = (AdresaInitialaMutare % 10) - 1;

			cout << "Catre: ";
			int AdresaFinalaMutare;
			cin >> AdresaFinalaMutare;
			int AdresaFinalaRand = (AdresaFinalaMutare / 10) - 1;
			int AdresaFinalaColoana = (AdresaFinalaMutare % 10) - 1;

			// Verificam validitatea input-ului
			if ((AdresaInitialaRand >= 0 && AdresaInitialaRand <= 7) &&
				(AdresaInitialaColoana >= 0 && AdresaInitialaColoana <= 7) &&
				(AdresaFinalaRand >= 0 && AdresaFinalaRand <= 7) &&
				(AdresaFinalaColoana >= 0 && AdresaFinalaColoana <= 7)) {
				// Verificam piesa
				Piesa* PiesaDeMutat = TablaDeJocRepr[AdresaInitialaRand][AdresaInitialaColoana];
				// Verificam culoarea
				if ((PiesaDeMutat != 0) && (PiesaDeMutat->GetCuloare() == JucatorLaMutare)) {
					// Verificam destinatia
					if (PiesaDeMutat->VerificareMutare(AdresaInitialaRand, AdresaInitialaColoana, AdresaFinalaRand, AdresaFinalaColoana, TablaDeJocRepr)) {
						// Mutarea este executata
						Piesa* PointerTemp					= TablaDeJocRepr[AdresaFinalaRand][AdresaFinalaColoana];
						TablaDeJocRepr[AdresaFinalaRand][AdresaFinalaColoana]		= TablaDeJocRepr[AdresaInitialaRand][AdresaInitialaColoana];
						TablaDeJocRepr[AdresaInitialaRand][AdresaInitialaColoana]	= 0;
						// Verificam ca jucatorul sa nu fie in sah
						if (!mJocSah.EsteRegeleAtacat(JucatorLaMutare)) {
							delete PointerTemp;
							EMutareaValida = true;
						} else { // Daca este in sah revenim la starea initiala
							TablaDeJocRepr[AdresaInitialaRand][AdresaInitialaColoana] = TablaDeJocRepr[AdresaFinalaRand][AdresaFinalaColoana];
							TablaDeJocRepr[AdresaFinalaRand][AdresaFinalaColoana]		= PointerTemp;
						}
					}
				}
			}
			if (!EMutareaValida) {
				cout << "Mutarea NU este valida" << endl;
			}
		} while (!EMutareaValida);
	}

	void UrmatorulJucator() {
		JucatorLaMutare = (JucatorLaMutare == 'W') ? 'B' : 'W';
	}

	bool FinalJoc() {
		// Verificam daca se poate munta. Daca nu verificam daca este sah-mat sau pat
		bool bPoateMuta(false);
		bPoateMuta = mJocSah.PoateMuta(JucatorLaMutare);
		if (!bPoateMuta) {
			if (mJocSah.EsteRegeleAtacat(JucatorLaMutare)) {
				UrmatorulJucator();
				std::cout << "Sah-mat, " << JucatorLaMutare << " a castigat!" << std::endl;
			} else {
				std::cout << "Egalitate!" << std::endl;
			}
		}
		return !bPoateMuta;
	}
private:
	TablaSah mJocSah;
	char JucatorLaMutare;
};

int main() {
	JoculDeSah Sah;
	Sah.Start();
	return 0;
}

