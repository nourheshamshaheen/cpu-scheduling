#ifndef _yy_defines_h_
#define _yy_defines_h_

#define WORD 257
#define COMMA 258
#define STATS 259
#define TRACE 260
#define DIGIT 261
#define DASH 262
#define DOUBLE_DIGIT 263
#define CHAR 264
#define NEWLINE 265
#define number_of_proc 266
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union YYSTYPE	{
		char   *string_val;
	} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

#endif /* _yy_defines_h_ */
