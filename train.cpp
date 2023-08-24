#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>



// #define NUMBERCLIENT 32

static int CountClients = 0;



class Car_Client
{
private:
    std::string brand;
    std::string model;

public:

    Car_Client() = default;
    
    Car_Client(const std::string &brand, const std::string &model) : brand(brand), model(model) {}

    virtual void displayInfo() const {
        std::cout << "Brand: " << brand << std::endl;
        std::cout << "Model: " << model << std::endl;
    }


};



class Client
{
private:
    std::string last_name;
    std::string first_name;
    Car_Client machine;
    int identifier;

public:

    Client() = default;


    Client( const std::string &last_name, const std::string &first_name, 
            const std::string &car_brand, const std::string &car_model)
        : last_name(last_name), first_name(first_name), machine(car_brand, car_model) {}

    virtual void displayInfo() const {
        std::cout << "Client name: " << last_name << " " << first_name << std::endl;
        std::cout << "identifier: " << identifier << std::endl;
        machine.displayInfo();
    }

    void setIdentifier(int num){
        identifier = num;
    }

};



class ClientService
{
private:
    int size = 32;
    int *arrayIdentifier;
    int identifier;
    std::vector<Client> myVector;
    Client client;
public:

    ClientService() {
        arrayIdentifier = new int[size];
    }



    void new_client( const std::string &last_name, const std::string &first_name, 
                const std::string &car_brand, const std::string &car_model)
    {   
        client = Client(last_name, first_name, car_brand, car_model);
        
        addIdentifier(identifier);
        client.setIdentifier(identifier);
        myVector.push_back(client);
        CountClients++;

    }


    ~ClientService(){
        delete[] arrayIdentifier;
    }
    
    void showClient(){
        for (std::vector<Client>::size_type i = 0; i < myVector.size(); i++){
            myVector[i].displayInfo();
        }
    }



    void showIdef(){
        for (int i = 0; i < 5; i++){
            std::cout << arrayIdentifier[i] << std::endl;
        }
    }
    

private:

     void addIdentifier(int number){
        
        if (CountClients >= size){

            int new_size = size;

            new_size *= 2;
            int *new_arrayIdentifier = new int[new_size];

            for (int i = 0; i < CountClients; i++){
                new_arrayIdentifier[i] = arrayIdentifier[i];
            }

            delete [] arrayIdentifier;

            arrayIdentifier = new_arrayIdentifier;
            size = new_size;
        }

        
        // if (!checkIdentifiernumber(arrayIdentifier))
        //     arrayIdentifier[CountClients] = number;
        // else 
        //     std::cout << "Yes" << std::endl;

        do
        {
            identifier = rand() % 100;
            arrayIdentifier[CountClients] = identifier;           
        } while (checkIdentifierNumber(identifier));
         

        
    }

    bool checkIdentifierNumber(int number){
        for (int i = 0; i < CountClients; i++){
            if (arrayIdentifier[i] == number){
                return true;
            }

        }

        return false;
    }
};





int main()
{

    ClientService client;

    client.new_client("Taras", "Shybistyi", "Skoda", "Octavia");
    client.new_client("Mykhailo ", "Mykytiuk", "Opel", "Vectra");
    client.showClient();
    client.showIdef();


}