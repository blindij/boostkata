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

boost::tuple<boost::posix_time::ptime,int> string2datetime_height(const std::string& s, std::string& cm_height);
size_t read_iso_file(std::string& filename, std::vector<std::string>& vecent);
#endif // EBB_FLOW_H_
