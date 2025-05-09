// Source : https://oj.leetcode.com/problems/valid-parentheses/
// Author : Hao Chen
// Date   : 2014-06-30

/********************************************************************************** 
* 
* Given a string containing just the characters '(', ')', '{', '}', '[' and ']', 
* determine if the input string is valid.
* 
* The brackets must close in the correct order, "()" and "()[]{}" are all valid 
* but "(]" and "([)]" are not.
* 
*               
**********************************************************************************/

// compile command
// g++ -o hi 0020-validParentheses.cpp 


/*
#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool isValid(string s) {
    stack<char> st;
    for(auto ch : s) {
        if (ch=='{' || ch =='[' || ch=='(' ) {
            st.push(ch);
        }else if (ch=='}' || ch ==']' || ch == ')' ){
            if (st.empty()) return false;
            char sch = st.top();
            if ( (sch=='{' && ch =='}') || (sch=='[' && ch==']') || (sch=='(' && ch==')' ) ){
                st.pop();
            }else {
                return false;
            }
        }else{
            return false;
        }
    }
    return st.empty();
}

int main(int argc, char**argv)
{
    string s = "{{}{[]()}}";
    if (argc>1){
        s = argv[1];
    }
    cout << "str = \"" << (s) << "\"" << endl;
    cout << isValid(s) << endl;
}
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// checks if parenthesis of types (){}[] have appropriate pairing
bool pMatch(string s) {
    if(s == "") return true;
    
    // one pointer movew from front and one from back
    int head = -1;
    int tail = s.length();

    
    // step through string, verifying with each encountered paren 
    // there is a closing paren
    while(head < tail){
        // find next paren opener (if it exists)
        while(true){
            head++;
            //cout << "head: " << head << endl;
            if(head >= tail) return true;
            
            // is this a parenthesis opener?
            if(s[head] == '(') break;
            if(s[head] == '{') break;
            if(s[head] == '[') break;
            
            // report if unexpected closer is found
            if(s[head] == ')') return false;
            if(s[head] == '}') return false;
            if(s[head] == ']') return false;
        }
        
        // find next paren closer
        // report if unexpected opener is found
        while(true){
            tail--;
            //cout << "tail: " << tail << endl;
            if(head >= tail) return false;
            
            // is this the next parenthesis closer?
            if(s[tail] == ')') {
                if(s[head] == '(') break;
                return false;
            }
            if(s[tail] == '}') {
                if(s[head] == '{') break;
                return false;
            }
            if(s[tail] == ']') {
                if(s[head] == '[') break;
                return false;
            }
            
            
            
            // check if we are passing over a parenthesis item that indicates their partner is missing 
            if(s[tail] == '(') return false;
            if(s[tail] == '{') return false;
            if(s[tail] == '[') return false;
        }
    }
    return true;
}

// checks if expected result, prints result
void test(string s, bool expected){
    bool result = pMatch(s) == expected;
    if(result) cout << "PASS" << endl;
    else cout << "FAILED: " << s << endl;
}

int main() {
    // run all the test cases

    test("", true);
    test("hi", true);
    test("(", false);
    test(")", false);
    test("()", true);
    test("aa ()", true);
    test(" (aa)bb", true);
    test("jlkjf ({[]})", true);
    test("[{}])", false);

    return 0;
}

