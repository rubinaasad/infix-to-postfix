// postfix expression.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<stdio.h>
#include<cstring>
#include<string>
#include<conio.h>

using namespace std;


struct ADT
{
	struct stack
	{
		int data;
		stack* next;
		stack()
		{
		data=0;
		next=0;
		}
	};
	typedef stack* stkptr;
	stkptr TOP;
	ADT()
	{
	TOP=0;
	}
	
	void push(int newData)
	{
	stack *ptr=new stack;
	ptr->next=TOP;
	TOP=ptr;
	TOP->data=newData;
	}
	int pop()
	{
		int topData;
		if(TOP==NULL)
		{
		return-1;
		}
		else
		{
			topData=TOP->data;
			TOP=TOP->next;
			return topData;
		}
	}
	
	int top()
	{
		if(TOP==NULL)
		{
			return -1;
		}
		else
		{
		return TOP->data;
		}
	}
	bool isempty()
	{
		if(TOP==0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

struct linklist
{
	struct node
	{
	char info;
	node* next;
	node()
	{
		info=0;
		next=0;
	}
	};
	typedef node* nodeptr;
	nodeptr pfirst,plast;
	linklist()
	{
		pfirst=0;
		plast=0;
	}

	void insert(char d)
	{
		nodeptr pnew=new node;
		pnew->info=d;
		pnew->next=0;
		if(pfirst==0)
		{
			pfirst=pnew;
			plast=pnew;
		}
		else
		{
			plast->next=pnew;
			plast=pnew;
		}
	}
	
	void traverse()
	{
		nodeptr temp=pfirst;
		while(temp!=0)
		{
			cout<<temp->info;
			temp=temp->next;
		}

	}

};

bool IsOperator(char ch)
{
	if(ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='$')
		return true;
	else
		return false;
}

bool IsRightAssociative(char op)
{
	if(op=='$')
		return true;
	else
		return false;
}
int GetOperatorWeight(char op)
{
	int weight=-1;
	switch(op)
	{
	case'+':
	case'-':
		weight=1;
	case'*':
	case'/':
		weight=2;
	case'$':
		weight=3;
	}
	return weight;
}
bool HasHigherPrecedence(char op1,char op2) 
{
	int op1Weight=GetOperatorWeight(op1);
	int op2Weight=GetOperatorWeight(op2);
	if(op1==op2)
	{
		if(IsRightAssociative(op1))
			return false;
		else
			return true;
	}
	return op1Weight>op2Weight ? true:false;
}

bool IsOperand(char ch)
{
	if(ch>='0' && ch<='9')
		return true;
	else if(ch>='a' && ch<='z')
		return true;
	else if(ch>='A' && ch<='Z')
		return true;
	else
		return false;
}

string conversion(string infix) 
{
	ADT S;
	string postfix="";
	for(int i=0;i<infix.length();i++)
	{
		if(infix[i]==' ' || infix[i]==',')
			continue;
		else if(IsOperator(infix[i]))
		{
			while(!S.isempty() && S.top()!='(' && HasHigherPrecedence(S.top(),infix[i]))
			{
				postfix+=S.top();
				S.pop();
			}
			S.push(infix[i]);
		}

		else if(IsOperand(infix[i]))
		{
			postfix+=infix[i];
		}
		else if(infix[i]=='(')
		{
			S.push(infix[i]);
		}
		else if(infix[i]=')')
		{
			while(!S.isempty() && S.top()!='(')
			{
				postfix+=S.top();
				S.pop();
			}
			S.pop();
		}
	}
	while(!S.isempty())
	{
		postfix+=S.top();
		S.pop();
	}
	return postfix;
}

int eval(int op1,int op2,char operator1)
{
	int result;
	switch(operator1)
	{
	case'*':
		result=op2*op1;
		break;
	case'/':
		result=op2/op1;
		break;
	case'+': 
		result=op2+op1;
		break;
	case'-':
		result=op2-op1;
		break;
	default:
		return 0;
	}
	return result;
}

int cal_postfix(string postfix)
{
	ADT S;
	int value;
	char ch;
	int i=0;
	while(i<postfix.length())
	{
		ch=postfix[i];
		if(isdigit(ch))
		{
			S.push(ch-'0');
		}
		else if(IsOperator(postfix[i]))
		{
			int op1=S.top();
			S.pop();
			int op2=S.top();
			S.pop();
			value=eval(op1,op2,ch);
			S.push(value);
		}
		i++;
	}
	return value;
}

char sFileName[50]="D:\\infix.txt";
string readfile()
{
	string str;
	fstream f;
	f.open(sFileName,ios::in);
	if(f.is_open()==false)
	{
		cout<<"unable to open file..." <<endl;
	}
	else
	{
		while(getline(f,str,'\n'))
		{
			cout<<str <<endl;
		}
	}

		f.close();
		return str;
	
}

linklist add_list(string infix)
{
	linklist l1;
	for(int i=0;i<infix.length();i++)
	{
		l1.insert(infix[i]);
	}

	l1.traverse();
	return l1;
}



int _tmain(int argc, _TCHAR* argv[])
{
	cout<<"Expression read from file: " <<endl;
	string infix=readfile();

	cout<<"Infix Expression stored in Linked List:" <<endl;
	linklist infixlist=add_list(infix);

	string postfix=conversion(infix);
	cout<<"\nPostfix Expression stored in Linked List:" <<endl;
	linklist postfixlist=add_list(postfix);

	int result=cal_postfix(postfix);
	cout<<"\nThe result is " <<result <<endl;
	system("pause");
	return 0;
}

