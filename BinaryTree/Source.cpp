#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor: \t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		this->Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			insert(*it, this->Root);
		}
	}
	~Tree()
	{
		clear(Root);
		cout << "Tdestructor:\t" << this << endl;
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, this->Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int count()const
	{
		return count(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	double avg()const
	{
		return (double)sum(Root) / count(Root);
	}
	void print()const
	{
		print(this->Root);
		cout << endl;
	}
private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			return;
		}
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight)insert(Data, Root->pRight);
			else Root->pRight = new Element(Data);
		}
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == nullptr && Root->pRight == nullptr)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	int minValue(Element* Root)const
	{
		if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int count(Element* Root)const
	{
		if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;
	}
	int sum(Element* Root)const
	{
		return Root == nullptr ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве:" << tree.maxValue() << endl;
	cout << "Количество элементов в дереве" << tree.count() << endl;
	cout << "Сумма элементов дерева:" << tree.sum() << endl;
	cout << "Среднее арифметическое элементов дерева: " << tree.avg() << endl;
#endif // BASE_CHECK

	Tree tree = { 50,25,80,16,32,64,85,58,75,84,91 };
	tree.print();
	int value;
	cout << "Введите элемент, который хотите удалить:"; cin >> value;
	tree.erase(value);
	tree.print();
}

/*

Бинарное дерево - это структура данных, каждый элемент которой имеет два потомка: левый и правый.
Как и у любого другого дерева у бинарного дерева есть корень (root), который содержит указатель на корневой элемент дерева.
Зайти в дерево можно только через корень. 
Когда дерево пустое корень указывает на ноль, в противном случае корень указывает на нулевой элемент.
Узлы, не имеющие потомков называют листьями. 
Узел, у которого есть потомки является обычным узлом, но также является корневым элементом поддерева в основном дереве.
Бинарное дерево может быть и вырожденным. 
В выражденном дереве есть только одна ветка: левая либо правая.
Вырожденное бинарное дерево по своим свойствам напоминает односвязный список
Существует множество разных деревьев, но мы будем рассматривать бинарное дерево поиска.
Особенность этого дерева состоит в том, что оно осуществляет очень быстрый поиск элементов.
В идеально сбалансированном бинарном дереве из тысячи элементов любой элемент можно найти за максимум 10 итераций.
*/