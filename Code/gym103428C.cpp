// Problem: C. Assign or Multiply
// Contest: Codeforces - The 2021 CCPC Weihai Onsite
// URL: https://codeforces.com/gym/103428/problem/C
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-05-23 16:22:33
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int maxn=1000010;
const int inf=2e9;

int n,p,g;
bool f[maxn],ff[maxn];
inline int ksm(int a,int b){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%p;
        a=a*a%p;
        b>>=1;
    }
    return ans;
}
bool chk(int v){
    for(int i=2;i*i<=p-1;i++)if((p-1)%i==0){
        if(ksm(v,i)==1)return 0;
        if(i*i!=p-1&&ksm(v,(p-1)/i)==1)return 0;
    }
    return 1;
}
int rnk[maxn];
int a[maxn],m,t[maxn];
vector<int> b[maxn];
void work(){
    p=read(),n=read();
    g=1;while(!chk(g))g++;
    for(int i=0,j=1;i<p-1;i++,j=j*g%p)rnk[j]=i;
    for(int i=0;i<p-1;i++)f[i]=t[i]=0;
    bool fl=0,fl0=0;
    while(n--){
        int op=read(),x=read();
        if(!x)fl0=1;
        else{
            if(!op)fl=1,f[rnk[x]]=1;
            else t[rnk[x]]++;
        }
    }
    // cout<<fl<<" "<<fl0<<" "<<g<<"\n";
    if(!fl){printf("%lld\n",p-1);return ;}
    m=0;
    for(int i=0;i<p-1;i++)if(t[i]){
        for(int j=1;j<=t[i];j<<=1){
            a[++m]=i*j%(p-1);
            t[i]-=j;
        }
        if(t[i])a[++m]=i*t[i]%(p-1);
    }
    // cout<<g<<"\n";
    // for(int i=1;i<=m;i++)cout<<a[i]<<" ";cout<<"\n";
    for(int i=1;i<=m;i++)b[__gcd(a[i],p-1)].pb(a[i]);
    for(int i=0;i<p-1;i++){
        for(int v:b[i]){
            bool fl=0;
            for(int j=0;j<p-1;j++)if(f[j]&&!f[(j+v)%(p-1)]){
                ff[(j+v)%(p-1)]=1;
                fl=1;
            }
            for(int j=0;j<p-1;j++)f[j]|=ff[j],ff[j]=0;
            if(!fl)break;
        }
        b[i].clear();
    }
    // for(int i=0;i<p-1;i++)cout<<f[i];cout<<"\n";
    int num=1-fl0;for(int i=0;i<p-1;i++)num+=1-f[i];
    printf("%lld\n",num);
}

int T;
signed main(){
    // freopen("operation.in","r",stdin);
    // freopen("operation.out","w",stdout);
    
    T=1;
    while(T--)work();
}