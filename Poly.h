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
    Poly& operator=(const Poly& cpy);  ///sobrecarga do operador de atribuição por cópia    FEITO
    Poly& operator=(Poly&& mov); ///sobrecarga do operador de atribuição por movimento    FEITO
    int getGrau() const;    ///método de consulta do grau do polinômio   FEITO
    double getCoef(const int& i) const;    ///método de consulta do i-ésimo coeficiente do polinômio  FEITO
    void setCoef(const int& i, const double& novo_coef);     ///método para alterar o i-ésimo coeficiente do polinômio   FEITO
    /// PARTE 1. ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    double operator[](const int& i) const;   ///sobrecarga do operador [] para que p[0] seja o mesmo que p.getCoef(0)  FEITO
    void recriar(const int& degree);  ///método para redefinir o grau e o coeficiente do polinomio    FEITO
    bool operator==(const Poly& p) const;  ///método para comparar se um polinômio é igual a outro    FEITO
    bool operator!=(const Poly& p) const;  ///método para verificar se um polinômio é diferente do outro   FEITO
    bool empty() const;   ///método para verificar se o polinômio é vazio FEITO
    bool isZero() const;  ///método para verificar se o polinômio é de grau 0 e tem seu único coeficiente sendo nulo  FEITO
    double getValor(const double& X) const; ///método para retornar o valor do polinômio dado um valor real X   FEITO
    double operator()(const double& X) const;    ///sobrecarga de operador para que p(1.5) seja igual a p.getValor(1.5)  FEITO
    friend ostream& operator<<(ostream& os,const Poly& p);  ///sobrecarga do operador << para escrever o polinômio na sua forma mais usual  FEITO
    /// PARTE 2. ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    friend istream& operator>>(istream& is, Poly& p); ///sobrecarrega o operador >> para ler via teclado os coeficiente de um polinômio FEITO
    bool salvar(const string& file_name) const; ///método para salvar o poly em um arquivo. O ARQUIVO TEM FORMATO ESPECÍFICO(CONSULTAR ESPECIFICAÇÕES DO PROJETO!)  FEITO
    /// PARTE 3. ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    bool ler(const string file_name);   ///método para ler polinômios a partir de arquivos FEITO
    /// PARTE 4. ^^^^^^^^^^^^^^^^^^^
    Poly operator-() const; ///sobrecarga do operador - unário para
    Poly operator+(const Poly& p) const;
    Poly operator-(const Poly& p) const;
    //-----------------------------------------------------------------------------------------------------------------------------------------------------//
    friend bool operator<=(int& valor, const Poly& p);
    friend bool operator<(int& valor, const Poly& p);
};


#endif // POLY_H_INCLUDED
