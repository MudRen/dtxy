inherit NPC;
#include <ansi.h>
string ask_jiutian();
string ask_change();
void create()
{
        set_name("����", ({"hou yi"}));
  	set("gender", "����" );
    	set("title","�������");
        set("long", "�����Ǵ�˵������Ÿ�̫���Ĵ�Ӣ�ۡ�\n");
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
   	"����": (: ask_jiutian :),
   	"�¹�": (: ask_change :),
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
	      	return("Ҫ��ǰ���¹�Ҳ���ԣ�������Ҫ��Ū���׵�������࣡");
	}
	else if( me->query_temp("jueqing/sun") == 1 )
	{
		command ("say �ã���Ȼ��Ҫ̫����İ������Ҿ�����һ�̣�");
		message_vision(HIC"\nֻ��$Nȡ�¾�����������������$n�Ͻ�����׼����\n"NOR,this_object(),me);
		message_vision(HIC"\n$N���һ���������ˡ�$nֻ��һ�ɾ޴����������$nֱ�ɾ���֮�⣡\n"NOR,this_object(),me);
		me->move("/d/moon/9sky/9sky");
		return ("���졢̫���񡣡���");
	}
	else
	{
		command("touchy");
		command("say ��ǧ���ˣ�����Ū���������̫࣬��л���ˣ�");
		command("say ���������ȥ�¹����϶𣬲�֪�������ںò��ã�");
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
			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"������ĸ(xi wangmu)��" + me->name() + "��ħ�硢����꣬���֯Ůţ�ɣ�Ѱ���ࡢ�Ͼ��죬�ƽ�ǧ�����š�����������������⣬������"+HIB"[����]"+HIC"�İ��أ�\n\n\n"NOR,users());
			message_vision(HIC"\n���������$N��ϲ��\n"NOR,me);
			return("��ϲ��ϲ��");
		}
		else
		{
			me->set("jueqing_cant",1);
			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"������ĸ(xi wangmu)��" + me->name() + "��ħ�硢����꣬���֯Ůţ�ɣ�Ѱ���ࡢ�Ͼ��죬�ƽ�ǧ�����š�ȴ����᲻�����������⣬�޷�����"+HIB"[����]"+HIC"�����հ��أ�\n\n\n"NOR,users());
			message_vision(HIC"\n���һ��ο$N��\n"NOR,me);
			return("��Ҫ���ģ��ȿݹ�д��ת�������л����Ŷ��");
		}
	}
}

string ask_jiutian()
{
	object me=this_player();
	
      	if( !me->query_temp("jueqing/sun") )
      	{
	      	return("����֮�ϣ�����̫����ĵ��̣�����ȥΣ�յĺܰ���");
	}
	else
	{
		command ("say �ã��Ҿ�����һ�̣�");
		message_vision(HIC"\nֻ��$Nȡ�¾�����������������$n�Ͻ�����׼����\n"NOR,this_object(),me);
		message_vision(HIC"\n$N���һ���������ˡ�$nֻ��һ�ɾ޴����������$nֱ�ɾ���֮�⣡\n"NOR,this_object(),me);
		me->move("/d/moon/9sky/9sky");
		return ("���졢̫���񡣡���");
	}
}