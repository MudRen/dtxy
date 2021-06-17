inherit NPC;
#include <ansi.h>
string *first_name = ({ "��","Ǯ","��","��","��","��","֣","��"});
string *name_words = ({ "һ", "��", "��", "��", "��", "��", "��", "��", "��"});
string ask_jueqing();
void create()
{
	string name;
        name = first_name[random(sizeof(first_name))];
        name += name_words[random(sizeof(name_words))];

        set_name(name, ({"lie hu", "hu"}));
	set("title", "�Ի�");
        set("long", "һ��ɽ�����֡�\n");
        set("age", 30+random(20));
	set("attitude", "heroism");
        set("gender", "����");
        set("str", 1000);
        set("int", 20);
        set("per", 30);
        set("con", 30);
        set("combat_exp", 2000000);
	  set("daoxing", 2000000);
	
	  set_skill("unarmed", 180);
	  set_skill("force", 180);
	  set_skill("lengquan-force", 180);
	  set_skill("dodge", 180);
	  set_skill("parry", 180);
	  set_skill("spells", 180);
	  set_skill("baguazhou", 180);
	  set_skill("archery", 300);
	  set_skill("xuanyuan-archery", 300);
	  set_skill("yanxing-steps", 180);
	  map_skill("force", "lengquan-force");
	  map_skill("spells", "baguazhou");
	  map_skill("archery", "xuanyuan-archery");
	  map_skill("dodge", "yanxing-steps");
	
	  set("force", 6000); 
	  set("max_force", 10000);
	  set("force_factor", 160);
	  set("max_mana", 1000);
	  set("mana", 2000);
	  set("mana_factor", 100);
set("inquiry", ([
"name": "�����񣬴���Ϊ����˵��������Ҳ��֪����\n",
"here": "�˵�����ʯɽ��ɽ��Ұ�����࣬���ҪС���ġ�\n",
"ǰ��": (: ask_jueqing :),
]) );

        setup();
        carry_object("/d/obj/armor/shoupi")->wear();
	carry_object("/d/obj/weapon/archery/mugong")->wield();
	carry_object("/d/obj/weapon/archery/zhujian");
}

int accept_object(object me,object ob)
{
       	if( !query("jueqing/qianshi") && me->query_temp("jueqing/houyi") == 1 && ob->query("id") == "qiankun gong" )
       	{
       		command ("jump");
       		command ("say �ñ���ñ��");
       		me->set_temp("jueqing/bow",1);
       		if( me->query_temp("jueqing/arrow") )
       			call_out("wakeup",1,me);
       		call_out("destroy", 2, ob);
       		return 1;
       	}
       	if( !query("jueqing/qianshi") && me->query_temp("jueqing/houyi") == 1 && ob->query("id") == "zhentian jian" )
       	{
       		command ("jump");
       		command ("say �ñ���ñ��");
       		me->set_temp("jueqing/arrow",1);
       		if( me->query_temp("jueqing/bow") )
       			call_out("wakeup",1,me);
       		call_out("destroy", 2, ob);
       		return 1;	
       	}
       	if( me->query_temp("jueqing/houyi") == 2 && ob->query("id") == "jiutian arrow" )
       	{
       		command ("say ����Ϥ����");
       		call_out("destroy", 2, ob);
       		call_out("wakeup1",3,me);
       		return 1;
       	}
       	return 0;
}

void destroy(object ob)
{
        destruct(ob);
        return;
}

void wakeup(object me)
{
        me->delete_temp("jueqing/bow");
        me->delete_temp("jueqing/arrow");
        message_vision(CYN"\n$N���ָ�����Ǭ���������������������������һƬ��â��\n"NOR,this_object(),me);
        message_vision(CYN"\n$N��$n��һ��ãȻ����Щ��㵣���Щ���⡣\n"NOR,this_object(),me);
        message_vision(CYN"\n$NͻȻ���ʹ���쳣�������亹������������ֱ�ס���Դ����ݷ���Щ����Ҫ�Ӽ������������\n"NOR,this_object(),me);
        message_vision(CYN"\n$nһʱ�����޴룬����������״���ͳ����ˡ�����$N����ȥ�ö��ˡ�\n"NOR,this_object(),me);
        set("jueqing/qianshi",1);
        return;
}

string ask_jueqing()
{
	object me=this_player();
	object houyi;
	if( me->query("jueqing/houyi") )
	{
		message_vision(CYN"\n$N����˵���������Ҿ��Ǻ��ࡣ\n"NOR,this_object(),me);
        	houyi = new("/d/moon/npc/houyi");
        	houyi->move(environment(me));
        	destruct(this_object());
	}
      	else if( !query("jueqing/qianshi") )
      	{
	      	return("ǰ���������κ��ţ�������������˭���ܼǵ�ǰ������");
	}
	else if( me->query_temp("jueqing/huoyi") == 2 )
	{
		return("ϣ�������ҵ�����Ҫ�Ķ�����");
	}
      	else
      	{
      		me->set_temp("jueqing/houyi",2);
      		command ("say �ղ�������Ǭ��������������о�����������һЩ����Ҫ�������");
      		command ("say ������Щ����Ӧ�ú͹����й�ϵ������Ǭ�����������������������");
      		return("ϣ������ȥ���������ҵ��ˣ���һ�£��������а취���һָ�ǰ������ģ�");
      	}
}

void wakeup1(object me)
{
        object houyi;
        me->delete_temp("jueqing");
        me->set("jueqing/houyi",1);
        message_vision(CYN"\n$N���ָ����ž���������������ͻȻ������ҫ�۵Ĺ�â��\n"NOR,this_object(),me);
        message_vision(CYN"\n$N��¶ϲɫ��������ϸ��ݷ���������ʲô��\n"NOR,this_object(),me);
        message_vision(CYN"\n$n��������ĸ�Ľ��������һ�������࣬����������\n"NOR,this_object(),me);
        message_vision(CYN"\n$N��$n��ȣ�����һ����˲���ָֻ��򶨣���ó��ȼᶨ������ǰ��ȫ��ͬ�ˡ�\n"NOR,this_object(),me);
        message_vision(CYN"\n$N����������������У�����˵���������Ҿ��Ǻ��ࡣ\n"NOR,this_object(),me);
        houyi = new("/d/moon/npc/houyi");
        houyi->move(environment(me));
        destruct(this_object());
        return;
}