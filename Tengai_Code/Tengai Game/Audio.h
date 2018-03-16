#ifndef AUDIO_H
#define AUDIO_H

class Audio : public Module {
public:
	Audio() {};
	bool Init();
	int PreUpdate();
	int Update();
	int  PostUpdate();
	bool CleanUp();
	~Audio() {};
};

#endif
