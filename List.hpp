//感谢《数据结构（C++语言版）》提供的代码

#include"ListNode.hpp"

template <typename T> class List {
private:
	int _size;
	ListNodePosi(T) header;
	ListNodePosi(T) trailer;
protected:
	void init();
	int clear();
	void copyNodes(ListNodePosi(T) p, int n);
	void merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T)& q, int m);
	void mergeSort(ListNodePosi(T)& p, int n);
public:
	List() { init(); }
	List(List<T> const& L)
	{
		copyNodes(L.first(), L._size);
	}
	List(List<T> const& L, Rank r, int n)
	{
		copyNodes(L[r], n);
	}
	List(ListNodePosi(T) p, int n)
	{
		copyNodes(p, n);
	}
	~List()
	{
		clear();
		delete header;
		delete trailer;
	}
	Rank size() const { return _size; }
	bool empty() const { return _size <= 0; }
	T& operator[] (Rank r) const;
	ListNodePosi(T) first() const { return header->succ; }
	ListNodePosi(T) last() const { return trailer->pred; }
	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;
	ListNodePosi(T) find(T const& e) const
	{
		return find(e, _size, trailer);
	}
	ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;
	ListNodePosi(T) search(T const& e) const
	{
		return search(e, _size, trailer);
	}
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);
	ListNodePosi(T) selectMax() { return selectMax(header->succ, _size); }
	ListNodePosi(T) insertAsFirst(T const& e);
	ListNodePosi(T) insertAsLast(T const& e);
	ListNodePosi(T) insert(ListNodePosi(T) p, T const& e);
	ListNodePosi(T) insert(T const& e, ListNodePosi(T) p);
	T remove(ListNodePosi(T) p);
	void merge(List<T>& L) { merge(first(), _size, L, L.first(), L._size); }
	void sort(ListNodePosi(T) p, int n);
	void sort() { sort(first(), _size); }
	int deduplicate();
	int uniquify();
	void reverse();
};

template <typename T> 
void List<T>::init()
{
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer;
	header->pred = NULL;
	trailer->pred = header;
	trailer->succ = NULL;
	_size = 0;
}

template <typename T>
T& List<T>::operator[] (Rank r) const {
	ListNodePosi(T) p = first();
	while (0 < r--)
		p = p->succ;
	return p->data;
}

template <typename T>
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const {
	while (0 < n--)
		if (e == (p = p->pred)->data) return p;
	return NULL;
}

template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const& e)
{
	_size++; return header->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertAsLast(T const& e)
{
	_size++; return trailer->insertAsPred(e);
}

template <typename T>
ListNodePosi(T) List<T>::insert(ListNodePosi(T) p, T const& e)
{
	_size++; return p->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insert(T const& e, ListNodePosi(T) p)
{
	_size++; return p->insertAsPred(e);
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e)
{
	ListNodePosi(T) x = new ListNode(e, pred, this);
	pred->succ = x;
	pred = x;
	return x;
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e)
{
	ListNodePosi(T) x = new ListNode(e, this, succ);
	succ->pred = x;
	succ = x;
	return x;
}

template <typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n)
{
	init();
	while (n--) {
		insertAsLast(p->data); p = p->succ;
	}
}

template <typename T>
T List<T>::remove(ListNodePosi(T) p) {
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return e;
}

template <typename T>
int List<T>::clear()
{
	int oldSize = _size;
	while (0 < _size) remove(header->succ);
	return oldSize;
}

template <typename T>
int List<T>::deduplicate()
{
	if (_size < 2) return 0;
	int oldSize = _size;
	ListNodePosi(T) p = header;
	Rank r = 0;
	while (trailer != (p = p->succ)) {
		ListNodePosi(T) q = find(p->data, r, q);
		q ? remove(q) : r++;
	}
	return oldSize - _size;
}

template <typename T>
int List<T>::uniquify() {
	if (_size < 2) return 0;
	int oldSize = _size;
	ListNodePosi(T) p = first();
	ListNodePosi(T) q;
	while (trailer != (q = p->succ))
	{
		if (p->data != q->data) p = q;
		else remove(q);
	}
	return oldSize - _size;
}

template <typename T>
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const {
	while (0 < n--)
		if (((p = p->pred)->data) <= e) break;
	return p;
}

template <typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n)
{
	ListNodePosi(T) max = p;
	for (ListNodePosi(T) cur = p; 1 < n; n--)
	{
		if ((cur = cur->succ)->data > max->data)
			max = cur;
	}
	return max;
}

template <typename T>
void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T)& q, int m) {
	ListNodePosi(T) pp = p->pred;
	while (0 < m)
	{
		if ((0 < n) && (p->data <= q->data))
		{
			if (q == (p = p->succ))
			{
				break;
			}
			n--;
		}
		else
		{
			insert(L.remove((q = q->succ)->pred), p);
			m--;
		}
	}
	p = pp->succ;
}

template <typename T>
void List<T>::mergeSort(ListNodePosi(T)& p, int n)
{
	if (n < 2) return;
	int m = n >> 1;
	ListNodePosi(T) q = p;
	for (int i = 0; i < m; i++)
		q = q->succ;
	mergeSort(p, m);
	mergeSort(q, n - m);
	merge(p, m, *this, q, n - m);
}

template <typename T>
void List<T>::sort(ListNodePosi(T) p, int n) {
	mergeSort(p, n);
}

template <typename T>
void List<T>::reverse()
{
	int n = _size - 1;
	ListNodePosi(T) a = header->succ;
	ListNodePosi(T) b = trailer;
	ListNodePosi(T) c;
	for (int i = 0; i < n; i++)
	{
		c = a->succ;
		header->succ = c;
		c->pred = header;
		a->pred = b->pred;
		b->pred->succ = a;
		b->pred = a;
		a->succ = b;
		b = a;
		a = c;
	}
}
