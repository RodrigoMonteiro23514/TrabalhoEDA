#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

//txt, wb
//registo   !!!!!!!!!!!!!!!!!!!
//lista decrescente autonomia

//Guardar em txt e binario -> wb
int guardarMeios(Meio* inicio) 
{FILE* fp;
 fp = fopen("meios.txt","w");
 if (fp!=NULL)
 {
 Meio* aux= inicio;
 while (aux != NULL)
 {
  fprintf(fp,"%d;%f;%s\n", aux->codigo, 
	                      aux->autonomia, aux->tipo);
  aux = aux->seguinte;
 }
 fclose(fp);
 return(1);
 }
 else return(0);
}




//--------------------------------------------------------------  MENUS ---------------------------------------------------

void menuPrincipal (Cliente **listaCliente, Gestor **listaGestor, Meio **inicio)
{
int op;
printf("-----------------MENU--------------------\n");
printf("1 - Gerir Clientes\n");
printf("2 - Gerir Gestores\n");
printf("3 - Gerir Meios\n");
printf("4 - Alugar Meio\n");
printf("5 - Sair\n");
printf("Opcao:\n");
scanf("%d",&op);

do {
  switch(op)
{ case 1: menuCliente(listaCliente, listaGestor, inicio); 
          break;

  case 2: system("clear");
          printf("1 - Adicionar Gestor \n");
          printf("2 - Remover Gestor \n");
          printf("3 - Voltar \n");
          menuGestor(listaGestor);
          break;

  case 3: system("clear");
          printf("1 - Adicionar Meio \n");
          printf("2 - Remover Meio \n");
          printf("3 - Alterar Dados Meio \n");
          printf("4 - Voltar \n");
          menuMeio(inicio);
          break;         
  
  case 4: system("clear");
          // adicionar menu aluguer
          break;

  case 5: continue;

  default: printf("Escolha invalida! \n\n");
           menuPrincipal(listaCliente, listaGestor, inicio);
           break;
}

} while ( op != 5);

}




void menuCliente(Cliente **listaCliente, Gestor **listaGestor, Meio **inicio)
{
  Cliente *cliente = *listaCliente;
  int op;
  int nif;
  float saldo;
  char nome[50];
  char endereco[100]; 
  do {
  system("clear");
  printf("1 - Adicionar Cliente \n");
  printf("2 - Remover Cliente \n");
  printf("3 - Alterar Dados Cliente \n");
  printf("4 - Voltar \n");
  printf("Opcao:\n");
  scanf("%d", &op);
  switch(op) 
  { case 1: printf("Digite o NIF do cliente: \n");
            scanf("%d", &nif);
            printf("Digite o saldo do cliente: \n");
            scanf("%f", &saldo);
            printf("Digite o nome do cliente: \n");
            scanf("%s", nome);
            printf("Digite o endereço do cliente: \n");
            scanf("%s", endereco); 
            printList(cliente);
            adicionarCliente(listaCliente, nif, saldo, nome, endereco);
            printf("Cliente adicionado! \n");
            printf("Press a button...");
            break;

    case 2: listarClientes(cliente);
            printf("Digite o NIF do cliente: \n");
            scanf("%d", &nif);
            removerCliente(listaCliente, nif);   
            printf("Cliente removido! \n");
            break;

    case 3: printf("Qual o novo endereco que deseja? \n");
            scanf("%s", endereco);
            alterarCliente(listaCliente, nif, saldo, nome, endereco);
            printf("Cliente alterado! \n");
            break;

    case 4: system("clear");
            menuPrincipal(listaCliente, listaGestor, inicio);
                  
  }

} while ( op != 4);

}




