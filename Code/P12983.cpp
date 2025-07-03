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

int n,k,ans;
mt19937 rnd(time(0));
void work(){
    n=read();k=read();
    if(k>=n-1){
        int u=0,sum=0,num=0;
        u=read();sum+=read(),num++;
        for(int i=1;i<=n;i++)if(i!=u)cout<<"T "<<i<<endl,u=read(),sum+=read(),num++;
        cout<<"E "<<sum/2<<endl;
    }
    else{
        vector<int> a;
        for(int i=1;i<=n;i++)a.pb(i);
        shuffle(a.begin(),a.end(),rnd);
        int k1=500,k2=k-k1,u=0;
        int s1=0,n1=0,s2=0,n2=0;
        u=read();s1+=read(),n1++;
        while(k1--){
            cout<<"T "<<a.back()<<endl;a.pop_back();
            u=read(),s1+=read(),n1++;
        }
        while(k2--){
            cout<<"W"<<endl;
            u=read(),s2+=read(),n2++;
        }
        cout<<"E "<<(s1*n/n1/2+s2*n/n2/2)/2<<endl;
    }
}

int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}