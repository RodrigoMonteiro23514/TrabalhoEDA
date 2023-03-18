#include <stdio.h>
#include <stdbool.h>

typedef struct meio
{
 int codigo; 
 char tipo[50];
 float autonomia;
 bool estado;
 float custo_por_hora;
 struct meio* seguinte;
} Meio;



typedef struct cliente {
    int nif;
    float saldo;
    char nome[50];
    char endereco[100];
    struct cliente *prox;
} Cliente;



typedef struct gestor 
{
    int idGestor;
    char nomeGestor[50];
    struct gestor *proximo;

} Gestor;


void menuPrincipal (Cliente **listaCliente, Gestor **listaGestor, Meio **inicio);
void menuCliente(Cliente **listaCliente, Gestor **listaCGestor, Meio **inicio);
void menuGestor(Gestor **listaGestor);
void menuMeio(Meio **inicio);
void adicionarCliente(Cliente **listaCliente, int nif, float saldo, char nome[50], char endereco[100]);
void listarClientes(Cliente *listaCliente);
void removerCliente(Cliente **listaCliente, int nif);
void printList(Cliente *listaCliente);
void alterarCliente(Cliente **listaCliente, int nif, float saldo, char nome[], char endereco[]);
Cliente* procurarCliente(Cliente** listaCliente, int nif);
void adicionarGestor(Gestor  **listaGestor,char nomeGestor[50], int idGestor);
void removerGestor(Gestor **listaGestor, char nomeGestor[50], int idGestor);
void listarGestores(Gestor *listaGestor);
void adicionarMeio(Meio  **inicio, int codigo, char tipo[50], float autonomia, float custo_por_hora);
void listarMeios(Meio* inicio); 
int existeMeio(Meio* inicio, int codigo); 
void alterarMeio(Meio **inicio, int codigo, float autonomia);
void removerMeio(Meio ** inicio, int codigo);
Meio* procurarMeio(Meio** inicio, int codigo);
Meio* lerMeios();