void menuGestor(Gestor **listaGestor)
{
  Gestor *gestor = *listaGestor;
  int op;
  int idGestor;
  char nomeGestor[50];
  do {
  switch(op) 
  { case 1: printf("Digite o id do gestor: \n");
            scanf("%d", &idGestor);
            printf("Digite o nome do gestor: \n");
            scanf("%s", nomeGestor);
            adicionarGestor(listaGestor, nomeGestor, idGestor);
            break;

    case 2: listarGestores(gestor);
            printf("Digite o id do gestor que deseja remover: \n");
            scanf("%d", &idGestor);
            removerGestor(listaGestor, nomeGestor, idGestor);
            break;

    case 3: continue;
  }
} while ( op!= 0);

}




void menuMeio(Meio **inicio)
{
int op;
int codigo;
char tipo[50];
float autonomia;
float custo_por_hora;
do {
  switch(op) 
  { case 1: printf("Codigo? \n");
	          scanf("%d",&codigo);
	          scanf("%*c"); 
	          printf("Tipo de meio?(Bicileta ou Trotinete) \n");
	          scanf("%[^\n]s",&tipo);
	          printf("Autonomia? \n");
	          scanf("%f",&autonomia);
            printf("Qual o custo por hora? \n");
            scanf("%f", &custo_por_hora);
            adicionarMeio(inicio, codigo, tipo, autonomia, custo_por_hora);
            break;

    case 2: printf("Digite o codigo do meio: \n");
            scanf("%d", &codigo);
            removerMeio(inicio, codigo);
            break;

    case 3: printf("Qual a autonomia do meio? \n");
            scanf("%f", autonomia);
            alterarMeio(inicio, codigo, autonomia);
            break;

    case 4: continue;      
  }

} while ( op != 0);

}



//-------------------------------------------------------------------Gerir Clientes ---------------------------------------------------------------------------------------

// Função para adicionar um novo cliente à lista
void adicionarCliente(Cliente  **listaCliente, int nif, float saldo, char nome[], char endereco[]) 
{
    Cliente *novoCliente = malloc(sizeof(Cliente));
    novoCliente->nif = nif;
    novoCliente->saldo = saldo;
    strcpy(novoCliente->nome, nome);
    strcpy(novoCliente->endereco, endereco);
    novoCliente->prox = NULL;
    Cliente* atual = *listaCliente;

  if (*listaCliente == NULL)
  {
    *listaCliente = novoCliente;
    return;
  }
  
  while (atual->prox != NULL) 
  {
   atual = atual->prox;
  }
    atual->prox = novoCliente;
    
  return;
}



void printList(Cliente *listaCliente)
{
  while (listaCliente != NULL)
  {
    printf("%d", listaCliente->nif);
    listaCliente = listaCliente->prox;
    
  }
  
}


/*int checkRepeatedNIF(struct Cliente *listaCliente, char *nif) {
    struct Cliente *atual = listaCliente;
    while (atual != NULL) {
        if (strcmp(atual->nif, nif) == 0) 
        {
            return 1; // nif já existe
        }
        atual = atual->prox;
    }
    return 0; // nif não existe
}
*/




// Função para remover um cliente com base no NIF fornecido
void removerCliente(Cliente ** listaCliente, int nif) 
{
    
    
    Cliente *cliente = *listaCliente, *anterior;
    if (cliente->nif == nif) 
    {
        anterior = cliente;
        *listaCliente = cliente->prox;
        free(anterior);
        return;
    } 
    while (cliente != NULL)
    {
      while (cliente != NULL && cliente->nif != nif)
      {
        anterior = cliente;
        cliente = cliente->prox;
      }
      
      if (cliente == NULL)
      {
        return;
      }
      
     anterior->prox = cliente->prox;
     free(cliente);
     cliente = anterior->prox;
     return;

    }
      
}     







 // Função para alterar dados cliente
void alterarCliente(Cliente **listaCliente, int nif, float saldo, char nome[], char endereco[])
{ 
  Cliente *cliente  = *listaCliente;
  
  while (cliente != NULL)
  {
    if (nif == cliente->nif)
  
      strcpy(cliente->endereco, endereco);

    cliente = cliente->prox;
    

  }
  

}



