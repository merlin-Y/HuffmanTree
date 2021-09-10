#include<iostream>
#include<queue>

using namespace std;

#define DefaultSize 100
void ToChar(char*&ch,string code);
typedef struct wood{
    int weight;
    char str;
    wood *lchild,*rchild,*parent;
    wood(int weight):weight(weight),lchild(NULL),rchild(NULL),parent(NULL){}
    wood():lchild(NULL),rchild(NULL),parent(NULL){}
    bool operator <= (wood& R){return weight <= R.weight;}
    bool operator > (wood& R){return weight > R.weight;}
} DHTNode,*dynamicHuffmanTree;

class minHeap{
    public:
        minHeap(int sz = DefaultSize);
        ~minHeap(){delete []heap;}
        bool Insert(const dynamicHuffmanTree& x);
        bool RemoveMin(DHTNode& x);
        bool IsEmpty(){return (currentSize == 0) ? true : false;}
        bool IsFull(){return (currentSize == maxHeapSize) ? true : false;}
        void MakeEmpty(){currentSize = 0;}
        void print();
    private:
        dynamicHuffmanTree heap;
        int currentSize;
        int maxHeapSize;
        void siftDown(int start,int m);
        void siftUp(int start);
};

minHeap::minHeap(int sz){
    maxHeapSize = (30 < sz) ? sz : 30;
    heap = new wood[maxHeapSize];
    if(heap == NULL)
        cout << "¶Ñ´´½¨Ê§°Ü" << endl;
    currentSize = 0;
}

void minHeap::siftDown(int start,int m){
    int i = start,j = 2 * i + 1;
    wood temp = heap[i];
    while(j <= m){
        if(j < m && heap[j] > heap[j + 1])
            j++;
        if(temp <= heap[j])
            break;
        else {
            heap[i] = heap[j];
            i = j;
            j = 2 * j + 1;
        }
    }
    heap[i] = temp;
}

void minHeap::siftUp(int start){
    int j = start,i = (j - 1) / 2;
    wood temp = heap[j];
    while(j > 0){
        if(heap[i] <= temp)
            break;
        else{
            heap[j] = heap[i];
            j = i;
            i = (i - 1) / 2;
        }
    }
    heap[j] = temp;
}

bool minHeap::Insert(const dynamicHuffmanTree& x){
    if(currentSize == maxHeapSize){
        cout << "¶ÑÂú" << endl;
        return false;
    }
    heap[currentSize] = *x;
    siftUp(currentSize);
    currentSize++;
    return true;
}

bool minHeap::RemoveMin(DHTNode& x){
    if(!currentSize){
        cout << "¶Ñ¿Õ" << endl;
    return false;
}
x = heap[0];
heap[0] = heap[currentSize - 1];
currentSize--;
siftDown(0,currentSize - 1);
return true;
}

void minHeap::print(){
    for(int i = 0;i <= currentSize;i++)
        cout << heap[i].weight << " ";
    cout << endl;
}
