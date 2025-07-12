#ifndef TERMINAL_TABLE_H
#define TERMINAL_TABLE_H

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace terminal_table {

const std::string RESET = "\x1b[0m";
const std::string RED = "\x1b[31m";
const std::string GREEN = "\x1b[32m";
const std::string YELLOW = "\x1b[33m";
const std::string BLUE = "\x1b[34m";
const std::string MAGENTA = "\x1b[35m";
const std::string CYAN = "\x1b[36m";
const std::string WHITE = "\x1b[37m";

/**
 * 计算表格各列的最大宽度
 * 
 * @param headers 表头字符串向量
 * @param rows 二维字符串向量，表示表格数据行
 * @return 包含每列最大宽度的size_t向量
 */
inline std::vector<size_t>
calc_col_widths(const std::vector<std::string> &headers,
                const std::vector<std::vector<std::string>> &rows) {
  // 初始化宽度向量，初始值为表头长度
  std::vector<size_t> widths(headers.size(), 0);
  for (size_t i = 0; i < headers.size(); ++i) {
    widths[i] = headers[i].length();
  }
  for (const auto &row : rows) {
    for (size_t i = 0; i < row.size(); ++i) {
      widths[i] = std::max(widths[i], row[i].length());
    }
  }
  return widths;
}

/**
 * 打印单行表格数据
 * 
 * @param row 字符串向量，表示一行数据
 * @param widths 每列宽度的size_t向量
 * @param colors 颜色代码字符串向量（可选，默认为空）
 */
inline void print_row(const std::vector<std::string> &row,
                      const std::vector<size_t> &widths,
                      const std::vector<std::string> &colors = {}) {
  // 打印行数据，应用指定的颜色和对齐方式
  std::cout << "|";
  for (size_t i = 0; i < row.size(); ++i) {
    // 判断是否有对应颜色
    if (!colors.empty() && i < colors.size() && !colors[i].empty()) {
      std::cout << " " << colors[i] << std::left << std::setw(widths[i])
                << row[i] << RESET << " |";
    } else {
      std::cout << " " << std::left << std::setw(widths[i]) << row[i] << " |";
    }
  }
  std::cout << std::endl;
}


/**
 * 打印带边框的标题
 * 
 * @param title 标题文本
 * @param title_length 标题区域总长度
 * @param color 颜色代码（可选，默认为空）
 */
inline void print_title(const std::string &title, size_t title_length,
                        const std::string &color = "") {
  // 构建顶部边框和标题行
  // 这里 -2（两边竖线）再 -2（两边空格）
  std::cout << "+" << std::string(title_length - 2, '-') << "+" << std::endl;
  std::cout << "|";
  if (!color.empty()) {
    std::cout << color;
  }
  std::cout << " " << std::setw(title_length - 4) << std::setfill(' ')
            << std::left << title << " ";
  if (!color.empty())
    std::cout << RESET;
  std::cout << "|" << std::endl;
  std::cout << "+" << std::string(title_length - 2, '-') << "+" << std::endl;
}

/**
 * 打印表格分隔行
 * 
 * @param widths 每列宽度的size_t向量
 */
inline void print_separator(const std::vector<size_t> &widths) {
  // 构建分隔行，使用'-'字符连接各列宽度
  std::cout << "+";
  for (auto w : widths) {
    std::cout << std::string(w + 2, '-') << "+";
  }
  std::cout << std::endl;
}

/**
 * 打印完整的表格
 * 
 * @param title 表格标题
 * @param headers 表头字符串向量
 * @param rows 二维字符串向量，表示表格数据行
 * @param title_color 标题颜色代码
 * @param header_colors 表头颜色代码向量（可选，默认为空）
 * @param row_colors 二维颜色代码向量，表示每行的颜色（可选，默认为空）
 */
inline void print_table_by_row(
    const std::string title, const std::vector<std::string> &headers,
    const std::vector<std::vector<std::string>> &rows,
    const std::string title_color = "",
    const std::vector<std::string> &header_colors = {},
    const std::vector<std::vector<std::string>> &row_colors = {}) {

  auto widths = calc_col_widths(headers, rows);
  size_t title_length = 1; // 首个 '+'
  for (auto w : widths)
    title_length += w + 3; // 每列内容+左右空格+分隔符
  title_length = std::max(title_length, title.size() + 4);
  print_title(title, title_length, title_color);
  print_separator(widths);
  print_row(headers, widths, header_colors); // 标题可加色
  print_separator(widths);
  for (size_t i = 0; i < rows.size(); ++i) {
    if (!row_colors.empty() && i < row_colors.size())
      print_row(rows[i], widths, row_colors[i]);
    else
      print_row(rows[i], widths);
  }
  print_separator(widths);
}

} // namespace terminal_table

#endif