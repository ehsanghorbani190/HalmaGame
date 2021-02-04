int boardSize = 20;
int playerCount = 4;
int beadType = 4;
int leaveCampValue = 50;
int FPC = 2;
int SPC = 1;
int TPC = 0;
int FoPC = 0; 
//keys
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
//Board 
int **boardBead;
//Role : this var shows us which player should play
int Role = 1;
// Reading from config file
int getColor(char ch){
  switch(ch){
    case 'g':
      return 2;
      break;
    case 'y':
      return 14;
      break;
    case 'b':
      return 1;
      break;
    case 'r':
      return 4;
      break;      
  }
}
void searchConsts()
{
  FILE *constsFile;
  constsFile = fopen("config.txt","r");
  if(!constsFile) {printf("Couldn't read setting from file , using default configuration"); return;}
  char tmp1[20],tmp2[20];
  int tmp3;
  fscanf(constsFile,"%s" , tmp1);
  do{   // find beadtype
    fscanf(constsFile,"%s",tmp1);
      if(strcmp(tmp1,"Size")==0){ 
          fscanf(constsFile,"%s",tmp2);
          fscanf(constsFile,"%d",&tmp3);
          boardSize = tmp3;
      }else
          fscanf(constsFile,"\n");
  } while (strcmp(tmp1,"Size")!=0);
  rewind(constsFile);
  do {// find playerCount
    fscanf(constsFile,"%s",tmp1);
      if(strcmp(tmp1,"Player_Num")==0){ 
          fscanf(constsFile,"%s",tmp2);
          fscanf(constsFile,"%d",&tmp3);
          playerCount = tmp3;
      }else
          fscanf(constsFile,"\n");
  } while (strcmp(tmp1,"Player_Num")!=0);
  rewind(constsFile);
  do{ // find leavecamp value
    fscanf(constsFile,"%s",tmp1);
      if(strcmp(tmp1,"leave_camp_value")==0){ 
          fscanf(constsFile,"%s",tmp2);
          fscanf(constsFile,"%d",&tmp3);
          leaveCampValue = tmp3;
      }else
          fscanf(constsFile,"\n");
  } while (strcmp(tmp1,"leave_camp_value")!=0);
  rewind(constsFile);
  do{ // find beadtype
    fscanf(constsFile,"%s",tmp1);
      if(strcmp(tmp1,"Beads_order")==0){ 
          fscanf(constsFile,"%s",tmp2);
          fgets(tmp2,20,constsFile);
          int l2 = strlen(tmp2);
          beadType = tmp2[l2-2] - '0';
          beadType++;
      }else
          fscanf(constsFile,"\n");
   } while (strcmp(tmp1,"Beads_order")!=0);
   rewind(constsFile);
   do{ // find Colors
    fscanf(constsFile,"%s",tmp1);
      if(strcmp(tmp1,"First_Color")==0){ 
          fscanf(constsFile," = %s",tmp2);
          FPC = getColor(tmp2[0]);
      }
      else if(strcmp(tmp1,"Second_Color")==0){
          fscanf(constsFile," = %s",tmp2);
          SPC = getColor(tmp2[0]);
      }
      else if(strcmp(tmp1,"Third_Color")==0){
          fscanf(constsFile," = %s",tmp2);
          TPC = getColor(tmp2[0]);
      }
      else if(strcmp(tmp1,"Forth_Color")==0){
          fscanf(constsFile," = %s",tmp2);
          FoPC = getColor(tmp2[0]);
      }
      else
          fscanf(constsFile,"\n");
  } while (!feof(constsFile));
  fclose(constsFile);
}


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