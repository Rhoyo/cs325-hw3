#include <time.h>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct item{
	int val;
	int weight;

};

vector<vector<int>> dp(vector<item> val, vector <int> w, vector<int> max){ 

	int bu[val.size()+1][w.size()+1]; //x is value, y is weight
	//setting base case 0th row1
	for(int y=0; y<w.size()+1; y++)
		bu[0][y]=0;

	//filling the 2d array
	for(int x=1; x<val.size()+1; x++){
		bu[x][0]=0;//setting base case

		for(int y=1; y<w.size()+1; y++){
			if(val[x-1].weight<=y){

				if(val[x-1].val+bu[x-1][y-val[x-1].weight] > bu[x-1][y]){
					bu[x][y]=val[x-1].val+bu[x-1][y-val[x-1].weight];
				}
				else
					bu[x][y]=bu[x-1][y];
			}
			else
				bu[x][y]=bu[x-1][y];
		}
	}
	// fill the 2d vector with the item #s for each member
	vector <vector<int>> sack;
	for(int j=0;j<max.size();j++){
		int i=val.size();
		int k=max[max.size()-1-j];

		sack.push_back(vector<int>());
		while(i>0){
			
			if(bu[i][k]!=bu[i-1][k]){
				sack[j].push_back(i);
				i=i-1;
				k=k-val[i].weight;
			}
			else
				i=i-1;
		}
	}
	return sack;

}


int main(){

	int cases;

	ifstream in;
	in.open("shopping.txt");
	if(!in)
		return 1;		

	ofstream out;
	out.open("results.txt", ofstream::out | ofstream::trunc);
	if(!out){
		return 1;
	}
	
	string s;
	in >> s;
	cases=stoi(s);

	vector<item> items;
	vector<int> max;
	vector<int> knaps;


	for(int i=0;i<cases;i++){
		struct item a;
		int hi;
		int size;
		int mems;
		int k;
		int total=0;
		items.clear();
		max.clear();
		knaps.clear();

		in >> s;
		size=stoi(s);
		
		for(int x=0;x<size;x++){ //pushing item basket
			in>>s;
			a.val=stoi(s);
			in >>s; 
			a.weight=stoi(s);
			items.push_back(a);
		}
		cout<<endl;

		
		in >>s;
		mems=stoi(s);
		hi=0;
		for(int m=0;m<mems;m++){ 
			in >> s;
			k=stoi(s);
			max.push_back(k);

			if(m==0){
				hi=max[m];
			}

			else if(max[m]>hi){
				hi=max[m];
			}
		}
		for(int w=0;w<hi;w++){
			knaps.push_back(w+1);	
		}


		out<<"Case "<<i+1<<"\n";


		//filling 2d vector in main with item #s per member
		vector<vector<int>> sack= dp(items,knaps,max);

		for(int i=sack.size()-1;i>=0;i--){
			out<<"Mem "<<sack.size()-i<<": ";
			for(int x=sack[i].size()-1;x>=0;x--){
				out<<sack[i][x]<<" ";
				total+=items[sack[i][x]-1].val;
			}
			out<<"\n";
		}
		out<<"Total: "<<total<<"\n";	
		out<<"\n";

		
	}
	out.close();
	in.close();
}

