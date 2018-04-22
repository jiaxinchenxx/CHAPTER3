#include <iostream>
#include <string>
#include <vector>

using namespace std;


#include <iostream>
#include <string>

using namespace std;

class BinaryTreeNode {

public:

	char element;
	BinaryTreeNode * parent;
	BinaryTreeNode * leftChild;
	BinaryTreeNode * rightChild;

	BinaryTreeNode() {
		leftChild = NULL;
		rightChild = NULL;
	}

	BinaryTreeNode(char x) {
		this->element = x;
		leftChild = NULL;
		rightChild = NULL;
	}

	BinaryTreeNode(char x, BinaryTreeNode * lc, BinaryTreeNode *rc) {
		this->element = x;
		this->leftChild = lc;
		this->rightChild = rc;
	}

	BinaryTreeNode * getLeftChild() { return this->leftChild; }
	BinaryTreeNode * getRightChild() { return this->rightChild; }

	void setLeftChild(BinaryTreeNode *lc) { this->leftChild = lc; }
	void setRightChild(BinaryTreeNode * rc) { this->rightChild = rc; }

	char getValue() { return this->element; }
	void setValue(char x) { this->element = x; }
	bool isLeaf() { return (this->leftChild == NULL && this->rightChild == NULL) ? true : false; }
};


class ArrStack {

public:

	int maxSize;
	int top;
	BinaryTreeNode* (*st);

	ArrStack(int maxSize) {
		this->maxSize = maxSize;
		top = -1;
		st = new BinaryTreeNode*[this->maxSize];
	}

	~ArrStack() {}

	bool push(BinaryTreeNode * node) {
		if (top == this->maxSize - 1) {
			cout << "FULL Stack!" << endl;
			return false;
		}
		st[++top] = node;
		return true;
	}

	BinaryTreeNode* Pop() {
		if (top == -1) {
			cout << "FULL Stack" << endl;
			return NULL;
		}

		return st[top--];
	}

	BinaryTreeNode * Top() {
		if (top == -1) {
			cout << "FULL Stack!" << endl;
			return NULL;
		}

		return st[top];
	}

	bool isEmpty() { return (this->top == -1) ? true : false; }
};


class ArrQueue {

public:
	int maxSize;
	int front;
	int rear;
	BinaryTreeNode * (*q);

	ArrQueue(int maxSize) {
		this->maxSize = maxSize;
		q = new BinaryTreeNode *[this->maxSize];
		front = rear = 0;
	}

	~ArrQueue() {}

	bool EnQueue(BinaryTreeNode * node) {
		if ((rear + 1) % this->maxSize == front) {
			cout << "FULL Queue!" << endl;
			return false;
		}

		q[rear] = node;
		rear = (rear + 1) % this->maxSize;
		return true;
	}

	BinaryTreeNode * DeQueue() {
		if (front == rear) {
			cout << "EMPTY Queue!" << endl;
			return NULL;
		}

		BinaryTreeNode * node = q[front];
		front = (front + 1) % this->maxSize;
		return node;
	}

	BinaryTreeNode * GetFront() {
		if (front == rear) {
			cout << "EMPTY Queue!" << endl;
			return NULL;
		}

		BinaryTreeNode * node = q[front];
		return node;
	}

	bool isEmpty() { return (rear == front) ? true : false; }
};

class BinaryTree {

public:

	BinaryTreeNode * root;

	BinaryTree() {
		root = new BinaryTreeNode();
		root->leftChild = NULL;
		root->rightChild = NULL;
		root->parent = NULL;
	}

	~BinaryTree() {}

};

void pre_order_recur(BinaryTreeNode *root) {

	if (root != NULL) {
		cout << root->element << ' ';
		if (root->leftChild)
			pre_order_recur(root->leftChild);
		if (root->rightChild)
			pre_order_recur(root->rightChild);
	}
	else
		return;
}

void in_order_recur(BinaryTreeNode * root) {
	if (root != NULL) {
		if (root->leftChild)
			in_order_recur(root->leftChild);
		cout << root->element << ' ';
		if (root->rightChild)
			in_order_recur(root->rightChild);
	}
	else
		return;
}

void post_order_recur(BinaryTreeNode * root) {
	if (root != NULL) {
		if (root->leftChild)
			post_order_recur(root->leftChild);
		if (root->rightChild)
			post_order_recur(root->rightChild);
		cout << root->element << ' ';
	}
	else
		return;
}

void pre_order_basic(BinaryTreeNode *root) {

	ArrStack as(36);

	BinaryTreeNode *pointer = root;

	while (pointer || !as.isEmpty()) {
		if (pointer == NULL)
			pointer = as.Pop()->rightChild;
		else {
			cout << pointer->element << ' ';
			as.push(pointer);
			if (pointer->leftChild)
				pointer = pointer->leftChild;
			else
				pointer = as.Pop()->rightChild;
		}
	}

}

