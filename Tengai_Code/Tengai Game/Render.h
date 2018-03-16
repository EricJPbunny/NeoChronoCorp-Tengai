#ifndef _REND_H
#define _REND_H

class Render :public Module {
public:
	Render() {};
	bool Init();
	int PreUpdate();
	int Update();
	int  PostUpdate();
	bool CleanUp();
	~Render() {};
};

#endif
