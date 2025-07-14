#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=1000010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n;
char s[maxn];
int a[maxn];
void work(){
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;i++){
		if(s[i]=='('||s[i]==')')a[i]=1;
		else a[i]=2;
	}
	for(int i=1;i+2<=n;i++)if(a[i]==a[i+1]&&a[i]==a[i+2]){printf("No\n");return ;}
	int num=0;
	for(int i=1;i<n;i++){
		if(a[i]==a[i+1])++num;
	}
	if(num>2)printf("No\n");
	else printf("Yes\n");
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
	
	T=read();
	while(T--)work();
}
