#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=350;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a,b,d;
int mp[maxn][maxn],a[maxn][maxn],sx,sy,ex,ey;
int fx[8][2]={{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
string s;
struct nd{
	int x,y;
};
struct ans{
	int tim,sum,cnt;
}dis[maxn][maxn];
queue<nd> q;

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	n=read();m=read();a=read();b=read();d=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			dis[i][j].tim=dis[i][j].sum=dis[i][j].cnt=inf;
			cin>>s;
			if(s[0]=='.')mp[i][j]=1;
			else if(s[0]=='S'){
				mp[i][j]=1;
				sx=i;sy=j;
			}
			else if(s[0]=='T'){
				mp[i][j]=2;
				ex=i;ey=j;
			}
			else{
				int x=0;
				for(int k=0;k<s.size();k++){
					x+=s[k]-'0';
					x*=10; 
				}
				for(int k=-x+1;k<=x-1;k++){
					if(k>=1&&k<=n){
						a[i+k][j+x-1-abs(k)+1]--;
						a[i+k][j-(x-1-abs(k))]++
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]+=a[i][j-1];
			if(a[i][j])mp[i][j]=0;
		}
	}
	dis[sx][sy].tim=dis[sx][sy].sum=dis[sx][sy].cnt=0;
	q.push({sx,sy});
	while(!q.empty()){
		nd t=q.front();q.pop();
		for(int i=0;i<8;i++){
			int nx=t.x+fx[i][0],ny=t.y+fx[i][1];
			if(nx>=1&&nx<=n&&ny>=1&&ny<=m){
				if(dis[nx][ny].tim>dis[t.x][t.y].tim+1){
					dis[nx][ny].tim=dis[t.x][t.y].tim+1;
					dis[nx][ny].sum=dis[t.x][t.y].sum+(!mp[nx][ny]);
					dis[nx][ny].cnt=dis[t.x][t.y].cnt+(!mp[nx][ny]);
					q.push({nx,ny});
				}
				else if(dis[nx][ny].tim==dis[t.x][t.y].tim+1){
					if(dis[nx][ny].sum>dis[t.x][t.y].sum+(!mp[nx][ny])){
						dis[nx][ny].sum=dis[t.x][t.y].sum+(!mp[nx][ny]);
						dis[nx][ny].cnt=dis[t.x][t.y].cnt+(!mp[nx][ny]);
						q.psuh({nx,ny});
					}
					else if(dis[nx][ny].sum==dis[t.x][t.y].sum+(!mp[nx][ny])){
						if(dis[nx][ny].cnt>dis[t.x][t.y].cnt+(!mp[nx][ny])){
							dis[nx][ny].cnt=dis[t.x][t.y].cnt+(!mp[nx][ny]);
							q.push({nx,ny});
						}
					}
				}
			}
		}
		for(int i=0;i<4;i++){
			int nx=t.x+f[i][0]*d,ny=t.y+f[i][1]*d;
			if(nx>=1&&nx<=n&&ny>=1&&ny<=m){
				if(dis[nx][ny].tim>dis[t.x][t.y].tim+1){
					dis[nx][ny].tim=dis[t.x][t.y].tim+1;
					dis[nx][ny].sum=dis[t.x][t.y].sum+(!mp[nx][ny])+1;
					dis[nx][ny].cnt=dis[t.x][t.y].cnt+(!mp[nx][ny]);
					q.push({nx,ny});
				}
				else if(dis[nx][ny].tim==dis[t.x][t.y].tim+1){
					if(dis[nx][ny].sum>dis[t.x][t.y].sum+(!mp[nx][ny])+1){
						dis[nx][ny].sum=dis[t.x][t.y].sum+(!mp[nx][ny])+1;
						dis[nx][ny].cnt=dis[t.x][t.y].cnt+(!mp[nx][ny]);
						q.psuh({nx,ny});
					}
					else if(dis[nx][ny].sum==dis[t.x][t.y].sum+(!mp[nx][ny])+1){
						if(dis[nx][ny].cnt>dis[t.x][t.y].cnt+(!mp[nx][ny])){
							dis[nx][ny].cnt=dis[t.x][t.y].cnt+(!mp[nx][ny]);
							q.push({nx,ny});
						}
					}
				}
			}
		}
	}
	if(dis[ex][ey].tim==inf)printf("-1\n");
	else printf("%lld %lld %lld\n",dis[ex][ey].tim,dis[ex][ey].sum,dis[ex][ey].cnt);
}

/*
. 1 T 1
. . / 2
. 1 . /
S . . .
1 . . .
*/
