#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

void scan_algo(vector<int> queries, int init)
{
    int ans = 0; 
    bool * checked = new bool[queries.size()]();


    sort(queries.begin(), queries.end());
    //encontrar el inicial
    int i = 0; bool started = false;
    while (i<queries.size() && !started)
    {
        if (queries[i] >= init){
            started = true;
        }
        i+=1;
    }

    //sumar el costo de moverse al primero
    int prev = i-1;
    int prevValue = queries[prev];
    ans +=prevValue-init;
    checked[prev] = true;
    //sube
    for (prev = i; prev < queries.size(); prev++)
    {
        checked[prev] = true;
        
        ans+= queries[prev]-prevValue;
        prevValue = queries[prev];
    }
    
    //baja solo si tiene que bajar
    prevValue = 0;
    if (!checked[0]){
        ans+=queries[queries.size()-1]; //suma la distancia desde arriba a abajo
    }
    //sube
    for (prev = 0; prev < queries.size(); prev++)
    {
        if (!checked[prev])
        {
            checked[prev] = true;
            
            ans+= queries[prev]-prevValue;
            prevValue = queries[prev];
        }
    }
    
    delete checked;
    cout<<"Inicia: "<<init<<endl;
    cout<<"Resultado: "<<ans<<endl;
    
}


int main()
{
    std::ifstream file("input.txt");
    string line; 

    if (file.is_open()) { 
        string line;
       
        while(getline(file, line))
        {
            std::stringstream ss(line);
            string val;
            ss>>val;
            int init = stoi(val);
            
            vector<int> queries;
            while (ss>>val)
            {
                queries.push_back(stoi(val));    
            }
            scan_algo(queries, init);
        }

        file.close();
    } 
    else { 
        cerr << "ERROR OPENING PROGRAM FILE" << endl; 
    } 
    return 0;
}
