#include <stdio.h>

void find(char*name,char*h,int *point,char x[]){

 


for(int i =0 ; name[i] != '\0' ;i++){

	if(name[i] == h[0]){
		x[i]=name[i];
		*point=*point+1;
	}
	else{
		if(x[i]=='<' ){
		
		x[i]= '_' ;
		}
	}

}
printf("%s \n",x) ;
}



int main(){
	
	char name[] = "kayraaa" ;	//UNKOWN WORD
	
	char x[] ="<<<<<";
	int point = 0 ;
	char h[20] ;
	
	
	for(int i =0 ;i<10;i++){//10 REPRESENT CHANCES 
		
	
		
		scanf("%s",h) ;
		
		
		find(name,h,&point,x) ;
		
		if (point==5) {
			printf(" you got it");
			break ;
		}
	
		
 
 					
		
		
		
		
	}
	
	if(point!=5){
		printf("hanging from the gallows pole") ;
	}
	
	
	return 0 ;
	
	
}
