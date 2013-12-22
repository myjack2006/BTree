#include <stdio.h>
#include <malloc.h>

#define INVALID -1
#define M 4

/*=========================== data struct =====================*/

typedef char ElementType;
typedef struct Node{
ElementType data;
struct Node *LChild; /* 左子树 */
struct Node *RChild; /* 右子树*/
} TreeNode;
/*=============================== function prounce ===============*/
typedef struct node{
	bool isLeaf;
	int flagLR;//0 is left; 1 is right;
	int data[3]; 
	struct node* child[4];
	struct node* parent;
};

node* root;

node* getSuitLeaf(node* p_root, int a)
{
	if(p_root->isLeaf) return p_root;
    if(a < p_root->data[0]){
		return getSuitLeaf(p_root->child[0], a);
	}else if( p_root->data[0]<= a && (p_root->data[1] == NULL || a < p_root->data[1]) ){
		return getSuitLeaf(p_root->child[1], a);
	}else if( p_root->data[1]<= a &&  (p_root->data[2] == NULL || a < p_root->data[2]) ){
		return getSuitLeaf(p_root->child[2], a);
	}else if( p_root->data[2]<= a ){
		return getSuitLeaf(p_root->child[3], a);
	}else{
		//do nothing.
	}
}
/*
 * node* p_node: parent node.
 * node* c_node: child node.
 */
node* insertNode(node* p_node, node* c_node){
	int a = c_node->data[0];
	c_node->parent = p_node;
	if(a < p_node->data[0]){
		node* tmpA = p_node->child[0];
		node* tmpB = p_node->child[1];
		node* tmpC = p_node->child[2];
		p_node->child[0] = c_node;
		p_node->child[1] = tmpA;
		p_node->child[2] = tmpB;
		p_node->child[3] = tmpC;
	}else if( p_node->data[0]<= a && (p_node->data[1] == NULL || a < p_node->data[1]) ){
		node* tmpB = p_node->child[1];
		node* tmpC = p_node->child[2];
		p_node->child[1] = c_node;
		p_node->child[2] = tmpB;
		p_node->child[3] = tmpC;
	}else if( p_node->data[1]<= a &&  (p_node->data[2] == NULL || a < p_node->data[2]) ){
		node* tmpC = p_node->child[2];
		p_node->child[2] = c_node;
		p_node->child[3] = tmpC;
	}else if( p_node->data[2]<= a ){
		p_node->child[3] = c_node;
	}else{
		//do nothing.
	}
	return p_node;
}
void insetInt(int a[],int len, int b){
	int i=0;
	for( ;i<len;i++){
		if(b < a[i] || a[i] == INVALID){
			break;
		}
	}
	int tmp = a[i];
	int k;
    for(k = len; k>i; k--){
		a[k] = a[k-1];
	}
	a[i] = b;
}
/*
 * node* p_node:将被拆分的节点.
 * int a:待插入的整数.
 */
int splitNode(node* p_node, int a){
	if(p_node->data[2] == INVALID){//还有空位.
		insetInt(p_node->data, M-1, a);
		return 0;
	}else{
		node* newNode = (node*)malloc(sizeof(node));
		newNode->isLeaf = p_node->isLeaf;
		newNode->parent = p_node->parent;
		newNode->data[0] = p_node->data[2];
		newNode->data[1] = INVALID;
		newNode->data[2] = INVALID;

		int tmp = p_node->data[1];
		p_node->data[1] = INVALID;
		p_node->data[2] = INVALID;
	    
		if(p_node->parent == NULL){//如果是根节点.
			node* newRoot = root = (node*)malloc(sizeof(node));
			newRoot->parent = NULL;
			newRoot->data[0] = tmp;
			newRoot->data[1] = INVALID;
			newRoot->data[2] = INVALID;
			newRoot->child[0] = p_node;
			newRoot->child[1] = newNode;

			p_node->parent= newRoot;
			newNode->parent= newRoot;
		}else{
		    splitNode(p_node->parent, tmp);
			insertNode(p_node->parent, newNode);
		}
		return 1;
	}
}

