//modified by vikee for xlqy for NK_DX
//2000-11-23 16:21

#include <ansi.h>
inherit NPC;
void create()
{
        set_name("魔礼海", ({ "moli hai", "duowen tianwang", "hai", "tianwang" }) );
        set("gender", "男性" );
	set("long",
		"魔家四将之一，使一根盘龙棍，背上一面琵琶，上有四条弦；也按\n"
                "地、水、火、风，拨动弦声，风火齐至，如青云剑一般。\n"
	);
	set("age",50);
	set("title", "多闻天王");
	set("attitude", "heroism");
	set("str",40);
	set("int",30);
	set("max_kee",3100);
	set("kee",3100);
	set("max_sen",3100);
	set("sen",3100);
	set("combat_exp",3000000);
        set("daoxing",3000000);
	set("force",7200);
	set("max_force",3600);
	set("mana",7200);
	set("max_mana",3600);
	set("force_factor", 120);
	set("mana_factor",120);

        set("eff_dx", 1500000);
        set("nkgain", 800);
	set("family/family_name","方寸山三星洞");
	set_skill("unarmed",240);
	set_skill("puti-zhi", 240);
	set_skill("parry",240);
	set_skill("dodge",240);
	set_skill("stick",240);
	set_skill("qianjun-bang",240);
	set_skill("force",240);
	set_skill("wuxiangforce",240);
	set_skill("spells", 240);
	set_skill("dao", 240);
	set_skill("jindouyun", 240);
	map_skill("spells", "dao");
	map_skill("force", "wuxiangforce");
	map_skill("dodge", "jindouyun");
	map_skill("parry", "qianjun-bang");
	map_skill("stick", "qianjun-bang");
	map_skill("unarmed", "puti-zhi");
	set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "stick","pili" :),
                (: perform_action, "unarmed","xpt" :),
	}) );
	set("inquiry", ([
		"name" : "在下多闻天王魔礼海，奉圣谕把守北天门。",
		"here" : "这里就是北天门, 入内就是天界了。",
	]) );

	setup();
	carry_object("/d/sea/obj/dragonstick")->wield();
	carry_object("/d/obj/armor/jinjia")->wear();
}


int accept_fight(object me)
{
        object ob=this_object();

    if( living(ob) )
      {
        message_vision("$N说到：也要你知道本天王的厉害！\n", ob);
      }
        return 1;
}

void kill_ob (object me)
{
        object ob=this_object();

    if( living(ob) )
      {
        message_vision("$N说到：送你上西天！\n", ob);
      }

        ::kill_ob(me);

}

void die()
{
	object who = query_temp("last_damage_from");
	if( objectp(who) && who->query_temp("kill/tianwang") && !who->query_temp("kill/hai") )
	{
		who->add_temp("kill/tianwang",1);
		who->set_temp("kill/hai",1);
		if( who->query_temp("kill/tianwang") == 5 )
		{
			who->delete_temp("kill");
			if( random(who->query("int")) > 20 - random( who->query("lunhui_zhuanshi") ) )
			{
				who->add("qingyun_known",1);
   				message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗姬邑考(ji yikao)：" + who->name() + "杀死四大天王，悟出了琴音伤敌之法！\n\n\n"NOR,users());
			}
			else
			{
				who->set("qingyun_cant",1);
	   			message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗姬邑考(ji yikao)：" + who->name() + "杀死四大天王，可惜机缘不到，没有领悟琴音伤敌之法！\n\n\n"NOR,users());
			}
		}
	}
	::die();
}