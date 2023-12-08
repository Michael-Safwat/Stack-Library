#include<iostream>	
#include<string>
#include<cmath>
#define SIZE 4
using namespace std;


class Stack
{
private:
	int* arr{};
	int top{};
	int size{};

public:
	Stack(int size) :size(size),top(-1) //O(N)time O(N)memory
	{
		arr = new int[size];
	}
	int get_size()
	{
		return size;
	}
	int get_top()
	{
		return top;
	}

	bool is_full() //O(1)time O(1)memory
	{
		if (top == size - 1)
			return true;
		return false;
	}
	bool is_empty() //O(1)time O(1)memory
	{
		if (top == -1)
			return true;
		return false;
	}

	bool push(int data) //O(1)time O(1)memory
	{
		if(!is_full())	
		{
			arr[++top] = data;
			return true;
		}
		return false;
	}
	int pop() //O(1)time O(1)memory
	{
		if (!is_empty())
		{
			return arr[top--];
		}
	}
	int peek() //O(1)time O(1)memory
	{
		if (!is_empty())
			return arr[top];
	}

	void display() //O(N)time O(1)memory	
	{
		cout << "[ ";
		for (int i = top; i >= 0; i--)
		{
			cout << arr[i];
			if (i - 1 >= 0)
				cout << " , ";
		}
		cout << " ]";
	}
	void display_reversed() //O(N)time O(1)memory	
	{
		cout << "[ ";
		for (int i = 0; i <= top; i++)
		{
			cout << arr[i];
			if (i + 1 <= top)
				cout << " , ";
		}
		cout << " ]";
	}

	void insert_at_bottom(int data) //O(N)time O(1)memory
	{
		if (is_empty())
			push(data);
		else
		{
			int current = pop();
			insert_at_bottom(data);
			push(current);
		}
	}
	void reverse() //O(N^2)time O(1)memory
	{
		int result = pop();

		if (is_empty())
		{
			push(result);
			return;
		}
		
		reverse();
		insert_at_bottom(result);
	}
};

string direction(int asteriod)
{
	if (asteriod < 0)
		return "left";
	else
		return "right";
}
void asteriod_collision(int* arr,int size)
{
	Stack st(size);
	int top{}, asteriod{};
	
	for (int i = 0; i < size; i++)
	{
		asteriod = arr[i];
		if (st.is_empty() || direction(st.peek()) == "left" || direction(st.peek()) == direction(asteriod))
			st.push(asteriod);
		else
		{
			bool exploded = false;
			while (!st.is_empty())
			{
				top = st.peek();

				if (-asteriod > top)
					st.pop();
				else if (-asteriod == top)
				{
					st.pop();
					exploded = true;
					break;
				}
				else
				{
					exploded = true;
					break;
				}		
			}
			if (!exploded)
				st.push(asteriod);
		}
	}
	st.display_reversed();
}

string reverse_subwords(const string& line)
{
	Stack st(line.length());
	for (int i = 0; i < line.length(); i++)
	{
		st.push(line[i]);
	}

	string result;

	for (int i = 0; i < st.get_size(); i++)
	{
		result+=st.pop();
	}

	return result;
}

int reverse_num(int num)
{
	if (num < 10)
		return num;

	int size = 1;
	for (int i = 1; num / i > 1; i *= 10)
		size++;
	
	Stack st(size);
	
	int result = 0;

	for(int i=0;i<size;i++)
	{
		st.push(num % 10);
		num /= 10;
		result = result * 10 + st.pop();
	}

	return result;
}

char get_char(char c)
{
	if (c == ')')
		return '(';
	else if (c == '}')
		return '{';
	else 
		return '[';
}
bool is_valid(string str)
{
	Stack st(str.length());

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '(' || str[i] == '{' || str[i] == '[')
			st.push(str[i]);
		else if (!st.is_empty() && st.peek() == get_char(str[i]))
			st.pop();
		else
			return false;
	}
	if (st.is_empty())
		return true;
}

string removeDuplicates(string s)
{
	Stack st(s.length());

	for (int i = 0; i < s.length(); i++)
	{
		if (!st.is_empty() && s[i] == st.peek())
			st.pop();
		else
			st.push(s[i]);
	}

	string result;
	while (!st.is_empty())
	{
		result = char(st.pop()) + result;
	}

	return result;
}

int ScoreOfParantheses(string str)
{
	Stack st((int)str.length());

	for (int i = 0; i < (int)str.length(); i++)
	{
		if (str[i] == '(')
			st.push(0);
		else if(str[i]==')')
		{
			if (st.peek() == 0)
			{
				st.pop();
				st.push(1);
			}
			else
			{
				int sum = 0;

				while (st.peek() != 0)
				{
					sum += st.pop();
				}
				sum *= 2;
				st.pop();
				st.push(sum);
			}
		}
	}

	int sum = 0;
	while (!st.is_empty())
	{
		sum += st.pop();
	}
	return sum;
}

int precedence(char oper) //O(1)time O(1)memory
{
	if (oper == '+' || oper == '-')
		return 1;
	else if (oper == '*' || oper == '/')
		return 2;
	else
		return 0;
}

string infix_to_posfix(string infix) //O(N)time O(1)memory
{
	char token;
	infix += '-';
	string postfix = "";
	Stack operators((int)infix.size());
	operators.push('#');

	for (int i = 0; i < (int)infix.size(); i++)
	{
		token = infix[i];
		if (isdigit(token))
			postfix += token;
		else
		{
			while (precedence(operators.peek()) >= precedence(token))
				postfix += operators.pop();

			operators.push(token);
		}
	}

	return postfix;
}

int main(void)
{
	/*Stack stk(10);
	stk.display();

	stk.push(1);
	stk.push(2);
	stk.push(3);
	stk.push(4);

	stk.display();*/

	/*string line;
	cout << "Enter words: ";
	getline(cin, line);

	cout<<reverse_subwords(line);*/

	/*int num = 1234;
	cout << reverse_num(num);*/

	/*string str = "(])[";
	cout << is_valid(str);*/

	/*string str = "abbaca";
	cout << removeDuplicates(str);*/

	/*int arr[SIZE] = { -2,-1,1,2};
	asteriod_collision(arr, SIZE);*/

	/*Stack st(5);
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);
	st.insert_at_bottom(5);
	st.display();*/

	//Stack st(5);
	//st.push(1);
	//st.push(2);
	//st.push(3);
	//st.push(4);
	//*st.push(5);
	//st.display();
	//st.reverse();
	//cout << "\n";
	//st.display();
	
	/*string str;
	cout << "Enter string: ";
	cin >> str;

	cout << ScoreOfParantheses(str);*/

	string infix = "2+3*4-5*6+7";
	cout << infix_to_posfix(infix);


	return 0;
}