void test(){
	root = (node*)malloc(sizeof(node));
	root->isLeaf = true;
	root->parent = NULL;
	root->data[0] = 100;
	root->data[1] = 200;
	root->data[2] = 300;
	node* suitNode = getSuitLeaf(root, 34);
	splitNode(suitNode, 34);
	suitNode = getSuitLeaf(root, 45);
	splitNode(suitNode, 45);
	suitNode = getSuitLeaf(root, 54);
	splitNode(suitNode, 54);
	suitNode = getSuitLeaf(root, 9);
	splitNode(suitNode, 9);
}
int getMaxValue(node* p_node)
{
	for(int i = 0; i< M -1; i++){
		if(p_node->data[i] == INVALID){
			return p_node->data[i];
	    }
	}
}
//
//node* getSuitablePossition(node* root, int a){
//	node* point = root;
//	if(point->LChild == NULL && point->RChild == NULL){
//		return point;
//	}
//	if(a<point->dataA){
//		point = point->LChild;
//	}else{
//		point = point->RChild;
//	}
//	return getSuitablePossition(point, a);
//};
//
//int addNode(node* p_node, int a){
//	node *point = p_node;
//	if(a < p_node->dataA && p_node->dataB == INVALID){//[4,]  3
//		int tmp = p_node->dataA;
//		p_node->dataA = a;
//		p_node->dataB = tmp;
//	}else if(a >= p_node->dataA &&  p_node->dataB == INVALID ){//[4,]  4,5
//		p_node->dataB = a;
//	}else if(p_node->dataA != INVALID &&  p_node->dataB != INVALID){//a>=p_node->dataB       //[4,6]   8
//		int minInt,middleInt,maxInt;
//		if( a < p_node->dataA ){
//			minInt = a;
//			middleInt = p_node->dataA;
//			maxInt = p_node->dataB;
//		}else if( p_node->dataA <= a && a < p_node->dataB){
//			minInt = p_node->dataA;
//			middleInt = a;
//			maxInt = p_node->dataB;
//		}else{
//			minInt = p_node->dataA;
//			middleInt = p_node->dataB;
//			maxInt = a;
//		}
//		node *left = (node*)malloc(sizeof(node));
//		node *right = (node*)malloc(sizeof(node));
//		left->flagLR = 0;
//		left->dataA = minInt;
//		left->dataB = INVALID;
//		left->LChild = p_node->LChild;
//		left->RChild = NULL;
//		left->Parent = p_node->Parent;
//		right->flagLR = 1;
//		right->dataA = maxInt;
//		right->dataB = INVALID;
//		right->LChild = NULL;
//		right->RChild = p_node->RChild;
//		right->Parent = p_node->Parent;
//		if(p_node->Parent == NULL){
//			root = p_node->Parent = (node*)malloc(sizeof(node));
//			p_node->Parent->flagLR = NULL;
//            p_node->Parent->Parent = NULL;
//			p_node->Parent->dataA = middleInt;
//			p_node->Parent->dataB = INVALID;
//			p_node->Parent->LChild = left;
//		    p_node->Parent->RChild = right;
//		}else{
//		    p_node->Parent->LChild = left;
//		    p_node->Parent->RChild = right;
//		    addNode(p_node->Parent, middleInt);
//		}
//	}else{
//
//	}
//	return 0;
//}
int CreateBinTree( TreeNode **rootp,ElementType **lp );
void FreeTree( TreeNode *rootp );

int DelTree( TreeNode *rootp,ElementType e );
int Insert( TreeNode *rootp,ElementType Curr,ElementType e,int CurrPos );

TreeNode *FindNode( TreeNode *rootp,ElementType e );
TreeNode *FindParent( TreeNode *rootp,ElementType e );

void Leaf( TreeNode *rootp,int *np );
int Depth( TreeNode *rootp );

void PreOrder( TreeNode *rootp );
void MidOrder( TreeNode *rootp );
void BackOrder( TreeNode *rootp );
/*================================ function body ================*/

