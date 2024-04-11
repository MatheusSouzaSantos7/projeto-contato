#include <iostream>
#include <locale.h>
#include <ctime>
using namespace std;

class Data
{
	private:
		int dia;
		int mes;
		int ano;
		
    public: 
    	// Construtores
    	Data(int dia, int mes, int ano) {
			this->dia = dia;
			this->mes = mes;
			this->ano = ano;
		}
    	Data() {
			this->dia = 0;
			this->mes = 0;
			this->ano = 0;
		}
		
		// Getter's e Setter's
		void setDia(int dia) {
			this->dia = dia;
		}
		void setMes(int mes) {
			this->mes = mes;
		}
		void setAno(int ano) {
			this->ano = ano;
		}
		int getDia() {
			return this->dia;
		}
		int getMes() {
			return this->mes;
		}
		int getAno() {
			return this->ano;
		}
		string getData() {
		    string sDia = to_string(this->dia);
		    string sMes = to_string(this->mes);
		    string sAno = to_string(this->ano);
		    
		    return sDia.insert(0, 2-sDia.size(),'0') + "/" +
		           sMes.insert(0, 2-sMes.size(),'0') + "/" +
			       sAno;
        } // Vai retornar algo no seguinte formato: "03/04/2024"
        
        Data* dia_seguinte() { 
        	Data *d1 = new Data(this->dia, this->mes, this->ano);
		    int diasNoMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};;
			if (d1->ano%4 == 0)
			{
				diasNoMes[1] = 29;
			} 
			d1->dia++;
			if (d1->dia > diasNoMes[d1->mes-1])
			{
				d1->dia = 1;
				d1->mes++;
				if(d1->mes > 12)
				{
					d1->mes = 1;
					d1->ano++;
				}
			}
			return d1;
		}
		
}; // Fim da classe Data

// Classe Contato
class Contato
{
	private:
		string email;
		string nome;
		string telefone;
		Data *dtnasc;
		
    public: 
    	// Construtores
    	Contato(string email, string nome, string telefone, int dia, int mes, int ano) {
			this->email = email;
			this->nome = nome;
			this->telefone = telefone;
			this->dtnasc = new Data(dia, mes, ano);
		}
		Contato(){
			this->email = "Sem email";
			this->nome = "Sem nome";
			this->telefone = "Sem telefone";
			this->dtnasc = new Data(0, 0, 0000);
		}
		
		// Getter's e Setter's
		void setEmail(string email){
			this->email = email;
		}
		void setNome(string nome){
			this->nome = nome;
		}
		void setTelefone(string telefone){
			this->telefone = telefone;
		}
		
		string getEmail(){
			return email;
		}
		string getNome(){
			return nome;
		}
		string getTelefone(){
			return nome;
		}
		
		// Métodos
		int calcularIdade(){
			time_t now = time(0);
		    tm* ltm = localtime(&now);
        	int anoAtual = 1900 + ltm->tm_year;

		    return anoAtual - this->dtnasc->getAno();
		} 
}; // Fim da classe Contato

#define anoAtual 2024;
int main(int argc, char** argv)
{
// Instancias das classes.
    Data* hoje;
    Contato* contatos[5];

    time_t now = time(0);
    tm* ltm = localtime(&now);
    hoje = new Data(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);

    cout << "Cadastro de contatos" << endl;
    for (int i = 0; i < 5; i++) {
        string nome, email, telefone;
        int dia, mes, ano;

        cout << "Contato " << i + 1 << ":" << endl;
        cout << "Nome: ";
        getline(cin, nome);
        cout << "Email: ";
        getline(cin, email);
        cout << "Telefone: ";
        getline(cin, telefone);
        cout << "Data de nascimento (DD MM AAAA): ";
        cin >> dia >> mes >> ano;
        cin.ignore(); // Limpa o buffer do teclado

        // Cria um novo contato com as informações fornecidas
        contatos[i] = new Contato(email, nome, telefone, dia, mes, ano);
    }

    // Exibe os contatos cadastrados
    cout << "\nContatos cadastrados:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Nome: " << contatos[i]->getNome() << endl;
        cout << "Email: " << contatos[i]->getEmail() << endl;
        cout << "Telefone: " << contatos[i]->getTelefone() << endl;
        cout << "Idade: " << contatos[i]->calcularIdade() << " anos" << endl;
        cout << endl;
    }

    // Libera a memória alocada
    delete hoje;
    for (int i = 0; i < 5; i++) {
        delete contatos[i];
    }

    return 0;
}