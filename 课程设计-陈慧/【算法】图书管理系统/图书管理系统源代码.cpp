#include<stdio.h>     
#include<string.h>    
#include<stdlib.h>   
#define N 1000   
#define M 4   
       
int amount=0;               //ȫ�ֱ����������������  

 /*************��Ľṹ��***********/      
typedef struct              
{   
    int num;				//��� 
    char name[20];		    //����
    char writer[20];        //������
    int left;               //ͼ���ִ���
    int storage;            //��ͼ������
           
}DataType;   
       
/*************B-���Ĵ洢�ṹ***********/      
typedef struct node         
{    
    struct node *parent;    //ָ�򸸽���ָ��
    int keynum;             //���ؼ�ֵ
    DataType key[M + 1];    //һ�����������ŵ���ĸ���
    struct node *ptr[M + 1];    //ָ���ӽ���ָ��
}node;   

node *root; //���ڵ�ָ�� 
       
/*************��������Ϣ���õ�����ʽ�洢��***********/
typedef struct { 
	char number[20];				//�����߱��
	char limtdata[20];				//�黹ʱ��
}Reader;
     
   

/*************���ҽ���Ĵ洢�ṹ��***********/      
typedef struct   
{    
    node *ptr;    //���ָ�룬ָ����ҽ���Ľ�� 
    int pos;      //����λ�ñ�ʾ
    int find;     //һ����ר�ñ�ţ��жϸ����Ƿ�¼�룬�����ж��Ƿ��ҵ�
}result; 
   					
 
DataType b[N];//��Ľṹ������   


/*************��������***********/      
void assist();   
result SearchBT(node *root, int key);   //�����������ڸ������в�����Ӧ���λ�� 
void Insert(node *root, int pos, node *child, DataType key);   // ֱ�Ӳ�����
void Split(node *p, int *key, int pos, node **child);   //���ѽ��
void output(node *root, int floor);   //�԰�������ʽ����� 
void assist(node *root);   //��ѯ����
void borrow(node *root);   //���麯��
void dele(node *root);   //�������  
void welcome();   //��ӭ����������ص�ѡ�����
void input();   //�ɱ����
       
