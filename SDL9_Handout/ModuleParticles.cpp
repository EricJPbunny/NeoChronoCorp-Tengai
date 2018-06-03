#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModulePlayer3.h"
#include "ModuleAudio.h"
#include "ModuleUI.h"
#include "ModuleEnemies.h"
#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	//Koyori Bullets
	bullet.anim.PushBack({ 24, 136, 13, 13 });
	bullet.anim.loop = true;
	bullet.life = 1400;
	bullet.speed.x = 12;

	bullet2.anim.PushBack({ 48, 136, 13, 13 });
	bullet2.anim.loop = true;
	bullet2.life = 1400;
	bullet2.speed.x = 12;

	bullet3.anim.PushBack({ 72, 136, 13, 13 });
	bullet3.anim.loop = true;
	bullet3.life = 1400;
	bullet3.speed.x = 12;

	bullet4.anim.PushBack({ 97, 136, 13, 13 });
	bullet4.anim.loop = true;
	bullet4.life = 1400;
	bullet4.speed.x = 12;

	bullet5.anim.PushBack({ 120, 136, 13, 13 });
	bullet5.anim.loop = true;
	bullet5.life = 1400;
	bullet5.speed.x = 12;

	//Sho Bullets
	shoot.anim.PushBack({ 26,107,26,2 });
	shoot.anim.loop = true;
	shoot.life = 1400;
	shoot.speed.x = 8;

	shoot1.anim.PushBack({ 26,111,26,2 });
	shoot1.anim.loop = true;
	shoot1.life = 1400;
	shoot1.speed.x = 8;

	shoot2.anim.PushBack({ 26,115,26,2 });
	shoot2.anim.loop = true;
	shoot2.life = 1400;
	shoot2.speed.x = 8;

	shoot_sho_big.anim.PushBack({ 55,114,32,3 });
	shoot_sho_big.anim.loop = true;
	shoot_sho_big.life = 1400;
	shoot_sho_big.speed.x = 8;

	shoot_sho_big_1.anim.PushBack({ 55,119,32,3 });
	shoot_sho_big_1.anim.loop = true;
	shoot_sho_big_1.life = 1400;
	shoot_sho_big_1.speed.x = 8;

	shoot_sho_big_2.anim.PushBack({ 55,124,32,3 });
	shoot_sho_big_2.anim.loop = true;
	shoot_sho_big_2.life = 1400;
	shoot_sho_big_2.speed.x = 8;

	//Enemies Explosion

	explosion.anim.PushBack({ 24, 206, 56, 65 });
	explosion.anim.PushBack({ 81, 206, 56, 65 });
	explosion.anim.PushBack({ 140, 206, 56, 65 });
	explosion.anim.PushBack({ 202, 206, 56, 65 });
	explosion.anim.PushBack({ 264, 206, 56, 65 });
	explosion.anim.PushBack({ 326, 206, 56, 65 });
	explosion.anim.PushBack({ 387, 206, 56, 65 });
	explosion.anim.PushBack({ 454, 206, 56, 65 });
	explosion.anim.PushBack({ 521, 206, 56, 65 });
	explosion.anim.PushBack({ 588, 206, 56, 65 });
	explosion.anim.PushBack({ 654, 206, 56, 65 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.10f;
	explosion.life = 700;

	//Power UP/DOWN
	power_up.anim.PushBack({ 5,313,26,15 });
	power_up.anim.PushBack({ 5,331,26,15 });
	power_up.anim.PushBack({ 5,350,26,15 });
	power_up.anim.loop = true;
	power_up.anim.speed = 0.20f;
	power_up.life = 1000;

	power_down.anim.PushBack({ 36,331,26,15 });
	power_down.anim.PushBack({ 36,350,26,15 });
	power_down.anim.loop = true;
	power_down.anim.speed = 0.10f;
	power_down.life = 2000;

	//Coin Value

	coin_100.anim.PushBack({ 77,333,9,7 });
	coin_100.anim.PushBack({ 77,342,9,7 });
	coin_100.anim.PushBack({ 77,351,9,7 });
	coin_100.anim.loop = true;
	coin_100.anim.speed = 0.20f;
	coin_100.life = 1000;

	coin_200.anim.PushBack({ 89,333,11,7 });
	coin_200.anim.PushBack({ 89,342,11,7 });
	coin_200.anim.PushBack({ 89,351,11,7 });
	coin_200.anim.loop = true;
	coin_200.anim.speed = 0.20f;
	coin_200.life = 1000;

	coin_500.anim.PushBack({ 103,333,11,7 });
	coin_500.anim.PushBack({ 103,342,11,7 });
	coin_500.anim.PushBack({ 103,351,11,7 });
	coin_500.anim.loop = true;
	coin_500.anim.speed = 0.20f;
	coin_500.life = 1000;

	coin_1000.anim.PushBack({ 117,333,13,7 });
	coin_1000.anim.PushBack({ 117,342,13,7 });
	coin_1000.anim.PushBack({ 117,351,13,7 });
	coin_1000.anim.loop = true;
	coin_1000.anim.speed = 0.20f;
	coin_1000.life = 1000;

	coin_2000.anim.PushBack({ 133,333,15,7 });
	coin_2000.anim.PushBack({ 133,342,15,7 });
	coin_2000.anim.PushBack({ 133,351,15,7 });
	coin_2000.anim.loop = true;
	coin_2000.anim.speed = 0.20f;
	coin_2000.life = 1000;

	coin_4000.anim.PushBack({ 151,333,15,7 });
	coin_4000.anim.PushBack({ 151,342,15,7 });
	coin_4000.anim.PushBack({ 151,351,15,7 });
	coin_4000.anim.loop = true;
	coin_4000.anim.speed = 0.20f;
	coin_4000.life = 1000;

	//Bullet sparks
	spark.anim.PushBack({32,35,45,19});
	spark.anim.PushBack({ 84,35,45,19 });
	spark.anim.PushBack({ 141,35,45,19 });
	spark.anim.PushBack({213,35,45,19 });
	spark.anim.PushBack({ 267,35,45,19 });
	spark.anim.PushBack({ 325,35,45,19 });
	spark.anim.PushBack({ 391,35,45,19 });
	spark.anim.PushBack({ 457,35,45,19 });
	spark.anim.loop = false;
	spark.anim.speed = 0.25f;
	spark.life = 1200;

	//Mirror Bullets
	mirror_shoot.anim.PushBack({ 26,79,23,13 });
	mirror_shoot.anim.loop = true;
	mirror_shoot.life = 1400;
	mirror_shoot.speed.x = 12;

	c_mirror_green.anim.PushBack({ 55,63,32,13 });
	c_mirror_green.anim.loop = true;
	c_mirror_green.life = 1400;
	c_mirror_green.speed.x = 12;

	c_mirror_blue.anim.PushBack({ 55,79,32,13 });
	c_mirror_blue.anim.loop = true;
	c_mirror_blue.life = 1400;
	c_mirror_blue.speed.x = 12;

	c_mirror_cyan.anim.PushBack({ 55,95,32,13 });
	c_mirror_cyan.anim.loop = true;
	c_mirror_cyan.life = 1400;
	c_mirror_cyan.speed.x = 12;

	//Basaro Bullet
	egg_shoot.anim.PushBack({ 14,11,13,13 });
	egg_shoot.anim.PushBack({ 38,11,13,13 });
	egg_shoot.anim.PushBack({ 62,11,13,13 });
	egg_shoot.anim.speed = 0.10f;
	egg_shoot.anim.loop = false;
	egg_shoot.life = 2800;
	egg_shoot.speed.x = 5;

	cat_shoot.anim.PushBack({1,278,57,32});
	cat_shoot.anim.PushBack({ 61,278,57,32 });
	cat_shoot.anim.PushBack({ 122,278,57,32 });
	cat_shoot.anim.speed = 0.10f;
	cat_shoot.anim.loop = true;
	cat_shoot.life = 8400;
	cat_shoot.speed.x = 3;

	basaro_shot.anim.PushBack({379,134,15,15});
	basaro_shot.anim.speed = 0.10f;
	basaro_shot.anim.loop = true;
	basaro_shot.life = 1400;
	basaro_shot.speed.x = 12;

	//Ninja shurikens

	shuriken.anim.PushBack({ 46,176,8,8 });
	shuriken.anim.PushBack({ 58,175,10,10 });
	shuriken.anim.PushBack({ 71,175,10,10 });
	shuriken.anim.PushBack({ 84,175,10,10 });
	shuriken.anim.PushBack({ 98,176,8,8 });
	shuriken.speed.x = -7;
	shuriken.anim.loop = true;
	shuriken.life = 1400;

	//Junis Bullets
	kunai.anim.PushBack({ 88,95,31,9 });
	kunai.speed.x = 8;
	kunai.anim.loop = true;
	kunai.life = 2000;

	kunai1.anim.PushBack({ 88,107,31,9 });
	kunai1.speed.x = 8;
	kunai1.anim.loop = true;
	kunai1.life = 2000;

	kunai2.anim.PushBack({ 88,118,31,9 });
	kunai2.speed.x = 8;
	kunai2.anim.loop = true;
	kunai2.life = 2000;

	//socrates shurikens
	shuriken_socrates_1.anim.PushBack({132,97,8,8});
	shuriken_socrates_1.speed.x = 8;
	shuriken_socrates_1.speed.y = -5;
	shuriken_socrates_1.anim.loop = true;
	shuriken_socrates_1.life = 3000;

	shuriken_socrates_2.anim.PushBack({ 132,97,8,8 });
	shuriken_socrates_2.speed.x = 8;
	shuriken_socrates_2.speed.y = 5;
	shuriken_socrates_2.anim.loop = true;
	shuriken_socrates_2.life = 3000;

	shuriken_socrates_3.anim.PushBack({ 141,94,13,13 });
	shuriken_socrates_3.speed.x = 8;
	shuriken_socrates_3.speed.y = -5;
	shuriken_socrates_3.anim.loop = true;
	shuriken_socrates_3.life = 3000;

	shuriken_socrates_4.anim.PushBack({ 141,94,13,13 });
	shuriken_socrates_4.speed.x = 8;
	shuriken_socrates_4.speed.y = 5;
	shuriken_socrates_4.anim.loop = true;
	shuriken_socrates_4.life = 3000;

	shuriken_socrates_5.anim.PushBack({ 155,90,21,21 });
	shuriken_socrates_5.speed.x = 8;
	shuriken_socrates_5.speed.y = -5;
	shuriken_socrates_5.anim.loop = true;
	shuriken_socrates_5.life = 3000;

	shuriken_socrates_6.anim.PushBack({ 155,90,21,21 });
	shuriken_socrates_6.speed.x = 8;
	shuriken_socrates_6.speed.y = 5;
	shuriken_socrates_6.anim.loop = true;
	shuriken_socrates_6.life = 3000;

	shuriken_socrates_7.anim.PushBack({ 155,90,21,21 });
	shuriken_socrates_7.speed.x = -8;
	shuriken_socrates_7.speed.y = -5;
	shuriken_socrates_7.anim.loop = true;
	shuriken_socrates_7.life = 3000;

	shuriken_socrates_8.anim.PushBack({ 155,90,21,21 });
	shuriken_socrates_8.speed.x = -8;
	shuriken_socrates_8.speed.y = 5;
	shuriken_socrates_8.anim.loop = true;
	shuriken_socrates_8.life = 3000;

	//socrates fire
	fire.anim.PushBack({18,399,10,16});
	
	
	
	fire.speed.x = 3;
	fire.anim.speed = 0.10f;
	fire.anim.loop = true;
	fire.life = 100;

	fire2.anim.PushBack({ 33,396,16,20 });
	fire2.speed.x = 3;
	fire2.anim.speed = 0.10f;
	fire2.anim.loop = true;
	fire2.life = 100;

	fire3.anim.PushBack({ 54,395,19,25 });
	fire3.speed.x = 3;
	fire3.anim.speed = 0.10f;
	fire3.anim.loop = true;
	fire3.life = 100;

	fire4.anim.PushBack({ 79,386,26,36 });
	fire4.speed.x = 3;
	fire4.anim.speed = 0.10f;
	fire4.anim.loop = true;
	fire4.life = 100;

	fire5.anim.PushBack({ 108,382,36,46 });
	fire5.speed.x = 3;
	fire5.anim.speed = 0.10f;
	fire5.anim.loop = true;
	fire5.life = 100;

	fire6.anim.PushBack({ 146,384,40,45 });
	fire6.speed.x = 3;
	fire6.anim.speed = 0.10f;
	fire6.anim.loop = true;
	fire6.life = 100;

	fire7.anim.PushBack({ 195,385,39,44 });
	fire7.speed.x = 3;
	fire7.anim.speed = 0.10f;
	fire7.anim.loop = true;
	fire7.life = 100;

	fire8.anim.PushBack({ 244,389,42,33 });
	fire8.speed.x = 3;
	fire8.anim.speed = 0.10f;
	fire8.anim.loop = true;
	fire8.life = 100;

	fire9.anim.PushBack({ 294,393,39,24 });
	fire9.speed.x = 3;
	fire9.anim.speed = 0.10f;
	fire9.anim.loop = true;
	fire9.life = 100;

	fire10.anim.PushBack({ 340,394,41,20 });
	fire10.speed.x = 3;
	fire10.anim.speed = 0.10f;
	fire10.anim.loop = true;
	fire10.life = 100;

	//Kinfe bullets
	enemie_shoot.anim.PushBack({26,440,6,6});
	enemie_shoot.anim.PushBack({ 43,440,6,6 });
	enemie_shoot.anim.PushBack({ 58,440,6,6 });
	enemie_shoot.anim.PushBack({ 73,440,6,6 });
	enemie_shoot.anim.PushBack({ 89,440,6,6 });
	enemie_shoot.anim.PushBack({ 106,440,6,6 });
	enemie_shoot.anim.loop = true;
	enemie_shoot.life = 1400;
	enemie_shoot.speed.x = -6;

	//Archer bullets

	archer_shoot.anim.PushBack({ 20,461,8,8 });
	archer_shoot.anim.PushBack({ 38,461,8,8 });
	archer_shoot.anim.PushBack({ 56,461,8,8 });
    archer_shoot.anim.PushBack({ 75,461,8,8 });
	archer_shoot.anim.PushBack({ 94,461,8,8 });
	archer_shoot.anim.PushBack({ 114,461,8,8 });
	archer_shoot.anim.loop = true;
	archer_shoot.life = 1400;
	archer_shoot.speed.x = -2;

	//Bird bullets
	bird_shoot2.anim.PushBack({ 7,438,10,10 });
	bird_shoot.anim.PushBack({ 24,438,10,10 });
	bird_shoot.anim.PushBack({ 41,438,10,10 });
	bird_shoot.anim.PushBack({ 56,438,10,10 });
	bird_shoot.anim.PushBack({ 71,438,10,10 });
	bird_shoot.anim.PushBack({ 87,438,10,10 });
	bird_shoot.anim.PushBack({ 104,438,10,10 });
	bird_shoot.anim.loop = true;
	bird_shoot.life = 1400;
	bird_shoot.speed.x = -4;

	//Ship head boss bullets
	shipHead_shoot.anim.PushBack({ 20,461,8,8 });
	shipHead_shoot.anim.PushBack({ 38,461,8,8 });
	shipHead_shoot.anim.PushBack({ 56,461,8,8 });
	shipHead_shoot.anim.PushBack({ 75,461,8,8 });
	shipHead_shoot.anim.PushBack({ 94,461,8,8 });
	shipHead_shoot.anim.PushBack({ 114,461,8,8 });
	shipHead_shoot.anim.loop = true;
	shipHead_shoot.life = 1400;
	shipHead_shoot.speed.x = -1.2f;
	shipHead_shoot.speed.y = 0;
	

	//Elf bullets

	
	elf_shoot.anim.PushBack({ 20,461,8,8 });
	elf_shoot.anim.PushBack({ 38,461,8,8 });
	elf_shoot.anim.PushBack({ 56,461,8,8 });
	elf_shoot.anim.PushBack({ 75,461,8,8 });
	elf_shoot.anim.PushBack({ 94,461,8,8 });
	elf_shoot.anim.PushBack({ 114,461,8,8 });
	elf_shoot.anim.loop = true;
	elf_shoot.life = 3400;
	elf_shoot.speed.x = -2;
	

	
	elf_shoot2.anim.PushBack({ 20,461,8,8 });
	elf_shoot2.anim.PushBack({ 38,461,8,8 });
	elf_shoot2.anim.PushBack({ 56,461,8,8 });
	elf_shoot2.anim.PushBack({ 75,461,8,8 });
	elf_shoot2.anim.PushBack({ 94,461,8,8 });
	elf_shoot2.anim.PushBack({ 114,461,8,8 });
	elf_shoot2.anim.loop = true;
	elf_shoot2.life = 3400;
	elf_shoot2.speed.x = -2;
	

	elf_shoot3.anim.PushBack({ 20,461,8,8 });
	elf_shoot3.anim.PushBack({ 38,461,8,8 });
	elf_shoot3.anim.PushBack({ 56,461,8,8 });
	elf_shoot3.anim.PushBack({ 75,461,8,8 });
	elf_shoot3.anim.PushBack({ 94,461,8,8 });
	elf_shoot3.anim.PushBack({ 114,461,8,8 });
	elf_shoot3.anim.loop = true;
	elf_shoot3.life = 3400;
	elf_shoot3.speed.y = 2;

	
	elf_shoot4.anim.PushBack({ 20,461,8,8 });
	elf_shoot4.anim.PushBack({ 38,461,8,8 });
	elf_shoot4.anim.PushBack({ 56,461,8,8 });
	elf_shoot4.anim.PushBack({ 75,461,8,8 });
	elf_shoot4.anim.PushBack({ 94,461,8,8 });
	elf_shoot4.anim.PushBack({ 114,461,8,8 });
	elf_shoot4.anim.loop = true;
	elf_shoot4.life = 3400;
	elf_shoot4.speed.y = 2;

	
	elf_shoot5.anim.PushBack({ 20,461,8,8 });
	elf_shoot5.anim.PushBack({ 38,461,8,8 });
	elf_shoot5.anim.PushBack({ 56,461,8,8 });
	elf_shoot5.anim.PushBack({ 75,461,8,8 });
	elf_shoot5.anim.PushBack({ 94,461,8,8 });
	elf_shoot5.anim.PushBack({ 114,461,8,8 });
	elf_shoot5.anim.loop = true;
	elf_shoot5.life = 3400;
	elf_shoot5.speed.x = -2;
	elf_shoot5.speed.y = 2;

	
	elf_shoot6.anim.PushBack({ 20,461,8,8 });
	elf_shoot6.anim.PushBack({ 38,461,8,8 });
	elf_shoot6.anim.PushBack({ 56,461,8,8 });
	elf_shoot6.anim.PushBack({ 75,461,8,8 });
	elf_shoot6.anim.PushBack({ 94,461,8,8 });
	elf_shoot6.anim.PushBack({ 114,461,8,8 });
	elf_shoot6.anim.loop = true;
	elf_shoot6.life = 3400;
	elf_shoot6.speed.x = -2;
	elf_shoot6.speed.y = 2;

	elf_shoot7.anim.PushBack({ 20,461,8,8 });
	elf_shoot7.anim.PushBack({ 38,461,8,8 });
	elf_shoot7.anim.PushBack({ 56,461,8,8 });
	elf_shoot7.anim.PushBack({ 75,461,8,8 });
	elf_shoot7.anim.PushBack({ 94,461,8,8 });
	elf_shoot7.anim.PushBack({ 114,461,8,8 });
	elf_shoot7.anim.loop = true;
	elf_shoot7.life = 3400;
	elf_shoot8.speed.x = -2;
	elf_shoot7.speed.y = -2;



	elf_shoot8.anim.PushBack({ 20,461,8,8 });
	elf_shoot8.anim.PushBack({ 38,461,8,8 });
	elf_shoot8.anim.PushBack({ 56,461,8,8 });
	elf_shoot8.anim.PushBack({ 75,461,8,8 });
	elf_shoot8.anim.PushBack({ 94,461,8,8 });
	elf_shoot8.anim.PushBack({ 114,461,8,8 });
	elf_shoot8.anim.loop = true;
	elf_shoot8.life = 3400;
	elf_shoot8.speed.x = -2;
	elf_shoot8.speed.y = -2;



	//Elf shurikens

	elf_shuriken.anim.PushBack({ 136,440,10,11 });
	elf_shuriken.anim.PushBack({ 160,440,10,11 });
	elf_shuriken.anim.PushBack({ 187,440,10,11 });
	elf_shuriken.anim.PushBack({ 215,440,10,11 });
	elf_shuriken.anim.PushBack({ 244,440,10,11 });
	elf_shuriken.anim.loop = true;
	elf_shuriken.life = 3400;
	elf_shuriken.speed.x = -3;


	elf_shuriken2.anim.PushBack({ 136,440,10,11 });
	elf_shuriken2.anim.PushBack({ 160,440,10,11 });
	elf_shuriken2.anim.PushBack({ 187,440,10,11 });
	elf_shuriken2.anim.PushBack({ 215,440,10,11 });
	elf_shuriken2.anim.PushBack({ 244,440,10,11 });
	elf_shuriken2.anim.loop = true;
	elf_shuriken2.life = 3400;
	elf_shuriken2.speed.x = -3;



	elf_shuriken3.anim.PushBack({ 136,440,10,11 });
	elf_shuriken3.anim.PushBack({ 160,440,10,11 });
	elf_shuriken3.anim.PushBack({ 187,440,10,11 });
	elf_shuriken3.anim.PushBack({ 215,440,10,11 });
	elf_shuriken3.anim.PushBack({ 244,440,10,11 });
	elf_shuriken3.anim.loop = true;
	elf_shuriken3.life = 3400;
	elf_shuriken3.speed.x = 3;


	elf_shuriken4.anim.PushBack({ 136,440,10,11 });
	elf_shuriken4.anim.PushBack({ 160,440,10,11 });
	elf_shuriken4.anim.PushBack({ 187,440,10,11 });
	elf_shuriken4.anim.PushBack({ 215,440,10,11 });
	elf_shuriken4.anim.PushBack({ 244,440,10,11 });
	elf_shuriken4.anim.loop = true;
	elf_shuriken4.life = 3400;
	elf_shuriken4.speed.x = 3;


	elf_shuriken5.anim.PushBack({ 136,440,10,11 });
	elf_shuriken5.anim.PushBack({ 160,440,10,11 });
	elf_shuriken5.anim.PushBack({ 187,440,10,11 });
	elf_shuriken5.anim.PushBack({ 215,440,10,11 });
	elf_shuriken5.anim.PushBack({ 244,440,10,11 });
	elf_shuriken5.anim.loop = true;
	elf_shuriken5.life = 3400;
	elf_shuriken5.speed.y = 2;


	elf_shuriken6.anim.PushBack({ 136,440,10,11 });
	elf_shuriken6.anim.PushBack({ 160,440,10,11 });
	elf_shuriken6.anim.PushBack({ 187,440,10,11 });
	elf_shuriken6.anim.PushBack({ 215,440,10,11 });
	elf_shuriken6.anim.PushBack({ 244,440,10,11 });
	elf_shuriken6.anim.loop = true;
	elf_shuriken6.life = 3400;
	elf_shuriken6.speed.y = 2;

	elf_shuriken7.anim.PushBack({ 136,440,10,11 });
	elf_shuriken7.anim.PushBack({ 160,440,10,11 });
	elf_shuriken7.anim.PushBack({ 187,440,10,11 });
	elf_shuriken7.anim.PushBack({ 215,440,10,11 });
	elf_shuriken7.anim.PushBack({ 244,440,10,11 });
	elf_shuriken7.anim.loop = true;
	elf_shuriken7.life = 3400;
	elf_shuriken7.speed.y = -2;

	elf_shuriken8.anim.PushBack({ 136,440,10,11 });
	elf_shuriken8.anim.PushBack({ 160,440,10,11 });
	elf_shuriken8.anim.PushBack({ 187,440,10,11 });
	elf_shuriken8.anim.PushBack({ 215,440,10,11 });
	elf_shuriken8.anim.PushBack({ 244,440,10,11 });
	elf_shuriken8.anim.loop = true;
	elf_shuriken8.life = 3400;
	elf_shuriken8.speed.y = -2;

	elf_shuriken9.anim.PushBack({ 136,440,10,11 });
	elf_shuriken9.anim.PushBack({ 160,440,10,11 });
	elf_shuriken9.anim.PushBack({ 187,440,10,11 });
	elf_shuriken9.anim.PushBack({ 215,440,10,11 });
	elf_shuriken9.anim.PushBack({ 244,440,10,11 });
	elf_shuriken9.anim.loop = true;
	elf_shuriken9.life = 3400;
	elf_shuriken9.speed.x = -2;
	elf_shuriken9.speed.y = -2;

	elf_shuriken10.anim.PushBack({ 136,440,10,11 });
	elf_shuriken10.anim.PushBack({ 160,440,10,11 });
	elf_shuriken10.anim.PushBack({ 187,440,10,11 });
	elf_shuriken10.anim.PushBack({ 215,440,10,11 });
	elf_shuriken10.anim.PushBack({ 244,440,10,11 });
	elf_shuriken10.anim.loop = true;
	elf_shuriken10.life = 3400;
	elf_shuriken10.speed.x = -2;
	elf_shuriken10.speed.y = -2;

	elf_shuriken11.anim.PushBack({ 136,440,10,11 });
	elf_shuriken11.anim.PushBack({ 160,440,10,11 });
	elf_shuriken11.anim.PushBack({ 187,440,10,11 });
	elf_shuriken11.anim.PushBack({ 215,440,10,11 });
	elf_shuriken11.anim.PushBack({ 244,440,10,11 });
	elf_shuriken11.anim.loop = true;
	elf_shuriken11.life = 3400;
	elf_shuriken11.speed.x = 2;
	elf_shuriken11.speed.y = 2;

	elf_shuriken12.anim.PushBack({ 136,440,10,11 });
	elf_shuriken12.anim.PushBack({ 160,440,10,11 });
	elf_shuriken12.anim.PushBack({ 187,440,10,11 });
	elf_shuriken12.anim.PushBack({ 215,440,10,11 });
	elf_shuriken12.anim.PushBack({ 244,440,10,11 });
	elf_shuriken12.anim.loop = true;
	elf_shuriken12.life = 3400;
	elf_shuriken12.speed.x = 2;
	elf_shuriken12.speed.y = 2;

	elf_shuriken13.anim.PushBack({ 136,440,10,11 });
	elf_shuriken13.anim.PushBack({ 160,440,10,11 });
	elf_shuriken13.anim.PushBack({ 187,440,10,11 });
	elf_shuriken13.anim.PushBack({ 215,440,10,11 });
	elf_shuriken13.anim.PushBack({ 244,440,10,11 });
	elf_shuriken13.anim.loop = true;
	elf_shuriken13.life = 3400;
	elf_shuriken13.speed.x = 2;
	elf_shuriken13.speed.y = -2;

	elf_shuriken14.anim.PushBack({ 136,440,10,11 });
	elf_shuriken14.anim.PushBack({ 160,440,10,11 });
	elf_shuriken14.anim.PushBack({ 187,440,10,11 });
	elf_shuriken14.anim.PushBack({ 215,440,10,11 });
	elf_shuriken14.anim.PushBack({ 244,440,10,11 });
	elf_shuriken14.anim.loop = true;
	elf_shuriken14.life = 3400;
	elf_shuriken14.speed.x = 2;
	elf_shuriken14.speed.y = -2;

	elf_shuriken15.anim.PushBack({ 136,440,10,11 });
	elf_shuriken15.anim.PushBack({ 160,440,10,11 });
	elf_shuriken15.anim.PushBack({ 187,440,10,11 });
	elf_shuriken15.anim.PushBack({ 215,440,10,11 });
	elf_shuriken15.anim.PushBack({ 244,440,10,11 });
	elf_shuriken15.anim.loop = true;
	elf_shuriken15.life = 3400;
	elf_shuriken15.speed.x = -2;
	elf_shuriken15.speed.y = 2;

	elf_shuriken16.anim.PushBack({ 136,440,10,11 });
	elf_shuriken16.anim.PushBack({ 160,440,10,11 });
	elf_shuriken16.anim.PushBack({ 187,440,10,11 });
	elf_shuriken16.anim.PushBack({ 215,440,10,11 });
	elf_shuriken16.anim.PushBack({ 244,440,10,11 });
	elf_shuriken16.anim.loop = true;
	elf_shuriken16.life = 3400;
	elf_shuriken16.speed.x = -2;
	elf_shuriken16.speed.y = 2;

}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("assets/sprite/particles.png");

	shoot_audio = App->audio->LoadEffect("assets/audio/Shot_Koyori.wav");
	shoot_sho = App->audio->LoadEffect("assets/audio/Shot_Sho.wav");
	shoot_junis = App->audio->LoadEffect("assets/audio/junis_attack.wav");
	power_up_koyori_fx = App->audio->LoadEffect("assets/audio/power_up_koyori.wav");
	power_up_sho_fx = App->audio->LoadEffect("assets/audio/power_up_sho.wav");
	power_up_junis_fx = App->audio->LoadEffect("assets/audio/power_up_junis.wav");
	koyori_death = App->audio->LoadEffect("assets/audio/death_koyori.wav");
	sho_death = App->audio->LoadEffect("assets/audio/death_sho.wav");
	junis_death = App->audio->LoadEffect("assets/audio/junis_hit.wav");
	coin_fx = App->audio->LoadEffect("assets/audio/catch_coin.wav");

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	App->audio->UnloadFx(sho_death);
	App->audio->UnloadFx(koyori_death);
	App->audio->UnloadFx(junis_death);
	App->audio->UnloadFx(power_up_sho_fx);
	App->audio->UnloadFx(power_up_koyori_fx);
	App->audio->UnloadFx(shoot_sho);
	App->audio->UnloadFx(shoot_junis);
	App->audio->UnloadFx(shoot_audio);
	App->audio -> UnloadFx(coin_fx);

	App->textures->Unload(graphics);

	// Unload fx

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if(p->fx_played == false)
			{
				p->fx_played = true;
				//App->audio->PlayFx(p->fx);
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, PARTICLE_TYPE particle_type, Uint32 delay)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if(collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			if (particle_type == PARTICLE_SHOT) {
				App->audio->PlaySoundEffects(shoot_audio);
			}
			if (particle_type == PARTICLE_SHOT_2) {
				App->audio->PlaySoundEffects(shoot_sho);
			}
			if (particle_type == PARTICLE_SHOT_3) {
				App->audio->PlaySoundEffects(shoot_junis);
			}
			if (particle_type == PARTICLE_POWER_UP_KOYORI) {
				App->audio->PlaySoundEffects(power_up_koyori_fx);
			}
			if (particle_type == PARTICLE_POWER_UP_SHO) {
				App->audio->PlaySoundEffects(power_up_sho_fx);
			}
			if (particle_type == PARTICLE_POWER_UP_JUNIS) {
				App->audio->PlaySoundEffects(power_up_junis_fx);
			}
			if (particle_type == PARTICLE_COIN) {
				App->audio->PlaySoundEffects(coin_fx);
			}
			active[i] = p;
			break;
		}
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if(active[i] != nullptr && active[i]->collider == c1)
		{
			if (c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_SHOT && (c2->type == COLLIDER_TYPE::COLLIDER_ULTI2 || c2->type == COLLIDER_TYPE::COLLIDER_ULTI3)) {
				delete active[i];
				active[i] = nullptr;
				break;
			}
			//Enemy Shot collide Player
			if (c2->type == COLLIDER_TYPE::COLLIDER_HITBOX && c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_SHOT)
			{
				if (c2 == App->player->hitbox) {
					App->audio->PlaySoundEffects(App->enemies->fx_death);
					App->particles->AddParticle(App->particles->explosion, active[i]->position.x, active[i]->position.y);
					App->audio->PlaySoundEffects(koyori_death);
					App->ui->num_life_koyori--;
					App->player->state = DEATH;
				}
				if (c2 == App->player2->hitbox) {
					App->audio->PlaySoundEffects(App->enemies->fx_death);
					App->audio->PlaySoundEffects(sho_death);
					App->ui->num_life_sho--;
					App->player2->state = DEATH_2;
				}
				if (c2 == App->player3->hitbox) {
					App->audio->PlaySoundEffects(App->enemies->fx_death);
					App->audio->PlaySoundEffects(junis_death);
					App->ui->num_life_junis--;
					App->player3->state = DEATH_3;
				}
			}
			//AddParticle(explosion, active[i]->position.x, active[i]->position.y);
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		if((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if(collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}

