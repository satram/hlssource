//AddedLine.cpp

#include "AddedLine.h"

#include <iostream>
#include <sstream>
using namespace std;

AddedLine::AddedLine(long long src_index, long long dst_index, long long num3, string str)
	: CompareResultInterface(ResultTypes::ADDED)
{
	src_line_index = src_index;
	dst_line_index = dst_index;
	if( !str.empty() )	dst_lines.push_back(str);
}

void AddedLine::add_line(string str)
{
        dst_lines.push_back(str);
}

string AddedLine::marshall(void)
{
	stringstream ss;
	ss << (src_line_index+1) << "a" << (dst_line_index+1);
	if( dst_lines.size() > 1 ) ss << "," << (dst_line_index+dst_lines.size());
	ss << endl;

	for( auto str : dst_lines )
		ss << "> " << str << endl;

	return ss.str();
}