result SearchBT(node *root,int key)    //������   
{    
    if (root == NULL)   
    {    
        printf("SearchBT Error...\n"); //��������   
        exit(0);    
    }    
           
    int pos = 0, find = 0;    
    node *just = NULL;           
    while (root && !find)              //���û���ҵ�����ѭ������   
    {    
        pos = 0;    
        while (pos<root->keynum && root->key[pos+1].num<=key)    
        {    
            pos++;    
        }    
        if (pos && root->key[pos].num == key)   
        {    
            find = 1;    
        }    
        else {    
            just = root;    
            root = root->ptr[pos];    
            }    
    }    
           
        if (find)                          //����ҵ��ˣ���������   
        {    
            result val = { root, pos, 1 };    
            return val;    
        }           
        else    
        {    
            result val = { just, pos, 0 };    
            return val;    
        }    
}    

      
void Insert(node *root, int pos, node *child, DataType key) //ֱ�Ӳ�����   
{    
    int i;    
           
    for (i=root->keynum; i>=pos+1; i--) {   //һ�����һ�����������
        root->key[i + 1] = root->key[i];    
        root->ptr[i + 1] = root->ptr[i];    
    }    
    root->key[pos + 1] = key;               //�ڿճ�����λ�ò�����
    root->ptr[pos + 1] = child;    
    root->keynum++;    
}    
       
       
void Split(node *p, DataType *key, int pos, node **child) //���ѽ��        
{    
    DataType tempkey[M + 2];    
    node *temptr[M + 2];    
    int i, j;    
    i = j = 0;    
    for (i=0; i<=M+1; i++) {    
        if (i == pos + 1) {    
            tempkey[i] = *key;    
            temptr[i] = *child;    
        }    
        else {    
            tempkey[i] = p->key[j];    
            temptr[i] = p->ptr[j++];    
        }    
    }                                 //�����ѽ��֮ǰ�Ľ�㰲�ú�
                   
    *child = (node *)malloc(sizeof(node));    //Ϊ�µ��ӽ�����ռ�

    (*child)->parent = p->parent;    
    int mid = (M + 1) / 2 + 1;    
    p->keynum = mid - 1;    
    (*child)->keynum = M - (mid - 1);    //�������֧����������

    for (i=0; i<=M+1; i++) {    
        if (i < mid) {    
            p->key[i] = tempkey[i];    
            p->ptr[i] = temptr[i];    
        }    
        else if (i == mid) {    
            (*child)->ptr[0] = temptr[i];    
            *key = tempkey[i];    
        }    
        else {    
            (*child)->key[i - mid] = tempkey[i];    
            (*child)->ptr[i - mid] = temptr[i];    
        }    
    }    
}    
       
       
//�������ʱ����ֱ�Ӳ��뵽Ҷ��㣬   
//���ж��Ƿ�Ҫ���ѽ��   
void InsertBT(node **T, DataType key, node *p, int pos)   
{    
    node *child = NULL;                      //�����µĽ��ָ�룬Ϊ����Ľ�������׼��
    node *just;    
    while (p)    
    {    
        if (p->keynum < M)                   //���p�е�������ࡴM
        {    
            Insert(p, pos, child, key);      //ֱ�Ӳ�����
            return;    
        }   
        else {                               //�����ý�����������������Ŀ
            Split(p, &key, pos, &child);     //�����µ�key, child...����λ��pos���½����Ϣָ��key������ָ��p�У��ٽ��з��ѣ���childָ�����ָ��ָ����Ѻ����һ�����
            just = p;    
            p = p->parent;                   //pָ�����ĸ����
            if (p)    
            {    
                pos = 0;    
                while (pos<p->keynum && p->key[pos+1].num<=key.num)    //����һ������֧���޶����ã�pos��Ӧ��1
                {    
                    pos++;    
                }    
            }    
        }    
    }    
    node *root = (node *)malloc(sizeof(node));    
    root->keynum = 1;    
    root->key[1] = key;    
    root->ptr[0] = just;    
    root->ptr[1] = child;    
    root->parent = NULL;    
           
    (*T)->parent = child->parent = root;    
    *T = root;    
}    
       
       
void SearchInsert2(node **root, DataType key)    
{    
    if (*root == NULL)    
    {    
        *root = (node *)malloc(sizeof(node));    
        (*root)->key[1] = key;    
        (*root)->keynum = 1;    
        (*root)->ptr[0] = (*root)->ptr[1] = NULL;    
        (*root)->parent = NULL;    
        return;    
    }    
           
    result val=SearchBT(*root,key.num);    
    InsertBT(root, key, val.ptr, val.pos);    
           
}    
       
       
void SearchInsert(node **root, DataType key)    //�������Ҳ����㣬���ú����ҵ��������λ��   key-����һ�����������Ϣ
{    
    if (*root == NULL)                          //rootָ���ʱ��ֱ�������Ϣ
    {    
        *root = (node *)malloc(sizeof(node));    
        (*root)->key[1] = key;                  //һ�������Ϣ��������
        (*root)->keynum = 1;                    //��Ӧ�����Ŀ��1
        (*root)->ptr[0] = (*root)->ptr[1] = NULL;    //�ӽ��ſ� 
        (*root)->parent = NULL;                      //�����ſ�
        return;    
    }    
            
    result val=SearchBT(*root,key.num);         //��rootָ��ǿ�ʱ�����������Ƿ�����ָͬ��
    if (val.find)    
    {    
        printf("already exist...\n");           //����ָͬ�룬������Ϣ��ʾ
    }    
    else    
    {    
        InsertBT(root, key, val.ptr, val.pos);   //���������
    }    
}    
       
       


