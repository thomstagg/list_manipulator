#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

//Clears console screen
void clear()
{
    std::cout << "\x1B[2J\x1B[H";
}

//Checks for valid input of an integer
int valid_integer()
{
    int input{};
    std::cin >> input;
    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nInvalid entry, enter a NUMBER: ";
        std::cin >> input;
    }
    return input;
}

//checks for valid response
std::string valid_menu_choice() {
    std::string const valid_options("pPaAmMsSlLcCqQ");
    std::string input{};

    std::cin >> input;
    while (input.size() != 1 || valid_options.find(input) == std::string::npos)
    {
        std::cin.clear();
        std::cout << "\nInput invalid, please enter a valid character : ";
        std::cin >> input;
    }
    return input;
}

//checks for valid response
std::string valid_continue() {
    std::string const valid_options("yYnN");
    std::string input{};

    std::cin >> input;
    while (input.size() != 1 || valid_options.find(input) == std::string::npos)
    {
        std::cin.clear();
        std::cout << "\nInput invalid, please enter a valid character : ";
        std::cin >> input;
    }
    return input;
}

//adds ordinal suffix e.g. rd or th to numbers
const char* ordinal_suffix(const int n)
{
    static constexpr char suffixes[][3] = { "th", "st", "nd", "rd" };
    auto ord = n % 100;
    if (ord / 10 == 1) { ord = 0; }
    ord = ord % 10;
    if (ord > 3) { ord = 0; }
    return suffixes[ord];
}

//Prints menu to console
void print_menu() {
    std::cout << "\nPlease choose from the following options:" << std::endl;
    std::cout << "\n--------------------------------------------" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "||                                        ||" << std::endl;
    std::cout << "||    A - Add numbers to list             ||" << std::endl;
    std::cout << "||    P - Print full list                 ||" << std::endl;
    std::cout << "||    M - Display average number          ||" << std::endl;
    std::cout << "||    S - Display the smallest number     ||" << std::endl;
    std::cout << "||    L - Display the largest number      ||" << std::endl;
    std::cout << "||    C - Clear list                      ||" << std::endl;
    std::cout << "||    Q - Quit program                    ||" << std::endl;
    std::cout << "||                                        ||" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "\nEnter your choice : ";
}

bool cont()
{
    std::string user_selection{};
    bool to_quit{true};
    std::cout << "\nPress 'Y' to continue : ";
    user_selection = valid_continue();
    if (user_selection == "y" || user_selection == "Y") {
        to_quit = true;
    }
    else if (user_selection == "q" || user_selection == "Q") {
        to_quit = false;
    }
    return to_quit;
}


