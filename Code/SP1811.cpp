#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,ans;
char c[maxn],s[maxn];
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
		lnk[q]=lnk[nd]=cl;
		while(p&&a[p][c]==q)a[p][c]=cl,p=lnk[p];
	}
	p=nd;
}

void work(){
	scanf("%s%s",c+1,s+1);
	n=strlen(c+1);m=strlen(s+1);
	for(int i=1;i<=n;i++)insert(c[i]-'a');
	int p=1,l=0;
	for(int i=1;i<=m;i++){
		int x=s[i]-'a';
		while(1){
			if(a[p][x]){
				p=a[p][x],l++;
				break;
			}
			if(!l)break;
			l--;
			if(l==len[lnk[p]])p=lnk[p];
		}
		ans=max(ans,l);
	}
	printf("%lld\n",ans);
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
