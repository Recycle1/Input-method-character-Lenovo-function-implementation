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
	mytype a;                   //存储权值
	char b[2];                  //汉字内容
}Node;
typedef struct sqlist{
	Node *elem;
	int length;
	int listsize;
}sqlist;
typedef struct Node1{
	sqlist address;              //将每个汉字的权值线性表存储在链表中 
	char d[2];
	int memory;                   //记录该线性表的数据量 
	struct Node1 *next1;
}Node1,*linklist;
typedef struct cylist{ 
        char cy[2];
        char houzhui[6*N2];
        int cysum;
        struct cylist *next;
}*idm;
char cysuggest[8]={0};            //成语选项 
idm cy;
linklist name;                   //总链表
linklist next1;
sqlist next;
sqlist L1;
char xx[166];                     //存储输入内容
int shu=0;
char suggest[8];                  //存储推荐选项
void Initidiom(idm &cy)                 
{                                   //初始化成语链表 
	cy=(idm)malloc(sizeof(cylist));
	cy->next=NULL;
}
void Creatidiom(idm &cy,char n1,char n2)
{                                    //增加一个新字的成语，创建新的成语节点 
	idm cy1;
	cy1=(idm)malloc(sizeof(cylist));
	cy1->cysum=1;
	cy1->cy[0]=n1;
	cy1->cy[1]=n2;
	cy1->next=cy->next;
	cy->next=cy1;
}
void Addidiom(idm &cy,char n1,char n2,char n3,char n4,char n5,char n6,char n7,char n8)
{                                       //增加成语 
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
{                                        //读取成语文件 
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
	{                                  //每8个字节（ 四个字）进行一次增加成语 
		Addidiom(cy,cynr[i],cynr[i+1],cynr[i+2],cynr[i+3],cynr[i+4],cynr[i+5],cynr[i+6],cynr[i+7]);
	}
}
void Search_cy(idm cy,char n1,char n2,int k)
{                                       //查找成语内容 
	int flag=0;
	idm c=cy->next;
	while(c)
	{
		if((c->cy[0]==n1)&&(c->cy[1]=n2))
		{
			cysuggest[0]=n1;
			cysuggest[1]=n2;
			flag=1;                             //循环变换选项 
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
	if(flag==0){                           //查找不到时推荐选项输出空 
		for(int i=0;i<8;i=i+2)
		{
			cysuggest[i]=char(-65);
		    cysuggest[i+1]=char(-43);
		}
	}
}
void Creatlist(linklist &L)
{                                              //建立新链表
	L=(linklist)malloc(sizeof(Node1));
	L->d[0]='1';
	L->d[1]='2';
	L->next1=NULL;
}
void Newlist(linklist &L,char n1,char n2,sqlist &a)
{                                                // 将线性表存储在链表中
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
{                                                     //创建线性表
	L.elem = (Node *)malloc(N*sizeof(Node));
	L.elem[0].b[0]=n1;
	L.elem[0].b[1]=n2;
	L.elem[0].a=1;
	L.length=1;
	L.listsize=N;
	Newlist(name,n1,n2,L);
}
void Addelem(sqlist &L,char n1,char n2,linklist &c)
{                                                        //增加新的汉字元素
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
{                                           //增加权值
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
{                                                   //返回需要的线性表
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
{                                            //读取文件得到权值
	FILE* fp = NULL;
	fp = fopen("b.txt", "r");
	if (fp == NULL)
	{
		perror("my_fread fopen");
		return;
	}
	char *hanzi;                          //汉字由两字节构成，按块读
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
		if(hanzi[i]=='\n')             //去掉回车
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
			Addweight(next,hanzi[i+2],hanzi[i+3],next1);          //增加下一个汉字相比前一个汉字的权值
		}
	}
	//printf("ret = %d\n", ret)；
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
{                                    //权值排序
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
{                                       //创建选择
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
	if(flag==0)                                   //没有记录过选项是空
		{
			for(j=0;j<8;j=j+2)
			{
				suggest[j]=char(-65);
				suggest[j+1]=char(-43);
			}
		}
}
void Change(int g,int p)
{                                          //变换光标位置
	HANDLE hOut;
	COORD pos={0,0};
	pos.X=g;
    pos.Y=p;
    hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut,pos);
}
void Association()
{                                         //输出联想选项
	int i,j=11;
	if(a=='1')                  //1界面 
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
	if(a=='0')                    //0界面 
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
	fp=fopen("已输入的信息.txt","w");
	fflush(stdin);
	fwrite(xx,2,shu/2,fp);
	fclose(fp);
}
int Set_end()
{
	int i=1;
	char ze;
	Change(10,21);
	printf("输入1  导出文件\n");
	Change(10,22);
	printf("输入2  结束并退出\n");
	Change(10,23);
	while(i)
	{
		ze=getch();
	    switch(ze)
	    {
		    case'1':system("已输入的信息.txt");
		            return 0;
		    case'2':return 0;
		    default:Change(10,23);
			        printf("[%d]重新键入信息\n",i);
			        Change(10,24);
	    }
	    i++;
	}
}
void Input()
{                                  //输入汉字
	char nr[2]={0};
	int i=1,g=10,p=8,flag=0,gai=1;
	while(i)
	{
	    fflush(stdin);
	    if(i==42)                      //设置最大输入数量
	    {
    		p++;
    		g=10;
    	}
	    if(i==83)
	    {
    		Change(70,14);
    		printf("已超过输入最大限制！！");
            break;
    	}
	    if(flag==0)Change(g,p);                  //判断是否退格
		if(flag==1)
	    {
    		Change(g-2,p);
    		flag=0;
    		g=g-2;
    	}
		nr[0]=getchar();
		if(nr[0]=='n')                      //n退出程序 
		{
			Change(10,20);
			printf("已退出程序\n");
			break;
		}
		nr[1]=getchar();
		if(nr[0]=='\n')continue;         //错误输入调整 
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
		   {                                                //联想选项输出
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
{                                           //美化界面
	int i,j=1;
	Change(46,12);
	printf("欢迎来到汉字输入联想系统");
	Change(90,25);
	printf("designed by huo yuanhao");
	Change(0,25);
	Change(46,14);
	printf("输入版本(0/1):");
	while(j)
	{
		Change(61,14);
		a=getch();
		if(a=='0'||a=='1')break;
		else{
			Change(46,15);
			printf("[%d]输入错误，重新输入",j);
		}
		j++;
	}
	system("cls");
	Change(45,4);
	printf("汉字输入联想"); 
	Change(8,14);
	printf("<1>建议输入的数据是汉字或中文字符，否则无联想");
	Change(8,15);
	if(a=='1')printf("<2>退格输入t,退出程序输入n，输入66可变换成语推荐");
	if(a=='0')printf("<2>退格输入tt,退出程序输入n");
	Change(8,16);
	printf("<3>每次只可输入一个汉字，并需要按回车键"); 
	Change(8,17);
	printf("<4>如需要联想到的汉字则输入对应的数字");
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
		printf("■");
		Change(i,26);
		printf("■");
	}
	for(i=7;i<26;i++)
	{
		Change(6,i);
		printf("■");
		Change(94,i);
		printf("■");
	}
	for(i=8;i<95;i=i+2)
	{
		Change(i,18);
		printf("■");
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
	printf("欢迎下次使用\n");
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
