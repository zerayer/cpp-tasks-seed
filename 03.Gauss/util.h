#ifndef GAUSS_UTIL_H
#define GAUSS_UTIL_H

#include <iosfwd>

#include <Eigen/Dense>

using GaussVector = Eigen::VectorXd;
using GaussMatrix = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

GaussMatrix load_csv_to_matrix(const char *filename);

void print_solution_csv(std::ostream& out, const GaussVector& solution, int prec = 6);

#endif // GAUSS_UTIL_H
