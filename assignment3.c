#include<stdio.h>
#include <stdlib.h>


int main(){
	

int s,c,yaxis,axis;
printf("Size: ") ;
scanf("%d",&s);

if(s>=51){
	printf("max size must be 50");   //this if block checks whether the size condition satisfied or not.
	printf("\n");
	printf("Size: ") ;
	scanf("%d",&s);
}

printf("Cars: ");
scanf("%d",&c);

if(c>s*s){
	return EXIT_FAILURE ; // if there are more cars than parking place it  returns failure.
}

if(c == 0){
	printf("Best Slot Found In: 1 1\n"); //if there is no car in the parking area best place is 1 1
	return 0 ;
}

if (c== s*s){
	printf("Best Slot Found In: 0 0\n"); //if  park is full it says 0 0 is your park place
	return 0 ;
}
	
int slot [50][50];// Parking area

int x,y ; // coordinates

for(int k =0 ;k<s ;k++){

	for(int j = 0 ; j < s ; j++ ){ // in this for loop all park places are filled with 0
	
			slot[k][j]= 0;
				
								 }
	
	
}
for (int i = 0;i < c  ;i++){

	printf("Locations: ");
	scanf("%d %d",&x,&y);		
	
	
	x-- ;
	y-- ;
	slot[y][x] = 1 ;
	
		
}	
int  array[50][50] ; // this array keeps distance values inside.

for(int k =0 ;k<s ;k++){ 	// in order to compare all park places first I fill with 0

	for(int j = 0 ; j < s ; j++ ){
	
			array[k][j]= 0;
				
	 }
}

int z ; //manhattan distance 
int dist =109; // this parameter is 109 because max distance could be 98 ,so it is greater than max distance
int distx,disty; // parameters for calculating manhattan distance

for (int a =0 ;a<s ;a++){
	for(int b =0 ;b<s ;b++){
		dist =109 ;
		if (slot[a][b] ==0){
			for (int l = 0 ; l<s ; l++){
				for (int o =0 ; o<s ;o ++){
					if (slot[l][o]==1){
									disty=a-l;
									distx=b-o;
									if(distx<0){
										distx=distx*-1;
									}
									if(disty<0)
									{
										disty=disty*-1;	
									}			
									z=distx+disty;					
									
									if (z<dist){
										dist = z;
										array[a][b] = dist;
									}  										
																	
																
					}	
					
								
					
				}
				
			}
			
			
		}
		
				
	}
	
		
}


int max = -10;

for(int a =0 ; a<s ;a++){
	for(int b =0 ; b<s; b ++){ 				/*this part compares manhattan distances and if there are points that have the same distance it chooses the point which 
											has the smaller x and y																			*/
		if(array[a][b] == max ){
			
			if (yaxis<a+1){
				max = array[a][b] ;
				axis =b+1;
				yaxis =a+1 ;
			
								
			}
									
		}
		
		else if(array[a][b]>max){
			max = array[a][b];
			axis =b+1 ;
			yaxis =a+1 ;
		}
		
	}
	
	
	
}
printf("Best Slot Found In: %d %d\n",axis,yaxis);

 
return 0 ;
}