// Listar clientes
void listarClientes(Cliente * listaCliente) 
{
    Cliente *aux = listaCliente;
    while (aux != NULL) 
    {
      printf("Nome: %s\n", aux->nome);
      printf("NIF: %d\n", aux->nif);
      printf("Endereço: %s\n", aux->endereco);
      printf("Saldo: %.2f\n\n", aux->saldo);
      aux = aux->prox;
    }
}





//-------------------- Gerir gestores ----------------------------------------------------

// Função para adicionar um novo gestor à lista
void adicionarGestor(Gestor  **listaGestor,char nomeGestor[], int idGestor) 
{
    Gestor *novoGestor = malloc(sizeof(Gestor));
    strcpy(novoGestor->nomeGestor, nomeGestor);
    novoGestor->idGestor = idGestor;
    novoGestor->proximo = NULL;
    Gestor* atualGestor = *listaGestor;

  if (*listaGestor == NULL)
  {
    *listaGestor = novoGestor;
    return;
  }
  
  while (atualGestor->proximo != NULL) 
  {
   atualGestor = atualGestor->proximo;
  }
    atualGestor->proximo = novoGestor;
    
  return;
}




// Função para remover um gestor com base no id fornecido
void removerGestor(Gestor ** listaGestor, char nomeGestor[50], int idGestor) 
{
    
    
    Gestor *gestor = *listaGestor, *anterior;
    if (gestor->idGestor == idGestor) 
    {
        anterior = gestor;
        *listaGestor = gestor->proximo;
        free(anterior);
        return;
    } 
    while (gestor != NULL)
    {
      while (gestor != NULL && gestor->idGestor != idGestor)
      {
        anterior = gestor;
        gestor = gestor->proximo;
      }
      
      if (gestor == NULL)
      {
        return;
      }
      
     anterior->proximo = gestor->proximo;
     free(gestor);
     gestor = anterior->proximo;
     return;

    }
      
}     



// Listar gestores
void listarGestores(Gestor * listaGestor) 
{
    Gestor *aux = listaGestor;
    while (aux != NULL) 
    {
      printf("Nome: %s\n", aux->nomeGestor);
      printf("Id: %d\n", aux->idGestor);
      aux = aux->proximo;
    }
}



// ------------------Gerir meios ----------------------------------------

// Função para adicionar um novo meio à lista
void adicionarMeio(Meio  **inicio, int codigo, char tipo[50], float autonomia, float custo_por_hora) 
{
    Meio *novoMeio = malloc(sizeof(Meio));
    novoMeio->codigo = codigo;
    strcpy(novoMeio->tipo, tipo);
    novoMeio->autonomia = autonomia;
    novoMeio->custo_por_hora = custo_por_hora;
    novoMeio->seguinte = NULL;
    Meio* atualMeio = *inicio;

  if (*inicio == NULL)
  {
    *inicio = novoMeio;
    return;
  }
  
  while (atualMeio->seguinte != NULL) 
  {
   atualMeio = atualMeio->seguinte;
  }
    atualMeio->seguinte = novoMeio;
    
  return;
}



// Função para remover um meio com base no codigo fornecido
void removerMeio(Meio ** inicio, int codigo) 
{
    Meio *meio = *inicio, *anterior;
    if (meio->codigo == codigo) 
    {
        anterior = meio;
        *inicio = meio->seguinte;
        free(anterior);
        return;
    } 
    while (meio != NULL)
    {
      while (meio != NULL && meio->codigo != codigo)
      {
        anterior = meio;
        meio = meio->seguinte;
      }
      
      if (meio == NULL)
      {
        return;
      }
      
     anterior->seguinte = meio->seguinte;
     free(meio);
     meio = anterior->seguinte;
     return;

    }
      
}     



 // Função para alterar dados meio
void alterarMeio(Meio **inicio, int codigo, float autonomia)
{ 
  Meio *meio  = *inicio;
  
  while (meio != NULL)
  {
    if (codigo == meio->codigo)
  
    meio->autonomia = autonomia;

    meio = meio->seguinte;
  } 

}


