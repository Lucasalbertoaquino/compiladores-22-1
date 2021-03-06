#include <stdio.h>
#include <ctype.h>
#include <string>
#include <iostream>

using namespace std;

//NOME TOKENS
#define IF  256;
#define THEN  257;
#define ELSE  258;
#define RELOP  259;
#define ID 260;
#define NUMERO 261;
#define ARIOP 262;
#define WHILE 263;
#define DO 281;
#define BEGIN 282;
#define PROCEDURE 283;
#define END 284;
#define VAR 263;
#define WHILE 263;
#define AND 264;
#define OR 265;
#define NOT 266;
#define COMENTARIO 267


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

char letras[52] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                'A', 'B','C','D','E','F','G','H', 'I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char numeros[10] = {'1','2','3','4','5','6','7','8','9','0'};
char identificadores[100][200];
char palavrasReservadas[100][100] = {"WHILE", "DO", "IF","BEGIN","END","THEN","ELSE","PROGRAM","AND","NOT","PROCEDURE","VAR","DIV", "INT","BOOLEAN","READ","WRITE","TRUE","FALSE","OR"};

struct Token{
 int nome_token;
 int atributo;
};

bool eLetra(char letra){
    if((letra >= 'a' && letra<='z')  || (letra >= 'A' && letra <= 'Z')){
        return true;
    }
    else{
        return false;
    }
}

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

	while ((c = fgetc(file)) != EOF)
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

	case 9: partida = 13; break; //se não for ariop testa se é identificador

	case 13: partida = 15; break; //se não for identificador testa se é numero

	case 15: partida = 18; break; //se não for numero testa se é comentário

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
    string palavra;
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
                else if(c == 'd') {
                    palavra += c;
                    estado = 13;
                }
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

            //fim subrotina ariop

            //início subrotina identificador
            case 13:
                c = code[cont_sim_lido];
                bool letra;
                letra = eLetra(c); //testa se é letra
                if((c == ' ')||(c == '\n'))
                {
                    estado = 0;
                    cont_sim_lido++;
                }
                else if(letra){
                    palavra += c;
                    estado = 14;
                }
                else
                {
                    estado = falhar();
                }
                break;
            case 14:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                bool letra;
                bool numero;
                letra = eLetra(c); // testa se é letra
                numero = isdigit(c);
                if((letra) || (numero)){
                    palavra += c;
                    estado = 14;
                }
                else{
                    int j;
                    for(j=0; j<200; j++){
                        if(strcmp(palavrasReservadas[j], string) == 0){ //comparar a string que achamos com as oalavras reservadas
                            printf("<%s, >\n", palavrasReservadas[j]);
                            token.nome_token = toupper(palavrasReservadas[j]);
                            token.atributo = NULL;
                            estado = 0;
                            return(token);
                            break;
                        }
                        if(strcmp(identificadores[j][0], string) == 0){ //comparar a string que achamos com os identificadores
                            printf("<ID, %s>\n", identificadores[j][0]);
                            token.nome_token = ID;
                            token.atributo = null;
                            estado = 0;
                            return(token);
                            break;
                        }
                        else if(identificadores[j][0] == NULL){
                            identificadores[j][0] = string;
                            break;
                        }
                    }
                }
                break;

            //fim subrotina identificador

            //início subrotina numero
            case 15:
                c = code[cont_sim_lido];
                if((c == ' ')||(c == '\n'))
                {
                    estado = 0;
                    cont_sim_lido++;
                }
                int posicaoNumeros = strcspn(numeros, c); //testar se o caracter esta presente no array de letras
                else if(posicaoNumeros<strlen(numeros)){ //essa função quando não encontra o caracter ou numero retorna o tamanho do array entao testo pra ver se o valor é menor q o tam do array
                    estado = 16;
                    string[i] = c;
                    i++;
                }
                else
                {
                    estado = falhar();
                }
                break;
            case 16:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                int posicaoNumeros = strcspn(numeros, c); //testar se o numero esta presente no array de numeros
                if((posicaoNumeros<strlen(numeros)){ //essa função quando não encontra o numero  retorna o tamanho do array entao testo pra ver se o valor é menor q o tam do array
                    string[i] = c; //adiciona no array string
                    i++; // vai para a proxima prosição
                    estado = 16;
                }
                else{
                    estado = 25;
                    estado = falhar();
                }
                break;
            case 17:
                printf("<numero, %s>\n", string);
                token.nome_token = NUMERO;
                token.atributo = string;
                estado = 0;
                return(token);
                break;
            //fim subrotina numero

            //início subrotina comentario
            case 18:
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
            case 19:
                cont_sim_lido++;
                printf("<{, >\n");
                token.nome_token = COMENTARIO;
                token.atributo = OKEY;
                estado = 0;
                return(token);
                break;
            case 20:
                cont_sim_lido++;
                printf("<}, >\n");
                token.nome_token = COMENTARIO;
                token.atributo = CKEY;
                estado = 0;
                return(token);
                break;
            case 21:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == '/') estado = 24;
                else estado = 0;
                break;
            case 22:
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
    programa(token);
    while(token != "<., >"){ //"." delimita o final do programa
        token = proximo_token();
    }
}

