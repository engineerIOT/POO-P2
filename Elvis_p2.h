#include <iostream>
using namespace std;

class Funcao {
public:
	Funcao(Funcao* f) { }
	Funcao() { cout << "(" << this << ") Funcao Constructed!" << endl; } //construtor padrao
	virtual ~Funcao() {} //destrutor padrao
	double operator() (double x) 	{}
	double integrar (Funcao* f, double x0, double x1, double step){}

};

class Constante : public Funcao {
public:
	double _value;
	Constante(double val) : _value(val) { cout << "(" << this << ") Constante(" << _value << ") Constructed!" << endl; }
private:
	//Constante(double val) : _value(val) { cout << "(" << this << ") Constante(" << _value << ") Constructed!" << endl; }
	double operator()(double x) {
		return _value;
	}
};




/*
class Seno : public Funcao {};
class Coseno : public Funcao {};
class FuncaoAgregada : public Funcao {};
class Escalar : public Funcao {};
class Potencial : public Funcao {};
class Exponencial : public Funcao {};*/




int main()
{
	Funcao ();
	Constante a(5);
	
}

