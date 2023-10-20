#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <unistd.h>

// Pra funcionar os TXT é preciso criar os arquivos de textos na pasta com os nomes
// db_profiles.txt
// db_clients.txt
// db_employes.txt

struct Usuario {
    int id;
    int senha;
};

int main() {
    setlocale(LC_ALL, "Portuguese");

    int opcao;
    struct Usuario user;
    printf("Tela de Login\n");
    printf("ID: ");
    scanf("%i", &user.id);
    printf("PASSWORD: ");
    scanf("%i", &user.senha);

    if (autenticarUsuario(user.id, user.senha)) {
        system("cls");
        do {
            printf("Bem-vindo, user %i!\n", user.id);
            printf("\nMenu Inicial\n");
            printf("1. Cadastro de Clientes\n");
            printf("2. Cadastro de Funcionários\n");
            printf("3. Cadastro de Perfil\n");
            printf("4. Gerar Relatório\n");
            printf("5. Sair\n");
            printf("Escolha uma opção: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    system("cls");
                    cadastrarCliente();
                    break;
                case 2:
                    system("cls");
                    cadastrarFuncionario();
                    break;
                case 3:
                    system("cls");
                    cadastrarPerfil();
                    break;
                case 4:
                    system("cls");
                    gerarRelatorio();
                    break;
                case 5:
                    system("cls");
                    printf("Saindo do programa.\n");
                    break;
                default:
                    printf("Opção inválida. Tente novamente.\n");
                    break;
            }

        } while (opcao != 5);
    } else {
        printf("Autenticação falhou. Saindo do programa.\n");
    }

    return 0;
}


void cadastrarCliente() {
    printf("Cadastro de Cliente\n\n");
    FILE* pF = fopen("db_clients.txt", "a");
    char client[150];
    printf("Qual o nome do cliente que será cadastrado: ");
    scanf("%s",&client);
    fprintf(pF,client);
    fprintf(pF,"\n");
    fclose(pF);
    system("cls");
    system("cls");
    printf("O cliente %s foi cadastrado com sucesso!\n",client);
}

void cadastrarFuncionario() {
    printf("Cadastro de Funcionário\n");
    FILE* pF = fopen("db_employes.txt", "a");
    char employe[150];
    printf("Qual o nome do funcionário que será cadastrado: ");
    scanf("%s",&employe);
    fprintf(pF,employe);
    fprintf(pF,"\n");
    fclose(pF);
    system("cls");
    printf("O novo funcionário %s foi cadastrado com sucesso!\n",employe);
}

void cadastrarPerfil() {
    printf("Cadastro de Perfil\n");
    FILE* pF = fopen("db_profiles.txt", "a");
    char profile[150];
    printf("Qual o nome do perfil que será cadastrado: ");
    scanf("%s",&profile);
    fprintf(pF,profile);
    fprintf(pF,"\n");
    fclose(pF);
    system("cls");
    printf("O novo perfil %s foi cadastrado com sucesso!\n",profile);
}

void gerarRelatorio() {
    for (int k = 0;k < 100;k++){
        system("cls");
        printf("Gerando Relatório: %i%%",k);
        sleep(0.5);
    };
    printf("\nRelatório Gerado com sucesso!");
    sleep(3);
    system("cls");
    report();
    system("cls");
}

int autenticarUsuario(const int *id, const int *senha) {
    int users[3][2] = {{127,1924672},{459,84523},{123,456}};
    for(int j = 0;j < 3;j++){
        if(users[j][0] == id && users[j][1] == senha){
            return 1;
        }
    }
    return 0;
}

int report(){
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);

    int clients = read_registered("db_clients.txt") - 1;
    int employes = read_registered("db_employes.txt") - 1;
    int profiles = read_registered("db_profiles.txt") - 1;

    printf("Relatório gerado na Data: %d/%d/%d\n\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    printf("Clientes Cadastrados no Sistema: %i\n",clients);
    printf("Funcionários Cadastrados no Sistema: %i\n",employes);
    printf("Perfis Cadastrados no Sistema: %i\n\n",profiles);

    sleep(5);
}

int read_registered(FILE* file){
  file = fopen(file, "r");
  if (file == NULL)
  {
    printf("Error opening file.\n");
    return 1;
  }
  int current_line = 1;
  char c;
  do
  {
    c = fgetc(file);
    if (c == '\n') current_line++;
  } while (c != EOF);

  fclose(file);
  return current_line;
}
