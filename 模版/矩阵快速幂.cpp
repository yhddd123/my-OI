int n,m=49;
struct mat{
	int e[55][55];
	mat(){mems(e,0);}
	mat operator*(const mat&tmp)const{
		mat res;
		for(int i=0;i<m;i++){
			for(int j=0;j<m;j++){
				for(int k=0;k<m;k++)(res.e[i][j]+=e[i][k]*tmp.e[k][j])%=mod;
			}
		}
		return res;
	}
}a,b;
mat one(){
	mat res;
	for(int i=0;i<m;i++)res.e[i][i]=1;
	return res;
}
mat ksm(mat a,int b){
	mat ans=one();
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}
mat pw[maxn];
mat mul(mat u,mat v){
	mat res;
	for(int j=0;j<m;j++){
		for(int k=0;k<m;k++)(res.e[0][j]+=u.e[0][k]*v.e[k][j])%=mod;
	}
	return res;
}
void work(){
	n=read();
	mat ans;ans.e[0][0]=1;
	for(int i=1;i<32;i++)pw[i]=pw[i-1]*pw[i-1];
}