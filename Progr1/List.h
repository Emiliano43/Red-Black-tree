template<typename T>
class List
{
private:
	class Node
	{
	private:
		T value;
		Node* next, *prev;
	public:
		Node() : next(NULL), prev(NULL) {};
		Node(T value) {
			this->value = value;
			next = NULL;
			prev = NULL;
		}
		~Node() {
			next = NULL;
			prev = NULL;
		}
		void set_value(T value) {
			this->value = value;
		}
		T get_value() {
			return value;
		}
		Node* get_next() {
			return next;
		}
		Node* get_prev() {
			return prev;
		}
		void set_next(Node* pointer) {
			next = pointer;
		}
		void set_prev(Node* pointer) {
			prev = pointer;
		}
	};
	Node *head, *tail;
	Node* get_pointer(size_t index)
	{
		if (isEmpty() || (index > get_size() - 1))
		{
			throw out_of_range("Invalid argument");
		}
		else if (index == get_size() - 1)
			return tail;
		else if (index == 0)
			return head;
		else
		{
			Node* cur = head;
			while ((cur) && (index--))
			{
				cur = cur->get_next();
			}
			return cur;
		}
	}
public:
	List() : head(NULL), tail(NULL) {}
	List(const List<T>& list) {
		clear();
		Node* cur = list.head;
		while (cur) {
			push_back(cur->get_value());
			cur = cur->get_next();
		}
	}
	~List()
	{
		while (head)
		{
			tail = head->get_next();
			delete head;
			head = tail;
		}
		head = NULL;
	}
	void push_back(T value)
	{
		Node* cur = new Node;
		cur->set_value(value);
		if (head)
		{
			cur->set_prev(tail);
			tail->set_next(cur);
			tail = cur;
		}
		else
		{
			head = cur;
			tail = head;
		}
	}
	void push_front(T value)
	{
		Node* cur = new Node;
		cur->set_value(value);
		if (head)
		{
			cur->set_next(head);
			head->set_prev(cur);
			head = cur;
		}
		else
		{
			head = cur;
			tail = head;
		}
	}
	void push_front(List& ls2)
	{
		Node* cur = ls2.tail;
		size_t n = ls2.get_size();
		while ((cur) && (n--))
		{
			push_front(cur->get_value());
			cur = cur->get_prev();
		}
	}
	void pop_back()
	{
		if (head != tail)
		{
			Node* cur = tail;
			tail = tail->get_prev();
			tail->set_next(NULL);
			delete cur;
		}
		else if (!isEmpty())
		{
			Node* cur = tail;
			tail = head = NULL;
			delete cur;
		}
		else
			throw out_of_range("The list is empty");
	}
	void pop_front()
	{
		if (head != tail)
		{
			Node* cur = head;
			head = head->get_next();
			head->set_prev(NULL);
			delete cur;
		}
		else if (!isEmpty())
		{
			Node* cur = head;
			head = tail = NULL;
			delete cur;
		}
		else
			throw out_of_range("The list is empty");
	}
	void insert(size_t index, T value)
	{
		Node* cur;
		cur = get_pointer(index);
		if (cur == head)
			push_front(value);
		else
		{
			Node* newElem = new Node;
			newElem->set_value(value);
			cur->get_prev()->set_next(newElem);
			newElem->set_prev(cur->get_prev());
			newElem->set_next(cur);
			cur->set_prev(newElem);
		}
	}
	T at(size_t index)
	{
		Node* cur;
		cur = get_pointer(index);
		return cur->get_value();
	}
	void remove(size_t index)
	{
		Node* cur;
		cur = get_pointer(index);
		if (cur == head)
			pop_front();
		else if (cur == tail)
			pop_back();
		else
		{
			cur->get_prev()->set_next(cur->get_next());
			cur->get_next()->set_prev(cur->get_prev());
			delete cur;
		}
	}
	void remove(T value) {
		Node* cur = head;
		while (cur && cur->get_value() != value)
			cur = cur->get_next();
		if (!cur)
			throw out_of_range("Invalid argument");
		if (cur == head)
			pop_front();
		else if (cur == tail)
			pop_back();
		else
		{
			cur->get_prev()->set_next(cur->get_next());
			cur->get_next()->set_prev(cur->get_prev());
			delete cur;
		}
	}
	size_t get_size()
	{
		Node* cur = head;
		size_t length = 0;
		while (cur)
		{
			length++;
			cur = cur->get_next();
		}
		return length;
	}
	void print_to_console()
	{
		Node* cur = head;
		while (cur)
		{
			cout << cur->get_value() << ' ';
			cur = cur->get_next();
		}
		cout << endl;
	}
	void clear()
	{
		while (head)
		{
			tail = head->get_next();
			delete head;
			head = tail;
		}
	}
	void set(size_t index, T value)
	{
		Node* cur;
		cur = get_pointer(index);
		cur->set_value(value);
	}
	bool isEmpty()
	{
		if (!head)
			return true;
		else
			return false;
	}
};
