inherit NPC;
#include <ansi.h>
string ask_jiutian();
string ask_change();
void create()
{
        set_name("后羿", ({"hou yi"}));
  	set("gender", "男性" );
    	set("title","落日神箭");
        set("long", "他就是传说中射落九个太阳的大英雄。\n");
    	set("age", 25);
  	set("str", 1000);
      	set("combat_exp", 5000000);
        set("daoxing", 500000);
  	set("attitude", "friendly");
    	set("per", 30);
  	set_skill("unarmed", 180);
	set_skill("force", 180);
	set_skill("lengquan-force", 180);
	set_skill("dodge", 180);
	set_skill("parry", 180);
	set_skill("spells", 180);
	set_skill("baguazhou", 180);
	set_skill("archery", 600);
	set_skill("xuanyuan-archery", 600);
	set_skill("yanxing-steps", 180);
	map_skill("force", "lengquan-force");
	map_skill("spells", "baguazhou");
	map_skill("archery", "xuanyuan-archery");
	map_skill("dodge", "yanxing-steps");
	set("inquiry",([
   	"九天": (: ask_jiutian :),
   	"月宫": (: ask_change :),
   	]));
	set("force", 6000); 
	set("max_force", 10000);
	set("force_factor", 160);
	set("max_mana", 1000);
	set("mana", 2000);
	set("mana_factor", 100);
  	setup();
    	carry_object("/d/obj/cloth/surcoat")->wear();
      	carry_object("/d/moon/obj/jiutian-arrow");
}

string ask_change()
{
	object me=this_player();
	object change;
      	if( !me->query_temp("jueqing/sun") )
      	{
	      	return("要我前往月宫也可以，不过我要先弄明白当年的真相！");
	}
	else if( me->query_temp("jueqing/sun") == 1 )
	{
		command ("say 好，既然需要太阳神的帮助，我就送你一程！");
		message_vision(HIC"\n只见$N取下九天神箭，拉弓搭箭，$n赶紧做好准备。\n"NOR,this_object(),me);
		message_vision(HIC"\n$N大喝一声：出发了。$n只觉一股巨大的力量带着$n直飞九天之外！\n"NOR,this_object(),me);
		me->move("/d/moon/9sky/9sky");
		return ("九天、太阳神。。。");
	}
	else
	{
		command("touchy");
		command("say 几千年了，终于弄明白了真相，太感谢你了！");
		command("say 我这就随你去月宫见嫦娥，不知道她现在好不好！");
		this_object()->move("/d/moon/wangmu_room");
		change = present("chang e",load_object("/d/moon/change_room"));
		if( !change ) change = new("/d/moon/npc/change");
		change->move("/d/moon/wangmu_room");
		me->move("/d/moon/wangmu_room");
		me->delete_temp("jueqing");
		me->delete("jueqing");
		if( random(me->query("int")) > 30 - random( me->query("lunhui_zhuanshi") ) )
		{
			me->add("jueqing_known",1);
			message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗西王母(xi wangmu)：" + me->name() + "闯魔界、夺冰魂，玉成织女牛郎，寻后羿、上九天，破解千古谜团。最终领会世间真情意，掌握了"+HIB"[绝情]"+HIC"的奥秘！\n\n\n"NOR,users());
			message_vision(HIC"\n大家齐声向$N道喜！\n"NOR,me);
			return("恭喜恭喜！");
		}
		else
		{
			me->set("jueqing_cant",1);
			message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗西王母(xi wangmu)：" + me->name() + "闯魔界、夺冰魂，玉成织女牛郎，寻后羿、上九天，破解千古谜团。却看领会不到世间真情意，无法掌握"+HIB"[绝情]"+HIC"的最终奥秘！\n\n\n"NOR,users());
			message_vision(HIC"\n大家一起安慰$N！\n"NOR,me);
			return("不要灰心，等枯骨写出转世来还有机会的哦！");
		}
	}
}

string ask_jiutian()
{
	object me=this_player();
	
      	if( !me->query_temp("jueqing/sun") )
      	{
	      	return("九天之上，那是太阳神的地盘，你上去危险的很啊！");
	}
	else
	{
		command ("say 好，我就送你一程！");
		message_vision(HIC"\n只见$N取下九天神箭，拉弓搭箭，$n赶紧做好准备。\n"NOR,this_object(),me);
		message_vision(HIC"\n$N大喝一声：出发了。$n只觉一股巨大的力量带着$n直飞九天之外！\n"NOR,this_object(),me);
		me->move("/d/moon/9sky/9sky");
		return ("九天、太阳神。。。");
	}
}