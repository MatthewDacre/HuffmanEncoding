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

int main()
{
    string characters, freq, enc, total1, total2;
    getline(cin, characters);
    getline(cin, freq);
    getline(cin, enc);
    getline(cin, total1);
    getline(cin, total2);
    vector<pi>count;
    for(int i = 0; i < characters.length(); i+=2)
    {
        int charint = freq[i] - '0';
        count.push_back(make_pair(charint, characters[i]));
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

    TreeNode*tree = treeQueue.top().second;
    TreeNode*tempTree = tree;
    string message;
    for(int it = 0; it < enc.length(); it++)
    {
        char t = enc[it];
        if(tempTree->left == nullptr && tempTree->right == nullptr)
        {
            message = message + tempTree->value;
            tempTree = tree;
        }
        else
        {
            if(t == '1')
            {
                tempTree = tempTree->right;
            }
            else if(t == '0')
            {
                tempTree = tempTree->left;
            }
        }
    }
    cout << message << endl;
    return 0;
}
