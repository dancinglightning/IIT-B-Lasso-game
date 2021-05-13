#include <simplecpp>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace simplecpp;

//movingObject.h
#ifndef _MOVINGOBJECT_INCLUDED_
#define _MOVINGOBJECT_INCLUDED_

#include <simplecpp>
#include <vector>
#include <composite.h>
#include <sprite.h>

using namespace simplecpp;

extern int type;
int type = 1;

extern int points;
int points = 0;

extern int speed_up;
int speed_up = 0;

extern int slow_down;
int slow_down = 0;

extern int life;
int life = 3;

extern int pp21;
int pp21=0;

extern int pp22;
int pp22=0;

extern int pp31;
int pp31=0;

extern int pp32;
int pp32=0;

extern int pp41;
int pp41=0;

extern int pp42;
int pp42=0;

extern int pp51;
int pp51=0;

extern int pp52;
int pp52=0;

extern int pp61;
int pp61=0;

extern int pp62;
int pp62=0;

class MovingObject : public Sprite {
  vector<Sprite*> parts;
  double vx, vy;
  double ax, ay;
  bool paused;
  void initMO(double argvx, double argvy, double argax, double argay, bool argpaused=true) {
    vx=argvx; vy=argvy; ax=argax; ay=argay; paused=argpaused;
  }
 public:
 MovingObject(double argvx, double argvy, double argax, double argay, bool argpaused=true)
    : Sprite() {
    initMO(argvx, argvy, argax, argay, argpaused);
  }
 MovingObject(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : Sprite() {
   double angle_rad = angle_deg*PI/180.0;
   double argvx = speed*cos(angle_rad);
   double argvy = -speed*sin(angle_rad);
   initMO(argvx, argvy, argax, argay, argpaused);
  }
  void set_vx(double argvx) { vx = argvx; }
  void set_vy(double argvy) { vy = argvy; }
  void set_ax(double argax) { ax = argax; }
  void set_ay(double argay) { ay = argay; }
  double getXPos();
  double getYPos();
  void reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta);

  void pause() { paused = true; }
  void unpause() { paused = false; }
  bool isPaused() { return paused; }

  void addPart(Sprite* p) {
    parts.push_back(p);
  }
  void nextStep(double t);
  void getAttachedTo(MovingObject *m);
};

#endif

//MovingObject.cpp

void MovingObject::nextStep(double t) {
  if(paused) { return; }
   //cerr << "x=" << getXPos() << ",y=" << getYPos() << endl;
   //cerr << "vx=" << vx << ",vy=" << vy << endl;
   //cerr << "ax=" << ax << ",ay=" << ay << endl;

  for(size_t i=0; i<parts.size(); i++){
    parts[i]->move(vx*t, vy*t);
  }
  vx += ax*t;
  vy += ay*t;
} // End MovingObject::nextStep()

double MovingObject::getXPos() {
  return (parts.size() > 0) ? parts[0]->getX() : -1;
}

double MovingObject::getYPos() {
  return (parts.size() > 0) ? parts[0]->getY() : -1;
}

void MovingObject::reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) {
  for(size_t i=0; i<parts.size(); i++){
    parts[i]->moveTo(argx, argy);
  }
  double angle_rad = angle_deg*PI/180.0;
  double argvx = speed*cos(angle_rad);
  double argvy = -speed*sin(angle_rad);
  vx = argvx; vy = argvy; ax = argax; ay = argay; paused = argpaused;
} // End MovingObject::reset_all()

void MovingObject::getAttachedTo(MovingObject *m) {
  double xpos = m->getXPos();
  double ypos = m->getYPos();
  for(size_t i=0; i<parts.size(); i++){
    parts[i]->moveTo(xpos, ypos);
  }
  initMO(m->vx, m->vy, m->ax, m->ay, m->paused);
}

//coin.h
#ifndef __COIN_H__
#define __COIN_H__



class Coin : public MovingObject {
  double coin_start_x;
  double coin_start_y;
  double release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;

  // Moving parts
  Circle coin_circle;

 public:
 int type=1;
 Coin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;
    initCoin();
  }

  void initCoin();
  int resetCoin();

}; // End class Coin

#endif

//lasso.h
#ifndef __LASSO_H__
#define __LASSO_H__

