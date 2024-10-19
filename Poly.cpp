#include <iostream>
#include <cmath>
#include <fstream>
#include "Poly.h"

using namespace std;

Poly::Poly() : grau(-1), a(nullptr) {} //construtor default da classe
Poly::Poly(const Poly& cpy) : grau(cpy.grau) //construtor por cópia da classe
{
    int i;  //variavel auxiliar

    if(cpy.grau<0)
    {
        grau = -1;  //a dimensão deve sempre ser grau+1 e eu estou transoformando grau em -1
        //se o grau for <0 para que fique no mesmo formato do polinômio vazio padrão
        a = nullptr;//boa prática de programação: fazer ponteiros não usados apontarem para nullptr
    }
    else
    {
            a = new double[grau+1];   //alocando memoria de acordo com o grau se ele for maior ou igual a 0
            for(i=0; i<grau+1; i++)
            {
                a[i] = cpy.a[i];    //copiando os valores de cpy para o objeto em que o método está atuando
            }
    }
    //nao liberei a memoria de cpy pois ele deve existir independente da copia que está sendo feita
}
Poly::~Poly()   //destrutor da classe
{
    delete[] a; //desalocando a memoria de a
    a = nullptr;    //fazendo a apontar para nullptr
    grau = -1;  //fazendo o grau se tornar invalido
}
Poly::Poly(Poly&& mov) noexcept : grau(mov.grau), a(mov.a)  //construtor por movimento da classe
{
    mov.a = nullptr;    //fazendo mov.a apontar para nullptr
    mov.grau = -1;  //fazendo o grau do polinomio ser invalido
}
Poly::Poly(const int& i) : grau(i)    //construtor específico da classe
{
    int j;
    if(grau<0)  //testa se o grau é negativo
    {
        grau = -1;
        a = nullptr;
    }
    else if(grau==0)    //testa se o grau é nulo
    {
        a=new double[grau+1];   //alocando recursos para armazenar nada mais nada menos que
        //a quantidade correta de coeficientes
        a[0] = 0.0; //atribuindo 0.0 ao único coeficiente desse polinômio como manda a especificação
    }
    else if(grau>0) //testa se o grau é positivo
    {
        a=new double[grau+1];   //alocando recursos para armazenar nada mais nada menos que
        for(j=0; j<grau+1; j++) //a quantidade correta de coeficientes
        {
            a[j] = 0.0; //todos os coeficientes devem ser nulos
        }
        a[grau] = 1.0;  //exceto o de maior grau que deve ser 1.0
    }
}
Poly& Poly::operator=(const Poly& cpy)   //sobrecarga do operador =
{
    if(this == &cpy)    //verifica a autoatribuição
    {
        return *this;
    }

    delete[] a; //desaloca a memória alocada atualmente para o objeto atual

    this->grau = cpy.grau;

    if(this->grau<0)
    {
        this->grau = -1;  //se o grau for <0 para que fique no mesmo formato do polinômio vazio padrão
        this->a = nullptr;//boa prática de programação: fazer ponteiros não usados apontarem para nullptr
        return *this;
    }
    else
    {
            a = new double[grau+1];   //alocando memoria de acordo com o grau se ele for maior ou igual a 0
            for(int i=0; i<this->grau+1; i++)
            {
                a[i] = cpy.a[i];    //copia os valores de temp para o objeto em que o método está atuando
            }
    }

    return *this;   //permite o encadeamento de operadores = usando referências constantes
}
Poly& Poly::operator=(Poly&& mov)  //sobrecarga do operador =
{
    if(this == &mov)    //verifica a autoatribuição
    {
        return *this;
    }

    delete[] a;

    this->grau = mov.grau;
    this->a=mov.a;
    mov.grau=-1;
    mov.a=nullptr;

    return *this; //permite o encadeamento de operadores = usando referências temporárias
}
int Poly::getGrau() const   //definição da função de consultar o grau do polinômio
{
    return grau;    //retorna dado privado grau
}
double Poly::getCoef(const int& i) const   //definição da função para consultar o coeficiente desejado
{
    //passando o número do grau do termo em que ele se encontra
    if(i<0 || i>grau)   //verificando a validade do índice. Não considerei igual a 0 pois se ele for igual a 0 o único termo dele já é 0.0
    {
        return 0.0; //retorna 0.0 sem emitir mensagem de erro
    }
    else return a[i];   //retorna o valor na posição i do polinômio em questão
}
void Poly::setCoef(const int& i, const double& novo_coef)   //método para mudar o valor do coeficiente
{
    if(i<0 || i>grau)   //teste de validade do indice
    {
        cerr << "Indice invalido\n";    //mensagem de erro
    }
    else if(novo_coef==0 && i==grau && grau>0)  //teste de validade do grau
    {
        cerr << "Valor invalido\n"; //mensagem de erro
    }
    else a[i] = novo_coef;  //se passou nos dois testes, o valor eh valido
}
double Poly::operator[](const int& i) const   //sobrecarga do operador colchete
{
    return getCoef(i);  //retorna uma chamada aa funcao getCoef usando como parametro o mesmo parametro que foi passado para o operador colchete
}
void Poly::recriar(const int& degree) //método para redefinir o grau e os coeficientes de um poly
{
    *this = Poly(degree);   //chama o construtor específico da classe e atribui a this um Poly criado a partir do parâmetro passado como parâmetro para a função recriar
}
bool Poly::operator==(const Poly& p) const //método para comparar dois poly
{
    int i;  //variável auxiliar
    if(grau!=p.grau) return false;  //se o grau dos polinômios forem diferentes, é suficiente para dizer que são diferentes
    else
    {
        for(i=0; i<grau+1; i++)
        {
            if(a[i]!=p.a[i]) return false;  //se algum termo de 0 a grau-1 for diferente entre os dois polinômios, eles são diferentes
        }
    }
    return true;    //se passou nos três testes, eles são iguais
}
bool Poly::operator!=(const Poly& p) const
{
    return !(*this==p);  //retorna a negação da comparação entre dois polinômios: se der forem iguais, retorna false. Se forem diferentes, retorna true
}
bool Poly::empty() const  //método de consulta para verificar se o poly é vazio(implica em grau = -1)
{
    return grau<0;  //retorna uma expressão lógicas que sera true se gfrau for menor que 0 e false se grau não for menor que 0
}
bool Poly::isZero() const //método de consulta para verificar se o polinômio é nulo(implica em grau = 0 e a[0] = 0.0
{
    if (grau == 0 && a[0]==0.0) return true;    //verifica se o grau é nulo e se o elemento na posição 0 é igual a 0.0
    return false;   //se passar no teste retorna falso
}
double Poly::getValor(const double& X) const
{
    int i;
    double soma_acumulada=0.0;
    double potencia = 1.0;

    if(empty()) return 0.0;    //verifica se o poly é vazio e se sim retorna 0.0 sem emitir mensagem de erro
    else
    {
        for(i=0; i<grau+1; i++)
        {
                soma_acumulada += a[i]*potencia;
                potencia*=X;
        }
    }
    return soma_acumulada;
    ///exceção que vai alterar o poly é o 0!!!!!!
}
double Poly::operator()(const double& X) const
{
    return getValor(X);
}
ostream& operator<<(ostream& os, const Poly& p)
{
    int i;
    if(p.empty())
    {
        return os;
    }
    else
    {
        for(i=p.grau; i>=0; --i) //i vai percorrer do maior valor até o menor valor
        {
            if(p.a[i]==0.0) //se a[i] for igual  a 0.0
            {
                if(i==0 && p.grau==0) os << p.a[i];   //avalia se i é igual a 0 e se o grau do polinômio é igual a 0.
            }                                         //Se sim, imprime o termo a[i] para a stream
            else    //caso contrário
            {
                //imprime sinal do coeficiente
                if(p.a[i]<0.0)  //verifica se a[i] é menor que 0
                {
                    os << '-'; //se sim, imprime o caractere '-' na stream
                }
                else    //caso contrário
                    if(i!=p.grau)   //verifica se i é diferente do grau do polinômio
                    {
                        os << '+';  //se sim, imprime '+' na stream
                    }

                //imprime módulo do coeficiente
                if( (abs(p.a[i])) !=1.0 || i==0)   //verifica se o módulo do coeficiente é igual a 1.0 e se i é diferente de 0
                {
                    os << abs(p.a[i]); //imprime o termo a[i] na stream
                }
                //imprime o termo que depende de x
                if(i!=0)    //verifica se i é diferente de 0
                {
                    if( (abs(p.a[i])) != 1.0) //verifica se o módulo do termo é diferente de 1.0
                    {
                        os << '*';  //se sim, imprime '*' na stream
                    }
                    os << 'x';  //imprime 'x' na stream
                    if(i>1) //verifica se i é maior que 1
                    {
                        os << '^';  //se sim, imprime '^' na stream
                        os << i;    //e imprime junto o grau do termo
                    }
                }
            }
        }
    }
    return os;
}
istream& operator>>(istream& is, Poly& p)
{
    int i;
    if(p.empty())
    {
        return is;
    }
    else
    {
        for(i=p.grau; i>=0; i--) //começa do grau maior e vai até zero
        {
            cout << "x^" << i << endl; //imprime o coeficiente o qual o usuário vai atribuir um valor
            if(i==p.grau && p.grau>0)  //se o i for igual ao grau e o grau maior que zero
            {
                do
                {
                    is >> p.a[i];   //lê do usuário o valor do coeficiente no grau i que é igual ao grau
                }
                while(p.a[i]==0);
            }
            else
            {
                if(i==p.grau && p.grau==0) //lida com a exceção do caso do polinômio nulo
                {
                    //permitindo o usuário digitar qualquer valor
                    is >> p.a[i];      //lê o valor do usuário
                }
                else
                {
                    if(i!=p.grau)  //se i é diferente do grau
                    {
                        is >> p.a[i];  //lê do usuário valores que serão atribuidos ao Poly
                    }
                }
            }
        }
    }
    return is; //retorna istream para possibilitar encadeamento do operador >>
}
bool Poly::salvar(const string& file_name) const
{
    int i;
    ofstream arq_dest(file_name, ostream:: out);    //inicializando o output file stream com o nome file_name no modo de escrita

    if(arq_dest.bad())  //verifica se há erro na stream
    {
        return false;
    }
    else if(arq_dest.is_open()) //se a stream está aberta para leitura, faça
    {
        arq_dest << "Poly " << grau << endl;    //escreve o cabeçalho no arquivo

        if(grau>-1) //checa se o grau é maior ou igual a 0
        {
            for(i=0; i<=grau; i++)  //escreve o coeficiente de cada term de grau i
            {
                arq_dest << a[i] << " " << endl;    //escreve no arquivo os coeficientes do poly separados por espaço e quebra de linha

                if(arq_dest.fail()) return false;   //verifica se ocorreu erro na leitura da stream
            }
        }

        arq_dest.close();   //fecha a stream(chama o destrutor que também é chamado automaticamente para fstreams)
    }
    return true;
}
bool Poly::ler(const string file_name)
{
    string cabecalho;
    ifstream arq_source(file_name, ifstream::in);   //inicializa ifstream com nome do arquivo e modo de operação para leitura
    int i, grau_prov;
    Poly temp;

    arq_source >> cabecalho;    //escreve o cabecalho na string homônima
    if(arq_source.bad()) return false;  //verifica os critérios de invalidade
    if(cabecalho!= "POLY") return false;//relacionados a stream e ao cabecalho

    //verifica os critérios de invalidade em relação ao grau e os coeficientes do Poly
    arq_source >> grau_prov;         //lendo do arquivo o grau do polinômio

    if(grau_prov<0) return false;    //se o grau for inexistente, retorna falso;

    temp.recriar(grau_prov);    //recria o polinômio com a alocação exata de memória para o grau certo

    for(i=0; i<temp.grau+1; i++) //verifica o último critério de invalidade antes de ler do arquivo atribuindo os valores do arquivo
    {
        //a uma variável temporária

        arq_source >> temp.a[i];    //atribui a variável temporária os coeficientes lidos do arquivo
        if(arq_source.fail())   //se ocorrer falha ao ler do arquivo,
        {
            //significa que o arquivo contém menos coeficientes do que o necessário
            return false;       //para o grau lido do arquivo
        }
    }
    if((temp.a[temp.grau]==0.0 && temp.grau>0)) return false;
    //Depois de todas as atribuições terem sido feitas,
    //se o coeficiente de maio grau for igual a 0.0 e o grau for maior que 0, retorna falso

    //se passou nos teste, é seguro atribuir os coeficientes à instância atual pois é sabido que não ocorrerá nenhum erro
    *this = move(temp);   //atribui todos os membros de temp a this e temp é destruída ao fim da função/método;
    return true;
}
Poly Poly::operator-() const
{
    int i;
    Poly negative(*this);   //chama o construtor por cópia
    if(grau<0) //verifica se o polinômio é vazio
    {
        return *this; //encerra a função pois -vazio = vazio
    }
    else for(i=0; i<grau+1; i++) negative.a[i] = -a[i];  //caso contrário, multiplica cada membro por -1 para o polinômio se tornar negativo

    return negative;
}
Poly Poly::operator+(const Poly& other) const
{
    int i,j,pos;

    if(other.empty()) return *this;
    if(this->empty()) return other;
    if(!this->empty() && other.isZero()) return *this;
    if(this->isZero() && !other.empty()) return other;

    int grau_max = this->grau + other.grau; //armazena o valor da soma dos graus dos dois polinômios para suportar a operação de soma adequadamente
    Poly max(grau_max); //chamada do construtor por cópia da classe para criar um polinômio com grau igual a soma dos graus dos 2 plinômios

    //realizando a operação de soma
    for(i=0;i<grau_max+1;i++)
    {
        max.a[i]= this->getCoef(i) + other.getCoef(i);
    }

    //tratando dos casos em que geram polinômios de grau menor do que o esperado
    for(i=grau_max;i>=0;i--)
    {
        if(max[i]==0)
        {
            pos = i;
        }
    }
    Poly prov(pos); //cria o polinômio adequado para caso o resultado da soma resulte em um polinômio de grau menor
    for(i=0;i<pos+1;i++)
    {
        prov.a[i] = max.a[i];
    }

    j=max.grau;

    if(max.a[j]==0.0)
    {
        Poly temp;
        while(j>0 && max.a[j]==0.0)
        {
            temp.recriar(j-1);
            for(i=0;i<j;i++)
            {
                temp.a[i] = max.a[i];
            }

            j--;
        }
        return temp;
    }
    return prov;
}
Poly Poly::operator-(const Poly& other) const
{
int i,j,pos;

    if(other.empty()) return *this;
    if(this->empty()) return -other;
    if(!this->empty() && other.isZero()) return *this;
    if(this->isZero() && !other.empty()) return -other;

    int grau_max = this->grau + other.grau; //armazena o valor da soma dos graus dos dois polinômios para suportar a operação de soma adequadamente
    Poly max(grau_max); //chamada do construtor por cópia da classe para criar um polinômio com grau igual a soma dos graus dos 2 plinômios

    //realizando a operação de soma
    for(i=0;i<grau_max+1;i++)
    {
        max.a[i]= this->getCoef(i) - other.getCoef(i);
    }

    //tratando dos casos em que geram polinômios de grau menor do que o esperado
    for(i=grau_max;i>=0;i--)
    {
        if(max[i]==0)
        {
            pos = i;
        }
    }
    Poly prov(pos); //cria o polinômio adequado para caso o resultado da soma resulte em um polinômio de grau menor
    for(i=0;i<pos+1;i++)
    {
        prov.a[i] = max.a[i];
    }

    j=max.grau;

    if(max.a[j]==0.0)
    {
        Poly temp;
        while(j>0 && max.a[j]==0.0)
        {
            temp.recriar(j-1);
            for(i=0;i<j;i++)
            {
                temp.a[i] = max.a[i];
            }

            j--;
        }
        return temp;
    }
    return prov;
}
Poly Poly::operator*(const Poly& other) const
{
    if(this->empty()) return *this;
    if(other.empty()) return other;
    if(this->isZero() && !other.empty()) return *this;
    if(!this->empty() && other.isZero()) return other;

    int grau_result = this->grau + other.grau;

    Poly prov(grau_result);

    int i,j,k;

    for(k=0;k<prov.grau+1;k++)
    {
        prov.a[k]=0;    //inicializa com zeros;
    }
    for(i=0;i<this->grau+1;i++)
    {
        for(j=0;j<other.grau+1;j++)
        {
            prov.a[i+j] += this->a[i] *other.a[j];
        }
    }
    return prov;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------//
///Extras
bool operator<=(int& valor, const Poly& p)  //sobrecarga fora da classe
{
    return valor<=p.grau;
}
bool operator<(int& valor, const Poly& p)
{
    return valor<p.grau;
}
