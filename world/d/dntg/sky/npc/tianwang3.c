//modified by vikee
//2000.10
inherit NPC;
#include "huoyannpc2.h"

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
	set("str",40);
	set("int",30);
	set("max_kee",1100);
	set("kee",1100);
	set("max_sen",1100);
	set("sen",1100);
	set("combat_exp",2000000);
    set("daoxing",1500000);
	set("force",2500);
	set("max_force",1500);
	set("mana",2500);
	set("max_mana",1600);
	set("force_factor", 80);
	set("mana_factor",80);
	
    
    set("nkgain", 800);

	set_skill("sword",200);
	set_skill("bainiao-jian", 200);
	set_skill("parry",200);
	set_skill("dodge",200);
	set_skill("throwing",200);
	set_skill("ningxie-force",200);
	set_skill("force",200);
	set_skill("spells", 200);
	set_skill("moshenbu", 200);
	map_skill("dodge", "moshenbu");
	map_skill("parry", "bainiao-jian");
	map_skill("sword","bainiao-jian");
	map_skill("force", "ningxie-force");
	set("inquiry", ([
		"name" : "������������ħ���࣬��ʥ�Ͱ��������š�",
		"here" : "�������������, ���ھ�������ˡ�",
		"��ȥ": (: send_me :),
		"back": (: send_me:),
	]) );

	setup();
carry_object("/d/sky/obj/zhanyaojian")->wield();
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

void hurting(object me, object ob)
{
   remove_call_out("hurting");

   if(environment(me)!=environment(ob) || !me->is_fighting()) return;
   me->command_function("perform chaofeng");

   call_out("hurting",5+random(6),me,ob);
}

