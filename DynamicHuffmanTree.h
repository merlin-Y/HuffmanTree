#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include"MinHeap.h"
using namespace std;

/*typedef struct wood{
    int weight;
    char str;
    wood *lchild,*rchild,*parent;
    wood(int weight):weight(weight),lchild(NULL),rchild(NULL),parent(NULL){}
    wood():lchild(NULL),rchild(NULL),parent(NULL){}
    bool operator <= (wood& R){return weight <= R.weight;}
    bool operator > (wood& R){return weight > R.weight;}
} DHTNode,*dynamicHuffmanTree;*/

struct PrintCode{
    int weight;
    char val;
    string code;
};

bool cmp(const PrintCode &a,const PrintCode &b){
    return a.weight < b.weight;
}

class DHFMNode{
    private:
        dynamicHuffmanTree root =  NULL;

    public:
        DHFMNode(){}
        //DHFMNode(vector<int> &w,vector<char> &str,int n);
        ~DHFMNode(){}
        dynamicHuffmanTree CreatHuffmanTree(vector<int> &w,vector<char> &str,int n);
        void mergeTree(dynamicHuffmanTree &ht1,dynamicHuffmanTree &ht2,dynamicHuffmanTree &parent);
        void print(dynamicHuffmanTree node,string res,vector<PrintCode> &vpn);
        void prinrCode(vector<PrintCode> &vpn,char** &ch,vector<char> &b);
        void TransCode();
};

/*DHFMNode::DHFMNode(vector<int> &w,vector<char> &str,int n){
    minHeap hp;
    dynamicHuffmanTree first,second,work,parent;
    work = new DHTNode;
    for(int i = 0;i < n;i++){
        work->weight = w[i];
        work->str = str[i];
        work->lchild = NULL;
        work->rchild = NULL;
        work->parent = NULL;
        hp.Insert(work);
    }
    for(int i = 0;i < n - 1;i++){
        first = new DHTNode;
        second = new DHTNode;
        hp.RemoveMin(*first);
        hp.RemoveMin(*second);
        mergeTree(first,second,parent);
        hp.Insert(parent);
    }
    root = parent;
}*/

void DHFMNode::mergeTree(dynamicHuffmanTree &ht1,dynamicHuffmanTree &ht2,dynamicHuffmanTree &parent){
    parent = new DHTNode;
    parent->lchild = ht1;
    parent->rchild = ht2;
    parent->weight = ht1->weight + ht2->weight;
    ht1->parent = ht2->parent = parent;
}

dynamicHuffmanTree DHFMNode::CreatHuffmanTree(vector<int> &w,vector<char> &str,int n){
    if(root)
        root = NULL;
    minHeap hp;
    dynamicHuffmanTree first,second,work,parent;
    work = new DHTNode;
    for(int i = 0;i < n;i++){
        work->weight = w[i];
        work->str = str[i];
        work->lchild = NULL;
        work->rchild = NULL;
        work->parent = NULL;
        hp.Insert(work);
    }
    for(int i = 0;i < n - 1;i++){
        first = new DHTNode;
        second = new DHTNode;
        hp.RemoveMin(*first);
        hp.RemoveMin(*second);
        mergeTree(first,second,parent);
        hp.Insert(parent);
    }
    root = parent;
    return root;
}

void DHFMNode::print(dynamicHuffmanTree node,string res,vector<PrintCode> &vpn){
    if(!node->lchild && !node->rchild){
        PrintCode pn;
        pn.val = node->str;
        pn.weight = node->weight;
        pn.code = res;
        vpn.push_back(pn);
        return ;
    }
    print(node->lchild,res + "0",vpn);
    print(node->rchild,res + "1",vpn);
}

void DHFMNode::prinrCode(vector<PrintCode> &vpn,char** &ch,vector<char> &b){
    b.clear();
    ch=(char **)malloc(sizeof(char *)*(vpn.size()+1));
    sort(vpn.begin(),vpn.end(),cmp);
    /*for(int i = 0;i < vpn.size();i++)
        cout << vpn[i].val << " " << vpn[i].weight << " " << vpn[i].code << endl;*/
    for(int i = 1;i <= vpn.size();i++){
        ch[i]=(char *)malloc(sizeof(char)*(vpn[i - 1].code.length()));
        strcpy(ch[i],vpn[i - 1].code.c_str());
        b.push_back(vpn[i - 1].val);
    }
    cout<<"哈夫曼编码表已生成，下面输出哈夫曼编码表！"<<endl;
    cout<<"结点i\t"<<"字符\t"<<"权值\t"<<"编码\t"<<endl;
    for(int i=1; i<=vpn.size(); i++)
        cout<<i<<"\t"<<vpn[i - 1].val<<"\t"<<vpn[i - 1].weight<<"\t"<<ch[i]<<endl;
}

void DHFMNode::TransCode(){
    FILE *fw;
    dynamicHuffmanTree HNode = root;
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
            HNode = HNode->lchild;
        else if(c == '1')
            HNode = HNode->rchild;
        if(!HNode->lchild && !HNode->rchild){
            fputc(HNode->str,fw);
            HNode = root;
        }
    }
    infile.close();
    fclose(fw);
    return ;
}