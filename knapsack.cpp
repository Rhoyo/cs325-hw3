#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct item{
	int val;
	int weight;

};


int rec(int weight, int n, vector<item> val){
	if(n==0||weight==0) //base
		return 0;

	if(val[n-1].weight>weight)
		return rec(weight,n-1,val);

	int use=val[n-1].val + rec(weight-val[n-1].weight,n-1,val);
	int no=rec(weight,n-1,val);

	if(use > no)
		return use;

	else
		return no;
}

//bottom up dp
void dp(vector<item> val, vector <int> w){ 
	int bu[val.size()+1][w.size()+1]; //x is value, y is weight
	//setting base case 0th row1
	for(int y=0; y<w.size()+1; y++)
		bu[0][y]=0;

	//filling the 2d array
	for(int x=1; x<val.size()+1; x++){
		bu[x][0]=0;//setting base case

		for(int y=1; y<w.size()+1; y++){
			if(val[x-1].weight<=y){

				if(val[x-1].val+bu[x-1][y-val[x-1].weight] > bu[x-1][y])
					bu[x][y]=val[x-1].val+bu[x-1][y-val[x-1].weight];

				else
					bu[x][y]=bu[x-1][y];
			}
			else
				bu[x][y]=bu[x-1][y];
		}
	}

	cout<<"Max DP:"<<bu[val.size()][w.size()]<<" ";
}

/* MAIN FOR VARYING ITEM LIST
int main(){
}
*/

//varying weight main
int main(){
	for(int i=0;i<2;i++){
		if(i==0){
			cout<<endl<<"Varying weight";
			vector<item> val;
			vector<int> weight;
			int x=15001;
			srand(time(NULL));

			struct item a;

			for(int i=0;i<40;i++){
				a.val=rand()%100;
				a.weight=1+rand()%20;
				val.push_back(a);
			}
	
			for(int z=0;z<8;z++){
				weight.clear();
			cout<<endl;

				for (int i=1;i<x;i++)
					weight.push_back(i); 
	
				clock_t t1=clock();
				int maxR=rec(weight.size(),20,val);
				clock_t t2=clock();
				float sec=((float)t2-(float)t1)/CLOCKS_PER_SEC;

				cout<<"N:"<<20<<" "<<"Weight:"<<weight.size()<<" | ";
				cout<<"Rec Time:"<<sec<<" max rec:"<<maxR<<" | ";

				t1=clock();
				dp(val,weight);
				t2=clock();
				sec=((float)t2-(float)t1)/CLOCKS_PER_SEC;
				cout<<"DP Time:"<<sec<<endl;
				x+=5000;
			}
		}
		else{
			cout<<endl<<"Varying Item #";
			
			vector<item> val;
			vector<int> weight;
			int x=20;

			for (int i=1;i<41;i++)
				weight.push_back(i); 

			srand(time(NULL));

			for(int z=0;z<8;z++){
				val.clear();
			cout<<endl;

			struct item a;

			for(int i=0;i<x;i++){
				a.val=rand()%100;
				a.weight=1+rand()%20;
				val.push_back(a);
			}

	
			clock_t t1=clock();
			int maxR=rec(weight.size(),x,val);
			clock_t t2=clock();
			float sec=((float)t2-(float)t1)/CLOCKS_PER_SEC;

			cout<<"N:"<<x<<" "<<"Weight:"<<weight.size()<<" | ";
			cout<<"Rec Time:"<<sec<<" max rec:"<<maxR<<" | ";

			t1=clock();
			dp(val,weight);
			t2=clock();
			sec=((float)t2-(float)t1)/CLOCKS_PER_SEC;
			cout<<"DP Time:"<<sec<<endl;
			x+=5;
			}
		}
	}
}
