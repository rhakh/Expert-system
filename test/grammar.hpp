#ifndef __CALCULATOR_GRAMMAR_SIMPLE_HPP__
#define __CALCULATOR_GRAMMAR_SIMPLE_HPP__

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct calculator_simple : qi::grammar<Iterator>
{
        calculator_simple() : calculator_simple::base_type(expression)
        {
        expression = term   >> *( '+' >> term   | '-' >> term );

        term       = factor >> *( '*' >> factor | '/' >> factor );

        factor     = qi::char_("A", "Z")
                        |  '(' >> expression >> ')'
                        | '+' >> factor
                        | '-' >> factor;
        }

        qi::rule<Iterator> expression, term, factor;
};

#endif