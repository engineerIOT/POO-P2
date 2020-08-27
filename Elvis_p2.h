#include <iostream>		//biblioteca entradas e saidas
using namespace std;
#include <vector>		//adicionada para utilizar na funcao agrega

class Funcao {				//Uma classe abstrata que serve de modelo para outras classes.
public:
	Funcao(Funcao* f) { } //ponteiro para a uncao empregada (f)
	Funcao() { /*cout << "(" << this << ") Funcao Constructed!" << endl;*/ } //construtor padrao
	virtual ~Funcao() { /*cout << "(" << this << ") Funcao Desconstructed!" << endl;*/ } //destrutor padrao
	double operator() (double x) { 
		return x; //a classe funcao retorna o valor da funcao através do operador de chamada de funcao
	}
	static double integrar (Funcao* f, double x0, double x1, double step){	// método estático 
		double _area = 0;
		double i;
		for (i = x0; i <= x1 - 1; i += step) {
			cout << "f(x) = " << f->operator()(i) << "\n";
			_area += ((f->operator()(i)) * step);
		}
		return (_area);
	}
};


class FuncaoAgregada : public Funcao {
public:
	//FuncaoAgregada() {}
	void agrega(Funcao* f) {
		_myvector.push_back(f);
	}
	double operator()(double x) {
		double _funcaoAgregada = 0;
		for (it = _myvector.begin(); it != _myvector.end(); it++) {
			_funcaoAgregada += static_cast<Funcao*>(*it)->operator()(x);
		}
		return _funcaoAgregada;

	}
private:
	vector <Funcao*> _myvector;
	vector <Funcao*> ::iterator it;
};


class Constante : public Funcao {
public:
	Constante(double val) : _value(val) { cout << "(" << this << ") constante(x)=(" << _value << ") " << endl; }
	Constante() {}
	double operator()(double x) {
		return (_value);
	}

private:
	double _value;
};


class Escalar : public Funcao {
public:
	Escalar (double val,Funcao *f): _value(val), f(f){}
	Escalar(Funcao* f) : f(f){ } //comentado porque estava dando conflito com o outro construtor
	Escalar(double val) : _value(val) { cout << "(" << this << ") escalar(x)=(" << _value << ") " << endl; }
	Escalar() { /*cout << "(" << this << ") Escalar Constructed!" << endl;*/ } //construtor padrao
	double operator()(double x) {
		_escalarResultado = _value * x;
		return(_escalarResultado);
	}
private:
	double _value;
	Funcao* f;
	double _escalarResultado;
};


class Potencial : public Funcao {
public:
	Potencial(double val, Funcao *f): _value(val), f(f){}
	Potencial(Funcao* f) : f(f) {}
	Potencial(double val) : _value(val) { cout << "(" << this << ") Potencial(" << _value << ") Constructed!" << endl; }
	Potencial() { cout << "(" << this << ") Potencial Constructed!" << endl; } //construtor padrao
	double operator()(double x){ 
		double _potencial = _value;
		int i;
		for (i = 0; i < (x - 1); i++) {
			_potencial *= _value;

			if (x == 0) // Qualquer numero elevado a 0 é igual 1
			{
				_potencial = 1;
			}
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
		double _exponencial = _value;
		int i;
		for (i = 0; i < (x - 1); i++) {
			_exponencial *= _value;

			if (x == 0) // Qualquer numero elevado a 0 é igual 1
			{
				_exponencial = 1;
			}
		}
		return (_exponencial);
	}
private:
	double _value;
	Funcao* f;
};

class Seno : public Funcao {
public:
	Seno(double val, Funcao* f) : _value(val), f(f) {}
	Seno(Funcao* f) : f(f) {}
	Seno(double val) : _value(val) {}
	Seno() { cout << "(" << this << ") Seno Constructed!" << endl; } //construtor padrao
	double operator()(double x) {
		return (sin(x));
	}

private:
	double _value;
	Funcao* f;

};	

class Coseno : public Funcao {
public:
	Coseno(double val, Funcao* f) : _value(val), f(f) {}
	Coseno(Funcao* f) : f(f) {}
	Coseno(double val) : _value(val) {}
	Coseno() { cout << "(" << this << ") Coseno Constructed!" << endl; } //construtor padrao
	double operator()(double x) {
		return (cos(x));
	}

private:
	double _value;
	Funcao* f;
};





void main()
{
	
	//Escalar g(1, new Potencial (1)); //g(x) = 3x^2
	//Escalar h(3);
	//Constante i(8);
	//Escalar i(3);
	Constante h(3);
	Constante i(3);


	FuncaoAgregada f;
	//f.agrega(&g); 
	f.agrega(&h); 
	f.agrega(&i);

	double x = 0;
	while (x < 5) {
		cout << "f(" << x << ") = " << f(x) << endl;
		x += 1;
	}

	cout << " A integral de [0,5] : ";
	cout << f.integrar(&f, 0, 5, 1) << endl;
	
}