void output(node *root, int floor)               //�԰�������ʽ�����   
{     
    int t=1;
    if (root == NULL) return;          
    output(root->ptr[0], floor + 1);    
    for (int i=1; i<=root->keynum; i++)    
    {    
        for (int j=0; j<5; j++)    
        {    
            if (j == floor)    
            {    
                printf("\t[%d]%3d", t++, root->key[i].num);    
            }    
            else if (j < floor)   
            {    
                printf("      ");    
            }    
            else    
            {    
                printf("------");    
            }    
        }    
        printf("\t%s  %s  %d\n", root->key[i].name,root->key[i].writer,root->key[i].left);    
        output(root->ptr[i], floor + 1);    
    }    
}   
       
       
void assist(node *root)//��ѯ����   
{   
    int num,i,m;  
    DataType b2;
	char  mingzi[20];
    result d;   
    char a[3];   
    do
	{
	    printf("================================================================================\n");    
        puts("\t\t*****************��ѯ*********************\n\n");   
        puts("\t\t\t\t1.��Ų�ѯ\n");   
        puts("\t\t\t\t2.������ѯ\n");   
        puts("\t\t\t\t3.���߲�ѯ\n");   
        puts("================================================================================\n");   
        printf("����1-3��ѡ���Իس���������\n\n");   
		scanf("%d",&m);
		switch(m)   
        {   
        case 1: printf("��������Ҫ��ѯ�������ţ�\n\n");   
                scanf("%d",&num);   
                d=SearchBT(root,num);   
                if(d.find&&d.ptr->key[d.pos].storage!=0)   
                {   
                    printf("���\t����\t����\tʣ����\t�ܿ��\n");   
                    printf("%d\t%s\t%s\t%d\t%d\n\n",d.ptr->key[d.pos].num,d.ptr->key[d.pos].name,d.ptr->key[d.pos].writer,d.ptr->key[d.pos].left,d.ptr->key[d.pos].storage);         
                }   
                else    
                printf("��Ҫ�ҵ��鲻����!\n\n");   
                printf("�㻹Ҫ����������?ѡ��yes����no.\n");   
                scanf("%s",a);  
                break;   
                
        case 2:printf("��������Ҫ��ѯ�����������\n\n");   
                scanf("%s",&b2.name);   
                for(i=0;i<amount;i++)
                {
                	if(strcmp(b2.name,b[i].name)==0)
                	num=b[i].num;
				}
                d=SearchBT(root,num);   
                if(d.find&&d.ptr->key[d.pos].storage!=0)   
                {   
                    printf("���\t����\t����\tʣ����\t�ܿ��\n");   
                    printf("%d\t%s\t%s\t%d\t%d\n\n",d.ptr->key[d.pos].num,d.ptr->key[d.pos].name,d.ptr->key[d.pos].writer,d.ptr->key[d.pos].left,d.ptr->key[d.pos].storage);         
                }   
                else    
                printf("��Ҫ�ҵ��鲻����!\n\n");   
                printf("�㻹Ҫ����������?ѡ��yes����no.\n");   
                scanf("%s",a);  
                break;    
                
		case 3:printf("��������Ҫ��ѯ����������\n\n");   
                scanf("%s",&b2.writer);  
			    printf("���\t����\t����\tʣ����\t�ܿ��\n");
                for(i=0;i<amount;i++)
                {
                	if(strcmp(b2.writer,b[i].writer)==0)
                	{
					    num=b[i].num;
                        d=SearchBT(root,num);   
                        if(d.find&&d.ptr->key[d.pos].storage!=0)   
                        {   
                            printf("%d\t%s\t%s\t%d\t%d\n\n",d.ptr->key[d.pos].num,d.ptr->key[d.pos].name,d.ptr->key[d.pos].writer,d.ptr->key[d.pos].left,d.ptr->key[d.pos].storage);         
                        } 
					} 
				} 
                if(i>amount)    
                printf("��Ҫ�ҵ�������ʱû���鴢���ڸ�ϵͳ!\n\n");   
                
                printf("�㻹Ҫ����������?ѡ��yes����no.\n");   
                scanf("%s",a);  
                break;   
        
        }         
    } while(strcmp(a,"yes")==0);   
    welcome();   
}   
       
       
  void print(node *root)   
{   
           
    root=NULL;   
           
    for(int x=0;x<amount;x++)   
    {   
               
        SearchInsert(&root,b[x]);   
    }   
	//SearchInsert(&root, b[i].num); 
	printf("\t���� ���------------------------����   ����  ʣ���� \n");    
    output(root, 0);    
	getchar();    
    printf("\n");    
}   
       
