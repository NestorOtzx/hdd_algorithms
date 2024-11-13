#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

void cscan_algo_asc(vector<int> queries, int init)
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

void cscan_algo_desc(vector<int> queries, int init) { 
	int ans = 0; 
	sort(queries.begin(), queries.end(), greater<int>());
	
	// Encontrar el inicial 
	int i = 0; 
	while (i < queries.size() && queries[i] > init) { 
		i++; 
	}
	
	// Baja 
	int prevValue = init;
	for (int j = i; j < queries.size(); j++) { 
		ans += prevValue - queries[j]; 
		prevValue = queries[j]; 
	}
	
	// Regresar al punto superior 
	ans += queries[0] - prevValue; 
	prevValue = queries[0];
	
	// Continuar hacia abajo
	for (int j = 0; j < i; j++) { 
		ans += prevValue - queries[j]; 
		prevValue = queries[j];
	}
	
	cout << "Inicia: " << init << endl; 
	cout << "Resultado: " << ans <<endl;
}

int main() {
    std::ifstream file("input.txt");
    std::string line; 

    if (file.is_open()) { 
        while(getline(file, line)) {
            std::stringstream ss(line);
            std::string val;
            
            ss >> val;
            int init = std::stoi(val);
            
            ss >> val;
            int direc = std::stoi(val);
            
            std::vector<int> queries;
            while (ss >> val) {
                queries.push_back(std::stoi(val));    
            }
            
            if (direc == 0){
            	cscan_algo_desc(queries, init);
            }
            
            if (direc == 1){
            	cscan_algo_asc(queries, init);
            }
        }
        file.close();
        
    } else { 
        std::cerr << "ERROR OPENING PROGRAM FILE" << std::endl; 
    }
    
    return 0;
}