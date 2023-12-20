#include <iostream>
#include <string> 

#include "vihicle.h"
  
 #include "AirVihicle.h"
     #include "Broom.h"
     #include "Eagle.h"
     #include "Flycarpet.h"

  #include "Landvihicle.h"
     #include "fastCamel.h"
     #include "Boots.h"
     #include "Camel.h"
     #include "Centaur.h"
     #include "fastCamel.h"
  

#include "Race.h"
  #include "LandRace.h"
  #include "AirRace.h"
  #include "MixRace.h"

using namespace std;

void ShowFinishList(Vihicle** racerArray, int racerCount, double distance) {
    // Пузырьковая сортировка
    for (int i = 0; i < racerCount - 1; ++i) {
        for (int j = 0; j < racerCount - i - 1; ++j) {
            if (racerArray[j]->calculating(distance) > racerArray[j + 1]->calculating(distance)) {
                
                Vihicle* temp = racerArray[j];
                racerArray[j] = racerArray[j + 1];
                racerArray[j + 1] = temp;
            }
        }
    }

    std::cout << "\nFinish LIST: " << std::endl;
    for (int i = 0; i < racerCount; ++i) {
        std::cout << i + 1 << ". " << racerArray[i]->getName() << " - " << racerArray[i]->calculating(distance) << std::endl;
    }
}

void RegisterVihicle(Vihicle**& racerArray, Vihicle* newVihicle, int& capacity, int& racerCount) {
    if (racerCount >= capacity) {
        capacity *= 2; // Увеличиваем вместимость при необходимости
        Vihicle** newArray = new Vihicle * [capacity];
        for (int i = 0; i < racerCount; ++i) {
            
            newArray[i] = racerArray[i];
        }
        delete[] racerArray; // Удаляем старый массив
        racerArray = newArray; // Обновляем указатель
    }
    racerArray[racerCount] = newVihicle; // Добавляем новый Vihicle в массив
    ++racerCount; // Увеличиваем счетчик зарегистрированных Vihicle
}

void ShowRegisteredVehicles(Vihicle** racerArray, int racerCount) {
    cout << "\nRegistrated vehicles : ";
    for (int i = 0; i < racerCount; ++i) {
        cout << i + 1 << ". " << racerArray[i]->getName() << " ; ";
    }
}

bool isVehicleAlreadyRegistered(Vihicle** racersArray, int racerCount, const Vihicle* newVihicle) {
    for (int i = 0; i < racerCount; ++i) {
        if (typeid(*racersArray[i]) == typeid(*newVihicle)) {
            return true;
        }
    }
    return false;
}


