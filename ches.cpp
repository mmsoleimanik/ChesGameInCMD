#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

void swap(string *str1 , string *str2) {
    string temp; temp = *str1;
    *str1 = *str2;
    *str2 = temp;
    return;
}

string board_ch[8][8] = {
    {"1R0" , "1H0" , "1E0" , "1K0" , "1M0" , "1E1" , "1H1" , "1R1"} , 
    {"1S0" , "1S1" , "1S2" , "1S3" , "1S4" , "1S5" , "1S6" , "1S7"} ,
    {"   " , "   " , "   " , "   " , "   " , "   " , "   " , "   "} ,
    {"   " , "   " , "   " , "   " , "   " , "   " , "   " , "   "} ,
    {"   " , "   " , "   " , "   " , "   " , "   " , "   " , "   "} ,
    {"   " , "   " , "   " , "   " , "   " , "   " , "   " , "   "} ,
    {"2S0" , "2S1" , "2S2" , "2S3" , "2S4" , "2S5" , "2S6" , "2S7"} ,
    {"2R0" , "2H0" , "2E0" , "2M0" , "2K0" , "2E1" , "2H1" , "2R1"}
};//front board of ches that show the game
int board_num[8][8] = {0};//the back of the board that specify the sides of gamer

struct soldier {
    int color;// 1 or -1
    int number;
    int place[2];
    bool first_move = true;

    bool cango(int newplace[2]) {
        //just one step to front
        if (newplace[0]==place[0]+1*color && newplace[1]==place[1] && board_num[newplace[0]][newplace[1]]==0) {
            first_move = false;
            return true;
        }
        //to hit enemy
        else if (newplace[0]==place[0]+1*color && (newplace[1]==place[1]+1 || newplace[1]==place[1]-1) && board_num[newplace[0]][newplace[1]]==-1*color) {
            first_move = false;
            return true;
        }
        //to step for fist move
        else if (first_move && newplace[0]==place[0]+2*color && newplace[1]==place[1] && board_num[newplace[0]][newplace[1]]==0) {
            first_move = false;
            return true;
        }
        return false;
    }
    
};

struct horse {
    int color;// 1 or -1
    int number;
    int place[2];

    bool cango(int newplace[2]) {
        //only L move
        if ((newplace[0]==place[0]+2 || newplace[0]==place[0]-2) && (newplace[1]==place[1]+1 || newplace[1]==place[1]-1)) {
            return true;
        }
        else if ((newplace[0]==place[0]+1 || newplace[0]==place[0]-1) && (newplace[1]==place[1]+2 || newplace[1]==place[1]-2)) {
            return true;
        }
        return false;
    }
};

struct elephant {
    int color;//-1 or 1
    int number;
    int place[2];

    bool cango(int newplace[2]) {
        //only diagonal move
        if (newplace[1]-place[1]==newplace[0]-place[0] || newplace[1]-place[1]==place[0]-newplace[0]) {
            int Dcolumn = newplace[1]-place[1];//to define DELTA column
            int Drow = newplace[0]-place[0];//to define DELTA row
            if (Drow>0) {
                for (int i=1; i<Drow; i++) {
                    //to prevent from crash with enemys
                    if (Dcolumn>0 && board_num[place[0]+i][place[1]+i]!=0) {
                        return false;
                    }
                    else if (Dcolumn<0 && board_num[place[0]+i][place[1]-i]!=0) {
                        return false;
                    }
                }
                return true;
            }
            else if (Drow<0) {
                for (int i=1; i<(-1*Drow); i++) {
                    //to prevent from crash with enemys
                    if (Dcolumn>0 && board_num[place[0]-i][place[1]+i]!=0) {
                        return false;
                    }
                    else if (Dcolumn<0 && board_num[place[0]-i][place[1]-i]!=0) {
                        return false;
                    }
                }
                return true;
            }
            //to define 00 move
            else if (Drow==0) {
                return false;
            }
        }
        return false;
    }
};

struct minister {
    int color;//-1 or 1
    int place[2];
    
