//Name : Matheus Figueroa


#include <cassert>
#include <cstdlib>
#include "sequence3.h"
#include "node1.h"
using namespace std;
namespace main_savitch_5
{
	//CONSTRUCTOR ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//Here we are making an object pointers NULL and setting the nodes to 0
	sequence::sequence ()
	{
 

		m_head_ptr = NULL;
		m_tail_ptr = NULL;
		m_cursor = NULL;
		m_precursor = NULL;
		m_many_nodes = 0;
	}


	//This is the copy constructor where there are three cases to look out for 
	/*
	   Case 1: the source is empty, wew will simply copy all of the emptiness from the source into the copied list
	   Case 2: the cursor is currently at the beginning of the list, therfore we copy everthing and make the precursor NULL
	   Case 3: the cursor is not in the first node, it can be anywhere, therfore we use a special function to handle this case. the copy begins at the head ptr to the precursor, the second copy goes from the cursor to the tail node. This is used to easily set the precursor and cursor
	*/
	sequence::sequence ( const sequence& source )
	{
		

		if ( !source.is_item())
		{
			list_copy ( source.m_head_ptr, m_head_ptr, m_tail_ptr);
			m_many_nodes = source.m_many_nodes;
			m_cursor = NULL;
			m_precursor = NULL;
		}

		else if ( source.m_cursor == source.m_head_ptr && source.m_head_ptr == source.m_tail_ptr )
		{

			list_copy ( source.m_head_ptr, m_head_ptr, m_tail_ptr);
			m_many_nodes = source.m_many_nodes;
			m_cursor = source.m_head_ptr;
			m_precursor = NULL;
		}
		else 
		{
			list_piece(source.m_head_ptr, source.m_tail_ptr, m_head_ptr, m_tail_ptr);
			m_many_nodes = source.m_many_nodes;
			if ( source.m_cursor -> link() == NULL )
			{

			m_precursor = m_tail_ptr;
			m_cursor = m_precursor;
			}
			else if ( source.m_cursor == source.m_head_ptr )
			{
				m_cursor = m_head_ptr;
				m_precursor = NULL;
			}
			else
			{
				m_precursor = source.m_precursor;
				m_cursor = source.m_cursor;
			}

		}
	}
	//This is the destructor to release the memory back to the heap
	sequence::~sequence ()
	{
		//Runtime analysis: O(n)

		list_clear(m_head_ptr);
		m_many_nodes = 0;
	}

	//MODIFICATION MEMBERS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//this will put the cursor to the start and the precursor to null, if the list is empty we will return
	void sequence::start () 
	{
		
		if ( m_head_ptr == NULL )
		{
			return;
		}
		m_cursor = m_head_ptr; 
		m_precursor = NULL;
	}

	//This is to advance the cursor, if the link is empty we return, if the link after the cursor in NULL we return, otherwise we progress the cursor and the precursor behind it

	void sequence::advance () 
	{
		
		if ( !is_item())
		{
			return;
		}

		if ( m_cursor->link() != NULL)
		{
			m_precursor = m_cursor;
			m_cursor = m_cursor->link();
		}
		else{
			m_cursor = NULL;
		}
	}

	/*
	   here there are 4 cases to look for
	   case 1: the list is empty, the function will add a new node when the insert function is called
	   case 2: when there is no current item and the head ptr is not null, we will return the cursor back to the front by assigning it to the value of the head pt
	   case 3: when the head ptr link is null and teh head ptr is equal to the cursor, that means only one node is present, so we will insert a new node as the head
	   case 4: when the cursor is somewhere in the middle, we simple insert the precursor to add a node before the cursor
	*/

	void sequence::insert ( const value_type& entry )
	{
		
		if (!is_item() && m_head_ptr != NULL)
		{
			m_cursor = m_head_ptr;
		}


		if ( m_head_ptr == NULL )
		{
			list_head_insert ( m_head_ptr, entry);
			m_cursor = m_head_ptr;
			m_tail_ptr = m_head_ptr;
			m_precursor = m_cursor;
		}
		else if ( m_head_ptr->link() == NULL || m_head_ptr == m_cursor)
		{
			node* insert_ptr = new node ( entry, m_head_ptr);
			m_head_ptr = insert_ptr;
			m_cursor = m_head_ptr;
			m_precursor = m_cursor;
		}
		else
		{
			list_insert(m_precursor, entry);	
			m_cursor = m_precursor->link();
		}

		++m_many_nodes;
	}

