#include<iostream>
#include<string>
#include"Menu.h"
#include"StaticHuffmanTree.h"
#include"DynamicHuffmanTree.h"

using namespace std;


vector<char> b;
vector<int> a;
char ** HC;
dynamicHuffmanTree root;
void preorder(dynamicHuffmanTree root);
void InOrd(dynamicHuffmanTree root);
void Coding(char **&HC,int num,vector<char> &b);

int main(){
    int choose;
    int num;
    int flag = 1;
    int structure,in;
    int ntemp;
    char ctemp;
    SHFMNode SHFMTree;
    DHFMNode DHFMTree;
    vector<PrintCode> vpn;
    menu();
    while(flag){
        cout << "请选择你要进行的操作(1-6) ： ";
        cin >> choose;
        switch (choose)
        {
        case 1:
            a.clear();
            b.clear();
            cout << "选择存储结构-----1、静态存储结构    2、动态存储结构 ：";
            cin >> structure;
            cout << "选择权值数据读取方式-----1、键盘输入    2、文件读入 ：";
            cin >> in;
            if(structure == 1){
                if(in == 1){
                    cout << "请输入字符的个数 ： ";
                    cin >> num;
                    cout << "请依次输入" << num << "个字符:(空格用-来代替) ：";
                    for(int i = 0;i < num;i++){
                        char s;
                        cin >> s;
                        b.push_back(s);
                    }
                    cout << "请依次输入" << num << "个字符的权值 ： ";
                    SHFMTree.CreatHuffmanTree(num,b);
                }
                if(in == 2){
                    FILE *fp;
                    fp = fopen("data.txt","r");
                    while(ctemp != '\n'){
                        fscanf(fp,"%c",&ctemp);
                        b.push_back(ctemp);
                    }
                    ctemp = '\0';
                    b.pop_back();
                    while(!feof(fp)){
                        fscanf(fp,"%d",&ntemp);
                        a.push_back(ntemp);
                    }
                    fclose(fp);
                    num = a.size();
                    SHFMTree.CreatHuffmanTree(a);
                }
            }
            if(structure == 2){
                if(in == 1){
                    cout << "请输入字符的个数 ：";
                    cin >> num;
                    cout << "请依次输入" << num << "个字符:(空格用-来代替) ： ";
                    for(int i = 0;i < num;i++){
                        char s;
                        cin >> s;
                        b.push_back(s);
                    }
                    cout << "请依次输入" << num << "个字符的权值 ：";
                    for(int i = 0;i < num;i++){
                        int n;
                        cin >> n;
                        a.push_back(n);
                    }
                    root = DHFMTree.CreatHuffmanTree(a,b,num);
                    cout << "创建哈夫曼树成功" << endl;
                    //preorder(root);
                }
                if(in == 2){
                    FILE *fp;
                    ctemp = '\0';
                    fp = fopen("data.txt","r");
                    while(ctemp != '\n'){
                        fscanf(fp,"%c",&ctemp);
                        b.push_back(ctemp);
                    }
                    b.pop_back();
                    while(!feof(fp)){
                        fscanf(fp,"%d",&ntemp);
                        a.push_back(ntemp);
                    }
                    fclose(fp);
                    num = a.size();
                    root = DHFMTree.CreatHuffmanTree(a,b,num);
                }
            }
            break;
        case 2:
            delete HC;
            vpn.clear();
            if(structure == 1){
                SHFMTree.creatHuffmanCode(HC,num);
                SHFMTree.PrintCOde(b,HC,num);
            }
            if(structure == 2){
                DHFMTree.print(root,"",vpn);
                DHFMTree.prinrCode(vpn,HC,b);
            }
            break;
        case 3:
            cout << "现在对文件进行编码" << endl;
            Coding(HC,num,b);
            break;
        case 4:
            cout << "对文件进行译码" << endl;
            if(structure == 1){
                SHFMTree.TransCode(b,num);
            }
            if(structure == 2){
                DHFMTree.TransCode();
            }
            break;
        case 5:
            cout << "打印哈夫曼树" << endl;
            if(structure == 1){
                StaticHuffmanTree STree = SHFMTree.GetHT();

            }
            if(structure == 2){
                //root = DHFMTree.CreatHuffmanTree(a,b,num);
                //preorder(root);
            }
            break;
        case 6:
            menu();
            break;
        case 0:
            flag = 0;
            break;
        default:
            cout<<"输入不合法,请重新输入！"<<endl;
            continue;
        }
    }
    return 0;
}

void preorder(dynamicHuffmanTree root){
    if(root != NULL){
        cout << root->weight  << " ";
        preorder(root->lchild);
        preorder(root->rchild);
    }
}
void InOrd(dynamicHuffmanTree root){
    if(root){
        InOrd(root->lchild);
        cout << root->weight <<" ";
        InOrd(root->rchild);
    }
}

void Coding(char **&HC,int num,vector<char> &b){
    FILE *fp,*fw;
    char c;
    int k;
    if((fp = fopen("ToCode.txt","r")) == NULL)
        cout << "Open Sourcefile error!" << endl;
    if((fw = fopen("CodeFile.txt","w")) == NULL)
        cout << "Open codefile error!" << endl;
    fscanf(fp,"%c",&c);
    while(!feof(fp)){
        for(int i = 1;i <= num;i++)
            if(b[i - 1] == c){ 
                k = i;
                break;
            }
            for(int i = 0;HC[k][i] != '\0';i++)
                fputc(HC[k][i],fw);
            fscanf(fp,"%c",&c);
    }
    fclose(fp);
    fclose(fw);
}