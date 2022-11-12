#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <syslog.h>
#include "command.h"
#include <time.h>


int glob_sig;
SimpleCommand::SimpleCommand()
{
	// Creat available space for 5 arguments
	_numberOfAvailableArguments = 5;
	_numberOfArguments = 0;
	_arguments = (char **) malloc( _numberOfAvailableArguments * sizeof( char * ) );
}

void
SimpleCommand::insertArgument( char * argument )
{
	if ( _numberOfAvailableArguments == _numberOfArguments  + 1 ) {
		// Double the available space
		_numberOfAvailableArguments *= 2;
		_arguments = (char **) realloc( _arguments,
				  _numberOfAvailableArguments * sizeof( char * ) );
	}
	
	_arguments[ _numberOfArguments ] = argument;

	// Add NULL argument at the end
	_arguments[ _numberOfArguments + 1] = NULL;
	
	_numberOfArguments++;
}

Command::Command()
{
	// Create available space for one simple command
	_numberOfAvailableSimpleCommands = 1;
	_simpleCommands = (SimpleCommand **)
		malloc( _numberOfSimpleCommands * sizeof( SimpleCommand * ) );

	_numberOfSimpleCommands = 0;
	_outFile = 0;
	_inputFile = 0;
	_errFile = 0;
	_background = 0;
	_appendFlag = 0;
	_appendFlagErr = 0;
}

void
Command::insertSimpleCommand( SimpleCommand * simpleCommand )
{
	if ( _numberOfAvailableSimpleCommands == _numberOfSimpleCommands ) {
		_numberOfAvailableSimpleCommands *= 2;
		_simpleCommands = (SimpleCommand **) realloc( _simpleCommands,
			 _numberOfAvailableSimpleCommands * sizeof( SimpleCommand * ) );
	}
	
	_simpleCommands[ _numberOfSimpleCommands ] = simpleCommand;
	_numberOfSimpleCommands++;
}

void
Command:: clear()
{
	for ( int i = 0; i < _numberOfSimpleCommands; i++ ) {
		for ( int j = 0; j < _simpleCommands[ i ]->_numberOfArguments; j ++ ) {
			free ( _simpleCommands[ i ]->_arguments[ j ] );
		}
		
		free ( _simpleCommands[ i ]->_arguments );
		free ( _simpleCommands[ i ] );
	}

	if ( _outFile ) {
		free( _outFile );
	}

	if ( _inputFile ) {
		free( _inputFile );
	}

	if ( _errFile ) {
		free( _errFile );
	}

	_numberOfSimpleCommands = 0;
	_outFile = 0;
	_inputFile = 0;
	_errFile = 0;
	_background = 0;
}

void
Command::print()
{
	printf("\n\n");
	printf("              COMMAND TABLE                \n");
	printf("\n");
	printf("  #   Simple Commands\n");
	printf("  --- ----------------------------------------------------------\n");
	
	for ( int i = 0; i < _numberOfSimpleCommands; i++ ) {
		printf("  %-3d ", i );
		for ( int j = 0; j < _simpleCommands[i]->_numberOfArguments; j++ ) {
			printf("\"%s\" \t", _simpleCommands[i]->_arguments[ j ] );
		}
		printf("\n");
	}

	printf( "\n\n" );
	printf( "  Output       Input        Error        Background\n" );
	printf( "  ------------ ------------ ------------ ------------\n" );
	printf( "  %-12s %-12s %-12s %-12s\n", _outFile?_outFile:"default",
		_inputFile?_inputFile:"default", _errFile?_errFile:"default",
		_background?"YES":"NO");
	printf( "\n\n" );
	
}


