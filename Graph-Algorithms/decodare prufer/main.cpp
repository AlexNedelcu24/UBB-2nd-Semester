#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

ifstream in("f.in");
ofstream out("f.out");

int n,aparitie[100000],parinte[100000];
deque <int> cod;

int main()
{
    in>>n;
    for(int i=0; i<n; i++){
        int x;
        in>>x;
        cod.push_back(x);
        aparitie[x]++;
    }

    n++;

    for(int i=0; i<n; i++){
        parinte[i] = -1;
    }

    for(int i=1; i<=n-1; i++){
        int minim;
        for(int j=0; j<n; j++)
            if(aparitie[j] == 0){
            minim = j;
            break;
        }
        parinte[minim] = cod.front();
        aparitie[cod.front()]--;
        cod.pop_front();
        aparitie[minim]++;
        cod.push_back(minim);
    }

    out<<n<<'\n';
    for(int i=0; i<n; i++){
        out<<parinte[i]<<" ";
    }
}
