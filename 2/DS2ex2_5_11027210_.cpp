//DS2ex2_5_11027210_
#include <bits/stdc++.h>


#define     PTR_NUM    3
#define     KEY_NUM    PTR_NUM - 1

using namespace std;

typedef struct sT {
    int    no;              // serial number   序號
    string sName;           // school name 學校名稱

    string sData;           // 6筆資料
}   schoolType;

typedef struct slotT {
    vector<int> rSet;           //存放序號
    string      key;            //放學校名稱
}   slotType;

typedef struct nT {
    slotType   data[KEY_NUM];
    struct nT* link[PTR_NUM];
    struct nT* parent;
}   *nodeType;

class TwoThreeTree {
    void clearUp() {
    } // cut off the

    ~TwoThreeTree() {
        clearUp();
    } // destructor
};    //end TwoThreeTree


typedef struct aT {
    vector<int> rSet;  // data index
    int         key;   // search key
    aT*         left;  // left child
    aT*         right; // right child
}   *AVLtreeType;

class AVL_Tree {
    int node = 0;
    string fileNO;                   // number to form a file name
    vector<schoolType> data;         //資料
    AVLtreeType root;                //AVL樹的根

    int getH(AVLtreeType k) {        //計算樹高
        vector<AVLtreeType> N;
        int H = 0, len;

        if(k == NULL)
            return 0;

        N.push_back(k);
        while(N.size() != 0) {
            len = N.size();
            H++;

            while(len > 0) {
                AVLtreeType temp = N[0];
                N.erase(N.begin());
                if(temp->left != NULL)
                    N.push_back(temp->left);

                if(temp->right != NULL)
                    N.push_back(temp->right);
                len--;
            } // while
        }     // while

        return H;
    } // calculate the tree height

