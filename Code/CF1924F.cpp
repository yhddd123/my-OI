#include<bits/stdc++.h>
#include <ios>
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
bool mbe;

int n;
void work(){
    n=read();
    vector<int> a(n);
    for(int i=1;i<=n;i++)a[i-1]=i;
    auto ask=[&](int l,int r){
        cout<<"? "<<l<<" "<<r<<endl;
        return read()<r-l+1;
    };
    auto del=[&](int l,int r){
        vector<int> tmp;
        for(int p:a)if(p<l||p>r)tmp.pb(p);
        swap(a,tmp);
    };
    while(a.size()>2){
        // cout<<a.size()<<"\n";
        // for(int u:a)cout<<u<<" ";cout<<"\n";
        int p=a.size()*0.36;
        int l1=a[0],r1=a[p-1],l2=a[p],r2=a[a.size()-p-1],l3=a[a.size()-p],r3=a.back();
        if(ask(l1,r2)){
            if(ask(l1,r1)){
                if(ask(l1,r3))del(l1,r1);
                else del(l3,r3);
            }
            else{
                if(ask(l1,r2))del(l2,r2);
                else{
                    if(ask(l1,r3))del(l3,r3);
                    else del(l1,r1);
                }
            }
        }
        else{
            if(ask(l1,r1)){
                if(ask(l1,r2)){
                    if(ask(l1,r3))del(l1,r1);
                    else del(l3,r3);
                }
                else del(l2,r2);
            }
            else{
                if(ask(l1,r3))del(l3,r3);
                else del(l1,r1);
            }
        }
    }
    cout<<"! "<<a[0]<<endl;
    if(!read()){
        cout<<"! "<<a[1]<<endl;
        if(!read())exit(0);
    }
    cout<<"#"<<endl;
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);

    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=read();
    while(T--)work();
}