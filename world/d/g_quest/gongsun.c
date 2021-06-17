//weiqi...97/12/11

inherit NPC;
#include <quest.h>
string apply_dancer(object me);
string answer_leaving(object me);
int do_yes(string arg);
void do_something();

void create()
{
	set_name("̫ƽ����", ({"taiping gongzhu", "taiping", "gongzhu"}));
	set("age", 32);
	set("gender", "Ů��");
	set("per", 20);
	set("long", "�����Ǵ����쳯̫ƽ�����������е�������ʿ������Ͷ���丮�С�\n��������б�����Ұ�Ĳ�С��\n");
//	set("title", "�����ַ��ϰ���");
	set("attitude", "friendly");

	set("combat_exp", 40000);
	set("max_force", 400);
	set("force", 400);
	set("force_factor", 5);
	set_skill("unarmed", 60);
	set_skill("dodge", 490);
	set_skill("moondance", 520);
	set_skill("parry", 60);
	set_skill("literate", 690);
	set_skill("sword", 290);
	set_skill("snowsword", 290);
	map_skill("dodge", "moondance");
	map_skill("sword", "snowsword");

	set("quest_type", "captor");
	set("inquiry", ([
		"name" : "����...����̫ƽ�����㶼��֪��...\n",
		"here" : "��...����������ʤ���������˴������\n",
		"���" : (: apply_dancer :),
		"��Ů" : (: apply_dancer :),
		"���" : (: apply_dancer :),
		"��Ů" : (: apply_dancer :),
		"leave" : (: answer_leaving :),
		"�뿪" : (: answer_leaving :),
		"mihan": (:give_quest:),
		"�ܺ�": (:give_quest:),
	]) );

	setup();
	carry_object("/d/obj/cloth/skirt")->wear();
	carry_object("/d/obj/cloth/shoes")->wear();
	carry_object("/d/obj/weapon/sword/snow_sword")->wield();
	add_money("silver", 200);
}

void do_something()
{
	command(sprintf("bet %d silver", 1+random(5)));
	call_out ("do_something", 120);	
}

string apply_dancer(object me)
{
	me=this_player();
	if( (string)me->query("gender") == "����" ) 
	{
		return "���Ҫ�����µı����ˣ��ҿɰﲻ�϶���æ��\n";
	}
	else
	{
		if( (string)me->query("class") == "dancer" )
			return "�úøɰɣ��Ժ󲻳�޲��Ϻ��˼ҡ�\n";

		if( (int)me->query("age") >= 30 )
			return "���²����ˣ����ﻹ����Ѱ��·�ɡ�\n";

		message_vision("̫ƽ��������$Nһ��̾�������뷹�ɲ������׳Եġ�\n", me);	
		me->set_temp("dancer_applied", 1);
		return "������������˾��ģ�(yes)\n";
	}
}

string answer_leaving(object me)
{
	me=this_player();
	if( (string)me->query("gender") == "����" ) 
	{
		return "���������ԶԶ�ģ�\n";
	}
	else
	{
		if( (string)me->query("class") == "dancer" )
			return "������ţ���Ҷ�֪���ˣ��벻�뿪����ʲô�ֱ��أ�\n";
		else return "���߰ɣ����ﱾ���Ͳ���Ů����ĵط���\n";
	}
}

void init()
{
	::init();

	remove_call_out("do_something");
	call_out ("do_something", 120);		

	add_action("do_yes", "yes");
}

int do_yes(string arg)
{
	object me;

	me=this_player();
	
	if(me->query_temp("dancer_applied")) 
	{
		message_vision("$N������Ҷ�������ˣ�\n\n", me);
		message_vision("̫ƽ����������$N��ͷ�����úøɣ�ֻҪ�����Ϻ��������ٻ������ֿɵã�\n", me);
		me->delete_temp("dancer_applied");
		me->set("class", "dancer");
		return 1;
	}

	return 0;
}



