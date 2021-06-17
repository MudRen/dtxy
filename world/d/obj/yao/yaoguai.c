inherit NPC;
inherit __DIR__"yaoguai_reward.c";

#include <ansi.h>
#include <zhuanshi.h>

#define SHILI_D "/adm/daemons/shili"

string _invocation(object who, int level, string loc);
int exp_reward, pot_reward;
int other_kee=0, other_sen=0;

string *death_msg= ({
HIB"\n$n���һ�����������Ӯ�ˣ��´����������ơ�������\n$n˵�꣬����һ����⣬ֱ������ȥ�ˣ�����\n"NOR,
HIY"\n$N�ȵ��������ߣ�\n$n�޿��κΣ�������һ�꣬����ʧ�ˡ�\n"NOR,
WHT"\n$n�ҽ�һ�������ˡ�\n"NOR,
});

int random_place(object me, string loc);
int strength();
void leave();

int cast_chance(int level) 
{
    return 10+level/2;
}

// here should be this NPC specific skills.
void set_skills(int j, int level)
{
}

void copy_status(object me,object ob, int lv)
{
        int j, lvl;

        int base=20;

        mapping skill=ob->query_skills();
        int i=sizeof(skill);
        string* key;
        int max_level;
        int max_sen, max_kee;

        lvl=lv+base-2;
        
            if(i>0) {
                key=keys(skill);
                max_level=skill[key[0]];
                while(i--) { // find out victim's maximum level
                    if(skill[key[i]]>max_level&&key[i]!="literate")
                        max_level=skill[key[i]];
                }
                max_level=max_level*lvl/base;

            } else max_level=1;

       //max_sen=ob->query("max_sen")*(1000+max_level)/1000;
       //  max_kee=ob->query("max_kee")*(200+max_level)/200;
	max_sen=(max_level+ob->query("max_sen"))*lvl/10;
        max_kee=(ob->query("max_kee")+max_level)*lvl/10;
        if( ob->query("combat_exp") < 100000 )
        {
        	max_sen = max_sen/2;
        	max_kee = max_kee/2;
        }
            // skill level will be set to the maximum level
            // of the player.
            set("eff_sen",max_sen);
            set("eff_kee",max_kee);
            set("sen",max_sen);
            set("kee",max_kee);
            set("max_sen",max_sen);
            set("max_kee",max_kee);
            
             max_kee=ob->query("max_force");
             max_sen=ob->query("max_mana");
            set("max_force",max_kee);
            set("force",max_kee);
            set("force_factor",max_kee/50);
            set("max_mana",max_sen);
            set("mana",max_sen);
            set("mana_factor",max_sen/50);
        set("combat_exp",ob->query("combat_exp")/20*lvl);
        set("daoxing",ob->query("daoxing")/20*lvl);    
            set_skills(max_level, lv);
}

int random_place(object me, string loc)
{
        int  j, k;
        object  newob;
        mixed*  file, exit;

        file = get_dir( loc+"/*.c", -1 );
        if( !sizeof(file) )             return 1;

        for(k=0;k<30;k++) { // try 20 times
           j = random(sizeof(file));
           if( file[j][1] > 0 ) {
             newob=load_object(loc+"/"+file[j][0]);
             if (newob) {  
               if(newob->query("no_fight") ||
                       newob->query("no_magic") ||
                       newob->query("alternative_die") ||
                       !(exit=newob->query("exits")) ||
                       sizeof(exit)<1)
                   continue;

               if(me->move(newob)) {
                   message_vision("$N���˹�����\n",me);
                   return 1;
               }
             }
           }
        }

        return 0;
}

void leave()
{
      if(this_object()) { 
        if(environment())
          message("vision",HIB + name() + 
                  "����һ�Σ����һ������ɢȥ�ˡ�\n" NOR,environment());
        destruct(this_object());
      }
      return;
}

string invocation(object who, int level,string loc)
{
        object me=this_object();

        copy_status(me,who, level);
        //carry_object("/d/obj/armor/yinjia")->wear();
        
        return _invocation(who, level, loc);
}

