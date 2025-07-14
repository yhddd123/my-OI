#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=400010;
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

int n,len;
struct cp{
	db a,b;
	cp(db u=0,db v=0){a=u,b=v;}
	cp operator+(const cp&tmp)const{return cp(a+tmp.a,b+tmp.b);}
	cp operator-(const cp&tmp)const{return cp(a-tmp.a,b-tmp.b);}
	cp operator*(const cp&tmp)const{return cp(a*tmp.a-b*tmp.b,a*tmp.b+b*tmp.a);}
}a[maxn],b[maxn],c[maxn];
int to[maxn];
void fft(cp *a,int n,int flag){
	for(int i=0;i<n;i++)if(i<to[i])swap(a[i],a[to[i]]);
	for(int k=2;k<=n;k<<=1){
		cp bas=cp(cos(2*pi/k),flag*sin(2*pi/k));
		int l=k>>1;
		for(int i=0;i<n;i+=k){
			cp mul=cp(1,0);
			for(int j=i;j<i+l;j++){
				cp val=mul*a[j+l];
				a[j+l]=a[j]-val;
				a[j]=a[j]+val;
				mul=mul*bas;
			}
		}
	}
	if(flag==-1)for(int i=0;i<n;i++)a[i].a/=n;
}
void work(){
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%lf",&a[i].a);
		c[n-i].a=a[i].a;
		b[i].a=db(1.0/i/i);
	}
	len=1;while(len<=(n<<1))len<<=1;
	for(int i=0;i<len;i++)to[i]=(to[i>>1]>>1)|(i&1?len>>1:0);
	fft(a,len,1);fft(b,len,1);fft(c,len,1);
	for(int i=0;i<len;i++)a[i]=a[i]*b[i],c[i]=c[i]*b[i];
	fft(a,len,-1);fft(c,len,-1);
	for(int i=1;i<=n;i++)printf("%.3lf\n",a[i].a-c[n-i].a);
}

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
