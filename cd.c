/* Author: Hemanth Kumar Veeranki */
/* Nick: Harry7 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <cd.h>

#ifdef _WIN32
#include <windows.h>
#define chdir _chdir

#else
#include <unistd.h>
#endif

#define MAX_LENGTH 1024

void implement_cd(char *path,char *home,char *exe,char *cmd,char *origin){
	//Malloc ing 	
	char *token;
	char *mypath=(char*)malloc(MAX_LENGTH*sizeof(char));
	//checking whether the given path starts with /
	int cnt=0,err;
	if(path[0]=='/'){
		chdir("/");
		strcpy(mypath,"/");
		cnt++;
	}
	bzero(mypath,sizeof(mypath));
	//we store path we have travelled so far in mypath so as to print in case of error 

	token=strtok(path,"/");
	while(token!=NULL){
		strcat(mypath,token);
		if (cnt==0 && strcmp(token,"~")==0) err=chdir(home);
		else err=chdir(token);
		if (err==-1){
			//exe has the name of executable .. cmd is the name of command 
			//strerror is used to get error message for a particular errorno 
			//errno contains the error number generated by previous command
			printf("%s: %s: %s: %s\n",exe,cmd,mypath,strerror(errno));
			chdir(origin);
			break;
		}
		token=strtok(NULL,"/");
		//To store path correctly
		strcat(mypath,"/");
	}
	//token=NULL;
	free(mypath);
	return ;
}