    /*bool cango(int newplace[2]) {
        //move only left or right
        if (newplace[0]==place[0] && newplace[1]!=place[1]) {
            int Dcolumn = newplace[1]-place[1];
            if (Dcolumn>0) {
                for (int i=1; i<Dcolumn-1; i++) {
                    if (board_num[newplace[0]][newplace[1]+i]!=0) {
                        return false;
                    }
                }
                return true;
            }
            else if (Dcolumn<0) {
                for (int i=1; i<(0-Dcolumn)-1; i++) {
                    if (board_num[newplace[0]][newplace[1]-i]!=0) {
                        return false;
                    }
                }
                return true;
            }
        }
        //move only up or down
        else if (newplace[1]==place[1] && newplace[0]!=place[0]) {
            int Drow = newplace[0]-place[0];
            if (Drow>0) {
                for (int i=1; i<Drow; i++) {
                    if (board_num[newplace[0]+i][newplace[1]]!=0) {
                        return false;
                    }
                }
                return true;
            }
            else if (Drow<0) {
                for (int i=1; i<(0-Drow); i++) {
                    if (board_num[newplace[0]-i][newplace[1]]!=0) {
                        return false;
                    }
                }
                return true;
            }
        }
        //only diagonal move
        else if (newplace[1]-place[1]==newplace[0]-place[0] || newplace[1]-place[1]==place[0]-newplace[0]) {
            int Dcolumn = newplace[1]-place[1];//to define DELTA column
            int Drow = newplace[0]-place[0];//to define DELTA row
            if (Drow>0) {
                for (int i=1; i<Drow; i++) {
                    if (Dcolumn>0 && board_num[place[0]+i][place[1]+i]!=0) {
                        return false;
                    }
                    else if (Dcolumn<0 && board_num[place[0]+i][place[1]-i]!=0) {
                        return false;
                    }
                }
                return true;
            }
            else if (Drow<0) {
                for (int i=1; i<(-1*Drow); i++) {
                    if (Dcolumn>0 && board_num[place[0]-i][place[1]+i]!=0) {
                        return false;
                    }
                    else if (Dcolumn<0 && board_num[place[0]-i][place[1]-i]!=0) {
                        return false;
                    }
                }
                return true;
            }
            //to define 00 move
            else if (Drow==0) {
                return false;
            }
        }
        return false;
    }*/


    //powered by Qwen-AI
    bool cango(int newplace[2]) {
        int Dcolumn = newplace[1] - place[1];
        int Drow = newplace[0] - place[0];
    
        // Check if move is vertical, horizontal, or diagonal
        bool isVertical = (Dcolumn == 0 && Drow != 0);
        bool isHorizontal = (Drow == 0 && Dcolumn != 0);
        bool isDiagonal = (abs(Drow) == abs(Dcolumn));
    
        if (!isVertical && !isHorizontal && !isDiagonal) {
            return false;//invalid move
        }
        //Determine direction and step size
        int step_row = (Drow > 0) ? 1 : (Drow < 0) ? -1 : 0;
        int step_column = (Dcolumn > 0) ? 1 : (Dcolumn < 0) ? -1 : 0;
    
        // Check for obstructions
        int steps = max(abs(Drow), abs(Dcolumn));
        for (int i = 1; i < steps; i++) {
            int check_row = place[0] + i * step_row;
            int check_column = place[1] + i * step_column;
    
            //Bounds check
            if (check_row < 0 || check_row >= 8 || check_column < 0 || check_column >= 8) {
                return false;//out of board
            }
    
            //Obstruction check
            if (board_num[check_row][check_column] != 0) {
                return false;
            }
        }
    
        return true;//valid move
    }
};

struct  rokh {
    int color;//-1 or 1;
    int number;
    int place[2];

    /*bool cango(int newplace[2]) {
        //move only left or right
        if (newplace[0]==place[0] && newplace[1]!=place[1]) {
            int Dcolumn = newplace[1]-place[1];
            if (Dcolumn>0) {
                for (int i=1; i<Dcolumn; i++) {
                    if (board_num[newplace[0]][newplace[1]+i]!=0) {
                        return false;
                    }
                }
                return true;
            }
            else if (Dcolumn<0) {
                for (int i=1; i<(-1*Dcolumn); i++) {
                    if (board_num[newplace[0]][newplace[1]-i]!=0) {
                        return false;
                    }
                }
                return true;
            }
        }
        //move only up or down
        else if (newplace[1]==place[1] && newplace[0]!=place[0]) {
            int Drow = newplace[0]-place[0];
            if (Drow>0) {
                for (int i=1; i<Drow; i++) {
                    if (board_num[newplace[0]+i][newplace[1]]!=0) {
                        return false;
                    }
                }
                return true;
            }
            else if (Drow<0) {
                for (int i=1; i<(-1*Drow); i++) {
                    if (board_num[newplace[0]-i][newplace[1]]!=0) {
                        return false;
                    }
                }
                return true;
            }
        }
        return false;
    }*/

