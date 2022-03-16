#include <ctype.h>
#include <stdio.h>


//NOME TOKENS
#define IF  256;
#define THEN  257;
#define ELSE  258;
#define RELOP  259;
#define ID 260;
#define NUMERO 261;
#define ARIOP 262;
#define WHILE 263;
#define AND 264;
#define OR 265;
#define NOT 266;
#define COMENTARIO 267 //COMPLETAR TODAS


//ATRIBUTOS
#define LT 268;
#define LE 269;
#define EQ 270;
#define NE 271;
#define GT 272;
#define GE 273;

#define ADD 274;
#define SUB 275;
#define MULT 276;
#define DIV 277;

#define OKEY 278;
#define CKEY 279;
#define BAR 280;

char letras[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','w','x','y','z',
                'A', 'B','C','D','E','F','G','H', 'I','J','K','L','M','N','O','P','Q','R','S','T','U','W','X','Y','Z'};
char numeros[] = ['1','2','3','4','5','6','7','7','8','9','0'];
char identificadores[200][2];
char palavrasReservadas[200] = {{'WHILE', 'DO', 'IF'}; //Acrescentar todas que estão do arquivo da prof (menos os simbolos)

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

	case 9: partida = 16; break; //se não for ariop testa se é identificador

	case 16: partida = 18; break; //se não for identificador testa se é numero

	case 18: partida = 20; break; //se não for numero testa se é comentário

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
    char string[200]; //para armazenar os caracteres lidos para ver a string final
    int i = 0; //para iterar o array string
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
                else if(c == '+') estado = 10;
                else if(c == '-') estado = 11;
                else if(c == '*') estado = 12;
                else if(c == 'd') estado = 13;
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
                c = code[cont_sim_lido];
                if(c == 'i') estado = 14;
                else estado = 0;
                break;
            case 14:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'v') estado = 15;
                else estado = 0;
                break;
            case 15:
                cont_sim_lido++;
                printf("<ariop, DIV>\n");
                token.nome_token = ARIOP;
                token.atributo = DIV;
                estado = 0;
                return(token);
                break;

            //fim subrotina ariop

            //início subrotina identificador
            case 16:
                c = code[cont_sim_lido];
                if((c == ' ')||(c == '\n'))
                {
                    estado = 0;
                    cont_sim_lido++;
                }
                int posicao = strcspn(letras, c); //testar se o caracter esta presente no array de letras
                else if(posicao<strlen(letras)){ //essa função quando não encontra o caracter ou numero encontrado retorna o tamanho do array entao testo pra ver se o valor é menor q o tam do array
                    estado = 17;
                    string[i] = c;
                    i++;
                }
                else
                {
                    estado = falhar();
                }
                break;
            case 17:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                int posicaoLetras = strcspn(letras, c); //testar se o caracter esta presente no array de letras
                int posicaoNumeros = strcspn(numeros, c); //testar se o numero esta presente no array de numeros
                if(posicaoLetras<strlen(letras) || (posicaoNumeros<strlen(numeros)){ //essa função quando não encontra o caracter ou numero encontrado retorna o tamanho do array entao testo pra ver se o valor é menor q o tam do array
                    string[i] = c; //adiciona no array string
                    i++; // vai para a proxima prosição
                    estado = 17;
                }
                else{
                    int j;
                    for(j=0; j<200; j++){
                        if(strcmp(palavrasReservadas[j], string) != 0){ //comparar a string que achamos com as oalavras reservadas
                            printf("<%s, >\n", palavrasReservadas[j]);
                            token.nome_token = toupper(palavrasReservadas[j]);
                            token.atributo = NULL;
                            estado = 0;
                            return(token);
                            break;
                        }
                        if(strcmp(identificadores[j][0], string) != 0){ //comparar a string que achamos com os identificadores
                            identificadores[j][0] = "linha correspondente"; //Salva a linha correspondente no array
                            printf("<identificador, %s>\n", identificadores[j][0]);
                            token.nome_token = ID;
                            token.atributo = null;
                            estado = 0;
                            return(token);
                            break;
                        }
                    }
                }
                break;
            //fim subrotina identificador

            //início subrotina numero
            case 18:
                c = code[cont_sim_lido];
                if((c == ' ')||(c == '\n'))
                {
                    estado = 0;
                    cont_sim_lido++;
                }
                int posicaoNumeros = strcspn(numeros, c); //testar se o caracter esta presente no array de letras
                else if(posicaoNumeros<strlen(numeros)){ //essa função quando não encontra o caracter ou numero retorna o tamanho do array entao testo pra ver se o valor é menor q o tam do array
                    estado = 19;
                    string[i] = c;
                    i++;
                }
                else
                {
                    estado = falhar();
                }
                break;
            case 19:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                int posicaoNumeros = strcspn(numeros, c); //testar se o numero esta presente no array de numeros
                if((posicaoNumeros<strlen(numeros)){ //essa função quando não encontra o numero  retorna o tamanho do array entao testo pra ver se o valor é menor q o tam do array
                    string[i] = c; //adiciona no array string
                    i++; // vai para a proxima prosição
                    estado = 19;
                }
                else{
                    printf("<numero, %s>\n", string);
                    token.nome_token = NUMERO;
                    token.atributo = string;
                    estado = 0;
                    return(token);
                }
                break;
            //fim subrotina numero

            //início subrotina comentario
            case 20:
                c = code[cont_sim_lido];
                if((c == ' ')||(c == '\n'))
                {
                    estado = 0;
                    cont_sim_lido++;
                }
                else if(c=="{") estado = 21;
                else if(c=="}") estado = 22;
                else if(c=="/") estado = 23;
                else
                {
                    estado = falhar();
                }
                break;
            case 21:
                cont_sim_lido++;
                printf("<{, >\n");
                token.nome_token = COMENTARIO;
                token.atributo = OKEY;
                estado = 0;
                return(token);
                break;
            case 22:
                cont_sim_lido++;
                printf("<}, >\n");
                token.nome_token = COMENTARIO;
                token.atributo = CKEY;
                estado = 0;
                return(token);
                break;
            case 23:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == '/') estado = 24;
                else estado = 0;
                break;
            case 24:
                cont_sim_lido++;
                printf("<//, >\n");
                token.nome_token = COMENTARIO;
                token.atributo = BAR;
                estado = 0;
                return(token);
                break;
            //fim subrotina comentario
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