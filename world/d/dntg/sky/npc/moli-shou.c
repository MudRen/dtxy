//modified by vikee for xlqy for NK_DX
//2000-11-23 16:21

inherit NPC;
#include <ansi.h>
void create()
{
        set_name("魔礼寿", ({ "moli shou", "chiguo tianwang", "shou", "tianwang", "wang" }) );
        set("gender", "男性" );
        set("long","
四大天王之一，身担着保护后宫安全的重担，非同小可。他
的武功似乎属佛门一派，护国天王还有另外的杀手绝招，但
没有人知道是什么。也许正因为如此，玉皇才放心让他独担
重任。\n"
        );
	set("class", "xian");
	set("title", "持国天王");
	set("family/family_name","将军府");
        set("age",43);
        set("str",30);
        set("int",37);
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


        set_skill("unarmed",240);
	set_skill("dragonfight", 240);
        set_skill("parry",240);
        set_skill("dodge",240);
        set_skill("mace",240);
	set_skill("spells", 240);
	set_skill("baguazhou",240);
        set_skill("wusi-mace",240);
        set_skill("force",240);
        set_skill("literate",240);
        set_skill("lengquan-force",240);
	set_skill("yanxing-steps", 240);
	map_skill("spells", "baguazhou");
	map_skill("force", "lengquan-force");
	map_skill("dodge", "yanxing-steps");
        map_skill("mace","wusi-mace");
        map_skill("parry","wusi-mace");
	map_skill("unarmed", "dragonfight");
	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
                (: perform_action, "mace","andu" :),
	}) );
        set("inquiry", ([
                "name" : "在下就是持国天王，奉圣谕把守东天门。",
                "here" : "这里就是东天门，里面就是天宫。",
        ]) );
        setup();
	carry_object("/d/obj/fabao/biyu-pipa");
        carry_object("/d/obj/weapon/mace/copperjian")->wield();
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
	if( objectp(who) && who->query_temp("kill/tianwang") && !who->query_temp("kill/shou") )
	{
		who->add_temp("kill/tianwang",1);
		who->set_temp("kill/shou",1);
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