#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=400010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,q;
char s[maxn],t[maxn];
int len[maxn],lnk[maxn];
int a[maxn][26];
int p=1,cur=1;
void insert(int c){
	int nd=++cur;
	len[nd]=len[p]+1;
	while(p&&!a[p][c])a[p][c]=nd,p=lnk[p];
	if(!p){lnk[p=nd]=1;return ;}
	int q=a[p][c];
	if(len[p]+1==len[q])lnk[nd]=q;
	else{
		int cl=++cur;
		len[cl]=len[p]+1;lnk[cl]=lnk[q];
		memcpy(a[cl],a[q],sizeof(a[q]));
		lnk[nd]=lnk[q]=cl;
		while(p&&a[p][c]==q)a[p][c]=cl,p=lnk[p];
	}
	p=nd;
}
namespace ST{
	int st[20][maxn];
	void init(){
		for(int j=1;j<20;j++){
			for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=max(st[j-1][i],st[j-1][i+(1<<j-1)]);
		}
	}
	int query(int l,int r){
		if(l>r)return 0;
		int k=log2(r-l+1);
		return max(st[k][l],st[k][r-(1<<k)+1]);
	}
}
void go(int &p,int c,int &l){
	while(1){
		if(a[p][c]){
			p=a[p][c],l++;
			break;
		}
		if(!l)break;
		l--;
		if(l==len[lnk[p]])p=lnk[p];
	}
}
void work(){
	scanf("%s%s",s+1,t+1);n=strlen(s+1);m=strlen(t+1);
	for(int i=1;i<=m;i++)insert(t[i]-'a');
	int nd=1,d=0;
	for(int i=1;i<=n;i++){
		go(nd,s[i]-'a',d);
		ST::st[0][i]=d;
	}
	ST::init();
//	for(int i=1;i<=n;i++)cout<<ST::st[0][i]<<" ";cout<<"\n";
	q=read();
	while(q--){
		int u=read(),v=read();
		int l=u,r=v,ans=v+1;
		while(l<=r){
			int mid=l+r>>1;
			if(mid-ST::st[0][mid]+1>=u)ans=mid,r=mid-1;
			else l=mid+1;
		}
//		cout<<ans<<" ";
		printf("%lld\n",max(ST::query(ans,v),ans-u));
	}
}

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