void programa(Token token){
    if (token = "program"){
        token = proximo_token();
        id(token);
        if (token = ";"){
            token = proximo_token();
            bloco(token);
        }
        else falhar();
    }
}

void bloco(Token token){
    if ((token = "int") || (token = "boolean")){
        d_var(token);
    }
    else if (token = "procedure"){
        d_sub(token);
    }
    else if (token = "begin"){
        c_composto(token);
    }
    else falhar();
}

void d_var(Token token){
    declarando_var(token);
    if (token = ";"){
        while(true){
            token = proximo_token();
            declarando_var(token);
            if(token != ";"){
                break;
            }
        }
    }
    else falhar();
}

void declarando_var(Token token){
    tipo(token);
    list_id(token);
}

void tipo(Token token){
    if ((token = "int") || (token = "boolean")){
        t_simples(token);
    }
    else if ((token = "read") || (token = "write")){
        t_procedimento(token);
    }
    else if ((token = "true") || (token = "false")){
        t_constantes(token);
    }
    else falhar();
}

void t_procedimento(Token token){
    if (token = "read"){
        token = proximo_token();
    }
    if (token = "write"){
        token = proximo_token();
    }
    else falhar();
}

void t_constantes(Token token){
    if (token = "true"){
        token = proximo_token();
    }
    if (token = "false"){
        token = proximo_token();
    }
    else falhar();
}

void list_id(Token token){
    id(token);
    if (token = ";"){
        while(true){
            token = proximo_token();
            id(token);
            if (token != ";"){
                    break;
            }
        }
    }
    else falhar();
}

void d_sub(Token token){
    while(true){
        d_procedimento(token);
        if (token != ";"){
            falhar();
        }
        token = proximo_token();
        if (token != "procedure"){
            break;
        }
    }
}

void d_procedimento(Token token){
    if (token = "procedure"){
        token = proximo_token();
        id(token);
        if (token = "("){
            p_formais(token);
        }
        else if (token = ";"){
            token = proximo_token();
            bloco(token);
        }
        else falhar();
    }
}

void p_formais(Token token){
    if (token = "("){
        token = proximo_token();
        s_p_formais(token);
        if (token = ";"){
            token = proximo_token();
            s_p_formais(token);
        }
        if (token != ")"){
            falhar();
        }
    }
}

void s_p_formais(Token token){
    if (token = "var"){
        token = proximo_token();
        list_id(token);
        if (token = ":"){
            token = proximo_token();
            id(token);
        }
        else falhar();
    }
}

void c_composto(Token token){
    if (token = "begin"){
        token = proximo_token();
        comando(token);
        if (token = ";"){
            while(true){
                token = proximo_token();
                comando(token);
                if (token != ";"){
                    break;
                }
            }
        }
        if (token != "end"){
            falhar();
        }
        else falhar();
    }
}

void PROGRAM(){
	obter_token();
	if (token = "program"){
        obter_token();
        }
	else {printf("Erro: program esperado");
        ERRO(firstId);
        }
    if (token = ';'){
        obter_token();
    }
    else {printf("Erro: ; esperado");
        ERRO(firstBloco);
        }
    if (token = "."){
        obter_token();
    }
    else {
        printf("Erro: . esperado");
        }
    }
    
void BLOCO():
	if (token = "int" || token = "boolean" || token = "read" || token = "write" || token = "true"|| token = "false"){
	D_VAR(); = token}
	else{printf("Erro: int ou boolean ou read ou write true ou false esperado");
        ERRO(firstDSub);}
	else if (token = "procedure"){
        D_SUB(); = token}
    else{printf("Erro: procedure esperado");
        ERRO(firstCComposto)}
	else if (token = "begin"){
		C_COMPOSTO(); = token}
	else{printf("Erro: begin esperado");}

void D_VAR():
	DECLARANDO_VAR();
    if (token = ';'){
        while(true){
        obter_token();
        if (token != ';'){ 
        break;}
    }
    else {printf("Erro: ; esperado");
    ERRO(firstTipo)}

void DECLARANDO_VAR():
	TIPO = token();
	LIST_ID = token();

void TIPO():
	if (token = "int" || token = "boolean"){
		T_SIMPLES() = token;
	}
	else if (token = "read" || token = "wright"){
		T_PROCEDIMENTO() = token;
	}
	else if token = "true" || token = “false”{
		T_CONSTANTES() = token;
	}
	else{printf("Erro: int ou boolean ou read ou write true ou false esperado")
	ERRO(firstListId);}

void T_SIMPLES():
    if (token = "int"){
        obter_token();
        }
	else if (token = "boolen"){
        obter_token();}
	else {printf("Erro: int ou boolean esperado"); 
        ERRO(firstTprocedimento);
    }