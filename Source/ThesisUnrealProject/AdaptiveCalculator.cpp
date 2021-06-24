#include <iostream>
#include <string>

using namespace std;

void Update(float& a, float& b, string S1, string S2);

int main(){
    float Achiever = 50;
    float Killer = 50;
    float Socializer = 50;
    float Explorer = 50;

    Update(Killer, Explorer, "Killer", "Explorer");
    Update(Achiever, Socializer, "Achiever", "Socializer");
    
    Update(Killer, Socializer, "Killer", "Socializer");
    Update(Achiever, Explorer, "Achiever", "Explorer");
    
    Update(Killer, Achiever, "Killer", "Achiever");
    Update(Socializer, Explorer, "Socializer", "Explorer");
    
    Update(Socializer, Explorer, "Socializer", "Explorer");
    Update(Killer, Achiever, "Killer", "Achiever");
    
    Update(Achiever, Explorer, "Achiever", "Explorer");
    Update(Killer, Socializer, "Killer", "Socializer");
    
    Update(Killer, Explorer, "Killer", "Explorer");
    Update(Achiever, Socializer, "Achiever", "Socializer");
    

    cout << " ------------- "<< endl;
    cout << " Achiever: " << Achiever << endl;
    cout << " Killer: " << Killer << endl;
    cout << " Socializer: " << Socializer << endl;
    cout << " Explorer: " << Explorer << endl;

    return 0;
}

void Update(float& a, float& b, string S1, string S2){
    
    cout << " 1 " << S1 << " 2  " << S2 << endl;

    int value;

    cin >> value;

    if(value == 1){
        a += 8;
        b -= 8;
    }else{
        b += 8;
        a -= 8;
    }
}

void Update2(float& a, float& b, string S1, string S2){
    
    cout << " 1 " << S1 << " 2  " << S2 << endl;

    int value;

    cin >> value;

    if(value == 1){
        
        if(a < b){
            a += 12;
            b -= 4;
        }else if (a > b){
            a += 4;
            b -= 12;
        }else{
            a += 8;
            b -= 8;
        }

    }else{
        if(a < b){
            a -= 12;
            b += 4;
        }else if (a > b){
            a -= 4;
            b += 12;
        }else{
            a += 8;
            b -= 8;
        }
    }
}

