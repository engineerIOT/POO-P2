#ifndef ELVIS_P2_H_INCLUDED
#define ELVIS_P2_H_INCLUDED

#include <iostream>		//biblioteca entradas e saidas
using namespace std;
#include <vector>		//adicionada para utilizar na funcao agrega
#include <math.h>	    //adicionada para utilizar nas funcoes seno e coseno 			
#define VALUE_DEFAULT	70.29525	


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
		double _operatorX1;
		double _i;

		//for (_i = x0+step; _i < x1; _i += step)
		for (_i = x0; _i < x1; _i += step)
		{	
			cout << "f(" << _i << ")=" << f->operator()(_i) << "\n";
			_area += ((f->operator()(_i)));
		}

		_operatorX0 = f->operator()(x0);
		_operatorX1 = f->operator()(x1);
		//double _somaOperador = (_operatorX1 + _operatorX0);
		//double _diferencaOperador = (_operatorX1 - _operatorX0);
		_i = (step/2) * (_operatorX0 + 2 * _area + _operatorX1);
		double erro = ((_i -(VALUE_DEFAULT)) / _i)* 100;
		cout << "erro = " << fabs(erro) << "%" << "\n";		//
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
		//cout << "Funcao agregada resultado: f(" << x << ")= " << _funcaoAgregada << endl;
		return _funcaoAgregada;

	}
private:
	_myVectorFunction _myvector;
	//vector <Funcao*> ::iterator it; //substituido porque nao estava agregando as funcoes
};


class Constante : public Funcao {
public:
	Constante(double val) : _value(val) { cout << "(" << this << ") constante(x)=(" << _value << ") " << endl; }
	Constante() { cout << "(" << this << ") Constante Constructed!" << endl; }
	double operator()(double x) {
				return (_value);
	}

private:
	double _value;
};


class Escalar : public Funcao {
public:
	Escalar (double val,Funcao *f): _value(val), f(f){ cout << "(" << this << ") escalar(x)=(" << _value << ") " << endl; }
	Escalar(Funcao* f) : f(f){ }
	Escalar(double val) : _value(val) { cout << "(" << this << ") escalar(x)=(" << _value << ") " << endl; }
	Escalar() { cout << "(" << this << ") Escalar Constructed!" << endl; } //construtor padrao
	double operator()(double x) {
		/*double _valorEscalar = 0;*/
		if(f != NULL) {
			x = (*f)(x);
			//return (_valorEscalar);
		}
		/*return (_value * _valorEscalar);
		*/
		_escalarResultado = _value * x;
		//cout << "x = " << x << endl;
		//cout << "escalar resultado: " << _escalarResultado << endl;
		return(_escalarResultado);
		
	}

	
private:
	double _value;
					
	Funcao* f; 			  
	double _escalarResultado;
	double x;
};


class Potencial : public Funcao {
public:
	Potencial(double val, Funcao *f): _value(val), f(f){ cout << "(" << this << ") Potencial(" << _value << ") Constructed!" << endl; }
	Potencial(Funcao* f) : f(f) {}
	Potencial(double val) : _value(val)/*, f(0)*/ { cout << "(" << this << ") Potencial(" << _value << ") Constructed!" << endl; }
	Potencial()/*: f(0)*/ { cout << "(" << this << ") Potencial Constructed!" << endl; } //construtor padrao
	double operator()(double x){ 
			if(f != NULL) {
			return pow((*f)(x), _value);
		}
			return pow((x), _value);
	}
private:
	double _value;
	Funcao* f;
};



class Exponencial : public Funcao {
public:
	Exponencial(double val, Funcao* f) : _value(val), f(f) { cout << "(" << this << ") Exponencial(" << _value << ") Constructed!" << endl; }
	Exponencial(Funcao* f) : f(f) {}
	Exponencial(double val) : _value(val) { cout << "(" << this << ") Exponencial(" << _value << ") Constructed!" << endl; }
	Exponencial() { cout << "(" << this << ") Exponencial Constructed!" << endl; } //construtor padrao
	double operator()(double x) {

		if (f != NULL) {
			return pow(_value, (*f)(x));
		}
		
			return pow(_value, x);
		}

		/*
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
		*/


private:
	double _value;
	Funcao* f;
};

class Seno : public Funcao {
public:
	Seno(double val, Funcao* f) : _value(val), f(f) { cout << "(" << this << ") Seno(" << _value << ") Constructed!" << endl; }
	Seno(Funcao* f) : f(f) {}
	Seno(double val) : _value(val) { cout << "(" << this << ") Seno(" << _value << ") Constructed!" << endl; }
	Seno() { cout << "(" << this << ") Seno Constructed!" << endl; } //construtor padrao
	double operator()(double x) {
		double _valorSeno = 0;
		if (f != NULL) {
			_valorSeno = sin((*f)(x));
				return (_valorSeno);
		}
		 _valorSeno = sin((x));
		 return (_valorSeno);
	}

private:
	double _value;
	Funcao* f;

};	

class Coseno : public Funcao {
public:
	Coseno(double val, Funcao* f) : _value(val), f(f) { cout << "(" << this << ") Coseno(" << _value << ") Constructed!" << endl; }
	Coseno(Funcao* f) : f(f) {}
	Coseno(double val) : _value(val) { cout << "(" << this << ") Coseno(" << _value << ") Constructed!" << endl; }
	Coseno() { cout << "(" << this << ") Coseno Constructed!" << endl; } //construtor padrao
	double operator()(double x) {
		double _valorCoseno = 0;
		if (f != NULL) {
			_valorCoseno = cos((*f)(x));
			return (_valorCoseno);
		}
		_valorCoseno = cos(x);
		return (_valorCoseno);
	
	}

private:
	double _value;
	Funcao* f;
};

void teste() {

	Escalar a(1, new Potencial(2)); //a(x) = 1x^2
	//Potencial a(2);
	Constante b(5);					 //b(x) = 5
	FuncaoAgregada c;				 //c(x) = (x^2 + 5)	
	c.agrega(&a);
	c.agrega(&b);
	
	Escalar d(2);					 //d(x) = 2x	
	Constante e(-1);				 //e(x) = -1;
	FuncaoAgregada f;			     //f(x) = (2x -1)		
	f.agrega(&d);
	f.agrega(&e);

	Seno g = Seno(&f);				//g((f(x))= Seno (2x -1)
	Escalar h(5, &g);				//5*g((f(x))= 5*(Seno (2x -1))
	FuncaoAgregada i;				//i(x) = 5*(Seno (2x -1))
	i.agrega(&h);

	FuncaoAgregada j;				//j(x) = (x^2 + 5)	+ 5*(Seno (2x -1))
	j.agrega(&c);					//c(x) = (x^2 + 5)	
	j.agrega(&i);					//i(x) = 5*(Seno (2x -1))	
		
	cout << " A integral de [0,5] : ";
	cout << Funcao::integrar(&j, 0, 5, 0.01) << endl;
		
}


int main() {
	teste();
	return 9999;
}


#endif // ELVIS_P2_H_INCLUDED

