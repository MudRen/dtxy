// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
//change.c
inherit NPC;
#include <ansi.h>
inherit F_MASTER;
string ask_sanshou();
string ask_jueqing();
int do_lianxi();
void create()
{
       set_name("痴梦仙姑",({"chi meng","dream", "fairy"}));
       set("long",
"此乃迷津痴梦仙姑也；不受金银之谢，但遇有缘者渡之！\n");
       set("title", "迷津渡者");
       set("gender", "女性");
       set("age", 18);
       set("class", "xian");
       set("attitude", "friendly");
       set("rank_info/respect", "仙姑");
       set("per", 30);
   set("int", 30);
       set("max_kee", 1000);
       set("max_gin", 1000);
       set("max_sen", 1000);
       set("force", 800);
       set("max_force", 800);
       set("force_factor", 50);
       set("max_mana", 500);
       set("mana", 500);
       set("mana_factor", 40);
       set("combat_exp", 1000000);

        set("eff_dx", 100000);
        set("nkgain", 300);

       set_skill("literate", 90);
       set_skill("parry", 100);
       set_skill("unarmed", 80);
       set_skill("dodge", 100);
       set_skill("force", 120);
       set_skill("whip", 180);
       set_skill("unarmed", 80);
       set_skill("spells", 120);
       set_skill("baihua-zhang", 120);
        set_skill("moonshentong",140);
        set_skill("jueqingbian", 180);
        set_skill("moonforce", 120);
        set_skill("moondance", 100);
        map_skill("spells", "moonshentong");
        map_skill("unarmed", "baihua-zhang");
        map_skill("force", "moonforce");
        map_skill("whip", "jueqingbian");
        map_skill("parry", "jueqingbian");
        map_skill("dodge", "moondance");
        set("inquiry",([
      "绝情": (: ask_jueqing :),
      ]));


create_family("月宫", 2, "弟子");
setup();

       // carry_object("/d/obj/book/lovebook");
        carry_object("/d/obj/cloth/luoyi")->wear();
   carry_object("/d/obj/weapon/whip/jueqingwhip")->wield();
}

void init()
{
        add_action("do_lianxi", "lianxi");
}

string ask_sanshou()
{
    object me=this_player();

    if(me->query("family/family_name") != "月宫" )
                return ("你不是我月宫弟子!!\n");
    if(me->query("faith")<500)
       return ("你对本门做了多少贡献，就想打听三无三不手！");
    if( (string)me->query("gender") !="女性")
                return ("你非为纯阴之身,怎能知哓女儿家的心思??\n");
//    if(me->query("family/master_id") != "chi meng")
//     return ("你不是我的弟子,不传。\n");
    if(me->query("JQB_known"))
      return ("你不是已经知道了么，难道是来戏弄我的！");
    command("pat "+me->query("id"));
    me->set("JQB_known",1);
    return ("你附耳过来，三无三不手乃如此如此...");
}
string ask_jueqing()
{
	object me=this_player();
	if(me->query("family/family_name") != "月宫" )
                return ("你不是我月宫弟子!!\n");
        if( me->query("betray/count") )
		return ("你三心二意无法领会月宫绝学。\n");
        if( (string)me->query("gender") !="女性")
                return ("你非为纯阴之身,怎能知哓女儿家的心思??\n");
        if(me->query("jueqing_known"))
      		return ("绝情中绝情鞭的口诀你都已经知道了啊！");
      	if(me->query("jueqing_cant"))
      		return ("你与绝情无缘！");
      	if(me->query("jueqing/chimeng"))
      		return ("绝情中绝情鞭的口诀你都已经知道了啊！");
      	if( !me->query_temp("jueqing/chimeng") )
      	{
      		me->set_temp("jueqing/chimeng",1);
      		command("sigh");
	      	command("say 问世间情为何物？直叫人生死相许！");
	      	command("say 这么多年过去了，难道师妹还是没有看开吗？！");
	      	return("这月宫莲湖中的莲藕甚是特别，能通心窍，你这就替我帮师妹挖(dig)一根吧！");
	}
	else if( me->query_temp("jueqing/chimeng") == 2 )
	{
		return("好，你果然有心。你先把这莲藕送于嫦娥师妹，回来我便传你绝情鞭的口诀！");
	}
	else if( me->query_temp("jueqing/chimeng") == 3 )
	{
		me->set_temp("jueqing/chimeng",4);
		return("好，情到深处，百炼钢亦能化作绕指柔。绝情鞭虽以绝情为名，实是有情之法。你这就练习（lianxi）一下吧，我自会在一旁指点于你！");
	}
      	else if( me->query_temp("jueqing/chimeng") == 4 )
      	{
      		return("你还是快点练习吧！");
      	}
      	else
      	{
      		return("快去湖底挖(dig)莲藕吧！");
      	}
}
void attempt_apprentice(object ob)
{
        if ( !((string)ob->query("gender")=="女性")){
           command("shake");
           command("say 我们月宫只收女徒，这位" +
   RANK_D->query_respect(ob) + "还是另请高就吧。\n");
           return ;
        }
//if (random(this_player()->query_kar()) < 3 || this_player()->query("mark/moon_chimeng")){
//     this_player()->set("mark/moon_chimeng", 1);
//     command("shake");
//     command("say 你我无缘，还是另请高就吧。\n");
//     return ;
//   }
        else{
   command("pat "+ob->query("id"));
        command("say 既然" + RANK_D->query_respect(ob) +
"与我有缘，我就收下你了。\n");
        command("recruit " + ob->query("id") );
        return ;
}
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "xian");
     ob->set("title", HIM"痴梦仙姑亲传弟子"NOR);
}

