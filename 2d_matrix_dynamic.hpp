#include <vector>

enum class Columnar_methods { m0, m1, m2 };

typedef double (*columnar_fun_ptr) (std::vector<double>);

double m0(std::vector<double> v) { return 0.0; }
double m1(std::vector<double> v) { return 1.0; }
double m2(std::vector<double> v) { return 2.0; }

// Marix_dynamic dynamically add new rows into the matrix, you can think
// the row as a CSV record or entry
// then for each column, we have a predifined function to perform columnar computation
// after we have the columnar result for each columnar, we can apply to the each row to
// get the final result, please see the following example
// for matrix
// 1.0, 2.0, 3.0
// 4.0, 5.0, 6.0
// 7.0, 8.0, 9.0
// for column 0, we have 1.0, 4.0, 7.0, if we predefine the method to mean, we will have the result
// for column 0 to 4.0 , then after computeRows we will have -3.0, 0, 3.0 as the first columnar result
// same apply to column 1, and 2

class Matrix_dynamic {
 public:
 Matrix_dynamic(size_t n_col_, std::vector<Columnar_methods> &methods) : n_col{n_col_} {
    for (const auto& it : methods) {
      switch (it) {
      case Columnar_methods::m0:
	funcs.push_back(m0);
	break;
      case Columnar_methods::m1:
	funcs.push_back(m1);
	break;
      case Columnar_methods::m2:
	funcs.push_back(m2);
	break;
      default:
	break;
      }
    }
  }
  
  void addRow(std::vector<double>&);
  void addMultiRows(std::vector<std::vector<double>>&);

  // compute the result based on column
  std::vector<double> computeColumns();

  // apply the column result on each row
  void computeRows(std::vector<double> &columnar_result);

 private:
  std::vector<std::vector<double>> matrix;
  size_t n_col;
  std::vector<columnar_fun_ptr> funcs;
};
