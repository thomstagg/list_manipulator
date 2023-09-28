#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

//Stores user numbers
std::vector<int> user_numbers_v;

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
std::string valid_menu_choice()
{
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
std::string valid_continue()
{
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
    if (ord / 10 == 1)
    {
	    ord = 0;
    }
    ord = ord % 10;
    if (ord > 3)
    {
    	ord = 0;
    }
    return suffixes[ord];
}

//Prints menu to console
void print_menu()
{
	std::cout << "\nYou have " << user_numbers_v.size() << " out of max of 10 numbers in your list" << std::endl;
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

//Allows the user to add numbers to the vector user_numbers_v
void add_numbers()
{
    if (user_numbers_v.size() >= 10)
    {
        std::cout << "\n---------------------------------------" << std::endl;
        std::cout << "||           *WARNING*               ||" << std::endl;
        std::cout << "||       List size reached!          ||" << std::endl;
        std::cout << "||    add numbers unsuccessful.      ||" << std::endl;
        std::cout << "---------------------------------------" << std::endl;
    }
    if (user_numbers_v.size() < 10)
    {
        bool running{ true };
        while (running) {
            std::cout << "\nHow many numbers would you like to add? : ";
            int const total_user_numbers = valid_integer();
            if (total_user_numbers <= 10 && total_user_numbers + user_numbers_v.size() <= 10)
            {
                for (int i{ 1 }; i <= total_user_numbers; ++i)
                {
                    std::cout << "\nEnter your " << i << ordinal_suffix(i) << " number to add: ";
                    int user_numbers_item = valid_integer();
                    user_numbers_v.push_back(user_numbers_item);
                }
                std::cout << "\n---------------------------------------" << std::endl;
                std::cout << "||    Numbers added successfully!    ||" << std::endl;
                std::cout << "---------------------------------------" << std::endl;
				running = false;
            }
            else if (total_user_numbers <= 10 && total_user_numbers + user_numbers_v.size() > 10)
            {
                std::cout << "\nThe number you have entered exceeds the maximum list size! Try again." << std::endl;
            }
        }
    }
}

//Prints each of the numbers the user entered into the console originally
void print_numbers()
{
    std::cout << "\nThe numbers you have stored in the list are : " << std::endl;
    if (!user_numbers_v.empty())
    {
        std::cout << "\n[";
        for (int unsigned long long i{ 0 }; i < user_numbers_v.size(); i++)
        {
            std::cout << " " << user_numbers_v[i];
        }
        std::cout << " ]" << std::endl;
    }
    else
    {
        std::cout << "\nYour list is empty, there's nothing to print." << std::endl;
    }
}

//Prints out the average of the numbers in the list
void average_number()
{
    if (!user_numbers_v.empty())
    {
        int unsigned long long total_numbers{};
        for (int unsigned long long i{ 0 }; i < user_numbers_v.size(); i++)
        {
            total_numbers = total_numbers + user_numbers_v[i];
        }
        int const unsigned long long avg = total_numbers / user_numbers_v.size();
        std::cout << "The average of your numbers is : " << avg << std::endl;
    }
    else
    {
        std::cout << "\nYour list is empty, there's nothing to print." << std::endl;
    }
}

//prints smallest number in the list
void smallest_number()
{
    if (!user_numbers_v.empty())
    {
        std::cout << "\nThe smallest number in your list is: ";
        std::cout << *std::min_element(user_numbers_v.begin(), user_numbers_v.end()) << std::endl;
    }
    else
    {
        std::cout << "\nYour list is empty, there's nothing to print." << std::endl;
    }
}

//prints largest number in the list
void largest_number()
{
    if (!user_numbers_v.empty())
    {
        std::cout << "\nThe largest number in your list is: ";
        std::cout << *std::max_element(user_numbers_v.begin(), user_numbers_v.end()) << std::endl;
    }
    else
    {
        std::cout << "\nYour list is empty, there's nothing to print." << std::endl;
    }
}

//Clears the list of all numbers unless the user says no
void clear_numbers()
{
    std::string user_selection{};
    std::cout << "\nAre you sure you would like to clear the list?" << std::endl;
    std::cout << "\nIf yes press 'Y' or press 'N' to return to the menu : ";
    user_selection = valid_continue();
    clear();
    if (user_selection == "y" || user_selection == "Y")
    {
        user_numbers_v.clear();
        std::cout << "\n---------------------------------------" << std::endl;
        std::cout << "||     List cleared successfully!    ||" << std::endl;
        std::cout << "---------------------------------------" << std::endl;
    }
}

//Processes all user inputs and calls the appropriate function
void process_user_inputs()
{
    std::string user_selection{};
    bool running{ true };
	while (running) 
    {
        print_menu();
        user_selection = valid_menu_choice();
        clear();
        while (running) 
        {
            if (user_selection == "a" || user_selection == "A") 
            {
                add_numbers();
                break;
            }
        	if (user_selection == "p" || user_selection == "P") 
            {
                print_numbers();
                break;
            }
            if (user_selection == "m" || user_selection == "M") 
            {
                average_number();
                break;
            }
            if (user_selection == "s" || user_selection == "S") 
            {
                smallest_number();
                break;
            }
            if (user_selection == "l" || user_selection == "L") 
            {
                largest_number();
                break;
            }
            if (user_selection == "c" || user_selection == "C") 
            {
                clear_numbers();
                break;
            }
            if (user_selection == "q" || user_selection == "Q") 
            {
                running = false;
            }
        }
    }
}

int main()
{
    std::cout << "\nWelcome to the LIST MANIPULATOR!" << std::endl;
    process_user_inputs();
    std::cout << "\nGoodbye!" << std::endl;
    return 0;
}