int do_lianxi()
{
	object me=this_player();
	object weapon = me->query_temp("weapon");
	if( me->query_temp("jueqing/chimeng") != 4 )
		return 0;
	if( me->query_temp("lianxi") )
		return notify_fail("你正在练习！\n");
	if( me->is_busy() )
		return notify_fail("你正在忙着呢！\n");
	 if (!objectp(weapon)
                || (string)weapon->query("skill_type") != "whip")
                        return notify_fail("没有鞭子怎么练习绝情鞭？\n");
	me->set_temp("lianxi",1);
	me->set_temp("no_move",1);
	me->start_busy(10);
	message("vision", "你默念痴梦仙姑传授的口诀，开始练习绝情鞭。\n", environment());
	call_out("check",2,me,1);
	return 1;
}

int check( object me,int kk)
{
	if( !me )	
		return 1;
	if( environment(me) != environment(this_object()) )
	{
		tell_object(me,"你离开了湖边，失去了痴梦的指点，无法继续练习绝情鞭了！");
		me->delete_temp("lianxi");
		return 1;
	}
	if( !me->is_busy() )
		me->start_busy(3);
	remove_call_out("check");
	if( kk < 8 ) 
		call_out("check",2,me,kk+1);
	else
	{
		me->delete_temp("no_move");
		me->set("jueqing/chimeng",1);
                me->delete_temp("lianxi");
                me->delete_temp("jueqing/chimeng");	
	}
	switch (kk)
        {
        	case 1:
                { 
                      	message_vision("$N纤腰急转，皓腕轻抖，使出一式"HIM"「天地双飞」"NOR"。\n",me);
                        break;
                }
                case 2:
                { 
                      	message_vision("$N舞出一式"HIM"「君应有语」"NOR"，神色凄楚惘然。\n",me);
                        break;
                }
                case 3:
                { 
                      	tell_object(me,"\n\n耳边传来痴梦的声音：好，意在招先，果然悟性过人。\n\n");
                      	message_vision("$N心头缠绵婉转，使出"HIM"「万里层云」"NOR"，招虽断意相连。\n",me);
                        break;
                }
                case 4:
                { 
                      	message_vision("只见$N一路"HIM"「寂寞箫鼓」"NOR"，使得回风舞雪，暗合韵理，虽无丝竹之音，反倒别有幽愁暗恨生，此时无声胜有声。\n",me);
                        break;
                }
                case 5:
                { 
                      	tell_object(me,"\n\n耳边传来痴梦的声音：日月穿梭，纵是千秋万古，若痴心不变，情亦不变。\n\n");
                      	message_vision("忽然间$N鞭势陡变，浏漓顿挫，古意盎然，一式"HIM"「千秋万古」"NOR"如月之曙，如气之秋，纵有千载情愁，亦化于这一招之中。\n",me);
                        break;
                }
                case 6:
                { 
                	tell_object(me,"\n\n耳边传来痴梦的声音：绝情鞭的精髓尽在一个情字，若要知情首先就要入情。\n\n");
                      	message_vision("$N随手舞出一招，但见鞭意缱绻缠绵，如泣如诉，犹似双丝网，中有千千结，直是剪之不断，理之还乱。\n",me);
                        break;
                }
                case 7:
                { 
                      	message_vision("$N心有所悟，终于鞭人合一舞出了"HIM"「生死相许」"NOR"，只见$N袖舞时幻起花雨满天，鞭落处化作断霞千缕。\n",me);
                        break;
                }
                case 8:
                { 
                      	tell_object(me,"\n\n痴梦说道：好，好。这么短的时间就能悟出绝情鞭的精髓，我也没什么好教你的了，你就去找嫦娥师妹吧！\n\n");
                      	message_vision("\n$N停下练习，定睛一看，只见身边残荷满地，痴梦正在一旁含笑看着$N。\n",me);
                        break;
                }
	}
	return 1;
}
