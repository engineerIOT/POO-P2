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
private:
	double _value;
public:
	Constante(double val) : _value(val) { cout << "(" << this << ") Constante(" << _value << ") Constructed!" << endl; }
	double operator()(double x) {
		return _value;
	}
};


class Escalar : public Funcao {
public:
	Escalar (double val,Funcao *f): _value(val), f(f){}
	Escalar	(Funcao* f){}
	Escalar(double val) : _value(val) { cout << "(" << this << ") Escalar(" << _value << ") Constructed!" << endl; }
	Escalar() { cout << "(" << this << ") Escalar Constructed!" << endl; } //construtor padraoa
private:
	double _value;
	Funcao* f;
};



class Seno : public Funcao {
public:
	Seno(double val, Funcao* f) {}
	Seno(Funcao* f) {}
	Seno(double val) {}
	Seno() { cout << "(" << this << ") Seno Constructed!" << endl; } //construtor padrao
	double operator()(double x) {
		return (sin(x));
	}

};	

class Coseno : public Funcao {
public:
	Coseno(double val, Funcao* f) {}
	Coseno(Funcao* f) {}
	Coseno(double val) {}
	Coseno() { cout << "(" << this << ") Coseno Constructed!" << endl; } //construtor padrao
	double operator()(double x) {
		return (cos(x));
	}
};

/*
class FuncaoAgregada : public Funcao {};

class Potencial : public Funcao {};
class Exponencial : public Funcao {};
*/




void main()
{
	Funcao ();
	Constante i(5);    //i(x)=5;
	Escalar h(2);
	
}

