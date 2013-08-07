#include <allegro.h>
#include <vector>
#include <string>

using namespace std;

void init();
void deinit();

int main() {
	init();
    int panning = 128;
    int pitch = 1000;
    int volume = 128;
    show_os_cursor(1);
    
    srand(time(0));
    MIDI* songs[3];
    songs[0] = load_midi("3_doors_down-here_without_you.mid");
    songs[1] = load_midi("survivor-eye_of_the_tiger.mid");
    songs[2] = load_midi("david_guetta-sexy_bitch_feat_akon.mid");
    SAMPLE *right_wav;
    SAMPLE *wrong_wav;
    right_wav = load_sample("cashtill.wav");
    wrong_wav = load_sample("electric.wav");
    //if (!music)
    //     abort_on_error("Couldn't load background music!");
    //play_looped_midi(music, 81, 85);
    play_midi(songs[1],1);
	char guessed[26]={0};
	int word = 0;
	int score = 0, level = 1;
	
    vector<string> words;
    words.push_back("GUESS");
    words.push_back("HANGMAN");
    words.push_back("DIFFICULT");
    words.push_back("THE GAME");
    words.push_back("SQUIRLE");
    words.push_back("SPHINX");
    words.push_back("TURTLE");
    words.push_back("RAY");
    words.push_back("CAN'T");
    words.push_back("SHE'S");
    words.push_back("WANT");
    words.push_back("ZOO");
    words.push_back("ATTACK");
    words.push_back("PENGUIN");
    words.push_back("LION");
    words.push_back("BLUE");
    words.push_back("SPARK");
    words.push_back("SCREWDRIVER");
    words.push_back("CLOTHES");
    words.push_back("MAN");
    words.push_back("FLASK");
    words.push_back("CLASS");
    words.push_back("MONSTER");
    words.push_back("CRAB");
    words.push_back("POOL");
    words.push_back("LAST");
    words.push_back("GOOFY");
    words.push_back("MOUSE");
    words.push_back("GOOD GUESS");
    words.push_back("THE WORD");
    words.push_back("WORLD DOMINATION");
    words.push_back("DOG ATTACK");
    words.push_back("MAKE-UP");
    words.push_back("WORLDLY");
    words.push_back("BLACK");
    words.push_back("IPHONE");
    words.push_back("CAMERA");
    words.push_back("SWEETS");
    words.push_back("COMPLEX");
    words.push_back("MANNER");
    
    random_shuffle(words.begin(), words.end());
    bool won = false;
    
    string THE_WORD = words[0];
    
    int wrong = 0; 
    int numguesses = 0;
    BITMAP* buffer = create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP* hangman[7];
    hangman[0] = load_bitmap("base.bmp",NULL);
    hangman[1] = load_bitmap("1.bmp",NULL);
    hangman[2] = load_bitmap("2.bmp",NULL);
    hangman[3] = load_bitmap("3.bmp",NULL);
    hangman[4] = load_bitmap("4.bmp",NULL);
    hangman[5] = load_bitmap("5.bmp",NULL);
    hangman[6] = load_bitmap("6.bmp",NULL);
    
    BITMAP* end_screen[2];
    end_screen[0] = load_bitmap("spacecowboy1.bmp",NULL);
    end_screen[1] = load_bitmap("spacecowboy2.bmp",NULL);
    
    
    char s[20];
    BITMAP *kitty[7];
    for (int n=0; n<6; n++)
    {
        sprintf(s,"cat%d.bmp",n+1);
        kitty[n] = load_bitmap(s, NULL);
    }
    int x = -100;
    int y = SCREEN_H-100;
    int curr = 0;
    
    int cowboy_x = -127;
    int next = 0;
    
    clear_to_color(buffer,0);
    int last_button_pressed = 0;
    
    
	while (!key[KEY_ESC]) 
    {
       clear_to_color(buffer,makecol(199,133,33));
       if(last_button_pressed == 1)
       {
            if(curr == 5)
                curr = 0;
            else
                curr++;
            if(x>=SCREEN_W)
                x = -100;
            else
                x += 5;
            rest(40);
            draw_sprite(buffer, kitty[curr], x, y);
            int b_button_x=SCREEN_W-120,b_button_y=SCREEN_H-150,b_button_w=100,b_button_h=50;
            if(mouse_x>=b_button_x&&mouse_x<=b_button_x+b_button_w&&mouse_y>=b_button_y&&mouse_y<=b_button_y+b_button_h)
    	    {
                rectfill(buffer,b_button_x,b_button_y,b_button_x+b_button_w,b_button_y+b_button_h,makecol(0,255,0));
                if(mouse_b == 1)
                {
                    last_button_pressed = 0;
                    while(mouse_b == 1);
                } 
            }
            else
    	        rectfill(buffer,b_button_x,b_button_y,b_button_x+b_button_w,b_button_y+b_button_h,makecol(255,0,0));
    	    textout_centre_ex(buffer,font,"Menu",SCREEN_W-70,SCREEN_H-125,makecol(255,255,255),-1);
            if(won == false)
            {
                
                if(wrong<=5)
                {
                    textprintf_ex(buffer,font,SCREEN_W-100,3,makecol(255,255,255),-1,"Score: %i",score);
                    blit(hangman[wrong],buffer,0,0,25,50,100,350);

                    if(keypressed())
                    {
                        
                        int key_p = readkey();
                        key_p = key_p>>8;
                        char guess = toupper((char)(scancode_to_ascii(key_p)));
                        if(key_p != 0&&guess>='A'&&guess<='Z')
                        {
                            bool already_picked = false;
                            for(int i = 0;i<26;i++)
                            {
                                if(guessed[i]==guess)
                                    already_picked = true;
                            }    
                            if(!already_picked)
                            {    
                                guessed[numguesses] = guess;
                                numguesses++;
                                bool inc_wrong = true;
                                for(int i = 0;i<THE_WORD.length();i++)
                                {
                                     if(toupper(THE_WORD[i])==guess)
                                     {
                                            inc_wrong = false;
                                    }
                                          
                                }
                                if(inc_wrong)
                                {
                                     wrong++;
                                     play_sample(wrong_wav, volume, panning, pitch, FALSE);

                                }
                                else
                                    play_sample(right_wav, volume, panning, pitch, FALSE);

                            }
                            
                        }
                    }
                    for(int i = 0;i<26;i++)
                    {
                        textprintf_ex(buffer,font,300+(10*(i%6)),100+(10*(i/6)),makecol(255,255,255),-1,"%c",guessed[i]);
                    }
                    int correct = 0;
                    for(int i = 0;i<THE_WORD.length();i++)
                    {
                            bool disp_letter = false;
                            for(int j = 0;j<26;j++)
                            {
                                 char guess = toupper(guessed[j]); 
                                 if(toupper(THE_WORD[i])==guess)
                                       disp_letter = true;
                            }
                            
                            if(toupper(THE_WORD[i])<'A'||toupper(THE_WORD[i])>'Z')
                                 disp_letter=true;
                            if(disp_letter)
                            {
                                textprintf_ex(buffer,font,300+(10*i),200,makecol(255,255,255),-1,"%c",toupper(THE_WORD[i]));
                                correct++;
                            }
                            else
                                 textprintf_ex(buffer,font,300+(10*i),200,makecol(255,255,255),-1,"_");
                    
                                 
                    }
                    if(correct == THE_WORD.length())
                    {
                        won = true;
                    }
                }
                else 
                {
                    next = !next;
                    cowboy_x+=4;
                    if(cowboy_x >= SCREEN_W)
                        cowboy_x=-127;
                    rest(10);
                    draw_sprite(buffer,end_screen[next], cowboy_x, 0);
                    textout_centre_ex(buffer,font,"You lose",SCREEN_W/2,SCREEN_H/2-5,makecol(255,255,255),-1);
                    textprintf_centre_ex(buffer,font,SCREEN_W/2,SCREEN_H/2+5,makecol(255,255,255),-1,"Your Score:%i",score);
                    textprintf_centre_ex(buffer,font,SCREEN_W/2,SCREEN_H/2+15,makecol(255,255,255),-1,"The word was: %s",THE_WORD.c_str());
                }
            }
            else
            {
                rest(1000);
                if(word+1<words.size())
                {
                    word++;
                    score += 5*level*(numguesses-wrong);
                    won = false;
                    for(int i = 0;i<26;i++)
                    {
                        guessed[i]=0;
                    }
                    
                    THE_WORD = words[word];
                    numguesses = 0;
                    wrong = 0;
                    level++;
                    
                }
                else
                {
                    textout_centre_ex(buffer,font,"You Win",SCREEN_W/2,SCREEN_H/2-5,makecol(255,255,255),-1);
                    textprintf_centre_ex(buffer,font,SCREEN_W/2,SCREEN_H/2+5,makecol(255,255,255),-1,"Your Score:%i",score+5*level*(numguesses-wrong));
                }
            }
                    
       }
       else if(last_button_pressed == 2)
       {
            score = 0;
            won = false;
            for(int i = 0;i<26;i++)
            {
                guessed[i]=0;
            }
            random_shuffle(words.begin(), words.end());
            THE_WORD = words[0];
            wrong = 0;
            level = 1;
            numguesses = 0;
            word = 0;
            textout_centre_ex(buffer,font,"Game Reset",SCREEN_W/2,SCREEN_H/2-5,makecol(255,255,255),-1);
            int b_button_x=SCREEN_W-120,b_button_y=SCREEN_H-75,b_button_w=100,b_button_h=50;
    	    if(mouse_x>=b_button_x&&mouse_x<=b_button_x+b_button_w&&mouse_y>=b_button_y&&mouse_y<=b_button_y+b_button_h)
    	    {
                rectfill(buffer,b_button_x,b_button_y,b_button_x+b_button_w,b_button_y+b_button_h,makecol(0,255,0));
                if(mouse_b == 1)
                {
                     last_button_pressed = 0;
                     while(mouse_b == 1);
                } 
            }
            else
    	        rectfill(buffer,b_button_x,b_button_y,b_button_x+b_button_w,b_button_y+b_button_h,makecol(255,0,0));
    	    textout_centre_ex(buffer,font,"Menu",SCREEN_W-70,SCREEN_H-50,makecol(255,255,255),-1);
       
       }
       else
       {
    	   //textprintf_ex(buffer,font,20,20,makecol(255,255,255),-1,"%i %i %i %i %i",mouse_x,mouse_y,mouse_z,mouse_b,mouse_pos);
    	   //textprintf_ex(buffer,font,120,120,makecol(255,255,255),-1,"last Button Pressed was %i",last_button_pressed);
    	   
    
        	   
           int p_button_x=SCREEN_W-120,p_button_y=SCREEN_H-75,p_button_w=100,p_button_h=50;
    	   if(mouse_x>=p_button_x&&mouse_x<=p_button_x+p_button_w&&mouse_y>=p_button_y&&mouse_y<=p_button_y+p_button_h)
    	   {
               rectfill(buffer,p_button_x,p_button_y,p_button_x+p_button_w,p_button_y+p_button_h,makecol(0,255,0));
               if(mouse_b == 1)
               {
                    last_button_pressed = 1;
                    while(mouse_b == 1);
                }
           }
           else
    	        rectfill(buffer,p_button_x,p_button_y,p_button_x+p_button_w,p_button_y+p_button_h,makecol(255,0,0));
    	   int s_button_x=SCREEN_W-120,s_button_y=SCREEN_H-150,s_button_w=100,s_button_h=50;
    	   if(mouse_x>=s_button_x&&mouse_x<=s_button_x+s_button_w&&mouse_y>=s_button_y&&mouse_y<=s_button_y+s_button_h)
    	   {
                rectfill(buffer,s_button_x,s_button_y,s_button_x+s_button_w,s_button_y+s_button_h,makecol(0,255,0));
    	        if(mouse_b == 1)
                {
                    last_button_pressed = 2;
                    while(mouse_b == 1);
                }
           }
           else
    	       rectfill(buffer,s_button_x,s_button_y,s_button_x+s_button_w,s_button_y+s_button_h,makecol(255,0,0));
           textout_centre_ex(buffer,font,"Reset Game",SCREEN_W-70,SCREEN_H-125,makecol(255,255,255),-1);
           textout_centre_ex(buffer,font,"Start",SCREEN_W-70,SCREEN_H-50,makecol(255,255,255),-1);
      
       }	   
       blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }

	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	//depth = desktop_color_depth();
	//if (depth == 0)
    //depth = 32;
	//set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}
    
	install_timer();
	install_keyboard();
	install_mouse();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT,"");
	/* add other initializations here */
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}
