#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=25;
const int maxc=65;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,k;
int mp[maxn][maxn];
int a[maxn][maxn][maxn];pii sz[maxn];
int t[maxc],num[maxn][maxc],c[maxc];
char s[maxn];
int id(char c){
	if(c>='a'&&c<='z')return c-'a'+1;
	if(c>='A'&&c<='Z')return c-'A'+1+26;
	if(c>='0'&&c<='9')return c-'0'+1+52;
}
char cid(int id){
	if(id<=26)return 'a'+id-1;
	if(id<=52)return 'A'+id-26-1;
	return '0'+id-52-1;
}
vector<pair<int,pii>> ans;
void mov(int x,int y,int xx,int yy){
	// cout<<x<<" "<<y<<" "<<xx<<" "<<yy<<"\n";
	while(x<xx)ans.push_back({-3,{x,y}}),swap(mp[x][y],mp[x+1][y]),x++;
	while(y<yy)ans.push_back({-1,{x,y}}),swap(mp[x][y],mp[x][y+1]),y++;
	while(y>yy)ans.push_back({-2,{x,y}}),swap(mp[x][y],mp[x][y-1]),y--;
	while(x>xx)ans.push_back({-4,{x,y}}),swap(mp[x][y],mp[x-1][y]),x--;
}
void work(){
	n=read();m=read(),k=read();
	sz[0]={n,m};
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)a[0][i][j]=id(s[j]),num[0][a[0][i][j]]++;
	}
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)mp[i][j]=id(s[j]),t[mp[i][j]]++;
	}
	for(int ii=1;ii<=k;ii++){
		int nn=read(),mm=read();sz[ii]={nn,mm};
		for(int i=1;i<=nn;i++){
			scanf("%s",s+1);
			for(int j=1;j<=mm;j++)a[ii][i][j]=id(s[j]),num[ii][a[ii][i][j]]++;
		}
	}
	for(int tim=0;tim<=k;tim++){
		for(int ii=0;ii<=k;ii++){
			int nn=sz[ii].fi,mm=sz[ii].se;
			int cnt=0;for(int i=1;i<=62;i++)cnt+=max(0ll,num[ii][i]-t[i]),c[i]=max(0ll,num[ii][i]-t[i]);
			if(cnt>t[0]||cnt==nn*mm)continue;
			// cout<<tim<<" "<<ii<<"\n";
			while(cnt<=t[0]&&cnt<nn*mm){
				for(int i=1;i<=nn;i++){
					for(int j=1;j<=mm;j++){
						int ch=a[ii][i][j];
						if(c[ch])c[ch]--,ch=0;
						// cout<<i<<" "<<j<<" "<<ch<<"\n";
						if(mp[i][j]!=ch){
							bool fl=0;
							for(int pi=1;pi<=n;pi++){
								for(int pj=1;pj<=m;pj++)if(mp[pi][pj]==ch){
									if(pi<i&&pj<=mm)continue;
									if(pi==i&&pj<=j)continue;
									mov(pi,pj,i,j);fl=1;break;
								}
								if(fl)break;
							}
						}
					}
				}
				for(int i=1;i<=nn;i++){
					for(int j=1;j<=mm;j++)if(mp[i][j])t[mp[i][j]]--,t[0]++,mp[i][j]=0;
				}
				ans.push_back({ii,{1,1}});
				cnt=0;for(int i=1;i<=62;i++)cnt+=max(0ll,num[ii][i]-t[i]),c[i]=max(0ll,num[ii][i]-t[i]);
			}
			// for(int i=1;i<=n;i++){for(int j=1;j<=m;j++)cout<<cid(mp[i][j]);cout<<"\n";}
			if(t[0]==n*m){
				if(!ans.back().fi)ans.pop_back();
				reverse(ans.begin(),ans.end());
				printf("%lld\n",(int)ans.size());
				for(auto [op,p]:ans)printf("%lld %lld %lld\n",op,p.fi,p.se);
				// for(auto [op,p]:ans){
					// if(op==-4)swap(a[0][p.fi][p.se],a[0][p.fi-1][p.se]);
					// if(op==-3)swap(a[0][p.fi][p.se],a[0][p.fi+1][p.se]);
					// if(op==-2)swap(a[0][p.fi][p.se],a[0][p.fi][p.se-1]);
					// if(op==-1)swap(a[0][p.fi][p.se],a[0][p.fi][p.se+1]);
					// if(op>0){
						// // cout<<op<<"\n";
						// // for(int i=1;i<=n;i++){for(int j=1;j<=m;j++)cout<<cid(a[0][i][j]);cout<<"\n";}
						// int nn=sz[op].fi,mm=sz[op].se;
						// for(int i=1;i<=nn;i++){
							// for(int j=1;j<=mm;j++)a[0][i][j]=a[op][i][j];
						// }
					// }
				// }
				// for(int i=1;i<=n;i++){for(int j=1;j<=m;j++)cout<<cid(a[0][i][j]);cout<<"\n";}
				return ;
			}
			break;
		}
	}
	puts("-1");
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