void borrow(node *root)//���麯��   
{   
    int num,count,i,id,date;   
    int tag;
	Reader a;
    result d;   
    if(root==NULL)   
    {   
        printf("�����һ���鶼û�У������ܽ���!\n");   
        welcome();   
    }  
    printf("�������Ȿ������:");   
    scanf("%d",&num);   
    d=SearchBT(root,num);   
    if(d.find==0||d.ptr->key[d.pos].storage==0)   
    {   
        printf("û����Ҫ�����!\n");   
        welcome();   
    }   
    else   
    {   
        printf("��� \t���� \t���� \tʣ���� \t�ܿ��\n");   
        printf("%5d \t%5s \t%5s \t%5d \t%5d\n\n",d.ptr->key[d.pos].num,d.ptr->key[d.pos].name,d.ptr->key[d.pos].writer,d.ptr->key[d.pos].left,d.ptr->key[d.pos].storage);   
    }      
    if(d.ptr->key[d.pos].left==0)   
        printf("�����Ѿ�����!\n");   
           
    else    
    {   
        printf("��������Ҫ���Ȿ�������(С�����%d)\n",d.ptr->key[d.pos].left);   
        scanf("%d",&count);   
        while(count>d.ptr->key[d.pos].left)    
        {   
            printf("������������������\n");   
            scanf("%d",&count);   
        }   
        printf("����ɹ�\n");   
        d.ptr->key[d.pos].left=d.ptr->key[d.pos].left-count;   
        printf("����������ͼ��֤�ţ�");
		scanf("%s",&a.number);
		printf("���������Ļ������ڣ�");
		scanf("%s",&a.limtdata);
    }   
    welcome();    
}   
       
void returnback()//���麯��   
{   
    int num,count,i;   
    int tag;   
    result d;   
    printf("�������Ȿ������:");   
    scanf("%d",&num);   
    d=SearchBT(root,num);   
    if(d.find==0||d.ptr->key[d.pos].storage==0)   
    {   
        printf("�Ȿ�鲻����ͼ���!\n");   
        welcome();   
    }   
    else   
    {   
        printf("���     ����     ����      ʣ����        �ܿ��\n");   
        printf("%d%7s%7s%8d%12d\n\n",d.ptr->key[d.pos].num,d.ptr->key[d.pos].name,d.ptr->key[d.pos].writer,d.ptr->key[d.pos].left,d.ptr->key[d.pos].storage);   
    }      
           
    printf("��������Ҫ���������:\n");   
    scanf("%d",&count);   
    while(count>d.ptr->key[d.pos].storage-d.ptr->key[d.pos].left)    
    {   
        printf("������������������\n");   
        scanf("%d",&count);   
    }   
    printf("����ɹ�\n");   
    d.ptr->key[d.pos].left=d.ptr->key[d.pos].left+count;   
    welcome();    
}   
       
       
void welcome()//��ӭ����������ص�ѡ�����   
{   
    int  j;   
	    printf("=================================ͼ�����ϵͳ===================================\n");   
    do   
    {   printf("=================================B16070404�»�===================================\n"); 
        puts("\t\t*****************MENU*********************\n\n");   
        puts("\t\t\t\t1.�ɱ����\n");   
        puts("\t\t\t\t2.�������\n");   
        puts("\t\t\t\t3.����\n");   
        puts("\t\t\t\t4.�黹\n");   
        puts("\t\t\t\t5.��ʾ\n");   
        puts("\t\t\t\t6.��ѯ\n");   
        puts("\t\t\t\t0.�˳�\n");   
        puts("================================================================================\n");   
        printf("����0-6��ѡ���Իس���������\n\n");   
        scanf("%d",&j);   
        switch(j)   
        {   
        case 1: input();   
            break;   
        case 2:dele(root);   
            break;   
        case 3:borrow(root);   
            break;   
        case 4:returnback();   
            break;   
        case 5:print(root);    
            break;   
        case 6:assist(root);     
        }   
    }while(j!=0);     //�жϽ���   
    printf("ллʹ�ã��ټ���\n"); 
	exit(0);  
}//����������   
       
