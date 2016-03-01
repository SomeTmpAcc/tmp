#include <fstream>
#include <iostream>
#include <queue>
#include <algorithm>


using namespace std;

struct node{
    int info;
    node *l, *r, *top;
	int numbLeft, numbRight; //число детей слева и справа
};

node* tree = NULL;
int element; //Который нужно удалить
node* delel; //Указатель на Element
vector <int> arrNecesElem; 
vector <int> arrFinal;
 
/*ФУНКЦИЯ ЗАПИСИ ЭЛЕМЕНТА В БИНАРНОЕ ДЕРЕВО*/
void pushInTree(int a,node **t, node *p)
{
    if ((*t)==NULL) //Если дерева не существует
    {
        (*t)=new node; //Выделяем память
        (*t)->info=a; //Кладем в выделенное место аргумент a
		(*t)->l=(*t)->r=NULL; //Очищаем память для следующего роста
		(*t)->top = p;
        return; //Заложили семечко, выходим
    }
	p = *t;
       //Дерево есть
        if (a>(*t)->info) pushInTree(a,&(*t)->r, p); //Если аргумент а больше чем текущий элемент, кладем его вправо
        else pushInTree(a,&(*t)->l, p); //Иначе кладем его влево
}

/*ФУНКЦИЯ ЗАНЕСЕНИЯ ДЕРЕВА В МАССИВ*/
void pushTreeInArray (node *t) 
{
    if (t == NULL) 
		return; //Если дерево пустое, то отображать нечего, выходим
    else //Иначе
    {
		arrFinal.push_back(t->info);
		pushTreeInArray(t->l);//С помощью рекурсивного посещаем левое поддерево
		pushTreeInArray(t->r); //С помощью рекурсии посещаем правое поддерево
    }
}

void countChild(node* t, int ul, int ur){
	if (t == NULL) 
		return;
    else
    {
		countChild(t->l, ul, ur);//С помощью рекурсивного посещаем левое поддерево
		if(t->l != NULL)
			t->numbLeft = t->l->numbLeft + t->l->numbRight + 1;
		else
			t->numbLeft = 0;
		countChild(t->r, ul, ur); //С помощью рекурсии посещаем правое поддерево
		if(t->r != NULL)
			t->numbRight = t->r->numbLeft + t->r->numbRight + 1;
		else
			t->numbRight = 0;
    }
}

void pushInArrayNeededElements(node *t){
	 if (t == NULL) 
		return; //Если дерево пустое, то отображать нечего, выходим
    else //Иначе
    {
		if(t->numbLeft != t->numbRight)
			arrNecesElem.push_back(t->info);
		pushInArrayNeededElements(t->l);//С помощью рекурсивного посещаем левое поддерево
		pushInArrayNeededElements(t->r); //С помощью рекурсии посещаем правое поддерево
		
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
	deleteElement(t->l);//С помощью рекурсивного посещаем левое поддерево
	deleteElement(t->r); //С помощью рекурсии посещаем правое поддерево
}
int main ()
{
	ifstream fin("/home/mary/Work/C++/AISD/1lab/in.txt");
	int sc = 0;
//	if (!fin.is_open()) // если файл не открыт
  //      cout << "File can't be open\n"; // сообщить об этом
   // else
    //{
		int s;
		while(fin >> s){
			sc++;
			pushInTree(s,&tree, NULL); //И каждый кладем в дерево
			//cout << s << endl;
		}
	//}
	ofstream fout("/home/mary/Work/C++/AISD/1lab/out.txt");
	if(sc <= 1)// если один элемент в дереве или их нет
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