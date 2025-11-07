#include<bits/stdc++.h>
#define int long long
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

mt19937 rnd(time(0));
int n,m,px,py;
int ask(int l1,int r1,int l2,int r2){
	cout<<"? "<<l1<<" "<<r1<<" "<<l2<<" "<<r2<<endl;
	// int x=read();
	// return x;
	int res=0;
	for(int i=l1;i<=r1;i++){
		for(int j=l2;j<=r2;j++)res+=(i==px||j==py);
	}
	return res;
}
void out(int x,int y){
	cout<<"! "<<x<<" "<<y<<endl;
	// assert(px==x&&py==y);
}
bool in(int u,int v){return 1<=u&&u<=n&&1<=v&&v<=m;}
void sovle(int l1,int r1,int l2,int r2){
	int n=r1-l1+1,m=r2-l2+1;
	cout<<l1<<" "<<r1<<" "<<l2<<" "<<r2<<"\n";
	if(n==2&&m==3){
		int p=l1>1?l1-1:r1+1;
		int x=ask(p,p,l2,l2);
		if(x)return sovle(l1,r1,l2,l2);
		else return sovle(l1,r1,l2+1,r2);
	}
	if(n==3&&m==2){
		int p=l2>1?l2-1:r2+1;
		int x=ask(l1,l1,p,p);
		if(x)return sovle(l1,l1,l2,r2);
		else return sovle(l1+1,r1,l2,r2);
	}
	if(n<=2&&m<=2){
		if(n<2){
			if(l1>1)l1--;
			else r1++;
		}
		if(m<2){
			if(l2>1)l2--;
			else r2++;
		}
		// cout<<n<<" "<<m<<" "<<l1<<" "<<r1<<" "<<l2<<" "<<r2<<endl;
		for(int i=l1;i<=r1;i++){
			for(int j=l2;j<=r2;j++){
				int o1=(i==l1?-1:1),o2=(j==l2?-1:1);
				for(int o=0;o<2;o++){
					if(o)o1*=2;
					else o2*=2;
					if(in(i+o1,j+o2)){
						int pl1=i+o1,pr1=i,pl2=j+o2,pr2=j;
						if(pl1>pr1)swap(pl1,pr1);
						if(pl2>pr2)swap(pl2,pr2);
						// cout<<i<<" "<<j<<" "<<o1<<" "<<o2<<" "<<pl1<<" "<<pr1<<" "<<pl2<<" "<<pr2<<endl;
						int x=ask(pl1,pr1,pl2,pr2);
						for(int i=l1;i<=r1;i++){
							for(int j=l2;j<=r2;j++){
								int res=0;
								for(int ii=pl1;ii<=pr1;ii++){
									for(int jj=pl2;jj<=pr2;jj++)res+=(i==ii||j==jj);
								}
								if(res==x)return out(i,j);
							}
						}
						assert(0);
					}
					if(o)o1/=2;
					else o2/=2;
				}
			}
		}
		// cout<<"run\n";
		int x=ask(l1,l1,l2,l2);
		if(x==1)return out(l1,l2);
		if(x==0)return out(r1,r2);
		x=ask(l1,l1,r2,r2);
		if(x==1)return out(l1,r2);
		else return out(l2,r1);
	}
	int m1=l1+(n+1)/2-1,m2=l2+(m+1)/2-1;
	if(!(n&1)&&!(m&1)&&n==m){
		if(l1>1){
			int x=ask(l1-1,m1,l2,m2);
			if(x==n)sovle(l1,m1,l2,m2);
			else if(x==n/2+1)sovle(m1+1,r1,l2,m2);
			else if(x==n/2)sovle(l1,m1,m2+1,r2);
			else sovle(m1+1,r1,m2+1,r2);
		}else{
			int x=ask(m1+1,r1+1,m2+1,r2);
			if(x==n)sovle(m1+1,r1,m2+1,r2);
			else if(x==n/2+1)sovle(l1,m1,m2+1,r2);
			else if(x==n/2)sovle(m1+1,r1,l2,m2);
			else sovle(l1,m1,l2,m2);
		}
	}
	else{
		if((n+1)/2==(m+1)/2){
			if(n&1)m1--;
			else m2--;
		}
		int x=ask(l1,m1,l2,m2);
		if(x==m1-l1+1+m2-l2+1-1)sovle(l1,m1,l2,m2);
		else if(x==m1-l1+1)sovle(m1+1,r1,l2,m2);
		else if(x==m2-l2+1)sovle(l1,m1,m2+1,r2);
		else sovle(m1+1,r1,m2+1,r2);
	}
}
void work(){
	n=read();m=read();
	// px=rnd()%n+1,py=rnd()%m+1;
	px=read(),py=read();
	// cout<<px<<" "<<py<<"\n";
	int p1=n/2,p2=n/2;
	if(p1==p2)p1++;
	int x=ask(1,p1,1,p2);
	// cout<<p1<<" "<<p2<<" "<<x<<"\n";
	if(x==p1+p2-1)sovle(1,p1,1,p2);
	else if(x==p1)sovle(p1+1,n,1,p2);
	else if(x==p2)sovle(1,p1,p2+1,m);
	else sovle(p1+1,n,p2+1,m);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}