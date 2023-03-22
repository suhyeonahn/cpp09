#include <string>
#include <iostream>
#include <exception>
#include <stack>

class RPN {
    public:
        RPN();
	    RPN( std::string input );
	    RPN( RPN const & src );
        ~RPN();
        //RPN &   operator=( RPN const & rhs );
        class LowStackException : public std::exception {
			public:
				virtual const char *	what()	const throw();
		};
        class BadCharException : public std::exception {
			public:
				virtual const char *	what()	const throw();
		};
        class BadFormulaException : public std::exception {
			public:
				virtual const char *	what()	const throw();
		};

        float calcul();
    private:
        std::string _input;
};