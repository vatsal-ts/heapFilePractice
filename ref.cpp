#include <bits/stdc++.h>
using namespace std;
int page_size;

class page
{
    public:
    int cnt, first_space;
    vector<pair<int, int>> records; //address, key(record)
    bool insert(int record_size, int primary_key)
    {
        if(first_space+(cnt+1)*4+record_size+16>page_size) return false;
        records.push_back({first_space, primary_key});
        first_space+=record_size;
        cnt++;
        return true;
    }
    int search(int primary_key)
    {
        for(int i=0; i<records.size(); i++)
        {
            if(records[i].second==primary_key)
                return i;
        }
        return -1;
    }
    page()
    {
        cnt=0;
        first_space=0;
    }
};
int main()
{
    cin>>page_size;
    vector<page*> heap;
    int input;
    do
    {
        cin>>input;
        if(input==1) //insert
        {
            int record_size, primary_key;
            cin>>record_size>>primary_key;
            bool ok=false;
            for(auto pages : heap)
                if(ok=pages->insert(record_size, primary_key))
                    break;
            if(!ok)
            {
                page* temp=new page;
                temp->insert(record_size, primary_key);
                heap.push_back(temp);
            }
        }
        else if(input==3) //search
        {
            int primary_key; cin>>primary_key;
            pair<int,int> ans={-1,-1};
            for(int i=0; i<heap.size(); i++)
            {
                if((ans.second=heap[i]->search(primary_key))!=-1)
                {
                    ans.first=i;
                    break;
                }
            }
            cout<<ans.first<<" "<<ans.second<<endl;
        }
        else if(input==2) //status
        {
            cout<<heap.size()<<" ";
            for(auto pages : heap)
                cout<<pages->cnt<<" ";
            cout<<endl;
        }
    } while (input!=4);
    
    return 0;
}