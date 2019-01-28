
#ifndef QUADTREE_INL
#define QUADTREE_INL

template < typename T >
Node<T> * Quadtree<T>::GetNode( long long x, long long y ) const
{
	Node<T> * current = this->root;
	long long currentShifting = 63;
	
	for( ; currentShifting >= 0; --currentShifting )
	{
		Node<T> * c = current->child[ ( (x&(1<<currentShifting)) ? 2 : 0 ) + ( (y&(1<<currentShifting)) ? 1 : 0 ) ];
		if( c )
			current = c;
		else
			break;
	}
	
	if( currentShifting == 0 )
		return current;
	return NULL;
}

template < typename T >
Node<T> * Quadtree<T>::GetNodeCreate( long long x, long long y )
{
	Node<T> * current = this->root;
	long long currentShifting = 63;
	
	for( ; currentShifting >= 0; --currentShifting )
	{
		Node<T> ** c = current->child + ( ( (x&(1<<currentShifting)) ? 2 : 0 ) + ( (y&(1<<currentShifting)) ? 1 : 0 ) );
		if( *c == NULL )
		{
			*c = new Node<T>();
			(*c)->parent = current;
			
		}
		current = *c;
	}
	
	return current;
}



template < typename T >
const T & Quadtree<T>::Access( long long x, long long y ) const
{
	Node<T> * node = this->GetNode( x, y );
	if( node != NULL )
		if( node->data != NULL )
			return *(node->data);
	return defaultVal;
}

template < typename T >
T & Quadtree<T>::Access( long long x, long long y )
{
	Node<T> * node = this->GetNodeCreate( x, y );
	if( node != NULL )
	{
		if( node->data == NULL )
		{
			node->data = new T;
			*(node->data) = defaultVal;
		}
		return *(node->data);
	}
	return defaultVal;
}

template < typename T >
bool Quadtree<T>::Exist( long long x, long long y ) const
{
	Node<T> * node = this->GetNode( x, y );
	if( node != NULL )
		if( node->data != NULL )
			return true;
	return false;
}

template < typename T >
void Quadtree<T>::Erase( long long x, long long y )
{
	Node<T> * node = this->GetNode( x, y );
	if( node )
	{
		if( node->data )
		{
			delete node->data;
			node->data = NULL;
		}
		
		node = node->parent;
		
		while( true )
		{
			if( node->child[0] != NULL )
				break;
			if( node->child[1] != NULL )
				break;
			if( node->child[2] != NULL )
				break;
			if( node->child[3] != NULL )
				break;
			
			Node<T> * prev = node;
			node = node->parent;
			
			if( node != NULL )
			{
				for( int i = 0; i < 4; ++i )
				{
					if( node->child[i] == prev )
					{
						delete node->child[i];
						node->child[i] = NULL;
						i = 4;
					}
				}
			}
			else
			{
				break;
			}
		}
	}
}





template < typename T >
void Quadtree<T>::Clear()
{
	this->root->Destroy();
}


template < typename T >
Quadtree<T>::Quadtree( const T & defaultVal_ ) :
	defaultVal(defaultVal_)
{
	this->root = new Node<T>();
}

template < typename T >
Quadtree<T>::~Quadtree()
{
	delete this->root;
	this->root = NULL;
}

#endif

