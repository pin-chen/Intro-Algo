class Solution {
public:
    
    vector<vector<string>> ans;
    
    bool isValid(int r,int c,int n, vector<bool> &d1,vector<bool> &d2, vector<bool> &rv, vector<bool> &cv){
        
        if(d1[r+c] || d2[n-(c-r+1)] || rv[r] || cv[c])return false;
        
        return true;
    }
    
    void solve(int r, int n, vector<string> &board, vector<bool> &d1,vector<bool> &d2, vector<bool> &rv, vector<bool> &cv){
        
        if(r == n){
            ans.push_back(board);
            return ;
        }
        
        
        for(int c = 0 ; c < n ; c++){
            
            if(isValid(r, c, n, d1, d2, rv, cv)){
                
                board[r][c] = 'Q';
                d1[r+c] = true;
                d2[n-(c-r+1)] = true;
                rv[r] = true;
                cv[c] = true;
                
                solve(r+1, n, board, d1, d2, rv, cv);
                
                d1[r+c] = false;
                d2[n-(c-r+1)] = false;
                rv[r] = false;
                cv[c] = false;
                board[r][c] = '.';
            }
        }
        
    }
    
    vector<vector<string>> solveNQueens(int n) {
        
        vector<string> board;
        
        for(int i = 0 ; i < n ; i++){
            string t(n,'.');
            board.push_back(t);
        }
        
        vector<bool> d1(2*n-1,false),d2(2*n-1,false), rv(n,false), cv(n,false);
        
        solve(0, n, board, d1, d2, rv, cv);
        
        return ans;
    }
};