/*------------------------------------   建树 -------------------------*/
int CreateBinTree( TreeNode **rootp,ElementType **lp )
{
ElementType CurrElement;

if(*lp==NULL) return 0; /*    字符串不存在，返回 0 */
if(**lp==0) return 1; /*    字符串为空，返回1      */
CurrElement=*(*lp);
(*lp)++;
if(CurrElement=='.') { (*rootp)=NULL; return 1; }
if(!((*rootp)=(TreeNode *) malloc(sizeof(TreeNode))) ) return 0;
(*rootp)->data=CurrElement;
if(!CreateBinTree(&(*rootp)->LChild,lp)) return 0;
return CreateBinTree(&(*rootp)->RChild,lp);
}
/*-------------------------------------------------------   前序遍历子树--------*/
void PreOrder( TreeNode *rootp )
{
if(rootp==NULL) return;
printf(" %c",rootp->data); /*    打印父节点            */
if(rootp->LChild!=NULL) PreOrder(rootp->LChild); /*   打印左子树节点*/
if(rootp->RChild!=NULL) PreOrder(rootp->RChild); /*   打印右子树节点 */
return;
}
/*--------------------------------------------------------   中序遍历子树 --------*/
void MidOrder( TreeNode *rootp )
{
if(rootp==NULL) return;
if(rootp->LChild!=NULL) MidOrder(rootp->LChild);
printf(" %c",rootp->data);
if(rootp->RChild!=NULL) MidOrder(rootp->RChild);
return;
}
/*------------------------------------------------------ 后序遍历子树--------*/
void BackOrder( TreeNode *rootp )
{
if(rootp==NULL) return;
if(rootp->LChild!=NULL) BackOrder(rootp->LChild);
if(rootp->RChild!=NULL) BackOrder(rootp->RChild);
printf(" %c",rootp->data);
return;
}
/*-------------------------------------------------------   查找节点--------*/
TreeNode *FindNode( TreeNode *rootp,ElementType e )
{
TreeNode *temp;

if(rootp==NULL) return NULL; /*    根节点为空，没有找到（空树） */
if(rootp->data==e) return rootp;
if(temp=FindNode(rootp->LChild,e)) return temp;
return FindNode(rootp->RChild,e);
}
/*-------------------------------------------------------    释放树所占内存空间   --------*/
void FreeTree( TreeNode *rootp )
{
if(!rootp) return;
FreeTree(rootp->LChild);
FreeTree(rootp->RChild);
free(rootp);
}
/*-----------------------------------------------------   查询父节点--------*/
TreeNode *FindParent( TreeNode *rootp,ElementType e )
{
TreeNode *temp;

if((rootp==NULL)||(rootp->LChild==NULL && rootp->RChild==NULL)) return NULL;
if((rootp->LChild && rootp->LChild->data==e)
||(rootp->RChild && rootp->RChild->data==e)) return rootp;
temp=FindParent(rootp->LChild,e);
if(temp) return temp;
return FindParent(rootp->RChild,e);
}
/*--------------------------------------------------------    删除树节点   --------*/
int DelTree( TreeNode *rootp,ElementType e )
{
TreeNode *temp;

temp=FindParent(rootp,e);
if(!temp) return 0;
if(temp->LChild &&(temp->LChild->data==e))
{ FreeTree(temp->LChild);
temp->LChild=NULL;
}
else
{ FreeTree(temp->RChild);
temp->RChild=NULL;
}
return 1;
}
/*--------------------------------------------------------   插入节点--------*/
int Insert( TreeNode *rootp,ElementType Curr,ElementType e,int CurrPos )
{
TreeNode *parent,*newA,*temp;

if(!(parent=FindParent(rootp,Curr))) return 0;
if(!(newA=(TreeNode *) malloc(sizeof(TreeNode)))) return 0;
newA->data=e;
if(parent->LChild->data==Curr) { temp=parent->LChild; parent->LChild=newA; }
temp=parent->RChild;
parent->RChild=newA;

if(CurrPos==0) newA->LChild=temp; newA->RChild=NULL;
if(CurrPos==1) newA->RChild=temp; newA->LChild=NULL;

return 1;
}
/*-----------------------------------------------------------    计算叶子节点 --------*/
void Leaf( TreeNode *rootp,int *np )
{
if(rootp==NULL) return ;
if(rootp->LChild==NULL && rootp->RChild==NULL) { (*np)++; return; }
Leaf(rootp->LChild,np);
Leaf(rootp->RChild,np);
}
/*----------------------------------------------------------   计算树高--------*/
int Depth( TreeNode *rootp )
{
int ld,rd; /* ld:左子树深度*/
             /* rd: 右子树深度*/
if(rootp==NULL) return 0;
ld=Depth(rootp->LChild);
rd=Depth(rootp->RChild);
if(ld>rd) return ld+1;
else return rd+1;
}
/*=========================== The end of BinTreeh.h ======================*/

int main()
{
	//TreeNode *a =(TreeNode*)malloc(sizeof(TreeNode));
	//a->data = 100;
	//int b[100];
	//for(int i=0;i<100;i++){
	//	b[i] = i;
	//	

	//}
	int ran[100] = {5, 10, 70, 89, 349};
	insetInt(ran,5, 52);
	insetInt(ran,6, 362);
	//root = (node*)malloc(sizeof(node));
	test();
	//root->dataA = 23;
	//root->dataB = INVALID;
	//root->flagLR = NULL;
 //   root->LChild = root->RChild = root->Parent = NULL;

	//for(int i=0;i<50;i++){
	//	node* tmpNode = getSuitablePossition(root,i);
	//	addNode(tmpNode, i);
	//}
	//root = root;

}