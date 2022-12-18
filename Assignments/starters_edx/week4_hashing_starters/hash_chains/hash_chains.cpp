#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using std::cin;
using std::list;
using std::string;
using std::vector;

struct Query
{
    string type, s;
    size_t ind;
};

class QueryProcessor
{
    int bucket_count;
    // store all strings in one vector
    vector<list<string>> hashTable;
    // vector<string> elems;
    size_t hash_func(const string &s) const
    {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count)
    {
        hashTable.resize(bucket_count);
    }

    Query readQuery() const
    {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const
    {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query &query)
    {
        if (query.type == "check")
        {
            /* use reverse order, because we append strings to the end
            for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
                if (hash_func(elems[i]) == query.ind)
                    std::cout << elems[i] << " ";
            std::cout << "\n";
            */
            if (hashTable[query.ind].empty())
                std::cout << "\n";
            else
            {
                for (list<string>::reverse_iterator rit = hashTable[query.ind].rbegin(); rit != hashTable[query.ind].rend(); rit++)
                {
                    std::cout << *rit << " ";
                }
                std::cout << "\n";
            }
        }
        else
        {
            /*
            vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != elems.end());
            else if (query.type == "add") {
                if (it == elems.end())
                    elems.push_back(query.s);
            } else if (query.type == "del") {
                if (it != elems.end())
                    elems.erase(it);
            }
            */
            if (query.type == "find")
            {
                size_t hash = hash_func(query.s);
                list<string>::iterator it;
                for (it = hashTable[hash].begin(); it != hashTable[hash].end(); it++)
                {
                    if (*it == query.s)
                        break;
                }
                writeSearchResult(it != hashTable[hash].end());
            }

            else if (query.type == "add")
            {
                size_t hash = hash_func(query.s);
                if (hashTable[hash].empty())
                    hashTable[hash].push_back(query.s);
                else
                {
                    list<string>::iterator it;
                    for (it = hashTable[hash].begin(); it != hashTable[hash].end(); it++)
                    {
                        if (*it == query.s)
                            break;
                    }
                    if (it == hashTable[hash].end())
                        hashTable[hash].push_back(query.s);
                }
            }
            else if (query.type == "del")
            {
                size_t hash = hash_func(query.s);
                if (!hashTable[hash].empty())
                {
                    list<string>::iterator it;
                    for (it = hashTable[hash].begin(); it != hashTable[hash].end(); it++)
                    {
                        if (*it == query.s)
                            break;
                    }
                    if (it != hashTable[hash].end())
                        hashTable[hash].erase(it);
                }
            }
        }
    }

    void processQueries()
    {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
