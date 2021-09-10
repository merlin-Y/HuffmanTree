#include<iostream>
#include<cstring>
#include<vector>
#include<cmath>
#include<fstream>
#include<algorithm>
using namespace std;

typedef struct{
    int weight;
    int lchild,rchild,parent;
} SHTNode,*StaticHuffmanTree;

class SHFMNode{
    private:
        StaticHuffmanTree HT = NULL;

    public:
        SHFMNode(){}
        ~SHFMNode(){}
        void CreatHuffmanTree(int num,vector<char> &a);
        void CreatHuffmanTree(vector<int> &a);
        void FindMin(int n,int &s1,int &s2);
        void creatHuffmanCode(char ** &HC,int num);
        void TransCode(vector<char> &a,int num);
        void PrintCOde(vector<char> &a,char ** &HC,int num);
        StaticHuffmanTree GetHT();
};

void SHFMNode::CreatHuffmanTree(int num,vector<char> &a){
    if(HT != NULL)
        delete HT;;
    if(num <= 1)
        return ;
    int m = 2 * num - 1;
    HT = new SHTNode[m + 1];
    for(int i = 1;i <= m;i++){
        HT[i].lchild = 0;
        HT[i].rchild = 0;
        HT[i].parent = 0;
        HT[i].weight = 0;
    }
    for(int i = 1;i <= num;i++)
        cin >> HT[i].weight;
    int s1,s2;
    for(int i = num + 1;i <= m;i++){
        FindMin(i - 1,s1,s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    cout<<"创建哈夫曼树成功。"<<endl;
    cout<<"结点i"<<"\t字符"<<"\t权值"<<"\t双亲"<<"\t左孩子"<<"\t右孩子"<<endl;
    for(int i=1; i<=num; i++)
        cout<<i<<"\t"<<a[i - 1]<<"\t"<<HT[i].weight<<"\t"<<HT[i].parent<<"\t"<<HT[i].lchild<<"\t"<<HT[i].rchild<<endl;
    for(int i = num + 1;i <= num * 2 - 1;i++)
        cout<<i<<"\t"<<" "<<"\t"<<HT[i].weight<<"\t"<<HT[i].parent<<"\t"<<HT[i].lchild<<"\t"<<HT[i].rchild<<endl;    
    return ;
}

void SHFMNode::CreatHuffmanTree(vector<int> &a){
    if(HT != NULL)
        delete HT;
    if(a.size() <= 1)
        return ;
    int m = 2 * a.size() - 1;
    int num = a.size();
    HT = new SHTNode[m + 1];
    for(int i = 1;i <= m;i++){
        HT[i].lchild = 0;
        HT[i].rchild = 0;
        HT[i].parent = 0;
        HT[i].weight = 0;
    }
    for(int i = 1;i <= a.size();i++)
        HT[i].weight = a[i - 1];
    int s1,s2;
    for(int i = a.size() + 1;i <= m;i++){
        FindMin(i - 1,s1,s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    cout<<"创建哈夫曼树成功。"<<endl;
    cout<<"结点i"<<"\t字符"<<"\t权值"<<"\t双亲"<<"\t左孩子"<<"\t右孩子"<<endl;
    for(int i=1; i<=num; i++)
        cout<<i<<"\t"<<a[i - 1]<<"\t"<<HT[i].weight<<"\t"<<HT[i].parent<<"\t"<<HT[i].lchild<<"\t"<<HT[i].rchild<<endl;
    for(int i = num + 1;i <= num * 2 - 1;i++)
        cout<<i<<"\t"<<" "<<"\t"<<HT[i].weight<<"\t"<<HT[i].parent<<"\t"<<HT[i].lchild<<"\t"<<HT[i].rchild<<endl;    
    return ;
}

void SHFMNode::FindMin(int n,int &s1,int &s2){
    int i = 1;
    while(HT[i].parent != 0 && i <= n)
        i++;
    if(i == n + 1)
        return ;
    s1 = i;
    i++;
    while(HT[i].parent != 0 && i <= n)
        i++;
    if(i == n + 1)
        return ;
    s2 = i;
    i++;
    if(HT[s1].weight > HT[s2].weight)
        swap(s1,s2);
    for(;i <= n;i++){
        if(HT[i].parent == 0){
            if(HT[i].weight < HT[s1].weight)
                s2 = s1,s1 = i;
            else if(HT[i].weight < HT[s2].weight)
                s2 = i;
        }
    }
    return ;
}
void SHFMNode::creatHuffmanCode(char ** &HC,int num){
    char *col;
    HC=(char **)malloc(sizeof(char *)*(num+1));
    col=(char *)malloc(sizeof(char)*num);
    col[num-1]='\0';
    for(int i=1; i<=num; i++)
    {
        int str=num-1;
        int p=i,f=i;
        while(HT[f].parent!=0)
        {
            f=HT[f].parent;
            if(HT[f].lchild==p)
                col[--str]='0';
            else if(HT[f].rchild==p)
                col[--str]='1';
            p=f;
        }
        HC[i]=(char *)malloc(sizeof(char)*(num-str));
        strcpy(HC[i],&col[str]);
    }
    free(col);
}

void SHFMNode::PrintCOde(vector<char> &a,char ** &HC,int num){
    cout<<"哈夫曼编码表已生成，下面输出哈夫曼编码表！"<<endl;
    cout<<"结点i\t"<<"字符\t"<<"权值\t"<<"编码\t"<<endl;
    for(int i=1; i<=num; i++)
        cout<<i<<"\t"<<a[i - 1]<<"\t"<<HT[i].weight<<"\t"<<HC[i]<<endl;
}

void SHFMNode::TransCode(vector<char> &a,int num){
    FILE *fw;
    int q = 2 * num - 1;
    int k = 0;
    fstream infile;
    char c;
    infile.open("CodeFile.txt");
    if((fw = fopen("TransCode.txt","w")) == NULL)
        cout << "Open transfile error" << endl;
    while(!infile.eof()){
        infile.get(c);
        if(c == '\n')
            fputc('\n',fw);
        if(c == '0')
            q = HT[q].lchild;
        else if(c == '1')
            q = HT[q].rchild;
        if(HT[q].lchild == 0 && HT[q].rchild == 0){
            fputc(a[q - 1],fw);
            q = 2 * num - 1;
        }
    }
    infile.close();
    fclose(fw);
    return ;
}

StaticHuffmanTree SHFMNode::GetHT(){
    return HT;
}