#define TKId 1
#define TKVoid 2
#define TKInt 3
#define TKFloat 4
#define TKVirgula 5
#define TKDoisPontos 6
#define TKAbreParenteses 7
#define TKFechaParenteses 8
#define TKAtrib 9
#define TKPontoEVirgula 10
#define TKAbreChaves 11
#define TKFechaChaves 12
#define TKSoma 13
#define TKDuploMais 14
#define TKProd 15
#define TKChar 16
#define TKSub 17
#define TKVolatile 18
#define TKDouble 19
#define TKFimArquivo 20
#define TKAndBit 21
#define TKAndLogico 22

#define false 0
#define true 1

#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
int pos = 0;

int tk;
char lex[20];
FILE *arqin;
char c; // último caracter lido do arquivo

struct pal_res{char palavra[20]; int tk;};
struct pal_res lista_pal[]={{"void",TKVoid},
                  {"int",TKInt},
                  {"float",TKFloat},
                  {"char",TKChar},
                  {"volatile",TKVolatile},
                  {"double",TKDouble},
                  {"fimtabela",TKId}};

int palavra_reservada(char lex[])
{
int postab=0;
while (strcmp("fimtabela",lista_pal[postab].palavra)!=0)
   {
   if (strcmp(lex,lista_pal[postab].palavra)==0)
      return lista_pal[postab].tk;
   postab++;
   }
return TKId;
}


void getToken(); // protótipos
void proxC();

// variáveis globais para retrocesso

long int posglobal;

void proxC()
{
if (feof(arqin)) {
   c=-1;
//   printf("Chegou no fim de arquivo\n");
   return;
   }
fread(&c,1,1,arqin);
//printf("Leu caracter %c\n",c);
}

void getToken()
{
int estado=0,
    fim=0,
    posl=0;
while (!fim)
   {
/*printf("%s\n",exp1);
printf("char=%c pos=%d\n",c,pos);*/
   lex[posl++]=c;
   switch(estado){
      case 0:if (c>='a' && c<='z' || c>='A' && c<='Z' || c=='_')
                {proxC();estado=1;break;}
             if (c=='='){lex[posl]='\0';proxC();tk=TKAtrib;/*printf("Reconheceu token TKAtrib\n");*/return;}
             if (c=='+')
			    {
			    proxC();
				if (c=='+')
			       {
				   lex[posl++]='+';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKDuploMais;/*printf("Reconheceu token TKDuploMais\n");*/return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKSoma;/*printf("Reconheceu token TKSoma\n");*/return;
				   }
			    }
             if (c=='&')
			    {
			    proxC();
				if (c=='&')
			       {
				   lex[posl++]='+';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKAndLogico;/*printf("Reconheceu token TKDuploMais\n");*/return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKAndBit;/*printf("Reconheceu token TKSoma\n");*/return;
				   }
			    }
             if (c=='*'){lex[posl]='\0';proxC();tk=TKProd;/*printf("Reconheceu token TKProd\n");*/return;}
             if (c=='('){lex[posl]='\0';proxC();tk=TKAbreParenteses;/*printf("Reconheceu token TKAbrePar\n");*/return;}
             if (c==')'){lex[posl]='\0';proxC();tk=TKFechaParenteses;/*printf("Reconheceu token FechaPar\n");*/return;}
             if (c=='&'){lex[posl]='\0';proxC();tk=TKAndBit;/*printf("Reconheceu token TKAndBit\n");*/return;}
             if (c=='{'){lex[posl]='\0';proxC();tk=TKAbreChaves;/*printf("Reconheceu token TKAbreChaves\n");*/return;}
             if (c=='}'){lex[posl]='\0';proxC();tk=TKFechaChaves;/*printf("Reconheceu token TKFechaChaves\n");*/return;}
             if (c==','){lex[posl]='\0';proxC();tk=TKVirgula;/*printf("Reconheceu token TKVirgula\n");*/return;}
             if (c==';'){lex[posl]='\0';proxC();tk=TKPontoEVirgula;/*printf("Reconheceu token TKPontoEVirgula\n");*/return;}
             if (c==':'){lex[posl]='\0';proxC();tk=TKDoisPontos;/*printf("Reconheceu token TKDoisPontos\n");*/return;}
             if (c=='-'){lex[posl]='\0';proxC();tk=TKSub;/*printf("Reconheceu token TKSub\n");*/return;}
             if (c==-1){lex[posl]='\0';proxC();tk=TKFimArquivo;/*printf("Reconheceu token TKFimArquivo\n");*/return;}
             if (c==' ' || c=='\n' || c=='\t' || c=='\r') {proxC();posl--;break;}
             if (c=='\0') {tk=-1;return;}
             printf("Erro léxico: encontrou o caracter %c (%d)",c,c);
             getch();
             break;
      case 1:if (c>='a' && c<='z' || c>='A' && c<='Z' || c=='_' || c>='0' && c<='9') {proxC();break;}
             lex[--posl]='\0';
             tk=palavra_reservada(lex);
             //printf("reconheceu token %s\n",lex);
             return;
      } //switch
   }// while
}// função


int TLinha();
int ELinha();


//T -> id T'
int T(){
	if(tk == TKId){// id
		getToken();
		if(TLinha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//T' -> * id T' | ?
int TLinha(){
	if(tk == TKProd){// *
		getToken();
		if(tk == TKId){// id
			getToken();
			if(TLinha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//E -> T E'
int E(){
	if(T()){
		if(ELinha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//E' -> + T E' | ?
int ELinha(){
	if(tk == TKSoma){// +
		getToken();
		if(T()){
			if(ELinha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

int main()
{
arqin=fopen("c:\\teste\\prog.c","rb");
if (!arqin) {
printf("Erro na abertura do fonte.\n");
return 0;
}
proxC(); // lê primeiro caracter do arquivo
getToken(); // lê primeiro token
if (E()==0) printf("Erro no reconhecimento\n");
else printf("Reconheceu OK!\n");
system("pause");
}