    //powered by Qwen-AI
    bool cango(int newplace[2]) {
        int Dcolumn = newplace[1] - place[1];
        int Drow = newplace[0] - place[0];
    
        // Check if move is vertical, horizontal, or diagonal
        bool isVertical = (Dcolumn == 0 && Drow != 0);
        bool isHorizontal = (Drow == 0 && Dcolumn != 0);
        bool isDiagonal = (abs(Drow) == abs(Dcolumn));
    
        if (!isVertical && !isHorizontal && !isDiagonal) {
            return false;//invalid move
        }
        //Determine direction and step size
        int step_row = (Drow > 0) ? 1 : (Drow < 0) ? -1 : 0;
        int step_column = (Dcolumn > 0) ? 1 : (Dcolumn < 0) ? -1 : 0;
    
        // Check for obstructions
        int steps = max(abs(Drow), abs(Dcolumn));
        for (int i = 1; i < steps; i++) {
            int check_row = place[0] + i * step_row;
            int check_column = place[1] + i * step_column;
    
            //Bounds check
            if (check_row < 0 || check_row >= 8 || check_column < 0 || check_column >= 8) {
                return false;//out of board
            }
    
            //Obstruction check
            if (board_num[check_row][check_column] != 0) {
                return false;
            }
        }
    
        return true;//valid move
    }
};

struct king {
    int color;//-2 or 2;
    int place[2];

    bool cango(int newplace[2]) {
        //only lef or right just in one step
        if (newplace[0]==place[0] && (newplace[1]==place[1]+1 || newplace[1]==place[1]-1) && board_num[newplace[0]][newplace[1]]*color<=0) {
            return true;
        }
        //only up or down just in one step
        else if (newplace[1]==place[1] && (newplace[0]==place[0]+1 || newplace[0]==place[0]-1) && board_num[newplace[0]][newplace[1]]*color<=0) {
            return true;
        }
        return false;
    }
};

//to define elements: [0]==>color +1      [1]==>color -1
soldier s[2][8];
king k[2];
minister m[2];
rokh r[2][2];
elephant e[2][2];
horse h[2][2];

// Function to set console text color
void SetColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}





