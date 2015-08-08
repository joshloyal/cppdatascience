//-----------------------------------------------------------------------------
//  statvector.cxx:
//-----------------------------------------------------------------------------

#include "include/statvector.hh"
#include <functional>
#include <algorithm>
#include <numeric>
#include <cmath>

namespace ds
{

statvector::statvector(record_t &data) : data(data)
{
    m_size = data.size();
}

statvector::statvector(const statvector &v) : data(v.data), m_size(v.m_size)
{
}

statvector::statvector(statvector &&v) : data(std::move(v.data)), m_size(std::move(v.m_size))
{
}

statvector& statvector::operator=(const statvector &v)
{
    data = v.data;
    m_size = v.m_size;
    return *this;
}

statvector& statvector::operator=(statvector &&v)
{
    data = std::move(v.data);
    m_size = std::move(v.m_size);
    return *this;
}

statvector::~statvector()
{
}

std::size_t statvector::count() 
{
    return m_size;
}

record_t& statvector::raw() 
{
    return data;
}

double statvector::min()
{
    return *std::min_element(std::begin(data), std::end(data));
}

double statvector::max()
{
    return *std::max_element(std::begin(data), std::end(data));
}

double statvector::sum()
{
    return std::accumulate(std::begin(data), std::end(data), 0.0);
}

double statvector::mean() 
{
    return sum() / m_size;
}

double statvector::std()
{
    std::vector<double> diff(m_size);
    auto m = mean();
    std::transform(std::begin(data), std::end(data), std::begin(diff), 
        std::bind2nd(std::minus<double>(), m));
    double sq_sum = std::inner_product(std::begin(diff), std::end(diff), 
        std::begin(diff), 0.0);
    return std::sqrt(sq_sum / (m_size - 1));
}

double statvector::percentile(float percent)
{
    if (percent > 1 || percent < 0)
    {
        throw std::domain_error("`percent` must be in the range [0,1]");
    }
    
    auto const quantile = data.size() * percent;
    std::nth_element(std::begin(data), std::begin(data) + quantile, std::end(data));
    return data[quantile];
}

double statvector::at(const std::size_t &idx)
{
    return data.at(idx);
}

} // end ns ds