void in_order_basic(BinaryTreeNode *root) {
	ArrStack as(36);

	BinaryTreeNode *pointer = root;

	while (pointer || !as.isEmpty()) {

		if (pointer == NULL) {
			pointer = as.Pop();
			cout << pointer->element << ' ';
			pointer = pointer->rightChild;
		}
		else {
			for (; pointer; pointer = pointer->leftChild)
				as.push(pointer);

			pointer = as.Pop();
			cout << pointer->element << ' ';

			pointer = pointer->rightChild;
		}

	}

}

void post_order_basic(BinaryTreeNode * root) {

	ArrStack as(36);
	BinaryTreeNode *pointer = root;
	BinaryTreeNode *prev = NULL;

	while (pointer || !as.isEmpty()) {

		if (pointer && pointer->rightChild != prev) {

			for (; pointer; pointer = pointer->leftChild)
				as.push(pointer);

			pointer = as.Top()->rightChild;
		}

		else {
			pointer = as.Pop();
			cout << pointer->element << ' ';
			prev = pointer;

			if (as.isEmpty())
				break;
			if (as.Top()->rightChild != prev)
				pointer = as.Top()->rightChild;
			else
				pointer = as.Top();
		}
	}

}

void post_order_basic1(BinaryTreeNode * root) {
	ArrStack as(36);
	BinaryTreeNode *pointer = root;
	BinaryTreeNode *prev = NULL;

	while (pointer || !as.isEmpty()) {
		if (pointer) {
			as.push(pointer);
			pointer = pointer->leftChild;
		}

		else {
			if (as.Top()->rightChild && as.Top()->rightChild != prev)
				pointer = as.Top()->rightChild;
			else {
				cout << as.Top()->element << ' ';
				prev = as.Pop();
			}
		}
	}
}


void breadth_first(BinaryTreeNode *root) {

	ArrQueue aq(36);

	BinaryTreeNode *cur = root;
	if (cur)
		aq.EnQueue(cur);

	while (!aq.isEmpty()) {

		cur = aq.DeQueue();
		cout << cur->element << ' ';
		if (cur->leftChild)
			aq.EnQueue(cur->leftChild);
		if (cur->rightChild)
			aq.EnQueue(cur->rightChild);
	}
}

BinaryTreeNode * pre_inGetRoot(string pre_order, string in_order) {


	int count = 0, len = in_order.length();
	if (len == 1)
		return new BinaryTreeNode(pre_order[0]);

	BinaryTreeNode * root = new BinaryTreeNode(pre_order[0]);
	for (int i = 0; i < len; i++) {
		if (in_order[i] != root->element)
			count++;
		else
			break;
	}

	if (count == 0)
		root->leftChild = NULL;
	else {
		string left_in_order = in_order.substr(0, count);
		string left_pre_order = pre_order.substr(1, count);
		root->leftChild = pre_inGetRoot(left_pre_order, left_in_order);
	}

	if (count + 1 == len)
		root->rightChild = NULL;
	else {
		string right_in_order = in_order.substr(count + 1, len - count - 1);
		string right_pre_order = pre_order.substr(count + 1, len - count - 1);
		root->rightChild = pre_inGetRoot(right_pre_order, right_in_order);
	}
	return root;
}

BinaryTreeNode * post_inGetRoot(string post_order, string in_order) {

	int count = 0, len = in_order.length();
	if (len == 1)
		return new BinaryTreeNode(post_order[0]);

	BinaryTreeNode * root = new BinaryTreeNode(post_order[len - 1]);

	for (int i = 0; i < len; i++) {
		if (in_order[i] != root->element)
			count++;
		else
			break;
	}

	if (count > 0) {
		string left_in_order = in_order.substr(0, count);
		string left_post_order = post_order.substr(0, count);
		root->leftChild = post_inGetRoot(left_post_order, left_in_order);
	}

	if (count + 1 < len) {
		string right_in_order = in_order.substr(count + 1, len - count - 1);
		string right_post_order = post_order.substr(count, len - count - 1);
		root->rightChild = post_inGetRoot(right_post_order, right_in_order);
	}

	return root;
}

int GetOne(BinaryTreeNode * root) {
	if (root == NULL || root->isLeaf())
		return 0;
	else {
		if ((root->leftChild != NULL && root->rightChild == NULL) || (root->leftChild == NULL && root->rightChild != NULL))
			return 1 + GetOne(root->leftChild) + GetOne(root->rightChild);
		else
			return GetOne(root->leftChild) + GetOne(root->rightChild);
	}

}

int GetZero(BinaryTreeNode * root) {
	if (!root)
		return 0;
	if (root->isLeaf())
		return 1;

	return GetZero(root->leftChild) + GetZero(root->rightChild);

}

int GetTwo(BinaryTreeNode * root) {

	if (root == NULL || root->isLeaf()) //|| (root->leftChild == NULL && root->rightChild != NULL) || (root->leftChild != NULL && root->rightChild == NULL))
		return 0;

	else {
		if (root->leftChild != NULL && root->rightChild != NULL)
			return 1 + GetTwo(root->leftChild) + GetTwo(root->rightChild);
		else
			return GetTwo(root->leftChild) + GetTwo(root->rightChild);
	}

}