    void addNode(int value, int no) {       //將value加入樹中
        AVLtreeType temp   = root;
        AVLtreeType parent = NULL;

        while(temp != NULL) {
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

        if(root == NULL) {
            root      = new aT;
            root->key = value;
            root->rSet.push_back(no);
            root->left  = NULL;
            root->right = NULL;
            node++;
        }
        else if(value == parent->key)
            parent->rSet.push_back(no);
        else if(value < parent->key) {
            parent->left      = new aT;
            parent->left->key = value;
            parent->left->rSet.push_back(no);
            parent->left->left  = NULL;
            parent->left->right = NULL;
            node++;
        }
        else if(value > parent->key) {
            parent->right      = new aT;
            parent->right->key = value;
            parent->right->rSet.push_back(no);
            parent->right->left  = NULL;
            parent->right->right = NULL;
            node++;
        }
    }

    AVLtreeType rotateLL(AVLtreeType x) {
        AVLtreeType y = x->left;

        x->left  = y->right;
        y->right = x;
        return y;

        /*
         * AVLtreeType y = x -> left;
         * AVLtreeType z = y -> right;
         * y -> right = x ;
         * x -> left = z;
         * return y;
         */
    }

    AVLtreeType rotateRR(AVLtreeType x) {
        AVLtreeType y = x->right;

        x->right = y->left;
        y->left  = x;
        return y;

        /*
         * AVLtreeType y = x -> right;
         * AVLtreeType z = y -> left;
         * y -> left = x ;
         * x -> right = z;
         * return y;
         */
    }

    AVLtreeType rotateLR(AVLtreeType x) {
        /*
         * AVLtreeType y = x -> left;
         * AVLtreeType z = y -> right;
         * y -> right = z -> left;
         * x -> left = z -> right;
         * z -> right = x;
         * z -> left = y ;
         * return z;
         */
        x->left = rotateRR(x->left);
        x       = rotateLL(x);
        return x;
    }

    AVLtreeType rotateRL(AVLtreeType x) {
        /*
         * AVLtreeType y = x -> right;
         * AVLtreeType z = y -> left;
         * y -> left = z -> right;
         * x -> right = z -> left;
         * z -> left = x;
         * z -> right = y ;
         * return z;
         */
        x->right = rotateLL(x->right);
        x        = rotateRR(x);
        return x;
    }

public:
    AVL_Tree() : fileNO(""), root(NULL) {
    }                           // constructor: do nothing

    bool readFile() {           // read records from a file
        ifstream ifs;

        data.clear();
        fileNO = "";

        string     strs, temp;
        schoolType List;

        if(fileNO == "") {
            cout << "\nInput a file number [0: quit]: ";
            cin >> fileNO;
        } // if

        ifs.open("input" + fileNO + ".txt");

        while(!ifs) {
            if(fileNO == "0") {
                ifs.close();
                return false;
            } // if

            cout << "\n### input" + fileNO + ".txt does not exist! ###" << endl;
            cout << "\nInput a file number [0: quit]: ";
            cin >> fileNO;
            ifs.open("input" + fileNO + ".txt");
        } // while

        getline(ifs, temp);                                                //跳過第一行
        getline(ifs, temp);                            //跳過第二行
        getline(ifs, temp);                            //跳過第三行
        while(!ifs.eof()) {                            //掃到沒有
            getline(ifs, temp);                        //一行行讀直到最後一行
            if(temp.size() < 2) break;                 //如果沒數劇跳出迴圈，不放入
            int i = 0;
            List.no = data.size() + 1;                 // 放上序號
            for(int j = 0; j < 13; j++) {              //以tab鍵做判斷，把行數切成13段依序放入暫時的vector中
                strs.clear();
                for(; i < temp.size() && temp[i] != '\t'; i++) {
                    strs += temp[i];
                    if(j == 1 || j == 3 || j == 4 || j == 5 || j == 8) List.sData += temp[i];
                }
                i++;
                if(j == 1 || j == 3 || j == 4 || j == 5 || j == 8) List.sData += '\t';
                if(j == 1) List.sName = strs;                     // school name 學校名稱
                if(j == 8) List.gNum = stoi(strs);                // graduate number 上學年度畢業生數
            } // for

            data.push_back(List);
            List.sData = "";
        } // while()

        ifs.close();

        for(auto strs: data)
            cout << strs.gNum << endl;

        return true;
    } // read records from a file

    void add() {       //將一筆一筆資料加入樹中
        addNode(data[0].gNum, data[0].no);
        int num;
        for(int i = 1 ; i != data.size() ; i++) {
            //check

            cout << getH(root->left) - getH(root->right) << endl;
            if((getH(root->left) - getH(root->right)) > 1) {                                      //左邊向右旋轉 LL
                if((getH(root->left->left) - getH(root->left->right)) == (1 || 0)) root = rotateLL(root);
                else root = rotateLR(root);                                                       //右邊向左旋轉 LR
            }
            else if((getH(root->left) - getH(root->right)) < -1) {                                //右邊向左旋轉 RR
                num = getH(root->right->left) - getH(root->right->right);
                cout << "{" << num << "}" << endl;
                if((getH(root->right->left) - getH(root->right->right)) == (-1 || 0)) root = rotateRR(root);
                else root = rotateRL(root);

                num = getH(root->left) - getH(root->right);
                cout << "[" << num << "]" << endl;
                //else root = rotateRL( root ) ;                                                     //左邊向右旋轉 RL
            }

            //insert
            addNode(data[i].gNum, data[i].no);                          //新增資料放樹中
        }

        cout << getH(root->left) - getH(root->right) << endl;
        if((getH(root->left) - getH(root->right)) > 1) {                                      //左邊向右旋轉 LL
            if((getH(root->left->left) - getH(root->left->right)) == (1 || 0)) root = rotateLL(root);
            else root = rotateLR(root);                                                       //右邊向左旋轉 LR
        }
        else if((getH(root->left) - getH(root->right)) < -1) {                                //右邊向左旋轉 RR
            num = getH(root->right->left) - getH(root->right->right);
            cout << "{" << num << "}" << endl;
            if((getH(root->right->left) - getH(root->right->right)) == (-1 || 0)) root = rotateRR(root);
            else root = rotateRL(root);

            num = getH(root->left) - getH(root->right);
            cout << "[" << num << "]" << endl;
            //else root = rotateRL( root ) ;                                                     //左邊向右旋轉 RL
        }
    }

    void show() {
        cout << "Tree height = " << getH(root) << endl;
        cout << "Number of nodes = " << node << endl;
        int j = 1;
        for(auto strs: root->rSet)
            for(int i = 0 ; i != data.size() ; i++)
                if(strs == data[i].no) {
                    cout << j << ": [" << data[i].no << "] " << data[i].sData << endl;
                    j++;
                    break;
                }
        root = NULL;
    }

    void clearUp() { // erase the object content
        data.clear(); fileNO.clear();
    }                // end clearUp

    ~AVL_Tree() {
        clearUp();
    } // destructor: destroy the object
};    // class AVL_Tree


int main() {
    int      command = 0; // user command
    AVL_Tree orders;      // a list of orders

    while(1) {
        cout << endl << "*** Search Tree Utilities **";
        cout << endl << "* 0. QUIT                  *";
        cout << endl << "* 1. Build 2-3 tree        *";
        cout << endl << "* 2. Build AVL tree        *";
        cout << endl << "****************************";
        cout << endl << "Input a command(0, 1, 2): ";
        cin >> command; // get the command

        if(command == 0) return 0;

        if(command == 1) {
        } // command == 1

        if(command == 2) {
            if(!orders.readFile()) continue;

            orders.add();
            orders.show();
        } // command == 2

        if(command != 1 && command != 2)
            cout << endl << "Command does not exist!" << endl;
    } // while
}     // main()
