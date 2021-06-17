//modified by vikee for xlqy for NK_DX
//2000-11-23 16:18


#include <ansi.h>

inherit NPC;
void create()
{
        set_name("ħ���", ({ "moli hong", "guangmu tianwang", "hong", "tianwang" }) );
        set("gender", "����" );
	set("long",
		"ħ���Ľ�֮һ��ʹһ�˷��컭ꪣ�����һ��ɡ����Ի������Ԫɡ����\n"
                "ɡ�����鴩�ɣ�����ĸ�̣���ĸ�̣�ҹ���飬�ٳ��飬�ٻ��飬��ˮ\n"
                "�飬�����飬�����飬�����飬�����顣�������鴩�ɡ�װ��Ǭ����\n"
                "���֣����ɡ���ҳţ��ſ�ʱ���ذ��������޹⣬תһתǬ���ζ���\n"
	);
	set("age",50);
	set("title", "��Ŀ����");
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
	set("family/family_name","���ƶ�");
	set_skill("unarmed",240);
	set_skill("moyun-shou", 240);
	set_skill("parry",240);
	set_skill("dodge",240);
	set_skill("spear",240);
	set_skill("wuyue-spear",240);
	set_skill("force",240);
	set_skill("huomoforce",240);
	set_skill("spells", 240);
	set_skill("pingtian-dafa", 240);
	set_skill("moshenbu", 240);
	map_skill("spells", "pingtian-dafa");
	map_skill("force", "huomoforce");
	map_skill("dodge", "moshenbu");
	map_skill("parry", "wuyue-spear");
	map_skill("spear", "wuyue-spear");
	map_skill("unarmed", "moyun-shou");
	set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "spear","buhui" :),
                (: perform_action, "unarmed","zhangxinlei" :),
	}) );
	set("inquiry", ([
		"name" : "���¹�Ŀ����ħ��죬��ʥ�Ͱ��������š�",
		"here" : "�������������, ���ھ�������ˡ�",
	]) );

	setup();
	carry_object("/d/obj/weapon/spear/huaji")->wield();
	carry_object("/d/obj/armor/jinjia")->wear();
}


int accept_fight(object me)
{
        object ob=this_object();

    if( living(ob) )
      {
        message_vision("$N˵����ҲҪ��֪����������������\n", ob);
      }
        return 1;
}

void kill_ob (object me)
{
        object ob=this_object();

    if( living(ob) )
      {
        message_vision("$N˵�������������죡\n", ob);
       }
        ::kill_ob(me);

}

void die()
{
	object who = query_temp("last_damage_from");
	if( objectp(who) && who->query_temp("kill/tianwang") && !who->query_temp("kill/hong") )
	{
		who->add_temp("kill/tianwang",1);
		who->set_temp("kill/hong",1);
		if( who->query_temp("kill/tianwang") == 5 )
		{
			who->delete_temp("kill");
			if( random(who->query("int")) > 20 - random( who->query("lunhui_zhuanshi") ) )
			{
				who->add("qingyun_known",1);
   				message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"�����ؿ�(ji yikao)��" + who->name() + "ɱ���Ĵ�����������������˵�֮����\n\n\n"NOR,users());
			}
			else
			{
				who->set("qingyun_cant",1);
	   			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"�����ؿ�(ji yikao)��" + who->name() + "ɱ���Ĵ���������ϧ��Ե������û�����������˵�֮����\n\n\n"NOR,users());
			}
		}
	}
	::die();
}