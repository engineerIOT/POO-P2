#include <iostream>
using namespace std;
#include <vector>

class Funcao {
public:
	Funcao(Funcao* f) { }
	Funcao() { /*cout << "(" << this << ") Funcao Constructed!" << endl;*/ } //construtor padrao
	virtual ~Funcao() {} //destrutor padrao
	double operator() (double x = 0) {
		return x;
	}
	double integrar (Funcao* f, double x0, double x1, double step){
		double _area = 0;
		double i;
		for (i = x0; i <= x1; i += step) {
			cout << "f(x) = " << f->operator()(i) << "\n";
			_area += ((f->operator()(i)) * step);
		}
		return (_area);
	}
};

class Constante : public Funcao {
private:
	double _value;
public:
	Constante(double val) : _value(val) { cout << "(" << this << ") f(x)=(" << _value << ") " << endl; }
	double operator()(double) {
		return (_value);
	}
};


class Escalar : public Funcao {
public:
	Escalar (double val,Funcao *f): _value(val), f(f){}
	Escalar(Funcao* f) : f(f){ }
	Escalar(double val) : _value(val) { cout << "(" << this << ") g(x)=(" << _value << ") " << endl; }
	Escalar() { /*cout << "(" << this << ") Escalar Constructed!" << endl;*/ } //construtor padrao
	double operator()(double x) {
		double _escalar = 0;
		_escalar = (*f)(x);
		_escalar = _escalar * _value;
		return (_escalar);
	}
private:
	double _value;
	Funcao* f;
};


class Potencial : public Funcao {
public:
	Potencial(double val, Funcao *f): _value(val), f(f){}
	Potencial(Funcao* f) : f(f) {}
	Potencial(double val) : _value(val) { cout << "(" << this << ") Potencial(" << _value << ") Constructed!" << endl; }
	Potencial() { cout << "(" << this << ") Potencial Constructed!" << endl; } //construtor padrao
	double operator()(double x){ 
		double _potencial = x;
		uint8_t i;
		for (i = 0; i < (_value - 1); i++) {
			_potencial *= x;
		}
		return (_potencial);
	}
private:
	double _value;
	Funcao* f;
};

class Exponencial : public Funcao {
public:
	Exponencial(double val, Funcao* f) : _value(val), f(f) {}
	Exponencial(Funcao* f) : f(f) {}
	Exponencial(double val) : _value(val) { cout << "(" << this << ") Exponencial(" << _value << ") Constructed!" << endl; }
	Exponencial() { cout << "(" << this << ") Exponencial Constructed!" << endl; } //construtor padrao
	double operator()(double x) {
		return x;
	}
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


class FuncaoAgregada : public Funcao {
public:
	void agrega(Funcao *f){
		_myvector.push_back(f);
	}
	double operator()(const double x) {
		double _funcaoAgregada=0;
		for (it = _myvector.begin(); it != _myvector.end(); it++) {
			_funcaoAgregada += static_cast<Funcao*>(*it)->operator()(x);
		}
		return _funcaoAgregada;
		
	}
private: 
	vector <Funcao*> _myvector;
	vector <Funcao*> ::iterator it;
};


void main()
{
	//Funcao ();
	
	//Escalar g(0);    //i(x)=5;
	Constante h(0);
	Constante i(0);

	FuncaoAgregada f;
	f.agrega(&h); f.agrega(&i); 

	double x = 0;
	while (x < 5) {
		cout << "f(" << x << ") = " << f(x) << endl;
		x += 0.01;
	}

	cout << " A integral de [0,5] : ";
	cout << f.integrar(&f, 0, 5, 0.01) << endl;
	
}

