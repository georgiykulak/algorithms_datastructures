#ifndef __COMMON_DEBUG_HPP__
#define __COMMON_DEBUG_HPP__

#ifndef NO_DEBUG
#define DEBUG( out )    \
    std::cout << "Location: " << __FUNCTION__ << "; Line: " << __LINE__ << std::endl; \
    std::cout << out << std::endl;
#else
#define DEBUG( out ) ;
#endif /* NO_DEBUG */

#endif /* __COMMON_DEBUG_HPP__ */