//#define WINDOW_X 1200
//#define WINDOW_Y 960
#define WINDOW_X 800
#define WINDOW_Y 600

#define STEP_TIME 0.1

#define PLAY_X_START 100
#define PLAY_Y_START 0
#define PLAY_X_WIDTH (WINDOW_X-PLAY_X_START)
#define PLAY_Y_HEIGHT (WINDOW_Y-100)

#define LASSO_X_OFFSET 100
#define LASSO_Y_HEIGHT 100
#define LASSO_BAND_LENGTH LASSO_X_OFFSET
#define LASSO_THICKNESS 5

#define COIN_GAP 0

#define RELEASE_ANGLE_STEP_DEG 5
#define MIN_RELEASE_ANGLE_DEG 0
#define MAX_RELEASE_ANGLE_DEG (360-RELEASE_ANGLE_STEP_DEG)
#define INIT_RELEASE_ANGLE_DEG 45

#define RELEASE_SPEED_STEP 20
#define MIN_RELEASE_SPEED 0
#define MAX_RELEASE_SPEED 250
#define INIT_RELEASE_SPEED 125

#define COIN_SPEED 130
#define COIN_ANGLE_DEG 80

#define LASSO_G 30
#define COIN_G 30

#define LASSO_SIZE 10
#define LASSO_RADIUS 50
#define COIN_SIZE 5

class Lasso : public MovingObject {
  double lasso_start_x;
  double lasso_start_y;
  double release_speed;
  double release_angle_deg;
  double lasso_ax;
  double lasso_ay;

  // Moving parts
  Circle lasso_circle;
  Circle lasso_loop;

  // Non-moving parts
  Line lasso_line;
  Line lasso_band;

  // State info
  bool lasso_looped;
  Coin *the_coin;
  int num_coins;

  void initLasso();
 public:
 Lasso(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    lasso_ax = argax;
    lasso_ay = argay;
    initLasso();
  }

  void draw_lasso_band();
  void yank();
  void loopit();
  void addAngle(double angle_deg);
  void addSpeed(double speed);

  void nextStep(double t);
  void check_for_coin(Coin *coin);
  int getNumCoins() { return num_coins; }

}; // End class Lasso

#endif

//coin.h

void Coin::initCoin()
{
  coin_start_x = (PLAY_X_START+WINDOW_X)/2;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);

  coin_circle.setColor(COLOR(255,215,0));
  coin_circle.setFill(true);
  addPart(&coin_circle);
}

int Coin::resetCoin()
{
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
  int predictNorm;
  predictNorm=rand()%30;

  if(predictNorm>=pp21 and predictNorm<=pp22)
  {
     coin_circle.setColor(COLOR(149,71,182));  //Special Coin
     coin_circle.setFill(true);
     type=2;
     return 2;
  }

  if(predictNorm>=pp31 and predictNorm<=pp32)
  {
     coin_circle.setColor(COLOR(0,0,0));  //Bomb
     coin_circle.setFill(true);
     type=0;
     return 0;
  }

  if(predictNorm>=pp41 and predictNorm<=pp42)
  {
     coin_circle.setColor(COLOR(255,128,0));  //Speed_up coin
     coin_circle.setFill(true);
     type=3;
     return 0;
  }

  if(predictNorm>=pp51 and predictNorm<=pp52)
  {
     coin_circle.setColor(COLOR(0,255,255));  //Slow_down coin
     coin_circle.setFill(true);
     type=4;
     return 0;
  }

  if(predictNorm>=pp61 and predictNorm<=pp62)
  {
     coin_circle.setColor(COLOR(255,0,0));  //Life coin
     coin_circle.setFill(true);
     type=5;
     return 0;
  }

  else
  {
     coin_circle.setColor(COLOR(255,215,0));  //Golden Coin
     coin_circle.setFill(true);
     type=1;
     return 1;
  }

}

//lasso.cpp

void Lasso::draw_lasso_band()
{
  double len = (release_speed/MAX_RELEASE_SPEED)*LASSO_BAND_LENGTH;
  double arad = release_angle_deg*PI/180.0;
  double xlen = len*cos(arad);
  double ylen = len*sin(arad);
  lasso_band.reset(lasso_start_x, lasso_start_y, (lasso_start_x-xlen), (lasso_start_y+ylen));
  lasso_band.setThickness(LASSO_THICKNESS);
} // End Lasso::draw_lasso_band()

