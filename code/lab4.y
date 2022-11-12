
%token	<string_val> WORD
%token COMMA STATS TRACE DIGIT DASH DOUBLE_DIGIT CHAR


%union	{
		char   *string_val;
	}

%{
extern "C" 
{
	int yylex();
	void yyerror (char const *s);
}

#define yylex yylex
#include <stdio.h>
#include "scheduling.h"
#include <string.h>
%}

%%

goal:	
	schedule
	;

schedule: simple_schedule_file
        ;

simple_schedule_file:	
	flag NEWLINE policy_list NEWLINE timespan NEWLINE number_of_proc NEWLINE processes_list {
		//printf("   Yacc: \n");
	}
	;

policy_list:
	policy_list COMMA policy
	| policy
	;

processes_list:
	processes_list NEWLINE process
	| process
	;

flag:
	STATS {
		// flag of struct = 1				
	}
	| TRACE {
		// flag of struct = 0
	}

policy:
	DIGIT DASH DOUBLE_DIGIT {
		// insert into list of policies tuple id, quantum

	}
	| DIGIT {
		// insert into list of policies id, 0
	}
	;

timespan:
	DIGIT {
		// insert into current_scheduling timespan
	}
	;

process:
	CHAR COMMA DOUBLE_DIGIT COMMA DOUBLE_DIGIT {

	}
	;




%%

void
yyerror(const char * s)
{
	fprintf(stderr,"%s", s);
}

#if 0
main()
{
	yyparse();
}
#endif
