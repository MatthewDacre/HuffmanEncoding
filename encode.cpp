#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>
#include <stack>
using namespace std;

typedef pair<int, char> pi;

class TreeNode{
public:
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;

    char value = '*';
    int frequency = -1;

    bool operator<(const TreeNode &other){
        if(frequency < other.frequency){
            return true;
        }else if(frequency > other.frequency){
            return false;
        }else if(value < other.value){
            return true;
        }else {
            return false;
        }
    }

    void preorder(){
        cout << value << "[" << frequency << "] ";
        if(left) left->preorder();
        if(right) right->preorder();
    }
};

typedef pair<int, TreeNode*> ti;

TreeNode *merge(TreeNode *t1, TreeNode* t2){
    // Return a new node with t1 and t2 as children
    TreeNode *output = new TreeNode();
    if(*t1 < *t2)
    {
        output->left = t1;
        output->right = t2;
    }
    else
    {
        output->left = t2;
        output->right = t1;
    }
    output->frequency = t1->frequency + t2->frequency;
    return output;
}

void inOrderTrav(TreeNode*root)
{
    if(root->right != nullptr)
    {
    inOrderTrav(root->right);
    }
    cout<<root->frequency << " " << root->value << endl;
    if(root->left != nullptr)
    {
    inOrderTrav(root->left);
    }
}

vector<pair<char, string>> code(TreeNode*root)
{
    string code = "";
    vector <pair<char, string>> ret;
    stack<pair<string, TreeNode*>> stk;
    stk.push(make_pair(code, root));
    while(stk.size()>0)
    {
        pair<string, TreeNode*> temp = stk.top();
        stk.pop();
        if(temp.second->value != '*')
        {
            ret.push_back(make_pair(temp.second->value, temp.first));
        }
        if(temp.second->left != nullptr)
        {
            string tmpcode = temp.first + "0";
            stk.push(make_pair(tmpcode, temp.second->left));
        }
        if(temp.second->right != nullptr)
        {
            string tmpcode = temp.first + "1";
            stk.push(make_pair(tmpcode, temp.second->right));
        }
    }
    return ret;
}

string find(vector<pair<char, string>> vec, char t)
{
    for(int i = 0; i<vec.size(); i++)
    {
        if(vec[i].first == t)
        {
            return vec[i].second;
        }
    }
}

int main()
{
// This is how to use the tree
//    TreeNode *l1 = new TreeNode();
//    TreeNode *l2 = new TreeNode();

//    l1->value = 'i';
//    l1->frequency = 4;

//    l2->value = 'h';
//    l2->frequency = 4;

//    l1->preorder(); cout << endl;

//    if(*l1 < *l2){
//        cout << "L1 <  L2" << endl;
//    }else{
//        cout << "L1 >= L2" << endl;
//    }


    string line;
    getline(cin, line);
    // Build frequency table
    vector<pi>count;
    //Building frequencies
    for(int i = 0; i < line.size(); i++)
    {
        char temp = line[i];
        bool tmpfound = false;
        for(int j = 0; j<count.size(); j++)
        {
            if(count[j].second == temp)
            {
                count[j].first += 1;
                tmpfound = true;
            }
        }
        if(!tmpfound)
        {
            count.push_back(make_pair(1,temp));
        }
        tmpfound = false;
    }
    //Declaring and inserting frequencies into priority queue. Sorted in ascending order (pi == pair<int, char>)
    priority_queue<pi, vector<pi>, greater<pi>>pq;
    int size = count.size();
    for(int c = 0; c<count.size(); c++)
    {
        pq.emplace(count[c]);
    }
    //Printing Items
    priority_queue<pi, vector<pi>, greater<pi>> temp = pq;
    for(int i = 0; i < pq.size(); i++)
    {
        cout<<temp.top().second << " ";
        temp.pop();
    }
    cout<<endl;
    temp = pq;
    for(int j = 0; j<pq.size(); j++)
    {
        cout<<temp.top().first<<" ";
        temp.pop();
    }
    cout<<endl;
    // Create the tree
    //Converting each pair(pi) into a treenode
    priority_queue<ti, vector<ti>, greater<ti>> treeQueue;
    int tsize = size;
    while(pq.size() > 0)
    {
        TreeNode *tmp = new TreeNode;
        tmp->frequency = pq.top().first;
        tmp->value = pq.top().second;
        pq.pop();
        treeQueue.emplace(make_pair(tmp->frequency, tmp));
    }
    while(treeQueue.size()>1)
    {
        //cout<<treeQueue.top().first << " " << treeQueue.top().second << endl;
        TreeNode*tmpNode1 = new TreeNode;
        TreeNode*tmpNode2 = new TreeNode;
        TreeNode*mergeNode = new TreeNode;
        tmpNode1 = treeQueue.top().second;
        treeQueue.pop();
        tmpNode2 = treeQueue.top().second;
        treeQueue.pop();
        mergeNode = merge(tmpNode1, tmpNode2);
        treeQueue.emplace(make_pair(mergeNode->frequency, mergeNode));
    }
    // Encode the string
    TreeNode*root = treeQueue.top().second;
    vector<pair<char, string>>codes = code(root);
    // Output encoding
    string tempStr = "";
    for(int i = 0; i<line.size(); i++)
    {
        tempStr = tempStr + find(codes, line[i]);
    }
    cout<<tempStr << endl;
    int countP = 1;
    int counter = 0;
    while(countP < codes.size())
    {
        countP *= 2;
        counter++;
    }
    int totalBitsCod = tempStr.length();
    int totalBitsUnc = 8*line.length();
    cout << "Total Bits (Original):" << totalBitsUnc << endl << "Total Bits (Coded):" << totalBitsCod << endl;
    return 0;
}
