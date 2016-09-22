#include <iostream>
#include<algorithm>
#include<utility>
#include<map>
#include<queue>
#include<stack>
#include<math.h>
#include<stdlib.h>
using namespace std;
typedef pair< pair< pair<int,int>,vector<pair<int, int> > >, pair<bool,bool>  > cord;
typedef pair<double,cord > cordis;
pair <int,int> nothing1,child1,tempp;
cord temp1,source,temp2,goal,curr,nothing,child;
stack <cord> st;
map <cord, double > dist;
map <cord,cord> par;
vector <pair<int, int> > gem_collected;
int arr[1000][1000];
long int count1;
int total_points;
double epsilon  = 0.0000000000001,tdist;
int flag;
void display(){
	//cout << "inside display"<<endl;
	temp2 = goal;
	//st.push(temp1);
	while(temp2 != source){
		st.push(temp2);
		temp2 = par[temp2];
	}
	st.push(source);
	while(!st.empty()){
		temp2 = st.top();
		cout << temp2.first.first.first << " " << temp2.first.first.second << " ";
		st.pop();
	}
	cout << endl;
}
bool check_invalid(int x, int y, int m, int n){
	if((x >= m || x < 0) || (y >= n || y < 0)){
		return true;
	}
	else{
		return false;
	}
}
bool check_minus(int x, int y){
	if(arr[x][y] == -1){
		return true;
	}
	else{
		return false;
	}
}
void gen_child(int i, int m, int n){
	pair<int, int > final;
	if(i == 0){
		final.first  = child1.first;
		final.second = child1.second + 1;
		tdist = 1; 
	}
	if(i == 1){
		final.first  = child1.first + 1;
		final.second = child1.second + 1;
		tdist = sqrt(2); 
	}
	if(i == 2){
		final.first  = child1.first + 1;
		final.second = child1.second;
		tdist = 1; 
	}
	if(i == 3){
		final.first  = child1.first + 1;
		final.second = child1.second - 1;
		tdist = sqrt(2); 
	}
	if(i == 4){
		final.first  = child1.first;
		final.second = child1.second - 1;
		tdist = 1; 
	}
	if(i == 5){
		final.first  = child1.first - 1;
		final.second = child1.second - 1;
		tdist = sqrt(2); 
	}
	if(i == 6){
		final.first  = child1.first - 1;
		final.second = child1.second;
		tdist = 1; 
	}
	if(i == 7){
		final.first  = child1.first - 1;
		final.second = child1.second + 1;
		tdist = sqrt(2); 
	}
	if(check_invalid(final.first, final.second,m,n)){
		flag = 1;
		return;
	}
	else if(check_minus(final.first, final.second)){
		flag = 1;
		return;
	}
	else{
		child1 = final;
	}
}
bool search(int m, int n,int points, int alpha){
	priority_queue<cordis ,vector < cordis >, greater< cordis > > q;
	dist[source] = 0.0;
	q.push(make_pair(dist[source],source));
	count1 = 1;
	while(!q.empty()){
		curr = q.top().second;
		vector <pair<int,int> > :: iterator check;
		total_points = 0;
		for(check=curr.first.second.begin();check != curr.first.second.end();++check){
			total_points += arr[check->first][check->second];
		}              
		if(total_points >= points){
			goal = curr;                  //
			return true;
		}
		child1.first = curr.first.first.first;
		child1.second = curr.first.first.second;
		q.pop();
		for(int i = 0;i<8; i++){
			flag = 0;
			tdist = 0;
			gen_child(i,m,n);
			child.first.first = child1;
			child.second = curr.second;
			if((arr[child1.first][child1.second] == -2) && (curr.second.first == false && curr.second.second == false)){
				child.second.first == true;
				child.second.second == false;
			}
			if(flag == 0){
				child.first.second = curr.first.second;
				int gem_point = 0;
				vector <pair<int,int> > :: iterator check1;
				check1 = find(child.first.second.begin(),child.first.second.end(),child1);
				if((arr[child1.first][child1.second] > 0) && check1 == child.first.second.end()){
					child.first.second.push_back(child1);
					gem_point = alpha;
				}
				
				if(arr[child1.first][child1.second] >= 0 || arr[child1.first][child1.second] == -2){
					if(dist.find(child) == dist.end() || dist[child] > dist[curr] + tdist + count1*epsilon  + gem_point){
						dist[child] = dist[curr] + tdist + count1*epsilon+ gem_point;
						par[child] = curr;
						q.push(make_pair(dist[child], child));
						count1+=2;
					}
				}
			}
			child1.first = curr.first.first.first;
			child1.second = curr.first.first.second;
		}
		child1.first = curr.first.first.first;
		child1.second = curr.first.first.second;
		if(curr.second.first == true && curr.second.second == false){
			for(int p = child1.first - 5 ; p <= child1.first + 5; p++){
				for(int g = child1.second - 5; g <= child1.second + 5; g++ ){
					if(!(check_invalid(p,g,m,n))){
						if(!(check_minus(p,g))){
							tempp= make_pair(p,g);
							child.first.first = tempp;
							child.second = curr.second;
							child.second.first = true;
							child.second.second = true;
							child.first.second = curr.first.second;
							int gem_point = 0;
							vector <pair<int,int> > :: iterator check111;
							check111 = find(child.first.second.begin(),child.first.second.end(),tempp);
							if((arr[tempp.first][tempp.second] > 0) && check111 == child.first.second.end()){
								child.first.second.push_back(tempp);
								gem_point = alpha;
							}
							
							if(arr[tempp.first][tempp.second] >= 0 || arr[child1.first][child1.second] == -2){
								if(dist.find(child) == dist.end() || dist[child] > dist[curr] + 1 + count1*epsilon  + gem_point){
									dist[child] = dist[curr] + 1 + count1*epsilon+ gem_point;
									par[child] = curr;
									q.push(make_pair(dist[child], child));
									count1+=2;
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}
int main()
{
    int t,m,n,p,points,alpha;
    cin >> t;
    while(t--){
    	cin >> m >> n >> points >> alpha;
    	//taking input in array
    	for(int i = 0;i<m; i++){
    		for(int j = 0; j<n; j++){
    			cin >> p;
    			arr[i][j] = p;
    		}
    	}
    	cin >> source.first.first.first >> source.first.first.second;
    	source.first.second = gem_collected;
    	source.second.first = false;
    	source.second.second = false;
    	//cout << "flag1:" << flag1<< endl;
    	if(search(m,n,points,alpha)){
			display();
    	}
    	else{
    		cout << "-1" << endl;
    	}
    	nothing.swap(source);
    	nothing.swap(goal);
    	nothing.swap(curr);
    	nothing.swap(temp1);
    	nothing.swap(temp2);
    	nothing.swap(child);
    	nothing1.swap(child1);
    	//nothing1.swap(temp2);*/
    	dist.clear();
    	//visit.clear();
    	par.clear();
    	gem_collected.clear();
    }
    return 0;
}
