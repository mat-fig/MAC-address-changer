
#ifndef MAIN_SAVITCH_SEQUENCE3_H
#define MAIN_SAVITCH_SEQUENCE3_H
#include <cstdlib> // Provides size_t and NULL
#include "node1.h"   // Provides linked list toolkit

namespace main_savitch_5
{

    class sequence
    {
    public:
        // TYPEDEF
        typedef size_t size_type; //typedef std::size_t size_type;
        typedef node::value_type value_type;
        // CONSTRUCTORS and DESTRUCTOR
        sequence( );
        sequence(const sequence& source);
        ~sequence( );
        // MODIFICATION MEMBER FUNCTIONS
        void start( );
        void advance( );
        void insert(const value_type& entry);
        void attach(const value_type& entry);
        void remove_current( );
        void operator =(const sequence& source);
        // CONSTANT MEMBER FUNCTIONS
        size_t size( ) const;
        bool is_item( ) const;
        value_type current( ) const;
    private:
        node* m_head_ptr;
	   node* m_tail_ptr;
	   node* m_cursor; 
	   node* m_precursor; 
	   size_type m_many_nodes;
    };
}

#endif