void Lasso::initLasso()
{
  lasso_start_x = (PLAY_X_START+LASSO_X_OFFSET);
  lasso_start_y = (PLAY_Y_HEIGHT-LASSO_Y_HEIGHT);
  lasso_circle.reset(lasso_start_x, lasso_start_y, LASSO_SIZE);
  lasso_circle.setColor(COLOR(124,64,0));
  lasso_circle.setFill(true);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setColor(COLOR(124,64,0));
  lasso_loop.setFill(true);
  addPart(&lasso_circle);
  addPart(&lasso_loop);
  lasso_looped = false;
  the_coin = NULL;
  num_coins = 0;

  lasso_line.reset(lasso_start_x, lasso_start_y, lasso_start_x, lasso_start_y);
  lasso_line.setColor(COLOR(79,39,0));

  lasso_band.setColor(COLOR(79,39,0));
  draw_lasso_band();

} // End Lasso::initLasso()

void Lasso::yank()
{
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setFill(true);
  lasso_looped = false;
  if(the_coin != NULL) {
    num_coins++;
    the_coin->resetCoin();
    the_coin=NULL;
  }
} // End Lasso::yank()

void Lasso::loopit()
{
  if(lasso_looped) { return; } // Already looped
  lasso_loop.reset(getXPos(), getYPos(), LASSO_RADIUS);
  lasso_loop.setFill(false);
  lasso_looped = true;
} // End Lasso::loopit()