int GetHeight(BinaryTreeNode * root) {

	if (root == NULL)
		return 0;
	if (root->isLeaf())
		return 1;

	int lch = 0, rch = 0;
	lch = GetHeight(root->leftChild);
	rch = GetHeight(root->rightChild);

	return 1 + (lch > rch ? lch : rch);

}

int GetWidth(BinaryTreeNode * root) {
	if (root == NULL)
		return 0;
	if (root->isLeaf())
		return 1;

	int lcw = 0, rcw = 0;
	lcw = GetWidth(root->leftChild);
	rcw = GetWidth(root->rightChild);

	return (lcw + rcw > 1) ? (lcw + rcw) : 1;

}


void GetWidth(int * arr, BinaryTreeNode* root, int cur, int height) {

	if (cur == height)
		return;
	if (root == NULL) {
		arr[cur] += 0;
		return;
	}
	else
		arr[cur] += 1;

	GetWidth(arr, root->leftChild, cur + 1, height);
	GetWidth(arr, root->rightChild, cur + 1, height);


}

int GetWidest(BinaryTreeNode * root, int* arr, int height) {


	for (int i = 0; i < height; i++)
		arr[i] = 0;

	GetWidth(arr, root, 0, height);

	int max = -1;
	for (int i = 0; i < height; i++)
		if (arr[i] > max)
			max = arr[i];

	return max;

}


char GetMax(BinaryTreeNode * root) {

	if (root->isLeaf())
		return root->element;

	char lc = ' ', rc = ' ';

	if (root->leftChild)
		lc = GetMax(root->leftChild);

	if (root->rightChild)
		rc = GetMax(root->rightChild);

    char max = root->element;
	if (max < lc)
		max = lc;
	
	return (max > rc) ? max : rc;
}

void Exchange(BinaryTreeNode * root) {

	bool isChange = false;
	if (root->leftChild != NULL){
		if (root->leftChild->isLeaf())
			isChange = true;
	}

	if (root->rightChild!= NULL) {
		if (root->rightChild->isLeaf())
			isChange = true;
	}

	if (isChange) {
		BinaryTreeNode * tmp = root->leftChild;
		root->leftChild = root->rightChild;
		root->rightChild = tmp;
		return;
	}



	if (root->leftChild)
		Exchange(root->leftChild);
	if (root->rightChild)
		Exchange(root->rightChild);

	BinaryTreeNode * tmp = root->leftChild;
	root->leftChild = root->rightChild;
	root->rightChild = tmp;
	return;
}

void delLeaf(BinaryTreeNode * root) {

	if (root->leftChild == NULL || root->leftChild->isLeaf())
		root->leftChild = NULL;
	if (root->rightChild == NULL || root->rightChild->isLeaf())
		root->rightChild = NULL;

	if (root->leftChild)
		delLeaf(root->leftChild);
	if (root->rightChild)
		delLeaf(root->rightChild);
	return;
}


void isComplete(BinaryTreeNode * root) {

	ArrQueue aq(36);
	vector<BinaryTreeNode * > vec;
	vec.push_back(new BinaryTreeNode());
	int count = 0;

	BinaryTreeNode * cur = root;
	if (cur)
		aq.EnQueue(cur);
	else {
		cout << "YES!" << endl;
		return;
	}


	while (!aq.isEmpty()) {

		cur = aq.DeQueue();
		count++;
		vec.push_back(cur);
		if (cur->leftChild)
			aq.EnQueue(cur->leftChild);
		if (cur->rightChild)
			aq.EnQueue(cur->rightChild);
	}

	int p = count / 2;
	int lorr = count % 2;

	cout << vec[p]->element << ' ' << vec[count]->element << endl;

	if (lorr == 0) {
		if (vec[p]->leftChild != vec[count])
			cout << "NO!" << endl;
	}
	else {
		if (vec[p]->rightChild != vec[count])
			cout << "NO!" << endl;
	}


	

}

void main() {

	string pre_order = "ABDFGCEH";
	string in_order = "BFDGACEH";
	string post_order = "FGDBHECA";

	//BinaryTreeNode * root = post_inGetRoot(post_order, in_order);
	BinaryTreeNode *root = pre_inGetRoot(pre_order, in_order);
	pre_order_basic(root);
	cout << endl;

	cout << "ONE: " << GetOne(root) << endl;
	cout << "ZERO: " << GetZero(root) << endl;
	cout << "TWO: " << GetTwo(root) << endl;
	cout << "HEIGHT: " << GetHeight(root) << endl;

	int height = GetHeight(root);
	int * arr = new int[height];

	cout << "WIDTH: " << GetWidest(root, arr, height) << endl;
	cout << "MAX: " << GetMax(root) << endl;
	//Exchange(root);
	//delLeaf(root);
	pre_order_basic(root);
	cout << endl;

	isComplete(root);

	system("pause");
}


