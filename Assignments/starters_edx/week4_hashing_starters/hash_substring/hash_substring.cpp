#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef long long ll;

struct Data
{
    string pattern, text;
};

class RabinKarpAlgo
{
public:
    std::vector<int> get_occurrences(const Data &input)
    {
        std::vector<int> result;
        patternLen = input.pattern.length();
        textLen = input.text.length();
        patternHash = hash_func(input.pattern);
        textHash = hash_func(input.text.substr(textLen - patternLen, textLen));
        h = getH(input.pattern.length());
        //std::cout << h << std::endl;


        for(int i = textLen - patternLen; i >= 0; i--)
        {
            //std::cout << textHash << " " << patternHash << std::endl;
            if(textHash == patternHash)
            {
                if(checkEqual(input.text, input.pattern, i, patternLen))
                    result.push_back(i);
            }
            //std::cout << textHash * multiplier << std::endl;
            //std::cout << input.text[i-1] - h * input.text[i+patternLen-1] << std::endl;
            textHash = (multiplier * textHash + input.text[i-1] - 'A' - h * (input.text[i+patternLen-1] - 'A')) % prime;
            if(textHash < 0)
                textHash = (textHash + prime) % prime;
        }
        return result;
    }
private:
    static const int prime = 1000000007;
    static const int multiplier = 3;
    int patternLen;
    int textLen;
    ll patternHash;
    ll textHash;
    ll h;

    int hash_func(const string &s) const
    {
        //std::cout << s << std::endl;
        ll hash = 0;
        for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i] - 'A') % prime;
        return hash;
    }

    int getH(int patternLen) 
    {
        h = 1;
        for(int i = 0; i < patternLen; i++)
        {
            h = (h * multiplier) % prime;
        }
        return h;
    }

    bool checkEqual(const string& text, const string& pattern, int start, int len)
    {
        for(int i = 0; i < len; i ++)
        {
            if(text[i + start] != pattern[i])
                return false;
        }
        return true;
    }
};

Data read_input()
{
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int> &output)
{
    for (int i = output.size() - 1; i >= 0; i--)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data &input)
{
    const string &s = input.pattern, t = input.text;
    std::vector<int> ans;
    for (size_t i = 0; i + s.size() <= t.size(); ++i)
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    return ans;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    RabinKarpAlgo rk;
    print_occurrences(rk.get_occurrences(read_input()));
    //print_occurrences(get_occurrences(read_input()));
    return 0;
}