int main() {

    double distance;
    int pCMD=0;
    int p_v_c;
    VihicleType choose;
    int capicity = 10;
    int racerCount = 0;

    Vihicle** racersArray = new Vihicle*[capicity];

    
    cout << "Welcome to Rabbits Race !\n1. Race for Land vehicles \n2. Race for Air vehicles \n3. Unlim Race";
    cout << "\nChoose race type: ";
    cin >> p_v_c;
       while (p_v_c !=1 && p_v_c!= 2 && p_v_c!=3) {
        cout << "WRONG CHOOSE ! !\n1. Race for Land vehicles \n2. Race for Air vehicles \n3. Unlim Race";
        cout << "\nChoose race type: ";
        cin >> p_v_c;
        }
    cout << "Enter the distance (has to be positive) : ";
    cin >> distance;
    
    
    AirRace air_race(3); // Создаем объектsы гонки
    LandRace land_race(4);
    MixRace mix_race(7);

    
        cout << "Minimum count of racers is 2!" << endl;
        cout << "1. Register vehicle." << endl;
        cout << "Choose action: ";
        cin >> pCMD;
        while (pCMD != 1) {
            cout << "WRONG CHOOSE !! \n1. Register vehicle." << endl;
            cout << "Choose action: ";
            cin >> pCMD;
        }


        while (pCMD != 0) {
         
        if (pCMD == 1 && p_v_c == 2) {
            cout << "\nChoose a vehicle to register:" << endl;
            cout << "1. Broom" << endl;
            cout << "2. Boots" << endl;
            cout << "3. Eagle" << endl;
            cout << "4. Camel" << endl;
            cout << "5. Centaur" << endl;
            cout << "6. Fly carpet" << endl;
            cout << "7. Fast Camel" << endl;
            cout << "0. End registration" << endl;
          
            cout << "Enter your choice: ";
            int vehicleChoice;
            cin >> vehicleChoice;

            Vihicle* newVihicle = nullptr;
            switch (vehicleChoice) {
            case 1:
                newVihicle = new Broom;
                break;
            case 2:
                newVihicle = new Boots;
                break;
            case 3:
                newVihicle = new Eagle; 
               break;
            case 4:
                newVihicle = new Camel; 
                break;
            case 5:
                newVihicle = new Centaur; 
                break;
            case 6:
                newVihicle = new Flycarpet ;  
                break;
            case 7:
                newVihicle = new fastCamel ; 
                break;
            case 0:
                pCMD = 0;
                break;
            default:
                cout << "Incorrect vehicle number!" << endl;
                continue;
            }
            if (newVihicle->getType() == VihicleType::Air) {
                
                if (isVehicleAlreadyRegistered(racersArray, racerCount, newVihicle)) {
                    cout << "This type of vehicle is already registered." << endl << "Try another one or PRESS 0 " << endl;
                    delete newVihicle; // Удаляем созданный объект
                    continue;
                }
                else {
                    RegisterVihicle(racersArray, newVihicle, capicity, racerCount);
                    air_race.recerRegistr(newVihicle); // Регистрируем ТС в гонке
                    cout << "Vehicle registered successfully!" << endl;
                    ShowRegisteredVehicles(racersArray, racerCount); // Показываем зарегистрированные 


                    cout << "\nFree places in race:" << capicity - racerCount;
                }
            }
            else {
                delete newVihicle;
                cout << "\nThis vehicle cant run this race! " << endl;
                continue; 
            }
            
        }
        else if (pCMD == 1&& p_v_c ==1) {
            int capisity = 4;
            cout << "\nChoose a vehicle to register:" << endl;
           

            cout << "1. Broom" << endl;
            cout << "2. Boots" << endl;
            cout << "3. Eagle" << endl;
            cout << "4. Camel" << endl;
            cout << "5. Centaur" << endl;
            cout << "6. Fly carpet" << endl;
            cout << "7. Fast Camel" << endl;
            cout << "0. End registration" << endl;

            cout << "Enter your choice: ";
            int vehicleChoice;
            cin >> vehicleChoice;

            Vihicle* newVihicle = nullptr;
            
            switch (vehicleChoice) {
            case 1:
                newVihicle = new Broom;
                break;
            case 2:
                newVihicle = new Boots;
                break;
            case 3:
                newVihicle = new Eagle;
                break;
            case 4:
                newVihicle = new Camel;
                break;
            case 5:
                newVihicle = new Centaur;
                break;
            case 6:
                newVihicle = new Flycarpet;
                break;
            case 7:
                newVihicle = new fastCamel;
                break;
            case 0:
                pCMD = 0;
                break;
            default:
                cout << "\n! Incorrect vehicle number !" << endl;
                continue;
            }
            if (newVihicle->getType() == VihicleType::Land) {

                if (isVehicleAlreadyRegistered(racersArray, racerCount, newVihicle)) {
                    cout << "This type of vehicle is already registered." << endl << "Try another one or PRESS 0 " << endl;

                }
                else {
                    RegisterVihicle(racersArray, newVihicle, capicity, racerCount);
                    land_race.recerRegistr(newVihicle); // Регистрируем ТС в гонке
                    cout << "Vehicle registered successfully!" << endl;
                    ShowRegisteredVehicles(racersArray, racerCount); // Показываем зарегистрированные 


                    cout << "\nFree places in race:" << capicity - racerCount;
                    if (capicity == racerCount) {
                        break;
                    }
                }
            }
            else {
                delete newVihicle;
                cout << "\nThis vehicle cant run this race! " << endl;
                continue;
            }
        }
        else if (pCMD == 1 && p_v_c == 3) {

            int capicity = 7;

            cout << "\nChoose a vehicle to register:" << endl;

            cout << "1. Broom" << endl;
            cout << "2. Boots" << endl;
            cout << "3. Eagle" << endl;
            cout << "4. Camel" << endl;
            cout << "5. Centaur" << endl;
            cout << "6. Fly carpet" << endl;
            cout << "7. Fast Camel" << endl;
            cout << "0. End registration" << endl;

            cout << "Enter your choice: ";
            int vehicleChoice;
            cin >> vehicleChoice;


            Vihicle* newVihicle = nullptr;
            switch (vehicleChoice) {
            case 1:
                newVihicle = new Broom;
                break;
            case 2:
                newVihicle = new Boots;
                break;
            case 3:
                newVihicle = new Eagle;
                break;
            case 4:
                newVihicle = new Camel;
                break;
            case 5:
                newVihicle = new Centaur;
                break;
            case 6:
                newVihicle = new Flycarpet;
                break;
            case 7:
                newVihicle = new fastCamel;
                break;
            case 0:
                pCMD = 0;
                break;
            default:
                cout << "Incorrect vehicle number!" << endl;
                continue;
            }
            if (isVehicleAlreadyRegistered(racersArray, racerCount, newVihicle)) {
                cout << "This type of vehicle is already registered." << endl << "Try another one or PRESS 0 " << endl;

            }
            else {
                RegisterVihicle(racersArray, newVihicle, capicity, racerCount);
                mix_race.recerRegistr(newVihicle); // Регистрируем ТС в гонке
                cout << "Vehicle registered successfully!" << endl;
                ShowRegisteredVehicles(racersArray, racerCount); // Показываем зарегистрированные 


                cout << "\nFree places in race:" << capicity - racerCount;
                
            }
        }
            
            
 

    } 
    
    
    ShowFinishList(racersArray, racerCount, distance);
    
    
    
    for (int i = 0; i < racerCount; ++i) {
        delete racersArray[i];
    }
    delete[] racersArray;

    return 0;
}












