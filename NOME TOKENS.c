//NOME TOKENS
#define IF  256;
#define THEN  257;
#define ELSE  258;
#define RELOP  259;
#define ID  260;
#define NUMERO 261;
#define ARIOP 262;
#define DELIM 263;
#define AND 264;
#define OR 265;
#define NOT 266;


//ATRIBUTOS
#define LT 267;
#define LE 268;
#define EQ 269;
#define NE 270;
#define GT 271;
#define GE 272;

#define ADD 273;
#define SUB 274;
#define MULT 275;
#define DIV 276;

struct Token{
 int nome_token;
 int atributo;
};



int estado = 0;
int partida = 0;
int cont_sim_lido = 0;
char *code;


char *readFile(char *fileName)
{
	FILE *file = fopen(fileName, "r");
	char *code;
	int n = 0;
	int c;

	if(file == NULL) return NULL;

	fseek(file, 0, SEEK_END);
	long f_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	code = new char (f_size);

	while ((c = fgetc(file))!= EOF)
	{
		code[n++] = (char) c;
	}
	code[n] = '\0';
	return code;
}




int falhar()
{
	switch(estado)
	{
	case 0: partida = 9; break; //se não for relop testa se é ariop

	case 9: partida = 13; break; //se não for ariop testa se é

	case 13: partida = 18; break;

	case 20: partida = 25; break;

	case 25:
		//retornar msg de erro
		printf("Erro encontrado no código\n");
		cont_sim_lido++;
		break;

	default: printf("Erro do compilador");
	}
	return(partida);
}

Token proximo_token()
{
	Token token;
	char c;
	while(code[cont_sim_lido] != EOF){
		switch(estado){

            //subrotina relop
            case 0:
                c = code[cont_sim_lido];
                if((c == ' ')||(c == '\n'))
                {
                    estado = 0;
                    cont_sim_lido++;
                }
                else if(c == '<') estado = 1;
                else if(c == '=') estado = 5;
                else if(c == '>') estado = 6;
                else
                    {
                        estado = falhar();
                    }
                break;
            case 1:
                cont_sim_lido++;
                c = code[cont_sim_lido];

                if(c == '=') estado = 2;
                else if(c == '>') estado = 3;
                else estado = 4;
                break;
            case 2:
                cont_sim_lido++;
                printf("<relop, LE>\n");
                token.nome_token = RELOP;
                token.atributo = LE;
                estado = 0;
                return(token);
                break;

            case 3:
                cont_sim_lido++;
                printf("<relop, NE>\n");
                token.nome_token = RELOP;
                token.atributo = NE;
                estado = 0;
                return(token);
                break;

            case 4:
                cont_sim_lido++;
                printf("<relop, LT>\n");
                token.nome_token = RELOP;
                token.atributo = LT;
                estado = 0;
                return(token);
                break;

            case 5:
                cont_sim_lido++;
                printf("<relop, EQ>\n");
                token.nome_token = RELOP;
                token.atributo = EQ;
                estado = 0;
                return(token);
                break;

            case 6:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == '=') estado = 7;
                else estado = 8;
                break;

            case 7:
                cont_sim_lido++;
                printf("<relop, GE>\n");
                token.nome_token = RELOP;
                token.atributo = GE;
                estado = 0;
                return(token);
                break;

            case 8:
                cont_sim_lido++;
                printf("<relop, GT>\n");
                token.nome_token = RELOP;
                token.atributo = GT;
                //ATENÇÃO - CORREÇÃO: foi acrescentado o comando "estado = 0;"
                estado = 0;
                return(token);
                break;
            //fim subrotina relop

            //inicio subrotina ariop
            case 9:
                c = code[cont_sim_lido];
                if((c == ' ')||(c == '\n'))
                {
                    estado = 0;
                    cont_sim_lido++;
                }
                else if(c == '+') estado = 14;
                else if(c == '-') estado = 15;
                else if(c == '*') estado = 16;
                else if(c == 'div') estado = 17;
                else
                {
                    estado = falhar();
                }
                break;
            case 10:
                cont_sim_lido++;
                printf("<ariop, ADD>\n");
                token.nome_token = ARIOP;
                token.atributo = ADD;
                estado = 0;
                return(token);
                break;
            case 11:
                cont_sim_lido++;
                printf("<ariop, SUB>\n");
                token.nome_token = ARIOP;
                token.atributo = SUB;
                estado = 0;
                return(token);
                break;
            case 12:
                cont_sim_lido++;
                printf("<ariop, MULT>\n");
                token.nome_token = ARIOP;
                token.atributo = MULT;
                estado = 0;
                return(token);
                break;
            case 13:
                cont_sim_lido++;
                printf("<ariop, DIV>\n");
                token.nome_token = ARIOP;
                token.atributo = DIV;
                estado = 0;
                return(token);
                break;
            //fim subrotina ariop
        }

	}
	token.nome_token = EOF;
	token.atributo = -1;
	return(token);
}

int main ()
{
	Token token;
    code = readFile("programa.txt");
    token = proximo_token();
    token = proximo_token();
    //...


}