#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline unsigned read(){unsigned x=0;char c=getchar();while(c<'0'||c>'9'){c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x;}
const int maxn=(1000000>>6)+5;
const int U=(1<<8)-1;
bool mbe;

int n,m,q;
#define ull unsigned long long
ull fa[U+1][maxn],fb[U+1][maxn],fc[U+1][maxn],fd[U+1][maxn];
void work(){
	read();q=read();
	while(q--){
		char o=getchar();unsigned x=read();
		unsigned a=x&U,b=(x>>8)&U,c=(x>>16)&U,d=x>>24;
		if(o=='!'){
			m=n>>6;ull p=1ull<<(n&63);
			// cout<<m<<" "<<n<<" "<<p<<"\n";
			for(int i=a;i<=U;i=(i+1)|a)fa[i][m]|=p;
			for(int i=b;i<=U;i=(i+1)|b)fb[i][m]|=p;
			for(int i=c;i<=U;i=(i+1)|c)fc[i][m]|=p;
			for(int i=d;i<=U;i=(i+1)|d)fd[i][m]|=p;
			n++;
		}
		else{
			ull res=0;
			for(int i=0;i<=m;i++)res^=fa[a][i]&fb[b][i]&fc[c][i]&fd[d][i];
			// cout<<res<<" "<<__builtin_parityll(res)<<"\n";
			putchar(__builtin_parityll(res)+'0');puts("");
		}
	}
	
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}