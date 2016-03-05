#include <stdio.h>
#include <stdlib.h>
/*
����������(�������������������١�������ȡ������Ŀ���������������������������������������������)
ʱ�䣺2015-1-2 22:21
˵��������������(�������������������١�������ȡ������Ŀ���������������������������������������������) 
*/ 


/*����һ��ö����������ʾָ����״̬��Link=0��ʾָ�����Һ��ӣ�Thread=1��ʾָ��ǰ�����ߺ��*/
typedef enum{Link=0,Thread=1}PointerTag;

typedef struct BiTNode
{
	char data;
	struct BiTNode *lchild,*rchild;
	PointerTag LTag,RTag;//�����־λ 
}BiTNode,*BiTree;

/*
�������ƣ�CreateBinaryTree(BiTree *T)  
˵����������������������'#'��Ϊ��ָ���־�������������˳������������и������ 
*/
void CreateBinaryTree(BiTree *T)
{
	char ch;
	scanf("%c",&ch);
	if(ch=='#')
		*T=NULL;
	else
	{
		*T=(BiTree)malloc(sizeof(BiTNode));
		
		if(!(*T))//�ݴ��жϣ������ڴ�ռ�ʧ��ʱ���� 
			return;
			 
		(*T)->data=ch;
		 
		CreateBinaryTree(&((*T)->lchild));		
		if((*T)->lchild)//����������ʱ����־λ����ΪLink 
		//if(((*T)->lchild)!=NULL)
			(*T)->LTag=Link;
			
		CreateBinaryTree(&((*T)->rchild));//�������Һ���ʱ����־λ����ΪLink
		if((*T)->rchild)
			(*T)->RTag=Link;			
	}	
}

/*�������������*/
void PreOrderTraverse(BiTree T)
{
	if(!T)
		return;
	else
	{
		printf("%c",T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);	
	}
}

/*�������������*/
void InOrderTraverse(BiTree T)
{
	if(T==NULL)
		return;
	else
	{
		InOrderTraverse(T->lchild);
		printf("%c",T->data);
		InOrderTraverse(T->rchild);		
	}
}

/*�������������*/
void PostOrderTraverse(BiTree T)
{
	if(!T)
		return;
	else
	{		
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c",T->data);	
	}
}
/*������������*/
int BinaryDepth(BiTree T)
{
	int ldepth,rdepth;
	
	if(!T)
		return 0;
	else
	{
		ldepth=BinaryDepth(T->lchild);
		rdepth=BinaryDepth(T->rchild);
		return (ldepth>rdepth?ldepth+1:rdepth+1);
	}
}

/*����������*/
int NodeCount(BiTree T)
{
	if(!T)
		return 0;
	else 
		return (NodeCount(T->lchild)+NodeCount(T->rchild)+1);
} 
 /*����һ��������*/
 void DestoryBinaryTree(BiTree *T)
{
	if(*T)
	{
		if((*T)->lchild)
			DestoryBinaryTree(&((*T)->lchild));
		if((*T)->rchild)
			DestoryBinaryTree(&((*T)->rchild));	
		free(*T);
		*T=NULL;		
	}
} 

/*********����������������*********/

BiTree pre; /* ȫ�ֱ���,ʼ��ָ��ոշ��ʹ��Ľ�� */
/*����������*/
void InThreading(BiTree T)
{
	if(T)
	{
		InThreading(T->lchild);
		/*��û������ʱǰ������*/
		if(!T->lchild)
		{
			T->LTag=Thread;
			T->lchild=pre;	
		}
		/*��û���Һ���ʱ�������*/
		if(!pre->rchild)
		{
			pre->RTag=Thread;
			pre->rchild=T;
		}
		
		pre=T;/* ����preָ��ǰ�� */
		InThreading(T->rchild);
	}
}
/*�������������T����������������headΪͷָ��
��������������ͷ���lchild����ָ��������ĸ���㣬
rchild�Һ���ָ���������ʱ���ʵ����һ����㣻
��������������������е�һ������lchildָ������һ�����ӵ�rchildָ��ͷ��� 
*/
void InOrderThreading(BiTree *head,BiTree T)
{
	*head=(BiTree)malloc(sizeof(BiTNode));
	if(!*head)/*�������ʧ��*/
		return;
	/*��ʼ��ͷ���*/ 
	(*head)->LTag=Link;
	(*head)->RTag=Thread;
	(*head)->rchild=*head;/*ͷָ���ָ*/
	
	if(!T)/*�Դ����2���������кϷ��Լ�⣬����ȡ��Ӧ����,��TΪ��ʱ*/
	{
		(*head)->lchild=(*head);
	}
	else
	{
		(*head)->lchild=T;//��TΪ�ǿ�ʱͷ���ָ��������ĸ����T
		pre=(*head);
		
		InThreading(T);
		
		/*�����һ�����������*/
		pre->RTag=Thread;
		pre->rchild=*head;
		(*head)->rchild=pre;/*ͷ���ָ������������һ�����*/	
	}	 
}

/*�������һ�ö���������T(TΪͷ���)*/
void InOrderTraverseThreadTree(BiTree T)
{
	BiTree p;
	p=T->lchild;
	
	while(p!=T)/*����δ�������������ö��������������������ʱp=T*/
	{
		while(p->LTag==Link)
		{
			p=p->lchild;	
		}
		
		printf("%c ",p->data);
		
		while((p->rchild!=T)&&(p->RTag==Thread))
		{
			p=p->rchild;
			printf("%c ",p->data);	
		}
		p=p->rchild;		
	}
	

}

int main(int argc, char *argv[]) 
{
	
	BiTree T,H;
	printf("�봴��һ�ö�����(��:'ABDH##I##EJ###CF##G##')\n");
	CreateBinaryTree(&T);
	
	printf("\n�����������Ϊ:%d,�����ĿΪ:%d\n",BinaryDepth(T),NodeCount(T));
	
	printf("\n��������Ľ����:\n");
	PreOrderTraverse(T);
	
	printf("\n��������Ľ����:\n");
	InOrderTraverse(T);
	
	printf("\n��������Ľ����:\n");
	PostOrderTraverse(T);
	
	printf("\n�Զ�������������������\n");
	InOrderThreading(&H,T);
	printf("\n������������������Ľ����:\n");
	InOrderTraverseThreadTree(H);
	
	printf("\n�ݻ�һ�ö�����\n");
	DestoryBinaryTree(&T);
	printf("\n�����������Ϊ:%d,�����ĿΪ:%d\n",BinaryDepth(T),NodeCount(T));
	return 0;
}
