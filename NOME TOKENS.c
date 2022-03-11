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
//fim subrotina logop

//inicio subrotina ariop
case 10:
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
//fim subrotina ariop
case 11:
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