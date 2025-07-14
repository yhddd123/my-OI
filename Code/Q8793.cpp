#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n;
char op[10];
void puttim(int t){
	int u=t/60,v=t%60;
	if(u<10)putchar('0');
	printf("%lld:",u);
	if(v<10)putchar('0');
	printf("%lld",v);
}
bool ask(int t,int u){
	printf("at ");puttim(t);printf(" check %lld\n",u);fflush(stdout);
	scanf("%s",op+1);
	if(op[2]=='s')return 0;
	return 1;
}
vector<int> que[maxn];
int ans[maxn];
bool vis[maxn],fl[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)fl[i]=ask(0,i);
	for(int i=1,j=47,nw=0;nw<=720;i++,j--){
		nw+=j;
		if(nw>=720){
			for(int k=1;k<=n;k++)if(!vis[k])vis[k]=1,que[i].push_back(k);
			break;
		}
		for(int k=1;k<=n;k++)if(!vis[k]){
			if(ask(nw,k)!=fl[k])vis[k]=1,que[i].push_back(k);
		}
	}
	for(int i=1,j=47,nw=720;nw<=1440;i++,j--){
		for(int l=nw;l<=nw+j;l++){
			if(l>=1440){
				for(int k=1;k<=n;k++)if(vis[k])vis[k]=0,ans[k]=fl[k]?1440:0;
				break;
			}
			for(int k:que[i])if(vis[k]){
				if(ask(l,k)==fl[k])vis[k]=0,ans[k]=l;
			}
		}
		nw+=j;
	}
	for(int i=1;i<=n;i++)if(fl[i])ans[i]-=720;
	puts("answer");
	for(int i=1;i<=n;i++)puttim(ans[i]),puts("");
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
