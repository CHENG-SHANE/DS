#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <queue>
#include <vector>
#include <set>

using namespace std;

template <class T>
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
class WeigGraEdge;

template<class V, class E>
class WeigGraVertex : public Node<V>
{
public:
	WeigGraVertex() :Node<V>()
	{
		list = new LinkList<E>();
	}
	WeigGraVertex(V d) :Node<V>(d)
	{
		list = new LinkList<WeigGraEdge<V, E> *>();
	}
	void addEdge(WeigGraEdge<V, E> *edge)
	{
		list->addFromTail(edge);
	}
	void remove(WeigGraEdge<V, E> *node)
	{
	}
	ListNode<WeigGraEdge<V, E> *> *operator[](int n)
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
	LinkList<WeigGraEdge<V, E> *> *list;
};

template<class V, class E>
class WeigGraEdge : public Node<E>
{
public:
	WeigGraEdge() : Node<E>()
	{
		end[0] = NULL;
		end[1] = NULL;
	}
	WeigGraEdge(E d) : Node<E>(d)
	{
		end[0] = NULL;
		end[1] = NULL;
	}
	WeigGraEdge(E d, WeigGraVertex<V, E> *v1, WeigGraVertex<V, E> *v2) : Node<E>(d)
	{
		end[0] = v1;
		end[1] = v2;
	}
	WeigGraVertex<V, E> *&getAnotherEnd(WeigGraVertex<V, E> *v)
	{
		if(v != end[0])
			return end[0];
		return end[1];
	}
private:
	WeigGraVertex<V, E> *end[2];
};

template<class V, class E>
class WeightedGraph
{
public:
	WeightedGraph()
	{
		vertex = new LinkList<WeigGraVertex<V, E> *>();
		edge = new LinkList<WeigGraEdge<V, E> *>();
	}
	WeigGraVertex<V, E> *operator[](int n)
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
	void addLink(WeigGraVertex<V, E> *v1, WeigGraVertex<V, E> *v2, E w)
	{
		WeigGraEdge<V, E> *edge = new WeigGraEdge<V, E>(w, v1, v2);
		v1->addEdge(edge);
		if(v1 != v2)
			v2->addEdge(edge);
	}
	WeigGraVertex<V, E> *addVertex(V d)
	{
		WeigGraVertex<V, E> *v = new WeigGraVertex<V, E>(d);
		vertex->addFromTail(v);
		vertexCount ++;
		return v;
	}
	void adjList()
	{
		ListNode<WeigGraVertex<V, E> *> *cur = &(*vertex)[0];
		while(cur != NULL)
		{
			WeigGraVertex<V, E> *temp = cur->getData();
			cout<<temp<<": ";
			ListNode<WeigGraEdge<V, E> *> *e = (*temp)[0];
			while(e != NULL)
			{
				cout<<e->getData()->getAnotherEnd(temp)<<"("<<e->getData()<<") ";
				e = e->getNext();
			}
			cout<<endl;
			cur = cur->getNext();
		}
	}
//找出一個能夠連接圖中所有節點而且邊的權重總和最小的樹
WeightedGraph *minSpanTree(WeigGraVertex<V, E> *start)
{	
    //確保小的邊在前面(top)
    auto comp = [](WeigGraEdge<V, E> *a, WeigGraEdge<V, E> *b) {
        return a->getData() > b->getData();// a 大於 b返回 true
    };

    // 優先隊列
	//priority_queue <資料類型、容器類型、比較類型>
    priority_queue<WeigGraEdge<V, E>*, vector<WeigGraEdge<V, E>*>, decltype(comp)>  pq(comp);
    set<WeigGraVertex<V, E>*> visited;
	// 創建一個新的加權圖對象作為最小生成樹
    WeightedGraph *mst = new WeightedGraph();

    // 將起點加到最小生成樹和已訪問集合中
    mst->addVertex(start->getData());
    visited.insert(start);

    // 將從起始頂點出發的所有邊添加到優先隊列
    for (ListNode<WeigGraEdge<V, E>*> *node = (*start)[0]; node != NULL; node = node->getNext()) {
        pq.push(node->getData());//pq是優先對列所以已經用comp排好了
    }

    // 建立最小生成樹
    while (!pq.empty()) {
        // 從隊列中取出最小權重的邊
        WeigGraEdge<V, E> *edge = pq.top();
        pq.pop();

        // 獲取與當前最小邊相連的另一個頂點
        WeigGraVertex<V, E> *vertex = edge->getAnotherEnd(start);

        // 如果這個頂點還沒有被訪問
        if (visited.count(vertex) == 0) {
            // 添加頂點到最小生成樹和已訪問集合
            visited.insert(vertex);
            mst->addVertex(vertex->getData());
            mst->addLink(start, vertex, edge->getData());

            // 將所有從這個新頂點出發的未訪問邊添加到優先隊列
            for (ListNode<WeigGraEdge<V, E>*> *node = (*vertex)[0]; node != NULL; node = node->getNext()) {
                if (visited.count(node->getData()->getAnotherEnd(vertex)) == 0) {
                    pq.push(node->getData());
                }
            }
        }
    }
    return mst;
}
private: 
	LinkList<WeigGraVertex<V, E> *> *vertex;
	LinkList<WeigGraEdge<V, E> *> *edge;
	int vertexCount, edgeCount;
};

int main()
{
	WeightedGraph<char, int> *g = new WeightedGraph<char, int>();
	WeightedGraph<char, int> *tree;
	int j, k, i, l;
	srand(time(NULL));
	for(j = 0;j < 5;j++)
	{
		g->addVertex(j + 'a');
	}
	for(j = 0;j < 5;j ++)
    {
        k = rand() % 5;
        i = rand() % 5;
        l = rand() % 100;
        g->addLink((*g)[k], (*g)[i], l);
    }
	g->adjList();
	tree = g->minSpanTree((*g)[0]);
	tree->adjList();
	return 0;
}
