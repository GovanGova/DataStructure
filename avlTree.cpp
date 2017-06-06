//This avl based balanced binary search tree

#include<iostream>
#include<memory>
using namespace std;

//Data should be int. but it should be constructed before
// inserting into tree
//template<typename T>
class avltree{
private:
	int data;
	shared_ptr<avltree> left;
	shared_ptr<avltree> right;

	//store height of each node
	//
	int height;
public:
	avltree(int data):data(data){
		//leaf node height is one
		height=1;
		left=nullptr;
		right= nullptr;

	}

	~avltree(){
		left=nullptr;
		right=nullptr;
		
	}

	void updateHeight()
	{
		int leftH=0, rightH=0;
		if(left!=nullptr)
			leftH=left->height;
		if(right!=nullptr)
			rightH=right->height;

		height=1+max(leftH, rightH);
	}
	int getHeight(){return height;};
	int getData(){return data;};
	shared_ptr<avltree>& getleft(){ return left;}
	shared_ptr<avltree>& getRight(){ return right;}

	// return difference between height of left and 
	// right child subtree.
	int  getBalance()
	{
		int leftH=0, rightH=0;
		if(left!=nullptr)
			leftH=left->height;
		if(right!=nullptr)
			rightH=right->height;

		return leftH-rightH;
	}
	friend void leftRotation(shared_ptr<avltree>& root);
	friend void rightRotation(shared_ptr<avltree>& root);
	friend void insert(shared_ptr<avltree>& root, int data);
	friend void preorder(shared_ptr<avltree>& root);
	friend void postorder(shared_ptr<avltree>& root);
	friend void inorder(shared_ptr<avltree>& root);
	friend void formDoublyList(shared_ptr<avltree>& root);
	friend void formDoublyUtil(shared_ptr<avltree>& root);
};

//template<typename T>
void rightRotation(shared_ptr<avltree>& root)
{
	auto newroot=root->left;
	auto rootRight= newroot->right;

	root->left=rootRight;
	newroot->right=root;

	//udpate existig root height
	root->updateHeight();
	newroot->updateHeight();

	//update the reference
	root=newroot;

}

//template<typename T>
void leftRotation(shared_ptr<avltree>& root)
{
	auto newroot=root->right;
	auto rootLeft=newroot->left;

	root->right=rootLeft;
	newroot->left=root;

	//update height
	root->updateHeight();
	newroot->updateHeight();

	//update the reference
	root=newroot;
}


//template<typename T>
void insert(shared_ptr<avltree>& root, int key)
{
	// 1. create a node if root is null
	// 2. since this function itself designed as recurssion to insert till
	//    leaf, update height of previous node
	// 3. calculate balace.
	//    do left-left if balance is greater than 1 and key is less than root->left in this call
	//	  do left-right if balance is greater than 1 and key is greater than root->left in this call
	//	  do right-left if balance is less than -1 and key is less than root->right in this call
	//    do right-right if balance is greater than 1 and key is greater than root->right in this call

	if(root==nullptr)
	{
		shared_ptr<avltree> newnode(new avltree(key));
		root=newnode;
	}
	else
	{
		if(key>root->data)
			insert(root->right, key);
		else
			insert(root->left, key);

		//step 2 update height and calculate balance 
		root->updateHeight();
		auto balance=root->getBalance();

		//step3
		//right-right
		if(balance<-1 && key>root->right->data)
		{
			//Do left rotation
			leftRotation(root);
		}
		else if(balance<-1 && key<root->right->data)
		{
			//right-left
			rightRotation(root->right);
			leftRotation(root);
		}
		else if(balance>1 && key<root->left->data)
		{
			//left-left
			rightRotation(root);
		}
		else if(balance>1 && key>root->left->data)
		{
			//left-right
			leftRotation(root->left);
			rightRotation(root);
		}
	}

}

void preorder(shared_ptr<avltree>& root){

	if(root!=nullptr){
		cout<<root->data<<" ";
		preorder(root->left);
		preorder(root->right);
	}

}

void postorder(shared_ptr<avltree>& root){
	if(root!=nullptr){

		postorder(root->left);
		postorder(root->right);
		cout<<root->data<<" ";
	}
}

void inorder(shared_ptr<avltree>& root){
	if(root!=nullptr){

		inorder(root->left);
		cout<<root->data<<" ";
		inorder(root->right);

	}
}

/* print all node at given node*/
void printAtgivenlevel(shared_ptr<avltree>& root, int level){
	if(level==1 ){
		if(root!=nullptr)
			cout<<root->getData()<<" ";
	}
	else{
		printAtgivenlevel(root->getleft(), level-1);
		printAtgivenlevel(root->getRight(), level-1);
	}
}

// Level of tree. Prints all node starting from level 1 to height of 
// tree
void levelOfTree(shared_ptr<avltree>& root){

	for(int i=1; i<=root->getHeight();i++)
	{
		printAtgivenlevel(root, i);
		cout<<endl;
	}
}
void formDoublyList(shared_ptr<avltree>& root)
{
	if(root!=nullptr)
	{
		//left tree
		
		if(root->left!=nullptr)
		{
			formDoublyList(root->left);
			auto left=root->left;
			while(left->right!=nullptr)
			{
				
				left=left->right;
			}

			left->right=root;
			root->left=left;
			
		}
		if(root->right!=nullptr)
		{
			formDoublyList(root->right);
			auto right=root->right;

			while(right->left!=nullptr)
			{
				
				right=right->left;
			}

			right->left= root;
			root->right=right;
		}
	}
		
}

void formDoublyUtil(shared_ptr<avltree>& root)
{
	formDoublyList(root);
	while(root->left!=nullptr)
		root=root->left;

}
int main(){
	{
		shared_ptr<avltree> root;
		insert(root, 10);
		insert(root,20);
		insert(root, 30);
		insert(root, 40);
		insert(root,35);
		insert(root, 5);
		insert(root,7);
		insert(root,8);
		preorder(root);
		cout<<endl;
		postorder(root);
		cout<<endl;
		inorder(root);

		cout<<endl<<"Level of tree";
		levelOfTree(root);
		
		formDoublyUtil(root);
		
	}

}