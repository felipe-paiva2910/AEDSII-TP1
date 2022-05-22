#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tp1.h"

int main(){
    user* User = cria_lista_user();
    mailbox* mail = cria_lista_mailbox();

    int id, i = 0,count =0;
    char comando[50],aux[1];
    FILE *txt = fopen("teste.txt", "r");
    while(!feof(txt)){                              //conta o numero de linhas do arquivo
		fscanf(txt, "%[^\n]	%s", comando,comando);
			i++;
	}
	fclose(txt);                      //fecha o arquivo        
	txt = fopen("teste.txt", "r");                		//abre o arquivo
	while(count < i){                                 //percorre as linhas do txt
		fscanf(txt, "%s%c", comando, aux);
		if(strcmp(comando, "CADASTRA") == 0){           //cadastra uma nova conta(id)
			cadastra_Id(User, mail, txt);        
		}else if(strcmp( comando,"REMOVE")== 0){        //remove a conta referente a id
			fscanf(txt, "%d", &id);
			remove_Id(User, mail, id);         
			}else if(strcmp(comando, "ENTREGA") == 0){ 
			int aux;
			fscanf(txt, "%d",&aux);
			setbuf(stdin, NULL);
			entrega_IDPriMsgFim(mail, aux, User, txt); 			//entrega a mensagem
				}else if(strcmp(comando,"CONSULTA")== 0){        
					fscanf(txt, "%d", &id);
					printf("%d",id);
					consulta_Id(mail, id, User);   				//consulta o ultimo email da caixa de entrada

				}else if(strcmp(comando, "SAIR") == 0){      
					fclose(txt);                       //fecha o arquivo
					return 0;
		}
		count++;
	}
return 0;
}
