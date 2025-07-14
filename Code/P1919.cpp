#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=1000010;
const int inf=1e18;
const db eps=1e-8;
const db pi=acos(-1);
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
char s[maxn];
int ans[maxn<<2];
struct cp{
	db a,b;
	cp(db u=0,db v=0){a=u,b=v;}
	cp operator+(const cp&tmp)const{return cp(a+tmp.a,b+tmp.b);}
	cp operator-(const cp&tmp)const{return cp(a-tmp.a,b-tmp.b);}
	cp operator*(const cp&tmp)const{return cp(a*tmp.a-b*tmp.b,a*tmp.b+b*tmp.a);}
}a[maxn<<2],b[maxn<<2],c[maxn<<2];
int to[maxn<<2];
void fft(cp *a,int flag){
	for(int i=0;i<n;i++)if(i<to[i])swap(a[i],a[to[i]]);
	for(int len=2;len<=n;len<<=1){
		cp bas=cp(cos(2*pi/len),flag*sin(2*pi/len));
		for(int i=0;i<n;i+=len){
			cp mul=cp(1,0);
			for(int j=i;j<i+(len>>1);j++){
				cp val=mul*a[j+(len>>1)];
				a[j+(len>>1)]=a[j]-val;
				a[j]=a[j]+val;
				mul=mul*bas;
			}
		}
	}
}
void work(){
	scanf("%s",s);n=strlen(s)-1;
	for(int i=0;i<=n;i++)a[i].a=s[n-i]-'0';
	scanf("%s",s);m=strlen(s)-1;
	for(int i=0;i<=m;i++)b[i].a=s[m-i]-'0';
	m+=n,n=1;while(n<=m)n<<=1;
	for(int i=0;i<n;i++)to[i]=(to[i>>1]>>1)|((i&1)?(n>>1):0);
	fft(a,1);fft(b,1);
	for(int i=0;i<n;i++)c[i]=a[i]*b[i];
	fft(c,-1);
	for(int i=0;i<n;i++){
		ans[i]+=(int)(c[i].a/n+0.5);
		ans[i+1]+=ans[i]/10,ans[i]%=10;
	}
	bool fl=0;
	for(int i=n;~i;i--){
		if(ans[i])fl=1;
		if(fl)putchar(ans[i]+'0');
	}
}

bool Med;
int T;
signed main(){
//	freopen("P1919_1.in","r",stdin);
//	freopen("my.out","w",stdout);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