string _invocation(object who, int level,string loc)
{       object me=this_object(), env;
        string *dirs; 
        int dx, i, lvl, base;
        int exp;
        string where, guainame,title;
        title="";
        
        set("owner", who->query("id"));
        set("owner_ob", who);

        dx=me->query("combat_exp");
        if(dx>=100000000)
        title=title+HIW"�ϲ���"NOR;    
        else if(dx>=10000000)
        title=title+HIY"����"NOR;
        else if(dx>=1000000)
        title=title+HIW"ǧ��"NOR;
        else if(dx>=100000)
        title=title+HIB"����"NOR;
        else if(dx>10000)
        title=title+WHT"ʮ��"NOR;
        else
        title=title+MAG"СС"NOR;
            
            set("title",title);

        lvl=level;
        
        if(random(10)==0) {
            set("env/wimpy",40);
            if(lvl<9) lvl=lvl+1; // as more difficult to kill.
        } else {
            set("env/wimpy",1);
        }

        // determine reward
        exp=who->query("daoxing");
				exp += (zs_getSpentExp(who->query("lunhui_zhuanshi"))+zs_getSpentDx(who->query("lunhui_zhuanshi")))/2;
        
        /*if(exp<30000) {
            exp_reward=80+exp/60;
            pot_reward=30+exp/300;
        } else if(exp<300000) {
            exp_reward=180+exp/600;
            pot_reward=40+exp/6000;
        } else if(exp<3000000) {
            exp_reward=230+exp/6000;
            pot_reward=50+exp/60000;
        } else {
            exp_reward=280+random(500);
            pot_reward=70+random(100);
        }*/
        if(exp<100000) {
	    exp_reward=400+exp/500;
	    pot_reward=100+exp/1000;
	    base = 1;
	} else if(exp<1000000) {
	    exp_reward=600+exp/5000;
	    pot_reward=200+exp/10000;
	    base = 10;
	} else if(exp<10000000) {
	    exp_reward=800+exp/50000;
	    pot_reward=300+exp/100000;
	    base = 40;
	} else if(exp<100000000) {
	    exp_reward=1000+exp/100000;
	    pot_reward=400+exp/1000000;
	    base = 80;
	} else {
	    exp_reward=2000;
	    pot_reward=500;
	    base = 120;
	}
	add_temp("apply/damage",base*(lvl+1)/3);
	add_temp("apply/armor",base*(lvl+1));
        pot_reward=pot_reward*(lvl+1)/20;
        exp_reward=exp_reward*(lvl+1)/20;

        me->set("stay_time", time()+600);
        //who->set("mieyao_time",time());

        if(!random_place(me, loc)) {
            leave();
            return 0;
        }
        
        env=environment(me);
        guainame=me->query("name")+"("+me->query("id")+")";
        where=guainame;
        if(env)
          where+="��"+SHILI_D->query_chinese(query("pos"));
        return where;
}

void unconcious()
{
  die();
}

void die()
{
        string owner;
        string skill;
        object owner_ob;
        object me=this_object();
        string msg,str;
        int max_kee, max_sen, ratio, exp_r, pot_r, dx_r;

        owner = query("owner");
	max_kee=query("max_kee");
        max_sen=query("max_sen");
        ratio=100*(max_kee-other_kee)/max_kee;
        if(ratio<0) ratio=0;
        ratio=ratio*(max_sen-other_sen)/max_sen;
        if(ratio<0) ratio=0;
        ratio=ratio*(2+query("bian_num"))/2;

	dx_r=exp_reward*ratio/100;
        pot_r=pot_reward*ratio/100;
        exp_r=exp_reward*ratio/150;
        
        if( stringp(owner) && objectp(owner_ob = find_player(owner)) ) {
            if(environment(owner_ob)==environment() && living(owner_ob)) {
              message_vision(death_msg[random(sizeof(death_msg))],owner_ob,this_object());
            } else {
                message_vision("$N���ˡ�\n",this_object());
                exp_r = 0;
                pot_r = 0;
                dx_r = 0;
            }
 	//owner_ob->delete("mieyao");
 	//str=owner_ob->name()+" got "+exp_r+"/"+exp_reward+" dx "+
	//		pot_r+"/"+pot_reward+" pot "+
	//		" in level "+ owner_ob->query_temp("mieyao/level2")+
	//		".\n";
        owner_ob->set("mieyao/done2",1);
	//owner_ob->add("daoxing",exp_r);
        //owner_ob->add("potential",pot_r);
        owner_ob->add("faith",ratio/100);
        
        owner_ob->add("combat_exp",exp_r);
	owner_ob->add("potential",pot_r);
        owner_ob->add("daoxing",dx_r);
        owner_ob->add("balance",10000);
	
    	SHILI_D->increase_shili(query("pos"),owner_ob->query("family/family_name"),1);
                    
         if (owner_ob->query_temp("mieyao/level2")>=9) {
          skill=give_reward(owner_ob);
                 if(skill != "none"){
                 	//str+= "and rewarded 1 lvl of "+skill+".\n";
			msg="��˵"+ owner_ob->query("name")+ "��"+ to_chinese(skill)+ "�����������ˣ�\n";
     			CHANNEL_D->do_channel(me,"rumor",msg);
    			}
          }
	//MONITOR_D->report_system_msg(str);
        //  tell_object(owner_ob, RED"\n��õ���"+COMBAT_D->chinese_daoxing(exp_r)+"���к�"+chinese_number(pot_r)+"��Ǳ�ܣ�\n"NOR);
        tell_object(owner_ob, "��õ���"+chinese_number(exp_r)
		+"����ѧ�����"+chinese_number(pot_r)+
		"��Ǳ�ܡ�"+COMBAT_D->chinese_daoxing(dx_r)+"����!\n");
       } else {
            message_vision("$N���ˡ�\n",this_object());
       }

    destruct(this_object());

}


