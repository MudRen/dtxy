//modified by vikee for xlqy for NK_DX
//2000-11-23 16:18
#include <ansi.h>
inherit NPC;
string send_me(object me);
void create()
{
        set_name("魔礼青", ({ "moli qing", "zengzhang tianwang", "qing", "tianwang" }) );
        set("gender", "男性" );
	set("long",
		"增长天王为四大天王之首, 身高二丈四尺, 善用一杆长枪, \n"
		"枪法登峰造极, 更有密传「青云宝剑」, 「地，水，火，风」\n"
		"四式一出, 大罗金仙也难逃。\n"
	);
	set("age",50);
	set("title", "增长天王");
	set("attitude", "heroism");
	set("family/family_name","将军府");
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


	set_skill("unarmed",240);
	set_skill("dragonfight", 240);
	set_skill("parry",240);
	set_skill("dodge",240);
	set_skill("spear",240);
	set_skill("bawang-qiang",240);
	set_skill("force",240);
	set_skill("lengquan-force",240);
	set_skill("spells", 240);
	set_skill("baguazhou",240);
	set_skill("yanxing-steps", 240);
	map_skill("spells", "baguazhou");
	map_skill("force", "lengquan-force");
	map_skill("dodge", "yanxing-steps");
	map_skill("parry", "bawang-qiang");
	map_skill("spear","bawang-qiang");
	map_skill("unarmed", "dragonfight");
	set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "spear","meihua" :),
	}) );
	set("inquiry", ([
		"name" : "在下增长天王魔礼青，奉圣谕把守西天门。",
		"here" : "这里就是西天门, 入内就是天界了。",
		"回去": (: send_me :),
		"back": (: send_me:),
	]) );

	setup();
	carry_object("/d/obj/fabao/qingyun-baojian");
	carry_object("/d/obj/weapon/spear/jinqiang")->wield();
	carry_object("/d/obj/armor/jinjia")->wear();
}

string send_me(object me)
{
        me=this_player();
	        if( me->is_fighting() )
		return ("刚来就惹麻烦，鬼才要理你！\n");
        if( me->is_busy() || me->query_temp("pending/exercising"))
		return ("忙完再说吧。。。\n");

	message_vision("增长天王哈哈大笑，对$N说道：本王这就送你回去！\n", me);
	message_vision("增长天王飞起一脚把$N踢了下去。。。\n", me);
        me->move("/d/changan/nbridge");
	tell_room( environment(me), "「咕咚」一声，从天上掉下个人来！\n", ({me}));
	write("你从天上摔了下来，搞了个鼻青脸肿！\n");
	return ("老夫脚正痒痒。。。\n");
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
	if( objectp(who) && who->query_temp("kill/tianwang") && !who->query_temp("kill/qing") )
	{
		who->add_temp("kill/tianwang",1);
		who->set_temp("kill/qing",1);
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