#ifndef INPUT_H
#define INPUT_H

class Input :public Module {
public:
	Input() {};
	bool Init();
	int PreUpdate();
	int Update();
	int  PostUpdate();
	bool CleanUp();
	~Input() {};
};


#endif
