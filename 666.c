#include<stdio.h> 

int main() 
{ 
 	if(fork()==0) 
 	{ 
 	        printf("child id: %d\n",getpid());  	        printf("parent id: %d\n",getppid());  	        sleep(10); 
 	        printf("child id: %d\n",getpid());  	        printf("parent id: %d\n",getppid()); 
 	} 
 	else{ 
 	        sleep(10);  	        printf("PARENT id: %d\n",getpid()); 
 	} 
 	return 0; 
} 



#include<stdio.h> 
#include<stdlib.h> 

int main() 
{ 
       FILE *f;        char a[100];        

       printf("enter the data of file\n");       

       scanf("%[^\n]s",&a);        
       printf("the file data is: \n  %s",a);        
       f=fopen("mine.txt","w");        
       fprintf(f,"%s",a);        
       fclose(f); 
       f=fopen("mine.txt","r");        
       char c;       
        while(1) 
       { 
               c=fgetc(f);                
               if(feof(f))break;                
               printf("%c",c); 
       } 
       return 0;  
} 
