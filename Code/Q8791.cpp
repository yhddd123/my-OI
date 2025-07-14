#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=1000010;
const int inf=1e18;
char ch;
int read(){
	int x=0;ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return x;
}
bool Mbe;

int n;
char s[maxn];
vector<int> id[maxn];
void work(){
	while(~scanf("%s",s+1)){
		n=strlen(s+1);int p=1,x=0,xx=0;
		while(s[p]<'0'||s[p]>'9')p++;
		while(p<=n&&s[p]>='0'&&s[p]<='9')x=x*10+s[p]-'0',p++;
		// cout<<n<<" "<<x<<"\n";
		while(1){
			xx=read();
			id[xx].pb(x);
			// cout<<xx<<"\n";
			if(ch!=',')break;
		}
	}
	for(int i=1;i<maxn;i++)if(id[i].size()){
		printf("CS-%lld: ",i);
		for(int j=0;j<id[i].size();j++){
			printf("CS-%lld",id[i][j]);
			if(j!=id[i].size()-1)printf(", ");
		}
		puts("");
	}
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