int main() {
    // Define color codes
    const int GRAY_TEXT = FOREGROUND_RED | FOREGROUND_GREEN; // Low-intensity gray
    const int WHITE_TEXT = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; // High-intensity white
    const int DEFAULT_COLOR = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; // Default white text
    const int BLUE = FOREGROUND_BLUE | FOREGROUND_GREEN;

    /*create "br"
    11121111
    11111111
    00000000
    00000000
    00000000
    00000000
    -1-1-1-1-1-1-1-1
    -1-1-1-1-2-1-1-1
    */
    for (int i=0; i<2; i++) {
        for (int j=0; j<8; j++) {
            board_num[i][j] = 1;
        }
    }
    board_num[0][3]=2;
    for (int i=7; i>5; i--) {
        for (int j=0; j<8; j++) {
            board_num[i][j] = -1;
        }
    }
    board_num[7][4]=-2;


    //to define elements of game
    //team of +1
    //for soldiers
    for (int i=0; i<8; i++) {
        s[0][i].color = 1;
        s[0][i].number = i;
        s[0][i].place[0]=1; s[0][i].place[1]=i;
    }
    //for rokhs
    r[0][0].color = 1;  r[0][1].color = 1;
    r[0][0].number = 0; r[0][1].number = 1;
    r[0][0].place[0] = 0; r[0][0].place[1]=0;
    r[0][1].place[0] = 0; r[0][1].place[1]=7;
    //for horses
    h[0][0].color = 1;  h[0][1].color = 1;
    h[0][0].number = 0; h[0][1].number = 1;
    h[0][0].place[0] = 0; h[0][0].place[1]=1;
    h[0][1].place[0] = 0; h[0][1].place[1]=6;
    //for elephants
    e[0][0].color = 1;  e[0][1].color = 1;
    e[0][0].number = 0; e[0][1].number = 1;
    e[0][0].place[0] = 0; e[0][0].place[1]=2;
    e[0][1].place[0] = 0; e[0][1].place[1]=5;
    //for king
    k[0].color = 2;
    k[0].place[0] = 0; k[0].place[1]=3;
    //for minister
    m[0].color = 1;
    m[0].place[0]=0; m[0].place[1]=4;
    
    //team of -1
    //for soldiers
    for (int i=0; i<8; i++) {
        s[1][i].color = -1;
        s[1][i].number = i;
        s[1][i].place[0]=6; s[1][i].place[1]=i;
    }
    //for rokhs
    r[1][0].color = -1;  r[1][1].color = -1;
    r[1][0].number = 0; r[1][1].number = 1;
    r[1][0].place[0] = 7; r[1][0].place[1]=0;
    r[1][1].place[0] = 7; r[1][1].place[1]=7;
    //for horses
    h[1][0].color = -1;  h[1][1].color = -1;
    h[1][0].number = 0; h[1][1].number = 1;
    h[1][0].place[0] = 7; h[1][0].place[1]=1;
    h[1][1].place[0] = 7; h[1][1].place[1]=6;
    //for elephants
    e[1][0].color = -1;  e[1][1].color = -1;
    e[1][0].number = 0; e[1][1].number = 1;
    e[1][0].place[0] = 7; e[1][0].place[1]=2;
    e[1][1].place[0] = 7; e[1][1].place[1]=5;
    //for king
    k[1].color = -2;
    k[1].place[0] = 7; k[1].place[1]=4;
    //for minister
    m[1].color = -1;
    m[1].place[0]=7; m[1].place[1]=3;

    /*to define the board shown of game
        0   1   2   3   4   5   6   7
     0 [R0][H0][E0][K0][M0][E1][H1][R1]
     1 [S0][S1][S2][S3][S4][S5][S6][S7]
     2 [  ][  ][  ][  ][  ][  ][  ][  ]
     3 [  ][  ][  ][  ][  ][  ][  ][  ]
     4 [  ][  ][  ][  ][  ][  ][  ][  ]
     5 [  ][  ][  ][  ][  ][  ][  ][  ]
     6 [S0][S1][S2][S3][S4][S5][S6][S7]
     7 [R0][H0][E0][K0][M0][E1][H1][R1]
    */
   cout << "    0   1   2   3   4   5   6   7" << endl;
   for (int i=0; i<8; i++) {
       cout << " " << i << " ";
       for (int j=0; j<8; j++) {
           SetColor(WHITE_TEXT); cout << "[";
           if (board_ch[i][j][0]=='1') {
               SetColor(WHITE_TEXT);
           }
           else {
               SetColor(BLUE);
           } 
           cout << board_ch[i][j][1] << board_ch[i][j][2];
           SetColor(WHITE_TEXT); cout << "]";
       }
       cout << endl;
   }

    //to define for give turn
    int player = 1;
    //nonestop while for turns
    while (true) {
        //to cin prmpt
        string prmpt;
        if (player == 1) {
            cout << "this turn is for WITHE(e.g \"H0=>23\"): " << endl;
        }
        else {
            cout << "this turn is for BLACK(e.g \"H0=>23\"): " << endl;
        }
        cin >> prmpt;//for example "H0=>23" or end

        //for extract the nut from prmpt
        string nut = "000";
        int go_place[2]; go_place[0]=(prmpt[4]-'0'); go_place[1]=(prmpt[5]-'0');//go_place is for newplace that was in structs
        if (player == 1) {
            nut[0]='1'; nut[1]=prmpt[0]; nut[2]=prmpt[1];
        }
        else {
            nut[0]='2'; nut[1]=prmpt[0]; nut[2]=prmpt[1];
        }

        //to define an equal relation betwen nuts_list and color of player
        int equal_player;
        if (player == 1) {
            equal_player = 0;
        }
        else {
            equal_player = 1;
        }

        //for searh of last_place of nut
        int last_place[2]={-1};
        for (int i=0; i<8; i++) {
            for (int j=0; j<8; j++) {
                if (nut == board_ch[i][j]) {
                    last_place[0]=i;
                    last_place[1]=j;
                    break;
                }
            }
        }

        //prmopt should to write correct
        if ((prmpt.size()!=6 || (prmpt[2]!='=' || prmpt[3]!='>') || !(prmpt[1]-'0'<=9 && prmpt[1]-'0'>=0) || !(prmpt[0]>='A' && prmpt[0]<='Z')) && prmpt!="__end" && prmpt!="__continue") {
            cout << "a prmpt error!! write prmpt in true way." << endl;
            continue;
        }

        //newplace should be in board
        if ((go_place[0]<0 || go_place[0]>7 || go_place[1]<0 || go_place[1]>7)  && prmpt!="__end" && prmpt!="__continue") {
            cout << "there is not any cell with this numbers!!" << endl;
            continue;
        }

        //to do prompt
        if (prmpt[0] == 'S' && s[equal_player][prmpt[1]-'0'].cango(go_place)) {
            s[equal_player][prmpt[1]-'0'].place[0]=go_place[0];
            s[equal_player][prmpt[1]-'0'].place[1]=go_place[1];
        }
        else if (prmpt[0] == 'R' && r[equal_player][prmpt[1]-'0'].cango(go_place)) {
            r[equal_player][prmpt[1]-'0'].place[0]=go_place[0];
            r[equal_player][prmpt[1]-'0'].place[1]=go_place[1];
        }
        else if (prmpt[0] == 'H' && h[equal_player][prmpt[1]-'0'].cango(go_place)) {
            h[equal_player][prmpt[1]-'0'].place[0]=go_place[0];
            h[equal_player][prmpt[1]-'0'].place[1]=go_place[1];
        }
        else if (prmpt[0] == 'E' && e[equal_player][prmpt[1]-'0'].cango(go_place)) {
            e[equal_player][prmpt[1]-'0'].place[0]=go_place[0];
            e[equal_player][prmpt[1]-'0'].place[1]=go_place[1];
        }
        else if (prmpt[0] == 'K' && k[equal_player].cango(go_place)) {
            k[equal_player].place[0]=go_place[0];
            k[equal_player].place[1]=go_place[1];
        }
        else if (prmpt[0] == 'M' && m[equal_player].cango(go_place)) {
            m[equal_player].place[0]=go_place[0];
            m[equal_player].place[1]=go_place[1];
        }
        else if (prmpt == "__end") {
            break;
        }
        /*else if (prmpt == "__continue") {
            player *= -1;
            continue;
        }*/
        else {
            cout << "an error!! 1) check your prompt. 2)check that your nut is in board or not. 3)check there is no any nut in way." << endl;
            continue;
        }
        
        //for validate that No piece can collide with its mate.
        if (board_num[last_place[0]][last_place[1]]*board_num[go_place[0]][go_place[1]] > 0) {
           cout << "this nut is in your team!!" << endl;
           continue; 
        }

        //for switch player
        player *= -1;
        //for swap nut in front board
        string tempinstr = board_ch[last_place[0]][last_place[1]];
        board_ch[last_place[0]][last_place[1]] = board_ch[go_place[0]][go_place[1]];
        board_ch[go_place[0]][go_place[1]] = tempinstr;
        //for swap nut in back board
        int tempinint = board_num[last_place[0]][last_place[1]];
        board_num[last_place[0]][last_place[1]]=board_num[go_place[0]][go_place[1]];
        board_num[go_place[0]][go_place[1]] = tempinint;

        //if player hits enemy, opposite player will delete
        if (board_num[last_place[0]][last_place[1]]*board_num[go_place[0]][go_place[1]] < 0) {
            board_num[last_place[0]][last_place[1]]=0;
            board_ch[last_place[0]][last_place[1]] = "   ";
        }

        //give board
        cout << "    0   1   2   3   4   5   6   7" << endl;
        for (int i=0; i<8; i++) {
            cout << " " << i << " ";
            for (int j=0; j<8; j++) {
                SetColor(WHITE_TEXT); cout << "[";
                if (board_ch[i][j][0]=='1') {
                   SetColor(WHITE_TEXT);
                }
                else {
                    SetColor(BLUE);
                } 
                cout << board_ch[i][j][1] << board_ch[i][j][2];
                SetColor(WHITE_TEXT); cout << "]";
            }
            cout << endl;
        }
    }

    return 0;
}