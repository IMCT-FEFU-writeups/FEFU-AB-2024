#include <fstream>
#include <queue>
#include <algorithm>
#include <list>
#include <vector>
using namespace std;

struct sit
{
    short y,x;
};
sit dir[4] = {{0,1},{0,-1},{1,0},{-1,0}};


void bfs(vector<vector<int>>& sits, int y, int x)
{
    static int hash = 0;
    static queue<sit> going_to;
    going_to.push({y,x});
    static list<sit> was_before;
    while(!going_to.empty())
    {
        sit current = going_to.front();
        going_to.pop();
        if(current.y < 0 || current.y>=sits.size() || current.x < 0 || current.x >= sits[0].size()) continue;
        if(sits[current.y][current.x] != 1) continue;
        was_before.push_back(current);
        sits[current.y][current.x] = 0;
        for(int i = 0; i < 4; i++){
            going_to.push({current.y+dir[i].y,current.x+dir[i].x});
        }
    }
    for(sit was : was_before){
        sits[was.y][was.x] = was_before.size() | (hash<<20);
    }
    was_before.clear();
    hash++;
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    in.tie(0);
    ios_base::sync_with_stdio(false);
    int W,H;
    in >> W >> H;
    vector<vector<int>> sits (H, vector<int>(W));
    string next_input_row;
    for(int i = 0; i < H; i++)
    {
        in >> next_input_row;
        for(int j = 0; j < W; j++)
        {
            sits[i][j]= next_input_row[j] == '#'? 1:0;
        }
    }

    for(int i = 0; i < H; i++)
    {
        for(int j = 0; j < W; j++)
        {
            if(sits[i][j] == 1)
            {
                bfs(sits,i,j);
            }
        }
    }

    int m_sum = -1;
    sit m_sit = {1,1};
    list<int> values;
    for(int i = 0; i < H; i++)
    {
        for(int j = 0; j < W; j++)
        {
            int sum = 0;
            if(sits[i][j]) continue;
            if(j>0 && find(values.begin(),values.end(),sits[i][j-1])==values.end()){
                sum+=sits[i][j-1]&((1<<20)-1);
                values.push_back(sits[i][j-1]);
            }
            if(i>0 && find(values.begin(),values.end(),sits[i-1][j])==values.end()){
                sum+=sits[i-1][j]&((1<<20)-1);
                values.push_back(sits[i-1][j]);
            }

            if(j<W-1 && find(values.begin(),values.end(),sits[i][j+1])==values.end()){
                sum+=sits[i][j+1]&((1<<20)-1);
                values.push_back(sits[i][j+1]);
            }
            if(i<H-1 && find(values.begin(),values.end(),sits[i+1][j])==values.end()){
                sum+=sits[i+1][j]&((1<<20)-1);
                values.push_back(sits[i+1][j]);
            }
            values.clear();
            if(sum > m_sum){
                m_sum = sum;
                m_sit = {i+1,j+1};
            }
        }
    }
    out << m_sit.x << " " << m_sit.y << endl;
    return 0;
}
