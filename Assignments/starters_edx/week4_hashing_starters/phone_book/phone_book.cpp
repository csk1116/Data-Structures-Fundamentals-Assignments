#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>

using std::cin;
using std::list;
using std::pair;
using std::string;
using std::vector;

struct Query
{
    string type, name;
    int number;
};

vector<Query> read_queries()
{
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string> &result)
{
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query> &queries)
{
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<Query> contacts;
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add")
        {
            bool was_founded = false;
            // if we already have contact with such number,
            // we should rewrite contact's name
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number)
                {
                    contacts[j].name = queries[i].name;
                    was_founded = true;
                    break;
                }
            // otherwise, just add it
            if (!was_founded)
                contacts.push_back(queries[i]);
        }
        else if (queries[i].type == "del")
        {
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number)
                {
                    contacts.erase(contacts.begin() + j);
                    break;
                }
        }
        else
        {
            string response = "not found";
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number)
                {
                    response = contacts[j].name;
                    break;
                }
            result.push_back(response);
        }
    return result;
}

class PhoneBook
{
public:
    PhoneBook(int phoneMaxDigits)
    {
        numberOfKeys = 0;
        tableSize = 2;
        hashTable.resize(2);
        setPrime(phoneMaxDigits);
        generateRandAnB();
    }

    vector<string> process_queries(const vector<Query> &queries)
    {
        vector<string> result;
        for (int i = 0; i < queries.size(); i++)
        {
            if (getLoadFactor() >= 0.9)
            {
                rehash();
            }

            if (queries[i].type == "add")
            {
                insert(queries[i].number, queries[i].name);
                // std::cout << hashing(queries[i].number) << std::endl;
            }
            else if (queries[i].type == "del")
            {
                erase(queries[i].number);
            }
            else
            {
                string response = "not found";
                if (find(queries[i].number))
                {
                    int hash = hashing(queries[i].number);
                    for (list<pair<int, string>>::iterator it = hashTable[hash].begin(); it != hashTable[hash].end(); it++)
                    {
                        if (it->first == queries[i].number)
                            result.push_back(it->second);           
                    }
                }
                else
                    result.push_back(response);
            }
            // std::cout << i << std::endl;
        }

        return result;
    }

private:
    int numberOfKeys;
    int tableSize;
    int temptableSize;
    int prime;
    pair<int, int> AnB;
    vector<list<pair<int, string>>> hashTable;
    vector<list<pair<int, string>>> tempHashTable;

    double getLoadFactor()
    {
        return (double)numberOfKeys / tableSize; // should < 0.9
    }

    void generateRandAnB()
    {
        // 1 <= a <= p - 1, 0 <= b <= p - 1
        srand(time(nullptr));
        int a = 1 + (rand() % prime - 1);
        int b = 0 + (rand() % prime - 1);
        AnB.first = a;
        AnB.second = b;
        // std::cout << a << " " << b << std::endl;
    }

    void setPrime(int digits)
    {
        int length = pow(10, digits);
        for (int i = length + 1;; i++)
        {
            if (isPrime(i))
            {
                prime = i;
                // std::cout << prime << std::endl;
                return;
            }
        }
    }

    bool isPrime(int number)
    {
        for (int i = 2; i * i <= number; i++)
        {
            if (number % i == 0)
                return false;
        }
        return true;
    }

    int hashing(int phoneNumber)
    {
        long long Ax = (long long)AnB.first * phoneNumber;
        long long AxplusB = (long long)Ax + AnB.second;
        // std::cout << AxplusB << std::endl;
        return (int)(AxplusB % prime) % tableSize;
    }

    void rehash()
    {
        temptableSize = tableSize;
        tempHashTable = hashTable;
        hashTable.clear();
        tableSize = temptableSize * 2;
        hashTable.resize(tableSize);

        for (int i = 0; i < temptableSize; i++)
        {
            if (!tempHashTable[i].empty())
            {
                for (auto p : tempHashTable[i])
                    insert(p.first, p.second);
            }
        }
        tempHashTable.clear();
    }

    void insert(int phoneNumber, string name)
    {
        int hash = hashing(phoneNumber);
        if (find(phoneNumber))
        {
            for (list<pair<int, string>>::iterator it = hashTable[hash].begin(); it != hashTable[hash].end(); it++)
            {
                if (it->first == phoneNumber)
                {
                    it->second = name;
                    return;
                }
            }
            hashTable[hash].push_back(make_pair(phoneNumber, name));
            numberOfKeys++;
        }
        else
        {
            hashTable[hash].push_back(make_pair(phoneNumber, name));
            numberOfKeys++;
        }
    }

    void erase(int phoneNumber)
    {
        if (!find(phoneNumber))
            return;
        int hash = hashing(phoneNumber);
        if(hashTable[hash].size() > 1)
        {
            for (list<pair<int, string>>::iterator it = hashTable[hash].begin(); it != hashTable[hash].end(); it++)
            {
                if (it->first == phoneNumber)
                {
                    hashTable[hash].erase(it);
                    numberOfKeys--;
                    return;
                }
            }
        }
        else
        {
            hashTable[hash].clear();
            numberOfKeys--;
        }        
    }

    bool find(int phoneNumber)
    {
        int hash = hashing(phoneNumber);
        if(!hashTable[hash].empty())
        {
            for (list<pair<int, string>>::iterator it = hashTable[hash].begin(); it != hashTable[hash].end(); it++)
            {
                if (it->first == phoneNumber)
                    return true;
            }
        }        
        return false;
    }
};

int main()
{
    // write_responses(process_queries(read_queries()));
    PhoneBook phoneBook(7);
    write_responses(phoneBook.process_queries(read_queries()));

    return 0;
}
