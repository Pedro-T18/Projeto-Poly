#ifndef POLY_H_INCLUDED
#define POLY_H_INCLUDED

using namespace std;

class Poly
{
private:
    int grau;
    double* a;
public:
    Poly(); ///construtor default
    Poly(const Poly& cpy);      ///construtor por copia FEITO
    ~Poly();    ///destrutor da classe   FEITO
    Poly(Poly&& mov) noexcept;  ///constutor por movimento da classe FEITO
    Poly(const int& N);   ///construtor especifico da classe   FEITO
    Poly& operator=(const Poly& cpy);  ///sobrecarga do operador de atribui��o por c�pia    FEITO
    Poly& operator=(Poly&& mov); ///sobrecarga do operador de atribui��o por movimento    FEITO
    int getGrau() const;    ///m�todo de consulta do grau do polin�mio   FEITO
    double getCoef(const int& i) const;    ///m�todo de consulta do i-�simo coeficiente do polin�mio  FEITO
    void setCoef(const int& i, const double& novo_coef);     ///m�todo para alterar o i-�simo coeficiente do polin�mio   FEITO
    /// PARTE 1. ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    double operator[](const int& i) const;   ///sobrecarga do operador [] para que p[0] seja o mesmo que p.getCoef(0)  FEITO
    void recriar(const int& degree);  ///m�todo para redefinir o grau e o coeficiente do polinomio    FEITO
    bool operator==(const Poly& p) const;  ///m�todo para comparar se um polin�mio � igual a outro    FEITO
    bool operator!=(const Poly& p) const;  ///m�todo para verificar se um polin�mio � diferente do outro   FEITO
    bool empty() const;   ///m�todo para verificar se o polin�mio � vazio FEITO
    bool isZero() const;  ///m�todo para verificar se o polin�mio � de grau 0 e tem seu �nico coeficiente sendo nulo  FEITO
    double getValor(const double& X) const; ///m�todo para retornar o valor do polin�mio dado um valor real X   FEITO
    double operator()(const double& X) const;    ///sobrecarga de operador para que p(1.5) seja igual a p.getValor(1.5)  FEITO
    friend ostream& operator<<(ostream& os,const Poly& p);  ///sobrecarga do operador << para escrever o polin�mio na sua forma mais usual  FEITO
    /// PARTE 2. ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    friend istream& operator>>(istream& is, Poly& p); ///sobrecarrega o operador >> para ler via teclado os coeficiente de um polin�mio FEITO
    bool salvar(const string& file_name) const; ///m�todo para salvar o poly em um arquivo. O ARQUIVO TEM FORMATO ESPEC�FICO(CONSULTAR ESPECIFICA��ES DO PROJETO!)  FEITO
    /// PARTE 3. ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    bool ler(const string file_name);   ///m�todo para ler polin�mios a partir de arquivos FEITO
    /// PARTE 4. ^^^^^^^^^^^^^^^^^^^
    Poly operator-() const; ///sobrecarga do operador - un�rio para
    Poly operator+(const Poly& p) const;
    Poly operator-(const Poly& p) const;
    //-----------------------------------------------------------------------------------------------------------------------------------------------------//
    friend bool operator<=(int& valor, const Poly& p);
    friend bool operator<(int& valor, const Poly& p);
};


#endif // POLY_H_INCLUDED
