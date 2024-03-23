#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <cstdio>
#include <queue>
#include <unordered_set>
#include <stack>
#include <set>
using namespace std;

template<class T>
class Node
{
public:
	Node()
	{
		data = new T;
	}
	Node(T d)
	{
		data = new T;
		(*data) = d;
	}
	Node &operator=(T d)
	{
		(*data) = d;
		return *this;
	}
	friend ostream &operator<<(ostream &out, Node n)
	{
		out<<*(n.data);
		return out;
	}
	friend ostream &operator<<(ostream &out, Node *n)
	{
		out<<*(n->data);
		return out;
	}
	void setData(T d)
	{
		*data = d;
	}
	T &getData() const
	{
		return *data;
	}
protected:
	T *data;
};

template<class T>
class ListNode : public Node<T>
{
public:
	ListNode() : Node<T>()
	{
		prev = NULL;
		next = NULL;
	}
	ListNode(T d) : Node<T>(d)
	{
		prev = NULL;
		next = NULL;
	}
	ListNode(ListNode *p, ListNode *n) : Node<T>()
	{
		prev = p;
		next = n;
	}
	ListNode(T d, ListNode *p, ListNode *n) : Node<T>(d)
	{
		prev = p;
		next = n;
	}
	ListNode *getNext() const
	{
		return next;
	}
	ListNode *getPrev() const
	{
		return prev;
	}
	void setNext(ListNode *n)
	{
		next = n;
	}
	void setPrev(ListNode *p)
	{
		prev = p;
	}
	ListNode &operator=(T d)
	{
		this->setData(d);
		return *this;
	}
private:
	ListNode *prev, *next;
};

template<class T>
class LinkList
{
public:
	LinkList()
	{
		head = NULL;
		tail = NULL;
	}
	void addFromHead(T d)
	{
		ListNode<T> *node = new ListNode<T>(d);
		if(head != NULL)
		{
			head->setPrev(node);
		}
		node->setNext(head);
		head = node;
		if(tail == NULL)
			tail = node;
	}
	void addFromTail(T d)
	{
		ListNode<T> *node = new ListNode<T>(d);
		if(tail != NULL)
		{
			tail->setNext(node);
		}
		node->setPrev(tail);
		tail = node;
		if(head == NULL)
			head = node;
	}
	void addAfter(ListNode<T> *at, T d)
	{
		if(!exist(at))
			return;
		ListNode<T> *node = new ListNode<T>(d);
		if(at->getNext() != NULL)
			at->getNext()->setPrev(node);
		node->setNext(at->getNext());
		at->setNext(node);
		node->setPrev(at);
		if(node->getNext() == NULL)
			tail = node;
	}
	ListNode<T> *removeFromHead()
	{
		ListNode<T> *n = head;
		if(head != NULL)
		{
			head = head->getNext();
			if(head != NULL)
				head->setPrev(NULL);
			else
				tail = NULL;
			n->setNext(NULL);
		}
		return n;
	}
	ListNode<T> *removeFromTail()
	{
		ListNode<T> *n = tail;
		if(tail != NULL)
		{
			tail = tail->getPrev();
			if(tail != NULL)
				tail->setNext(NULL);
			else
				head = NULL;
			n->setPrev(NULL);
		}
		return n;
	}
	ListNode<T> *remove(ListNode<T> *n)
	{
		if(!exist(n))
			return NULL;
		if(n == head)
			return removeFromHead();
		if(n == tail)
			return removeFromTail();
		n->getPrev()->setNext(n->getNext());
		n->getNext()->setPrev(n->getPrev());
		n->setNext(NULL);
		n->setPrev(NULL);
		return n;
	}
	ListNode<T> *exist(T d)
	{
		ListNode<T> *j = head;
		while(j != NULL)
		{
			if(j->getData() == d)
				return j;
			j = j->getNext();
		}
		return NULL;
	}
	bool exist(ListNode<T> *n)
	{
		ListNode<T> *j = head;
		while(j != NULL)
		{
			if(j == n)
				return true;
			j = j->getNext();
		}
		return false;
	}
	ListNode<T> &operator[](int i)
	{
		ListNode<T> *j = head;
		int k;
		for(k = 0;k < i && j != NULL;k ++)
			j = j->getNext();
		if(j == NULL)
			throw invalid_argument("index does not exist.");
		return *j;
	}
	void print() const
	{
		ListNode<T> *j;
		j = head;
		while(j != NULL)
		{
			cout<<(*j)<<" ";
			j = j->getNext();
		}
		cout<<endl;
	}
protected:
	ListNode<T> *head, *tail;
};

template<class V, class E>
class WeightedGraphEdge;


template<class V, class E>
class WeightedGraphVertex : public Node<V>
{
public:
	WeightedGraphVertex() :Node<V>()
	{
		list = new LinkList<WeightedGraphEdge<V, E> *>();
	}
	WeightedGraphVertex(V d) :Node<V>(d)
	{
		list = new LinkList<WeightedGraphEdge<V, E> *>();
	}
	void addEdge(WeightedGraphEdge<V, E> *edge)
	{
		list->addFromTail(edge);
	}
	void remove(WeightedGraphEdge<V, E> *node)
	{
	}
	ListNode<WeightedGraphEdge<V, E> *> *operator[](int n)
	{
		try
		{
			return (&(*list)[n]);
		}
		catch(invalid_argument e)
		{
			return NULL;
		}
	}
private:
	LinkList<WeightedGraphEdge<V, E> *> *list;
};

