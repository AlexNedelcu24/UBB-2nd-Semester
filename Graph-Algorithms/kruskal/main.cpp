#include <bits/stdc++.h>

using namespace std;

ifstream in("f.in");
ofstream out("f.out");

int const lim =101;
int n,m,t;
struct ob
{
    int x,y,cost;
};
vector < ob > c;
vector < int > tat,rang;
vector < pair < int , int > > afis;

bool comp(ob a1, ob b1)
{
    return a1.cost<b1.cost;
}

void cit()
{
    in>>n>>m;
    for(int i=1;i<=m;i++)
    {
        ob r;
        in>>r.x>>r.y>>r.cost;
        c.push_back(r);
    }

    sort(c.begin(),c.end(),comp);

    //tat.push_back(0);
    //rang.push_back(0);
    for(int i=0;i<=n-1;i++)
    {
        tat.push_back(i);
        rang.push_back(1);
    }

}

int fin(int nod)
{
    while( nod != tat[nod])
        nod=tat[nod];
    return nod;
}

void unire(int a, int b)
{
    if(rang[a]>rang[b])
        tat[b]=tat[a];
    if(rang[b]>rang[a])
        tat[a]=tat[b];

    if(rang[a]==rang[b])
    {
        tat[a]=tat[b];
        rang[b]++;
    }
}

void rezolv()
{
    for(int i=0;i<c.size();i++)
    {
        int t1=fin(c[i].x);
        int t2=fin(c[i].y);

        if(t1 != t2)
        {
            unire(t1,t2);

            afis.push_back(make_pair(c[i].x,c[i].y));
            t=t+c[i].cost;
        }
    }
}

int main()
{
   cit();
   rezolv();

   out<<t<<'\n';
   out<<afis.size()<<'\n';
   for(int i=0;i<afis.size();i++)
    out<<afis[i].first<<" "<<afis[i].second<<'\n';

}
