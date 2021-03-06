//Changed by Start DHXY

#include <ansi.h>
inherit NPC;
string ask_for_leave();

void create()
{
        set_name(HIW"转世轮回菩萨"NOR, ({"lunhui pusa","pusa"}));
        set("gender", "女性" );
        set("age", 25);
        set("title",HIY"眼望世间虚缈，空、无、灭"NOR);
        set("long", HIG"\n\n佛祖如来身边掌管转世轮回的大智、无我菩萨\n\n"NOR);
        set("combat_exp", 10);
        set("daoxing", 10);

        set("attitude", "peaceful");
        set("per", 40);
        set("max_kee", 20000);
        set("max_gin", 20000);
        set("max_sen", 20000);
        set("inquiry", ([
                "轮回转世" : (: ask_for_leave :),
                "投胎" : (: ask_for_leave :),
                ]) );
        setup();
        carry_object("/d/ourhome/obj/pink_cloth")->wear();
        carry_object("/d/ourhome/obj/shoes")->wear();
}

void init()
{
        add_action("do_agree", "agree");
}

string ask_for_leave()
{
        object me=this_player();
        int zslev = me->query("lunhui_zhuanshi");
        int i,level;
        mapping skill;
        string *skillnames;

	if ( (int)me->query("lunhui_zhuanshi") >= 5 )
        	return HIM"只能转世5次！\n"NOR;
        if ( (int)me->query("combat_exp") < 11000000 + zslev * 10000000 )
        	return HIW"你的武学还不够，在100W武学、一千年道行后，每一千万武学、一万年道行可以转世一次！\n"NOR;
        if ( (int)me->query("daoxing") < 11000000 + zslev * 10000000 )
                return HIM"你的道行还不够，在100W武学、一千年道行后，每一千万武学、一万年道行可以转世一次！\n"NOR;
        if ( (int)me->query("obstacle/number") < 26)
                return HIM"你先去取经完了再来转世吧！\n"NOR;
         if (!me->query("obstacle/reward"))
             return HIM"要了取经的奖励再来转世吧！\n"NOR;
        if ( (int)me->query("dntg/number") < 10)
                return HIM"你还没去天庭大闹天宫怎么能来转世！\n"NOR;
        if ( (int)me->query("12gong/number") < 12)
                return HIM"你还没闯过黄金12宫怎么能来转世！\n"NOR;
        /*if ( (int)me->query("mingjie/number") < 15)
                return HIM"你还没闯过冥界怎么能来转世！\n"NOR;
        if ( (int)me->query("9sky/number") < 9)
                return HIM"你还没闯过九重天怎么能来转世！\n"NOR;
        */
	if ( (int)me->query_skill("literate", 1) >= 400 + (zslev*100)
		&& (int)me->query_skill("parry", 1) >= 400 + (zslev*100)
		&& (int)me->query_skill("force", 1) >= 400 + (zslev*100)
		&& (int)me->query_skill("spells", 1) >= 400 + (zslev*100)
		&& (int)me->query_skill("dodge", 1) >= 400+ (zslev*100) )
	{
                me->set_temp("c_lunhui", 2);
                return HIR"你可思虑过？轮回转世不可儿戏，你苦练已久的武功和情感方面都要放弃。沧海桑田，无望无我，你可愿意抛弃你的一切的一切，破红尘，忘自我，离师判门，你愿意否(agree)？"NOR;
        }
        return HIG"你对武功的领悟还不够，需要基本技能达到400加转世次数乘以100的等级才可以转世。\n"NOR;
}

