#include<bits/stdc++.h>
#define ll unsigned long long
#define short unsigned short
#define pii pair<short,ll>
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
const int maxn=45;
const int B=41;
const int maxm=1<<22;

short n,a[maxn];
struct hsh_table{
	int head[maxm],tot;
	struct nd{
        int nxt;
        vector<short> key;
		pii val;
	}e[maxm];
    int st[maxm],tp;
	int hsh(vector<short> a){
        int val=0;for(short v:a)val=(val*B+v)&(maxm-1);
        return val;
    }
	pii &operator[](vector<short> key){
		int u=hsh(key);
		for(int i=head[u];i;i=e[i].nxt){
			if(e[i].key==key)return e[i].val;
		}
        if(!head[u])st[++tp]=u;
		e[++tot]={head[u],key,{n*n,0}};head[u]=tot;
		return e[tot].val;
	}
	void clear(){
        while(tp)head[st[tp--]]=0;tot=0;
	}
}f[2];bool cur;
inline void chkmn(pii &u,pii v){
    if(u.fi>v.fi)u=v;
    else if(u.fi==v.fi)u.se+=v.se;
}
pii ans[maxn];

signed main(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    vector<short> s(n+1,0);
    f[0][s]={0,1};
    for(int i=1;i<=n;i++){
        f[i&1].clear();
        vector<int> val(n-i+1);
        for(int j=i;j<=n;j++)val[j-i]=a[j];
        sort(val.begin(),val.end());
        int p=upper_bound(val.begin(),val.end(),a[i])-val.begin()-1;
        // cout<<i<<" "<<f[cur].tot<<" "<<p<<" i\n";
        for(int j=1;j<=f[cur].tot;j++){
            vector<short> b=f[cur].e[j].key;pii dp=f[cur].e[j].val;
            int sz=b.size();
            int add=0;for(int k=p+1;k<sz;k++)add+=b[k];
            // cout<<i<<" "<<j<<" "<<dp.fi<<" "<<dp.se<<" "<<add<<" d\n";
            // for(int v:b)cout<<v<<" ";cout<<"\n";
            b[p+1]+=b[p];
            for(int k=p+1;k<sz;k++)b[k-1]=b[k];b.pop_back();
            chkmn(f[i&1][b],{dp.fi,dp.se});
            b[p]++;
            chkmn(f[i&1][b],{dp.fi+add,dp.se});
        }
        cur^=1;
    }
    for(int i=1;i<=n;i++)ans[i]={n*n,0};
    for(int j=1;j<=f[n&1].tot;j++){
        vector<short> b=f[n&1].e[j].key;pii dp=f[n&1].e[j].val;
        int num=0;for(int v:b)num+=v;
        chkmn(ans[num],dp);
    }
    for(int i=1;i<=n;i++)printf("%d %lld\n",ans[i].fi,ans[i].se);
}