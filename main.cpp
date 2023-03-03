#include<bits/stdc++.h> 
using namespace std; 

// Alphabet size (# of symbols) 
#define ALPHABET_SIZE (26) 

// Converts key current character into index 
// use only 'a' through 'z' and lower case 
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') 

// trie node 
struct TrieNode 
{ 
	struct TrieNode *children[ALPHABET_SIZE]; 

	// isWordEnd is true if the node represents 
	// end of a word 
	bool isWordEnd; 
}; 

// Returns new trie node (initialized to NULLs) 
struct TrieNode *getNode(void) 
{ 
	struct TrieNode *pNode = new TrieNode; 
	pNode->isWordEnd = false; 

	for (int i = 0; i < ALPHABET_SIZE; i++) 
		pNode->children[i] = NULL; 

	return pNode; 
} 

// If not present, inserts key into trie. If the 
// key is prefix of trie node, just marks leaf node 
void insert(struct TrieNode *root, const string key) 
{ 
	struct TrieNode *curr = root; 

	for (int level = 0; level < key.length(); level++) 
	{ 
		int index = CHAR_TO_INDEX(key[level]); 
		if (!curr->children[index]) 
			curr->children[index] = getNode(); 

		curr = curr->children[index]; 
	} 

	// mark last node as leaf 
	curr->isWordEnd = true; 
} 

// Returns true if key presents in trie, else false 
bool search(struct TrieNode *root, const string key) 
{ 
	int length = key.length(); 
	struct TrieNode *curr = root; 
	for (int level = 0; level < length; level++) 
	{ 
		int index = CHAR_TO_INDEX(key[level]); 

		if (!curr->children[index]) 
			return false; 

		curr = curr->children[index]; 
	} 

	return (curr != NULL && curr->isWordEnd); 
} 

// Returns 0 if current node has a child 
// If all children are NULL, return 1. 
bool isLastNode(struct TrieNode* root) 
{ 
	for (int i = 0; i < ALPHABET_SIZE; i++) 
		if (root->children[i]) 
			return 0; 
	return 1; 
} 

// Recursive function to print auto-suggestions for given 
// node. 
void suggestionsRec(struct TrieNode* root, string currPrefix) 
{ 
	// found a string in Trie with the given prefix 
	if (root->isWordEnd) 
	{ 
		cout << currPrefix; 
		cout << endl; 
	} 

	// All children struct node pointers are NULL 
	if (isLastNode(root)) 
		return; 

	for (int i = 0; i < ALPHABET_SIZE; i++) 
	{ 
		if (root->children[i]) 
		{ 
			// append current character to currPrefix string 
			currPrefix.push_back(97 + i); 

			// recur over the rest 
			suggestionsRec(root->children[i], currPrefix); 
			currPrefix.pop_back();
		} 
	} 
	
} 

// print suggestions for given query prefix. 
int printAutoSuggestions(TrieNode* root, const string query) 
{ 
	struct TrieNode* curr = root; 

	// Check if prefix is present and find the 
	// the node (of last level) with last character 
	// of given string. 
	int level; 
	int n = query.length(); 
	for (level = 0; level < n; level++) 
	{ 
		int index = CHAR_TO_INDEX(query[level]); 

		// no string in the Trie has this prefix 
		if (!curr->children[index]) 
			return 0; 

		curr = curr->children[index]; 
	} 

	// If prefix is present as a word. 
	bool isWord = (curr->isWordEnd == true); 

	// If prefix is last node of tree (has no 
	// children) 
	bool isLast = isLastNode(curr); 

	// If prefix is present as a word, but 
	// there is no subtree below the last 
	// matching node. 
	if (isWord && isLast) 
	{ 
		cout << query << endl; 
		return -1; 
	} 

	if (!isLast) 
	{ 
		string prefix = query; 
		suggestionsRec(curr, prefix); 
		return 1; 
	} 
}
//delete the word
bool removeword(TrieNode *root, string word) {
        //TrieNode* curr=root;
        if(word.size() == 0) {
            root->isWordEnd = false;
           // cout<<"Word deleted successfully "<<"\n";
            return true ;
            }

        int index = word[0] - 'a';
        TrieNode* child;

        if(root->children[index] != NULL) {
            child = root->children[index];
        }
        else {
        // absent
            //cout << "Word not found!! Unable to delete!!\n";
            return false ;
        }

        return removeword(child, word.substr(1));
}
    
 //update the word 
void updateword(TrieNode* root,string word, string newword){
    removeword(root,word);
    insert(root,newword);
}

// Driver Code 
int main() 
{ 
    struct TrieNode* root = getNode(); 
    int choice;
    while(1){
    cout<<endl<<"Enter 1 for Insertion of elements into Trie "<<endl;
    cout<<"Enter 2 for searching of elements into Trie "<<endl;
    cout<<"Enter 3 for Deletion of elements into Trie "<<endl;
    cout<<"Enter 4 for Updation of elements into Trie "<<endl;
    cout<<"Enter 5 to exit"<<endl;
    cout<<"Enter your choice"<<endl;
    cin>>choice;
    switch(choice)
    {
        //insertion of words
        case 1:{
            cout<<"Enter word to be inserted ";
            string word;
            cin>>word;
            insert(root,word);
            break;
        }
        //searching and autocorrect
        case 2:{
            string  key;
        	cout<<"Enter the key to be searched for :";
        	cin>>key;
        	cout<<endl;
        	if(search(root,key)) {
        	    cout<<key<<endl;
        	}
        	else{
        	int comp = printAutoSuggestions(root, key); 
        
        	if (comp == -1) 
        		cout << "No other strings found with this prefix\n"; 
        
        	else if (comp == 0) 
        		cout << "No string found with this prefix\n"; 
        	}
        	break;
        }
        
        //deletion of any word
        case 3:{
            cout<<"Enter the word you want to delete:";
        	string k;
        	cin>>k;
        	cout<<endl;
        	if(removeword(root,k))
        	cout<<"Word is deleted successfully"<<endl;
        	break;
        }
        //updating a word 
        case 4:{
            cout<<"Enter the word to be updated"<<endl;
            string oldword;
            cin>>oldword;
            cout<<endl;
            cout<<"Enter the word by which you want to replace the existing word";
            string newword;
            cin>>newword;
            cout<<endl;
            updateword(root,oldword,newword);
            break;
            }
        case 5:{
            exit(1);
            }
        } 
    }
	return 0; 
} 
