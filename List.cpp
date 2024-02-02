#include"List.hpp"

int main()
{
	List<char> L1;
	int N;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		char data;
		cin >> data;
		L1.insertAsLast(data);
	}
	cout << L1.selectMax()->data << endl;
	L1.reverse();
	for (int i = 0; i < N; i++)
	{
		cout << L1[i] << endl;
	}
	List<char> L2 = L1;
	L2.sort();
	for (int i = 0; i < N; i++)
	{
		cout << L2[i] << endl;
	}
}