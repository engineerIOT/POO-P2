#include <iostream>		//biblioteca entradas e saidas
using namespace std;
#include <vector>		//adicionada para utilizar na funcao agrega
#include <math.h>

class Funcao {				//Uma classe abstrata que serve de modelo para outras classes.
public:
	Funcao(Funcao* f) { } //ponteiro para a uncao empregada (f)
	Funcao() { /*cout << "(" << this << ") Funcao Constructed!" << endl;*/ } //construtor padrao
	virtual ~Funcao() { /*cout << "(" << this << ") Funcao Desconstructed!" << endl;*/ }  //destrutor padrao
	//double operator() (double x) = 0;
	virtual double operator()(double x) = 0;
	

	static double integrar (Funcao* f, double x0, double x1, double step){	// método estático 
		double _area = 0;
		double _operatorX0;
		double _operatorXn;
		double _i;

		for (_i = x0 +step ; _i < x1; _i += step)
		{
			cout << "f(x) = " << f->operator()(_i) << "\n";
			_area += ((f->operator()(_i)));
		}

		_operatorX0 = f->operator()(x0);
		_operatorXn = f->operator()(x1);
		_i = (step / 2) * (_operatorXn + 2 * _area + _operatorXn);
		return _i;
		
	}

private:

	static double _i;
};

double Funcao::_i;

typedef vector<Funcao*> _myVectorFunction;

class FuncaoAgregada : public Funcao {
public:
	FuncaoAgregada() {}
	void agrega(Funcao* f) {
		_myvector.push_back(f);
	}
	double operator()(double x) {
		double _funcaoAgregada = 0;
		for (_myVectorFunction::iterator it= _myvector.begin(); it != _myvector.end(); it++) {
			_funcaoAgregada += static_cast<Funcao*>(*it)->operator()(x);
		}
		cout << "Funcao agrgada resultado: f(" << x << ")= " << _funcaoAgregada << endl;
		return _funcaoAgregada;

	}
private:
	_myVectorFunction _myvector;
	//vector <Funcao*> ::iterator it; //substituito porque nao estava agregando as funcoes
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
	Escalar (double val,Funcao *f): _value(val), f(f){ /*x = f->operator()(x)*/}
	Escalar(Funcao* f) : f(f){ } //comentado porque estava dando conflito com o outro construtor
	Escalar(double val) : _value(val) { cout << "(" << this << ") escalar(x)=(" << _value << ") " << endl; }
	Escalar() { /*cout << "(" << this << ") Escalar Constructed!" << endl;*/ } //construtor padrao
	double operator()(double x) {
		_escalarResultado = _value * x;
		cout << "x = " << x << endl;
		cout << "escalar resultado: " << _escalarResultado << endl;
		return(_escalarResultado);
	}
private:
	double _value;
					
	Funcao* f; // teira q acessar o operator de f mas n sei se da de  fzr isso no mesmo operator do e
			   // talvez ttenha que instanciar dentro da classe?	
	double _escalarResultado;
	double x;
};


class Potencial : public Funcao {
public:
	Potencial(double val, Funcao *f): _value(val), f(f){ }
	Potencial(Funcao* f) : f(f) {}
	Potencial(double val) : _value(val) { cout << "(" << this << ") Potencial(" << _value << ") Constructed!" << endl; }
	Potencial() { cout << "(" << this << ") Potencial Constructed!" << endl; } //construtor padrao
	double operator()(double x){ 
		double _potencial = _value;
		int i;
		for (i = 0; i < x ; i++) { //ta aqui o erro
			//_potencial *= _value;//aqui ta o erro, acho que eh potencial = potencial^value
			_potencial = pow(x, _value);

			/*if (x == 0) // Qualquer numero elevado a 0 é igual 1
			{
				_potencial = 1;
			}
			*/
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
	
	Escalar g(1, new Potencial (2)); //g(x) = 1x^2
	Escalar h(1);					 //h(x) = 3x
	Constante i(1);				 //i(x) = 10
		

	FuncaoAgregada f;
	f.agrega(&g); 
	f.agrega(&h); 
	f.agrega(&i);

	/*double x = 0;
	while (x < 5) {
		cout << "f(" << x << ") = " << f(x) << endl;
		x += 1;
	}*/
	
	cout << " A integral de [0,5] : ";
	cout << Funcao::integrar(&f, 0, 5, 1) << endl;
	
//	f(1);
}

