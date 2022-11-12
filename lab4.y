
/*
 * CS-413 Spring 98
 * shell.y: parser for shell
 *
 * This parser compiles the following grammar:
 *
 *	cmd [arg]* [> filename]
 *
 * you must extend it to understand the complete shell grammar
 *
 */

%token	<string_val> WORD

%token 	NOTOKEN GREAT NEWLINE LESS AMPS APPEND PIPE GREATAMPS APPENDAMPS

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
#include "command.h"
#include <signal.h>
#include <glob.h>
#include <string.h>
%}

%%

goal:	
	commands
	;

commands: 
	command
	| commands command 
	;

command: simple_command
        ;

simple_command:	
	piped_command iomodifier_opt_list NEWLINE {
		printf("   Yacc: Execute command\n");
		Command::_currentCommand.execute();
	}
	/* Here, we wanted that each time we pressed enter, a new prompt got printed */
	| NEWLINE
	{
		Command::_currentCommand.prompt();
	}
	| error NEWLINE { yyerrok; }
	;

piped_command:
	piped_command PIPE command_and_args
	| command_and_args
	;

command_and_args:
	command_word arg_list {
		Command::_currentCommand.insertSimpleCommand( Command::_currentSimpleCommand );
	}
	;

arg_list:
	arg_list argument
	| /* can be empty */
	;

// input:
// 	WORD
// 	| CHAR 
// 	|
// 	;

argument:
	WORD {
		char * str = (char *) malloc( sizeof($1) * sizeof( char ) );
		str = $1;
		// printf("String is %s", str);
		if(strstr(str,"*")!=NULL || strstr(str,"?")!=NULL){
			glob_t glob_out; 
			if (glob(str, GLOB_ERR, NULL, &glob_out) != 0)
			{
				perror("ERROR IN PATTERN MATCHING. EXITING...");
				exit(2);
			}
			// Loop over found directories and files
			for(size_t i = 0; i < glob_out.gl_pathc; i++)
			{
				printf("   Yacc: insert argument \"%s\"\n", glob_out.gl_pathv[i]);
				Command::_currentSimpleCommand->insertArgument(glob_out.gl_pathv[i]);
			}
		}
		else
		{
			printf("   Yacc: insert argument \"%s\"\n", $1);
			Command::_currentSimpleCommand->insertArgument( $1 );
		}
	}
	;

command_word:
	WORD {
		// Here, we implement our exit function
			if (strcmp($1, "exit") == 0) {
				printf("You are now exiting Nour and Lara's shell. Bye!\n");
				exit(0);	
			}
			printf("   Yacc: insert command \"%s\"\n", $1);
	       
	       Command::_currentSimpleCommand = new SimpleCommand();
	       Command::_currentSimpleCommand->insertArgument( $1 );
	}
	;

iomodifier_opt_list:
	iomodifier_opt_list iomodifier_opt
	|
	iomodifier_opt
	|
	;

iomodifier_opt:
	GREAT WORD {
		printf("   Yacc: insert output \"%s\"\n", $2);
		Command::_currentCommand._outFile = $2;
		Command::_currentCommand._appendFlag = 0;

	}
	| APPEND WORD {
		printf("   Yacc: insert output \"%s\"\n", $2);
		Command::_currentCommand._outFile = $2;
		Command::_currentCommand._appendFlag = 1;
	}
	| LESS WORD {
		printf("   Yacc: insert input \"%s\"\n", $2);
		Command::_currentCommand._inputFile = $2;

	}
	| AMPS {
		printf("   Yacc: running in background.\n");
		Command::_currentCommand._background = true;

	}	
	| APPENDAMPS WORD {
		printf("   Yacc: insert error \"%s\"\n", $2);
		Command::_currentCommand._errFile = $2;
		Command::_currentCommand._appendFlagErr = 1;
	}
	| GREATAMPS WORD {
		printf("   Yacc: insert error \"%s\"\n", $2);
		Command::_currentCommand._errFile = $2;

	} 
	|
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