// This is called in heart_beat() to perform attack action.
int attack()
{
        object opponent;

        clean_up_enemy();

        opponent = select_opponent();
        if( objectp(opponent) ) {
                string owner=query("owner");
                
                // if the owner faints, then will not attack
                // and leave. -- mon 3/8/99
                if(opponent->query("id")==owner 
                        && userp(opponent)
                        && !living(opponent)
                        && environment()==environment(opponent)) {
                    call_out("leave",1);
                    return 0;
                }

                set_temp("last_opponent", opponent);
                COMBAT_D->fight(this_object(), opponent);
                return 1;
        } else
                return 0;
}

int accept_fight(object me)
{
     kill_ob(me);     
     return 1;
}
void init()
{
    object me=this_object();
    object who=this_player();
    string type;
    object *bianobj;
    string npcid;
    int t;
    object env=environment(me);
    if(!random(5)&&time()>query("stay_time")&&!is_fighting())
        leave();
    if( env && random(20) == 1 ) random_move();
    remove_call_out("check_room");
    call_out("check_room",2);
}
void check_room()
{
    object me=this_object();
    object env=environment(me);
    if(!living(me)) return;
    if(env && (env->query("no_fight") ||
           env->query("no_magic"))) {
        random_move();
    }
    
}
/*int heal_up()
{
    object weapon;
 
    if(!random(5)&&time()>query("stay_time")&&!is_fighting())
        leave();
//        check_room();

      if(!random(3)&&!query_temp("weapon")&&query("weapon_")){
     weapon=new(query("weapon_"));
     weapon->move(this_object());
     command("wield all");
    }
    return ::heal_up()+1;
}*/

int strength()
{
    string* ycolor=({NOR,BLK,RED,YEL,BLU,MAG,CYN,WHT,HIR,HIG,
      HIY,HIB,HIM,HIC,HIW});   
    int i;  
      
    if(!random(2)&&is_fighting()&&query("kee")*100/query("max_kee")<50){
         tell_room(environment(),query("name")+"�����У�"+RED+"�ϲԴ���������"+NOR+"\nת�۱�þ�����������\n");
         i=query("bian_num")+1;
         set("bian_num",i);
         if(i==sizeof(ycolor))i=1;
         set("name",ycolor[i]+query("name")+NOR);
         set("eff_kee",query("max_kee"));                       
         set("eff_sen",query("max_sen"));
         set("kee",query("max_kee"));
         set("sen",query("max_sen"));
         set("force",query("max_force")*(60+i)/50);
         set("mana",query("max_mana")*(60+i)/50);
         set("force_factor",query("max_force")*(i+4)/200);
         set("mana_factor",query("max_mana")*(i+4)/200);          
    }     
}

varargs int receive_wound(string type, int damage, object who)
{
    string owner=query("owner");
    
    if(who && who->query("id")!=owner && userp(who)) {
        if(damage>0) {
            switch(type) {
                case "kee": other_kee+=damage; break;
                case "sen": other_sen+=damage; break;
            }
        }
    }
    return ::receive_wound(type, damage, who);
}

varargs int receive_damage(string type, int damage, object who)
{
    string owner=query("owner");
    
    if(who && who->query("id")!=owner && userp(who)) {
        if(damage>0) {
            switch(type) {
                case "kee": other_kee+=damage; break;
                case "sen": other_sen+=damage; break;
            }
        }
    }
    return ::receive_damage(type, damage, who);
}
