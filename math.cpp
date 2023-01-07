#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>
#include <sstream>

using namespace std;

bool check_bracket(char inp[]){

    stack<char> s;   
    int i = 0;
    while(inp[i] != '\0'){
        
        if(inp[i] == '('){
            s.push(inp[i]);
        }
        
        if(inp[i] == ')'){
            if(s.empty()){
                return 0;
            }
            s.pop();
        }

        i++;
    }

    if(!s.empty()){
        return 0;
    }
    return 1;

}

int postfix(char inp[]){

    stack<char> s;
    queue<char> q;
    int i = 0;
    while(inp[i] != '\0'){

        if(inp[i] != '(' && inp[i] != ')' && inp[i] != '+' && inp[i] != '-' && inp[i] != '*' && inp[i] != '/' && inp[i] != ' '){
            q.push(inp[i]);
        }
        
        if(inp[i] == '+' || inp[i] == '-' || inp[i] == '*' || inp[i] == '/'){

            if (s.empty()){
                s.push(inp[i]);
            }        
            else if(s.top() == '('){
                s.push(inp[i]);
            }
            else if(s.top() == '+' || s.top() == '-'){

                if(inp[i] == '*' || inp[i] == '/'){
                    s.push(inp[i]);
                }

                if(inp[i] == '+' || inp[i] == '-'){
                    while(!s.empty()){
                        if(s.top() == '('){
                            break;
                        }
                        q.push(s.top());
                        s.pop();
                   }
                    s.push(inp[i]);
                }
            
            }
            else if(s.top() == '*' || s.top() == '/'){
                if(inp[i] == '+' || inp[i] == '-'){
                    s.push(inp[i]);
                }

                if(inp[i] == '*' || inp[i] == '/'){
                    while(!s.empty()){
                        if(s.top() == '('){
                            break;
                        }
                        q.push(s.top());
                        s.pop();
                   }
                    s.push(inp[i]);
                }

            }
            

        }

        if(inp[i] == '('){
            s.push(inp[i]);
        }

        if(inp[i] == ')'){
            
            char ch = s.top();
            s.pop();
            while(ch != '('){
                q.push(ch);
                ch = s.top();
                s.pop();
            }
        }
        i++;
    }

    while(!s.empty()){
        q.push(s.top());
        s.pop();
    }
    
    stack<string> s1;
    queue<string> q1;

    while(!q.empty()){
        string k;
        stringstream ss;
        ss << q.front();
        ss >> k;
        q.pop();
        q1.push(k);
    }


    int result = 0;


    while(!q1.empty()){

        string ch = q1.front();
        q1.pop();
        
        if(ch != "+" && ch != "-" && ch != "*" && ch != "/"){
            s1.push(ch);
        }   
        else if(ch == "+" || ch == "-" || ch == "*" || ch == "/"){

            if(ch == "+"){
                
                string ch1 = s1.top();
                cout << ch1;
                stringstream ss;
                int number1;
                ss << ch1;
                ss >> number1;
                
                s1.pop();
                
                string ch2 = s1.top();
                int number2 = stoi(ch2);
                s1.pop();

                result = number1 + number2;
                string ch3 = to_string(result);
                s1.push(ch3);                
                
            }
        }        

    }

    return result;

}


int main(){

    char inp[2000];
    cin.getline(inp, sizeof(inp));
    postfix(inp);   

    return 0;
}