// listar na consola o conteúdo da lista ligada (falta ser por ordem decresente autonomia)
void listarMeios(Meio * inicio)
{ while (inicio != NULL)
 {printf("%d %s %.2f\n",inicio->codigo,inicio->tipo, 
		                         inicio->autonomia);
  inicio = inicio->seguinte;
 }
}



/*
Meio* inserirMeio(Meio * inicio, int codigo, char tipo[], float bateria, float autonomia)
{
 if (!existeMeio(inicio, cod))
 {Meio * novo = malloc(sizeof(struct meio));
  if (novo != NULL)
  {novo->codigo = cod;
   strcpy(novo->tipo,tipo);
   novo->bateria = bat;
   novo->autonomia = aut;
   novo->seguinte = inicio;
   return(novo);
  }
 } else return(inicio);
}// falta if para nao repetir
*/


/*
// Determinar existência do 'codigo' na lista ligada 'inicio'
// devolve 1 se existir ou 0 caso contrário
int existeMeio(Meio* inicio, int cod)
{while(inicio!=NULL)
  {if (inicio->codigo == cod) return(1);
   inicio = inicio->seguinte;
  }
 return(0);
}
*/

/*
Meio* removerMeio(Meio* inicio, int cod) // Remover um meio a partir do seu código
{while (inicio!=NULL)
 {if (inicio->codigo==cod) 
	 {aux = inicio->seguinte;
          free(inicio);
	  return(aux);
	 }
  else {inicio = removerMeio(inicio->seguinte,cod);
	return(inicio);
       }
 }
}
*/

/*
// Remover um meio a partir do seu código
Meio* removerMeio(Meio* inicio, int cod)
{
 Meio *anterior=inicio, *atual=inicio, *aux;

 if (atual==NULL) return(NULL);
 else if (atual->codigo == cod) // remoção do 1º registo
 {aux = atual->seguinte;
  free(atual);
  return(aux);
 }
 else
 {while ((atual!=NULL)&&(atual->codigo!=cod)) 
  {anterior = atual;
   atual = atual->seguinte;
  }
  if (atual==NULL) return(inicio);
  else
  {anterior->seguinte = atual->seguinte;
   free(atual);
   return(inicio);
  }
 }
}
*/






//---------------------------Aluguer-------------------------------------------

//Procurar Cliente para Registo de Aluguer
Cliente* procurarCliente(Cliente** listaCliente, int nif)
{
  Cliente* atualMeio = listaCliente;

  while (atualMeio != NULL) 
  {
    if (atualMeio->nif == nif) 
    {
      return atualMeio;
    }
    atualMeio = atualMeio->prox;
  }

  return NULL;
}



 //Procurar Meio para Registo de Aluguer
Meio* procurarMeio(Meio** inicio, int codigo)
{
  Meio* atualMeio = inicio;

  while (atualMeio != NULL)
  {
    if (atualMeio->codigo == codigo) 
    {
      return atualMeio;

    }
    atualMeio = atualMeio->seguinte;
  }
  return NULL;

}





//Registo Aluguer
void registarAluguer(int nif, int codigo, int tempo)
{
  Cliente *cliente = procurarCliente(cliente, nif);
  Meio *inicio = procurarMeio(inicio, codigo);

  if (cliente == NULL) 
  {
    printf("Cliente nao encontrado!\n");
    return;
  }

  if (inicio == NULL)
  {
    printf("Meio de mobilidade nao encontrado!\n");
    return;
  }

  if (inicio->estado != true) 
  {
    printf("Meio de mobilidade nao esta disponivel para aluguer!\n");
    return;
  }

   
   if (cliente->saldo < tempo * inicio->custo_por_hora) 
   {
    printf("Saldo insuficiente para alugar meio de mobilidade!\n");
    return;
   }
   else cliente->saldo -= tempo * inicio->custo_por_hora;
   inicio->estado = true;


   //falta criar novo registo de aluguer, adicioná-lo à lista(criar lista) e fazer printf





}



