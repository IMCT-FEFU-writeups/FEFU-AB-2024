#include <fstream>
#include <vector>
#include <algorithm>

bool cmp (int a, int b)
{
    return a > b;
}

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    in.tie(0);
    vector<int> max_heap, min_heap;
    int center = 0;
    unsigned int cnt = 0;
    in>>cnt;

    in>>center;
    cnt--;
    out<<center<<" ";
    int next = 0;
    while(cnt--)
    {
        in>>next;
        if(next < center)
        {
            max_heap.push_back(next);
            push_heap(max_heap.begin(),max_heap.end());
        }
        else
        {
            min_heap.push_back(next);
            push_heap(min_heap.begin(),min_heap.end(),cmp);
        }
        if(max_heap.size() == min_heap.size() || max_heap.size() + 1 == min_heap.size()) goto print;
        if(max_heap.size() > min_heap.size())
        {
            min_heap.push_back(center);
            push_heap(min_heap.begin(),min_heap.end(),cmp);
            pop_heap(max_heap.begin(),max_heap.end());
            center = max_heap.back();
            max_heap.pop_back();
        }
        else
        {
            max_heap.push_back(center);
            push_heap(max_heap.begin(),max_heap.end());
            pop_heap(min_heap.begin(),min_heap.end(),cmp);
            center = min_heap.back();
            min_heap.pop_back();
        }
print:
        out<<center<<" ";
    }

    return 0;
}
