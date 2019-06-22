
#ifndef BLOCK_STATE_H
#define BLOCK_STATE_H

class BlockState
{
public:
	
	unsigned char data;
	
public:
	
	static BlockState & GetPureReference();
	
	bool IsWalkable() const;
	unsigned char GetOpaqueness() const;		// 0 - do not block view at all ; 255 - block all the view
	bool IsStaticallyDrawn() const;
	
	void Draw( class Drawer * drawer );
	
	BlockState();
	BlockState( unsigned char data );
	~BlockState();
};

#endif

