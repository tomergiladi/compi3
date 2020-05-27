%{
	#include "utils.hpp"
	#include "hw3_output.hpp"
	#include "parser.tab.hpp"
	
%}

%option yylineno
%option noyywrap

%%
void	return tkvoid;
int	return tkint;
byte	return tkbyte;
b    return tkb;
bool    return tkbool;
and	return tkand;
or	return tkor;
not	return tknot;
true	return tktrue;
false	return tkfalse;
return	return tkreturn;
if    return tkif;
else    return tkelse;
while return tkwhile;
break return tkbreak;
continue return tkcontinue;
\;    return tksc;
\,    return tkcomma;
\(	return tklp;
\)	return tkrp;
\{	return tklbrace;
\}	return tkrbrace;
\<|\>|\<=|\>=	return tkorder;
=	return tkassign;
==|!=	return tkequality;

\+|\-	return tkarithmetic;
\*|\/	return tkproduct;
[a-zA-Z]([a-zA-Z0-9])*	{yylval=new Token(yytext); return tkid;}
0|[1-9][0-9]*	{yylval=new Token(yytext); return tknumber;}
\"([^\n\r\"\\]|\\[rnt"\\])+\" {yylval=new Token(yytext); return tksrting;}
[\t\n ] ;
\/\/[^\r\n]*(\r|\n|\r\n)? ;
<*>. {output::errorLex(yylineno);exit(0);}; 
%%
