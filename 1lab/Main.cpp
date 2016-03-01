#include <fstream>
#include <iostream>
#include <queue>
#include <algorithm>


using namespace std;

struct node{
    int info;
    node *l, *r, *top;
	int numbLeft, numbRight; //����� ����� ����� � ������
};

node* tree = NULL;
int element; //������� ����� �������
node* delel; //��������� �� Element
vector <int> arrNecesElem; 
vector <int> arrFinal;
 
/*������� ������ �������� � �������� ������*/
void pushInTree(int a,node **t, node *p)
{
    if ((*t)==NULL) //���� ������ �� ����������
    {
        (*t)=new node; //�������� ������
        (*t)->info=a; //������ � ���������� ����� �������� a
		(*t)->l=(*t)->r=NULL; //������� ������ ��� ���������� �����
		(*t)->top = p;
        return; //�������� �������, �������
    }
	p = *t;
       //������ ����
        if (a>(*t)->info) pushInTree(a,&(*t)->r, p); //���� �������� � ������ ��� ������� �������, ������ ��� ������
        else pushInTree(a,&(*t)->l, p); //����� ������ ��� �����
}

/*������� ��������� ������ � ������*/
void pushTreeInArray (node *t) 
{
    if (t == NULL) 
		return; //���� ������ ������, �� ���������� ������, �������
    else //�����
    {
		arrFinal.push_back(t->info);
		pushTreeInArray(t->l);//� ������� ������������ �������� ����� ���������
		pushTreeInArray(t->r); //� ������� �������� �������� ������ ���������
    }
}

void countChild(node* t, int ul, int ur){
	if (t == NULL) 
		return;
    else
    {
		countChild(t->l, ul, ur);//� ������� ������������ �������� ����� ���������
		if(t->l != NULL)
			t->numbLeft = t->l->numbLeft + t->l->numbRight + 1;
		else
			t->numbLeft = 0;
		countChild(t->r, ul, ur); //� ������� �������� �������� ������ ���������
		if(t->r != NULL)
			t->numbRight = t->r->numbLeft + t->r->numbRight + 1;
		else
			t->numbRight = 0;
    }
}

void pushInArrayNeededElements(node *t){
	 if (t == NULL) 
		return; //���� ������ ������, �� ���������� ������, �������
    else //�����
    {
		if(t->numbLeft != t->numbRight)
			arrNecesElem.push_back(t->info);
		pushInArrayNeededElements(t->l);//� ������� ������������ �������� ����� ���������
		pushInArrayNeededElements(t->r); //� ������� �������� �������� ������ ���������
		
    }
}

void findMinElement(node* t){
	 if (t == NULL) 
		return;
    else{
			if(t->l != NULL)
				while(t->l != NULL){
					t = t->l;
					delel = t;
				}
			else
				delel = t;
    }
}

void deleteElement(node* t){
	if (t == NULL) 
		return;
	else{
		if(t->info == element){
			if(t->l == NULL && t->r == NULL){
				if(t->top != NULL){
					if(t->top->r == t)
						t->top->r = NULL;
					if(t->top->l == t)
						t->top->l = NULL;
				}
				else
					t = NULL;
				return;
			}
			if(((t->l == NULL)&&(t->r != NULL))||((t->l != NULL)&&(t->r == NULL))){
				if(t->top != NULL){
					if(t->top->l == t){
						if(t->l != NULL){
							t->l->top = t->top;
							t->top->l = t->l;
							return;
						}
						if(t->r != NULL){
							t->r->top = t->top;
							t->top->l = t->r;
							return;
						}
					}
					if(t->top->r == t){
						if(t->l != NULL){
							t->l->top = t->top;
							t->top->r = t->l;
							return;
						}
						if(t->r != NULL){
							t->r->top = t->top;
							t->top->r = t->r;
							return;
						}
					}
				}
				if(t->top == NULL){
					if(t->l == NULL){
						tree = t->r;
						return;
					}
					if(t->r == NULL){
						tree = t->l;
						return;
					}
				}
			}
			if((t->l != NULL) && (t->r != NULL)){
					findMinElement(t->r);
					t->info = delel->info;
					element = delel->info;
					deleteElement(delel);
					//element = 10100;
				return;
			}
		}
	}
	deleteElement(t->l);//� ������� ������������ �������� ����� ���������
	deleteElement(t->r); //� ������� �������� �������� ������ ���������
}
int main ()
{
	ifstream fin("/home/mary/Work/C++/AISD/1lab/in.txt");
	int sc = 0;
//	if (!fin.is_open()) // ���� ���� �� ������
  //      cout << "File can't be open\n"; // �������� �� ����
   // else
    //{
		int s;
		while(fin >> s){
			sc++;
			pushInTree(s,&tree, NULL); //� ������ ������ � ������
			//cout << s << endl;
		}
	//}
	ofstream fout("/home/mary/Work/C++/AISD/1lab/out.txt");
	if(sc <= 1)// ���� ���� ������� � ������ ��� �� ���
	{
		fin.close();
		fout.close();
		return 0;
	}
    countChild(tree, 0, 0);
	pushInArrayNeededElements(tree);
	int a = arrNecesElem.size();
	if((a % 2) == 0){
		pushTreeInArray(tree);
		for(int i = 0; i < arrFinal.size(); i++){
			cout << arrFinal[i] << endl;
			fout << arrFinal[i] << endl;
		}
		fin.close();
		fout.close();
		return 0;
	}
	sort(arrNecesElem.begin(), arrNecesElem.end());
	element = arrNecesElem[(a - 1) / 2];
	//element = 10;
	deleteElement(tree);
	pushTreeInArray(tree);
	for(int i = 0; i < arrFinal.size(); i++){
		cout << arrFinal[i] << endl;
		fout << arrFinal[i] << endl;
	}
	fout.close();
	fin.close();
	return 0;
} 