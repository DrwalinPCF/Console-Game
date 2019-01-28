
#ifndef QUADTREE_H
#define QUADTREE_H

template < typename T >
class Node
{
public:
	
	Node * parent;
	Node * child[4];
	T * data;
	
	void Destroy()
	{
		if( this->child[0] )
			delete this->child[0];
		this->child[0] = NULL;
		if( this->child[1] )
			delete this->child[1];
		this->child[1] = NULL;
		if( this->child[2] )
			delete this->child[2];
		this->child[2] = NULL;
		if( this->child[3] )
			delete this->child[3];
		this->child[3] = NULL;
		if( this->data )
			delete this->data;
		this->data = NULL;
		this->parent = NULL;
	}
	
	Node()
	{
		this->parent = NULL;
		this->child[0] = NULL;
		this->child[1] = NULL;
		this->child[2] = NULL;
		this->child[3] = NULL;
		this->data = NULL;
	}
	
	~Node()
	{
		this->Destroy();
	}
};

template < typename T >
class Quadtree
{
private:
	
	T defaultVal;
	
	Node<T> * root;
	
	Node<T> * GetNode( long long x, long long y ) const;
	Node<T> * GetNodeCreate( long long x, long long y );
	
public:
	
	const T & Access( long long x, long long y ) const;
	T & Access( long long x, long long y );
	bool Exist( long long x, long long y ) const;
	void Erase( long long x, long long y );
	
	void Clear();
	
	Quadtree( const T & defaultVal_ );
	~Quadtree();
};

#include "Quadtree.inl"

#endif

