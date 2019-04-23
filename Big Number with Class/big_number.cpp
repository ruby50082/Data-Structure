#include <iostream>
#include <cstdlib>
#include <fstream>
#include "big_number.h"
using namespace std;


int num,i,j,c,t,r,n,m,p,q,x_num,y_num,x_temp,index1,index2;
int div_ans[20001],x[20001],y[20001],temp_x[20001];
int mult[1],temp_ans[20001],temp_ans2[20001];
int flag=0,flag2=0;
char ch;
string xx, yy;


BigNum :: BigNum(){
	len=0;
	sign=1;
	for(int i=0;i<40001;i++){
		x[i]=0;
	}
}

BigNum :: BigNum(const BigNum& x)
{	
	*this = x;
}

BigNum BigNum :: operator+(const BigNum& in)
{
	BigNum tmp(*this);
	int maxi = max(tmp.len,in.len);
	
	if((tmp.sign * in.sign)==1){
		for(i=0;i<maxi;i++){
			tmp.x[i]+=in.x[i];
			if(tmp.x[i]>=10){
				tmp.x[i+1]+=tmp.x[i]/10;
				tmp.x[i]=tmp.x[i]%10;
			}
		}
		tmp.len=maxi+1;
	}
	
	else if(tmp.sign==1 && in.sign==-1){
		BigNum tmp2(in);
		tmp2.sign=1;
		tmp=tmp-tmp2;
	}
	else if(tmp.sign==-1 && in.sign==1){
		BigNum tmp2(in);
		tmp.sign=1;
		tmp=tmp2-tmp;
	}
	while(tmp.len>=0 && tmp.x[tmp.len]==0)	tmp.len--;
	if(tmp.len<1)	tmp.len=1;
	else			tmp.len++;
	return tmp;
}

BigNum BigNum :: operator-(const BigNum& in)
{
	BigNum tmp(*this);
	BigNum ans;
	ans.len = max(tmp.len,in.len);
	if(tmp.sign==1 && in.sign==1){
		if(tmp.len>in.len){
			for(i=0;i<tmp.len;i++){
				ans.x[i]=tmp.x[i]-in.x[i];
				if(ans.x[i]<0){
					tmp.x[i+1]-=1;
					tmp.x[i]+=10;
				}
			}
			ans.sign=1;
		}
		else if(tmp.len<in.len){
			for(i=0;i<in.len;i++){
				ans.x[i]=in.x[i]-tmp.x[i];
			}
			for(i=0;i<in.len;i++){
				if(ans.x[i]<0){
					ans.x[i+1]-=1;
					ans.x[i]+=10;
				}
			}
			ans.sign=-1;
		}
		else{
			ans.sign=1;
			for(i=tmp.len-1;i>=0;i--){
				if(in.x[i]>tmp.x[i]){
					ans.sign=(-1);
					break;
				}
			}
			
			if(ans.sign==1){
				for(i=0;i<tmp.len;i++){
					ans.x[i]=tmp.x[i]-in.x[i];
					if(tmp.x[i]<0){
						ans.x[i+1]-=1;
						ans.x[i]+=10;
					}
				}
			}
			else{
				for(i=0;i<in.len;i++){
					ans.x[i]=in.x[i]-tmp.x[i];
				}
				for(i=0;i<in.len;i++){
					if(ans.x[i]<0){
						ans.x[i+1]-=1;
						ans.x[i]+=10;
					}
				}
			}
		}
	}
	else if(tmp.sign * in.sign==-1){
		BigNum tmp2(tmp), tmp3(in);
		if(tmp.sign==-1){
			tmp2.sign=-1;
			tmp3.sign=-1;
			ans=tmp2+tmp3;
		}
		if(in.sign==-1){
			tmp2.sign=1;
			tmp3.sign=1;
			ans=tmp2+tmp3;
		}
	}
	else{
		BigNum tmp2(tmp), tmp3(in);
		tmp2.sign=1;
		tmp3.sign=1;
		ans=tmp3-tmp2;
	}
	while(ans.len>=0 && ans.x[ans.len]==0)	ans.len--;
	if(ans.len<1)	ans.len=1;
	else			ans.len++;
	return ans;
};

BigNum BigNum :: operator*(const BigNum& in)
{
	BigNum tmp(*this),ans;
	tmp.sign = tmp.sign * in.sign;
	
	ans.len = tmp.len+in.len;
	for(int i=0;i<in.len;i++){
		for(int t=0;t<tmp.len;t++){
			ans.x[i+t]+=(tmp.x[t]*in.x[i]);
			if(ans.x[i+t]>=10){
				ans.x[i+t+1]+=((ans.x[i+t])/10);
				ans.x[i+t]=(ans.x[i+t]%10);
			}
		}
	}
	while(ans.len>=0 && ans.x[ans.len]==0)	ans.len--;
	if(tmp.len<1)	ans.len=1;
	else			ans.len++;
	return ans;
}

BigNum BigNum :: operator/(const BigNum& in)
{
	BigNum tmp(*this),temp_x,ans;
	
	if(tmp.len>=in.len){
		for(m=tmp.len;m>=in.len;m--){		 
			if(tmp.len==in.len){			
				while(1){
					for(q=tmp.len-1;q>=0;q--){
						if(tmp.x[q]<in.x[q])	break;	
					}
					div_ans[0]++;
					for(q=0;q<in.len;q++){
						tmp.x[q]-=in.x[q];
						if(tmp.x[q]<0){
							tmp.x[q]+=10;
							tmp.x[q+1]-=1;
						}	
					}	
				}	
			}
			else{
				for(p=in.len;p>=0;p--){
					temp_x.x[p]=tmp.x[p+m-in.len];
				}
				while(temp_x.sign==1){
					temp_x=temp_x-in;
					div_ans[m-in.len]++;
				}
			
			}
		}
	}
	return tmp;
}

istream& operator>>(istream &in,BigNum& out){
	string tmp;
	in>>tmp;
	out.len=0;
	
	for(int i=0;i<40001;i++)	out.x[i]=0;
	if(tmp[0]=='-') out.sign=-1;
    else out.sign=1;
    int check=(out.sign<0?1:0);
    for(int i=tmp.length()-1;i>=check;i--){
        out.x[out.len]=(tmp[i]-'0');
        out.len++;
    }
	return in;
}

ostream& operator<<(ostream &out,const BigNum &in)
{
	if(in.sign==-1)	out<<'-';
	for(int i=in.len-1;i>=0;i--){
		out<<in.x[i];
	}
	return out;
}
