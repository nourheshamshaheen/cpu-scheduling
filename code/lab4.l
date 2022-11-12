
%{

#include <string.h>
#include "y.tab.h"

%}

%%

\n 	{
		return NEWLINE;
	}

"-" {
	return DASH;
}

"," {
	return COMMA;
}

"stats" {
	return STATS;
}

"trace" {
	return TRACE;
}

[A-Za-z] {
		yylval.string_val = strdup(yytext);
		return CHAR;
	}


[1-8] {
	return DIGIT;
}

[1-9]|[10-99] {
	return DOUBLE_DIGIT;
}

%%
	