template<class V, class E>
class WeightedGraphEdge : public Node<E>
{
public:
	WeightedGraphEdge() : Node<E>()
	{
		end[0] = NULL;
		end[1] = NULL;
	}
	WeightedGraphEdge(E d) : Node<E>(d)
	{
		end[0] = NULL;
		end[1] = NULL;
	}
	WeightedGraphEdge(E d, WeightedGraphVertex<V, E> *v1, WeightedGraphVertex<V, E> *v2) : Node<E>(d)
	{
		end[0] = v1;
		end[1] = v2;
	}
	//返回一個指向圖中頂點的指標的參考，該頂點是與給定邊相聯的另一個頂點。
	WeightedGraphVertex<V, E> *&getAnotherEnd(WeightedGraphVertex<V, E> *v)
	{
		if(v != end[0])
			return end[0];
		return end[1];
	}
private:
	WeightedGraphVertex<V, E> *end[2];
};

template<class V, class E>
class WeightedGraph
{
public:
	WeightedGraph()
	{
		vertex = new LinkList<WeightedGraphVertex<V, E> *>();
		edge = new LinkList<WeightedGraphEdge<V, E> *>();
	}
	WeightedGraphVertex<V, E> *operator[](int n)
	{
		try
		{
			return (*vertex)[n].getData();
		}
		catch(invalid_argument e)
		{
			return NULL;
		}
	}
	void addLink(WeightedGraphVertex<V, E> *v1, WeightedGraphVertex<V, E> *v2, E w)
	{
		WeightedGraphEdge<V, E> *edge = new WeightedGraphEdge<V, E>(w, v1, v2);
		v1->addEdge(edge);
		if(v1 != v2)
			v2->addEdge(edge);
	}
	WeightedGraphVertex<V, E> *addVertex(V d)
	{
		WeightedGraphVertex<V, E> *v = new WeightedGraphVertex<V, E>(d);
		vertex->addFromTail(v);
		return v;
	}


	// 廣度優先搜尋
	void BFS(WeightedGraphVertex<V, E> *v) {
		if (v == NULL) return;
		
		queue<WeightedGraphVertex<V, E>*> q;
		set<WeightedGraphVertex<V, E>*> visited;
		
		q.push(v);
		visited.insert(v);
		
		while (!q.empty()) {
			WeightedGraphVertex<V, E> *current = q.front();//當前頂點
			q.pop();
			cout << current->getData() << " ";
			
			//遍歷與當前節點相鄰的邊
			for (int i = 0; ; i++) {

				// 獲取當前節點的第i個邊
				ListNode<WeightedGraphEdge<V, E> *> *edgeNode = (*current)[i];// 獲取當前節點的第i個邊

				// 如果沒有邊了，就跳出
				if (edgeNode == NULL) break;
				
				// 獲取邊的另一端點adjacent(當前的鄰點)
				WeightedGraphVertex<V, E> *adjacent = edgeNode->getData()->getAnotherEnd(current);

				// 如果還沒有訪問過，就訪問
				if (visited.find(adjacent) == visited.end()) {
					q.push(adjacent);
					visited.insert(adjacent);
				}
			}
		}
	}

	void DFS(WeightedGraphVertex<V, E> *v) {
		if (v == NULL) return;

		stack<WeightedGraphVertex<V, E>*> s;
		set<WeightedGraphVertex<V, E>*> visited;

		s.push(v);

		while (!s.empty()) {
			WeightedGraphVertex<V, E> *current = s.top();// 當前節點
			s.pop();

			// 如果已經訪問過，就跳過
			if (visited.find(current) != visited.end()) {
				continue;
			}
			cout << current->getData() << " ";
			visited.insert(current);

			// 遍歷與當前節點相鄰的邊
			for (int i = 0; ; i++) {
				ListNode<WeightedGraphEdge<V, E> *> *edgeNode = (*current)[i];// 獲取當前節點的第i個邊
				if (edgeNode == NULL) break;

				// 獲取邊的另一端點adjacent(當前的鄰點)
				WeightedGraphVertex<V, E> *adjacent = edgeNode->getData()->getAnotherEnd(current);
				if (visited.find(adjacent) == visited.end()) {
					s.push(adjacent);
				}
			}
		}
	}

private:
	LinkList<WeightedGraphVertex<V, E> *> *vertex;//頂點
	LinkList<WeightedGraphEdge<V, E> *> *edge;//邊
};


bool operator>=(pair<int, int> a, pair<int, int> b)
{
    if(a.second >= b.second)
        return true;
    return false;
}

bool operator>(pair<int, int> a, pair<int, int> b)
{
    if(a.second > b.second)
        return true;
    return false;
}

int main()
{
    WeightedGraph<char, int> *g = new WeightedGraph<char, int>();
    LinkList<WeightedGraphVertex<char, int> *> *node = new LinkList<WeightedGraphVertex<char, int> *>();
	
    int j, k, n, a, b, w;
    scanf("%d", &n);
    srand(n);
	
    for(j = 0;j < 26;j ++)
        node->addFromTail(g->addVertex(j + 'A'));
    k = rand() % 100;
    for(j = 0;j < k;j ++){
        a = rand() % 26;
        b = rand() % 26;
        w = rand() % 100;
        g->addLink(((*node)[a]).getData(), ((*node)[b]).getData(), w);
    } 
    g->BFS((*node)[rand() % 26].getData());
    cout<<endl;
    g->DFS((*node)[rand() % 26].getData());
	return 0;
}