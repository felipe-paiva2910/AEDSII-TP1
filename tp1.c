#include<stdio.h>
#include<stdlib.h>
#include"tp1.h"

void cria_lista_user_lista_mailbox(){
	user *User = (user*)malloc(sizeof(user));    // Criação dinâmicamente da célula cabeça para a lista de User
	User->prox = NULL;
	User->id = -MAX_MAILBOX;
	mailbox *mail = (mailbox*)malloc(sizeof(mailbox));
	mail->prox = NULL;
	mail->prox_email = NULL;
}
void cadastra_Id(user *us,mailbox *recebidos,FILE *txt){

	user *User = us;
	mailbox *entrada = recebidos;
	int id_new;
	fscanf(txt, "%d", &id_new);							//le o arquivo 
	if(id_new > MAX_MAILBOX){					
		printf("ID %d INVALIDA\n",id_new);				//verifica se a id é maior que o total da caixa de entrada(que seria o limite de usuarios)
	}
		if(User->id == id_new){							//verifica se ja existe uma id igual à id lida
			printf("ID %d JA CADASTRADA\n",id_new);
			User = User->prox;
		}
		else{
			while(User->prox != NULL){
				User = User->prox;
				entrada = entrada->prox;
			}
			entrada->prox = (mailbox*)malloc(sizeof(mailbox));  //aloca a memoria para a caixa de entrada para a respectiva User
			entrada->prox->prox = NULL; 
			entrada->prox->id = id_new; 						// recebe o id lido na caixa de entrada
			entrada->prox->prox_email = NULL; 
			User->prox =(user*) malloc(sizeof(user)); 			//aloca a memoria para a User
			User->prox->prox = NULL; 							//transforma o primeiro email da User em NULL
			User->prox->id = id_new; 							//vincula o id ao novo user
			printf("ID %d CADASTRADA\n", id_new);
		}
}

void remove_Id(user *us,mailbox *entrada,int id){
	user *us_aux = us;					//usa 2 ponteiros auxiliares pra percorrer as Users
	user *us_aux2;
	mailbox *ent_aux = entrada;			// e 2 ponteiros auxiliares pra limpar a caixa de entrada
	mailbox *ent_ant = entrada;

	if(us_aux->id != NULL){ 		//verifica se a id existe, se existir ele entra no if
		if(us_aux->id == id){
			us_aux2->prox = us_aux->prox; 			//depois de limpar a caixa de entrada, remove o usuario
			free(us_aux);
			if(ent_aux->prox_email != NULL){				
				mailbox *busca = ent_aux->prox_email;			
				mailbox *remove = busca;
					while(busca != NULL){
						busca = busca->prox_email;			//percorre a caixa de entrada e limpa ela
						free(remove);
						remove = busca;
					}
			}
			if(ent_aux->prox == NULL){						
				ent_aux->id = 0;
				ent_aux->prox_email = NULL;				
			}
			else if(ent_aux == ent_ant){
				ent_ant->prox = ent_aux->prox;
				free(ent_aux);
			}
			else{
				ent_ant->prox = ent_aux->prox;
				free(ent_aux);
			}
		printf("ID %d REMOVIDA\n",id);
		}
	us_aux2 = us_aux;
	us_aux = us_aux->prox;
	ent_ant = ent_aux;
	ent_aux = ent_aux->prox;
		}else printf("ID INEXISTENTE\n");
	}

void entrega_IDPriMsgFim(mailbox *ent,user *us,int id,FILE *txt){
	int i = 0;
	mailbox *busca = ent;
	int pri;
	char *email;

	fscanf(txt, "%d",&pri);				//le a pri indicada no arquivo
	fflush(txt);						//limpa o buffer
	fgets(email,MAX_MSG,txt);			//le a mensagem no arquivo

	if(id >= MAX_MAILBOX){
		printf("ID %d INEXISTENTE\n",id);			//verifica se a id existe
	}while(us[i].id<=id){
		if(us[i].id == id){
			while(busca->id != id){
				busca = busca->prox;				//percorre a lsita
			}
			if(busca->id == id){
				if(pri > 9){      					//verifica se a pri é valida
					printf("pri %d INEXISTENTE, POR FAVOR INFORME VALORES DE 0 A 9\n",pri);
					return;
				}else{								//ordena os emails pela prioridade
					mailbox *pont_aux = ent;			
					mailbox *ant ;
					int aux = 0;												
					while(pont_aux != NULL){
						if(pont_aux->id == id){
							break;
						}
						pont_aux = pont_aux->prox;
					}

					ant = pont_aux;
					while(pont_aux != NULL){
						if(pont_aux->pri < pri && pont_aux != ant){
							mailbox *novo = (mailbox*)malloc(sizeof(mailbox));
							strcpy(novo->Msg, email);
							novo->pri = pri;
							novo->id = id;
							novo->prox_email = pont_aux;
							ant->prox_email = novo;
							aux = 1;
							break;
						}
						ant = pont_aux;
						pont_aux = pont_aux->prox_email;
					}
					if(ant->prox_email == NULL){
						mailbox *novo = (mailbox*)malloc(sizeof(mailbox));
						strcpy(novo->Msg, email);
						novo->pri = pri;
						novo->id = id;
						novo->prox_email = NULL;
						novo->prox = NULL;
						ant->prox_email = novo;
						aux = 1;
					}
				}										
			}
		}
	}
}

void consulta_Id(mailbox *entrada, int id,user *User){
	mailbox *ent_aux = entrada;
	while(ent_aux != NULL){							
		if(ent_aux->id == id) break;				//busca a id fornecida na caixa de entrada
		ent_aux = ent_aux->prox;
	}
	if(ent_aux->prox_email == NULL){
		printf("CAIXA DE ENTRADA VAZIA\n");			//verifica se a caixa de entrada está vazia
		return;
	}else{
		printf("%s\n",ent_aux->prox_email->Msg);						//imprime a mensagem e faz o ponteiro apontar pro proximo
		mailbox *ent_aux2 = ent_aux->prox_email;
		ent_aux->prox_email = ent_aux->prox_email->prox_email;
		free(ent_aux);
		return;
	}
}

void OrdenaMsg(mailbox *mail, char *msg, int pri, int id){ // Função para fazer a alocação e ordenação dos emails nas caixas de mailbox
    mailbox *pont_aux = mail;
	mailbox *ant ;												// recebe como paramêtros um vetor de char contendo o conteúdo do email, pri e endereço
	int aux = 0;
	while(pont_aux != NULL){
		if(pont_aux->id == id){
			break;
		}
		pont_aux = pont_aux->prox;
	}

	ant = pont_aux;
	while(pont_aux != NULL){
		if(pont_aux->pri < pri && pont_aux != ant){
			mailbox *novo = (mailbox*)malloc(sizeof(mailbox));
			strcpy(novo->Msg, msg);
			novo->pri = pri;
			novo->id = id;
			novo->prox_email = pont_aux;
			ant->prox_email = novo;
			aux = 1;
			break;
		}
		ant = pont_aux;
		pont_aux = pont_aux->prox_email;
	}
	if(ant->prox_email == NULL){
		mailbox *novo = (mailbox*)malloc(sizeof(mailbox));
		strcpy(novo->Msg, msg);
		novo->pri = pri;
		novo->id = id;
		novo->prox_email = NULL;
		novo->prox = NULL;
		ant->prox_email = novo;
		aux = 1;
	}
}
