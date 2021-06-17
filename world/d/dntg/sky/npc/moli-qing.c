//modified by vikee for xlqy for NK_DX
//2000-11-23 16:18
#include <ansi.h>
inherit NPC;
string send_me(object me);
void create()
{
        set_name("ħ����", ({ "moli qing", "zengzhang tianwang", "qing", "tianwang" }) );
        set("gender", "����" );
	set("long",
		"��������Ϊ�Ĵ�����֮��, ��߶����ĳ�, ����һ�˳�ǹ, \n"
		"ǹ���Ƿ��켫, �����ܴ������Ʊ�����, ���أ�ˮ���𣬷硹\n"
		"��ʽһ��, ���޽���Ҳ���ӡ�\n"
	);
	set("age",50);
	set("title", "��������");
	set("attitude", "heroism");
	set("family/family_name","������");
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
		"name" : "������������ħ���࣬��ʥ�Ͱ��������š�",
		"here" : "�������������, ���ھ�������ˡ�",
		"��ȥ": (: send_me :),
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
		return ("���������鷳�����Ҫ���㣡\n");
        if( me->is_busy() || me->query_temp("pending/exercising"))
		return ("æ����˵�ɡ�����\n");

	message_vision("��������������Ц����$N˵����������������ȥ��\n", me);
	message_vision("������������һ�Ű�$N������ȥ������\n", me);
        me->move("/d/changan/nbridge");
	tell_room( environment(me), "�����ˡ�һ���������ϵ��¸�������\n", ({me}));
	write("�������ˤ�����������˸��������ף�\n");
	return ("�Ϸ��������������\n");
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