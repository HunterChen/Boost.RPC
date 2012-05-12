#ifndef BOOST_RPC_ERROR_HPP
#define BOOST_RPC_ERROR_HPP
#include <boost/exception/all.hpp>
#include <boost/format.hpp>

namespace boost { namespace rpc {
typedef boost::error_info<struct err_msg_,std::string> err_msg;

struct exception : public virtual boost::exception, public virtual std::exception {
    const char* what()const throw()     { return "exception";                     }
    virtual void       rethrow()const   { BOOST_THROW_EXCEPTION(*this);                  } 
    const std::string& message()const   { return *boost::get_error_info<boost::rpc::err_msg>(*this); }
};

} } // boost::rpc

/**
 *  Helper macro for throwing exceptions with a message:  THROW( "Hello World %1%, %2%", %"Hello" %"World" )
 */
#define BOOST_RPC_THROW( MSG, ... ) \
  do { \
    BOOST_THROW_EXCEPTION( boost::rpc::exception() << boost::rpc::err_msg( (boost::format( MSG ) __VA_ARGS__ ).str() ) );\
  } while(0)

#endif
