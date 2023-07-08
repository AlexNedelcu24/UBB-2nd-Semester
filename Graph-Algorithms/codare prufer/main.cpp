#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream in("f.in");
ofstream out("f.out");

int n,x,copii[100000],rad;
vector <int> parinte,k;

int main()
{
    in>>n;
    for(int i=0; i<n; i++){
        in>>x;
        parinte.push_back(x);
        if(x != -1) copii[x]++;
        else rad = i;
    }

    int repeta = n-1;

    while(repeta){
        int frunza;
        for(int i=0; i<n; i++)
            if(copii[i] == 0 && i != rad){
                frunza = i;
                copii[i] = -1;
                copii[parinte[i]]--;
                break;
            }
        k.push_back(parinte[frunza]);
        repeta--;
    }

    out<<k.size()<<'\n';
    for(int i=0; i<k.size(); i++)
    {
        out<<k[i]<<" ";
    }
}
