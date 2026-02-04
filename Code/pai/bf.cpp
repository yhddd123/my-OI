#include<bits/stdc++.h>
#define LL long long
#define LLL __int128
#define uint unsigned
#define ldb long double
#define uLL unsigned long long
using namespace std;
namespace BasicMath{
	typedef vector<int> poly;
	typedef vector<int> Vec;
	typedef vector<Vec> Mat;
	typedef tuple<poly,poly,poly,poly> Mat2;
	mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
	const int Mod=998244353,Mod_G=3;
	const LL Mod2=(LL)Mod*Mod;
	poly frc({1,1}),inv({0,1}),ivf({1,1});
	inline int qpow(int x,int y,int z=1){
		for(;y;(y>>=1)&&(x=(LL)x*x%Mod))if(y&1)z=(LL)z*x%Mod;return z;
	}
	inline void Init(const int&n){
		for(int i=frc.size();i<=n;++i)
			frc.emplace_back((LL)frc.back()*i%Mod),
			inv.emplace_back(Mod-Mod/i*(LL)inv[Mod%i]%Mod),
			ivf.emplace_back((LL)ivf.back()*inv.back()%Mod);
	}
	inline int Binom(const int&n,const int&m){
		if(n<m||m<0)return 0;
		return Init(n),(LL)frc[n]*ivf[m]%Mod*ivf[n-m]%Mod;
	}
	inline poly invLinear(poly P){
		const int n=P.size();
		poly Q(n+1,1);
		for(int i=0;i<n;++i)Q[i+1]=(LL)Q[i]*P[i]%Mod;
		int t=qpow(Q[n],Mod-2);Q.pop_back();
		for(int i=n;i--;)Q[i]=(LL)Q[i]*t%Mod,t=(LL)t*P[i]%Mod;
		return Q;
	}
	inline uLL trans(const uLL&x){
		constexpr uLL A=-(uLL)Mod/Mod+1;
		constexpr uLL Q=(((__uint128_t)(-(uLL)Mod%Mod)<<64)+Mod-1)/Mod;
		return x*A+(uLL)((__uint128_t)x*Q>>64)+1;
	}
	inline uLL mul(const uLL&x,const uLL&y){
		return x*y*(__uint128_t)Mod>>64;
	}
	inline int add(int x,const int&y){
		return ((x+=y)-Mod)>=0?x-Mod:x;
	}
	inline int sub(int x,const int&y){
		return (x-=y)<0?x+Mod:x;
	}
	inline int neg(const int&x){
		return x?Mod-x:0;
	}
	inline int div2(const int&x){
		return x&1?(x+Mod)>>1:x>>1;
	}
}
namespace Polynomial{
	using namespace BasicMath;
	vector<uLL>Grt,iGrt;
	inline bool Empty(poly&P){
		for(;!P.empty()&&!P.back();P.pop_back());
		return P.empty();
	}
	inline poly Slice(poly&P,int l,int r){
		if(r<=0||l>=(int)P.size())return poly(r-l);
		if(0<=l&&r<=(int)P.size())return poly(P.begin()+l,P.begin()+r);
		poly Q;
		if(l<0)Q.insert(Q.end(),-l,0),l=0;
		if(r<=(int)P.size())Q.insert(Q.end(),P.begin()+l,P.begin()+r);
		else Q.insert(Q.end(),P.begin()+l,P.end()),Q.insert(Q.end(),r-P.size(),0);
		return Q;
	}
	inline void Reduce(poly&P,int n){
		for(int i=P.size()-1;i>=n;--i)P[i-n]=add(P[i-n],P[i]);
		P.resize(n);
	}
	inline poly Add(poly P,poly Q){
		if(P.size()<Q.size())P.swap(Q);
		for(int i=Q.size();i--;)P[i]=add(P[i],Q[i]);
		return P;
	}
	inline poly Add_Empty(poly P,poly Q){
		if(P.size()<Q.size())P.swap(Q);
		for(int i=Q.size();i--;)P[i]=add(P[i],Q[i]);
		return Empty(P),P;
	}
	inline poly Sub(poly P,poly Q){
		if(P.size()<Q.size())P.resize(Q.size());
		for(int i=Q.size();i--;)P[i]=sub(P[i],Q[i]);
		return P;
	}
	inline poly Sub_Empty(poly P,poly Q){
		if(P.size()<Q.size())P.resize(Q.size());
		for(int i=Q.size();i--;)P[i]=sub(P[i],Q[i]);
		return Empty(P),P;
	}
	inline poly Mulx(poly P,int x){
		const uLL v=trans(x);
		for(int&i:P)i=mul(i,v);
		return P;
	}
	inline poly Neg(poly P){
		for(int i=P.size();i--;)P[i]&&(P[i]=Mod-P[i]);
		return P;
	}
	inline int Eval(poly&P,int x){
		int z=0;
		for(int i=P.size();i--;)z=((LL)z*x+P[i])%Mod;
		return z;
	}
	inline void extend(const int&n){
		if(Grt.empty())Grt.emplace_back(trans(1)),iGrt.emplace_back(trans(1));
		if((int)Grt.size()<n){
			int L=Grt.size();
			for(Grt.resize(n),iGrt.resize(n);L<n;L*=2){
				const int w=qpow(Mod_G,Mod/(L*4)),iw=qpow(w,Mod-2);
				for(int i=0;i<L;++i)Grt[i+L]=trans(mul(Grt[i],w)),iGrt[i+L]=trans(mul(iGrt[i],iw));
			}
		}
	}
	template<int A,int B,int C=0,class fun>inline void Butterrep(int i,int j,int k,fun F){
		if(A!=C)F(i,j+C/B,k+C*2-C%B),Butterrep<A,B,C+(C<A)>(i,j,k,F);
	}
	template<int i,class fun>inline void Butter(int n,fun F){
		if(n>32)for(int j=0;2*i*j<n;j+=32/i)Butterrep<32,i>(i,j,2*i*j,F);
		else if(i<n)for(int j=0;2*i*j<n;++j)for(int k=0;k<i;++k)F(i,j,k+2*i*j);
	}
	template<class T>inline void DFT(T P,int n){
		extend(n);
		const auto F=[&](int x,int y,int z){const int a=P[z],b=mul(P[z+x],Grt[y]);P[z]=add(a,b),P[z+x]=sub(a,b);};
		for(int i=n>>1;i>16;i>>=1)for(int j=0;2*i*j<n;++j)for(int k=0;k<i;k+=32)Butterrep<32,32>(i,j,k+2*i*j,F);
		Butter<16>(n,F),Butter<8>(n,F),Butter<4>(n,F),Butter<2>(n,F),Butter<1>(n,F);
	}
	template<class T>inline void IDFT(T P,int n){
		const uLL ni=trans(Mod-(Mod-1)/n);
		for(int i=0;i<n;++i)P[i]=mul(P[i],ni);
		extend(n);
		const auto F=[&](int x,int y,int z){const int a=P[z],b=P[z+x];P[z]=add(a,b),P[z+x]=mul(a-b+Mod,iGrt[y]);};
		Butter<1>(n,F),Butter<2>(n,F),Butter<4>(n,F),Butter<8>(n,F),Butter<16>(n,F);
		for(int i=32;i<n;i<<=1)for(int j=0;2*i*j<n;++j)for(int k=0;k<i;k+=32)Butterrep<32,32>(i,j,k+2*i*j,F);
	}
	template<class T>inline void rDFT(T P,int n){
		extend(n);
		const auto F=[&](int x,int y,int z){const int a=P[z],b=mul(P[z+x],Grt[y]);P[z]=add(a,b),P[z+x]=sub(a,b);};
		for(int i=n>>1,t=1;i;i>>=1,t<<=1)for(int j=0;2*i*j<n;++j)for(int k=0;k<i;++k)F(i,j+t,k+2*i*j);
	}
	template<class T>inline void rIDFT(T P,int n){
		const uLL ni=trans(Mod-(Mod-1)/n);
		for(int i=0;i<n;++i)P[i]=mul(P[i],ni);
		extend(n);
		const auto F=[&](int x,int y,int z){const int a=P[z],b=P[z+x];P[z]=add(a,b),P[z+x]=mul(a-b+Mod,iGrt[y]);};
		for(int i=1,t=n>>1;i<n;i<<=1,t>>=1)for(int j=0;2*i*j<n;++j)for(int k=0;k<i;++k)F(i,j+t,k+2*i*j);
	}
	inline void DFT(poly&P){DFT(P.begin(),P.size());}
	inline void IDFT(poly&P){IDFT(P.begin(),P.size());}
	inline void rDFT(poly&P){rDFT(P.begin(),P.size());}
	inline void rIDFT(poly&P){rIDFT(P.begin(),P.size());}
	poly Mul(poly P,poly Q){
		if(P.empty()||Q.empty())return poly();
		const int pn=P.size(),qn=Q.size(),rn=pn+qn-1;
		if(min(pn,qn)<=32||max(pn,qn)<=64){
			if(pn<=qn){
				vector<uLL>H(rn);
				for(int i=0;i<pn;++i){
					if(i%8==0)for(int j=qn;j--;)(H[i+j]+=1ll*P[i]*Q[j])>=(Mod2<<3)&&(H[i+j]-=Mod2<<3);
					else for(int j=qn;j--;)H[i+j]+=1ll*P[i]*Q[j];
				}
				Q.resize(rn);
				for(int i=rn;i--;)Q[i]=H[i]%Mod;
				return Q;
			}
			else{
				vector<uLL>H(rn);
				for(int i=0;i<qn;++i){
					if(i%8==0)for(int j=pn;j--;)(H[i+j]+=1ll*Q[i]*P[j])>=(Mod2<<3)&&(H[i+j]-=Mod2<<3);
					else for(int j=pn;j--;)H[i+j]+=1ll*Q[i]*P[j];
				}
				P.resize(rn);
				for(int i=rn;i--;)P[i]=H[i]%Mod;
				return P;
			}
		}
		if(rn<=256){
			const int k=max(pn,qn)/2;
			poly A=(k<pn?poly(P.begin()+k,P.end()):poly());
			poly B=(k<pn?poly(P.begin(),P.begin()+k):P);
			poly C=(k<qn?poly(Q.begin()+k,Q.end()):poly());
			poly D=(k<qn?poly(Q.begin(),Q.begin()+k):Q);
			poly AC=Mul(A,C),BD=Mul(B,D),H=Sub(Mul(Add(A,B),Add(C,D)),Add(AC,BD));
			AC.insert(AC.begin(),k*2,0),H.insert(H.begin(),k,0);
			H=Add(AC,Add(H,BD));
			return H.resize(rn),H;
		}
		const int m=2<<__lg(max(1,rn-1));
		P.resize(m),Q.resize(m);
		DFT(P),DFT(Q);
		for(int i=m;i--;)P[i]=(LL)P[i]*Q[i]%Mod;
		IDFT(P);
		return P.resize(rn),P;
	}
	poly MulT(poly P,poly Q){
		if(P.empty()||Q.empty())return poly();
		reverse(Q.begin(),Q.end());
		const int pn=P.size(),qn=Q.size(),m=2<<__lg(max(1,pn-1));
		P.resize(m),Q.resize(m);
		DFT(P),DFT(Q);
		for(int i=m;i--;)P[i]=(LL)P[i]*Q[i]%Mod;
		IDFT(P);
		return Slice(P,qn-1,pn);
	}
	poly Inv(poly P){
		const int pn=P.size();
		const int m=2<<__lg(max(1,pn-1));
		poly Q({qpow(P[0],Mod-2)}),F,dQ;
		Q.reserve(m);
		for(int n=1;n<m;n*=2){
			F=Slice(P,0,n*2),dQ=Q;
			dQ.resize(n*2),DFT(dQ),DFT(F);
			for(int i=0;i<n*2;++i)F[i]=(LL)(Mod-F[i])*dQ[i]%Mod;
			IDFT(F),fill_n(F.begin(),n,0),DFT(F);
			for(int i=0;i<n*2;++i)dQ[i]=(LL)F[i]*dQ[i]%Mod;
			IDFT(dQ),Q.insert(Q.end(),dQ.begin()+n,dQ.end());
		}
		return Q.resize(pn),Q;
	}
	poly Quo(poly F,poly P){
		const int pn=P.size();
		if(pn<=64){
			const uLL r=trans(qpow(P[0],Mod-2));
			for(int i=0;i<pn;++i){
				LLL v=F[i];
				for(int j=0;j<i;++j)v-=(LLL)F[j]*P[i-j];
				if((F[i]=v%Mod)<0)F[i]+=Mod;
				F[i]=mul(F[i],r);
			}
			return F;
		}
		const int BL=max(1,__lg(pn)),m=2<<__lg(max(1,(pn-1)/BL)),L=(pn-1)/m+1;
		poly H(Slice(F,0,m)),Q=Inv(Slice(P,0,m));
		vector<poly>A(L),B(L-1);
		Q.resize(m*2),H.resize(m*2),DFT(Q),DFT(H);
		for(int i=0;i<m*2;++i)H[i]=(LL)H[i]*Q[i]%Mod;
		IDFT(H),H.resize(m);
		A[0]=Slice(P,0,m),A[0].resize(m*2),DFT(A[0]);
		for(int k=1;k<L;++k){
			A[k]=Slice(P,k*m,(k+1)*m),A[k].resize(m*2),DFT(A[k]);
			B[k-1]=Slice(H,(k-1)*m,k*m),B[k-1].resize(m*2),DFT(B[k-1]);
			poly C(m*2);
			for(int j=0;j<k;++j){
				for(int i=0;i<m;++i)C[i]=(C[i]+(LL)(A[k-j][i]+A[k-1-j][i])*(Mod-B[j][i]))%Mod;
				for(int i=m;i<m*2;++i)C[i]=(C[i]+(LL)(A[k-j][i]+Mod-A[k-1-j][i])*(Mod-B[j][i]))%Mod;
			}
			IDFT(C),fill_n(C.begin()+m,m,0),C=Add(C,Slice(F,k*m,(k+1)*m)),DFT(C);
			for(int i=0;i<m*2;++i)C[i]=(LL)C[i]*Q[i]%Mod;
			IDFT(C),H.insert(H.end(),C.begin(),C.begin()+m);
		}
		return H.resize(pn),H;
	}
	poly PointShift(poly,int,int);
	poly Div(poly,poly);
	pair<poly,poly>DivMod(poly,poly);
	poly ModPow(poly,LL,poly);
	Mat2 Hgcd(poly,poly,int);
	poly Gcd(poly,poly);
	poly Qpow(poly,int);
}
using namespace BasicMath;
using namespace Polynomial;
inline poly solve(poly a,poly F){
    const int n=a.size();
    if(n==1)return poly({(int)(accumulate(F.begin(),F.end(),0ll)%Mod)});
    const int m=(n+1)/2;
    for(int i=m;i<n;++i)a[i]-=a[m-1];
    poly Q=poly(F.begin()+a[m-1],F.end());
    Q=solve(poly(a.begin()+m,a.end()),Q);
    a.resize(m),F.resize(a.back());
    const auto col=[&](poly A,const int&d){
        if(d<0||A.empty())return A;
        poly B(A.size());
        for(int i=A.size();i--;)B[i]=Binom(i+d,i);
        return A.resize(A.size()*2-1),MulT(A,B);
    };
    const auto row=[&](poly A,const int&d){
        if(A.empty())return poly(d);
        for(int i=A.size();i--;)A[i]=(LL)A[i]*ivf[i]%Mod;
        Init(A.size()+d-1);
        poly B=MulT(poly(frc.begin(),frc.begin()+A.size()+d-1),A);
        for(int i=B.size();i--;)B[i]=(LL)B[i]*ivf[i]%Mod;
        return reverse(B.begin(),B.end()),B;
    };
    poly A=solve(a,Add(row(Q,a.back()),col(F,n-m-1)));
    poly B=Add(row(F,n-m),col(Q,a.back()-1));
    A.insert(A.end(),B.begin(),B.end());
    return A;
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
    int n;cin>>n;
    poly a(n);for(int&i:a)cin>>i;
    poly ans=solve(a,poly(a.back(),1));
    for(int i:ans)cout<<i<<' ';
    cout<<"1 ";
	return 0;
}