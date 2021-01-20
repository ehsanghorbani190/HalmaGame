#define boardSize 10 //size of the board
#define beadType 3
#define playerCount 2
#define leaveCampValue 50
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
const char * Note = R"V0G0N(
 _    ______________  __   ______  _______  ____  ____  _________    _   ________   _   ______  ____________
| |  / / ____/ __ \ \/ /  /  _/  |/  / __ \/ __ \/ __ \/_  __/   |  / | / /_  __/  / | / / __ \/_  __/ ____/
| | / / __/ / /_/ /\  /   / // /|_/ / /_/ / / / / /_/ / / / / /| | /  |/ / / /    /  |/ / / / / / / / __/   
| |/ / /___/ _, _/ / /  _/ // /  / / ____/ /_/ / _, _/ / / / ___ |/ /|  / / /    / /|  / /_/ / / / / /___   
|___/_____/_/ |_| /_/  /___/_/  /_/_/    \____/_/ |_| /_/ /_/  |_/_/ |_/ /_/    /_/ |_/\____/ /_/ /_____/   
                                                                                                            
)V0G0N";