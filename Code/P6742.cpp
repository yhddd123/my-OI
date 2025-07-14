#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1010;
const int inf=1e18;

int n,m;
char c[maxn];
int mp[maxn][maxn];
int x,y,ex,ey;
struct nd{
	int x,y;
}s;
int t[maxn][maxn];
int l[maxn][maxn],r[maxn][maxn],up[maxn][maxn],d[maxn][maxn];
int fx[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
queue<nd> q;
void sovle(){
	cin>>n>>m;
	memset(t,0x3f,sizeof(t));
	for(int j=1;j<=m+2;j++){
		mp[1][j]=mp[n+2][j]=2,
		l[1][j]=r[1][j]=up[1][j]=d[1][j]=-1;
		l[n+2][j]=r[n+2][j]=up[n+2][j]=d[n+2][j]=-1;
	}
	for(int i=1;i<=n+2;i++){
		mp[i][1]=mp[i][m+2]=2,
		l[i][1]=r[i][1]=up[i][1]=d[i][1]=-1;
		l[i][m+2]=r[i][m+2]=up[i][m+2]=d[i][m+2]=-1;
	}
	n+=2;m+=2;
	for(int i=2;i<n;i++){
		cin>>c+1;
		for(int j=2;j<m;j++){
			if(c[j-1]!='#'){
				mp[i][j]=1;
				if(c[j-1]=='S')x=i,y=j;
				if(c[j-1]=='C')ex=i,ey=j;
			}
			else{
				mp[i][j]=2;
				l[i][j]=r[i][j]=up[i][j]=d[i][j]=-1;
			}
		}
	}
//	cout<<x<<" "<<y<<" "<<ex<<" "<<ey<<"\n";
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)if(mp[i][j]==1)l[i][j]=l[i][j-1]+1;
		for(int j=n;j>=1;j--)if(mp[i][j]==1)r[i][j]=r[i][j+1]+1;
	}
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++)if(mp[i][j]==1)up[i][j]=up[i-1][j]+1;
		for(int i=n;i>=1;i--)if(mp[i][j]==1)d[i][j]=d[i+1][j]+1;
	}
	t[x][y]=0;
	q.push({x,y});
	while(!q.empty()){
		s=q.front();q.pop();
		if(s.x==ex&&s.y==ey)continue;
		for(int i=0;i<4;i++){
			int nx=s.x+fx[i][0],ny=s.y+fx[i][1];
			if(nx>=1&&ny>=1&&nx<=n&&ny<=m&&mp[nx][ny]==1&&t[nx][ny]>t[s.x][s.y]+1){
				t[nx][ny]=t[s.x][s.y]+1;
				q.push({nx,ny});
			}
		}
		if(!l[s.x][s.y]||!r[s.x][s.y]||!up[s.x][s.y]||!d[s.x][s.y]){
			if(t[s.x][s.y-l[s.x][s.y]]>t[s.x][s.y]+1 && s.y-l[s.x][s.y]>=1){
				t[s.x][s.y-l[s.x][s.y]]=t[s.x][s.y]+1;
				q.push({s.x,s.y-l[s.x][s.y]});
			}
			if(t[s.x][s.y+r[s.x][s.y]]>t[s.x][s.y]+1 && s.y+r[s.x][s.y]<=m){
				t[s.x][s.y+r[s.x][s.y]]=t[s.x][s.y]+1;
				q.push({s.x,s.y+r[s.x][s.y]});
			}
			if(t[s.x-up[s.x][s.y]][s.y]>t[s.x][s.y]+1 && s.x-up[s.x][s.y]>=1){
				t[s.x-up[s.x][s.y]][s.y]=t[s.x][s.y]+1;
				q.push({s.x-up[s.x][s.y],s.y});
			}
			if(t[s.x+d[s.x][s.y]][s.y]>t[s.x][s.y]+1 && s.x+d[s.x][s.y]<=n){
				t[s.x+d[s.x][s.y]][s.y]=t[s.x][s.y]+1;
				q.push({s.x+d[s.x][s.y],s.y});
			}
		}
		if(t[s.x][s.y-l[s.x][s.y]]>t[s.x][s.y]+min({r[s.x][s.y],up[s.x][s.y],d[s.x][s.y]})+1 && s.y-l[s.x][s.y]>=1){
			t[s.x][s.y-l[s.x][s.y]]=t[s.x][s.y]+min({r[s.x][s.y],up[s.x][s.y],d[s.x][s.y]})+1;
			q.push({s.x,s.y-l[s.x][s.y]});
		}
		if(t[s.x][s.y+r[s.x][s.y]]>t[s.x][s.y]+min({l[s.x][s.y],up[s.x][s.y],d[s.x][s.y]})+1 && s.y+r[s.x][s.y]<=m){
			t[s.x][s.y+r[s.x][s.y]]=t[s.x][s.y]+min({l[s.x][s.y],up[s.x][s.y],d[s.x][s.y]})+1;
			q.push({s.x,s.y+r[s.x][s.y]});
		}
		if(t[s.x-up[s.x][s.y]][s.y]>t[s.x][s.y]+min({l[s.x][s.y],r[s.x][s.y],d[s.x][s.y]})+1 && s.x-up[s.x][s.y]>=1){
			t[s.x-up[s.x][s.y]][s.y]=t[s.x][s.y]+min({l[s.x][s.y],r[s.x][s.y],d[s.x][s.y]})+1;
			q.push({s.x-up[s.x][s.y],s.y});
		}
		if(t[s.x+d[s.x][s.y]][s.y]>t[s.x][s.y]+min({l[s.x][s.y],r[s.x][s.y],up[s.x][s.y]})+1 && s.x+d[s.x][s.y]<=n){
			t[s.x+d[s.x][s.y]][s.y]=t[s.x][s.y]+min({l[s.x][s.y],r[s.x][s.y],up[s.x][s.y]})+1;
			q.push({s.x+d[s.x][s.y],s.y});
		}
	}
	cout<<t[ex][ey]<<"\n";
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	T=1;
	while(T--)sovle();
}