void process_user_inputs()
{
    std::string user_selection{};
    bool running{ true };
    std::vector<int> user_numbers_v;

    while (running) {
        if (user_numbers_v.size() == 1)
            std::cout << "\nYou have " << user_numbers_v.size() << " number in your list" << std::endl;
        else
            std::cout << "\nYou have " << user_numbers_v.size() << " numbers in your list" << std::endl;
        print_menu();
        user_selection = valid_menu_choice();
        clear();
        while (running) {

            //Allows the user to add numbers to the vector user_numbers_v
            if (user_selection == "a" || user_selection == "A") {
                if (user_numbers_v.size() < 10) {
                    std::cout << "\nHow many numbers would you like to add? : ";
                    int const total_user_numbers = valid_integer();
                    if (total_user_numbers <= 10) {
                        for (int i{ 1 }; i <= total_user_numbers; ++i) {
                            std::cout << "\nEnter your " << i << ordinal_suffix(i) << " number to add: ";
                            int user_numbers_item = valid_integer();
                            user_numbers_v.push_back(user_numbers_item);
                        }
                        std::cout << "\n---------------------------------------" << std::endl;
                        std::cout << "||    Numbers added successfully!    ||" << std::endl;
                        std::cout << "---------------------------------------" << std::endl;
                        break;
                    }
                    else
                    {
                        std::cout << "\nThe number you have entered exceeds the maximum list size! Try again." << std::endl;
                    }
                }
                else
                {
                    std::cout << "\n---------------------------------------" << std::endl;
                    std::cout << "||           *WARNING*               ||" << std::endl;
                    std::cout << "||        List is too big!           ||" << std::endl;
                    std::cout << "||    add numbers unsuccessful.      ||" << std::endl;
                    std::cout << "---------------------------------------" << std::endl;
                    break;
                }
            }

            //Prints each of the numbers the user entered into the console originally
        	if (user_selection == "p" || user_selection == "P") {
                std::cout << "\nThe numbers you have stored in the list are : " << std::endl;
                if (!user_numbers_v.empty()) {
                    std::cout << "\n[";
                    for (int unsigned long long i{ 0 }; i < user_numbers_v.size(); i++) {
                        std::cout << " " << user_numbers_v[i];
                    }
                    std::cout << " ]" << std::endl;
                }
                else {
                    std::cout << "\nYour list is empty, there's nothing to print." << std::endl;
                }
                running = cont();
                if (running == true)
                {
                    clear();
                    break;
                }
            }

            //Prints out the average of the numbers in the list
            if (user_selection == "m" || user_selection == "M") {

                if (!user_numbers_v.empty()) {
                    int unsigned long long total_numbers{};
                    for (int unsigned long long i{ 0 }; i < user_numbers_v.size(); i++) {
                        total_numbers = total_numbers + user_numbers_v[i];
                    }
                    int const unsigned long long avg = total_numbers / user_numbers_v.size();
                    std::cout << "The average of your numbers is : " << avg << std::endl;
                }
                else {
                    std::cout << "\nYour list is empty, there's nothing to print." << std::endl;
                }
                running = cont();
                if (running == true)
                {
                    clear();
                    break;
                }
            }

            //prints smallest number in the list
            if (user_selection == "s" || user_selection == "S") {
                if (!user_numbers_v.empty()) {
                    std::cout << "\nThe smallest number in your list is: ";
                    std::cout << *std::min_element(user_numbers_v.begin(), user_numbers_v.end()) << std::endl;
                }
                else {
                    std::cout << "\nYour list is empty, there's nothing to print." << std::endl;
                }
                running = cont();
                if (running == true)
                {
                    clear();
                    break;
                }
            }

            //prints largest number in the list
            if (user_selection == "l" || user_selection == "L") {
                if (!user_numbers_v.empty()) {
                    std::cout << "\nThe largest number in your list is: ";
                    std::cout << *std::max_element(user_numbers_v.begin(), user_numbers_v.end()) << std::endl;
                }
                else {
                    std::cout << "\nYour list is empty, there's nothing to print." << std::endl;
                }
                running = cont();
                if (running == true)
                {
                    clear();
                    break;
                }
            }

            //Clears the list of all numbers unless the user says no
            if (user_selection == "c" || user_selection == "C") {
                std::cout << "\nAre you sure you would like to clear the list?" << std::endl;
                std::cout << "\nIf yes press 'Y' or press 'N' to return to the menu : ";
                user_selection = valid_continue();
                clear();
                if (user_selection == "y" || user_selection == "Y") {
                    user_numbers_v.clear();
                    std::cout << "\n---------------------------------------" << std::endl;
                    std::cout << "||     List cleared successfully!    ||" << std::endl;
                    std::cout << "---------------------------------------" << std::endl;
                    break;
                }
                else if (user_selection == "n" || user_selection == "N") {
                    break;
                }
            }

            //Quits the program by breaking the loop
            if (user_selection == "q" || user_selection == "Q") {
                running = false;
            }
        }
    }
}

int main() {
    std::cout << "\nWelcome to the LIST MANIPULATOR!" << std::endl;
    process_user_inputs();
    std::cout << "\nGoodbye!" << std::endl;
    return 0;
}