	/*
	   here there are 4 cases to look for
	   case 1: the list is empty, the function will add a new node when the attach function is called
	   case 2: when there is no current item and the tail ptr is not null, we will return the cursor back to the front by assigning it to the value of the head pt
	   case 3: when the cursor link is null, we will attach a new node after the cursor adn the cursor will now point to the new node 
	   case 4: when the cursor is somewhere in the middle, we simply attach the cursor to the list_insert function to add a node after the cursor
	*/
	void sequence::attach ( const value_type& entry )
	{
		
		if (!is_item() && m_tail_ptr != NULL)
		{
			m_cursor = m_tail_ptr;
		}

		if ( m_head_ptr == NULL )
		{
			list_head_insert ( m_head_ptr, entry);
			m_cursor = m_head_ptr;
			m_tail_ptr = m_head_ptr;
			m_precursor = m_cursor;
		}
		else if ( m_cursor->link() == NULL )
		{
			list_insert (m_cursor, entry);
			m_precursor = m_cursor;
			m_cursor = m_cursor->link();
			m_tail_ptr = m_cursor;
		}

		else 
		{
			list_insert ( m_cursor, entry);
			m_precursor = m_cursor;
			m_cursor = m_cursor->link();
		}

		++m_many_nodes;
	}

	/*
	   Here there are three cases too look for
	   case 1: the head pt link is null, that means theres only one node so we remove the head
	   case 2: of the head is equal to the cursor we move the cursor forward and remove the head, the head is now in the position of the cursor
	   case 3: other wise, we just remove whatever node in the body of the list and decrementing the list
	   also of the list is empty we just return
	*/

	void sequence::remove_current ()
	{
		
		if (!is_item())
		{
			return;
		}
	
		else if (m_head_ptr->link() == NULL )
		{
			list_head_remove(m_head_ptr);
			m_cursor = NULL;
		}
		else if ( m_head_ptr == m_cursor )
		{
			m_cursor = m_cursor->link();
			list_head_remove(m_head_ptr);
			m_head_ptr = m_cursor;
			m_precursor = m_cursor;
		}
		else 
		{
			list_remove ( m_precursor );
			if(m_precursor->link() != NULL)
			{
				m_cursor = m_precursor->link();
			}
			else
			{
				m_cursor = NULL;
			}
		}

		--m_many_nodes;
	}

	/*
	   this function is the same as the copy constructorm the only difference is that we first check for self assignement , then we clear out the old node and return the memory back to the heap
	*/

	void sequence::operator = ( const sequence& source )
	{
		
		if ( this == &source ) return;

		list_clear(m_head_ptr);

		if ( !source.is_item())
		{
			list_copy ( source.m_head_ptr, m_head_ptr, m_tail_ptr);
			m_many_nodes = source.m_many_nodes;
			m_cursor = NULL;
			m_precursor = NULL;
		}

		else if ( source.m_cursor == source.m_head_ptr && source.m_head_ptr == source.m_tail_ptr )
		{

			list_copy ( source.m_head_ptr, m_head_ptr, m_tail_ptr);
			m_many_nodes = source.m_many_nodes;
			m_cursor = source.m_head_ptr;
			m_precursor = NULL;
		}
		else 
		{
			list_piece(source.m_head_ptr, source.m_tail_ptr, m_head_ptr, m_tail_ptr);
			m_many_nodes = source.m_many_nodes;
			if ( source.m_cursor -> link() == NULL )
			{

			m_precursor = m_tail_ptr;
			m_cursor = m_precursor;
			}
			else if ( source.m_cursor == source.m_head_ptr )
			{
				m_cursor = m_head_ptr;
				m_precursor = NULL;
			}
			else
			{
				m_precursor = source.m_precursor;
				m_cursor = source.m_cursor;
			}
		}
	}

	//CONSTANT MEMBER FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//return size
	size_t sequence::size () const 
	{
		return m_many_nodes;
	}

	//returns bool value if there is a current item
	bool sequence::is_item() const 
	{
		
		if ( m_cursor != NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//returns the current value if there is a current item
	sequence::value_type sequence::current () const 
	{
		
		if (!is_item())
		{
			return 0;
		}
		
		return m_cursor->data();
	}

}
