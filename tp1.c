#include<stdio.h>
#include<stdlib.h>
#include"tp1.h"

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
			entrada->prox = (mailbox*)malloc(sizeof(mailbox));  //aloca a memoria para a caixa de entrada para a respectiva conta
			entrada->prox->prox = NULL; 
			entrada->prox->id = id_new; 						// recebe o id lido na caixa de entrada
			entrada->prox->prox_email = NULL; 
			User->prox =(user*) malloc(sizeof(user)); 			//aloca a memoria para a conta
			User->prox->prox = NULL; 							//transforma o primeiro email da conta em NULL
			User->prox->id = id_new; 							//vincula o id ao novo user
			printf("ID %d CADASTRADA\n", id_new);
		}
}

void remove_Id(user *us,mailbox *entrada,int id){
	user *us_aux = us;					//usa 2 ponteiros auxiliares pra percorrer as contas
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