#include "terminal_table.h"
#include <string>

using namespace terminal_table;

int main() {
    std::string title = "student grade table";
    std::string title_color = BLUE;

    std::vector<std::string> headers = {"Name", "Score", "Grade"};
    std::vector<std::string> header_colors = {RED, GREEN, BLUE};

    std::vector<std::vector<std::string>> rows = {
        {"Alice", "90", "A"},
        {"Bob", "82", "B"},
        {"Charlie", "77", "C"},
        {"David", "65", "D"}
    };
    std::vector<std::vector<std::string>> row_colors = {
        {"", "", ""}, // 第一行不加色
        {CYAN, "", YELLOW}, // 第二行：第一列青色，第三列黄色
        {YELLOW, YELLOW, YELLOW} // 第三行全部黄色
        // 第四行不写，就是默认
    };

    print_table_by_row(title, headers, rows, title_color, header_colors, row_colors);
    return 0;
}
