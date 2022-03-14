#include<iostream>
#include<stack>
#include<string>
#include<math.h>
using namespace std;

	stack<float> vals;
	stack<char> oper;

	bool isDigit(char i){
		return (i>='0'&& i<='9');
	}

	float calculation(float prenum,float num,char oper){
		float result;
		switch(oper){
		case '+':
			return (prenum+num);
		case '-':
			return (prenum-num);
		case '*':
			return (prenum*num);
		case '/':
			return (prenum/num);
		default:
			return 0;

		}
	}

	int precedence(char oper){
		if(oper=='(')
			return 1;

		else if(oper=='+' || oper=='-')
			return 2;

		else return 3;
	}

	void postfixConverter(string s){
		float val=0;
		int temp=0;
		for(int i=0;i<s.length();i++){
		
			if(isDigit(s[i])){
				val=(val*10) +(s[i]-'0');
				if(i==(s.length()-1))
					vals.push(val);
				continue;
			}
			else if(s[i]=='('){
				oper.push(s[i]);
			}

			else if(s[i]==')'){
				vals.push(val);
				while(oper.top() !='('){
					float num=vals.top();vals.pop();
					float prenum=vals.top();vals.pop();
					char op=oper.top();oper.pop();
					float result=calculation(prenum,num,op);
					vals.push(result);
				}
				oper.pop();
				temp=1;// to prevent pushing values to stack vals where for example [ (5*2)+6 ] after ) we should enter charachter (+) not values 
				val=0;
			}

			else{
				if(temp==0)
					vals.push(val);
				else temp=0;

					while(!oper.empty() && ( precedence(s[i]) < precedence(oper.top()) )){
						float num=vals.top();vals.pop();
						float prenum=vals.top();vals.pop();
						char op=oper.top();oper.pop();
						float result=calculation(prenum,num,op);
						vals.push(result);
					}
						oper.push(s[i]);
				        val=0;
		 }
	 }
 }
	// perform the calculation after finishing filling the stacks
	float result(string statement){
		postfixConverter(statement);
		float val=0;
		while(vals.size()>1){
			float num=vals.top();vals.pop();
			float prenum=vals.top();vals.pop();
			char op=oper.top();oper.pop();
			float result=calculation(prenum,num,op);
			vals.push(result);	
		}
		float final=vals.top();
		vals.pop();
		return final;
	}

	// print the stacks
	void print(string statement){
		postfixConverter(statement);
		while(vals.size()>0){// print the stack of values
			cout<<vals.top()<<endl;
			vals.pop();
		}
		while(oper.size()>0){// print the stack of charachters
			cout<<oper.top()<<endl;
			oper.pop();
		}

	}

void main(){
	string statement;
	while(true){
	cout<<"enter statement"<<endl;
	cin>>statement;
	print(statement);
	cout<<"result is "<<result(statement)<<endl;
	}

	
}

