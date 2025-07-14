#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=2010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn];
int ans[maxn];
int len[maxn],lnk[maxn];
map<int,int> ch[maxn];
int p=1,cur=1;
void insert(int c){
	int nd=++cur;
	len[nd]=len[p]+1;
	while(p&&!ch[p][c])ch[p][c]=nd,p=lnk[p];
	if(!p){lnk[p=nd]=1;return ;}
	int q=ch[p][c];
	if(len[p]+1==len[q])lnk[nd]=q;
	else{
		int cl=++cur;
		len[cl]=len[p]+1,lnk[cl]=lnk[q];
		ch[cl]=ch[q];
		lnk[q]=lnk[nd]=cl;
		while(p&&ch[p][c]==q)ch[p][c]=cl,p=lnk[p];
	}
	p=nd;
}
int calc(int l,int r){
	int res=0;	
	for(int i=l;i<=r;i++)insert(a[i]),res+=len[p]-len[lnk[p]];
	while(cur){
		lnk[cur]=len[cur]=0;ch[cur].clear();
		cur--;
	}
	p=cur=1;
	return res;
}
int get(int l,int r){
	int res=0;
	for(int i=l;i<=r;i++)insert(ans[i]),res+=len[p]-len[lnk[p]];
	while(cur){
		lnk[cur]=len[cur]=0;ch[cur].clear();
		cur--;
	}
	p=cur=1;
	return res;
}
int ask(int l,int r){
	printf("? %lld %lld\n",l,r);fflush(stdout);
	int res=read();
	// int res=get(l,r);
	return res;
}
void work(){
	n=read();
	// for(int i=1;i<=n;i++)ans[i]=read();
	a[1]=1;int idx=1;
	for(int i=2;i<=n;i++){
		int l=1,r=i-1,res=0;
		while(l<=r){
			int mid=l+r>>1;
			if(ask(mid,i)!=calc(mid,i-1)+(i-mid+1))l=mid+1,res=mid;
			else r=mid-1;
		}
		if(!res)a[i]=++idx;
		else a[i]=a[res];
		// cout<<i<<" "<<res<<"\n";
	}
	printf("! ");for(int i=1;i<=n;i++)printf("%lld ",a[i]);fflush(stdout);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
