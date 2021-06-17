//modified by vikee for xlqy for NK_DX
//2000-11-23 16:21

#include <ansi.h>
inherit NPC;
void create()
{
        set_name("ħ��", ({ "moli hai", "duowen tianwang", "hai", "tianwang" }) );
        set("gender", "����" );
	set("long",
		"ħ���Ľ�֮һ��ʹһ��������������һ�����ã����������ң�Ҳ��\n"
                "�ء�ˮ���𡢷磬������������������������ƽ�һ�㡣\n"
	);
	set("age",50);
	set("title", "��������");
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
	set("family/family_name","����ɽ���Ƕ�");
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
		"name" : "���¶�������ħ�񺣣���ʥ�Ͱ��ر����š�",
		"here" : "������Ǳ�����, ���ھ�������ˡ�",
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