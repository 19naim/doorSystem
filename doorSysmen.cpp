#include <iostream>
#include <list>
#include <string>
#include <thread>

class AccessCard {
private:
    std::string cardID;
    std::string cardAccess;
    std::string dateOfReg;
public:
    AccessCard(const std::string& id, const std::string& cdAcc, const std::string& dtOfReg) : cardID(id) , cardAccess(cdAcc), dateOfReg(dtOfReg) {}
    
    std::string getCardID() const {
        return cardID;
    }

    std::string getCardAccess() const {
        return cardAccess;
    }

    void setCardAccess(std::string& crdAccess) {
        cardAccess = crdAccess;
    }
    std::string getDateOfReg() const {
        return dateOfReg;;
    }

};
//display all the stored card
void displayAllCards(const std::list<AccessCard>& cards) {
    std::cout << "All Access Cards:" << std::endl;
    for (const auto& card : cards) {
        std::cout << "- Card ID: " << card.getCardID() << " " << card.getCardAccess() << " " << card.getDateOfReg() << std::endl;
    }
}

//display only the specific card
void displaySpecificCard(const std::list<AccessCard>& cards){
    std::string cardNumber;
    std::cout << "Please enter the card number: " << std::endl;
    std::cin >> cardNumber;
    for (const auto& card : cards){
        if(card.getCardID() == cardNumber){
           std::cout << "Card: " << card.getCardID() << " " << card.getCardAccess() << " " << card.getDateOfReg() << std::endl; 
        }
    }
    

}

//add or remove access

void addOrRemoveAccess(std::list<AccessCard>& cards) {
    std::string cardNumber;
    std::string input;
    std::string cStatus1 = "Active";
    std::string cStatus2 = "Inactive";
    std::cout << "Please enter the card number: " << std::endl;
    std::cin >> cardNumber;

    for (auto& card : cards) {
        if (card.getCardID() == cardNumber) {
            std::cout << "Enter 1 to give access\nEnter 0 to remove access\nEnter your choice:" << std::endl;
            std::cin >> input;
            if (input == "1") {
                card.setCardAccess(cStatus1);
            } else if (input == "0") {
                card.setCardAccess(cStatus2);
            } else {
                std::cout << "Invalid input. Please enter '1' or '0'." << std::endl;
            }
        }
    }
}
//open remote door
void openRemoteDoor(const std::list<AccessCard>& cards, std::string drStatus){
    std::string cardNumber;
    std::cout << "Enter your card number: " << std::endl;
    std::cin >> cardNumber;

    for (const auto& card : cards){
        if(card.getCardID() == cardNumber){
            if(card.getCardAccess() == "Active"){
                drStatus = "Green";
                std::cout << "Door is Green now (for 15 second)" <<std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(5));
                drStatus = "Orange";
                std::cout << "Door is ORange now " <<std::endl;

            }else{
                std:: cout << "Sorry the card doesn't have access" << std::endl;
            }
        }else{
            std::cout << "Wrong card !!!!" << std::endl;
        }
    }
}


bool findCard(const std::list<AccessCard>& cards, const std::string& id) {
    for (const auto& card : cards) {
        if (card.getCardID() == id) {
            std::cout << "Card ID: " << id << " found." << std::endl;
            return true;
        }
    }
    std::cout << "Card ID: " << id << " not found." << std::endl;
    return false;
}

int main() {
    std::list<AccessCard> accessCardList;
    std::string doorStatus = "Orange";
   
    while (true) {
        std::cout << "\n1. Register new Card";
        std::cout << "\n2. Display All Access Cards";
        std::cout << "\n3. Find Access Card";
        std::cout << "\n4. Display one specific card";
        std::cout << "\n5. Add or remove access of the card";
        std::cout << "\n6. Open remote door";
        std::cout << "\n7. Exit";
        std::cout << "\nEnter your choice: " << std::endl;
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string cardID;
                std::string cardAccess = "Inactive";
                std::string regDate = __DATE__;
                
                std::cout << "Enter Card ID: ";
                std::cin >> cardID;
                accessCardList.push_back(AccessCard(cardID, cardAccess, regDate));
                std::cout << "Access Card added successfully." << std::endl;
                break;
            }
            case 2:
                displayAllCards(accessCardList);
                break;

            case 3: {
                std::string searchID;
                std::cout << "Enter Card ID to search: ";
                std::cin >> searchID;
                findCard(accessCardList, searchID);
                break;
            }

            case 4:{
                displaySpecificCard(accessCardList);
                break;
            }
            case 5:{
                addOrRemoveAccess(accessCardList);
                break;
            }
            case 6:{
                openRemoteDoor(accessCardList, doorStatus);
                break;
            }    
            case 7:
                std::cout << "Exiting program.\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please enter a valid option.\n";
        }
    }

    return 0;
}



