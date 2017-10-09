#include<stdio.h>
#include<string.h>
struct instr
{
char mc[10];
int len;
char op[5];
}optab[5];
void main()
{
FILE *fp1,*fp2,*fp3;
char str[30],label[20],str1[30];
int loc,ct,i,j,labadr;
struct instr optab[4]={{"LDA",3,"00"},{"STA",3,"0c"},{"LDCH",3,"50"},{"STCH",3,"54"}};
fp1=fopen("passonein.c","r");
fp2=fopen("passoneout.c","w");
fp3=fopen("sym.c","w+");
printf("\n enter the starting address:");
scanf("%x",&loc);
do{
loop:
fscanf(fp1,"%s",str);
for(i=0;i<4;i++)
{
if(strcmp(str,optab[i].mc)==0)
{
fscanf(fp1,"%s",str1);
fprintf(fp2,"\n\t%x\t%s\t%s",loc,str,str1);
printf("\n\t%x\t%s\t%s",loc,str,str1);
loc=loc+optab[i].len;
goto loop;
}}
if(strcmp(str,"WORD")==0)
{
fscanf(fp1,"%d",&ct);
fprintf(fp2,"\n\t%x\t%s\t%d",loc,str,ct);
printf("\n\t%x\t%s\t%d",loc,str,ct);
loc=loc+2;
}
else if(strcmp(str,"RESW")==0)
{
fscanf(fp1,"%d",&ct);
fprintf(fp2,"\n\t%x\t%s\t%d",loc,str,ct);
printf("\n\t%x\t%s\t%d",loc,str,ct);
loc=loc+(2*ct);
}
else if(strcmp(str,"RESB")==0)
{
fscanf(fp1,"%d",&ct);
fprintf(fp2,"\n\t%x\t%s\t%d",loc,str,ct);
printf("\n\t%x\t%s\t%d",loc,str,ct);
loc=loc+ct;
}
else if(strcmp(str,"byte")==0)
{fscanf(fp1,"%s",str1);
fprintf(fp2,"\n\t%x\t%s",loc,str,str1);
printf("\n\t%x\t%s\t%s",loc,str,str1);
if(str[0]=='c')
loc=loc+(strlen(str1)-4);
else
loc=loc+1;
}
else
fprintf(fp3,"\n%s\t%x",str,loc);
}
while(!feof(fp1));
printf("\nsymboltable\n");
rewind(fp3);
while(!feof(fp3))
{
fscanf(fp3,"%s%x",label,&labadr);
printf("\n%s\t%x",label,labadr);
}
fclose(fp1);
fclose(fp2);
fclose(fp3);
}