void log_func(int)
{
	FILE *f;
	time_t t;
	time(&t);
	f = fopen("file.log", "a");
	//int f = open("file.log", O_CREAT | O_APPEND, 0666); 
	fprintf(f, "Process Terminated at: %s \n",ctime(&t));
	fclose(f);
}
void
Command::execute()
{  
	glob_sig = 0;
	// Don't do anything if there are no simple commands
	if ( _numberOfSimpleCommands == 0 ) {
		prompt();
		return;
	}
	print();

	/////////////////////////////////////////////////////
	///////////// Handle File Redirection ///////////////
	/////////////////////////////////////////////////////

	// System call creates a copy of a file descriptor.
	// Here, we take stdin(0) and put it in default in and so on.
	
	int defaultin = dup( 0 );
	int defaultout = dup( 1 );
	int defaulterr = dup( 2 );
	int outfd;
	int infd;
	int errfd;
	int org_outfd;

	// Nour is debugging here
	// int err = open("err.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666); 
	/*
	printf("Here is defaultin %d\n",defaultin);
	printf("Here is defaultout %d\n",defaultout);
	printf("Here is defaulterr %d\n",defaulterr);
	*/

	// Setting the right file descriptors to redirect to
	// OUTPUT
	if (_outFile && _appendFlag){
		// create file descriptor for outfd to append to
		outfd = open(_outFile, O_CREAT | O_APPEND | O_WRONLY, 0666); // 0666 is to define set of permissions
		// O_CREAT: if file doesn't exist create it
		// O_APPEND: if file exists append to it
		// O_WRONLY: write only
		// printf("Appended to a file\n");	
		}
	else if(_outFile){
		// create file descriptor for outfd to overwrite to
		outfd = open(_outFile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		// O_CREAT: if file doesn't exist create it
		// O_TRUNC: if file exists delete what's in it
		// O_WRONLY: write only
		//printf("Created a file\n");
	}
	else{
		// if _outFile = 0, file descriptor remains the same
		outfd = defaultout;
	}
	// ERROR
	if (_errFile && _appendFlagErr){
		errfd = open(_errFile, O_CREAT | O_APPEND | O_WRONLY, 0666); // 0666 is to define set of permissions
	}
	else if(_errFile){
		// create file descriptor for errfd to overwrite to
		errfd = open(_errFile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	}
	else{
		// if _errFile = 0, file descriptor remains the same
		errfd = defaulterr;
	}
	// INPUT
	if (_inputFile){
		// create file descriptor for infd
		infd = open(_inputFile, O_RDONLY, 0666);
		// O_RDONLY: read only
	}
	else{
		// if _inputFile = 0, file descriptor remains the same
		infd = defaultin;
	}

	org_outfd = outfd;


	dup2(errfd, 2);
	close(errfd);
	/////////////////////////////////////////////////////

	/////////////////////////////////////////////////////
	//////////// Handle Commands & Piping ///////////////
	/////////////////////////////////////////////////////

	int pid;
	int n = _numberOfSimpleCommands;

	// Nour is debugging here
	// dprintf(err, "Number of commands is %d\n", n);

	// Looping on simple commands, each: cmd + [args]* 
	for (int i = 0; i < n; i++){

		// Redirecting to file or piped command as input
		dup2(infd, 0);

		// Nour is debugging here
		// dprintf(err, "IN OF COMMAND %d is %d\n", i, infd);

		if (i == n -1 ){ // if we're at the last command
			outfd = org_outfd;
		}
		else{ // If we're not at the last command, do a pipe
			int fdpipe[2];
			if(pipe(fdpipe) == -1){
				perror("ERROR IN PIPING.");
				exit(2);
			}
			outfd = fdpipe[1];
			infd = fdpipe[0];
		}
		// Nour is debugging here
		// dprintf(err, "OUT OF COMMAND %d is %d\n", i, outfd);

		// Redirect to output
		dup2(outfd, 1);
		close(outfd);

		// Handling the cd command before any process is forked 
			if(strcmp(_simpleCommands[i]->_arguments[0],"cd")==0){
				// Checking if dir is not specified
				if(_simpleCommands[i]->_numberOfArguments == 1){
					chdir(getenv("HOME"));
				}
				else if ( strcmp(_simpleCommands[i]->_arguments[1],"~") == 0 ){
					chdir(getenv("HOME"));
				}
				else{ 
					int change_dir = chdir(_simpleCommands[i]->_arguments[1]);
					if (change_dir == -1){
						printf("No such File or directory.\n");
					}
					// Lara debugging here
					// printf("change_dir value: %d\n",change_dir);
					// printf("argument is: %s\n",_simpleCommands[i]->_arguments[1]);
				}
			}

		// SIGCHLD catchers are usually set up as part of process initialization. 
		// They must be set before a child process is forked. 
		// A typical SIGCHLD handler retrieves the child process's exit status.
		signal (SIGCHLD, log_func);

		// Create child
		pid = fork();

		if (pid == -1) {
			perror("ERROR IN FORK.");
			exit(2);
		}
		if (pid == 0){
			
			// Close fds
			close(outfd);
			close(infd);
			close(defaultin);
			close(defaultout);
			close(defaulterr);

			// We add an extra argument called NULL to the lists of argument
			// This to make exevp work correcly
			int num_args = _simpleCommands[i]->_numberOfArguments;
			char ** args = _simpleCommands[i]->_arguments;
			char ** full_command = (char **) realloc(args,(num_args + 1) * sizeof(char*));
			full_command[num_args] = NULL;
			execvp(full_command[0],full_command);
			exit(1);

		}
	} //endfor



	/////////////////////////////////////////////////////
	////////// Handle File Redirection Contd. ///////////
	/////////////////////////////////////////////////////


	// Dup2 takes first argument and puts it in second argument (opposite of dup)
	// Here, we return input to be stdin, output to be stdout, and error to be stderr
	
	dup2(defaultin,0);
	dup2(defaultout,1);
	dup2(defaulterr,2);

	// Close file descriptors that are not needed
	close(defaultin);
	close(defaultout);
	close(defaulterr);
	close(infd);
	close(outfd);

	// Wait for child process to terminate
	if (_background == false) {
		waitpid(pid, NULL, 0);
	}

	////////////////////////////////////////////////////

	// Clear to prepare for next command
	clear();
	
	// Print new prompt
	if(glob_sig == 0){
		prompt(); // only prompts if the signal hasn't been generated yet
				// glob_sig gets assigned to 1 when CTRL + C signal is generated
				// this is done to prevent prompting user twice in commands that need
				// ctrl+c signal to terminate, such as "cat" command
	}

}

// Shell implementation

void
Command::prompt()
{
	printf("lano>");
	fflush(stdout);
}

Command Command::_currentCommand;
SimpleCommand * Command::_currentSimpleCommand;

int yyparse(void);

void handler(int i){
	fprintf(stdout, "\nCTRL-C does nothing here! Type \"exit\" to exit!\n");
	Command::_currentCommand.prompt();
	glob_sig = 1;
}

int 
main()
{
	glob_sig = 0;
	signal(SIGINT, handler); 
	Command::_currentCommand.prompt();
	yyparse();
	return 0;
}

