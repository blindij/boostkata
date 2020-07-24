//
// Created by Bjørn Lindi on 18/07/2020
//

#ifndef EBB_FLOW_H_
#define EBB_FLOW_H_
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/filesystem.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/tuple/tuple_io.hpp>

void new_datetime_height(boost::posix_time::minutes min, double heightfactor, boost::tuple<boost::posix_time::ptime, int>& tho);
boost::tuple<boost::posix_time::ptime,int> string2datetime_height(const boost::tuple<std::string, std::string>& tup);
size_t read_iso_file(std::string& filename, std::vector<std::string>& vecent);
size_t write_iso_file(std::string& filename, std::vector<boost::tuple<boost::posix_time::ptime, int>>& timeheightobjects);
#endif // EBB_FLOW_H_
