#include<bits/stdc++.h>
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
const int maxn=100010;

int n;
int pos[maxn];
void work(){
    n=read();
    vector<pii> ask;
    for(int i=0;i<n;i++)ask.pb({i,1});
    printf("? %d\n",ask.size());fflush(stdout);
    for(auto p:ask)printf("%d %d\n",p.fi,p.se);fflush(stdout);
    vector<int> id;
    int x=read();
    while(x--)id.pb(read());
    for(int l=1;l<=n&&id.size()>1;l<<=1){
        bool fl=id[0]+n-id.back()<l;
        for(int i=1;i<id.size();i++)if(id[i]-id[i-1]>=l){fl=false;break;}
        if(fl)break;
        vector<int> tmp;
        if(id[0]+n-id.back()>=l)tmp.pb(id[0]);
        for(int i=1;i<id.size();i++)if(id[i]-id[i-1]>=l)tmp.pb(id[i]);
        swap(id,tmp);
        if(id.size()==1)break;
        vector<pii> ask;
        for(int p:id){
            ask.pb({(p+l)%n,l});
            pos[ask.size()-1]=p;
        }
        id.clear();
        printf("? %d\n",ask.size());fflush(stdout);
        for(auto p:ask)printf("%d %d\n",p.fi,p.se);fflush(stdout);
        int x=read();
        while(x--)id.pb(pos[read()]);
        sort(id.begin(),id.end());
        // cout<<l<<"\n";
        // for(int p:id)cout<<p<<" ";cout<<"\n";
    }
    printf("! %d\n",id.size());fflush(stdout);
    for(auto p:id)printf("%d ",p);fflush(stdout);
}

int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}