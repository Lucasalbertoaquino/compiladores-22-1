//NOME TOKENS
#define IF  256;
#define THEN  257;
#define ELSE  258;
#define RELOP  259;
#define ID  260;
#define NUMERO 261;
#define ARIOP 262;
#define DELIM 263;
#define LOGOP 264;


//ATRIBUTOS
#define LT 265;
#define LE 266;
#define EQ 267;
#define NE 268;
#define GT 269;
#define GE 270;

#define ADD 271;
#define SUB 272;
#define MULT 273;
#define DIV 274;
#define AND 275;
#define OR 276;
#define NOT 277;

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
	case 0: partida = 9; break; //se não for relop testa se é logop

	case 9: partida = 13; break; //se não for logop testa se é ariop

	case 13: partida = 18; break; //se não for ariop testa se é

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

            //inicio subrotina logop
            case 9:
                c = code[cont_sim_lido];
                if((c == ' ')||(c == '\n'))
                {
                    estado = 0;
                    cont_sim_lido++;
                }
                else if(c == 'and') estado = 10;
                else if(c == 'or') estado = 11;
                else if(c == 'not') estado = 12;
                else
                {
                    estado = falhar();
                }
                break;
            case 10:
                cont_sim_lido++;
                printf("<logop, AND>\n");
                token.nome_token = LOGOP;
                token.atributo = AND;
                estado = 0;
                return(token);
                break;
            case 11:
                cont_sim_lido++;
                printf("<logop, OR>\n");
                token.nome_token = LOGOP;
                token.atributo = OR;
                estado = 0;
                return(token);
                break;
            case 12:
                cont_sim_lido++;
                printf("<logop, NOT>\n");
                token.nome_token = LOGOP;
                token.atributo = NOT;
                estado = 0;
                return(token);
                break;
            //fim subrotina logop

            //inicio subrotina ariop
            case 13:
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
            case 14:
                cont_sim_lido++;
                printf("<ariop, ADD>\n");
                token.nome_token = ARIOP;
                token.atributo = ADD;
                estado = 0;
                return(token);
                break;
            case 15:
                cont_sim_lido++;
                printf("<ariop, SUB>\n");
                token.nome_token = ARIOP;
                token.atributo = SUB;
                estado = 0;
                return(token);
                break;
            case 16:
                cont_sim_lido++;
                printf("<ariop, MULT>\n");
                token.nome_token = ARIOP;
                token.atributo = MULT;
                estado = 0;
                return(token);
                break;
            case 17:
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