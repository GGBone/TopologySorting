#include<vector> 
#include<queue> 
#include<map> 
#include<iostream> 
#include<string>   
using namespace std;  
class topp;
class item{ 
	string name;  
	vector<int>son;
	int n_dep;
	friend class topp; 
};
class topp{
	int n_relation;
	int n_subject;
	item *subject;
	map<string, int> name_to_id;
	vector<int> outcome;
public:
	topp();
	~topp();
	void process();
	void output();
};
topp::topp(){
	int i;
	cout << "请输入课程数目:"; 
	cin >> n_subject; 
	subject = new item[n_subject];  
	cout << endl << "请输课程名称:" << endl; 
	for (i = 0; i < n_subject; i++)
	{ 
		cin >> subject[i].name; 
		subject[i].n_dep = 0;  
		name_to_id[subject[i].name] = i;
	} 
	cout << endl << "请输入课程里面有多少组关系:";  
	cin >> n_relation; 
	cout << endl << "请分别输入先修课程和后修课程:" << endl;  
	for (i = 0; i < n_relation; i++)
	{
		string pre_sub;
		string next_sub;
		int pre_id;
		int next_id;
		cin >> pre_sub >> next_sub;
		pre_id = name_to_id[pre_sub];
		next_id = name_to_id[next_sub];
		subject[pre_id].son.push_back(next_id);
		subject[next_id].n_dep++;
	}
}
topp::~topp()
{ 
	delete[]subject;
}
void topp::process(){
	queue<int> temp;
	int i;
	for (i = 0; i < n_subject; i++)
	{
		if (subject[i].n_dep == 0)  
			temp.push(i);
	}
	while (!temp.empty())
	{ 
		int now_id = temp.front(); 
		temp.pop();   
		outcome.push_back(now_id); 
		const vector<int> &now_son = subject[now_id].son; 
		const int son_size = now_son.size();  
		for (i = 0; i < son_size; i++)
		{ 
			int now = now_son[i];  
			subject[now].n_dep--;   
			if (subject[now].n_dep == 0)
			{
				temp.push(now);
			} 
		}
	}
}
void topp::output()
{ 
	int i; 
	int size = outcome.size();  
	cout << endl << "您的课程学习顺序可这样安排:" << endl; 
	for (i = 0; i < size; i++)
	{ 
		int id = outcome[i]; 
		cout << subject[id].name << endl; 
	}
}
int main()
{ 
	topp a;  
	a.process();  
	a.output(); 
	getchar();  
	system("PAUSE");
}