#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=50010;
const int inf=1e9;
bool mbe;

int n,q;
char s[maxn];
namespace SA{
int sa[maxn],rk[maxn<<1],tmp[maxn<<1],ht[maxn],cnt[maxn],id[maxn];
void init(){
	int w=26;
	for(int i=1;i<=max(n,w);i++)tmp[i]=0;
	for(int i=1;i<=n;i++)++cnt[rk[i]=s[i]-'a'+1];
	for(int i=1;i<=w;i++)cnt[i]+=cnt[i-1];
	for(int i=n;i;i--)sa[cnt[rk[i]]--]=i;
	for(int i=1;i<=w;i++)cnt[i]=0;
    for(int len=1;len<n;len<<=1){
    	int cur=0;for(int i=n-len+1;i<=n;i++)id[++cur]=i;
    	for(int i=1;i<=n;i++)if(sa[i]>len)id[++cur]=sa[i]-len;
    	for(int i=1;i<=n;i++)cnt[tmp[i]=rk[i]]++;
    	for(int i=1;i<=w;i++)cnt[i]+=cnt[i-1];
    	for(int i=n;i;i--)sa[cnt[rk[id[i]]]--]=id[i];
    	for(int i=1;i<=w;i++)cnt[i]=0;
    	int p=0;
        for(int i=1;i<=n;i++){
            if(tmp[sa[i]]==tmp[sa[i-1]]&&tmp[sa[i]+len]==tmp[sa[i-1]+len])rk[sa[i]]=p;
            else rk[sa[i]]=++p;
        }
        w=p;
        if(w==n)break;
    }
    ht[1]=0;
    for(int i=1,l=0;i<=n;i++){
        if(rk[i]==1)continue;
        if(l)l--;
        while(min(i+l,sa[rk[i]-1]+l)<=n&&s[i+l]==s[sa[rk[i]-1]+l])l++;
        ht[rk[i]]=l;
    }
}
}
using SA::sa;
using SA::ht;
using SA::rk;
#define lb(x) (x&(-x))
struct bit{
	int tree[maxn];
	void upd(int x,int w){
		while(x<=n)tree[x]+=w,x+=lb(x);
	}
	int que(int x){
		int res=0;
		while(x)res+=tree[x],x-=lb(x);
		return res;
	}
	int que(int l,int r){return l>r?0:que(r)-que(l-1);}
}t;
struct node{
	int l,r,k;
};
struct node1{
	int l,r,k,id;
};
vector<node> que[maxn];
int ans[maxn];
int pre[maxn],suf[maxn],id[maxn];
void sovle(int l,int r){
	if(l==r)return ;
	int mid=l+r>>1;
	sovle(l,mid),sovle(mid+1,r);
	pre[mid+1]=n;for(int i=mid;i>=l;i--)pre[i]=min(pre[i+1],ht[i]);
	suf[mid]=n;for(int i=mid+1;i<=r;i++)suf[i]=min(suf[i-1],ht[i]);
	
	for(int i=l;i<=mid;i++)t.upd(sa[i],1);
	vector<node1> ask;
	for(int i=mid+1;i<=r;i++){
		int k=sa[i];
		for(auto[l,r,id]:que[k]){
			ans[id]+=t.que(k+1,r);
			if(suf[i]<=r-k)ans[id]+=t.que(l,k-1);
			else ask.pb({l,r,k,id});
		}
	}
	for(int i=l;i<=mid;i++)t.upd(sa[i],-1);
	sort(ask.begin(),ask.end(),[&](node1 u,node1 v){return u.r-u.k<v.r-v.k;});
	for(int i=0,j=l;i<ask.size();i++){
		auto[ll,rr,k,id]=ask[i];
		while(j<=mid&&pre[j+1]<=rr-k)t.upd(sa[j],1),j++;
		ans[id]+=t.que(ll,k-1);
		if(i+1==ask.size()){
			while(j>l){
				j--;t.upd(sa[j],-1);
			}
		}
	}
	ask.clear();
	for(int i=l;i<=mid;i++){
		int k=sa[i];
		for(auto[l,r,id]:que[k])ask.pb({l,r,k,id});
	}
	sort(ask.begin(),ask.end(),[&](node1 u,node1 v){return u.r>v.r;});
	sort(id+mid+1,id+r+1,[&](int u,int v){return sa[u]+suf[u]>sa[v]+suf[v];});
	for(int i=0,j=mid+1;i<ask.size();i++){
		auto[ll,rr,k,iid]=ask[i];
		while(j<=r&&sa[id[j]]+suf[id[j]]>=rr+1)t.upd(sa[id[j]],1),j++;
		ans[iid]+=t.que(max(k+1,rr-pre[rk[k]+1]+1),rr);
		if(i+1==ask.size()){
			while(j>mid+1){
				j--;t.upd(sa[id[j]],-1);
			}
		}
	}
	
	// for(int i=l;i<=mid;i++){
		// for(int j=mid+1;j<=r;j++){
			// int k=sa[j];
			// for(auto[l,r,id]:que[k])if(l<=sa[i]&&sa[i]<=r){
				// if(sa[i]>k||min(pre[i+1],suf[j])<=r-k)ans[id]++;
			// }
		// }
	// }
	// for(int i=l;i<=mid;i++){
		// int k=sa[i];
		// for(int j=mid+1;j<=r;j++){
			// for(auto[l,r,id]:que[k])if(l<=sa[j]&&sa[j]<=r){
				// if(sa[j]>k&&min(pre[i+1],suf[j])>=r-sa[j]+1)ans[id]++;
			// }
		// }
	// }
}
void work(){
	n=read();q=read();scanf("%s",s+1);SA::init();
	for(int i=1;i<=n;i++)que[i].clear();
	for(int i=1;i<=q;i++){
		int l=read(),r=read(),k=read();
		que[k].pb({l,r,i});ans[i]=0;
	}
	for(int i=1;i<=n;i++)id[i]=i;
	sovle(1,n);
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]+1);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}