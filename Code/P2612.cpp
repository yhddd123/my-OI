#include<bits/stdc++.h>
using namespace std;

const int maxn=110;
const int maxm=5000;

int n,m,k,cur;
long double f[2][maxn][maxm*2+1][3];
__float128 g[2][maxn][maxm*2+1][3];

inline void printRounded(long double x,int k){
	if(k<0) k=0; printf("%.*Lf", k, x);
}

inline void printRounded(__float128 x,int k){
	if(k<0) k=0;
	// handle sign (not expected negative here)
	if(x < 0) x = -x;
	int intPart = (int)x; // expected 0 or 1
	__float128 frac = x - ( __float128 )intPart;
	static char buf[1024];
	int pos = 0;
	buf[pos++] = char('0' + intPart);
	if(k == 0){ fwrite(buf,1,pos,stdout); return; }
	buf[pos++] = '.';
	// generate k+1 digits
	int extra = 1;
	int total = k + extra;
	static int dig[256];
	for(int i=0;i<total;i++){
		frac *= 10;
		int d = (int)frac;
		if(d < 0) d = 0; else if(d > 9) d = 9;
		dig[i] = d;
		frac -= ( __float128 )d;
	}
	// round half up
	int carry = (dig[k] >= 5);
	for(int i=k-1;i>=0 && carry;i--){
		int d = dig[i] + 1;
		dig[i] = d % 10;
		carry = d / 10;
	}
	if(carry){
		// increment integer part
		// rewrite head
		pos = 0;
		buf[pos++] = char('0' + min(1, intPart + 1));
		buf[pos++] = '.';
	}
	for(int i=0;i<k;i++) buf[pos++] = char('0' + dig[i]);
	fwrite(buf,1,pos,stdout);
}

template < class T >
void sovle(T f[][maxn][maxm*2+1][3]){
	f[0][0][maxm][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++){
			for(int k=0;k<=2*maxm;k++){
				for(int l=0;l<=2;l++)f[i&1][j][k][l]=0;
			}
		}
		for(int j=0;j<i;j++){
			for(int k=0;k<=2*maxm;k++){
				for(int l=0;l<=2;l++)if(f[cur][j][k][l]){
					if(k-2*i>=0)f[i&1][j+1][k-2*i][l]+=f[cur][j][k][l]*(j+1-l)/i;
					if(j)f[i&1][j][k+i-i][l]+=f[cur][j][k][l]*(2*j-l)/i;
					if(j>1&&k+2*i<=2*maxm)f[i&1][j-1][k+2*i][l]+=f[cur][j][k][l]*(j-1)/i;
					if(l<2){
						if(k-i>=0)f[i&1][j+1][k-i][l+1]+=f[cur][j][k][l]*(2-l)/i;
						if(j&&k+i<=2*maxm)f[i&1][j][k+i][l+1]+=f[cur][j][k][l]*(2-l)/i;
					}
				}
			}
		}
		cur^=1;
	}
	T ans=0;for(int i=maxm+m;i<=2*maxm;i++)ans+=f[n&1][1][i][2];
	printRounded(ans,k);
}

signed main(){
	cin>>n>>m>>k;
	if(k<=8)sovle(f);
	else sovle(g);
}