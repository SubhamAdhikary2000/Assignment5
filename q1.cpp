#include <iostream>
#include <stack>
#include <string>
using namespace std;
class Expr
{
    private:
    string expression;
    //Function to check the precedence of operators
    int priority(char ch)
    {
        if(ch=='^')
        {
            return 3;
        }
        else if(ch=='*'||ch=='/')
        {
            return 2;
        }
        else
        {
            return 1;
        }

    }
    int solve(int val1,int val2,char ch)
    {
        if(ch=='+')
        {
            return val1+val2;
        }
        else if(ch=='-')
        {
            return val1-val2;
        }
        else if(ch=='*')
        {
            return val1*val2;
        }
        else if(ch=='^')
        {
            return val1^val2;
        }
        else
        {
            return val1/val2;
        }
    }
    int EvaluateExpression(const string& s)
    {
       //We need two stacks,1 for values,1 for operators
       stack<int>val;
       stack<char>op;
       for(int i=0;i<s.length();i++)
       {
           //check if s[i] is a digit(0 to 9) by ascii value
           if(s[i]>=48 && s[i]<=57)
           {
               //but we have to push the no
               val.push(s[i]-48);
           }
           else
           {
               //If s[i] is an operator
               if(op.size()==0||priority(s[i])>priority(op.top()))
               {
                   /*
                     stack is empty or priority of the operator of s[i]
                     is greater than the operator present at the top of the stack
                     then push.
                   */
                   op.push(s[i]);
               }
               else
               {
                   /*
                     priority of the operator of s[i]
                     is less than or equal to the operator present at the top of the stack
                   */
                   while(op.size()>0 && priority(s[i])<=priority(op.top()))
                   {
                       //I have to val1 op val2
                       char ch=op.top();
                       op.pop();
                       int val2=val.top();
                       val.pop();
                       int val1=val.top();
                       val.pop();
                       int ans=solve(val1,val2,ch);
                       val.push(ans);
                   }
                   op.push(s[i]);
               }


           }
       }
       //The operator stack can still have values,so make it empty
       while(op.size()>0)
       {
           char ch=op.top();
           op.pop();
           int val2=val.top();
           val.pop();
           int val1=val.top();
           val.pop();
           int ans=solve(val1,val2,ch);
           val.push(ans);
       }
       return val.top();
    }
    public:
    //constructor
    Expr(const char* expr):expression(expr)
    {

    }
    int eval()
    {
        return EvaluateExpression(expression);
    }
    void print()
    {
        cout<<"Expression: "<<expression<<endl;
    }
};
int main()
{
    Expr x("8/4+3*4-3");
    cout << "x = " << x.eval() << "\n";
    x.print();
}