int do_agree(string arg)
{
        int i,j,level,rebirth;
        mapping skill;
        object who=this_player();
        object env, link_ob, obj;
        int zslev = who->query("lunhui_zhuanshi");
        string *skillnames,*xing,*ddel,*fa,family;
        seteuid(getuid());
        /*xing=({
               "str", "cor", "int","spi",
               "cps", "per", "con","kar",
               });
        ddel=({
                "gifts",       "dntg",
                "obstacle",     "shengri",
                "12gong",       "mingjie",                               
                "quiz_num",     "secmieyao_mudage",
                "secmieyao",    "secmieyao_killedtime",
                "MKS",          "bellicosity",
                "9sky"
                });*/
	ddel=({
                "obstacle",       "dntg",
                "12gong",       "bellicosity",
		"gift",
         });
        family=who->query("family/family_name");
        
        if(!who->query_temp("c_lunhui") )
	{
                 command("say 你从哪里来？。");
                 return 1;
        }
        if(who->query_temp("c_lunhui") > 1 )
        {
                message_vision("$N"HIR"说道：“红尘淡淡，我欲轮回转世，超度一生的罪孽”。\n\n", who);
                command("say "HIW"既然如此，我现在就上奏佛祖如来，破你红尘之身，圆你超度之意！另赐你"+chinese_number(zslev+1)+"根救命毫毛！\n\n");
               
         	who->add("combat_exp", -(10000000 + zslev * 10000000) );
         	who->add("daoxing", -(10000000 + zslev * 10000000) );
        	who->set("maximum_mana", 0);
         	who->set("max_mana", 0);
         	who->set("max_force", 0);
         	who->set("maximum_force", 0);
         	who->set("mud_age", 100000);
         	who->set("title", HIW"转世轮回"+ HIY"空有一切似云烟"NOR);
          

          	//给此玩家设定转世之后的int+2
		who->set("int", who->query("int") + 2);
        	rebirth = who->query("obstacle/rebirth");


         	//给此玩家消除的参数（哎，重复做一件事是很枯燥的，清理取经等状态）
         	for(i=0;i<sizeof(ddel);i++)
         	{ 
                	who->delete(ddel[i]);
		}
         
         	// 给此玩家skills（哎，也是lying老大坚持的！）
         	skill=who->query_skills();
         	skillnames=keys(skill);
         	for(i=0;i<sizeof(skillnames);i++)
         	{
            		who->set_skill(skillnames[i], 200);
          	}
        	who->set("obstacle/rebirth",rebirth);
                who->add("obstacle/rebirth",-(zslev+1) );
                who->add("lunhui_zhuanshi", 1);
                who->add("lunhui/lunhui",1);
                //who->delete("learned_points");
                who->delete("death");
                who->delete_temp("betray");
		obj = present("huangjin shengyi", who);
		if(objectp(obj))
			destruct(obj);
                who->set("startroom","/d/city/kezhan");

                command("say 你现在极限无量！\n");
                command("chat "HIG"所有一切众生类摄。若卵生若胎生若湿生若化生。若有色若无色。若有想若无想。若非有想若非无想。乃至众生界及假名说。\n\n");
                command("chat "HIR"不应生住法心。不应生住非法心。不应生有所住心。何以故。若心有住则为非住故。\n\n");
                command("chat "HIC"轮回转世空空荡去，世间万物终有一度，"HIR""+who->query("name")+""HIC"破红尘之身，化世俗凡念，心归我佛，轮回转世了。\n\n");

                who->move("/d/city/kezhan");
                env = environment(who);
                link_ob = who->query_temp("link_ob");
	        /*obj = LOGIN_D->make_body(link_ob);
	        if (!obj) return 0;
                who->save();
	        exec(link_ob, who);
	        destruct(who);
                obj->restore();
	        LOGIN_D->enter_world(link_ob, obj, 1);*/
                write(""BLINK""HIY"你经历了第"HIR""+chinese_number(zslev+1)+""HIY"次转世轮回。\n\n"NOR);
                //obj->move(env,1);
	        //obj->write_prompt();         
            
                return 1;  //转世到此为止，与转世相关的文件damage.c，human.c，updated.c
	}    
} 

int accept_fight(object me)
{
        return 0;
}

int accept_kill(object me)
{
        return 1;
}
