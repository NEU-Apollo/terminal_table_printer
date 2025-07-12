#include "terminal_table.h"
#include <string>

using namespace terminal_table;

int main() {
    std::string title = "student grade table";
    std::string title_color = BLUE;

    std::vector<std::string> headers = {"Name", "Score", "Grade"};
    std::vector<std::string> header_colors = {RED, GREEN, BLUE};

    std::vector<std::vector<std::string>> columns = {
        {"Alice", "Bob", "Charlie", "David"},
        {"90", "82", "77", "6554156841"},
        {"A", "B", "C", "D"}
    };
    std::vector<std::vector<std::string>> column_colors = {
        {RED, GREEN, BLUE, BLUE},
        {BLUE, BLUE, BLUE, BLUE},
        {BLUE, BLUE, YELLOW, BLUE},
    };

    print_table_by_column(title, headers, columns, title_color, header_colors, column_colors);
    return 0;
}
