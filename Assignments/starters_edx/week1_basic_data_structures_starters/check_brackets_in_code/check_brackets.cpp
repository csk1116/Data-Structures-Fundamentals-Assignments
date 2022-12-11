#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

struct Bracket
{
    Bracket(char type, int position) : type(type), position(position)
    { 
    }

    bool Matchc(char c)
    {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

class Solution
{
public:
    int checkBrackets(string text)
    {
        int unmatched = 0;
        stack<Bracket> opening_brackets_stack;
        for (int position = 0; position < text.length(); ++position)
        {
            char next = text[position];

            if (next == '(' || next == '[' || next == '{')
            {
                // Process opening bracket, write your code here
                opening_brackets_stack.push(Bracket(next, position));
            }

            if (next == ')' || next == ']' || next == '}')
            {
                // Process closing bracket, write your code here
                if (!opening_brackets_stack.empty() && opening_brackets_stack.top().Matchc(next))
                {
                    opening_brackets_stack.pop();
                }
                else
                {
                    unmatched = position + 1;
                    break;
                }
            }
        }

        if (opening_brackets_stack.empty() && unmatched == 0)
            return 0;
        else if (unmatched != 0)
            return unmatched;
        else
            return opening_brackets_stack.top().position + 1;
    }
};

void testAllAndCheckAnswer(int testcase)
{
    string path = "C:/Users/CSK/git/UCSanDiegoX-ALGS201x-Data-Structures-Fundamentals-Assignments/Assignments/starters_edx/week1_basic_data_structures_starters/check_brackets_in_code/tests/";
    ifstream myTestFile;
    ifstream myAnswerFile;
    stringstream ss;
    Solution mySolution;
    string testString = "";
    string answerString = "";
    string myAnswer = "";
    int count = 1;

    while(count <= testcase)
    {
        ss << setfill('0') << setw(2) << to_string(count);
        string testFileName = path + ss.str();
        //cout << testFileName << endl;
        myTestFile.open(testFileName);
        string answerFileName = path + ss.str() + ".a";
        myAnswerFile.open(answerFileName);

        ss.str("");

        if(myTestFile.is_open() && myAnswerFile.is_open())
        {            
            while(myTestFile)
                myTestFile >> testString;       
            while(myAnswerFile)     
                myAnswerFile >> answerString;

            myTestFile.close();
            myAnswerFile.close();
        }

        //cout << answerString << endl;
        //cout << testString << endl;

        int result = mySolution.checkBrackets(testString);
        if(result == 0)
            myAnswer = "Success";
        else
            myAnswer = to_string(result);
        
        //cout << myAnswer << endl;

        if(myAnswer == answerString)
            count ++;
        else
            break;
    }

    if(count > testcase)
        cout << "Pass" << endl;
    else
        cout << "fail at: " << count << endl;   

}

int main()
{
    std::string text;
    getline(std::cin, text);


    // Printing answer, write your code here
    Solution mySolution;
    int result = mySolution.checkBrackets(text);
    if(result == 0)
        cout << "Success" << endl;
    else
        cout << result << endl;

    testAllAndCheckAnswer(54);
    
    return 0;
}