void Lasso::addAngle(double angle_deg)
{
  release_angle_deg += angle_deg;
  if(release_angle_deg < MIN_RELEASE_ANGLE_DEG) { release_angle_deg = MIN_RELEASE_ANGLE_DEG; }
  if(release_angle_deg > MAX_RELEASE_ANGLE_DEG) { release_angle_deg = MAX_RELEASE_ANGLE_DEG; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addAngle()

void Lasso::addSpeed(double speed) {
  release_speed += speed;
  if(release_speed < MIN_RELEASE_SPEED) { release_speed = MIN_RELEASE_SPEED; }
  if(release_speed > MAX_RELEASE_SPEED) { release_speed = MAX_RELEASE_SPEED; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addSpeed()

void Lasso::nextStep(double stepTime) {
  draw_lasso_band();
  MovingObject::nextStep(stepTime);
  if(getYPos() > PLAY_Y_HEIGHT) { yank(); }
  lasso_line.reset(lasso_start_x, lasso_start_y, getXPos(), getYPos());
} // End Lasso::nextStep()

void Lasso::check_for_coin(Coin *coinPtr)
{
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  double xdiff = (lasso_x - coin_x);
  double ydiff = (lasso_y - coin_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS)
  {
    the_coin = coinPtr;
    the_coin->getAttachedTo(this);
  }
} // End Lasso::check_for_coin()


main_program {

  initCanvas("Lasso", WINDOW_X, WINDOW_Y);
  Text heading1(WINDOW_X/2, -40+WINDOW_Y/2,"LASSO GAME");
  Text heading2(WINDOW_X/2, WINDOW_Y/2,"Hanan Basheer (20B030018)");
  Text heading3(WINDOW_X/2, 20+WINDOW_Y/2,"[IIT-B]");
  wait(5);
  heading1.moveTo(10000,10000);
  heading2.moveTo(10000,10000);
  heading3.moveTo(10000,10000);
  int level;
  Text heading4(WINDOW_X/2, -20+WINDOW_Y/2,"Enter level in console and press enter");
  Text heading5(WINDOW_X/2, WINDOW_Y/2,"Min. Level = 1  &  Max. Level = 10");
  Text heading7(WINDOW_X/2, 20+WINDOW_Y/2,"(Initial time = 10 mins & each increase in level decreases time by 1 min)");
  cout<<"Level : ";
  cin>>level;
  while(level<1 or level>10)
  {
    cout<<"Enter a VALID level : ";
    cin>>level;
  }
  heading4.moveTo(10000,10000);
  heading5.moveTo(10000,10000);
  heading7.moveTo(10000,10000);

  Text mode_selector(WINDOW_X/2, (WINDOW_Y/2)-100, "Select Mode :");
  Text mode_selector1((WINDOW_X/2)-50, (WINDOW_Y/2)-60, "a. Quick match [ALL Coins]");
  Text mode_selector2((WINDOW_X/2), (WINDOW_Y/2)-40, "b. Gold Rush [Gold Coins + Special Coins]");
  Text mode_selector3((WINDOW_X/2)+17, (WINDOW_Y/2)-20, "c. Battlefield [Gold Coins + Bombs + Life Coins]");
  Text mode_selector4((WINDOW_X/2)+86, (WINDOW_Y/2)-0, "d. Time Travel [Gold Coins + Special Coins + Speed Changing Coins]");
  Text mode_selector5((WINDOW_X/2)-7, (WINDOW_Y/2)+20, "e. DeathMatch [Gold Coins + Life Coins]");

  char mode='z';
  while(mode!='a' and mode!='b' and mode!='c' and mode!='d' and mode!='e')
  {
    cout<<"\n"<<"Mode : ";
    cin>>mode;
  }

  mode_selector.moveTo(10000,10000);
  mode_selector1.moveTo(10000,10000);
  mode_selector2.moveTo(10000,10000);
  mode_selector3.moveTo(10000,10000);
  mode_selector4.moveTo(10000,10000);
  mode_selector5.moveTo(10000,10000);

  switch(mode)
  {
    case 'a':
        pp21=0;
        pp22=3;
        pp31=4;
        pp32=9;
        pp41=10;
        pp42=13;
        pp51=14;
        pp52=17;
        pp61=18;
        pp62=20;
        break;

    case 'b':
        pp21=100;
        pp22=100;
        pp31=100;
        pp32=100;
        pp41=100;
        pp42=100;
        pp51=100;
        pp52=100;
        pp61=100;
        pp62=100;
        break;


    case 'c':
        pp21=100;
        pp22=100;
        pp31=0;
        pp32=10;
        pp41=100;
        pp42=100;
        pp51=100;
        pp52=100;
        pp61=11;
        pp62=20;
        break;

    case 'd':
        pp21=0;
        pp22=4;
        pp31=100;
        pp32=100;
        pp41=5;
        pp42=12;
        pp51=13;
        pp52=20;
        pp61=100;
        pp62=100;
        break;

    case 'e':
        pp21=100;
        pp22=100;
        pp31=100;
        pp32=100;
        pp41=100;
        pp42=100;
        pp51=100;
        pp52=100;
        pp61=0;
        pp62=29;
        break;

  }

  Text helper((WINDOW_X/2),(WINDOW_Y/2)-100,"Objects in Game");

  Circle coin_type1((WINDOW_X/2)-100,(WINDOW_Y/2)-60,5);
  coin_type1.setColor(COLOR(255,215,0));  //Golden Coin
  coin_type1.setFill(true);
  Text coins_type1((WINDOW_X/2),(WINDOW_Y/2)-60,"Gold Coin [+15 points]");

  Circle coin_type2((WINDOW_X/2)-100,(WINDOW_Y/2)-40,5);
  coin_type2.setColor(COLOR(149,71,182));  //Special Coin
  coin_type2.setFill(true);
  Text coins_type2((WINDOW_X/2)+5,(WINDOW_Y/2)-40,"Bonus coin [+30 points]");

  Circle coin_type3((WINDOW_X/2)-100,(WINDOW_Y/2)-20,5);
  coin_type3.setColor(COLOR(0,0,0));  //Bomb
  coin_type3.setFill(true);
  Text coins_type3((WINDOW_X/2)+10,(WINDOW_Y/2)-20,"Bomb [-5 points & -1 Life]");

  Circle coin_type4((WINDOW_X/2)-100,(WINDOW_Y/2)+0,5);
  coin_type4.setColor(COLOR(255,128,0));  //Speed_up coin
  coin_type4.setFill(true);
  Text coins_type4((WINDOW_X/2)+27,(WINDOW_Y/2)+0,"Speed-Up [+1 Speed-Up Token]");

  Circle coin_type5((WINDOW_X/2)-100,(WINDOW_Y/2)+20,5);
  coin_type5.setColor(COLOR(0,255,255));  //Slow_down coin
  coin_type5.setFill(true);
  Text coins_type5((WINDOW_X/2)-2,(WINDOW_Y/2)+20,"Slow-Down [-1 Speed]");

  Circle coin_type6((WINDOW_X/2)-100,(WINDOW_Y/2)+40,5);
  coin_type6.setColor(COLOR(255,0,0));  //Life coin
  coin_type6.setFill(true);
  Text coins_type6((WINDOW_X/2)+53,(WINDOW_Y/2)+40,"Life token [If missed, reduces life by 1]");

  wait(5);

  Text helper2((WINDOW_X/2),(WINDOW_Y/2)+100,"Press LMB to start the game");
  int helper_input;
  helper_input=getClick();

  helper.moveTo(10000,10000);
  helper2.moveTo(10000,10000);
  coins_type1.moveTo(10000,10000);
  coins_type2.moveTo(10000,10000);
  coins_type3.moveTo(10000,10000);
  coins_type4.moveTo(10000,10000);
  coins_type5.moveTo(10000,10000);
  coins_type6.moveTo(10000,10000);

  int stepCount = 0;
  float stepTime = STEP_TIME;
  float runTime = 660-(60*level); // sec; -ve means infinite
  float currTime = 0;
  int type_before=1;

  coin_type1.moveTo(15,100);
  Text coin_typer1(55,100,"Gold Coin");

  coin_type2.moveTo(15,120);
  Text coin_typer2(58,120,"Bonus Coin");

  coin_type3.moveTo(15,140);
  Text coin_typer3(55,140,"Bomb");

  coin_type4.moveTo(15,160);
  Text coin_typer4(57,160,"Speed-Up");

  coin_type5.moveTo(15,180);
  Text coin_typer5(57,180,"Slow-Down");

  coin_type6.moveTo(15,200);
  Text coin_typer6(55,200,"Life coin");

  // Draw lasso at start position
  double release_speed = INIT_RELEASE_SPEED; // m/s
  double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  bool paused = true;
  bool rtheta = true;
  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

  Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
  b1.setColor(COLOR("blue"));
  Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
  b2.setColor(COLOR("blue"));

  string msg("Cmd: _");
  Text charPressed(PLAY_X_START+50, PLAY_Y_HEIGHT+20, msg);
  char coinScoreStr[256];
  sprintf(coinScoreStr, "Points : %d", points);
  Text coinScore(PLAY_X_START+50, PLAY_Y_HEIGHT+50, coinScoreStr);

  paused = true; rtheta = true;
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  double coin_ax = 0;
  double coin_ay = COIN_G;
  Coin coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);

  // After every COIN_GAP sec, make the coin jump
  double last_coin_jump_end = 0;
  int coins_before=0;

  // When t is pressed, throw lasso
  // If lasso within range, make coin stick
  // When y is pressed, yank lasso
  // When l is pressed, loop lasso
  // When q is pressed, quit

  Text time1(WINDOW_X-123,20,"Time left :");
  Text time3(WINDOW_X-40,20,"sec");
  Text speeds(WINDOW_X-250,20,"Speed-Up points : ");
  Text lifes(WINDOW_X-60,60,"Lives : ");
  Rectangle RecTime(WINDOW_X-90,20,140,30);
  Rectangle RecSpeeds(WINDOW_X-245,20,140,30);
  Rectangle Reclifes(WINDOW_X-57,60,70,30);
  RecSpeeds.setColor(COLOR("green"));
  RecTime.setColor(COLOR("red"));
  Text help_display(45,WINDOW_Y-65,"For help,");
  Text help_display2(45,WINDOW_Y-45,"Press 'h'");

  int help_pause=1;

  for(;;) {

    Text time2(WINDOW_X-70,20,runTime-currTime);
    Text speeds2(WINDOW_X-185,20,speed_up);
    Text lifes2(WINDOW_X-35,60,life);

    if(help_pause<0)
    {
        cout<<"------------------------------------ Guide ------------------------------------"<<"\n"<<"\n";
        cout<<"1. Game aim : Collect coins using Lasso."<<"\n"<<"\n";
        cout<<"2. Lasso controls :"<<"\n";
        cout<<"   a] Throw Lasso - Press 't'"<<"\n";
        cout<<"   b] Loop Lasso - Press 'l'"<<"\n";
        cout<<"   c] Yank Lasso - Press 'y'"<<"\n";
        cout<<"   d] Increase Lasso speed - Press '=' (If you have atleast 1 speed-Up token)"<<"\n";
        cout<<"   e] Decrease Lasso speed - Press '-'"<<"\n";
        cout<<"   f] Rotate Lasso clockswise - Press ']'"<<"\n";
        cout<<"   g] Rotate Lasso anti-clockswise - Press '['"<<"\n"<<"\n";
        cout<<"Note : To collect coin, Loop the Lasso when coin is near and then yank it."<<"\n"<<"\n";
        cout<<"3. Types of coins :"<<"\n";
        cout<<"   a] Gold Coin (+15 points) - Golden "<<"\n";
        cout<<"   b] Bonus coin (+30 points) - Purple"<<"\n";
        cout<<"   c] Bomb (-5 points & -1 Life) - Black"<<"\n";
        cout<<"   d] Speed-Up (+1 Speed-Up Token) - Orange"<<"\n";
        cout<<"   e] Slow-Down (-1 Speed) - Cyan"<<"\n";
        cout<<"   f] Life token (If missed, reduces life by 1) - Red"<<"\n"<<"\n";
        cout<<"4. Time is displayed on top-right."<<"\n";
        cout<<"5. Speed-Up coin provides 1 speed up token which can be used to increase speed by 1 unit."<<"\n";
        cout<<"6. Speed-Down coin reduces coin speed by 1 unit."<<"\n";
        cout<<"7. To quit the game, Press 'q'"<<"\n"<<"\n";
        cout<<"Game will continue after 30 sec automatically";

        wait(30);
        help_pause=1;
    }
    if((runTime > 0) && (currTime > runTime)) { break; }

    XEvent e;
    bool pendingEv = checkEvent(e);

    if(pendingEv) {
      char c = charFromEvent(e);
      msg[msg.length()-1] = c;
      charPressed.setMessage(msg);
      switch(c) {
      case 't':
	lasso.unpause();
	break;
      case 'y':
    type_before=coin.type;
    coins_before=lasso.getNumCoins();
	lasso.yank();
	if(type_before==0 and lasso.getNumCoins()-coins_before==1)
    {
        points-=5;
        life-=1;
    }

    if(type_before==1 and lasso.getNumCoins()-coins_before==1)
    {
        points+=15;
    }

    if(type_before==2 and lasso.getNumCoins()-coins_before==1)
    {
        points+=30;
    }

    if(type_before==3 and lasso.getNumCoins()-coins_before==1)
    {
        speed_up+=1;
    }

    if(type_before==4 and lasso.getNumCoins()-coins_before==1)
    {
        slow_down+=1;
    }

    if(type_before==5 and lasso.getNumCoins()-coins_before==1)
    {
        points+=5;
    }

	break;
      case 'l':
	lasso.loopit();
	lasso.check_for_coin(&coin);
	wait(STEP_TIME*5);
	break;
      case '[':
	if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
	break;
      case ']':
	if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
	break;
      case '-':
	if(lasso.isPaused()) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
	break;
      case '=':
	if(lasso.isPaused() and speed_up>0) { lasso.addSpeed(+RELEASE_SPEED_STEP); speed_up-=1; }
	break;
      case 'h':
    help_pause=-1;
    break;
      case 'q':
	exit(0);
      default:
	break;
      }
    }

    if(life==0)
    {
        exit(0);
    }

    while(slow_down>0 and lasso.isPaused())
    {
        lasso.addSpeed(-RELEASE_SPEED_STEP);
        slow_down-=1;
    }

    lasso.nextStep(stepTime);
    coin.nextStep(stepTime);

    if(coin.isPaused())
    {
        if((currTime-last_coin_jump_end) >= COIN_GAP)
        {
            coin.unpause();
        }
    }

    if(coin.getYPos() > PLAY_Y_HEIGHT)
    {
        if(coin.type==5)
        {
            life-=1;
        }
        type=coin.resetCoin();
        last_coin_jump_end = currTime;
    }

    sprintf(coinScoreStr, "Points : %d", points);
    coinScore.setMessage(coinScoreStr);

    stepCount++;
    currTime += stepTime;
    wait(stepTime);
  } // End for(;;)
  Text heading6(WINDOW_X/2, WINDOW_Y/2,"GAME OVER");
  wait(5);
} // End main_program
