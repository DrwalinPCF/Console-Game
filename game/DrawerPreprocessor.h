
#ifndef DRAWER_PREPROCESSOR_H
#define DRAWER_PREPROCESSOR_H

#include "../engine/Drawer.hpp"

class DrawerPreprocessor : public Drawer
{
protected:
	
	
	
public:
	
	void ScanOneLine( const Vector & start, const Vector & end, loctype distance );
	
	virtual void Preprocess() override;
	
	DrawerPreprocessor();
	~DrawerPreprocessor();
};

#endif

