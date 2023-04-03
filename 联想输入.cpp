#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#define N 40 
#define N1 10
#define N2 40
char a;
typedef int mytype;
typedef struct Node{
	mytype a;                   //�洢Ȩֵ
	char b[2];                  //��������
}Node;
typedef struct sqlist{
	Node *elem;
	int length;
	int listsize;
}sqlist;
typedef struct Node1{
	sqlist address;              //��ÿ�����ֵ�Ȩֵ���Ա�洢�������� 
	char d[2];
	int memory;                   //��¼�����Ա�������� 
	struct Node1 *next1;
}Node1,*linklist;
typedef struct cylist{ 
        char cy[2];
        char houzhui[6*N2];
        int cysum;
        struct cylist *next;
}*idm;
char cysuggest[8]={0};            //����ѡ�� 
idm cy;
linklist name;                   //������
linklist next1;
sqlist next;
sqlist L1;
char xx[166];                     //�洢��������
int shu=0;
char suggest[8];                  //�洢�Ƽ�ѡ��
void Initidiom(idm &cy)                 
{                                   //��ʼ���������� 
	cy=(idm)malloc(sizeof(cylist));
	cy->next=NULL;
}
void Creatidiom(idm &cy,char n1,char n2)
{                                    //����һ�����ֵĳ�������µĳ���ڵ� 
	idm cy1;
	cy1=(idm)malloc(sizeof(cylist));
	cy1->cysum=1;
	cy1->cy[0]=n1;
	cy1->cy[1]=n2;
	cy1->next=cy->next;
	cy->next=cy1;
}
void Addidiom(idm &cy,char n1,char n2,char n3,char n4,char n5,char n6,char n7,char n8)
{                                       //���ӳ��� 
	idm c=cy->next;
	int flag=0;
	while(c)
	{
		if((c->cy[0]==n1)&&(c->cy[1]=n2))
		{
			c->houzhui[6*(c->cysum-1)]=n3;
			c->houzhui[6*(c->cysum-1)+1]=n4;
			c->houzhui[6*(c->cysum-1)+2]=n5;
			c->houzhui[6*(c->cysum-1)+3]=n6;
			c->houzhui[6*(c->cysum-1)+4]=n7;
			c->houzhui[6*(c->cysum-1)+5]=n8;
			flag=1;
			c->cysum=c->cysum+1;
		}
		c=c->next;
	}
	if(flag==0){
		Creatidiom(cy,n1,n2);
		Addidiom(cy,n1,n2,n3,n4,n5,n6,n7,n8);
	}
}
void Read_cy()
{                                        //��ȡ�����ļ� 
	FILE* fp = NULL;
	fp = fopen("CY.txt", "r");
	if (fp == NULL)
	{
		perror("my_fread fopen");
		return;
	}
	char *cynr;
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if(size > 0)
    {
        //printf("size: %d\n",size);
        cynr=(char *)malloc((size+1)*sizeof(char));
    }
	int ret = fread(cynr,2,size/2, fp);
	int size1=size;
	for(int i=0;i<size1;i++)
	{
		if(cynr[i]=='\n')
		{
			for(int j=i;j<size1;j++)
			{
				cynr[j]=cynr[j+1];
				size1=size1-1;
			}
		}
	}
	for(int i=0;i<size1;i=i+8)
	{                                  //ÿ8���ֽڣ� �ĸ��֣�����һ�����ӳ��� 
		Addidiom(cy,cynr[i],cynr[i+1],cynr[i+2],cynr[i+3],cynr[i+4],cynr[i+5],cynr[i+6],cynr[i+7]);
	}
}
void Search_cy(idm cy,char n1,char n2,int k)
{                                       //���ҳ������� 
	int flag=0;
	idm c=cy->next;
	while(c)
	{
		if((c->cy[0]==n1)&&(c->cy[1]=n2))
		{
			cysuggest[0]=n1;
			cysuggest[1]=n2;
			flag=1;                             //ѭ���任ѡ�� 
			if(k<=(c->cysum)-1)for(int i=2;i<8;i++)cysuggest[i]=c->houzhui[6*(k-1)+i-2];
			if(k>(c->cysum)-1)
			{
				if(!(k%((c->cysum)-1)))k=(c->cysum)-1;
				else{
					k=k%((c->cysum)-1);
				}
				for(int i=2;i<8;i++)cysuggest[i]=c->houzhui[6*(k-1)+i-2];
			}
		}
		c=c->next;
	}
	if(flag==0){                           //���Ҳ���ʱ�Ƽ�ѡ������� 
		for(int i=0;i<8;i=i+2)
		{
			cysuggest[i]=char(-65);
		    cysuggest[i+1]=char(-43);
		}
	}
}
void Creatlist(linklist &L)
{                                              //����������
	L=(linklist)malloc(sizeof(Node1));
	L->d[0]='1';
	L->d[1]='2';
	L->next1=NULL;
}
void Newlist(linklist &L,char n1,char n2,sqlist &a)
{                                                // �����Ա�洢��������
	linklist s;
	s=(linklist)malloc(sizeof(Node1));
	s->address=a;
	s->memory=a.length;
	s->d[0]=n1;
	s->d[1]=n2;
	s->next1=L->next1;
	L->next1=s;	
}
void Creat_LINEAR_table(sqlist &L,char n1,char n2)
{                                                     //�������Ա�
	L.elem = (Node *)malloc(N*sizeof(Node));
	L.elem[0].b[0]=n1;
	L.elem[0].b[1]=n2;
	L.elem[0].a=1;
	L.length=1;
	L.listsize=N;
	Newlist(name,n1,n2,L);
}
void Addelem(sqlist &L,char n1,char n2,linklist &c)
{                                                        //�����µĺ���Ԫ��
	L.length=c->memory;
	L.elem[L.length].b[0]=n1;
	L.elem[L.length].b[1]=n2;
	L.elem[L.length].a=1;
	L.length++;
	c->memory=L.length;
	if(L.length==L.listsize)
	{
		L.elem = (Node *)realloc(L.elem,N1*sizeof(Node));
		L.listsize=L.listsize+N1;
	}
}
void Addweight(sqlist &L,char n1,char n2,linklist &c)
{                                           //����Ȩֵ
    int i=0;
	int flag=0;
	while(i<c->memory)
	{
			if((L.elem[i].b[0]==n1)&&(L.elem[i].b[1]==n2))
		    {
			    L.elem[i].a++;
			    flag=1;
		    }
		i++;
	}
	if(flag==0)
	{
		Addelem(L,n1,n2,next1);
	}
}
void Addname(linklist &L,char n1,char n2)
{                                                   //������Ҫ�����Ա�
	linklist c;
	c=L->next1;
	int flag=0;
	while(c)
	{
		if((c->d[0]==n1)&&(c->d[1]==n2))
		{
			flag=1;
			next=c->address;
			next1=c;
		}
		c=c->next1;
	}
	if(flag==0)
	{
		sqlist L1;
		Creat_LINEAR_table(L1,n1,n2);
		Addname(L,n1,n2);
	}
}
/*
void printList(sqlist L,linklist1 c)
{
	int i;
	for(i=0;i<c->memy;i++)
	{
		if(i<c->memy-1)
		{
			printf("%c%c ",L.elem[i].b[0],L.elem[i].b[1]);
			printf("%d->",L.elem[i].a);
		}
		else{
			printf("%c%c ",L.elem[i].b[0],L.elem[i].b[1]);
			printf("%d",L.elem[i].a);
		}
	}
	printf("\n");
}*/
void Read_file()
{                                            //��ȡ�ļ��õ�Ȩֵ
	FILE* fp = NULL;
	fp = fopen("b.txt", "r");
	if (fp == NULL)
	{
		perror("my_fread fopen");
		return;
	}
	char *hanzi;                          //���������ֽڹ��ɣ������
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if(size > 0)
    {
        //printf("size: %d\n",size);
        hanzi=(char *)malloc((size+1)*sizeof(char));
    }
	int ret = fread(hanzi,2,size/2, fp);
	int size1=size;
	for(int i=0;i<size1;i++)
	{
		if(hanzi[i]=='\n')             //ȥ���س�
		{
			for(int j=i;j<size1;j++)
			{
				hanzi[j]=hanzi[j+1];
				size1=size1-1;
			}
		}
	}
	//hanzi[size]='\0';
	//printf("%s\n",hanzi);
	for(int i=0;i<size;i=i+2)
	{
		Addname(name,hanzi[i],hanzi[i+1]);
		if(i<size-2)
		{
			Addweight(next,hanzi[i+2],hanzi[i+3],next1);          //������һ���������ǰһ�����ֵ�Ȩֵ
		}
	}
	//printf("ret = %d\n", ret)��
	//sqlist q=name->next1->next1->next1->next1->address;
	//printList(q,name->next1->next1->next1->next1->next1);
	free(hanzi);
	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}
}
void Sort(sqlist &L,int num)
{                                    //Ȩֵ����
	int i,j;
	char n1,n2;
	int a1;
	for(i=0;i<num-1;i++)
	{
		for(j=0;j<num-i-1;j++)
		{
			if(L.elem[j].a<L.elem[j+1].a)
			{
				a1=L.elem[j].a;
				L.elem[j].a=L.elem[j+1].a;
				L.elem[j+1].a=a1;
				n1=L.elem[j].b[0];
				L.elem[j].b[0]=L.elem[j+1].b[0];
				L.elem[j+1].b[0]=n1;
				n2=L.elem[j].b[1];
				L.elem[j].b[1]=L.elem[j+1].b[1];
				L.elem[j+1].b[1]=n2;
			}
		}
	}
}
void Set_option(char n1,char n2)
{                                       //����ѡ��
	linklist r=name->next1;
	int i,j,k=0,flag=0;
	int jilu=0;
	while(r)
	{
		if((r->d[0]==n1)&&(r->d[1])==n2)
		{
			flag=1;
			Sort(r->address,r->memory);
			for(i=0;i<8;k++)
			{
				suggest[i]=r->address.elem[k].b[0];
                suggest[i+1]=r->address.elem[k].b[1];
                i=i+2;
			    if((r->memory)<4)
				{
    				if(2*i==r->memory)
				    {
				    	break;
				    }
    			}
			}
		}
		r=r->next1;
	}
	if(flag==0)                                   //û�м�¼��ѡ���ǿ�
		{
			for(j=0;j<8;j=j+2)
			{
				suggest[j]=char(-65);
				suggest[j+1]=char(-43);
			}
		}
}
void Change(int g,int p)
{                                          //�任���λ��
	HANDLE hOut;
	COORD pos={0,0};
	pos.X=g;
    pos.Y=p;
    hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut,pos);
}
void Association()
{                                         //�������ѡ��
	int i,j=11;
	if(a=='1')                  //1���� 
	{
		for(i=0;i<8;i=i+2)
	  {
		if(i==6){
			Change(j,12);
			printf("%c%c",suggest[i],suggest[i+1]);
			j=j+16;
		}
		else{
			Change(j,12);
			printf("%c%c           ",suggest[i],suggest[i+1]);
			j=j+16;
		}
	  }
	  Change(75,12);
	  for(i=0;i<8;i++)printf("%c",cysuggest[i]);
	}
	if(a=='0')                    //0���� 
	{
		for(i=0;i<8;i=i+2)
	{
		if(i==6)
		{
			Change(j,12);
			printf("%c%c",suggest[i],suggest[i+1]);
		}
		else
		{
			Change(j,12);
			printf("%c%c               ",suggest[i],suggest[i+1]);
			j=j+21;
		}
	}
  }
}
void Record(char n1,char n2)
{
	xx[shu]=n1;
	xx[shu+1]=n2;
	shu=shu+2;
}
void Import_file()
{
	FILE*fp;
	fp=fopen("���������Ϣ.txt","w");
	fflush(stdin);
	fwrite(xx,2,shu/2,fp);
	fclose(fp);
}
int Set_end()
{
	int i=1;
	char ze;
	Change(10,21);
	printf("����1  �����ļ�\n");
	Change(10,22);
	printf("����2  �������˳�\n");
	Change(10,23);
	while(i)
	{
		ze=getch();
	    switch(ze)
	    {
		    case'1':system("���������Ϣ.txt");
		            return 0;
		    case'2':return 0;
		    default:Change(10,23);
			        printf("[%d]���¼�����Ϣ\n",i);
			        Change(10,24);
	    }
	    i++;
	}
}
void Input()
{                                  //���뺺��
	char nr[2]={0};
	int i=1,g=10,p=8,flag=0,gai=1;
	while(i)
	{
	    fflush(stdin);
	    if(i==42)                      //���������������
	    {
    		p++;
    		g=10;
    	}
	    if(i==83)
	    {
    		Change(70,14);
    		printf("�ѳ�������������ƣ���");
            break;
    	}
	    if(flag==0)Change(g,p);                  //�ж��Ƿ��˸�
		if(flag==1)
	    {
    		Change(g-2,p);
    		flag=0;
    		g=g-2;
    	}
		nr[0]=getchar();
		if(nr[0]=='n')                      //n�˳����� 
		{
			Change(10,20);
			printf("���˳�����\n");
			break;
		}
		nr[1]=getchar();
		if(nr[0]=='\n')continue;         //����������� 
	    if(nr[1]=='\n')
		{
            Change(g+1,p);
		    xx[shu]=nr[0];
		    g++;
		    shu++;
		    continue;
	    }
		Record(nr[0],nr[1]);
		if((nr[0]!='5')&&(nr[0]!='6'))
		{
			gai=1;
			Search_cy(cy,nr[0],nr[1],gai);
		}
		if(i==1)
		{
			Set_option(nr[0],nr[1]);
			Association();
		    g=g+2;
		}
		if(i>1)
        {		
			if(nr[0]=='t')
		    {
			    nr[1]='t';
				flag=1;
				Change(g-2,p);
			    printf("    ");
			    xx[shu-4]=xx[shu-3]=xx[shu-2]=xx[shu-1]=' ';
			    shu=shu-4;
			    i--;
			    continue;
		    }
			if((nr[0]=='1')||(nr[0]=='2')||(nr[0]=='3')||(nr[0]=='4')||(nr[0]=='5')||(nr[0]=='6'))
		   {                                                //����ѡ�����
			switch(nr[0])
			{
				case '1':
				         Change(g,p);
						 printf("%c%c",suggest[0],suggest[1]);
						 xx[shu-2]=suggest[0];
						 xx[shu-1]=suggest[1];
						 Set_option(suggest[0],suggest[1]);
						 Association();
				         break;
				case '2':
                         Change(g,p);
				         printf("%c%c",suggest[2],suggest[3]);
				         xx[shu-2]=suggest[2];
						 xx[shu-1]=suggest[3];
						 Set_option(suggest[2],suggest[3]);
						 Association();
						 break;
				case '3':
				         Change(g,p);
				         printf("%c%c",suggest[4],suggest[5]);
				         xx[shu-2]=suggest[4];
						 xx[shu-1]=suggest[5];
						 Set_option(suggest[4],suggest[5]);
						 Association();
						 break;
				case '4':
                         Change(g,p);
				         printf("%c%c",suggest[6],suggest[7]);
				         xx[shu-2]=suggest[6];
						 xx[shu-1]=suggest[7];
						 Set_option(suggest[6],suggest[7]);
						 Association();
						 break;
				case '5':if(a=='1'){
					         Change(g,p);
				             printf("%c%c%c%c%c%c",cysuggest[2],cysuggest[3],cysuggest[4],cysuggest[5],cysuggest[6],cysuggest[7]);
				             xx[shu-2]=cysuggest[2];
						     xx[shu-1]=cysuggest[3];
						     xx[shu]=cysuggest[4];
						     xx[shu+1]=cysuggest[5];
						     xx[shu+2]=cysuggest[6];
						     xx[shu+3]=cysuggest[7];
						     shu=shu+4;
						     g=g+4;
						     i=i+2; 
				   }
				   break;
  	            case '6':if(a=='1'){
            	  	     Change(g,p);
                         printf("  ");
                         Change(g,p);
                         g=g-2;
						 gai++;
						 Search_cy(cy,cysuggest[0],cysuggest[1],gai);
						 Association();
						 xx[shu-2]=xx[shu-1]='0';
						 shu=shu-2;
						 
            	  }
                  break;       
			}
		   }
		else{
				Set_option(nr[0],nr[1]);
			    Association(); 
			}
			g=g+2;
        }
	   i++;
	}
    //printf("%s",nr);
}
void Color()
{
	system("color f0");
}
void Set_interface()
{                                           //��������
	int i,j=1;
	Change(46,12);
	printf("��ӭ����������������ϵͳ");
	Change(90,25);
	printf("designed by huo yuanhao");
	Change(0,25);
	Change(46,14);
	printf("����汾(0/1):");
	while(j)
	{
		Change(61,14);
		a=getch();
		if(a=='0'||a=='1')break;
		else{
			Change(46,15);
			printf("[%d]���������������",j);
		}
		j++;
	}
	system("cls");
	Change(45,4);
	printf("������������"); 
	Change(8,14);
	printf("<1>��������������Ǻ��ֻ������ַ�������������");
	Change(8,15);
	if(a=='1')printf("<2>�˸�����t,�˳���������n������66�ɱ任�����Ƽ�");
	if(a=='0')printf("<2>�˸�����tt,�˳���������n");
	Change(8,16);
	printf("<3>ÿ��ֻ������һ�����֣�����Ҫ���س���"); 
	Change(8,17);
	printf("<4>����Ҫ���뵽�ĺ����������Ӧ������");
	Change(8,12);
	if(a=='1')
	{
		for(i=1;i<=5;i++)
	    {
		if(i==5)printf("%d%d*",i,i);
        else{
	             printf("%d%d.             ",i,i);
           }
	    } 
	}
	if(a=='0')
	{
		for(i=1;i<=4;i++)
	   {
		    printf("%d%d.                  ",i,i);
	   } 
	}
	for(i=6;i<96;i=i+2)
	{
		Change(i,6);
		printf("��");
		Change(i,26);
		printf("��");
	}
	for(i=7;i<26;i++)
	{
		Change(6,i);
		printf("��");
		Change(94,i);
		printf("��");
	}
	for(i=8;i<95;i=i+2)
	{
		Change(i,18);
		printf("��");
	}
	for(i=8;i<=93;i++)
	{
		Change(i,11);
		printf("*");
		Change(i,13);
		printf("*");
	}
}
void End()
{
	system("cls");
	Change(46,12);
	printf("********************\n");
	Change(50,13);
	printf("��ӭ�´�ʹ��\n");
	Change(46,14);
	printf("********************\n\n\n\n\n\n\n\n\n\n\n\n");
}
int main()
{
	Color();
	Initidiom(cy);
	Read_cy(); 
	Set_interface();
	Creatlist(name);
    Read_file();
    Input();
    Import_file();
    Set_end();
    End();
    return 0;       
}
