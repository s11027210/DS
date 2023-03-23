//DS2ex2_5_11027210_
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "vector"
#include <stack>

#define     PTR_NUM    3
#define     KEY_NUM    PTR_NUM - 1

using namespace std;

typedef struct sT
{
    int    no;              // serial number   序號
    string sName;           // school name 學校名稱
    int    gNum;            // graduate number 上學年度畢業生數

    string sData;           // 6筆資料
}   schoolType;

typedef struct slotT
{
    vector<int> rSet;           //存放序號
    string      key;            //放學校名稱
}   slotType;

typedef struct nT
{
    slotType   data[KEY_NUM];
    struct nT* link[PTR_NUM];
    struct nT* parent;
}   *nodeType;

class TwoThreeTree {
public:


    void clearUp()
    {
    } // cut off the

    ~TwoThreeTree()
    {
        clearUp();
    } // destructor
};    //end TwoThreeTree


typedef struct aT
{
    vector<int> rSet;   // data index
    int         key;    // search key
    aT*         left;   // left child
    aT*         right;  // right child
}   *AVLtreeType;

class AVL_Tree {
    int node = 0;                       //計算有幾個節點
    string fileNO;                      // number to form a file name
    vector<schoolType> data;            //資料
    AVLtreeType root;                   //AVL樹的根

    //走訪debug用
    void preOrder(AVLtreeType temp)
    {
        if(temp != NULL)
        {
            printf("%d ", temp->key);
            preOrder(temp->left);
            preOrder(temp->right);
        }
    }

    //計算樹高
    int getH(AVLtreeType now)
    {
        if(now == NULL)
            return 0;

        int leftH  = getH(now->left);
        int rightH = getH(now->right);
        return max(leftH, rightH) + 1;
    } // calculate the tree height

    //計算是否平衡
    int getBF(AVLtreeType now)
    {
        if(now == NULL)
            return 0;

        return getH(now->left) - getH(now->right);
    } // calculate the tree height

    //新增節點
    AVLtreeType newNode(int value, int no)
    {
        AVLtreeType temp = NULL;

        temp      = new aT;
        temp->key = value;
        temp->rSet.push_back(no);
        temp->left  = NULL;
        temp->right = NULL;
        node++;
        return temp;
    }

    //將value加入樹中
    void addNode(int value, int no)
    {
        AVLtreeType temp   = root;
        AVLtreeType parent = NULL;

        while(temp != NULL)
        {
            parent = temp;
            if(value < temp->key)
                temp = temp->left;
            else if(value > temp->key)
                temp = temp->right;
            else if(value == temp->key)    //等於
                break;
            else
                temp = NULL;
        } // while

        // 放入節點
        if(root == NULL)
            root = newNode(value, no);
        else if(value == parent->key)
            parent->rSet.push_back(no);
        else if(value < parent->key)
            parent->left = newNode(value, no);
        else if(value > parent->key)
            parent->right = newNode(value, no);
    }

    //找尋剛新增的節點
    AVLtreeType search(int value, AVLtreeType temp)
    {
        AVLtreeType now = temp;

        if(now == NULL)
            return NULL;

        if(now->key == value)
            return now;

        AVLtreeType left  = search(value, now->left);          //往下的左節點尋找
        AVLtreeType right = search(value, now->right);         //往下的右節點尋找

        return left ? left : right;                            //如果左子樹中存在目標節點的父節點，返回左子樹的根節點，否則返回右子樹的根節點。
    }

    //找尋父節點
    AVLtreeType searchParent(AVLtreeType head, AVLtreeType temp)
    {
        AVLtreeType now = temp;

        if(head == NULL || head == now)
            return NULL;                                            //沒找到

        if(head->left == now || head->right == now)
            return head;                                            //找到節點回傳

        AVLtreeType left  = searchParent(head->left, now);          //往下的左節點尋找
        AVLtreeType right = searchParent(head->right, now);         //往下的右節點尋找

        return left ? left : right;                                 //如果左子樹中存在目標節點的父節點，返回左子樹的根節點，否則返回右子樹的根節點。
    }

    //向上探索是否平衡
    AVLtreeType up(AVLtreeType temp)
    {
        AVLtreeType parent = NULL;
        AVLtreeType now    = temp;

        for(; now != NULL ; now = parent)
        {
            parent = searchParent(root, now);

            if(parent == NULL)
                break;

            if(parent->left == now)
            {
                now          = rotate(now);
                parent->left = now;
            }
            else if(parent->right == now)
            {
                now           = rotate(now);
                parent->right = now;
            }
        }
        now = rotate(now);
        return now;
    }

    //LL 左旋轉
    AVLtreeType rotateLL(AVLtreeType x)
    {
        AVLtreeType y = x->left;                        //先讓y指向x的左子樹的左指標，用於保存旋轉後的新節點

        x->left  = y->right;                            //x的左子樹指向y的右子樹，完成旋轉第一步
        y->right = x;                                   //y的右子樹指向x節點，完成旋轉第二步

        return y;                                       //再把y節點回傳這樣就完成了左旋轉第三步
    }

    //RR 右旋轉
    AVLtreeType rotateRR(AVLtreeType x)
    {
        AVLtreeType y = x->right;                       //先讓y指向x的右子樹的左指標，用於保存旋轉後的新節點

        x->right = y->left;                             //x的右子樹指向y的左子樹，完成旋轉第一步
        y->left  = x;                                   //y的左子樹指向x節點，完成旋轉第二步
        return y;                                       //再把y節點回傳這樣就完成了右旋轉第三步
    }

