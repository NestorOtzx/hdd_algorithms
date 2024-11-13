#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

void scan_algo_asc(vector<int> queries, int init);
void scan_algo_desc(vector<int> queries, int init);

void scan_algo_desc(vector<int> queries, int init)
{
    int ans = 0; 
    bool * checked = new bool[queries.size()]();

    sort(queries.begin(), queries.end());
    
    //encontrar el inicial
    int i = queries.size()-1; 
    bool started = false;
    while (i>=0 && !started)
    {
        if (queries[i] <= init){
            started = true;
        }
        i-=1;
    }

    //cout<<"Ini: "<<i+1<<endl;
    
    //sumar el costo de moverse al primero
    int prev = i+1;
    int prevValue = queries[prev];
    ans +=init-prevValue;
    checked[prev] = true;
    
	//baja
	for (prev = i; prev > 0; prev--)
	{
	    checked[prev] = true;
	    ans+= prevValue - queries[prev-1];
	    prevValue = queries[prev-1];
	}
	
	//volver a cero
	ans+=queries[0];
	prevValue = 0;
	
	//sube
	for (prev = i; prev < queries.size(); prev++)
	{
	    if (!checked[prev])
	    {
	        checked[prev] = true;
	        ans+= queries[prev]-prevValue;
	        prevValue = queries[prev];
	    }
	}

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
            
            ss >> val;
            int direc = std::stoi(val);
            
            vector<int> queries;
            while (ss>>val)
            {
                queries.push_back(stoi(val));    
            }
            
            if (direc == 0){
            	scan_algo_desc(queries, init);
        	}
        	
        	if (direc == 1){
        		scan_algo_asc(queries, init);
			}
        }

        file.close();
    }
    
    else { 
        cerr << "ERROR OPENING PROGRAM FILE" << endl; 
    } 
    return 0;
}


void scan_algo_asc(vector<int> queries, int init)
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
    
    //baja
    for (prev = queries.size()-1; prev > 0; prev--)
    {
        if (!checked[prev])
        {
            checked[prev] = true;
            ans+= prevValue - queries[prev-1];
            prevValue = queries[prev-1];
        }
    }

    //volver a cero
    ans+=queries[0];
    
    cout<<"Inicia: "<<init<<endl;
    cout<<"Resultado: "<<ans<<endl;
}