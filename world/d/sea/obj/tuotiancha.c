// gangcha.c

#include <weapon.h>
#include <ansi.h>
inherit FORK;
int do_read(string arg);

void create()
{
        set_name("�Ź������", ({ "tuotian fork","fork", "cha"}) );
        set_weight(12000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 5000);
		set("no_sell", 1);
		set("long", "һ���Ź�������Ť�ɵ����棬�������Щ��׭��\n");
		set("wield_msg", "$N�ӱ����ó��ѻ����������������\n");
		set("unwield_msg", "$N��$n�ַŻر���\n");
                set("material", "iron");
        }
        init_fork(60);
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
{       int gain;
        object me=this_player();
        object ob=this_object();

        if(! ob->query("OK_to_STUDY"))
                return notify_fail("���޷�������������ѧ���κζ�����\n");
        if( ob->query("transferred"))
                return notify_fail("���޷�������������ѧ���κζ�����\n");
    	if(environment(me)->query("no_fight") || 
       	environment(me)->query("no_magic") )
          return notify_fail("��ȫ���ڽ�ֹ������\n");


        if( (int)me->query_skill("fork", 1) >= 80 && ( !me->query_temp("cfpl/fork") || me->query_temp("cfpl/fork") >1 ) )
                return notify_fail("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫ǳ�ˡ�\n");
        if( (int)me->query_skill("spells", 1) < 20)
                return notify_fail("�������㷨���������޷��������ķ��䡣\n");

        if( (int)me->query_skill("spells", 1) < (int)me->query_skill("fork", 1) )
                return notify_fail("�������㷨����ỹ�����ʱ�����򲻳�����һ��Ĳ淨��\n");

        if( (int)me->query("kee") < 30)
                return notify_fail("��̫���ˣ�ЪЪ�����ɡ�\n");
        if( (int)me->query("sen") < 30)
                return notify_fail("��̫ƣ���ˣ�ЪЪ�����ɡ�\n");
        gain= (int)me->query_skill("spells", 1)/3 + 1 + random((int)me->query_int());

        me->improve_skill("fork", gain);
	me->receive_damage("kee", 30);
	me->receive_damage("sen", 30);

        write("�����洧Ħ�žŹ�������ϵ�������Ӱ���ƺ��ԡ������淨���������˽⡣\n");
        tell_room( environment(me), me->name() +"˫�۶��žŹ�����棬���ﻹ��֪�ڱȻ�ʲô��\n", ({me}));
        if( me->query_temp("cfpl/fork") && random((int)me->query_int()) > 30 )
	{
		me->set_temp("cfpl/fork",2);
		message_vision(HIC"\n$N��ϸ��Ħ�žŹ�������ϵ�������Ӱ����Ȼ������������������Ӧ��\n"NOR,me);
		message_vision(HIC"\n$N�Ľ���ͻȻӿ��һ��ˮ����ˮ������$N�������˺���ç�֣���\n"NOR,me);
		me->move("/d/sea/maze5");
		message_vision(HIC"\n����ç���Ĵ�������ӿ��$N��������������Ȼ���Ű��������崣�\n"NOR,me);
		message_vision(HIC"\n$NĬ��������������������$N����Ź����������������\n"NOR,me);
		message_vision(HIC"\n$N�ڲ���֮����棬Խ��Խ��˳�֣��������������˳�̡�����������������ĵ���\n"NOR,me);
		message_vision(HIC"\n$N����ʱ��ʼ���򣬶�ʱ�����˷粨ʮ����ľ���֮����\n"NOR,me);
	}
        return 1;
}

