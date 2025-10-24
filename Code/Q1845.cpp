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

int n;
int t[10];
int v[6]={1,4,6,5,2,0};
int calc(int l,int r){
	return (v[r%6]-v[(l+5)%6]+7)%7;
}
mt19937 rnd(time(0));
vector<int> get(int n,int m){
	vector<int> a,b;
	for(int i=1;i<n;i++){
		int p=rnd()%(m-1)+1;
		b.pb(p);
	}
	b.pb(0),b.pb(m);
	sort(b.begin(),b.end());
	for(int i=1;i<b.size();i++)if(b[i]!=b[i-1])a.pb(b[i]-b[i-1]);
	return a;
}
pii a[55];
int num=0,mx;
void work(){
	long long s=0;for(int i=0;i<10;i++)t[i]=read(),s+=t[i];
	if(s<=8){
		int m=0;
		for(int i=0;i<10;i++){
			for(int j=1;j<=t[i];j++)a[++m]={i,1};
		}
		do{
			int s=0;
			for(int i=1,l=0;i<=m;i++){
				(s+=calc(l,l+a[i].se-1)*a[i].fi)%=7;
				l+=a[i].se;l%=6;
			}
			if(!s){
				int mm=0;
				for(int i=1;i<=m;i++){
					if(mm&&a[mm].fi==a[i].fi)a[mm].se+=a[i].se;
					else a[++mm]=a[i];
				}
				printf("%d\n",mm);
				for(int i=mm;i;i--)printf("%d %d\n",a[i].se,a[i].fi);
				return ;
			}
		}while(next_permutation(a+1,a+m+1));
		puts("-1");
		return ;
	}
	for(int i=0;i<10;i++)if(s==t[i]){
		if(calc(0,t[i]-1)*i%7==0)printf("1\n%d %d\n",t[i],i);
		else puts("-1");
		return ;
	}
	int p1=-1,p2=-1,fl=1;
	for(int i=0;i<10;i++){
		if(t[i]){
			if(t[i]>1){
				if(p1!=-1)fl=0;
				p1=i;
			}else{
				if(p2!=-1)fl=0;
				p2=i;
			}
		}
	}
	if(fl){
		for(int i=0;i<7;i++){
			int s=calc(0,i)*p1+calc(i+1,i+1)*p2+calc(i+2,t[p1])*p1;
			if(s%7==0){
				printf("3\n%d %d\n%d %d\n%d %d\n",t[p1]-i-1,p1,1,p2,i+1,p1);
				return ;
			}
		}
		++num;
		puts("-1");
		return ;
	}
	int cnt=1000;
	map<vector<pii>,bool> vis;
	for(int T=1;cnt>=0&&T<=60;T++){
		int m=0;
		for(int i=0;i<10;i++){
			vector<int> b=get(min(t[i],3),t[i]);
			for(int j:b)a[++m]={i,j};
		}
		vector<pii> hsh;
		for(int i=1;i<=m;i++)hsh.pb({a[i].fi,a[i].se%6});
		sort(hsh.begin(),hsh.end());
		if(vis[hsh])continue;vis[hsh]=1;
		int fac=1;for(int i=1;i<=m;i++)fac=min(101,fac*i);
		if(m>4){
			for(int T1=1;T1<=100;T1++){
				shuffle(a+1,a+m+1,rnd);
				// for(int i=1;i<=m;i++)cout<<a[i].fi<<" "<<a[i].se<<"\n";
				int s=0;
				for(int i=1,l=0;i<=m;i++){
					(s+=calc(l,l+a[i].se-1)*a[i].fi)%=7;
					l+=a[i].se;l%=6;
				}
				if(!s){
					int mm=0;
					for(int i=1;i<=m;i++){
						if(mm&&a[mm].fi==a[i].fi)a[mm].se+=a[i].se;
						else a[++mm]=a[i];
					}
					printf("%d\n",mm);
					for(int i=mm;i;i--)printf("%d %d\n",a[i].se,a[i].fi);
					return ;
				}
			}
		}
		else{
			sort(a+1,a+m+1);
			do{
				int s=0;
				for(int i=1,l=0;i<=m;i++){
					s+=calc(l,l+a[i].se-1)*a[i].fi;
					l+=a[i].se;l%=6;
				}
				if(s%7==0){
					int mm=0;
					for(int i=1;i<=m;i++){
						if(mm&&a[mm].fi==a[i].fi)a[mm].se+=a[i].se;
						else a[++mm]=a[i];
					}
					printf("%d\n",mm);
					for(int i=mm;i;i--)printf("%d %d\n",a[i].se,a[i].fi);
					return ;
				}
			}while(next_permutation(a+1,a+m+1));
		}
		// cout<<m<<" "<<fac<<" a\n";
		cnt-=fac;
		mx=max(mx,T);
	}
	++num;
	puts("-1");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
	cerr<<num<<" "<<mx<<"\n";
}