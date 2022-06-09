#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//classe
class hospede{
public:
    string Nome;
    string Sobrenome;
    string Endereco;
    long long int Telefone; 
    string Email;
    string Cartao;
    int Tipo; //tipo de quarto
    int Chegada;
    int Saida;
    string Linha;

    //construtor
    hospede(string nome, string sobrenome, string endereco, long long int telefone, string email, string cartao, int chegada, int saida, int tipo){
        Nome = nome;
        Sobrenome = sobrenome;
        Endereco = endereco;
        Telefone = telefone;
        Email = email;
        Cartao = cartao;
        Tipo = tipo;
        Chegada = chegada;
        Saida = saida;
        
        
        Linha= to_string(Tipo) + "   " + Nome + " " + Sobrenome + "   " + Endereco + "  " + to_string(Telefone) + "  " + Email + "  " + to_string(Chegada) + "  " + to_string(Saida) + "  " + Cartao;
    }
};


//funcoes
void mostrar_tipos(int *p){ //recebe o ponteiro
    cout<<"1 - Standard: "<<*(p)<<endl;
    cout<<"2 - Solteiro: "<<*(p+1)<<endl;
    cout<<"3 - Executivo: "<<*(p+2)<<endl;
}

void carregar_reservas(){
    ifstream arq("reservas.txt");
    string linha[18];
    int i=0;
    while(!arq.eof()){
        getline(arq, linha[i]);
        i++;
    }

    arq.close();
    
}

void escreve_reserva(hospede hospede1){
    ifstream arq("reservas.txt");
    string linha[18];
    int i=0;
    while(!arq.eof()){
        getline(arq, linha[i]);
        i++;
    }

    arq.close();
    ofstream arq_saida("reservas.txt");
    
    for(int u=0; u<i; u++){
        arq_saida<<linha[u];
        arq_saida<<endl;
    }
    arq_saida<<hospede1.Linha;
    arq_saida.close();
}


