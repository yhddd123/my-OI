#include<bits/stdc++.h>
#define int long long
#define lll __int128
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
const int inf=1e18;
bool mbe;

int n,x,y;
int vx,vy;
vector<pii> a;
lll calcx(int p){
    int lst=x-1;lll res=0;
    for(int i=0;i<a.size();i++){
        if(a[i].fi<=p)res+=(lll)1*(a[i].fi-lst)*(a[i].se-y+1);
        else{res+=(lll)1*(p-lst)*(a[i].se-y+1);break;}
        lst=a[i].fi;
    }
    return res;
}
lll calcy(int p){
    int lst=y-1;lll res=0;
    for(int i=a.size()-1;~i;i--){
        if(a[i].se<=p)res+=(lll)1*(a[i].fi-x+1)*(a[i].se-lst);
        else{res+=(lll)1*(a[i].fi-x+1)*(p-lst);break;}
        lst=a[i].se;
    }
    return res;
}
void write(lll x){
    int v1=x/inf,v2=x%inf;
    cout<<v1<<v2<<"\n";
}
void work(){
    n=read();x=1,y=1;
    // vx=read(),vy=read();
    a.pb({n,n});
    while(1){
        int p,q;
        int l=x,r=n,res=n;lll S=calcx(n);
        // write(S),write(calcy(n));
        while(l<=r){
            int mid=l+r>>1;
            if(calcx(mid)*3>=S)res=mid,r=mid-1;
            else l=mid+1;
        }
        p=res;
        l=y,r=n,res=n;
        while(l<=r){
            int mid=l+r>>1;
            if(calcy(mid)*3>=S)res=mid,r=mid-1;
            else l=mid+1;
        }
        q=res;
        // write(calcx(p)),write(calcy(q));
        cout<<p<<" "<<q<<endl;
        int op=read();
        // int op=0;
        // if(p>vx||q>vy)op=3;
        // else if(p<vx)op=1;
        // else if(q<vy)op=2;
        if(!op)return ;
        if(op==1){
            x=p+1;
            vector<pii> tmp=a;a.clear();
            for(auto[u,v]:tmp)if(u>=x)a.pb({u,v});
        }
        else if(op==2){
            y=q+1;
            vector<pii> tmp=a;a.clear();
            for(auto[u,v]:tmp)if(v>=y)a.pb({u,v});
        }
        else{
            bool fl=0;
            for(auto[u,v]:a)fl|=(u>=p&&v>=q);
            if(fl){
                vector<pii> tmp=a;a.clear();
                int v1=0,v2=0;
                for(auto[u,v]:tmp){
                    if(u<p)a.pb({u,v});
                    else if(v>=q){
                        if(!v1)v1=v;
                        v2=u;
                    }
                    else a.pb({u,v});
                }
                // cout<<a.size()<<" "<<v1<<" "<<v2<<"\n";
                a.pb({p-1,v1}),a.pb({v2,q-1});
                sort(a.begin(),a.end());
            }
            // cout<<a.size()<<" c\n";
            // for(auto[u,v]:a)cout<<u<<" "<<v<<"\n";
        }
    }
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}