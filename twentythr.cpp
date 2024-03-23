#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <map>
#include <queue>
#include <limits>
#include <vector>

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
class WeightedGraphEdge;

template<class V, class E>
class WeightedGraphVertex : public Node<V>
{
public:
	WeightedGraphVertex() :Node<V>()
	{
		list = new LinkList<E>();
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
		vertexCount ++;
		return v;
	}
	void adjList()
	{
		ListNode<WeightedGraphVertex<V, E> *> *cur = &(*vertex)[0];
		while(cur != NULL)
		{
			WeightedGraphVertex<V, E> *temp = cur->getData();
			cout<<temp<<": ";
			ListNode<WeightedGraphEdge<V, E> *> *e = (*temp)[0];
			while(e != NULL)
			{
				cout<<e->getData()->getAnotherEnd(temp)<<"("<<e->getData()<<") ";
				e = e->getNext();
			}
			cout<<endl;
			cur = cur->getNext();
		}
	}

WeightedGraph *shortestPathTree(WeightedGraphVertex<V, E> *root)
{
    map<WeightedGraphVertex<V, E>*, E> dist; // 儲存每個頂點到root的最短距離
    map<WeightedGraphVertex<V, E>*, bool> visited; // 標記每個頂點是否已被訪問
	map<WeightedGraphVertex<V, E>*, WeightedGraphVertex<V, E>*> parent; // 儲存每個頂點在最短路徑樹中的父節點

    // 初始化距離和訪問標記
    for (int i = 0; i < vertexCount; i++) {
        WeightedGraphVertex<V, E> *v = (*vertex)[i].getData();
        dist[v] = numeric_limits<E>::max(); // 將所有頂點的距離初始化為無限大
        visited[v] = false; // 將所有頂點設為未訪問
    }
    dist[root] = 0; // 將起始頂點的距離設為0

    // 最短路徑
    for (int i = 0; i < vertexCount - 1; i++) {
        WeightedGraphVertex<V, E> *u = nullptr; // 用於儲存當前最小距離的頂點
        E minDist = numeric_limits<E>::max(); // 最小距離

        // 找到未訪問的最小距離頂點
		//從dist中找到最小值
        for (auto &pair : dist) {
			//如果該點未訪問且距離小於minDist，則更新頂點和距離
            if (!visited[pair.first] && pair.second <= minDist) {
                u = pair.first;//Key 頂點
                minDist = pair.second;//Value 最小距離
            }
        }

        if (u == nullptr) break; // 如果沒有可達的頂點則跳出循環

        visited[u] = true; // 標記當前頂點為已訪問

        // 更新鄰接頂點的距離
        ListNode<WeightedGraphEdge<V, E> *> *edgeNode = (*u)[0];//從第一個鄰居節點開始比較
        while (edgeNode != NULL) {
            auto edge = edgeNode->getData();//邊
            auto v = edge->getAnotherEnd(u);//點

            E weight = edge->getData();//獲得權重
			//如果該點未訪問且距離比已知的路徑更短，則更新距離和父節點
            if (!visited[v] && dist[u] + weight < dist[v]) {
				dist[v] = dist[u] + weight;
        		parent[v] = u; // 記錄父節點
			}

            edgeNode = edgeNode->getNext();
        }
    }

    WeightedGraph *shortestPathTree = new WeightedGraph();
	//dist現在存滿了到任何點的最短路徑
    for (auto it : dist) {
        auto vertex = shortestPathTree->addVertex(it.first->getData());
		// 檢查走到這個點之前有沒有父親節點(必經的節點)
        if (parent.find(it.first) != parent.end() && parent[it.first] != nullptr) {
            auto parentVertex = shortestPathTree->addVertex(parent[it.first]->getData());
            shortestPathTree->addLink(vertex, parentVertex, dist[it.first]);
        }
    }
    return shortestPathTree; // 返回最短路徑樹
}

private:
	LinkList<WeightedGraphVertex<V, E> *> *vertex;
	LinkList<WeightedGraphEdge<V, E> *> *edge;
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
	tree = g->shortestPathTree((*g)[0]);
	tree->adjList();
	return 0;
}
