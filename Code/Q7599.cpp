#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
inline int read(){
    int x=0,fl=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*fl;
}
const int maxn=200010;
const int inf=1e9;

int n;
vector<int> a;
map<int,bool> mp;
void get(int n){
    if(mp[n])return ;
    for(int i:a){
        for(int j:a){
            if(i*i-j==n){
                cout<<i<<" "<<j<<"\n";
                mp[n]=1,a.pb(n);
                return ;
            }
        }
    }
    int x=sqrt(n);
    while(x*x<n)x++;
    get(x),get(x*x-n);
    cout<<x<<" "<<x*x-n<<"\n";
    mp[n]=1,a.pb(n);
}
void work(){
    n=read();
    a.pb(0),a.pb(1),a.pb(2);
    mp[0]=1,mp[1]=1,mp[2]=1;
    get(n);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=1;
    while(T--)work();
}