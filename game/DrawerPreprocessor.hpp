
#ifndef DRAWER_PREPROCESSOR_HPP
#define DRAWER_PREPROCESSOR_HPP

#include "../engine/Drawer.hpp"

#include <cmath>

class DrawerPreprocessor : public Drawer
{
protected:
	
	int queueSize;
	Vector * queue;
	
public:
	
	bool IsPointDirectlyInView( Vector point )
	{
		const loctype multiplier = 4;
		Vector dir = this->playerPos - point;
		loctype l = sqrt( ((dir.x*dir.x) + (dir.y*dir.y)) * multiplier * multiplier );
		
		if( l == 0 )
			return true;
		
		dir = ( dir * multiplier * multiplier ) / l;
		
		Vector p = point, p2 = point, p3 = point;
		int i = 1;
		
		/*
		Vector prev;
		for( ; i < 3*multiplier && i < l; ++i )
		{
			p = point + ( ( dir * i ) / multiplier );
			//DEBUG( std::to_string(p.x) + ", " + std::to_string(p.y) );
			if( p != prev )
			{
				if( ( this->data[p.x][p.y].falgs &  ) == 0 )
				
				if( this->data[p.x][p.y].viewDistance == 0 || ( (this->data[p.x][p.y].flags & DRAWER_FLAGS::DIRECTLY_IN_VIEW) == 0 ) )
				{
					//DEBUG(1);
					return false;
				}
				
				prev = p;
			}
		}
		//DEBUG(2);
		return true;
		*/
		
		
		
		
		
		for( ; i < 5*multiplier && i < l; ++i )
		{
			p = point + ( ( dir * i ) / (multiplier*multiplier) );
			if( p != point )
			{
				p2 = p;
				p3 = p;
				break;
			}
		}
		
		for( ; i < 5*multiplier && i < l; ++i )
		{
			p = point + ( ( dir * i ) / (multiplier*multiplier) );
			if( p != p2 )
			{
				p3 = p;
				break;
			}
		}
		
		DrawerPointData & d1 = this->data[point.x][point.y];
		DrawerPointData & d2 = this->data[p2.x][p2.y];
		DrawerPointData & d3 = this->data[p3.x][p3.y];
		
//		DEBUG( ((int)d3.viewDistance) );
//		DEBUG( std::to_string(point.x) + ", " + std::to_string(point.y) );
//		DEBUG( std::to_string(p2.x) + ", " + std::to_string(p2.y) );
//		DEBUG( std::to_string(p3.x) + ", " + std::to_string(p3.y) );
		
		//if( d1.viewDistance == 0 )
		{
			if( p2 == p3 )
			{
				if( point == p2 )
				{
					d1.viewDistance = 255;
				}
				else
				{
					d1.viewDistance = d3.viewDistance - d1.opaqueness;
					if( d1.viewDistance > d3.viewDistance )
					{
//						DEBUG( 1 );
						d1.viewDistance = 0;
					}
				}
				return true;
			}
			else
			{
				d1.viewDistance = d3.viewDistance - d2.opaqueness;
				if( d1.viewDistance > d3.viewDistance )
				{
//					DEBUG( 2 );
					d1.viewDistance = 0;
				}
				else
				{
					d1.viewDistance -= d1.opaqueness;
					if( d1.viewDistance > (d3.viewDistance - d2.opaqueness) )
					{
//						DEBUG( 3 );
						d1.viewDistance = 0;
					}
				}
			}
			if( d1.viewDistance == 0 )
				return false;
		}
		
		return true;
	}
	
	virtual void Preprocess() override
	{
//		DEBUG( "BEG..." );
//		DEBUG( std::to_string(this->playerPos.x) + ", " + std::to_string(this->playerPos.y) );
		
		
		
		Drawer::Preprocess();
		if( this->queueSize != (this->w)*(this->h)*2 )
		{
			if( this->queue )
				Free( this->queue );
			this->queueSize = (this->w)*(this->h)*2;
			this->queue = Allocate<Vector>( this->queueSize );
		}
		
		int freePositionInQueue = 1;
		int toTake = 0;
		
		this->queue[0] = this->playerPos;
		this->data[this->playerPos.x][this->playerPos.y].viewDistance = 255;
		this->data[this->playerPos.x][this->playerPos.y].flags |= DRAWER_FLAGS::QUEUED | DRAWER_FLAGS::DIRECTLY_IN_VIEW | DRAWER_FLAGS::IN_VIEW;
		
		int i, j;
		
		while( toTake < freePositionInQueue && toTake < this->queueSize )
		{
			Vector p = this->queue[toTake];
			
			if( ( (this->IsPointDirectlyInView( p )) || ((this->data[p.x][p.y].flags & DRAWER_FLAGS::DIRECTLY_IN_VIEW) != 0) ) && ( (this->data[p.x][p.y].flags & DRAWER_FLAGS::AFTER_PREPROCESS) == 0 ) )
			{
				if( freePositionInQueue < this->queueSize )
				{
					for( i = p.x-1; i <= p.x+1; ++i )
					{
						for( j = p.y-1; j <= p.y+1; ++j )
						{
							if( i >= 0 && j >= 0 && i < this->w && j < this->h )
							{
								if( (this->data[i][j].flags & DRAWER_FLAGS::QUEUED) == 0 )
								{
									this->queue[freePositionInQueue] = Vector(i,j);
									this->data[i][j].flags |= DRAWER_FLAGS::QUEUED;
									++freePositionInQueue;
								}
								this->data[i][j].flags |= DRAWER_FLAGS::IN_VIEW;
							}
						}
					}
				}
				this->data[p.x][p.y].flags |= DRAWER_FLAGS::AFTER_PREPROCESS | DRAWER_FLAGS::DIRECTLY_IN_VIEW | DRAWER_FLAGS::IN_VIEW;
				//this->data[p.x][p.y].viewDistance = 255;
			}
			
			++toTake;
		}
		
//		DEBUG( std::string("processed = ") + std::to_string(toTake) );
		
		char sign;
		WORD color;
		for( i = 0; i < this->w; ++i )
		{
			for( j = 0; j < this->h; ++j )
			{
				if( (this->data[i][j].flags & DRAWER_FLAGS::IN_VIEW) == 0 )
				{
					this->win->GetChar( Vector(i,j), sign, color );
					this->win->PutChar( Vector(i,j), sign, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN /*| FOREGROUND_INTENSITY*/  |  /*BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | */BACKGROUND_INTENSITY );
					//this->win->PutChar( Vector(i,j), ' ' );
				}
			}
		}
	}
	
	DrawerPreprocessor()
	{
		this->queueSize = 0;
		this->queue = NULL;
	}
	
	~DrawerPreprocessor()
	{
		if( this->queue )
			Free( this->queue );
	}
};

#endif