int main(){

    int opt; //opção do menu a ser escolhida
    
    //variaveis para a reserva (hóspede)
    int chegada, saida;
    long long int telefone;
    string nome;
    string sobrenome;
    string endereco;
    string email;
    string cartao;

    


    //abertura e leitura dos arquivos (banco de dados dos quartos)
    int qtd_disponivel[3]; //3 tipos de quarto
    int qtd_existente[3];
    /*
    indice 0 = quantidade de quartos standard
    indice 1 = quantidade de quartos solteiro
    indice 2 = quantidade de quartos executivo*/
    //inicialização dos vetores
    for(int i=0; i<3; i++){
        qtd_disponivel[i]=0;
        qtd_existente[i]=0;
    }


    int *p = &qtd_disponivel[0]; // a ser usado para imprimir a quantidade depois

    ifstream quartos("disponibilidade_quartos.txt");
    for(int i=0; i<3; i++){ 
        quartos >> qtd_disponivel[i];
    }
    for(int i=0; i<3; i++){ 
        quartos >> qtd_existente[i];
    }



    while(opt !=5)
    {
        cout<<" - - - - - Menu Principal - - - - -"<<endl<<endl;
        cout<<"1 - Criar Reserva"<<endl;
        cout<<"2 - Cadastrar Quarto"<<endl;
        cout<<"3 - Quartos"<<endl;
        cout<<"4 - Mostrar cadastros"<<endl;
        cout<<"5 - Salvar e sair"<<endl;

        cin>>opt;

        switch(opt){//ITERAÇÃO PRO MENU //pagamento
            case 1:
            {
                cout<<"----- Dados pessoais do hóspede -----"<<endl;
                cout<<"Primeiro nome do hóspede: ";
                cin>>nome;
                cout<<endl<<"Sobrenome do hóspede: ";
                cin>>sobrenome;

                cout<<"--Dados de endereço do hóspede--"<<endl;
                cout<<"(Rua/Av) (nome da rua/av), número, bairro, cep, cidade, estado, país)"<<endl;
                cin.ignore();
                getline(cin, endereco);
                cout<<endl;

                cout<<"Telefone do hóspede(ex: 16999999999): ";
                cin>>telefone;
                cout<<endl;


                cout<<"Email do hóspede: ";
                cin>>email;
                cout<<endl;


                cout<<"Data de chegada(AAAAMMDD): ";
                cin>>chegada;
                cout<<endl;

                cout<<"Data de saída(AAAAMMDD): ";
                cin>>saida;
                cout<<endl;

                


                cout<< "selecione o tipo de quarto" <<endl;
                mostrar_tipos(p);

                int quarto_selecionado;
                cin >> quarto_selecionado;

                switch(quarto_selecionado){ //diminuir quarto disponivel
                    case 1:
                    {
                        qtd_disponivel[0]-=1;
                        break;
                    }
                    case 2:
                    {
                        qtd_disponivel[1]-=1;
                        break;
                    }
                    default:
                    {
                        qtd_disponivel[2]-=1;
                        break;
                    }
                }
                ofstream disp_quartos;
                disp_quartos.open("disponibilidade_quartos.txt");
                for(int i=0; i<3; i++){
                    disp_quartos<<qtd_disponivel[i]<<endl;
                }
                for(int i=0; i<3; i++){
                    disp_quartos<<qtd_existente[i]<<endl;
                }
                disp_quartos.close();
                
                

                cout<<"--- Dados do pagamento ---"<<endl;     
                cout<<"Credito/Débito - Bandeira - Número ou \"Dinheiro\" "<<endl;
                cin.ignore();
                getline(cin, cartao);
                cout<<"------RESERVA CONFIRMADA------"<<endl;


                hospede hospede1 = hospede(nome, sobrenome, endereco, telefone, email, cartao, chegada, saida, quarto_selecionado); //envio para construtor
                escreve_reserva(hospede1);
                cout<<endl<<endl;
                break;
            }
            case 2:
            {
                cout<<"---- CADASTRAR NOVO QUARTO ----"<<endl;
                cout<<"Selecione o tipo de quarto a ser cadastrado: \n1 - Standard\n2 - Solteiro\n3 - Executivo"<<endl;
                int auxiliar;
                cin >> auxiliar;
                switch(auxiliar){
                    case 1:
                    {
                        qtd_disponivel[0]=qtd_disponivel[0]+1;
                        qtd_existente[0]=qtd_existente[0]+1;
                        cout<<"-- Quarto Standard cadastrado com sucesso. --"<<endl<<endl;
                        break;
                    }
                    case 2:
                    {
                        qtd_disponivel[1]=qtd_disponivel[1]+1;
                        qtd_existente[1]=qtd_existente[1]+1;
                        cout<<"-- Quarto Solteiro cadastrado com sucesso. --"<<endl<<endl;
                        break;
                    }
                    case 3:
                    {
                        qtd_disponivel[2]=qtd_disponivel[2]+1;
                        qtd_existente[2]=qtd_existente[2]+1;
                        cout<<"-- Quarto Executivo cadastrado com sucesso. --"<<endl<<endl;
                        break;
                    }
                }


                ofstream quartos_saida("disponibilidade_quartos.txt"); //atualizando o arquivo com os dados
                for(int i=0; i<3; i++){ 
                	quartos_saida << qtd_disponivel[i];
                	quartos_saida<<endl;
                }
                for(int i=0; i<3; i++){ 
                    quartos_saida << qtd_existente[i];
                    quartos_saida<<endl;
                }
                break;
            }

            case 3:
            {
                cout<<endl<<"Quartos disponíveis: "<<endl;
                cout<<"Standard: "<<qtd_disponivel[0]<<"/"<<qtd_existente[0]<<endl;
                cout<<"Solteiro: "<<qtd_disponivel[1]<<"/"<<qtd_existente[1]<<endl;
                cout<<"Executivo: "<<qtd_disponivel[2]<<"/"<<qtd_existente[2]<<endl<<endl;
                break;
            }

            case 4:
            {
                string auxi[18];
                int i=0;
								cout<<endl;
                ifstream arq("reservas.txt");
                getline(arq, auxi[0]);//ignora primeira linha
                while(!arq.eof()){
                	getline(arq, auxi[i]);
                	cout<<auxi[i]<<endl<<endl;
                	i++;
                }
                arq.close();
                cout<<endl;
                break;
            }    
        } 
    }
    return 0;
}