#include<stdio.h>

int main(){
	
	int month,day,year,end_year;
	int beta = 112 ;

	printf("Enter date [year month day] : ");
	scanf("%d %d %d",&year,&month,&day);
	
	int first_year =year ;

	if ( month==1 && 0<day && day<32){
		month+=12;
		year--;		
	}
	else if(month==2&& 0<day&& day<28){
		month+=12;
		year--;
							}
	else if(month==3&& 0<day&& day<32){
							}
	else if(month==4&& 0<day&& day<31){
				}
	else if(month==5&& 0<day&& day<32){
				}
	else if(month==6&& 0<day&& day<31){
			}
	else if(month==7&& 0<day&& day<32){
			}
	else if(month==8&& 0<day&& day<32){
			}
	else if(month==9&& 0<day&& day<31){
			}
	else if(month==10&& 0<day&& day<32){
			}
	else if(month==11&& 0<day&& day<31){
		}
	else if(month==12&& 0<day&& day<32){
	 	 		 } 						
	else{
		printf("Invalid date\n");
		int beta =111 ;
		return beta ;
				 
	}
	
	int j = year/100 ;
	int k = year%100 ;
	int nday ;
	int a = k/4 ;
	int b = j/4 ;
	int c =(13*(month+1))/5 ;
	int same_dates = 0 ;
	int oday ;
	
	if(beta==112){
		printf("Enter end year : ");
	}		
	scanf("%d",&end_year);

	nday = (day+c+k+a+b+5*j) ;
	nday = nday%7 ;

	switch(nday){
		case 0 :
			printf("It's a Saturday.\n");
			break;
		case 1 :
			printf("It's a Sunday.\n");
			break;
		case 2 :
			printf("It's a Monday.\n");
			break;
		case 3 :
			printf("It's a Tuesday\n");
			break;
		case 4:
			printf("It's a Wednesday.\n");
			break;
		case 5 :
			printf("It's a Thursday.\n");
			break;
		case 6 :
			printf("It's a Friday.\n");
			break; 			
	}

	for(year ;year<=end_year ;year++) { 
		 int z = year%100 ; // j =z  
		 int x = year/100 ; //k =x
		 int e = k/4 ;//a
		 int d = j/4 ;//b
		 
		 oday = (day+ c+x+e+d+5*z) ;
		 oday =oday %7 ;
		 
		
	
		if(oday==nday){
			same_dates++;
		}			
			
	}
	
	printf("Same day-and-month on same weekday between %d and %d: %d\n",first_year,end_year,same_dates) ;

	return 0;
	
}


























































































