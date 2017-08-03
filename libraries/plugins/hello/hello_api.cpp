#include <graphene/app/application.hpp>
#include <graphene/chain/database.hpp>

#include <graphene/hello/hello_api.hpp>
#include <graphene/hello/hello_plugin.hpp>

namespace graphene { namespace hello {

namespace detail {

class hello_api_impl
{
   public:
      hello_api_impl( graphene::app::application& _app );
      graphene::app::application& app;
      std::shared_ptr< graphene::hello_plugin::hello_plugin > get_plugin();

      // TODO:  Add API methods here
      uint32_t hello();
};

/**
 * Initializer Implementation
 */
hello_api_impl::hello_api_impl( graphene::app::application& _app ) : app( _app )
{}

/**
 * Get plugin name Implementation
 */
std::shared_ptr< graphene::hello_plugin::hello_plugin > hello_api_impl::get_plugin()
{
   return app.get_plugin< graphene::hello_plugin::hello_plugin >( "hello" );
}

/**
 * Custom call 'hello' implementation
 */
uint32_t hello_api_impl::hello()
{
   // do nothing
   std::shared_ptr< graphene::chain::database > db = app.chain_database();
   return db->head_block_num();
}

} // detail

/*
 * Plugin constructor implementation
 */
hello_api::hello_api( graphene::app::application& app )
{
   my = std::make_shared< detail::hello_api_impl >(app);
}

/*
 * Custom call 'hello' interface
 */
uint32_t hello_api::hello()
{
   return my->hello();
}

} } // graphene::hello
