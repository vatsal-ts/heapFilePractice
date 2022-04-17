#include <bits/stdc++.h>
using namespace std;
#define gc getchar_unlocked
#define fo(i, n) for (auto i = 0; i < n; i++)
#define Fo(i, k, n) for (auto i = k; k < n ? i < n : i > n; k < n ? i += 1 : i -= 1)
#define ll long long
#define si(x) scanf("%d", &x)
#define sl(x) scanf("%lld", &x)
#define ss(s) scanf("%s", s)
#define pi(x) printf("%d\n", x)
#define pl(x) printf("%lld\n", x)
#define ps(s) printf("%s\n", s)
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, 0, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, a) for (auto it = a.begin(); it != a.end(); it++)
#define PI 3.1415926535897932384626
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<pll> vpll;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<vll> vvll;
#define lb lower_bound
#define ub upper_bound
#define PRESENT -1
#define FULL 0
#define SUCCESS 1
#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
int pageSize;
/*
Later cosnider if record is too big to fit in a page alone
*/

class page
{
public:
    page();
    int spaceOccupied();
    page *prev;
    page *next;
    int numRec;
    int freeSpacePtr;
    vector<pair<int, int>> records;
};

page::page()
{
    numRec = freeSpacePtr = 0;
}

int page::spaceOccupied()
{
    return (freeSpacePtr + 16 + numRec * 4);
}

class file
{
public:
    file();
    vector<page *> heap;
    void insert(int, int);
    void status();
    pair<int, int> search(int);
    int numPages;
};

file::file()
{
    numPages = 0;
}

void file::insert(int recSize, int primaryKey)
{

    if (numPages == 0)
    {
        page *newPage = new page;
        numPages++;
        heap.push_back(newPage);
        newPage->prev = NULL;
        newPage->next = NULL;
        newPage->records.push_back({recSize, primaryKey});
        heap[numPages - 1]->freeSpacePtr += recSize;
        heap[numPages - 1]->numRec++;
        return;
    }
    else
    {
        for (int i = 0; i < numPages; i++)
        {
            if (((heap[i]->spaceOccupied() + recSize + 4) < pageSize))
            {
                heap[i]->records.push_back({recSize, primaryKey});
                heap[i]->freeSpacePtr += recSize;
                heap[i]->numRec++;
                return;
            }
        }
    }
    //new page Creation situation
    page *newPage = new page;
    numPages++;
    heap.push_back(newPage);
    heap[numPages - 2]->next = newPage;
    newPage->prev = heap[numPages - 2];
    newPage->next = NULL;
    newPage->records.push_back({recSize, primaryKey});
    heap[numPages - 1]->freeSpacePtr += recSize;
    heap[numPages- 1]->numRec++;
    // cout << heap[numPages - 1]->spaceOccupied() + recSize + 4 << "occupied.\n";
    // (heap[numPage - 1]->freeSpacePtr) += recSize;
    // (heap[numPage - 1]->numRec)++;
}

pair<int, int> file::search(int primaryKey)
{
    for (int i = 0; i < heap.size(); i++)
    {
        for (int j = 0; j < heap[i]->records.size(); j++)
        {
            if ((heap[i]->records[j]).second == primaryKey)
                return {i, j};
        }
    }
    return {-1, -1};
}

void file::status()
{
    // cout << "stat";
    cout << heap.size() << " ";
    for (auto pages : heap)
        cout << pages->numRec << " ";
    cout /*<< "lol"*/<<"\n";
}

/*
Rcord1
Record 2
.
.
.
.

Ptrtorec1,ptrtorec2,p



*/

int main()
{
    fast;
    cin >> pageSize;
    file myFile;
    for (int i = 0; i != -1;)
    {
        int input;
        cin >> input;
        if (input == 1) // insertion
        {
            int record_size, primary_key;
            cin >> record_size >> primary_key;
            myFile.insert(record_size, primary_key);
        }
        else if (input == 3) // search
        {
            int primary_key;
            cin >> primary_key;
            pair<int, int> ans = {-1, -1};
            ans = myFile.search(primary_key);
            cout << ans.first << " " << ans.second << "\n";
        }
        else if (input == 2) // status
        {
            myFile.status();
        }
        else
            i = -1;
    }
}