#define boardSize 20 //size of the board
#define beadType 4
#define playerCount 4
//keys
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
//Board 
int boardBead[boardSize][boardSize];
//Role : this var shows us which player should play
int Role = 1;

#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))



const char * LOGO = R"V0G0N(
 
          _____                    _____                    _____            _____                    _____          
         /\    \                  /\    \                  /\    \          /\    \                  /\    \         
        /::\____\                /::\    \                /::\____\        /::\____\                /::\    \        
       /:::/    /               /::::\    \              /:::/    /       /::::|   |               /::::\    \       
      /:::/    /               /::::::\    \            /:::/    /       /:::::|   |              /::::::\    \      
     /:::/    /               /:::/\:::\    \          /:::/    /       /::::::|   |             /:::/\:::\    \     
    /:::/____/               /:::/__\:::\    \        /:::/    /       /:::/|::|   |            /:::/__\:::\    \    
   /::::\    \              /::::\   \:::\    \      /:::/    /       /:::/ |::|   |           /::::\   \:::\    \   
  /::::::\    \   _____    /::::::\   \:::\    \    /:::/    /       /:::/  |::|___|______    /::::::\   \:::\    \  
 /:::/\:::\    \ /\    \  /:::/\:::\   \:::\    \  /:::/    /       /:::/   |::::::::\    \  /:::/\:::\   \:::\    \ 
/:::/  \:::\    /::\____\/:::/  \:::\   \:::\____\/:::/____/       /:::/    |:::::::::\____\/:::/  \:::\   \:::\____\
\::/    \:::\  /:::/    /\::/    \:::\  /:::/    /\:::\    \       \::/    / ~~~~~/:::/    /\::/    \:::\  /:::/    /
 \/____/ \:::\/:::/    /  \/____/ \:::\/:::/    /  \:::\    \       \/____/      /:::/    /  \/____/ \:::\/:::/    / 
          \::::::/    /            \::::::/    /    \:::\    \                  /:::/    /            \::::::/    /  
           \::::/    /              \::::/    /      \:::\    \                /:::/    /              \::::/    /   
           /:::/    /               /:::/    /        \:::\    \              /:::/    /               /:::/    /    
          /:::/    /               /:::/    /          \:::\    \            /:::/    /               /:::/    /     
         /:::/    /               /:::/    /            \:::\    \          /:::/    /               /:::/    /      
        /:::/    /               /:::/    /              \:::\____\        /:::/    /               /:::/    /       
        \::/    /                \::/    /                \::/    /        \::/    /                \::/    /        
         \/____/                  \/____/                  \/____/          \/____/                  \/____/         
                                                                                                                     
  Press Any Key To Start :D
)V0G0N";