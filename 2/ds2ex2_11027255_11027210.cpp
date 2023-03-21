// 11027255 ����
#include <bits/stdc++.h>


using namespace std;

class dataa {
public:
    string raw;
    string school_name;
    string depart_name;
    string degree;
    string level;
    string graduate;
};          // struct

struct info // heap�|�Ψ쪺�ƾ�
{
    int index;
    int key;
};

int getNum(string input) {
    string temp;

    for(int i = 0 ; i < input.length() ; i++)
        if(input[i] >= '0' && input[i] <= '9')
            temp += input[i];
    return stoi(temp);
}

class Heap {
private:
    vector<info> minheap;
    vector<int> outputlist;
public:
    void initial() {
        minheap.clear();     // initial the heap
    }

    int parent(int index) {
        return (index - 1) / 2;    // return the parent index
    }

    bool isMin(int index) {
        return !(std::__lg(++index) % 2);
    }

    int grandparent(int index) {
        return parent(parent(index));     // return grandparent index
    }

    void buildMin(struct info input) {
        minheap.push_back(input);
        int index = minheap.size();
        index -= 1;
        while(index != 0 && minheap[index].key < minheap[parent(index)].key) { //����root�Τp��parent key
            swap(minheap[index], minheap[parent(index)]);                      // swap the content
            index = parent(index);
        }
    }

    void ch(int i) {
        int p = (i - 1) / 2;

        if(p < 0)
            return;

        p = (p - 1) / 2;
        if(p < 0)
            return;

        if(isMin(p)) {
            if(minheap[p].key > minheap[i].key) {
                swap(minheap[p], minheap[i]);
                ch(p);
                return;
            }
        }
        else if(minheap[p].key < minheap[i].key) {
            swap(minheap[p], minheap[i]);
            ch(p);
            return;
        }
    }

    void buildMinMax(struct info input) {
        minheap.push_back(input);
        int i = input.index - 1;
        int p = (i - 1) / 2;
        if(p < 0)
            return;

        if(isMin(p)) {
            if(minheap[p].key > minheap[i].key) {
                swap(minheap[p], minheap[i]);
                ch(p);
                return;
            }
        }
        else if(minheap[p].key < minheap[i].key) {
            swap(minheap[p], minheap[i]);
            ch(p);
            return;
        }

        p = (p - 1) / 2;
        if(p < 0)
            return;

        if(isMin(p)) {
            if(minheap[p].key > minheap[i].key) {
                swap(minheap[p], minheap[i]);
                ch(p);
                return;
            }
        }
        else if(minheap[p].key < minheap[i].key) {
            swap(minheap[p], minheap[i]);
            ch(p);
            return;
        }
    }

    int leftmost() {       // ��leftmost bottom
        int left = 0;
        int temp = 0;

        while(left < minheap.size()) {
            temp = left;
            left = left * 2 + 1;
        }
        return minheap[temp].index;
    }

    int bottom() {
        return minheap[minheap.size() - 1].index;
    }

    int root() {
        return minheap[0].index;
    }
};


class school {              // �B�zŪ�i�Ӫ����
private:
    vector<dataa> datalist; //�ΨӦs��D�n���
    Heap heap;
public:
    void ReadFile(string names) {
        datalist.clear();
        dataa    input;
        ifstream ifs("input" + names + ".txt");
        if(!ifs.is_open())                     //�䤣����
            cout << "Failed to open file.\n";
        else{
            string temp;
            string pass;
            int    times;
            int    total = 0;
            for(int i = 0 ; i < 3 ; i++)
                getline(ifs, pass);         // ����Ū �R���e�T��
            while(ifs.peek() != EOF) {      // Ū���ɮװ��U��
                getline(ifs, temp);
                times     = 0;
                input.raw = temp;
                for(int i = 0 ; i < temp.length() ; i++) {                 //
                    if(temp[i] == '\t') {
                        if(times == 1)
                            input.school_name = pass;
                        else if(times == 3)
                            input.depart_name = pass;
                        else if(times == 4)
                            input.degree = pass;
                        else if(times == 5)
                            input.level = pass;
                        else if(times == 8)
                            input.graduate = pass;
                        pass = "";
                        times++;
                    }
                    else
                        pass += temp[i];
                }
                datalist.push_back(input);
            } // while
        }     // else

        ifs.close();
    }     //ReadFile()

    void Problem1() {
        heap.initial();            // ��l�� heap
        struct info temp;
        for(int i = 0 ; i < datalist.size() ; i++) {
            temp.index = i + 1;
            temp.key   = getNum(datalist[i].graduate);
            heap.buildMin(temp);
        }
        cout << endl << "<min heap>\n";
        cout << "root: [" << heap.root() << "]" << datalist[heap.root() - 1].graduate << endl;             // ��X�p�⧹��쪺����
        cout << "bottom: [" << heap.bottom() << "]" << datalist[heap.bottom() - 1].graduate << endl;
        cout << "leftmost bottom : [" << heap.leftmost() << "]" << datalist[heap.leftmost() - 1].graduate << endl;
    }

    void Problem2() {
        heap.initial();
        struct info temp;
        for(int i = 0 ; i < datalist.size() ; i++) {
            temp.index = i + 1;
            temp.key   = getNum(datalist[i].graduate);
            heap.buildMinMax(temp);
        }
        cout << endl << "<min heap>\n";
        cout << "root: [" << heap.root() << "]" << datalist[heap.root() - 1].graduate << endl;             // ��X�p�⧹��쪺����
        cout << "bottom: [" << heap.bottom() << "]" << datalist[heap.bottom() - 1].graduate << endl;
        cout << "leftmost bottom : [" << heap.leftmost() << "]" << datalist[heap.leftmost() - 1].graduate << endl;
    }
}; // school


int main() {
    string filename;
    int    num     = -1;
    int    command = 0;
    school university;

    while(num != 0) {
        cout << "\n***** Heap Construction *****\n";
        cout << "* 0. QUIT                     *\n";
        cout << "* 1. Build a min heap         *\n";
        cout << "* 2. Build a min-max heap     *\n";
        cout << "*******************************\n";
        cout << "Input a choice(0, 1, 2):";
        cin >> command;
        switch(command) {    // �P�_�n�ϥέ��D��function
        case 0:
            return 0;

        case 1:
            cout << "\nInput a file number ([0] Quit): ";
            cin >> filename;
            university.ReadFile(filename);
            university.Problem1();
            break;

        case 2:
            cout << "\nInput a file number ([0] Quit): ";
            cin >> filename;
            university.Problem2();
            break;

        default:
            cout << endl << "Command does not exist!" << endl;      //�P�_���~���O
            break;
        } // switch
    } // while
}     // main()
