#include<stdio.h>


int ffunction(int number,char a);
int sfunction(int value,int ring,char segment,int target,int points);

int main(){
	
int target = 0 ;
int ring ;
char segment  ;
	
printf("Target:  ");
scanf("%d",&target);
int points = target ;
while (points>0){

	printf("Throw:  ");
	
	scanf("%d %c",&ring,&segment);


 	int value=ffunction(ring,segment);
 	
 	points = sfunction(value,ring,segment,target,points);	
 
 	printf("Points: %d \n",points);

	
	}
	
return 0 ;
	
}

int ffunction(int number,char a){
	
	int value;
	
	if( a == 'T'){
		value = number*3 ;
	}
	else if (a == 'D'){
		value = number * 2 ;
	}
	else if (a == 'S'){
		value = number;
	}
	else if (a == 'O'){
		value = 25;
	}
	else if (a == 'I'){
		value = 50;
	}

	
	
	
	return value ;
	
	
}

int sfunction(int value,int ring,char segment,int target,int points) {
	
	if (target == points){
		if(segment == 'D'){
			points = target - value ;
			return points ;
		}
		else{
		
			return target ;
		}
		
		
	}
	
	
	else{
	
		points = points - value ;
			if (points >0 ){
				return points;
						}
			else {
					if(segment == 'D' && points ==0){
						
									return points ;
									
													}					
					else{
						points =points+value ;
						return points ;
						}
		
		
				}
	
	
	
	
		}
	}
	
	
	
	
    
  
  



