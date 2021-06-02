#ifndef CONFIG_HPP_INCLUDED
#define CONFIG_HPP_INCLUDED

#include <boost/foreach.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <exception>
#include <iostream>
#include <set>
#include <string>
namespace pt = boost::property_tree;

namespace Server {

class config {
  public:
    config(){};
    virtual ~config() {
        tree.clear();
    }
    void load(const std::string &filename) {
        pt::read_ini(filename, tree);
    }

  private:
    pt::ptree tree;
};

} // namespace Server

#endif // CONFIG_HPP_INCLUDED