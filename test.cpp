#include "multiple_sheet.h"

#include <algorithm>

using multiple_sheet::MultipleSheet;

void append(MultipleSheet<int>& sheet, std::initializer_list<int> l) {
  sheet.append_row(std::begin(l), std::end(l));
}

void prepend(MultipleSheet<int>& sheet, std::initializer_list<int> l) {
  sheet.prepend_row(std::begin(l), std::end(l));
}

void append_prepend_test() {
  MultipleSheet<int> sheet(2, 0, 2);
  assert(sheet.size() == 0);

  append(sheet, {1, 2, 3, 4});
  assert(sheet.size() == 4);
  assert(sheet.at(0, 0, 0) == 1);
  assert(sheet.at(0, 0, 1) == 2);
  assert(sheet.at(1, 0, 0) == 3);
  assert(sheet.at(1, 0, 1) == 4);

  append(sheet, {5, 6, 7, 8});
  assert(sheet.size() == 8);
  assert(sheet.at(0, 0, 0) == 1);
  assert(sheet.at(0, 0, 1) == 2);
  assert(sheet.at(1, 0, 0) == 3);
  assert(sheet.at(1, 0, 1) == 4);
  assert(sheet.at(0, 1, 0) == 5);
  assert(sheet.at(0, 1, 1) == 6);
  assert(sheet.at(1, 1, 0) == 7);
  assert(sheet.at(1, 1, 1) == 8);

  assert(*sheet.iterator_at(0, 0, 1) == 2);
  assert(sheet[1] == 2);

  prepend(sheet, {9, 10, 11, 12});
  assert(sheet.at(0, 0, 0) == 9);
  assert(sheet.at(0, 0, 1) == 10);
  assert(sheet.at(1, 0, 0) == 11);
  assert(sheet.at(1, 0, 1) == 12);
  assert(sheet.at(0, 1, 0) == 1);
  assert(sheet.at(0, 1, 1) == 2);
  assert(sheet.at(1, 1, 0) == 3);
  assert(sheet.at(1, 1, 1) == 4);
  assert(sheet.at(0, 2, 0) == 5);
  assert(sheet.at(0, 2, 1) == 6);
  assert(sheet.at(1, 2, 0) == 7);
  assert(sheet.at(1, 2, 1) == 8);
}

void copy_test() {
  MultipleSheet<int> sheet(1, 1, 4);
  std::vector<int> data = {1, 2, 3, 4};
  std::copy(data.begin(), data.end(), sheet.begin());
  MultipleSheet<int> copied(sheet);
  assert(sheet[0] == 1);
  assert(sheet[1] == 2);
  assert(sheet[2] == 3);
  assert(sheet[3] == 4);
}

void list_index_test() {
  MultipleSheet<int> sheet(2, 2, 2);
  auto list0 = sheet.list_index(0);
  assert(list0[0] == std::make_tuple(0, 0, 0, 0));
  assert(list0[1] == std::make_tuple(1, 0, 0, 1));
  assert(list0[2] == std::make_tuple(2, 0, 1, 0));
  assert(list0[3] == std::make_tuple(3, 0, 1, 1));

  auto list1 = sheet.list_index(1);
  assert(list1[0] == std::make_tuple(4, 1, 0, 0));
  assert(list1[1] == std::make_tuple(5, 1, 0, 1));
  assert(list1[2] == std::make_tuple(6, 1, 1, 0));
  assert(list1[3] == std::make_tuple(7, 1, 1, 1));
}

void sheet_begin_end_test() {
  MultipleSheet<int> sheet(2, 2, 2);
  std::iota(sheet.begin(), sheet.end(), 0);
  assert(*sheet.sheet_begin(0) == 0);
  assert(*sheet.sheet_begin(1) == 4);
  assert(sheet.sheet_end(0) == sheet.sheet_begin(1));
  assert(sheet.sheet_end(1) == sheet.end());
}

void erase_last_row_test() {
  MultipleSheet<int> sheet(3, 2, 2);
  std::iota(sheet.begin(), sheet.end(), 0);
  assert(sheet.size() == 12);
  sheet.erase_last_row();
  assert(sheet.num() == 3);
  assert(sheet.rows() == 1);
  assert(sheet.cols() == 2);
  assert(sheet.size() == 6);
  assert(sheet.at(0, 0, 0) == 0);
  assert(sheet.at(0, 0, 1) == 1);
  assert(sheet.at(0, 1, 0) == 4);
  assert(sheet.at(0, 1, 1) == 5);
}

int main() {
  append_prepend_test();
  copy_test();
  list_index_test();
  sheet_begin_end_test();
  erase_last_row_test();

  return 0;
}
