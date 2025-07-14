#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
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

int n,a[maxn];
char s[maxn];
void work1(){
	scanf("%s",s+1);n=strlen(s+1);
	if(n<2000){
		printf("%lld 0\n",n);
		return ;
	}
	for(int i=1;i<=n;i++)a[i]=a[i-1]+(s[i]-'0');
	for(int d=1999,l=n-d+1;~d;d--,l++)if(a[l-1]%2000<=1){
		printf("%d %d\n",d,a[l-1]/2000*2+(a[l-1]%2000));
		return ;
	}
}
int val,res;
void work2(){
	val=read();scanf("%s",s+1);n=strlen(s+1);res=0;
	if(!val){
		for(int i=1;i<=n;i++)res+=s[i]-'0';
		printf("%lld\n",res);
		return;
	}
	for(int i=1;i<=n;i++)res+=s[i]-'0';
	printf("%lld\n",res+val/2*2000+(val&1));
}

// \
444

bool Med;
int T,op;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	op=read();T=read();
	while(T--){
		if(op==1)work1();
		else work2();
	}
}