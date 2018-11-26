#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<ctype.h>
struct instruction_s{
	int step ;
	int index;
	
};
char * get_word();

void get_sentence(char** lines, struct instruction_s* instructions,int n_instructions, char* sentence){
	int temp = instructions[0].step;
	
	for(int i =0 ;i<n_instructions;i++){
		
		if(i==0){
		
			strcat(sentence,get_word(*(lines+instructions[i].step-1),instructions[i].index-1));
			strcat(sentence," ");
			
			
		}
		else if(i ==n_instructions-1){
			temp+=instructions[i].step;
		
			strcat(sentence,get_word(*(lines+temp-1),instructions[i].index-1));
			strcat(sentence,"\n");
			
			
			
			
		}
		
		else {
			temp+=instructions[i].step;
		
			strcat(sentence,get_word(*(lines+temp-1),instructions[i].index-1));
			strcat(sentence," ");
			
		}
		
		
		
		
		
	}
		
}


void fixer(char *sentence){
	
	char *x = sentence ;
	char  *y = sentence ;

	
	for(int i = 0 ; x[i]!=0; i++){
		
		if(ispunct((unsigned char)x[i])==0){
			
			*y++ = tolower((unsigned char) x[i]);
		}
		
	}
	
	*y = 0;
	
}












char* get_word(char*line ,int index){
	const char s[2] = " ";
	
	
   	char *token;
	int b = 0 ;
	char temp[200];
	char *tem =malloc(sizeof(char*)*200);
	strcpy(temp,line);
	fixer(temp);
	token = strtok(temp, s);
	
	while( token != NULL ) {
   		if(b==index){
   		for(int i =0 ;i<strlen(token);i++){
   			if(token[i]=='\n'|| token[i]=='\r'){
   			break;
		   }
   		
		   tem[i]=token[i];
   		
	   }
		
		   
      	return tem ;
      	
    	}
      	token = strtok(NULL, s);
      	b++ ;
   }
	free(tem);
	free(token);
	
	return tem;
}






int main(int argc,char* argv[]){


char **book = malloc(sizeof(char*)*10000);


char sentence[200]={};

for (int i = 0; i < 10000; i++) {

book[i]= malloc(sizeof(char*)*200);
}

FILE *fptr =fopen(argv[2],"r") ;
if(fptr == NULL)
   {
      printf("%s can not read",argv[2]);   
      return 1  ;          
   }


FILE *fp =fopen(argv[1],"r") ;
if(fp == NULL)
   {
      printf("%s can not read",argv[1]);   
      return 1  ;          
   }
//struct
struct instruction_s *instructions;

instructions= (struct instruction_s*) malloc(10000 * sizeof(struct instruction_s));

int i = 0 ;

while(!feof(fptr)){

fscanf(fptr,"%d %d", &instructions[i].step,&instructions[i].index);	


i++;
}
//struct
int a = 0 ;
while(!feof(fp)){

fgets(book[a],200,fp)	;


a++ ;
}
puts(book);
get_sentence(book,instructions,i-1,sentence);
printf("%s",sentence);

free(*(book));
free(instructions);
fclose(fp);
fclose(fptr);
return 0 ;
	
	
}
