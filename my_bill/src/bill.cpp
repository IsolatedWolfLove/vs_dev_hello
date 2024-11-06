#include <filesystem>
#include <fstream>
#include <functional>
#include <ios>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

// namespace fs = std::filesystem;
int ID = 2;
// class bill {
// public:
//     bill() { }
//     bill(std::string _user, std::string _code)
//     {
//         std::fstream txt;
//         txt.open(userfilename, std::ios::in);
//         if (!txt.is_open()) {
//             std::cout << "openfail" << '\n';
//         }
//         std::string temp;
//         while (std::getline(txt, temp)) {
//             std::string substr_name = temp.substr(0, temp.find(" "));
//             std::string substr_code = temp.substr(temp.find(" ") + 1, temp.size());
//             users[ID] = std::make_pair(substr_name, substr_code);
//             ID++;
//         }
//         txt.close();
//         for (int i = 0; i < ID; i++) {
//             if (_user == users[i].first) {
//                 if (_code == users[i].second) {
//                     this->filename = usersspace + "\\" + users[i].first + ".txt";
//                 } else {
//                     std::cout << "your code is wrong,please try again\n";
//                 }
//             }
//             if (i == ID - 1) {
//                 std::cout << "can not find a account called" << _user << "\nplease check your name or you can create a new one\n";
//             }
//         }
//     }
//     ~bill()
//     {
//         save_to_file();
//     }
//     void write_bill(std::string _date, std::string _meal, double _dollar)
//     {
//         date.push_back(_date);
//         meal.push_back(_meal);
//         dollar.push_back(_dollar);
//     }
//     void print_current_bills()
//     {
//         for (int i = 0; i < date.size(); i++) {
//             std::cout << date[i] << " " << meal[i] << " " << dollar[i] << std::endl;
//         }
//     }
//     void save_to_file()
//     {
//         std::fstream txt;
//         txt.open(filename, std::ios::app);
//         if (!txt.is_open()) {
//             std::cout << "openfail" << '\n';
//         }
//         for (int i = 0; i < date.size(); i++) {
//             txt << date[i] << " " << meal[i] << " " << dollar[i] << " " << "\n";
//         }
//         txt.close();
//     }
//     void print_all_bills()
//     {
//         std::fstream txt;
//         txt.open(filename, std::ios::in);
//         if (!txt.is_open()) {
//             std::cout << "openfail" << '\n';
//         }
//         std::string temp;
//         while (std::getline(txt, temp)) {
//             std::cout << temp;
//         }
//     }
//     void regester(std::string _usersname, std::string _code)
//     {

//         users[ID] = std::make_pair(_usersname, _code);
//         ID++;
//         std::cout << "congratulations you have create a account ,your ID is" << ID << "\n";
//         std::string filePath = usersspace;
//         std::string fileName = _usersname + ".txt";
//         fs::path fullPath = fs::path(filePath) / fileName;
//         std::ofstream file(fullPath);
//         if (!file) {
//             std::cerr << "无法创建文件: " << fullPath << std::endl;
//         }
//         std::fstream txt;
//         txt.open(userfilename, std::ios::app);
//         if (!txt.is_open()) {
//             std::cout << "openfail" << '\n';
//         }
//         txt << _usersname << " " << _code << std::endl;
//         txt.close();
//     }

// private:
//     std::pair<std::string, std::string> user;
//     std::vector<std::pair<std::string, std::string>> users;
//     std::string filename; // 代之用户文件
//     std::string userfilename = "C:\\Users\\15694\\Desktop\\my_bill\\usersspace\\general.txt"; // 储存用户信息的文件
//     std::string usersspace = "C:\\Users\\15694\\Desktop\\my_bill\\usersspace"; // 存储所有用户文件的地方
//     std::vector<double> dollar;
//     std::vector<std::string> date;
//     std::vector<std::string> meal;
// };
// bool common_action(bill& bill_obj)
// {
//     std::cout << "please input your choose:\n1.write a bill\n2.print current bills\n3.save to file\n4.print all bills\n5.exit\n";
//     int choose;
//     std::cin >> choose;
//     switch (choose) {
//     case 1: {
//         std::cout << "please input the date,meal and dollar\n";
//         std::string date;
//         std::string meal;
//         double dollar;
//         std::cin >> date >> meal >> dollar;
//         bill_obj.write_bill(date, meal, dollar);
//         break;
//     }
//     case 2:
//         bill_obj.print_current_bills();
//         break;
//     case 3:
//         bill_obj.save_to_file();
//         break;
//     case 4:
//         bill_obj.print_all_bills();
//         break;
//     case 5:
//         return false;
//         break;
//     default:
//         std::cout << "wrong choose\n";
//         break;
//     }
// }
int main()
{
    std::cout << "welcome to ccy's bill,are you a new man of the app ?\n if so ,please input 'yes'and new a account\nif not please input'no'\n";
    // std::string choose;
    // std::cin >> choose;
    // if (choose == "yes") {
    //     bill bill_temp_obj;
    //     std::cout << "please input your name and code\n";
    //     std::string name;
    //     std::string code;
    //     std::cin >> name >> code;
    //     bill_temp_obj.regester(name, code);
    //     bill bill_obj(name, code);
    //     while (common_action(bill_obj) != false) { }
    // } else {
    //     std::cout << "please input your name and code\n";
    //     std::string name;
    //     std::string code;
    //     bill bill_obj(name, code);
    //     while (common_action(bill_obj) != false) { }
    // }
    // return 0;

    {
        std::pair<std::string, std::string> user;
        std::vector<std::pair<std::string, std::string>> users;
        std::string userfilename = "C:\\Users\\15694\\Desktop\\my_bill\\usersspace\\general.txt"; // 储存用户信息的文件
        std::string usersspace = "C:\\Users\\15694\\Desktop\\my_bill\\usersspace"; // 存储所有用户文件的地方
        std::fstream txt;
        txt.open(userfilename, std::ios::in);
        if (!txt.is_open()) {
            std::cout << "openfail" << '\n';
        }
        std::string temp;
for (int i=0;i<ID;i++){
    std::getline(txt,temp);
            std::string substr_name = temp.substr(0, temp.find(" "));
            std::string substr_code = temp.substr(temp.find(" ") + 1, temp.size());
            users[ID] = std::make_pair(substr_name, substr_code);
            ID++;
        }
        for (int i=0;i<ID;i++){
            std::cout<<users[ID].first<<users[ID].second<<"\n";   
        }

        // txt.close();
        // for (int i = 0; i < ID; i++) {
        //     if (_user == users[i].first) {
        //         if (_code == users[i].second) {
        //             this->filename = usersspace + "\\" + users[i].first + ".txt";
        //         } else {
        //             std::cout << "your code is wrong,please try again\n";
        //         }
        //     }
        //     if (i == ID - 1) {
        //         std::cout << "can not find a account called" << _user << "\nplease check your name or you can create a new one\n";
        //     }
        // }
    }
    return 0;
}
/*void save_all_users()
    {
        std::fstream txt;
        if (!txt.is_open()) {
            std::cout << "openfail" << '\n';
        } else {
            txt.open(userfilename, std::ios::app);
        }
        std::vector<std::string> temp_username;
        std::vector<std::string> temp_code;
        for (int i = 0; i < users.size(); i++) {
            temp_username.push_back(users[i].first);
            temp_code.push_back(users[ID].second);
        }
        for (int i = 0; i < users.size(); i++) {
            txt << temp_username[ID] << " " << temp_code[ID] << "\n";
        }
    }*/