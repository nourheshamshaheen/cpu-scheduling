
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
		// Scheduler::currentScheduler.flag = 1;
	}
	| TRACE {
		// Scheduler::currentScheduler.flag = 0;
	}

policy:
	DIGIT DASH DOUBLE_DIGIT {
		SimpleScheduler temp;
		// temp.policy_id = $1;
		// temp.quantum = $3;
		// Scheduler::currentScheduler.insertSimpleScheduler(temp);
	}
	| DIGIT {
		// SimpleScheduler temp;
		// temp.policy_id = $1;
		// temp.quantum = 0;
		// Scheduler::currentScheduler.insertSimpleScheduler(temp);
	}
	;

timespan:
	DIGIT {
		// Scheduler::currentScheduler.timespan=$1;
	}
	;

process:
	CHAR COMMA DOUBLE_DIGIT COMMA DOUBLE_DIGIT {
		// Process temp;
		// temp.name = $1;
		// temp.arrival = $3;
		// temp.service = $5;
		// Scheduler::currentScheduler.insertProcess(temp);

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
