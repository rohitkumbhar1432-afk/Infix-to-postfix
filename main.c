#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define max 100
int check_expresion(char *infix);
int is_operator(char ch);
void infix_postfix(char*infix,char*postfix);
int top=-1;
char stack[max];
int precedence(char ch);
int main()
{
	char infix[max],postfix[max]={0};
	printf("enter statement\n");
	fgets(infix,max,stdin);
	if(infix[strlen(infix)-1]=='\n')
	{
		infix[strlen(infix)-1]='\0';
	}
	infix_postfix(infix,postfix);
	printf("%s\n",postfix);
}
char pop()
{
	int temp;
	temp=stack[top];
	top--;
	return temp;
}
int peek()
{
	return(stack[top]);
}
void push(char ch)
{
	if(top==(max-1))
	{
		printf("stack is full\n");
	}
	else
	{
		stack[++top]=ch;
	}
}
int check_expresion(char *infix)
{
	int i,j;
	char ch;
	for(i=0;infix[i]!='\0';i++)
	{
		ch=infix[i];
		if(ch=='{'||ch=='['||ch=='(')
			push(ch);
		else if(ch=='}')
		{
			if(pop()!='{')
				break;
		}else if(ch==']')
		{
			if(pop()!='[')
				break;
		}
		else if(ch==')')
		{
			if(pop()!='(')
				break;
		}
	}
	if(infix[i]=='\0'&&top==-1)
	{
		return 1;
	}
	else
	return 0;
}
char ischar(char ch)
{
	if((ch>=65&&ch<=90)||(ch>=97&&ch<=122)||(ch>=48&&ch<=57))
	{
		return 1;
	}
	else
	return 0;
}
void infix_postfix(char*infix,char*postfix)
{
	int i=0,j=0;
	char ch;
	if((check_expresion(infix))==1)
	{
		for(i=0;infix[i]!='\0';i++)
		{
			ch=infix[i];
			if(ischar(ch)==1)
			{
				postfix[j++]=ch;
			}
			else if(ch=='['||ch=='{'||ch=='(')
			{
				push(ch);
			}
			else if((is_operator(ch))==1)
			{
				if(top==-1)
				{
					push(ch);
				}
				else if((is_operator(stack[top]))==0)
				{
					push(ch);
				}
				else 
				{
					if((precedence(stack[top]))>=(precedence(ch)))
					{
						postfix[j++]=pop();
						push(ch);	
					}
					else 
					{
						push(ch);
					}
				}
			}
			else if(ch==')')
			{
				while(stack[top]!='(')
				{
					postfix[j++]=pop();
				}
				pop();
			}
			else if(ch=='}')
			{
				while(stack[top]!='{')
				{
					postfix[j++]=pop();
				}
				pop();
			}
			else if(ch==']')
			{
				while(stack[top]!='[')
				{
					postfix[j++]=pop();
				}
				pop();
			}
		}
		if(top!=-1)
		{
			for(int i=top;i!=-1;i--)
			{
				postfix[j++]=pop();
			}
		}
	}
}
int is_operator(char ch)
{
	if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^')
	{
		return 1;
	}
	else 
		return 0;
}

int precedence(char ch)
{
	if(ch=='^')
		return 3;
	else if(ch=='*'||ch=='/')
		return 2;
	else if(ch=='+'||ch=='-')
		return 1;
	
}
