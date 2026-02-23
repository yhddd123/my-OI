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
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int o,n,nn,a,b,c;
int x[maxn],y[maxn],z[maxn];
void print(){
	for(int i=1;i<=n;i++)printf("%d ",x[i]);puts("");
	for(int i=1;i<=n;i++)printf("%d ",y[i]);puts("");
	for(int i=1;i<=n;i++)printf("%d ",z[i]);puts("");
}
int f[maxn];
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){
	while(x<=n)tree[x]=max(tree[x],w),x+=lb(x);
}
int que(int x){
	int res=0;
	while(x)res=max(res,tree[x]),x-=lb(x);
	return res;
}
int id[maxn];
int calc(int *a,int *b){
	for(int i=1;i<=n;i++)id[a[i]]=i;
	for(int i=1;i<=n;i++)tree[i]=0;
	int mx=0;
	for(int i=1;i<=n;i++){
		int v=id[b[i]];
		int dp=que(v)+1;
		upd(v,dp);
		mx=max(mx,dp);
	}
	return mx;
}
namespace sub1{
	map<tuple<int,int,int,int>,int> mp;int idx;
	bool ans[2010];
	int xx[2010][8],yy[2010][8],zz[2010][8];
	void sovle(){
		if(mp.find({n,a,b,c})==mp.end()){
			mp[{n,a,b,c}]=++idx;
			for(int i=1;i<=n;i++)x[i]=y[i]=z[i]=i;
			bool fl=0;
			do{
				if(calc(x,y)!=a)continue;
				do{
					if(calc(x,z)==b&&calc(y,z)==c){
						// for(int i=1;i<=n;i++)cout<<x[i]<<" ";cout<<"\n";
						// for(int i=1;i<=n;i++)cout<<y[i]<<" ";cout<<"\n";
						// for(int i=1;i<=n;i++)cout<<z[i]<<" ";cout<<"\n";
						// cout<<"\n";
						fl=1;break;
					}
				}while(next_permutation(z+1,z+n+1));
				if(fl)break;
				for(int i=1;i<=n;i++)z[i]=i;
			}while(next_permutation(y+1,y+n+1));
			ans[idx]=fl;
			for(int i=1;i<=n;i++)xx[idx][i]=x[i],yy[idx][i]=y[i],zz[idx][i]=z[i];
			// if(!ans[idx])cout<<n<<" "<<a<<" "<<b<<" "<<c<<"\n";
		}
		int id=mp[{n,a,b,c}];
		puts(ans[id]?"YES":"NO");
		if(ans[id]&&o){
			for(int i=1;i<=n;i++)printf("%d ",xx[id][i]);puts("");
			for(int i=1;i<=n;i++)printf("%d ",yy[id][i]);puts("");
			for(int i=1;i<=n;i++)printf("%d ",zz[id][i]);puts("");
		}
	}
}
int num[maxn];
bool chk(int n,int a,int b,int c){return b+c-a<=n&&1ll*a*b*c>=n;}
void work(){
	n=read();a=read(),b=read(),c=read();o=read();nn=n;
	if(!chk(n,a,b,c)){puts("NO");return ;}
	puts("YES");
	if(!o)return ;
	while(1){
		if(c==n){
			for(int i=1;i<=n;i++)y[i]=z[i]=i;
			for(int i=n;i>a;i--)x[n-i+1]=i;
			for(int i=1;i<=a;i++)x[n-a+i]=i;
			break;
		}
		if(a==1){
			for(int i=1;i<=n;i++)x[i]=i,y[i]=n-i+1;
			for(int i=1;i<=b;i++)z[i]=n-b+i;
			int d=n-(b+c-1);
			for(int i=2,j=b,v=n-b;i<=c;i++){
				int dd=min(d,b-1);
				d-=dd;dd++;
				for(int k=1;k<=dd;k++)z[j+k]=v-dd+k;
				v-=dd;j+=dd;
			}
			break;
		}
		if(a==2&&b==2&&c==n-1){
			for(int i=1;i<=n;i++)x[i]=i;
			for(int i=1;i<=n;i++)y[i]=z[i]=n-i+1;
			y[n-2]=3,y[n-1]=1,y[n]=2;
			z[n-2]=1,z[n-1]=3,z[n]=2;
			break;
		}
		if(a+b+c-2<=n){
		// cout<<n<<" "<<a<<" "<<b<<" "<<c<<"\n";
			for(int i=1;i<=n;i++)x[i]=i,y[i]=i,z[i]=i;
			int d=n-a;
			for(int i=1,s=0;i<=a;i++){
				int dd=min((long long)d,1ll*b*c-1);d-=dd;dd++;
				num[i]=dd;
				reverse(y+s+1,y+s+dd+1);s+=dd;
			}
			// for(int i=1;i<=a;i++)cout<<num[i]<<" ";cout<<"\n";
			reverse(num+1,num+a+1);
			reverse(z+1,z+n+1);
			for(int i=1,s=0;i<=a;i++)if(num[i]){
				int d=max(0,num[i]-c);
				for(int j=1;j<=c&&j<=num[i];j++){
					int dd=min(d,b-1);d-=dd,dd++;
					reverse(z+s+1,z+s+dd+1);s+=dd;
				}
			}
			break;
		}
		if(chk(n-1,a-1,b-1,c-1)){
			x[n]=y[n]=z[n]=n;
			n--,a--,b--,c--;
		}
		else{
			cout<<n<<" "<<a<<" "<<b<<" "<<c<<" err\n";
			exit(0);
		}
	}
	n=nn;
	if(o)print();
}

bool med;
int T;
signed main(){
	// freopen("lcs.in","r",stdin);
	// freopen("lcs.out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}