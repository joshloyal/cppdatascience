#include "dataframe.hh"
#include "statvector.hh"
#include <iostream>

int main(int argc, char const *argv[])
{
    auto csv_file = std::string(argv[1]);
    ds::dataframe D(csv_file, true);
    std::cout << "There are " << D.rows() << " rows and " << D.columns() << " columns." << std::endl;

    std::cout << "the column names are:\n";
    for (auto &entry : D.get_column_names())
    {
        std::cout << entry << "   ";
    }
    std::cout << "\nThe second row is :\n";
    
    std::vector<double> v = D.at(1);
    for (auto &entry : v)
    {
        std::cout << entry << "  ";
    }
    std::cout << "\nD.at(1, MEDV) = " << D.at(1, "MEDV") << std::endl;

   
   auto stats = D.at("MEDV");
   std::cout << "count = " << stats.count() << std::endl;
   std::cout << "mean = " << stats.mean() << std::endl;
   std::cout << "std = " << stats.std() << std::endl;
   std::cout << "min = " << stats.min() << std::endl;
   std::cout << "Q1 = " << stats.percentile(0.25) << std::endl;
   std::cout << "median = " << stats.percentile(0.5) << std::endl;
   std::cout << "Q3 = " << stats.percentile(0.75) << std::endl;
   std::cout << "max = " << stats.max() << std::endl;    
}
