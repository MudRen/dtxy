#include <weapon.h>
#include <ansi.h>
inherit HAMMER;
int do_read(string arg);

void create()
{
        set_name("�˰�÷����", ({ "meihua hammer", "hammer" }) );
        set_weight(12000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�ѷְ˰��÷��״��ͭ�����������Щ��׭��\n");
                set("value", 5000);
		set("no_sell", 1);
                set("material", "iron");
                set("wield_msg", "$N�ó�һ��$n��������������Ȼ���������С�\n");
                set("unwield_msg", "$N�������е�$n��\n");
        }
        init_hammer(60);
        setup();
}

void init()
{
 object me = this_object();
  object where = environment();

  if (interactive(where))
  {
    if (me->query("owned"))
    {
      if (me->query("owned")!=where->query("id"))
      {
	me->set("transferred", 1);
      }
    }
    else
    {
      me->set("owned",where->query("id"));
    }
  }

        add_action("do_read", "read");
}

int do_read(string arg)
{	int gain;
	object me=this_player();
	object ob=this_object();
	
	if(! ob->query("OK_to_STUDY"))
		return notify_fail("���޷�������������ѧ���κζ�����\n");
	if( ob->query("transferred"))
		return notify_fail("���޷�������������ѧ���κζ�����\n");
    	if(environment(me)->query("no_fight") || 
       	environment(me)->query("no_magic") )
          return notify_fail("��ȫ���ڽ�ֹ������\n");

	if( (int)me->query_skill("hammer", 1) >= 60 && !me->query_temp("cfpl/hammer") )
		return notify_fail("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫ǳ�ˡ�\n");
	if( (int)me->query_skill("spells", 1) < 20)
		return notify_fail("�������㷨���������޷��������ķ��䡣\n");

	if( (int)me->query_skill("spells", 1) < (int)me->query_skill("hammer", 1) )
		return notify_fail("�������㷨����ỹ�����ʱ�����򲻳�����һ��Ĵ�����\n");

	if( (int)me->query("kee") < 30)
		return notify_fail("��̫���ˣ�ЪЪ�����ɡ�\n");
	if( (int)me->query("sen") < 30)
		return notify_fail("��̫ƣ���ˣ�ЪЪ�����ɡ�\n");

	gain= (int)me->query_skill("spells", 1)/3 + 1 + random((int)me->query_int());

	me->improve_skill("hammer", gain);
	me->receive_damage("kee", 30);
	me->receive_damage("sen", 30);

	write("�����洧Ħ�Ű˰�÷�����ϵ�������Ӱ���ƺ��ԡ������������������˽⡣\n");
	tell_room( environment(me), me->name() +"˫�۶��Ű˰�÷���������ﻹ��֪�ڱȻ�ʲô��\n", ({me}));
	if( me->query_temp("cfpl/hammer") && random((int)me->query_int()) > 30 )
	{
		me->start_busy(20);
		me->delete_temp("cfpl");
		message_vision(HIC"\n$N��ϸ��Ħ�Ű˰�÷�����ϵ�������Ӱ����Ȼ������������������Ӧ��\n"NOR,me);
		if( base_name(environment(me)) != "/d/sea/inside1" )
		{
			message_vision(HIC"\n$N�Ľ���ͻȻӿ��һ��ˮ����ˮ������$N�������������㳡����\n"NOR,me);
			me->move("/d/sea/inside1");
		}
		message_vision(HIC"\n$N�����ף���������������ʢ��\n"NOR,me);
		message_vision(HIC"\n$N���ܺ�ˮ��ʼ��������������һ����ͷ������$N���߸�����\n"NOR,me);
		message_vision(HIC"\n$N������֣����������������ͣ��ݷ�Ҫ���������\n"NOR,me);
		message_vision(HIC"\n$Nһ������������ͻȻ��ת���£�����������׹�������ף����а˰�÷����ֱ�����£�\n"NOR,me);
		call_out("finish1",1,me);	
	}
	return 1;
}

void finish1(object me)
{
	message_vision(HIC"\n���顱��һ�����죬�˰�÷�������ػ��ڵ��ϣ������㳡����ʯ���\n"NOR,me);
	message_vision(HIC"\n�����������ҵ�ҡ�Σ��������༤��������ˣ�\n"NOR,me);
	message_vision(HIC"\n$N�������ŵ��ϴ�ӣ��������������Լ�һ�����£�\n"NOR,me);
	call_out("finish2",3,me);	
	return;
}
void finish2(object me)
{
	string str = "/d/sea/npc/long";
	string msg;
	int i;
	object longzi;
	message_vision(HIC"\n�������ˣ��Ĵ���ڣ�һʱ�ҳ�һ�š�\n"NOR,me);
	for(i=1;i<10;i++)
	{
		msg = str + i;
		longzi = new(msg);
		longzi->move(environment(me));
	}
	message_vision(HIC"\nͻȻ����ˮ��ӿ���������Ӵ������˳�������\n"NOR,me);
	message_vision(HIC"\n�������ӿ������ϴ�ӣ���Ȼһʱ˵����������\n"NOR,me);
	call_out("finish3",3,me);	
	return;
}

void finish3(object me)
{
	string str = "/d/sea/npc/";
	string msg;
	object longzi;
	message_vision(HIC"\n�������ˣ��Ĵ���ڣ�һʱ�ҳ�һ�š�\n"NOR,me);
	msg = str + "longpo";
	longzi = new(msg);
	longzi->move(environment(me));
	message_vision(HIC"\nͻȻһ��ˮ��ӿ�����ž����̴̻������˳�������\n"NOR,me);
	message_vision(HIC"\n������Щ����ʧ�룺�ǲ�����ֻ���������ˣ���\n"NOR,me);
	msg = str + "longwang";
	longzi = new(msg);
	longzi->move(environment(me));
	message_vision(HIC"\nͻȻһ��ˮ��ӿ�������������˳�������\n"NOR,me);
	message_vision(HIC"\n���㣺˭���ڴ�������������\n"NOR,me);
	call_out("finish4",3,me);	
	return;
}

void finish4(object me)
{
	object mazu;
	message_vision(HIC"\n���д�����������������ĪҪ���̣�����������֮ϲ����������޺ù㳡�ʹ�ɢȥ�ɣ�\n"NOR,me);
	message_vision(HIC"\nһ��ˮ����$N�ŵ�ӿ�𣬽�$N�͵��˴����\n"NOR,me);
	me->set("cfpl_lingwu",1);
	me->move("/d/dntg/donghai/mazeend");
	if(!(mazu = present("ma zu",environment(me))))
	{
		mazu=new("/d/sea/npc/shuishen");
		mazu->move(environment(me));
	}
	mazu->command("pat " + me->query("id"));
	mazu->command("say ����ڴ˾�������lingwu���ɣ�");
	me->start_busy(1);
	return;
}