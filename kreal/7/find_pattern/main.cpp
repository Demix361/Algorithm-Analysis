#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int find(string text, string substr)
{
    for (int i = 0; i < text.length(); ++i)
    {
        int j = 0;
        for (j = 0; j < substr.length(); ++j)
        {
            if(text[i+j] != substr[j])
                break;
        }
        if (j == substr.length())
            return i;
    }
    return -1;
}

bool isPrefix(const std::string &substr, const int &p)
{
    int j = 0;
    for (int i = p; i < substr.length(); ++i)
    {
        if (substr[i] != substr[j])
            return false;
        j++;
    }
    return true;
}

int suffixLength(const std::string &substr, const int &p)
{
    int len = 0;
    int i = p, j = substr.length() - 1;
    while (i >= 0 && substr[i] == substr[j])
    {
        len++;
        i--;
        j--;
    }
    return len;
}

std::vector<int> getSuffix(const std::string &substr)
{
    int n = substr.length();
    std::vector<int> table(n);
    int lastPrefixPosition = n;

    for (int i = n - 1; i >= 0; --i)
    {
        if (isPrefix(substr, i + 1))
            lastPrefixPosition = i + 1;
        table[n - 1 - i] = lastPrefixPosition - i + n - 1;
    }

    for (int i = 0; i < n - 1; i++)
    {
        int slen = suffixLength(substr, i);
        table[slen] = n - 1 - i + slen;
    }

    return table;
}

int searchBM(const std::string &text, const std::string &substr)
{
    std::unordered_map<char, int> stopTable;
    int m = substr.length();
    int n = text.length();
    std::vector<int> suffix = getSuffix(substr);
    for (int i = 0; i < m; ++i)
    {
        stopTable[substr[i]] = m - 1 - i;
    }

    for (int i = m - 1; i < n;)
    {
        int j = m - 1;

        while (substr[j] == text[i])
        {
            if (j == 0)
                return i;
            i--;
            j--;
        }
        auto stop_symbol = stopTable.find(text[i]);
        int stopAdd = stop_symbol != stopTable.end() ? stop_symbol->second : m;
        i += std::max(suffix[m - j - 1], stopAdd);
    }

    return -1;
}

string::size_type KMP(const string& S, const string& pattern)
{
    vector<int> pf (pattern.length());

    pf[0] = 0;
    for (int k = 0, i = 1; i < pattern.length(); ++i)
    {
        while ((k > 0) && (pattern[i] != pattern[k]))
            k = pf[k-1];

        if (pattern[i] == pattern[k])
            k++;

        pf[i] = k;
    }

    for (int k = 0, i = 0; i < S.length(); ++i)
    {
        while ((k > 0) && (pattern[k] != S[i]))
            k = pf[k-1];

        if (pattern[k] == S[i])
            k++;

        if (k == pattern.length())
            return (i - pattern.length() + 1);
    }

    return -1;
}

void gen_random(char *s, const int len)
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i)
    {
        s[i] = alphanum[std::rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

void test()
{
    FILE *f = fopen("std20.txt", "w"), *f1 = fopen("bm20.txt", "w"), *f2 = fopen("kmp20.txt", "w");

    printf("%5s,%10s,%10s,%10s\n", "N" , "base", "KMP", "BM");
    std::clock_t time = 0;

    int repeat = 100;
    int start = 1000;
    int end = 100000;
    int step = 1000;
    for (int i = start; i <= end; i += step)
    {
        fprintf(f, "%5d ", i);
        fprintf(f1, "%5d ", i);
        fprintf(f2, "%5d ", i);
        printf("%5d,", i);
        char str[i];
        gen_random(str,i);
        char sub[] = "sbdhsdfsdfxdesdsweqs";

        string s(str), p(sub);

        time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            std::clock_t start = clock();
            int res = find(str,sub);
            std::clock_t end = clock();
            time += end-start;
        }
        printf("%10f,", (float)time/repeat);
        fprintf(f,"%10f\n", (float)time/repeat);

        time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            std::clock_t start = clock();
            int res = KMP(s,p);
            std::clock_t end = clock();
            time += end-start;
        }
        printf("%10f,", (float)time/repeat);
        fprintf(f2,"%10f\n", (float)time/repeat);

        time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            std::clock_t start = clock();
            int res = searchBM(s,p);
            std::clock_t end = clock();
            time += end-start;
        }
        printf("%10f\n", (float)time/repeat);
        fprintf(f1,"%10f\n", (float)time/repeat);
    }
    fclose(f);
    fclose(f1);
    fclose(f2);
}

int main()
{
    string str, sub;
    cout <<"input str: ";
    cin >> str;
    cout << "input sub: ";
    cin >> sub;
    for (int i = 0; i < str.length(); i++){
        printf("%3d", i);
    }
    printf("\n");
    for (int i = 0; i < str.length(); i++){
        cout << "  "<< str[i];
    }
    printf("\n");
    for (int i = 0; i < sub.length(); i++){
        cout <<"  " <<sub[i];
    }
    printf("\n");
    cout << "base: " << find(str.c_str(), sub.c_str())<< endl;
    cout << "KMP : " << KMP(str, sub) << endl;
    cout << "BM  : " << searchBM(str, sub) << endl;

    return 0;
}
