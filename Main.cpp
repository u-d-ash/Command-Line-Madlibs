#include <iostream>
#include <fstream> 
#include <limits> 
#include <vector>

using namespace std;

void gameplay(string gamename){
    ifstream game;
    game.open(gamename + ".txt");
    string game_line;
    string the_game = "";
    while(!game.eof()){
        getline(game, game_line);
        the_game += game_line;
    }
   
    vector< pair<string, int> > questvec;
    for(int i = 0; i < the_game.length(); ){
        if(the_game[i] == '<'){
            string q = "";
            int j = i + 1;
            while(the_game[j] != '>'){
                    q += (the_game[j]);
                    j++;
                    
            }
            questvec.push_back(make_pair(q, i));
            i = j;
        }else{
            i++;
        }
    }
    
    vector<string> ansvec;
    string x;
    for(int i = 0; i < questvec.size(); i++){
        system("clear");
        cout << questvec[i].first << endl;
        ws(cin);
        getline(cin, x);
        ansvec.push_back(x);
    }
    
    int corr = 0;
    for(int i = 0; i < questvec.size(); i++){
        the_game.replace(questvec[i].second - corr, (questvec[i].first).size() + 2 , ansvec[i]);
        corr += (questvec[i].first).length() + 2 - ansvec[i].length();
    }
    system("clear");
    cout << the_game << endl;
    
}

void Play_a_game(){

    system("clear");
    cout << "Select a game from below options." << endl;
    cout << "=================================" << endl;
    ifstream game_file;
    game_file.open("games.txt");
    string game;
    int no_of_games = 0;
    while(!game_file.eof()){
        getline(game_file, game);
        cout << no_of_games + 1 << "." << " " << game << endl;
        no_of_games++;
    }
    game_file.close();
    re:
        int game_no;
        cin >> game_no;
        if(game_no > no_of_games || game_no <= 0 || cin.fail()){
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n' );
            }
            cout << "Please enter valid numerical input" << endl;
            goto re;
        }else{
            game_file.open("games.txt");
            int counter = 0;
            string game;
            while(!game_file.eof()){
                getline(game_file, game);
                counter++;
                if(counter == game_no){
                    game_file.close();
                    break;
                }
            }
            gameplay(game);

        }

}

void Create_a_game(){
    //rules();
    system("clear");
    cout << "Enter your game's name" << endl;
    string s;
    ws(cin);
    getline(cin, s);
    ofstream gamefile(s + ".txt");
    cout << "Enter your game text" << endl;
    string game;
    getline(cin, game, '^' );
    gamefile << game;
    gamefile.close();
    fstream list("games.txt", ios_base::app);
    list << s << '\n';
}

void Welcome_screen(){
    system("clear");
    cout << "Welcome to Madlibs" << endl;
    cout << "==================" << endl;
    cout << "Please Select from the options below.\n" << endl;
    cout << "1. Play a game" << endl;
    cout << "2. Create a game" << endl;
}

void GameOn(){
    Welcome_screen();
    input:
        int x;
        cin >> x; 
        if(x == 1){
            Play_a_game();
        }else if(x == 2){
            Create_a_game();
        }else if((x != 2 || x != 1) || cin.fail()){
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Please enter a valid input (1 or 2)" << endl;
            goto input;
        }
}

int main(){

    go:
        GameOn();
        cout << "\n===========================" << endl;
        cout << "Enter home screen? (Y/N)" << endl;
        char x;
        cin >> x;
        if(toupper(x) == 'Y'){
            goto go;
        }
    
    
}