// 	  while (pCMD != 1 ){
// 		cout<< "Minimum cout of racers = 2 !" << endl; 
// 	    cout<< "1. Registrate trasport ."<< endl; 
// 	    cout<< "Choose action : ";
// 		cin>> pCMD; 
// 		if(pCMD != 1){
// 			cout<<"\nIncorrect action ! Please choose available variants ";
//         }
// 	  }

// //AirType
// 	if (p_v_c == 2 ){
// 		capicity = 2;
// 		Vihicle **racersArray = new Vihicle*[capicity];
		
		

// 		while ( p_v_c !=0 && choose == VihicleType::Air){
// 			for(int i = 0; i<capicity ; i++){
// 		      if (i ==0) {
// 				 cout<<"Air race. Distance: "<< distance<<endl;
// 				 cout<< "1. Magic boots \n2. Broom \n3. Camel \n4.Centaur \n5.Eagle \n6.Fast Camel \n7.Fly Carpet \n0. End registration"<< endl;
// 				 cin>>v_choose;

// 		        racersArray[racerCount] = new AirVehicle(distance);; 
// 	   } else {
// 		cout<< " Registrated vegicles : "; 
// 		    for (int n = 0 ; n<= i ; n++){
// 			    cout<< racersArray[racerCount+1];
// 		    }
// 		    cout<<"Air race. Distance: "<< distance<<endl;
// 			racersArray = new Vihicle* [racerCount + 1]; 
// 		    racersArray[racerCount] = new AirVihicle(distance); 
     
// 	         }	
// 	      }
// 	   }
// 	}

// //LandType
//     else if(choose==VihicleType::Land){

// 	}

// //Unlim
    
	


// }



