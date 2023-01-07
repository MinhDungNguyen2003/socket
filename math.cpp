#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>
#include <sstream>

using namespace std;

bool check_bracket(char inp[]) {

    stack<char> s;
    int i = 0;
    while (inp[i] != '\0') {

        if (inp[i] == '(') {
            s.push(inp[i]);
        }

        if (inp[i] == ')') {
            if (s.empty()) {
                return 0;
            }
            s.pop();
        }

        i++;
    }

    if (!s.empty()) {
        return 0;
    }
    return 1;

}

bool check_operator(char inp[]) {

    int i = 0;
    if (inp[i] == '+' || inp[i] == '-' || inp[i] == '*' || inp[i] == '/') {
        return 0;
    }

    stack<char> s;
    
    while (inp[i] != '\0') {
        
        if (inp[i] != '(' && inp[i] != ')' && inp[i] != '+' && inp[i] != '-' && inp[i] != '*' && inp[i] != '/' && inp[i] != ' ') {
            s.push(inp[i]);
            i++;
        }
        else if (inp[i] == '+' || inp[i] == '-' || inp[i] == '*' || inp[i] == '/') {
            if (s.top() == '+' || s.top() == '-' || s.top() == '*' || s.top() == '/'){
                return 0;
            }
            s.push(inp[i]);
            i++;
        }
        else {
            i++;
        }
        

    }

    return 1;

}

int postfix(char inp[]) {

    stack<char> s;
    queue<char> q;

    int i = 0;
     
    while (inp[i] != '\0') {

        if (inp[i] != '(' && inp[i] != ')' && inp[i] != '+' && inp[i] != '-' && inp[i] != '*' && inp[i] != '/' && inp[i] != ' ') {
            q.push(inp[i]);
        }

        if (inp[i] == '+' || inp[i] == '-' || inp[i] == '*' || inp[i] == '/') {

            if (s.empty()) {
                q.push(' ');
                s.push(inp[i]);
            }
            else if (s.top() == '(') {
                q.push(' ');
                s.push(inp[i]);
            }
            else if (s.top() == '+' || s.top() == '-') {

                if (inp[i] == '*' || inp[i] == '/') {
                    q.push(' ');
                    s.push(inp[i]);
                }

                if (inp[i] == '+' || inp[i] == '-') {
                  
                    while (!s.empty()) {
                        if (s.top() == '(') {
                            break;
                        }
                 
                        q.push(' ');
                        q.push(s.top());
                        q.push(' ');
                        s.pop();
                    }
                    s.push(' ');
                    s.push(inp[i]);
                }

            }
            else if (s.top() == '*' || s.top() == '/') {

                while (!s.empty()) {
                    if (s.top() == '(') {
                        break;
                    }
                    q.push(' ');
                    q.push(s.top());
                    q.push(' ');
                    s.pop();
                }
                s.push(inp[i]);
                   
        
            }

        }

        if (inp[i] == '(') {
            s.push(inp[i]);
        }

        if (inp[i] == ')') {

            char ch = s.top();
            s.pop();
            while (ch != '(') {
                q.push(' ');
                q.push(ch);
                ch = s.top();
                s.pop();
            }
            
        }

        i++;
    }

    while (!s.empty()) {
        q.push(' ');
        q.push(s.top());
        s.pop();
    }

    string k;

    while (!q.empty()) {
        k += q.front();
        q.pop();
    }

    stack<int> s1;
    
    for (int i = 0; i < k.size(); i++) {
        

        if (k[i] == ' ') continue;

        else if (isdigit(k[i]))
        {
            int num = 0;

            //extract full number
            while (isdigit(k[i]))
            {
                num = num * 10 + (int)(k[i] - '0');
                i++;
            }
            i--;

            s1.push(num);
            
        }
        else
        {
            int val1 = s1.top(); s1.pop();

            int val2 = s1.top(); s1.pop();

            switch (k[i])
            {
            case '+': s1.push(val2 + val1); break;
            case '-': s1.push(val2 - val1); break;
            case '*': s1.push(val2 * val1); break;
            case '/': s1.push(val2 / val1); break;

            }
        }

    }
    
    return s1.top();

}




int main() {

    char inp[2000];
    cin.getline(inp, sizeof(inp));
    if (check_bracket(inp) == 1 && check_operator(inp) == 1) {
        cout << postfix(inp);
    }
    else {
        cout << "Invalid mathematical expression ";
    }

    return 0;
}
