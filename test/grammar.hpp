#ifndef GRAMMAR_TEST
#define GRAMMAR_TEST

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct calculator_simple : qi::grammar<Iterator>
        {
        calculator_simple()
                : calculator_simple::base_type(expression)
                {
                expression = term   >> *( '+' >> term   | '|' >> term );

                term       = factor >> *( '*' >> factor | '/' >> factor );

                factor     = qi::uint_
                           |  '(' >> expression >> ')'
                           | '+' >> factor
                           | '|' >> factor;
                }

        qi::rule<Iterator> expression, term, factor;
        };

#endif // GRAMMAR_TEST