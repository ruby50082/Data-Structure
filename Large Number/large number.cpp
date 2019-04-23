#include<iostream>
#include<fstream>
using namespace std;

void opera_minus(int x[],int y[],int x_fin,int y_fin);
void opera_plus(int x[],int y[],int x_amt,int y_amt);
void opera_time(int x[],int y[],int x_amt,int y_amt);
int compare(int m,int n,int a[],int b[]);

int num,i,c,t,r,n,m,p,q,x_num,y_num,x_temp,index1,index2;
int ans[20001],div_ans[20001],x[20001],y[20001],temp_x[20001];
int mult[1],temp_ans[20001],temp_ans2[20001];
int flag=0,flag2=0;
char char_x[20001],char_y[20001];
char ch;
char opera[1];
string xx, yy;

int main(int argc,char **argv)
{
	fstream fin;
	fin.open(argv[1],ios::in);
	
	fin>>num;
	for(r=0;r<num;r++){
		for(n=0;n<20001;n++){
			x[n]=0;
			y[n]=0;
			temp_x[n]=0;
			div_ans[n]=0;
			ans[n]=0;
			temp_ans[n]=0;
			temp_ans2[n]=0;
		}
		for(n=0;n<40001;n++){
			ans[n]=0;
		}
		
		fin>>xx;
		x_num=xx.length();
		for(int i=0;i<x_num;i++){
			char_x[i] = xx.at(i);
		}
		for(n=0;n<x_num;n++){
			x[n]=char_x[x_num-1-n]-'0';
		}
		
		fin>>opera[0];
		fin>>yy;
		y_num=yy.length();
		for(int i=0;i<y_num;i++){
			char_y[i] = yy.at(i);
		}
		for(n=0;n<y_num;n++){
			y[n]=char_y[y_num-1-n]-'0';
		}
		if(opera[0]=='+')	opera_plus(x,y,x_num,y_num);
		else if(opera[0]=='-')	opera_minus(x,y,x_num-1,y_num-1);
		else if(opera[0]=='*')	opera_time(x,y,x_num,y_num);
		
		else if(opera[0]=='/'){
			if(x_num>=y_num){
				for(m=x_num;m>=y_num;m--){		//砆埃计癶 m场だ砆埃计程蔼 
					if(x_num==y_num){				//砆埃计埃计计 
						while(1){
							if(compare(x_num,x_num,x,y)==1)	break;
							div_ans[0]++;
							for(q=0;q<y_num;q++){
								x[q]-=y[q];
								if(x[q]<0){
									x[q]+=10;
									x[q+1]-=1;
								}	
							}	
						}	
					}
					else{									//砆埃计埃计计ぃ
						for(p=y_num;p>=0;p--){
							temp_x[p]=x[p+m-y_num];
						}
						if(m!=x_num){
							for(p=y_num-1;p>=0;p--){
								temp_x[p+1]=ans[p];
							}
						}
						temp_x[y_num+1]=0;
						for(p=1;p<=10;p++){
							mult[0]=p;
							for(n=y_num+1;n>=0;n--){
								ans[n]=0;
							}
							opera_time(y,mult,y_num,1);
							for(n=y_num;n>=0;n--){
								temp_ans[n]=ans[n];
							}
							if(compare(y_num+2,y_num+2,temp_x,temp_ans)==1){
								opera_minus(temp_ans,y,y_num+1,y_num);
								for(n=y_num;n>=0;n--){
									temp_ans2[n]=ans[n];
								}
								for(n=y_num+1;n>=0;n--){
									ans[n]=0;
								}
								
								opera_minus(temp_x,temp_ans2,y_num+1,y_num+1);
								div_ans[m-y_num]=mult[0]-1;
								break;
							}
							else if(compare(y_num+2,y_num+2,temp_x,temp_ans)==2){
								for(n=y_num+1;n>=0;n--){
									ans[n]=0;
								}
								opera_minus(temp_x,temp_ans,y_num+1,y_num+1);
								div_ans[m-y_num]=mult[0];
								break;
							}
						} 
					}
				}
			}
			
		}
		
		fin>>index1>>index2;
		if(opera[0]=='/'){
			for(n=index2;n>=index1;n--){
				cout<<div_ans[n];
			}
		}
		else{
			if(ans[40000]==1)	cout<<'-';
			for(n=index2;n>=index1;n--){
				cout<<ans[n];
			}
		} 
		cout<<endl;
	}

	return 0;
 } 

 void opera_plus(int x[],int y[],int x_amt,int y_amt)	//x_amtxΤ碭计 
 {
 	if(x_amt>=y_amt){
 		for(i=0;i<x_amt;i++){
			ans[i]+=(x[i]+y[i]);
			if(ans[i]>=10){
				ans[i]-=10;
				ans[i+1]+=1;
			}
		}
	 }
	 else{
	 	for(i=0;i<y_amt;i++){
			ans[i]+=(x[i]+y[i]);
			if(ans[i]>=10){
				ans[i]-=10;
				ans[i+1]+=1;
			}
		}
	 }
 }
 
 void opera_minus(int x[],int y[],int x_fin,int y_fin) //x_finぇ畒夹 
 {
 	for(n=0;n<20001;n++){
		ans[n]=0;
	}
	if(x_fin > y_fin){
		for(i=0;i<=x_fin;i++){
			ans[i]+=(x[i]-y[i]);
			if(ans[i]<0){
				ans[i]+=10;
				ans[i+1]-=1;	
			}
		}
	}
	else if(x_fin < y_fin){
		for(i=0;i<=y_fin;i++){
			ans[i]+=(y[i]-x[i]);
			if(ans[i]<0){
				ans[i]+=10;
				ans[i+1]-=1;
			}
		}
		ans[40000]=1;
	}
	else{
		for(i=y_fin;i>=0;i--){
			if(x[i]>y[i]){
				flag=1;
				break;
			}
			else if(x[i]<y[i]){
				flag=0;
				break;
			}
		}
		if(flag==1){
			for(i=0;i<=x_fin;i++){
				ans[i]+=(x[i]-y[i]);
				if(ans[i]<0){
					ans[i]+=10;
					ans[i+1]-=1;
				}
			}
		}
		else if(flag==0){
			for(i=0;i<=y_fin;i++){
				ans[i]+=(y[i]-x[i]);
				
				if(ans[i]<0){
					ans[i]+=10;
					ans[i+1]-=1;
				}
			}
			ans[40000]=1;
		}
	}
}

void opera_time(int x[],int y[],int x_amt,int y_amt)		//x_amtxΤ碭计 
{
	for(i=0;i<(x_amt+y_amt);i++)	ans[i]=0;
	for(i=0;i<y_amt;i++){
		for(t=0;t<x_amt;t++){
			ans[i+t]+=(x[t]*y[i]);
			if(ans[i+t]>=10){
				ans[i+t+1]+=((ans[i+t])/10);
				ans[i+t]=(ans[i+t]%10);
			}
		}
	}
}

int compare(int m,int n,int a[],int b[])
{
	if(m>n)	flag=0;					// 0琌玡 1琌 
	else if(m<n)	flag=1;
	else{
		for(i=n-1;i>=0;i--){
			if(a[i]>b[i]){
				flag=0;
				break;
			}	
			else if(a[i]<b[i]){
				flag=1;
				break;
			}
			else{
				flag=2;
			}
		}	
	}
	return flag;
}