void input()   //�ɱ����
{   
    int y;   
           
    printf("����������ͼ����Ϣ:\n");        //��ӡ��ʾ��Ϣ   
    printf("--------------------------------------------------------------------------\n");   
    do{   
        for(int i=amount;i<N;i++)   
           {   
            printf("������ͼ����:");     
            scanf("%d",&b[i].num);            //b[N]��Ľṹ������
            printf("������ͼ����:");   
            scanf("%s",b[i].name);   
            printf("����������:");   
            scanf("%s",b[i].writer);   
            printf("�������ܿ����:");   
            scanf("%d",&b[i].storage);   
            b[i].left=b[i].storage;           //Ŀǰʣ����=����
            amount++;				          //��������+1 
            SearchInsert(&root,b[i]);         //�������Ҳ����㣬���ú����ҵ��������λ�� 
            printf("��%d����Ϣ�Ѿ������Ƿ����?���������ּ��������� 0����\n",amount);   
            scanf("%d",&y);   
            break;   
        }   
    }while(y!=0);   
}   
       
void dele(node *root)//ɾ������   
{   
    result d;   
    int num,n,tag;   
    char t[3];   
    do{   
        printf("ȷ��Ҫ���������?��\n\n");//��ӡɾ����ʽ�˵�   
        printf("1.ȷ��\n\n");   
        printf("0.����\n\n");   
        printf("��ѡ��\n");   
        scanf("%d",&n);   
        if(n==0)   
            welcome();       
        else   
        {   
            printf("��������Ҫɾ����������");   
            scanf("%d",&num);   
            d=SearchBT(root,num);   
        }   
        if(!d.find)printf("��Ҫ�ҵ��鲻����!");   
        else   
        {   
            printf("���     ����     ����      ʣ����        �ܿ��\n");   
            printf("%d%7s%7s%8d%12d\n\n",d.ptr->key[d.pos].num,d.ptr->key[d.pos].name,d.ptr->key[d.pos].writer,d.ptr->key[d.pos].left,d.ptr->key[d.pos].storage);   
            printf("ȷ��Ҫɾ����?������yes����no.\n");   
            scanf("%s",t);   
            if(!strcmp(t,"yes"))   
            {   
                d.ptr->key[d.pos].storage=0;   
                for(int i=0;i<amount;i++)   
                {   
                    if(b[i].num==num)   
                        tag=i;   
				}   
                b[tag]=b[amount-1];   
                amount--;   
                for(int x=0;x<amount;x++)   
                {
				    SearchInsert2(&root,b[x]);   
                }            
            }   
        }   
        printf("�Ƿ����ɾ��\n");        
        printf("�����yes��no�Իس�������\n");   
        scanf("%s",t);       //��ȡ�Ƿ������Ϣ   
        if(!strcmp(t,"yes")) //�ж��Ƿ����ɾ��       
            printf("�밴������Իس������������ϲ�˵�:\n");   
        break;   
    }while(!strcmp(t,"yes"));   
}   
       
       
       
int main()   
{      
   
    node *root=NULL;   
    welcome();   
}   
       
       
       
       
       


