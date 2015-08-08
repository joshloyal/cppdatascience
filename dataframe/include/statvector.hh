//-----------------------------------------------------------------------------
//  statvector.hh:
//-----------------------------------------------------------------------------
#ifndef STATVECTOR__HH
#define STATVECTOR__HH

#include "csv_reader.hh"

namespace ds
{
class statvector {
public:
//-----------------------------------------------------------------------------
//  Constructors, assignment, etc.
//-----------------------------------------------------------------------------
    statvector(record_t &data);
    statvector(const statvector &v);
    statvector(statvector &&v);
    
    statvector& operator=(const statvector &v);
    statvector& operator=(statvector &&v);
    
    ~statvector();
    
//-----------------------------------------------------------------------------
//  Size / other Information
//-----------------------------------------------------------------------------
    std::size_t count();
    record_t& raw();

//-----------------------------------------------------------------------------
//  Statistics
//-----------------------------------------------------------------------------
    double min();
    double max();
    double sum();
    double std();
    double mean();
    double percentile(float percent);

//-----------------------------------------------------------------------------
//  Element Access
//-----------------------------------------------------------------------------
    double at(const std::size_t &idx);

private:
    record_t data;
    unsigned int m_size;
};

} // end ns ds
#endif
