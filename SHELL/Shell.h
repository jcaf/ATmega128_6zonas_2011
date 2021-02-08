/*
 * Shell.h
 *
 * Created: 8/9/2012 3:26:59 PM
 *  Author: jcaf
 */ 
#ifndef SHELL_H_
#define SHELL_H_

	typedef enum _CODERETURN_TOSHELL
	{
		NONE_CODE = 0,
		INTERNAL_SELECTION= 1,
		RESTORE_SHELL =2,
		NO_CHANGES = 3,
		
	}CODERETURN_TOSHELL;
	
	typedef enum _EXEC_FX
	{
		NONE_TO_EXECUTE=0,
		PREPARE_EXECUTING=1,
		CONTINUOS_EXECUTING=2,
	}EXEC_FX;

	struct _shell
	{
		CODERETURN_TOSHELL coderet;
		EXEC_FX exec_fx;
	};	

	extern struct _shell shell;
	
	void Shell_main(void);

#endif /* SHELL_H_ */
