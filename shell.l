

%{

#include <string.h>
#include "y.tab.h"

%}

%%

\n 	{
		return NEWLINE;
	}

[ \t] 	{
		/* Discard spaces and tabs */
     	}	

">" 	{
		return GREAT;
	}
"<" 	{
		return LESS;
	}
">>" 	{
		return APPEND;
	}
">&" 	{
		return GREATAMPS;
	}
">>&" 	{
		return APPENDAMPS;
	}
"|" 	{
		return PIPE;
	}

"&" 	{
		return AMPS;
}

[^ ] {
		yylval.string_val = strdup(yytext);
		return WORD;
    }
	

.	{
		/* Invalid character in input */
		// return NOTOKEN;
		yylval.string_val = strdup(yytext);
		return WORD;
	}

[^ \t\n\>\>\<\&\|][^ \|\>\>\<\&\t\n]* {
		/* Assume that file names have only alpha chars */
		yylval.string_val = strdup(yytext);
		return WORD;
	}


%%
	