    //LR 先子節點右旋轉 在節點左旋轉
    AVLtreeType rotateLR(AVLtreeType x)
    {
        x->left = rotateRR(x->left);                    //呼叫右旋轉，讓左子節點先旋轉一次
        x       = rotateLL(x);                          //呼叫左旋轉，讓根節點旋轉一次
        return x;
    }

    //RL 先子節點左旋轉 在節點右旋轉
    AVLtreeType rotateRL(AVLtreeType x)
    {
        x->right = rotateLL(x->right);                  //呼叫左旋轉，讓右子節點先旋轉一次
        x        = rotateRR(x);                         //呼叫右旋轉，讓根節點先旋轉一次
        return x;
    }

    //判斷平衡，跟各個旋轉
    AVLtreeType rotate(AVLtreeType temp)
    {
        if(getBF(temp) == 2)                                                                //左子樹比右子樹高 LL or LR
        {
            if(getBF(temp->left) == 1 || getBF(temp->left) == 0)
                return rotateLL(temp);                                                      //左子樹的左子樹比左子樹的右子樹高 LL
            else if(getBF(temp->left) == -1)
                return rotateLR(temp);                                                      //左子樹的左子樹比左子樹的右子樹矮 LR
        }
        else if(getBF(temp) == -2)                                                          //左子樹比右子樹矮二 RR or RL
        {
            if(getBF(temp->right) == -1 || getBF(temp->right) == 0)
                return rotateRR(temp);                                                      //右子樹的左子樹比右子樹的右子樹矮 RR
            else if(getBF(temp->right) == 1)
                return rotateRL(temp);                                                      //右子樹的左子樹比右子樹的右子樹高 RL
        }

        return temp;
    }

public:
    AVL_Tree() : fileNO(""), root(NULL)
    {
    }                           // constructor: do nothing

    bool readFile()             // read records from a file
    {
        ifstream ifs;

        data.clear();
        fileNO = "";

        string     strs, temp;
        schoolType List;

        if(fileNO == "")
        {
            cout << "\nInput a file number [0: quit]: ";
            cin >> fileNO;
        } // if

        ifs.open("input" + fileNO + ".txt");

        while(!ifs)
        {
            if(fileNO == "0")
            {
                ifs.close();
                return false;
            } // if

            cout << "\n### input" + fileNO + ".txt does not exist! ###" << endl;
            cout << "\nInput a file number [0: quit]: ";
            cin >> fileNO;
            ifs.open("input" + fileNO + ".txt");
        } // while

        getline(ifs, temp);                            //跳過第一行
        getline(ifs, temp);                            //跳過第二行
        getline(ifs, temp);                            //跳過第三行
        while(!ifs.eof())                              //掃到沒有
        {
            getline(ifs, temp);                        //一行行讀直到最後一行
            if(temp.size() < 2)
                break;                                 //如果沒數劇跳出迴圈，不放入
            int i = 0;
            List.no = data.size() + 1;                 // 放上序號
            for(int j = 0; j < 13; j++)                //以tab鍵做判斷，把行數切成13段依序放入暫時的vector中
            {
                strs.clear();
                for(; i < temp.size() && temp[i] != '\t'; i++)
                {
                    strs += temp[i];
                    if(j == 1 || j == 3 || j == 4 || j == 5 || j == 8)
                        List.sData += temp[i];
                }
                i++;
                if(j == 1 || j == 3 || j == 4 || j == 5 || j == 8)
                    List.sData += '\t';
                if(j == 1)
                    List.sName = strs;                            // school name 學校名稱
                if(j == 8)
                    List.gNum = stoi(strs);                       // graduate number 上學年度畢業生數
            } // for

            data.push_back(List);
            List.sData = "";
        } // while()

        ifs.close();

        return true;
    } // read records from a file

    //一筆一筆新增近樹中，跟平衡
    void add()                                          //將一筆一筆資料加入樹中
    {
        AVLtreeType now = NULL;

        for(int i = 0 ; i != data.size() ; i++)
        {
            addNode(data[i].gNum, data[i].no);

            //check 找到最後那一格的
            now  = search(data[i].gNum, root);          //找放入的那個節點
            root = up(now);                             //向上找平衡，如果不平衡旋轉
        }
    }

    void show()
    {
        cout << "Tree height = " << getH(root) << endl;
        cout << "Number of nodes = " << node << endl;
        int j = 1;
        for(auto strs: root->rSet)
            for(int i = 0 ; i != data.size() ; i++)
                if(strs == data[i].no)
                {
                    cout << j << ": [" << data[i].no << "] " << data[i].sData << endl;
                    j++;
                    break;
                }
    }

    void clearUp()       // erase the object content
    {
        data.clear(); fileNO.clear(); root = NULL; node = 0;
    }                    // end clearUp

    ~AVL_Tree()
    {
        clearUp();
    } // destructor: destroy the object
};    // class AVL_Tree


int main()
{
    int      command = 0; // user command
    AVL_Tree orders;      // a list of orders

    while(1)
    {
        cout << endl << "*** Search Tree Utilities **";
        cout << endl << "* 0. QUIT                  *";
        cout << endl << "* 1. Build 2-3 tree        *";
        cout << endl << "* 2. Build AVL tree        *";
        cout << endl << "****************************";
        cout << endl << "Input a command(0, 1, 2): ";
        cin >> command; // get the command

        if(command == 0)
            return 0;

        if(command == 1)
        {
        } // command == 1

        if(command == 2)
        {
            if(!orders.readFile())
                continue;

            orders.add();
            orders.show();
            orders.clearUp();
        } // command == 2

        if(command != 1 && command != 2)
            cout << endl << "Command does not exist!" << endl;
    } // while
}     // main()
