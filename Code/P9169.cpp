// Problem: P9169 [省选联考 2023] 过河卒
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9169
// Memory Limit: 1 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-18 08:56:23
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=10;
const int maxm=1000000;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
int a[maxn][maxn];
int p1,p2,p3,p4,p5,p6;
char s[maxn];
int dp[maxm][2],f[maxm][2];
int head[maxm][2],tot;
struct nd{
	int nxt,to;
}e[maxm<<3];
void add(int u,int v,int fl){e[++tot]={head[u][fl],v};head[u][fl]=tot;}
inline int id(int i,int j,int ii,int jj,int k,int l){return i*100000+j*10000+ii*1000+jj*100+k*10+l;}
int fx1[4][2]={{0,-1},{0,1},{1,0},{-1,0}},fx2[3][2]={{-1,0},{0,1},{0,-1}};
int d[maxm][2];
pii q[maxm<<1];int h,t;
bool vis[maxm],bk[maxm];
void work(){
	n=read();m=read();
	p1=-1;
	for(int i=0;i<n;i++){
		scanf("%s",s);
		for(int j=0;j<m;j++){
			if(s[j]=='#')a[i][j]=1;
			else a[i][j]=0;
			if(s[j]=='O'){
				if(p1==-1)p1=i,p2=j;
				else p3=i,p4=j;
			}
			if(s[j]=='X')p5=i,p6=j;
		}
	}
	int sid=id(p1,p2,p3,p4,p5,p6),sfl=(p1+p2+p3+p4+p5+p6)&1;
	mems(head,0);tot=0;
	mems(vis,0);mems(d,0);
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)if(!a[i][j]){
			for(int ii=0;ii<n;ii++){
				for(int jj=0;jj<m;jj++)if(!a[ii][jj]&&(i!=ii||j!=jj)){
					for(int k=0;k<n;k++){	
						for(int l=0;l<m;l++)if(!a[k][l]){
							int nid=id(i,j,ii,jj,k,l);
							vis[nid]=1;
							if(!k)continue;
							if(i==k&&j==l)continue;
							if(ii==k&&jj==l)continue;
							// cout<<i<<" "<<j<<" "<<ii<<" "<<jj<<" "<<k<<" "<<l<<"\n";
							if(bk[nid]==sfl){
								for(int o=0;o<4;o++){
									int ni=i+fx1[o][0],nj=j+fx1[o][1];
									if(a[ni][nj]||ni<0||ni>=n||nj<0||nj>=m||(ni==ii&&nj==jj))continue;
									add(id(ni,nj,ii,jj,k,l),nid,0);d[nid][0]++;
								}
								for(int o=0;o<4;o++){
									int ni=ii+fx1[o][0],nj=jj+fx1[o][1];
									if(a[ni][nj]||ni<0||ni>=n||nj<0||nj>=m||(ni==i&&nj==j))continue;
									add(id(i,j,ni,nj,k,l),nid,0);d[nid][0]++;
								}
							}
							else{
								for(int o=0;o<3;o++){
									int ni=k+fx2[o][0],nj=l+fx2[o][1];
									if(a[ni][nj]||ni<0||ni>=n||nj<0||nj>=m)continue;
									add(id(i,j,ii,jj,ni,nj),nid,1);d[nid][1]++;
								}
							}
						}
					}
				}
			}
		}
	}
	mems(f,-1);mems(dp,0);h=0,t=-1;
	for(int i=0;i<maxm;i++)if(!d[i][0]&&vis[i]&&bk[i]==sfl){
		q[++t]={i,0},f[i][0]=0;
		// cout<<i<<"\n";
	}
	// cout<<d[sid][0]<<"\n";
	// for(int i:e[0][sid])cout<<sid<<" "<<i<<"\n";
	for(int i=0;i<maxm;i++)if(!d[i][1]&&vis[i]&&bk[i]!=sfl){
		if((i/10)%10==0)continue;
		q[++t]={i,1},f[i][1]=0;
	}
	while(h<=t){
		int u=q[h].fi,fl=q[h].se;h++;
		for(int i=head[u][fl^1];i;i=e[i].nxt){
			int v=e[i].to;
			if(f[v][fl^1]!=-1)continue;
			if(!f[u][fl]){
				if(f[v][fl^1]==-1){
					f[v][fl^1]=1,dp[v][fl^1]=dp[u][fl]+1;
					q[++t]={v,fl^1};
					continue;
				}
			}
			else{
				dp[v][fl^1]=dp[u][fl]+1;
			}
			--d[v][fl^1];
			if(!d[v][fl^1]){
				f[v][fl^1]=0;
				q[++t]={v,fl^1};
			}
		}
	}
	// cout<<d[sid][0]<<"\n";
	// cout<<sid<<"\n";
	if(f[sid][0]==-1)puts("Tie");
	else if(f[sid][0])printf("Red %lld\n",dp[sid][0]);
	else printf("Black %lld\n",dp[sid][0]);
}

// \
444

bool Med;
int T;
signed main(){
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
			for(int ii=0;ii<10;ii++)
				for(int jj=0;jj<10;jj++)
					for(int k=0;k<10;k++)
						for(int l=0;l<10;l++)bk[id(i,j,ii,jj,k,l)]=(i+j+ii+jj+k+l)&1;
	
	T=read();T=read();
	while(T--)work();
}
