
#define MAX_MSG 500
#define MAX_MAILBOX 10000

struct mailbox_t{      //lista referente à caixa de entrada
	char Msg[MAX_MSG];
	int pri;
	int id;
    int tam;
    struct mailbox_t *prox;
	struct mailbox_t *prox_email;
};

struct user_t{      //lista dos usuarios
	int id;
	struct user_t *prox;
	struct mailbox_t *entrada;
};

typedef struct mailbox_t mailbox;
typedef struct user_t user;


void cadastra_Id(user *user, mailbox *email, FILE *txt);
void removeId(user *User,mailbox *mail, int id);
void consulta_Id(mailbox *entrada, int id,user *conta);
void ordena(mailbox *recebe,char *email,int id,int pri);
void entrega_IDPriMsgFim(mailbox *ent,user *us,int id,FILE *txt);

